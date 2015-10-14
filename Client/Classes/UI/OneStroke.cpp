#include "OneStroke.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/MessageCenter.h"
#include "Net/NetDispatcher.h"
#include "GameScene/Chests.h"

#define Path_Res_DotNormal			("assets/ui/SmallGame/img_weixuanzedi.png")
#define Path_Res_DotSelected		("assets/ui/SmallGame/img_xuanzedi.png")
#define Path_Res_LineNormal			("assets/ui/SmallGame/img_weixuanzexian.png")
#define Path_Res_LineSelected		("assets/ui/SmallGame/img_xuanzexian.png")
#define Path_Res_MagicLineNormal	("assets/ui/SmallGame/img_xuanzexian.png")
#define Path_Res_MagicLineError		("assets/ui/SmallGame/img_xuanzexianhong.png")

COneStroke::COneStroke()
	:GameUI(IDU_OneStrokeUI,JsonFile_OneStrokeUI)
	,m_nStrokeId(0)
	,m_magicLine(nullptr)
	,m_pCountNum(nullptr)
	,m_nLeftTime(0)
	,m_nMaxTime(0)
	,m_nItemBoxId(0)
{

}

COneStroke::~COneStroke()
{
	m_dots.clear();
	m_lines.clear();
}

bool COneStroke::onInit()
{
	do 
	{
		Button* pBtnClose = (Button*)Helper::seekWidgetByName(m_pWidget,"BtnClose");
		Button* pBtnReset = (Button*)Helper::seekWidgetByName(m_pWidget,"Reset");
		Button* pBtnKey = (Button*)Helper::seekWidgetByName(m_pWidget,"BtnKey");
		m_pKeyNum = (Text*)Helper::seekWidgetByName(m_pWidget,"KeyCount");
		BREAK_IF(!(pBtnClose&&pBtnReset&&pBtnKey&&m_pKeyNum));
		pBtnClose->addTouchEventListener(this,toucheventselector(COneStroke::clickCloseBtn));
		pBtnReset->addTouchEventListener(this,toucheventselector(COneStroke::clickResetBtn));
		pBtnKey->addTouchEventListener(this,toucheventselector(COneStroke::clickKeyBtn));

		m_magicLine = CMagicLine::create(Point::ZERO,Point::ZERO,Path_Res_MagicLineNormal,Path_Res_MagicLineError);
		m_magicLine->setLocalZOrder(StrokeZOrder_MagicLine);
		m_magicLine->SetStartFixed(false);
		m_pWidget->addChild(m_magicLine);

		m_pWidget->setTouchEnabled(true);
		m_pWidget->addTouchEventListener(this,toucheventselector(COneStroke::touchEvent));

		m_pCountNum = Label::createWithBMFont("assets/common/font/timer.fnt",CCString::createWithFormat("60")->getCString());
		m_pCountNum->setPosition(Point(1170,150));
		m_pWidget->addChild(m_pCountNum);

		return true;
	} while (0);
	return false;
}

void COneStroke::onOpen()
{
	m_pCountNum->setString("");
}

void COneStroke::onClose()
{
	unschedule(SEL_SCHEDULE(&COneStroke::ScheduleLeftTime));

	CChests* pChests = dynamic_cast<CChests*>(gMap->getObjectManager()->getObject(GetItemBoxId()));
	if(pChests)
	{
		pk::C2GS_OPEN_TREAS_Req cmd;
		cmd.id = GetItemBoxId();
		cmd.open_state = (int)CChests::ChestsStatus_Idle;
		cmd.Send(gNetSocket);
	}
	SetItemBoxId(0);
}

void COneStroke::InitStrokeInfo(int nStrokeId)
{
	if(GetStrokeId() == nStrokeId)
	{
		ResetStrkeInfo();
		return;
	}

	ClearStrkeInfo();

	One_strokeCfg* pOneStrokeCfg = OneStrokeData.get(nStrokeId);
	if(!pOneStrokeCfg) return;
	vector<string> dotPositions;
	StringSplit(pOneStrokeCfg->dot,";",dotPositions);
	m_dots.clear();
	for (size_t i=0; i<dotPositions.size(); ++i)
	{
		vector<int> pos;
		StringSplitToInt(dotPositions[i],",",pos);
		CDot* pDot = CDot::create(Path_Res_DotNormal,Path_Res_DotNormal,Path_Res_DotSelected,Path_Res_DotNormal,Path_Res_DotNormal);
		pDot->SetRadius(pDot->getSize().width/2);
		pDot->setPosition(Point(pos[0],pos[1]));
		pDot->setTouchEnabled(false);
		pDot->setLocalZOrder(StrokeZOrder_Dot);
		m_pWidget->addChild(pDot);
		m_dots.push_back(pDot);
	}
	vector<string> lineCfgs;
	StringSplit(pOneStrokeCfg->line,";",lineCfgs);
	for (size_t i=0; i<lineCfgs.size(); ++i)
	{
		vector<int> lineCfg;
		StringSplitToInt(lineCfgs[i],",",lineCfg);
		size_t nDotIdxStart = lineCfg[0] - 1;
		size_t nDotIdxEnd = lineCfg[1] - 1;
		CLine* pLine = CLine::create(m_dots[nDotIdxStart]->getPosition(),m_dots[nDotIdxEnd]->getPosition(),Path_Res_LineNormal,Path_Res_LineSelected);
		pLine->setLocalZOrder(StrokeZOrder_Line);
		m_pWidget->addChild(pLine);
		m_lines.push_back(pLine);
	}

	SetStrokeId(nStrokeId);
	SetMaxTime(pOneStrokeCfg->max_time);
	SetLeftTime(pOneStrokeCfg->max_time);
	unschedule(SEL_SCHEDULE(&COneStroke::ScheduleLeftTime));
	schedule(SEL_SCHEDULE(&COneStroke::ScheduleLeftTime),1.0f,GetMaxTime()+1,0.0f);
}

void COneStroke::ClearStrkeInfo()
{
	for (size_t i=0; i<m_dots.size(); ++i)
	{
		m_dots[i]->removeFromParent();
	}
	m_dots.clear();
	for (size_t i=0; i<m_lines.size(); ++i)
	{
		m_lines[i]->removeFromParent();
	}
	m_lines.clear();
	m_magicLine->SetStartFixed(false);
}

void COneStroke::ResetStrkeInfo()
{
	for (size_t i=0; i<m_dots.size(); ++i)
	{
		m_dots[i]->setSelectedState(false);
	}
	for (size_t i=0; i<m_lines.size(); ++i)
	{
		m_lines[i]->SetPainted(false);
	}
	m_magicLine->SetStartFixed(false);

	unschedule(SEL_SCHEDULE(&COneStroke::ScheduleLeftTime));
	SetLeftTime(GetMaxTime());
	schedule(SEL_SCHEDULE(&COneStroke::ScheduleLeftTime),1.0f,GetMaxTime()+1,0.0f);
}

void COneStroke::touchEvent(Ref* pSender, TouchEventType type)
{
	Widget* pWidget = (Widget*)pSender;
	Point posStart = pWidget->getTouchStartPos();
	Point posMoved = pWidget->getTouchMovePos();
	Point posEnd = pWidget->getTouchEndPos();
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
		{
			if (m_magicLine->IsStartFixed())
			{
				m_magicLine->SetPosEnd(posStart);
				CheckAndPaintedLine();
			} 
			else
			{
				FixMagicLine(posStart);
			}
		}
		break;
	case TOUCH_EVENT_MOVED:
		{
			if (m_magicLine->IsStartFixed())
			{
				m_magicLine->SetPosEnd(posMoved);
				CheckAndPaintedLine();
			} 
		}
		break;
	case TOUCH_EVENT_ENDED:
		{
			if (m_magicLine->IsStartFixed())
			{
				m_magicLine->SetPosEnd(posEnd);
				CheckAndPaintedLine();
			} 
		}
		break;
	default:
		break;
	}
}

void COneStroke::FixMagicLine(const Point touchPosStart)
{
	for (size_t i=0; i<m_dots.size(); ++i)
	{
		if (m_dots[i]->ContainPoint(touchPosStart))
		{
			m_magicLine->SetPosStart(m_dots[i]->getPosition());
			m_magicLine->SetPosEnd(m_dots[i]->getPosition());
			m_dots[i]->setSelectedState(true);
			m_magicLine->SetStartFixed(true);
			break;
		}
	}
}

void COneStroke::CheckAndPaintedLine()
{
	size_t numPainted = 0;
	bool oneLinePainted = false;
	bool bMagicCanBeLine = false;

	for (size_t dotNum=0; dotNum<m_dots.size(); ++dotNum)
	{
		if(m_dots[dotNum]->ContainPoint(m_magicLine->GetPosStart()))
		{
			continue;;
		}

		if(m_dots[dotNum]->ContainPoint(m_magicLine->GetPosEnd()))
		{
			bMagicCanBeLine = true;
			for (size_t lineNum=0; lineNum<m_lines.size(); ++lineNum)
			{
				if (m_lines[lineNum]->ContainPos(m_magicLine->GetPosStart(),m_dots[dotNum]->getPosition()))
				{
					if(!m_lines[lineNum]->IsPainted())
					{
						m_lines[lineNum]->SetPainted(true);
						m_dots[dotNum]->setSelectedState(true);
						m_magicLine->SetPosStart(m_dots[dotNum]->getPosition());
						oneLinePainted = true;
					}
				}

				if(m_lines[lineNum]->IsPainted())
				{
					numPainted++;
				}
			}
			break;
		}
	}
	if(!oneLinePainted && bMagicCanBeLine)
	{
		m_magicLine->RunBlinkAction();
	}
	if (numPainted >= m_lines.size())
	{
		pk::C2GS_OPEN_TREAS_Succ_Req cmd;
		cmd.id = GetItemBoxId();
		cmd.Send(gNetSocket);  

		MessagePrompt("success");
		gGameUILayer->close(this);
	}
}

void COneStroke::ScheduleLeftTime(float dt)
{
	if (m_nLeftTime>=0)
	{
		m_pCountNum->setString(CCString::createWithFormat("%d",GetLeftTime())->getCString());
		SetLeftTime(GetLeftTime()-1);
	}
	else
	{
		unschedule(SEL_SCHEDULE(&COneStroke::ScheduleLeftTime));
		gGameUILayer->close(this);
	}
}

void COneStroke::clickCloseBtn(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
	}
}

void COneStroke::clickResetBtn(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		ResetStrkeInfo();
	}
}

void COneStroke::clickKeyBtn(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		//to do
	}
}

CDot* CDot::create(const std::string& backGround,
				   const std::string& backGroundSeleted,
				   const std::string& cross,
				   const std::string& backGroundDisabled,
				   const std::string& frontCrossDisabled,
				   TextureResType texType)
{
	CDot *pDot = new CDot;
	if (pDot && pDot->init(backGround,backGroundSeleted,cross,backGroundDisabled,frontCrossDisabled,texType)) {
		pDot->setSelectedState(false);
		pDot->autorelease();
		return pDot;
	}
	CC_SAFE_DELETE(pDot);
	return nullptr;
}

bool CDot::ContainPoint(const Point& pos)
{
	Rect RectDot = Rect(getPositionX()-GetRadius(),getPositionY()-GetRadius(),2*GetRadius(),2*GetRadius());
	return RectDot.containsPoint(pos);
}

CLine* CLine::create(	 Point posStart,
						 Point posEnd,
						 const std::string& normalImg,
						 const std::string& SelectedImg,
						 TextureResType texType	)
{
	CLine *pLine = new CLine;
	if (pLine && pLine->init(posStart,posEnd,normalImg,SelectedImg,texType))
	{
		pLine->autorelease();
		return pLine;
	}
	CC_SAFE_DELETE(pLine);
	return nullptr;
}

CLine::CLine()
	:m_pSelectedImage(nullptr)
	,m_bPainted(false)
	,m_posStart(Point::ZERO)
	,m_posEnd(Point::ZERO)
{
}

CLine::~CLine()
{

}

bool CLine::init(	Point posStart,
					Point posEnd,
					const std::string& normalImg,
					const std::string& SelectedImg,
					TextureResType texType	)
{
	m_pSelectedImage = ImageView::create(SelectedImg,texType);
	if(!m_pSelectedImage) return false;

	if (ImageView::init(normalImg,texType))
	{
		setScale9Enabled(true);
		setCapInsets(Rect(2,2,10,1));
		setAnchorPoint(Point(0,0.5f));
		setSize(Size(0,getVirtualRendererSize().height));
		SetPosStart(posStart);
		SetPosEnd(posEnd);

		m_pSelectedImage->setScale9Enabled(true);
		m_pSelectedImage->setCapInsets(Rect(2,2,10,1));
		m_pSelectedImage->setAnchorPoint(Point(0,0.5f));
		m_pSelectedImage->setSize(Size(0,m_pSelectedImage->getVirtualRendererSize().height));
		addChild(m_pSelectedImage);
		SetPainted(false);

		return true;
	} 
	else
	{
		return false;
	}
}

void CLine::OnPainted()
{
	if(IsPainted())
	{
		UpdatePropertySelected();
		m_pSelectedImage->setEnabled(true);
		m_pSelectedImage->setVisible(true);
	}
	else
	{
		m_pSelectedImage->setEnabled(false);
		m_pSelectedImage->setVisible(false);
	}
}

bool CLine::ContainPos(const Point pos1,const Point pos2)
{
	if(pos1 == pos2) return false;

	bool bContain = false;

	bContain = GetPosStart() == pos1;
	if(!bContain) bContain = GetPosStart() == pos2;
	if(!bContain) return false;

	bContain = GetPosEnd() == pos1;
	if(!bContain) bContain = GetPosEnd() == pos2;
	return bContain;
}

void CLine::UpdateProperty()
{
	setSize(Size(GetPosStart().getDistance(GetPosEnd()),getSize().height));
	setPosition(GetPosStart());
	Point posRadius = GetPosEnd() - GetPosStart();
	setRotation(-CC_RADIANS_TO_DEGREES(posRadius.getAngle()));
}

void CLine::UpdatePropertySelected()
{
	m_pSelectedImage->setSize(Size(GetPosStart().getDistance(GetPosEnd()),m_pSelectedImage->getSize().height));
	m_pSelectedImage->setPosition(Point(0,getSize().height/2));
}

CMagicLine* CMagicLine::create(Point posStart, Point posEnd, const std::string& normalImage, const std::string& selectedImage, TextureResType texType /* = UI_TEX_TYPE_LOCAL */)
{
	CMagicLine *pMagicLine = new CMagicLine;
	if (pMagicLine && pMagicLine->init(posStart,posEnd,normalImage,selectedImage,texType))
	{
		pMagicLine->autorelease();
		return pMagicLine;
	}
	CC_SAFE_DELETE(pMagicLine);
	return nullptr;
}

CMagicLine::CMagicLine()
	:m_bStartFixed(false)
{

}

void CMagicLine::RunBlinkAction()
{
	if (getActionManager()->getNumberOfRunningActionsInTarget(this)>0)
	{
		return;
	}
	std::function<void()> fun1 = [this]()
	{
		this->SetPainted(true);
	};
	std::function<void()> fun2 = [this]()
	{
		this->SetPainted(false);
	};
	std::function<void()> fun3 = [this]()
	{
		this->stopAllActions();
	};
	runAction(Sequence::create(CallFunc::create(fun1),DelayTime::create(0.5f),CallFunc::create(fun2),CallFunc::create(fun2),nullptr));
}
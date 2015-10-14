#include "OpenLock.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/MessageCenter.h"
#include "Net/NetDispatcher.h"
#include "GameScene/Chests.h"

#define Path_Res_PrizeKey		("assets/ui/SmallGame/img_gouzi.png")
#define Path_Res_LockKey		("assets/ui/SmallGame/img_gouzi.png")

COpenLock::COpenLock()
	:GameUI(IDU_OpenLock,JsonFile_OpenLockUI)
	,m_prizeKey(nullptr)
	,m_lockKey(nullptr)
	,m_openDegreeMin(0)
	,m_openDegreeMiddle(0)
	,m_openDegreeMax(0)
	,m_nItemBoxId(0)
	,m_pLock(nullptr)
	,m_pCountNum(nullptr)
	,m_pKeyNum(nullptr)
{

}

COpenLock::~COpenLock()
{

}

bool COpenLock::onInit()
{
	do 
	{
		Button* pBtnClose = (Button*)Helper::seekWidgetByName(m_pWidget,"CloseBtn");
		Button* pBtnReset = (Button*)Helper::seekWidgetByName(m_pWidget,"Reset");
		Button* pBtnKey = (Button*)Helper::seekWidgetByName(m_pWidget,"BtnKey");
		m_pKeyNum = (Text*)Helper::seekWidgetByName(m_pWidget,"KeyCount");
		m_pLock = (ImageView*)Helper::seekWidgetByName(m_pWidget,"Lock");
		BREAK_IF(!(pBtnClose&&pBtnReset&&pBtnKey&&m_pKeyNum&&m_pLock));
		pBtnClose->addTouchEventListener(this,toucheventselector(COpenLock::clickCloseBtn));
		pBtnReset->addTouchEventListener(this,toucheventselector(COpenLock::clickResetBtn));
		pBtnKey->addTouchEventListener(this,toucheventselector(COpenLock::clickKeyBtn));
		pBtnClose->addTouchEventListener(this,toucheventselector(COpenLock::clickCloseBtn));

		m_prizeKey = COpenLockKey::create(Path_Res_PrizeKey,Path_Res_PrizeKey,Path_Res_PrizeKey);
		m_lockKey = COpenLockKey::create(Path_Res_PrizeKey,Path_Res_PrizeKey,Path_Res_PrizeKey);
		BREAK_IF(!(m_prizeKey&&m_lockKey));

		m_prizeKey->setAnchorPoint(Point(1,0.5f));
		m_prizeKey->setScale9Enabled(true);
		m_prizeKey->setCapInsets(Rect(2,2,80,2));
		m_prizeKey->setSize(Size(400,30));
		m_prizeKey->setPosition(Point(617,375));
		m_prizeKey->SetRotateRange(-90.0f,90.0f);
		m_prizeKey->setTouchEnabled(true);
		m_prizeKey->AddRotateEvent(this,RoateEvent_CallBack(&COpenLock::RotateEventPrizeKey));
		m_prizeKey->addTouchEventListener(this,toucheventselector(COpenLock::clickLockKey));
		m_pWidget->addChild(m_prizeKey);

		m_lockKey->setAnchorPoint(Point(0,0.5f));
		m_lockKey->setScale9Enabled(true);
		m_lockKey->setCapInsets(Rect(2,2,80,2));
		m_lockKey->setSize(Size(400,30));
		m_lockKey->setPosition(Point(667,375));
		m_lockKey->SetRotateRange(0,90.0f);
		m_lockKey->setTouchEnabled(true);
		m_lockKey->setFlippedX(true);
		m_lockKey->AddRotateEvent(this,RoateEvent_CallBack(&COpenLock::RotateEventLockKey));
		m_lockKey->addTouchEventListener(this,toucheventselector(COpenLock::clickLockKey));
		m_pWidget->addChild(m_lockKey);

		m_pCountNum = Label::createWithBMFont("assets/common/font/timer.fnt",CCString::createWithFormat("60")->getCString());
		m_pCountNum->setPosition(Point(1170,150));
		m_pWidget->addChild(m_pCountNum);

		return true;
	} while (0);
	return false;
}

void COpenLock::onOpen()
{
	m_prizeKey->setRotation(0.0f);
	m_lockKey->setRotation(0.0f);
	m_lockKey->SetRotateable(true);
	m_pCountNum->setString("");
}

void COpenLock::onClose()
{
	unschedule(SEL_SCHEDULE(&COpenLock::ScheduleLeftTime));

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

void COpenLock::InitWithLockInfo(int nLockId)
{
	SetLockId(nLockId);
	ResetLockInfo();
}

void COpenLock::ResetLockInfo()
{
	Open_lockCfg* lockCfg = OpenLockData.get(GetLockId());
	if(!lockCfg) return;

	int randRange = abs(lockCfg->random_min)+lockCfg->random_max;
	srand (time(NULL));
	m_openDegreeMin = rand()%randRange + 1;
	if(m_openDegreeMin>lockCfg->random_max)
	{
		m_openDegreeMin = lockCfg->random_max - m_openDegreeMin;
	}
	m_openDegreeMax = m_openDegreeMin + lockCfg->section;
	m_openDegreeMiddle = (m_openDegreeMin+m_openDegreeMax)/2;

	SetMaxTime(lockCfg->max_time);
	SetLeftTime(lockCfg->max_time);
	unschedule(SEL_SCHEDULE(&COpenLock::ScheduleLeftTime));
	schedule(SEL_SCHEDULE(&COpenLock::ScheduleLeftTime),1.0f,GetMaxTime()+1,0.0f);
}

void COpenLock::ScheduleLeftTime(float dt)
{
	if (m_nLeftTime>=0)
	{
		m_pCountNum->setString(CCString::createWithFormat("%d",GetLeftTime())->getCString());
		SetLeftTime(GetLeftTime()-1);
	}
	else
	{
		unschedule(SEL_SCHEDULE(&COpenLock::ScheduleLeftTime));
		gGameUILayer->close(this);
	}
}

void COpenLock::setLockKeyRotate(COpenLockKey* pLockKey, const Point touchPoint)
{
	if(!pLockKey || !pLockKey->CanRotate()) return;

	Point radiansPoint = touchPoint - pLockKey->getPosition();
	if(pLockKey == m_prizeKey)
	{
		if(radiansPoint.x>0)
		{
			pLockKey->setRotation(pLockKey->GetBoundaryRotation(pLockKey->getRotation()));
			return;
		}
		radiansPoint.x = abs(radiansPoint.x);
		radiansPoint.y = -radiansPoint.y;
	}
	float fRotation = -CC_RADIANS_TO_DEGREES(radiansPoint.getAngle());
	float fRotationRangeMin = 0.0f;
	float fRotationRangeMax = 0.0f;
	pLockKey->GetRotateRange(fRotationRangeMin,fRotationRangeMax);
	float fRotationValid = clampf(fRotation,fRotationRangeMin,fRotationRangeMax);
	pLockKey->setRotation(fRotationValid);
}

void COpenLock::RotateEventPrizeKey()
{
	if (m_prizeKey->getRotation()>=m_openDegreeMin && m_prizeKey->getRotation()<=m_openDegreeMax)
	{
		m_lockKey->SetRotateRangeMax(90.0f);
	} 
	else
	{
		float degreeInterval = abs(m_prizeKey->getRotation()-m_openDegreeMiddle);
		degreeInterval = degreeInterval>90.0f?90.0f:degreeInterval;
		float rotateDegreeMax = 90.0f-degreeInterval;
		m_lockKey->SetRotateRangeMax(clampf(rotateDegreeMax,0.0f,90.0f));
	}
}

void COpenLock::RotateEventLockKey()
{
	m_pLock->setRotation(m_lockKey->getRotation());

	if (m_lockKey->getRotation() == 90.0f)
	{
		m_lockKey->SetRotateable(false);

		MessagePrompt("success");
		gGameUILayer->close(this);

		pk::C2GS_OPEN_TREAS_Succ_Req cmd;
		cmd.id = GetItemBoxId();
		cmd.Send(gNetSocket);
	}
}

void COpenLock::clickCloseBtn(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
	}
}

void COpenLock::clickResetBtn(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		ResetLockInfo();		
	}
}

void COpenLock::clickKeyBtn(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		
	}
}

void COpenLock::clickLockKey(Ref* pSender,TouchEventType type)
{
	COpenLockKey* lockKey = (COpenLockKey*)pSender;
	switch (type)
	{
	case TOUCH_EVENT_BEGAN:
			setLockKeyRotate(lockKey,lockKey->getTouchStartPos());
		break;
	case TOUCH_EVENT_MOVED:
			setLockKeyRotate(lockKey,lockKey->getTouchMovePos());
		break;
	case TOUCH_EVENT_ENDED:
		{
			setLockKeyRotate(lockKey,lockKey->getTouchEndPos());
			if(lockKey == m_lockKey && m_lockKey->CanRotate())
			{
				m_lockKey->runAction(EaseExponentialOut::create(RotateTo::create(0.5f,m_lockKey->GetRotateRangeMin())));
				m_pLock->runAction(EaseExponentialOut::create(RotateTo::create(0.5f,m_lockKey->GetRotateRangeMin())));
			}
		}
		break;
	case TOUCH_EVENT_CANCELED:
		{
			if(lockKey == m_lockKey && m_lockKey->CanRotate())
			{
				m_lockKey->runAction(EaseExponentialOut::create(RotateTo::create(0.5f,m_lockKey->GetRotateRangeMin())));
				m_pLock->runAction(EaseExponentialOut::create(RotateTo::create(0.5f,m_lockKey->GetRotateRangeMin())));
			}
		}
		break;
	default:
		break;
	}
}

COpenLockKey* COpenLockKey::create(const std::string& normalImage, const std::string& selectedImage /* = "" */, const std::string& disableImage /* = "" */, TextureResType texType /* = UI_TEX_TYPE_LOCAL */)
{
	COpenLockKey* openLockKey = new COpenLockKey;
	if (openLockKey&&openLockKey->init(normalImage,selectedImage,disableImage,texType))
	{
		openLockKey->autorelease();
		return openLockKey;
	}
	CC_SAFE_DELETE(openLockKey);
	return nullptr;
}

COpenLockKey::COpenLockKey()
{
	m_bRotateable = true;
	m_fRotateRangeMin = 0.0f;
	m_fRotateRangeMax = 0.0f;
	m_rotateEventListener = nullptr;
	m_rotateEventCallBack = nullptr;
}

COpenLockKey::~COpenLockKey()
{

}

void COpenLockKey::setRotation(float rotation)
{
	Node::setRotation(rotation);
	RotateEvent();
}

float COpenLockKey::GetBoundaryRotation(float fRotation)
{
	float fRangeMidRotation = (GetRotateRangeMax()+GetRotateRangeMin())/2;
	if(fRotation>fRangeMidRotation)
	{
		return GetRotateRangeMax();
	}
	else
	{
		return GetRotateRangeMin();
	}
}

void COpenLockKey::AddRotateEvent(Ref* pListener, RoateEvent_CallBack callback)
{
	m_rotateEventListener = pListener;
	m_rotateEventCallBack = callback;
}

void COpenLockKey::RotateEvent()
{
	if (m_rotateEventListener&&m_rotateEventCallBack)
	{
		(m_rotateEventListener->*m_rotateEventCallBack)();
	}
}
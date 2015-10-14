#include "DramaUi.h"
#include "GameScene/Hero.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/GameManager.h"
#include "MainUINormal.h"
#include "cfgTable.h"

enum Player_TYPE
{
	NPC_TYPE = 0,
	HERO_TYPE,
};

enum Direct_TYPE
{
	LEFT_TYPE = 0,
	RIGHT_TYPE,
};

DramaUI::DramaUI():GameUI(IDU_Drama, JSONFILE_DRAMAUI)
	,m_pShowTextNpc(nullptr)
	,m_pShowTextHero(nullptr)
	,m_heroIcon(nullptr)
	,m_npcIcon(nullptr)
	,m_curShowMode(false)
	,m_pNpcName(nullptr)
	,m_pHeroName(nullptr)
{
	m_touchCnt = 0;
	for (int i= 0; i < MAX_STRING; i++)
	{
		m_dump[i].clear();
	}
	m_isSkip = false;
	m_curIndex = 0;
	m_subIndex = 0;
	m_stcLen = 0;
}

DramaUI::~DramaUI()
{
	for (int i= 0; i < MAX_STRING; i++)
	{
		for (auto iter :m_dump[i])
		{
			if(iter)
			{
				delete iter;
				iter = nullptr;
			}
		}
		m_dump[i].clear();
	}
}

bool DramaUI::onInit()
{
	if(!GameUI::onInit())
		return false;

	// 屏幕适配
	Size vSize = gDirector->getVisibleSize();
	Size wSize = UI_ORIG_SIZE;
	float fScale = MIN(vSize.width / wSize.width, vSize.height / wSize.height);
	this->setScale(fScale);

	Point pos(0,0);
	pos += gDirector->getVisibleOrigin();
	this->setPosition(pos);
	return true;
}

void DramaUI::initModel()
{
	Widget* pPanel = Helper::seekWidgetByName(m_pWidget, "Panel_model");
	pPanel->setTouchEnabled(true);
	pPanel->setEnabled(true);
	Widget* punPanel = Helper::seekWidgetByName(m_pWidget, "Panel_unmodel");
	punPanel->setVisible(false);
	auto btn = dynamic_cast<Button*>(Helper::seekWidgetByName(pPanel, "Button_pass"));
	if(btn)
	{
		btn->setButtonSpriteGray();
		btn->addTouchEventListener(this, toucheventselector(DramaUI::passevent));
	}

	pPanel->addTouchEventListener(this, toucheventselector(DramaUI::touchevent));

	m_npcIcon   = dynamic_cast<ImageView*>(Helper::seekWidgetByName(pPanel, "Image_npc"));
	m_heroIcon  = dynamic_cast<ImageView*>(Helper::seekWidgetByName(pPanel, "Image_hero"));

	m_pShowTextNpc = dynamic_cast<Text*>(Helper::seekWidgetByName(pPanel,"Label_npc"));
	if(m_pShowTextNpc)
		m_pShowTextNpc->enableOutline(Color4B::BLACK, 2);
	m_pShowTextHero = dynamic_cast<Text*>(Helper::seekWidgetByName(pPanel, "Label_hero"));
	if(m_pShowTextHero)
		m_pShowTextHero->enableOutline(Color4B::BLACK, 2);

	m_pNpcName = dynamic_cast<Text*>(Helper::seekWidgetByName(pPanel, "Label_Nname"));
	m_pHeroName = dynamic_cast<Text*>(Helper::seekWidgetByName(pPanel, "Label_Hname"));
}

void DramaUI::initUnmodel()
{
	Widget* pPanel1 = Helper::seekWidgetByName(m_pWidget, "Panel_model");
	pPanel1->setTouchEnabled(false);
	pPanel1->setEnabled(false);
	Widget* pPanel = Helper::seekWidgetByName(m_pWidget, "Panel_unmodel");
	pPanel->setVisible(true);
	m_npcIcon   = dynamic_cast<ImageView*>(Helper::seekWidgetByName(pPanel, "Image_npc"));
	m_heroIcon  = dynamic_cast<ImageView*>(Helper::seekWidgetByName(pPanel, "Image_hero"));

	m_pShowTextNpc = dynamic_cast<Text*>(Helper::seekWidgetByName(pPanel,"Label_npc"));
	if(m_pShowTextNpc)
		m_pShowTextNpc->enableOutline(Color4B::BLACK, 2);
	m_pShowTextHero = dynamic_cast<Text*>(Helper::seekWidgetByName(pPanel, "Label_hero"));
	if(m_pShowTextHero)
		m_pShowTextHero->enableOutline(Color4B::BLACK, 2);

	m_pNpcName = dynamic_cast<Text*>(Helper::seekWidgetByName(pPanel, "Label_Nname"));
	m_pHeroName = dynamic_cast<Text*>(Helper::seekWidgetByName(pPanel, "Label_Hname"));
}

void DramaUI::onOpen()
{
	m_curShowMode = false;
	m_isSkip = false;
	m_curIndex = 0;
	m_subIndex = 0;
	m_stcLen = 0;
}

void DramaUI::onShow()
{

}

void DramaUI::onClose()
{
	for (int i= 0; i < MAX_STRING; i++)
	{
		for (auto iter :m_dump[i])
		{
			if(iter)
			{
				delete iter;
				iter = nullptr;
			}
		}
		m_dump[i].clear();
	}
}

void DramaUI::onDestroy()
{

}

void DramaUI::showDramaByParam(int _startid, int _npcid)
{
	m_dataID = _startid;
	subStringToVector();
	if(m_curShowMode)
	{
		this->unDoModel();
		initUnmodel();
		MainUI::ShowMainUI(gMap->getFuncType());
	}
	else
	{
		initModel();
		MainUI::CloseMainUI();
	}
	showByInterval();
}

void DramaUI::showDrama()
{
	gGameUILayer->open(this);
	showDramaByParam(GetStartId(),0);
}

void DramaUI::touchevent(Ref *pSender, TouchEventType _type)
{
	if(_type == TOUCH_EVENT_ENDED)
	{
		auto endPos = dynamic_cast<Widget*>(pSender)->getTouchEndPos();
		CCLOG("touch point = (%f, %f)", endPos.x, endPos.y );
		m_touchCnt += 1;
		if(m_touchCnt == 2)
		{
			m_touchCnt = 0;
			nextTalk(0);
		}
		else if(m_touchCnt == 1)
		{
			this->stopAllActions();
			m_isSkip = true;
			showByInstant();
			nextTalk();
			m_subIndex = 0;
		}
		else
		{
			m_touchCnt = 0;
		}
		CCLOG("m_touchCnt = %d", m_touchCnt);
	}
}

void DramaUI::passevent(Ref *pSender, TouchEventType _type)
{
	if(_type == TOUCH_EVENT_ENDED)
	{
		gGameUILayer->close(IDU_Drama);
		if(!m_curShowMode)
		MainUI::ShowMainUI(gMap->getFuncType());
	}
}

string DramaUI::getCurShowContext()
{
	m_showStr = "";
	m_stcLen = 0;
	if(m_dump[m_curIndex].size() == 0 || m_dump[m_curIndex][0]->talkstr.size() == 0) return m_showStr;
	vector<string>::iterator iter = m_dump[m_curIndex][0]->talkstr.begin();
	if(iter != m_dump[m_curIndex][0]->talkstr.end())
	{
		switch (m_dump[m_curIndex][0]->direct)
		{
		case LEFT_TYPE:
			m_npcIcon->setVisible(true);
			m_heroIcon->setVisible(false);
			m_pShowTextNpc->setVisible(true);
			m_pShowTextHero->setVisible(false);
			m_pHeroName->setVisible(false);
			m_pNpcName->setVisible(true);
			break;
		case RIGHT_TYPE:
			m_npcIcon->setVisible(false);
			m_heroIcon->setVisible(true);
			m_pShowTextNpc->setVisible(false);
			m_pShowTextHero->setVisible(true);
			m_pHeroName->setVisible(true);
			m_pNpcName->setVisible(false);
			break;
		default:
			break;
		}
		m_stcLen = m_dump[m_curIndex][0]->talkstr.size();
		for(auto iter_S : m_dump[m_curIndex][0]->talkstr)
			m_showStr += iter_S;
		return m_showStr;
	}
	if(m_dump[m_curIndex][0]->roleid != 0)
	{
		string Icon = "";
		string NameStr = "";
		MapObject* pObj = gMap->getObjectManager()->getObject(m_dump[m_curIndex][0]->roleid);
		if(pObj)
		{
			if ( pObj->GetType() == mapObjectType_Monster )
			{
				MonsterBaseCfg* data = gGameData->MonsterBaseTable.get(m_dump[m_curIndex][0]->roleid);
				if(data)
				{
					Icon = data->head;
					NameStr = data->name;
				}
				
			}
			else if(pObj->GetType() == mapObjectType_Npc)
			{
				NpcCfg* data = gGameData->NpcCfgTable.get(m_dump[m_curIndex][0]->roleid);
				if(data)
				{
					Icon = data->npchead;
					NameStr = data->name;
				}
				
			}
		}
		if(m_npcIcon && m_npcIcon->isVisible())
		{
			m_npcIcon->loadTexture(Icon);
			m_pNpcName->setText(NameStr);
		}
		else if(m_heroIcon  && m_heroIcon->isVisible())
		{
			m_heroIcon->loadTexture(Icon);
			m_pHeroName->setText(NameStr);
		}
	}
	else
	{
		m_heroIcon->loadTexture(gHero->getHeadIcon());
		m_pHeroName->setText(gHero->GetRoleName());
	}


	return m_showStr;
}

string  DramaUI::getSubShowString(int _index)
{
	string    reStr =  "";
    if (m_dump[m_curIndex].size() == 0 || m_dump[m_curIndex][0]->talkstr.size() == 0 || _index > (int)m_dump[m_curIndex][0]->talkstr.size() )
    {
        return reStr;
    }

	for(int i = 0; i < _index; i ++)
	{
		reStr += m_dump[m_curIndex][0]->talkstr.at(i);
	}

	if ( m_curShowMode )
	{
		reStr = StringUtil::StringCut(reStr,MAX_WORDS_1,"...");
	}
	else
	{
		reStr = StringUtil::StringCut(reStr,MAX_WORDS_0,"...");
	}

	return reStr;
}

void DramaUI::showByInstant()
{
	string str = getCurShowContext();
	m_pShowTextHero->setText(str);
	m_pShowTextNpc->setText(str);
}


void DramaUI::showByInterval()
{
	m_isSkip = false;
	m_subIndex = 0;
	m_stcLen = 0;
	getCurShowContext();
	m_pShowTextHero->setText("");
	m_pShowTextNpc->setText("");
	this->schedule(schedule_selector(DramaUI::updateShow), UPDATETIME);
}


void DramaUI::showCenterTips()
{

}

vector<DramaCfg*> DramaUI::subDataByMainType(int main)
{
	vector<DramaCfg*> subData;
	const CCfgTable<DramaCfg>::ConfigTable& data =  DramaTableData.getData();
	for (auto iter : data)
	{
		if(iter->main == main)
		{
			subData.push_back(iter);
		}
	}
	return subData;
}

void DramaUI::subStringToVector()
{
	vector<DramaCfg*> pSubData = subDataByMainType(m_dataID);
	if((int)pSubData.size() == 0) return;
	m_curShowMode = false;
	int idx = 0;
	for (auto pData : pSubData)
	{
		if(pData)
		{
			string str = pData->chatstr;
			int length = (int)str.length();
			const char* p_str = str.c_str();
			int i = 0;
			vector<string> talkstr;
			talkstr.clear();
			while (i<length)
			{
				unsigned char c = p_str[i];
				if(c >127){                      //中文
					talkstr.push_back(str.substr(i,3));
					i=i+3;
				}
				else{                                                //英文
					talkstr.push_back(str.substr(i,1));
					i=i+1;
				}
			}
			TalkLine_st * st = new TalkLine_st();
			st->person = pData->person_type;
			st->roleid = pData->npc_id;
			st->talkstr = talkstr;
			m_dump[idx].push_back(st);
			//判断结束条件
			if(pData->mode == 1)  //小框显示
				m_curShowMode = true;
			idx += 1;
			talkstr.clear();
		}
	}
}


void DramaUI::nextTalk(int _delay /* = DELAYTIME*/)
{
	this->unschedule(schedule_selector(DramaUI::updateShow));
	this->stopAllActions();
	this->runAction(Sequence::create(DelayTime::create(_delay),CallFunc::create(
		[=](){
			m_curIndex += 1;
			showByInterval();
	}), nullptr));
}


void DramaUI::updateShow(float fd)
{
	if(m_isSkip)
	{
		this->unschedule(schedule_selector(DramaUI::updateShow));
		return;
	}
	if(m_showStr.size() == 0 && m_stcLen == 0)
	{
		gGameUILayer->close(IDU_Drama);
		MainUI::ShowMainUI(gMap->getFuncType());
	};
	if(m_subIndex <= m_stcLen)
	{
		m_pShowTextNpc->setText(getSubShowString(m_subIndex));
		m_pShowTextHero->setText(getSubShowString(m_subIndex));
		m_subIndex += 1;
	}
	else if(m_subIndex > 0)
	{
		this->unschedule(schedule_selector(DramaUI::updateShow));
		m_subIndex = 0;
		nextTalk();
	}
}
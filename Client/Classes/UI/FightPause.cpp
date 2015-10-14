#include "FightPause.h"
#include "GameScene/GameUILayer.h"
#include "Net/pk_map.h"
#include "Net/NetDispatcher.h"


CFightPause::CFightPause() : GameUI(IDU_FightPause,JsonFile_FightPause)
{

}

CFightPause::~CFightPause()
{

}

bool CFightPause::onInit()
{
	do 
	{
		Button* BtnBack = (Button*)Helper::seekWidgetByName(m_pWidget,"Back");
		Button* BtnLeave = (Button*)Helper::seekWidgetByName(m_pWidget,"Leave");
		CheckBox* MusicSet = (CheckBox*)Helper::seekWidgetByName(m_pWidget,"MusicSet");
		CheckBox* EffectSet = (CheckBox*)Helper::seekWidgetByName(m_pWidget,"EffectSet");
		BREAK_IF( !(BtnBack&&BtnLeave&&MusicSet&&EffectSet) );
		BtnBack->addTouchEventListener(this,toucheventselector(CFightPause::ClickBack));
		BtnLeave->addTouchEventListener(this,toucheventselector(CFightPause::ClickLeave));
		MusicSet->addEventListenerCheckBox(this,checkboxselectedeventselector(CFightPause::ClickMusic));
		EffectSet->addEventListenerCheckBox(this,checkboxselectedeventselector(CFightPause::ClickEffect));
		MusicSet->setSelectedState(true);
		EffectSet->setSelectedState(true);
		return true;
	} while (0);
	
	return false;
}

void CFightPause::ClickBack(Ref *pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
	}
}

void CFightPause::ClickLeave(Ref *pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
		gHero->LeaveCopy();
	}
}

void CFightPause::ClickMusic(Ref* pSender,CheckBoxEventType type)
{
	gCocosAudio->SetMusicEnable(CHECKBOX_STATE_EVENT_SELECTED == type);
}

void CFightPause::ClickEffect(Ref* pSender,CheckBoxEventType type)
{
	gCocosAudio->SetEffectEnable(CHECKBOX_STATE_EVENT_SELECTED == type);
}

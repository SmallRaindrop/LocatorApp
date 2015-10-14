#include "RoleSelectUI.h"
#include "GameScene/GameManager.h"

RoleSelectUI::RoleSelectUI() : GameUI(IDU_NONE,"")
{

}

RoleSelectUI::~RoleSelectUI()
{

}

bool RoleSelectUI::onInit()
{
	return true;
}


void RoleSelectUI::onEnterGameBtnClicked(Ref *pSender, TouchEventType type)
{
	switch (type)
	{
	case TOUCH_EVENT_BEGAN: break;
	case TOUCH_EVENT_MOVED: break;
	case TOUCH_EVENT_ENDED: gGameManager->EnterGame(); break;
	case TOUCH_EVENT_CANCELED: break;
	default: break;
	}
}
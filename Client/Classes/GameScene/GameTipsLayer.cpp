#include "GameTipsLayer.h"
#include "UI/GamePrompt.h"

CGameTipsLayer::CGameTipsLayer()
{
	initialize();
}

CGameTipsLayer::~CGameTipsLayer()
{
	removeFromParent();
}

// on "init" you need to initialize your instance
bool CGameTipsLayer::initialize()
{
	addChild(gPromptCenter->GetWidgetPrompt());
	addChild(gPromptCenter->GetWidgetNotice1());
	addChild(gPromptCenter->GetWidgetNotice2());

	return true;
}
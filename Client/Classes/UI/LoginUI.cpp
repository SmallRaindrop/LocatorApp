#include "LoginUI.h"
#include "GameScene/GameManager.h"
#include "VersionManager.h"
#include "Net/NetDispatcher.h"
#include "Net/pk_betweenClientLs.h"
#include "GameDef.h"
#include "GameScene/LoginScene.h"

LoginUI::LoginUI() : GameUI(IDU_LOGIN,JSONFILE_LOGIN),m_acount("")
{

}

LoginUI::~LoginUI()
{

}

bool LoginUI::onInit()
{
	ui::Button* pBtnLogin = dynamic_cast<ui::Button*>(Helper::seekWidgetByName(m_pWidget,"Button_login"));
	if (pBtnLogin)
	{
		pBtnLogin->addTouchEventListener(this,toucheventselector(LoginUI::onLoginBtnClicked));
	}

	loadUserCfg();

	return true;
}

void LoginUI::onOpen()
{
}

void LoginUI::login()
{
	ui::TextField* pAccount = dynamic_cast<ui::TextField*>(Helper::seekWidgetByName(m_pWidget,"TextField_name"));
	//ui::TextField* pPwd = dynamic_cast<ui::TextField*>(m_pWidget->getChildByName("input_loginPwd"));
	if (pAccount)
	{
		if ( gNetDispatcher->Connect(gGameVersion->lvd().ip,gGameVersion->lvd().port) )
		{
			gGameManager->SetAccount(pAccount->getStringValue());
			//save user cfg
			saveUserCfg();
			gNetDispatcher->SetLine(NetLine_Login);
			pk::C2LS_Login_Test cmd;
			cmd.account = pAccount->getStringValue();
			cmd.platformID = gGameVersion->lvd().pid;
			cmd.Send(gNetSocket);
			//pk::C2LS_RequestGameServerList cmd;
			//cmd.Send(gNetSocket);
		}
	}
	else
	{
		CCLOGERROR("%s","can not get Acount and pwd widget!");
	}
}

void LoginUI::onLoginBtnClicked(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		login();
	}
}

void LoginUI::loadUserCfg(void)
{
	std::string defaultAccount = "";
	m_acount = cocos2d::UserDefault::getInstance()->getStringForKey("account",defaultAccount);
	if (!m_acount.empty())
	{
		ui::TextField* pAccount = dynamic_cast<ui::TextField*>(Helper::seekWidgetByName(m_pWidget,"TextField_name"));
		if (pAccount)
		{
			pAccount->setText(m_acount);
		}
	}
}

void LoginUI::saveUserCfg(void)
{
	ui::TextField* pAccount = dynamic_cast<ui::TextField*>(Helper::seekWidgetByName(m_pWidget,"TextField_name"));
	if (pAccount)
	{
		cocos2d::UserDefault::getInstance()->setStringForKey("account",pAccount->getStringValue());
	}
}
#include "LoginScene.h"
#include "UIButton.h"
#include "GameManager.h"
#include "Net/NetDispatcher.h"
#include "GameDataManager.h"
#include "VersionManager.h"
#include "UI/ServerList.h"
#include "UI/CreatePlayer.h"
#include "UI/SelectPlayer.h"
#include "UI/LoginUI.h"
#include "UI/ResMgr/CtrlAllocator.h"
#include "../Common/CommonDef.h"
#include "UI/GamePrompt.h"
#include "GameUILayer.h"


LoginLayer::LoginLayer() : m_curShowType(login_ui_login)
{
	for (int i=0; i<login_ui_count; ++i)
	{
		m_pLoginUIs[i]=NULL;
	}
}

LoginLayer::~LoginLayer()
{
	for (int i=0; i<login_ui_count; ++i)
	{
		CC_SAFE_RELEASE_NULL(m_pLoginUIs[i]);
	}
}

bool LoginLayer::init()
{
	/*m_pBk0 = Sprite::create("assets/ui/login/login_bg1.jpg");
	m_pBk1 = Sprite::create("assets/ui/login/login_bg2.jpg");
	m_pBk2 = Sprite::create("assets/ui/login/login_bg3.jpg");
	m_pBk3 = Sprite::create("assets/ui/login/login_bg4.jpg");

	if ( m_pBk0 )
	{
	m_pBk0->setPosition(m_fStartPos,0);
	m_pBk0->setAnchorPoint(Point(0,0));
	m_pBk0->setFlippedX(true);
	addChild(m_pBk0);
	}
	if ( m_pBk1 )
	{
	m_pBk1->setPosition(m_fStartPos-BG_UNIT_WIDTH,0);
	m_pBk1->setAnchorPoint(Point(0,0));
	m_pBk1->setFlippedX(true);
	addChild(m_pBk1);
	}
	if ( m_pBk2 )
	{
	m_pBk2->setPosition(m_fStartPos-BG_UNIT_WIDTH*2,0);
	m_pBk2->setAnchorPoint(Point(0,0));
	m_pBk2->setFlippedX(true);
	addChild(m_pBk2);
	}
	if ( m_pBk3 )
	{
	m_pBk3->setPosition(m_fStartPos-BG_UNIT_WIDTH*3,0);
	m_pBk3->setAnchorPoint(Point(0,0));
	m_pBk3->setFlippedX(true);
	addChild(m_pBk3);
	}*/

	// ÆÁÄ»ÊÊÅä
	//Size vSize = gDirector->getVisibleSize();
	//Size wSize(LoginLayer::BG_WIDTH,LoginLayer::BG_HEIGHT);
	//float fScale1 = MIN(vSize.width / wSize.width, vSize.height / wSize.height);
	//float fScale2 = MAX(vSize.width / wSize.width, vSize.height / wSize.height);

	Point pos(0,0);
	pos += gDirector->getVisibleOrigin();

	m_pLoginUIs[login_ui_login] = LoginUI::create();
	m_pLoginUIs[login_ui_serverlist] = CServerList::create();
	m_pLoginUIs[login_ui_createplayer] = CCreatePlayer::create();
	m_pLoginUIs[login_ui_selectplayer] = CSelectPlayer::create();
	for (int i=0; i<login_ui_count; ++i)
	{
		if (!m_pLoginUIs[i])
		{
			return false;
		}
		CC_SAFE_RETAIN(m_pLoginUIs[i]);
		m_pLoginUIs[i]->setPosition(pos);
		//m_pLoginUIs[i]->setScale(fScale1/fScale2);
	}

	scheduleUpdate();

	if (gPromptCenter->GetWidgetPrompt()->getParent())
	{
		gPromptCenter->GetWidgetPrompt()->removeFromParentAndCleanup(true);
	}

	addChild(gPromptCenter->GetWidgetPrompt(),1000);

	OpenUI(login_ui_login);
	return true;
}

GameUI* LoginLayer::OpenUI(LoginUIType type)
{
	m_curShowType = type;
	for (int i=0; i<login_ui_count; ++i)
	{
		if(m_pLoginUIs[i]->getParent())
		{
			m_pLoginUIs[i]->onClose();
			m_pLoginUIs[i]->removeFromParentAndCleanup(true);
		}
	}
	addChild(m_pLoginUIs[m_curShowType]);
	m_pLoginUIs[m_curShowType]->onOpen();
	return m_pLoginUIs[m_curShowType];
}

void LoginLayer::update(float dt)
{
	m_pLoginUIs[m_curShowType]->update(dt);
	gPromptCenter->update(dt);
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
LoginLayer*	CLoginScene::gLoginLayer;

CLoginScene::CLoginScene()
{
	gLoginLayer=NULL;
}

CLoginScene::~CLoginScene()
{
	gLoginLayer=NULL;
}

bool CLoginScene::init()
{
	gLoginLayer = LoginLayer::create();
	if ( !gLoginLayer )
	{
		return false;
	}

	// ÆÁÄ»ÊÊÅä
	Size vSize = gDirector->getVisibleSize();
	Size wSize =  Size(1334, 750);   //GAME_UI_ORIG_SIZE;
	float fScale = MIN(vSize.width / wSize.width, vSize.height / wSize.height);
	gLoginLayer->setScale(fScale);

	Point pos = gDirector->getVisibleOrigin();
		
	gLoginLayer->setPosition(pos);
	addChild(gLoginLayer);

	// °æ±¾ºÅÏÔÊ¾
	LayerColor* pLayerWhite = LayerColor::create(Color4B::WHITE);
	LayerColor* pLayerBlack = LayerColor::create(Color4B::BLACK);
	addChild(pLayerWhite,1);
	addChild(pLayerBlack,2);
	Text* pLVersionText = Text::create("VER:"+gGameVersion->lvd().ver.to_str()+"/"+gGameVersion->rvd().ver.to_str(),"Helvetica",18);
	if ( pLVersionText )
	{
		pLVersionText->setPosition(Point(5,0));
		pLVersionText->setColor(Color3B::GREEN);
		pLVersionText->setAnchorPoint(Point::ZERO);
		
		pos += Point(vSize.width - pLVersionText->getSize().width -10 ,0);
		pLayerWhite->setPosition(pos+Point(-1,-1));
		pLayerBlack->setPosition(pos);

		pLayerBlack->addChild(pLVersionText);
		pLayerBlack->setContentSize(pLVersionText->getSize()+Size(10,0));
		pLayerWhite->setContentSize(pLayerBlack->getContentSize()+Size(2,2));
	}

	return true;
}

void CLoginScene::update(float delta)
{
	gNetDispatcher->update(delta);
}

void CLoginScene::onEnter()
{
	Scene::onEnter();

	addChild(gGameUILayer);
	
	// ÆÁÄ»ÊÊÅä
	Size vSize = gDirector->getVisibleSize();
	Size wSize = UI_ORIG_SIZE;
	float fScale = MIN(vSize.width / wSize.width, vSize.height / wSize.height);
	gGameUILayer->setScale(fScale);

	Point pos(0,0);
	pos += gDirector->getVisibleOrigin();
	gGameUILayer->setPosition(pos);

	gGameUILayer->scheduleUpdate();
	scheduleUpdate();
}

void CLoginScene::onExit()
{
	unscheduleUpdate();

	gGameUILayer->unscheduleUpdate();
	gGameUILayer->removeFromParent();

	Scene::onExit();
}
#include "GameUpdateUI.h"
#include "GameScene/RootScene.h"
#include "GameUpdate.h"

USING_NS_CC;
//////////////////////////////////////////////////////////////////////////

GameUpdateUI::GameUpdateUI() : m_pProgressBar(nullptr),m_pLabelTips(nullptr)
{

}

GameUpdateUI::~GameUpdateUI()
{

}

bool GameUpdateUI::init()
{
	// 屏幕适配
	Size vSize = gDirector->getVisibleSize();
	Point pos = Point(vSize.width/2,vSize.height/2);
	pos += gDirector->getVisibleOrigin();

	// 背景
	Sprite* pBg = Sprite::create("update/bg.jpg");
	if ( pBg )
	{
		pBg->setPosition(pos);
		addChild(pBg);
	}

	// Logo
	Sprite* pLogo = Sprite::create("update/logo.jpg");
	if ( pLogo )
	{
		pLogo->setPosition(pos+Point(0,100));
		addChild(pLogo);
	}

	// 进度条
	m_pProgressBar = ProgerssBar::create();
	if ( m_pProgressBar )
	{
		m_pProgressBar->SetMoveSpeed(4.0f);
		m_pProgressBar->setTexture("update/progressBar0.png","update/progressBar.png");
		m_pProgressBar->setPosition(pos+Point(0,-150)-Point(m_pProgressBar->GetSize()/2));
		addChild(m_pProgressBar);
	}

	// 提示文字
	m_pLabelTips = Label::createWithSystemFont("","Arial",32);
	if ( m_pLabelTips )
	{
		m_pLabelTips->setPosition(pos+Point(0,-200));
		addChild(m_pLabelTips);
	}

	scheduleUpdate();
	return true;
}

void GameUpdateUI::update(float dt)
{
	if ( m_pProgressBar )
	{
		m_pProgressBar->update(dt);
	}
}




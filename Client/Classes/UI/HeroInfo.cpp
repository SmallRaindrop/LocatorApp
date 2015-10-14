#include "HeroInfo.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/Hero.h"


CHeroInfo::CHeroInfo() : GameUI(IDU_HeroInfo,JsonFile_HeroInfo)
{

}

CHeroInfo::~CHeroInfo()
{
	m_TxtVip = NULL;
	m_TxtLv = NULL;
	m_TxtGold = NULL;
	m_TxtMoney = NULL;
	m_TxtPower = NULL;
	m_TxtPowerTimes = NULL;
	m_pExpFrame = NULL;
	m_pExpValue = NULL;
	m_pExpBar = NULL;
}

bool CHeroInfo::onInit()
{
	do 
	{
		Button* BtnClose = (Button*)Helper::seekWidgetByName(m_pWidget,"Close");
		ImageView* CareerIcon = (ImageView*)Helper::seekWidgetByName(m_pWidget,"CareerIcon");
		Text* Name = (Text*)Helper::seekWidgetByName(m_pWidget,"Name");
		m_TxtVip = (Text*)Helper::seekWidgetByName(m_pWidget,"Vip");
		m_TxtLv = (Text*)Helper::seekWidgetByName(m_pWidget,"Lv");
		m_TxtGold = (Text*)Helper::seekWidgetByName(m_pWidget,"Gold");
		m_TxtMoney = (Text*)Helper::seekWidgetByName(m_pWidget,"Money");
		m_TxtPower = (Text*)Helper::seekWidgetByName(m_pWidget,"Power");
		m_TxtPowerTimes = (Text*)Helper::seekWidgetByName(m_pWidget,"PowerTimes");
		m_pExpFrame = (Layout*)Helper::seekWidgetByName(m_pWidget,"ExpBarFrame");
		m_pExpValue = (Text*)Helper::seekWidgetByName(m_pWidget,"ExpValue");
		m_pExpBar = Helper::seekWidgetByName(m_pWidget,"ExpBar");

		BREAK_IF( !(BtnClose&&CareerIcon&&m_TxtVip&&m_TxtLv&&m_TxtGold&&m_TxtMoney&&m_TxtPower&&m_TxtPowerTimes&&m_pExpFrame&&m_pExpValue&&m_pExpBar) );
		BtnClose->addTouchEventListener(this,toucheventselector(CHeroInfo::ClickClose));
		m_pExpFrame->setClippingEnabled(true);
		CareerIcon->loadTexture(gHero->getHeadIcon());
		Name->setText(gHero->GetRoleName());
		return true;
	} while (0);
	
	return false;
}

void CHeroInfo::onOpen()
{
	m_TxtVip->setText(CCString::createWithFormat("vip%d",gHero->GetVipLevel())->getCString());
	m_TxtLv->setText(CCString::createWithFormat("%d",gHero->GetLevel())->getCString());
	m_TxtGold->setText(CCString::createWithFormat("%d",gHero->GetGold())->getCString());
	m_TxtMoney->setText(CCString::createWithFormat("%d",gHero->GetMoney())->getCString());
	m_TxtPower->setText(CCString::createWithFormat("100/100")->getCString());
	m_TxtPowerTimes->setText(CCString::createWithFormat("10/10")->getCString());


	int nExpUp = 0;
	int nExp = gHero->GetExp();

	PlayerExpCfg* pData = PlayerExpData.get(gHero->GetLevel());
	if ( pData )
	{
		nExpUp = pData->exp;
	}
	if(nExpUp == 0) return;

	m_pExpValue->setText(CCString::createWithFormat("%d/%d",nExp,nExpUp)->getCString());
	m_pExpFrame->setSize(Size(m_pExpBar->getContentSize().width*((float)nExp/nExpUp),m_pExpBar->getContentSize().height));
}

void CHeroInfo::ClickClose(Ref *pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
	}
}

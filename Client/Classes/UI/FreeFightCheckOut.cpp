#include "FreeFightCheckOut.h"
#include "GameScene/GameUILayer.h"

CFreeFightCheckOut::CFreeFightCheckOut()
	:GameUI(IDU_FreeFightCheckOut,JsonFile_FreeFightCheckOut)
{
	m_pRedScore = nullptr;
	m_pBlueScore = nullptr;
	m_pSlider = nullptr;
	m_pListView = nullptr;
	m_pListItem = nullptr;
	m_pRadioBtn = nullptr;
}

CFreeFightCheckOut::~CFreeFightCheckOut()
{

}

bool CFreeFightCheckOut::onInit()
{
	do 
	{
		Button* pClose = (Button*)Helper::seekWidgetByName(m_pWidget,"BtnClose");
		m_pBlueScore = (Text*)Helper::seekWidgetByName(m_pWidget,"ScoreBlue");
		m_pRedScore = (Text*)Helper::seekWidgetByName(m_pWidget,"ScoreRed");
		m_pVictory = (Text*)Helper::seekWidgetByName(m_pWidget,"ScoreTitle");
		Widget* pLeftPanel = Helper::seekWidgetByName(m_pWidget,"LeftPanel");	
		Widget* pRightPanel = Helper::seekWidgetByName(m_pWidget,"RightPanel");	
		BREAK_IF(!(pClose&&m_pBlueScore&&m_pRedScore&&pLeftPanel&&pRightPanel&&m_pVictory));
		pClose->addTouchEventListener(this,toucheventselector(CFreeFightCheckOut::clickExit));
		m_pSlider = (Slider*)Helper::seekWidgetByName(m_pWidget,"Slider");	
		m_pListView = (ListView*)Helper::seekWidgetByName(m_pWidget,"ListView_List");
		m_pListItem = Helper::seekWidgetByName(m_pWidget,"ListItem");	
		BREAK_IF(!(m_pSlider&&m_pListView&&m_pListItem));
		m_pListItem->setEnabled(false);
		CheckBox *pBoxAll= (CheckBox*)(Helper::seekWidgetByName(m_pWidget, "Label_All"));
		CheckBox *pBoxMy= (CheckBox*)(Helper::seekWidgetByName(m_pWidget, "Label_My"));
		CheckBox *pBoxEnemy= (CheckBox*)(Helper::seekWidgetByName(m_pWidget, "Label_Enemy"));
		BREAK_IF(!(pBoxAll&&pBoxMy&&pBoxEnemy));
		m_pRadioBtn = RadioButtonSet::create();
		pBoxAll->getParent()->addChild(m_pRadioBtn);
		m_pRadioBtn->AddButton(pBoxAll);
		m_pRadioBtn->AddButton(pBoxMy);
		m_pRadioBtn->AddButton(pBoxEnemy);
		m_pRadioBtn->SetSelectEvent(this, SEL_SelectIndexEvent(&CFreeFightCheckOut::clickTab));
		return true;
	} while (0);
	return false;
}

void CFreeFightCheckOut::clickExit(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->destroyUI(this);
	}
}

void CFreeFightCheckOut::setCheckOutData(pk::GS2C_FreeFightCopyCheckout* value)
{
	m_checkOutdata = *value;
	m_pBlueScore->setText(CCString::createWithFormat("%d",value->blueCampScore)->getCString());
	m_pRedScore->setText(CCString::createWithFormat("%d",value->redCampScore)->getCString());
	bool bWin = gHero->GetCamp() == value->winCamp;
	m_pVictory->setText(bWin?"Win":value->winCamp?"Lose":"equal");
	m_pRadioBtn->ClickButton(0);
}

void CFreeFightCheckOut::clickTab(int index)
{
	vector<pk::freeFightCheckoutItem> listItems;
	switch (index)
	{
	case 0:
		{
			listItems = m_checkOutdata.blueVec;
			for (size_t i=0; i<m_checkOutdata.redVec.size(); ++i)
			{
				listItems.push_back(m_checkOutdata.redVec[i]);
			}
		}
		break;
	case 1:
		{
			listItems = (gHero->GetCamp()==RoleCamp_Blue)?m_checkOutdata.blueVec:m_checkOutdata.redVec;
		}
		break;
	case 2:
		{
			listItems = (gHero->GetCamp()!=RoleCamp_Blue)?m_checkOutdata.blueVec:m_checkOutdata.redVec;
		}
		break;
	default:
		break;
	}
	m_pListView->removeAllItems();
	for (size_t i=0; i<listItems.size(); ++i)
	{
		Widget* pItem = m_pListItem->clone();
		pItem->setEnabled(true);
		Text* pName = (Text*)pItem->getChildByName("Name");
		Text* pLevel = (Text*)pItem->getChildByName("Level");
		Text* pCount = (Text*)pItem->getChildByName("Count");
		Text* pCoin = (Text*)pItem->getChildByName("Coin");
		Text* pExp = (Text*)pItem->getChildByName("Exp");
		Text* pHonor = (Text*)pItem->getChildByName("Honor");
		BREAK_IF(!(pName&&pLevel&&pCount&&pCoin&&pExp&&pHonor));
		pName->setText(listItems[i].name);
		pLevel->setText(CCString::createWithFormat("%d",listItems[i].level)->getCString());
		pCount->setText(CCString::createWithFormat("%d/%d",listItems[i].killCnt,listItems[i].deadCnt)->getCString());
		pCoin->setText(CCString::createWithFormat("%d",listItems[i].bindCoin)->getCString());
		pExp->setText(CCString::createWithFormat("%d",listItems[i].exp)->getCString());
		pHonor->setText(CCString::createWithFormat("%d",listItems[i].honor)->getCString());
		m_pListView->pushBackCustomItem(pItem);
	}
	m_pSlider->setList(m_pListView, Slider::ListType::LISTVIEW_TYPE);
}
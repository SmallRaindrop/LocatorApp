#include "ItemTipsUI.h"
#include "GameScene/GameUILayer.h"
#include "StrengthenUI.h"


#define  DIFF_POS    667            //临界点
#define  DIS_LEN     300

enum OptionEvent
{
	OptionEvent_Refined,               //强化
};


ItemTipsUI::ItemTipsUI(void):GameUIWithOutSideTouchEvent(IDU_ITEMTIPSUI, JsonFile_ItemTipsUI)
	,m_pRoot(nullptr)
	,m_pAttri(nullptr)
	,m_pAttriList(nullptr)
	,m_pIcon(nullptr)
	,m_pName(nullptr)
	,m_pRefineVal(nullptr)
	,m_pRuleText(nullptr)
	,m_pSkillText(nullptr)
	,m_pStar(nullptr)
	,m_pStarList(nullptr)
	,m_pOptionBtn(nullptr)
	,m_pItem(nullptr)
	,m_pGodDevice(nullptr)
	,m_pGameUI(nullptr)
{
}


ItemTipsUI::~ItemTipsUI(void)
{
}

bool ItemTipsUI::onInit()
{
	if (!GameUIWithOutSideTouchEvent::onInit())
	{
		return false;
	}

	if(!m_pWidget) return false;

	m_pStar = Helper::seekWidgetByName(m_pWidget, "star");
	m_pAttri = Helper::seekWidgetByName(m_pWidget, "Panel_attri");

	m_pRoot = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_bg"));

	m_pIcon = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWidget, "icon_bg"));
	m_pName = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget, "name"));
	m_pRefineVal = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget, "RefinedLevel"));
	m_pStarList = dynamic_cast<ListView*>(Helper::seekWidgetByName(m_pWidget, "ListView_star"));
	m_pAttriList = dynamic_cast<ListView*>(Helper::seekWidgetByName(m_pWidget, "ListView_attri"));
	m_pSkillText = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget, "Skill"));
	m_pRuleText = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget, "Rule"));
	m_pOptionBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, "Button_19"));
	this->addOutSideTouchEventListener(this, OutSide_TouchEvent(&ItemTipsUI::outsideCallback));
	return true;
}

void ItemTipsUI::resetData()
{
	m_pIcon->removeAllChildren();
	m_pStarList->removeAllItems();
	m_pAttriList->removeAllItems();
	m_pItem = nullptr;
	m_pGodDevice = nullptr;
}

void ItemTipsUI::initByItem(CItem* item, Point locationpos, GameUI * ui)
{
	m_pItem = item;
	m_pGameUI = ui;
	if(locationpos.x > DIFF_POS)
	{
		m_pRoot->setPositionX(locationpos.x - DIS_LEN);
	}
	else
	{
		m_pRoot->setPositionX(locationpos.x + DIS_LEN);
	}
	ItemCfg* itemcfg = item->getItemData();
	ImageView* icon = ImageView::create();
	icon->loadTexture(ICON_PATH_ITEM+itemcfg->icon);
	icon->setPosition(Point(m_pIcon->getSize().width/2, m_pIcon->getSize().height/2));
	m_pIcon->addChild(icon);

	m_pName->setText(itemcfg->name);
	m_pRefineVal->setText(INT_TO_STRING(item->getItemInfo().strengthenLevel));
	for (int i = 0; i < item->getItemInfo().enhanceLevel; i++)
	{
		m_pStarList->pushBackCustomItem(m_pStar->clone());
	}

	m_pOptionBtn->setTag(OptionEvent_Refined);
	m_pOptionBtn->addTouchEventListener(this, toucheventselector(ItemTipsUI::eventCallBack));
}

void ItemTipsUI::initByGoddevice(GodDevice* goddevice, Point locationpos, GameUI * ui)
{
	m_pGodDevice = goddevice;
	m_pGameUI = ui;
	if(locationpos.x > DIFF_POS)
	{
		m_pRoot->setPositionX(locationpos.x - DIS_LEN);
	}
	else
	{
		m_pRoot->setPositionX(locationpos.x + DIS_LEN);
	}
	ItemCfg* itemcfg = goddevice->GetItemData();
	ImageView* icon = ImageView::create();
	icon->loadTexture(ICON_PATH_ITEM+itemcfg->icon);
	icon->setPosition(Point(m_pIcon->getSize().width/2, m_pIcon->getSize().height/2));
	m_pIcon->addChild(icon);

	m_pName->setText(itemcfg->name);
	m_pRefineVal->setText(INT_TO_STRING(goddevice->m_refineLevel));
	for (int i = 0; i < goddevice->m_enhanceLevel; i++)
	{
		m_pStarList->pushBackCustomItem(m_pStar->clone());
	}

	m_pOptionBtn->setTag(OptionEvent_Refined);
	m_pOptionBtn->addTouchEventListener(this, toucheventselector(ItemTipsUI::eventCallBack));
}

void ItemTipsUI::show(CItem* item, Point locationpos, GameUI* ui /*= nullptr*/)
{
	ItemTipsUI* pUI = dynamic_cast<ItemTipsUI*>(gGameUILayer->open(IDU_ITEMTIPSUI));
	pUI->resetData();
	if(!item) return;
	pUI->initByItem(item, locationpos, ui);
}

void ItemTipsUI::show(GodDevice* goditem,Point locationpos, GameUI* ui /*= nullptr*/)
{
	ItemTipsUI* pUI = dynamic_cast<ItemTipsUI*>(gGameUILayer->open(IDU_ITEMTIPSUI));
	pUI->resetData();
	if(!goditem) return;
	pUI->initByGoddevice(goditem, locationpos, ui);
}

void ItemTipsUI::eventCallBack(Ref* pSender, TouchEventType touchevent)
{
	if(touchevent == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		switch (tag)
		{
		case OptionEvent_Refined:
			{
				CStrengthenUI* pUI = dynamic_cast<CStrengthenUI*>(gGameUILayer->open(IDU_StrengthenUI));
				if(m_pItem)
				{
					if(pUI)
					{
						pUI->setItemType(m_pItem);
					}
				}
				else
				{
					if(pUI)
					{
						pUI->setItemType(m_pGodDevice);
					}
				}
				gGameUILayer->close(m_pGameUI);
				gGameUILayer->close(this);
			}
			break;
		default:
			break;
		}
	}
}

void ItemTipsUI::outsideCallback()
{
	gGameUILayer->close(this);
}




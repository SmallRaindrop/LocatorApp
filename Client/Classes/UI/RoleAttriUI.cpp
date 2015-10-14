#include "RoleAttriUI.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/Hero.h"
#include "RoleData.h"
#include "cocostudio/CCSGUIReader.h"
#include "CustomCtrl/ScrollGrids.h"
#include "MessageBoxUI.h"
#include "Net/NetDispatcher.h"
#include "ItemTipsUI.h"

#define   GRIDCNT                   64        //格子最大数
#define   AttributeCNT              38        //详细属性最大数
#define   LONGTIME                  1.f       //长按时间（秒）
#define   DELAYTIME                 300.f     //时间为毫秒

enum SignBtnTAG_en
{
	ATTRI_TAG,    //属性
	EQUIP_TAG,    //装备
	PACKSGE_TAG,  //背包
	CLOSE_TAG,    //关闭
	DETAIL_TAG,   //详细
	DETAIL_CL,    //详细关闭按钮
};

enum OperatBtn_en
{
	EqiupOP_TAG,  //装备
	DisBoardOP_TAG,//卸下
};

enum EquipBtnTag_en
{
	God_TAG,      //神器
	Weapons_TAG,  //武器
	Precious1_TAG,//法宝1
	Precious2_TAG,//法宝2
	Precious3_TAG,//法宝3
	Precious4_TAG,//法宝4
};


RoleAttriUI_cl::RoleAttriUI_cl():GameUI(IDU_RoleAttri, JSONFILE_ROLEATTRI)
	,m_longTime(0.f)
	,m_isLongTouch(false)
	,m_curEidx(-1)
	,m_curUIidx(ATTRI_TAG)
	,m_pAttackText(nullptr)
	,m_pScroll(nullptr)
	,m_pSlider(nullptr)
	,m_delayTime(0.f)
	,m_doubleTouched(false)
	,m_pMoveSprite(nullptr)
	,m_longTouched(false)
{
	for (int i = 0; i < 6; i++)
	{
		if(i < 3){m_pSignBtn[i] = nullptr; m_pPanel[i] = nullptr;}
		m_pEquipItem[i] = nullptr;
		m_pLabel[i]     = nullptr;
	}
}

RoleAttriUI_cl::~RoleAttriUI_cl()
{

}

bool RoleAttriUI_cl::onInit()
{
	if(!m_pWidget) return false;

	//背包滑动层
	m_pScroll = dynamic_cast<ScrollView*>(Helper::seekWidgetByName(m_pWidget, "ScrollView_bag"));
	m_pSlider = dynamic_cast<Slider*>(Helper::seekWidgetByName(m_pWidget, "Slider"));

	ScrollGrids_cl * scroll = nullptr;
	if(m_pScroll && m_pSlider)
	{
		scroll = ScrollGrids_cl::create(emGrids_BagEquip, 64, 4, m_pScroll, this);
		m_pSlider->setList(m_pScroll, Slider::ListType::SCROLLVIEW_TYPE);
		scroll->setLongTouched(true);
		scroll->setOneSelect(true);
		Point point = CCommonUI::getWorldPosition(m_pScroll);
		Size  size  = m_pScroll->getContentSize();
		m_scrollRect = Rect(point.x, point.y, size.width, size.height);
		gGridsManager->addScrollUI(scroll, emGrids_BagEquipRole);      //emGrids_BagEquip
	}

	for (int i =0; i < 6; i++)
	{
		if(i < 3)
		{
			m_pSignBtn[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget,FORMAT_TO_STRING("Button_%d", i)));
			if(m_pSignBtn[i])
			{
				m_pSignBtn[i]->setTag(i);
				m_pSignBtn[i]->addTouchEventListener(this, toucheventselector(RoleAttriUI_cl::callBack));
			}
		}
		if(i < 2)
		{
			//装备和卸下
			auto equipBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget,FORMAT_TO_STRING("Button_1%d", i)));
			equipBtn->setTag(i);
			equipBtn->addTouchEventListener(this, toucheventselector(RoleAttriUI_cl::operatCallBack));
		}
		m_pEquipItem[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, FORMAT_TO_STRING("Button_0_%d", i)));
		if(m_pEquipItem[i] && scroll)
		{
			m_pEquipItem[i]->setTag(i);
			if(i != EquipColumn_GodDevice )  //除了第一个格子神器
				scroll->addAreaEquip(m_pEquipItem[i]);
		}

		m_pLabel[i] = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget, FORMAT_TO_STRING("Label_0_%d", i)));
	}

	m_pPanel[0] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget, "Panel_attr"));
	m_pPanel[1] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget, "Panel_bag"));
	m_pPanel[2] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget, "Panel_xx"));
	Text * pAttackText = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget, "Label_attack"));
	Point point  = pAttackText->getPosition();
	pAttackText->removeFromParent();
	m_pAttackText = Label::createWithBMFont("assets/common/font/fightcapacity.fnt", "0");
	m_pAttackText->setAnchorPoint(Point(0.f, 0.5f));
	m_pAttackText->setPosition(point);
	m_pPanel[0]->addChild(m_pAttackText);

	//关闭按钮
	auto  closebtn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget,"Button_close"));
	if(closebtn)
	{
		closebtn->setTag(CLOSE_TAG);
		closebtn->addTouchEventListener(this, toucheventselector(RoleAttriUI_cl::callBack));
	}
	//详细属性按钮
	auto  detailbtn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, "Button_29"));
	if(detailbtn)
	{
		detailbtn->setTag(DETAIL_TAG);
		detailbtn->addTouchEventListener(this, toucheventselector(RoleAttriUI_cl::callBack));
	}

	//详细属性关闭按钮
	auto  cl_btn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, "Button_x"));
	if(cl_btn)
	{
		cl_btn->setTag(DETAIL_CL);
		cl_btn->addTouchEventListener(this, toucheventselector(RoleAttriUI_cl::callBack));
	}

	setBtnShowByIdx(ATTRI_TAG);
	setPanelShowByIdx(ATTRI_TAG);
	freshShow();
	initDetailData();
	initRoleEquip();
	return true;
}


void RoleAttriUI_cl::onOpen()
{
	if(m_pScroll && m_pSlider)
	{
		m_pSlider->setList(m_pScroll, Slider::ListType::SCROLLVIEW_TYPE);
	}
	m_takeoff.clear();
	m_curEidx = 0;
	initRoleEquip();
}


void RoleAttriUI_cl::setBtnShowByIdx(int idx)
{
	for (auto i = 0; i < 3; i++)
	{
		if(m_pSignBtn[i])
		{
			m_pSignBtn[i]->setButtonShowType(Normal_TYPE);
		}
	}
	if(m_pSignBtn[idx])
		m_pSignBtn[idx]->setButtonShowType(Press_TYPE);
}

void RoleAttriUI_cl::setPanelShowByIdx(int idx)
{
	m_doubleTouched = false;
	m_longTouched   = false;
	for (int i = 0; i < 2; i++)
	{
		if(m_pPanel[i])
			m_pPanel[i]->setEnabled(false);
	}
	if(m_pPanel[idx])
	{
		m_pPanel[idx]->setEnabled(true);
		if(idx == EQUIP_TAG){ m_doubleTouched = true; m_longTouched = true;}
	}
	if(m_pPanel[2]) m_pPanel[2]->setEnabled(false);
}


void RoleAttriUI_cl::initDetailData()
{
	Widget* child = GUIReader::getInstance()->widgetFromJsonFile(JSONFILE_ROLEEATTRICHILD);
	if(!child) return ;
	ListView * pList  = nullptr;
	if(m_pPanel[2])
	{
		pList = dynamic_cast<ListView*>(m_pPanel[2]->getChildByName("ListView_xiangx"));
		if(!pList) return;
		pList->setItemsMargin(10);
		pList->removeAllItems();
	}
	for(int i = 1; i <= AttributeCNT; i++)
	{
		AttributeInfoCfg * data =  AttributeTableData.get(i);
		if(data && data->detail_display == 1)
		{
			Widget * pChild = child->clone();
			if(!pChild) return;
			Text * name = dynamic_cast<Text*>(pChild->getChildByName("Label_type"));
			BREAK_IF(!name);
			name->setText(data->name);
			Text * num = dynamic_cast<Text*>(pChild->getChildByName("Label_name"));
			BREAK_IF(!num);
			Text * des = dynamic_cast<Text*>(pChild->getChildByName("Label_des"));
			BREAK_IF(!des);
			
			if(data->total_display == 1)   //除以1000 百分数显示  格式为56.65% 
			{
				num->setText(FORMAT_TO_STRING("%.02f%%",gHero->GetPropertyInt((RoleProperty)data->index)/(float)1000));
			}
			else
			{
				num->setText(INT_TO_STRING(gHero->GetPropertyInt((RoleProperty)data->index)));
			}
			pList->pushBackCustomItem(pChild);
		}
	}
}

void RoleAttriUI_cl::initRoleEquip()
{
	CItemGridArray* pGridsData = gGridsManager->getGridsData(emGrids_Role);
	if(!pGridsData) return ;
	for (size_t i = 0; i < 6; i++)
	{
		m_pEquipItem[i]->removeAllChildren();
		CItemGrid* pItemGrid = pGridsData->GetItemGrid(i);
		if(!pItemGrid) continue;
		CGridIcon* pGridIcon = CGridIcon::create(pItemGrid->GetItem(),i,emGrids_Role);
		if (pGridIcon)
		{
			pGridIcon->setPosition(Point(m_pEquipItem[i]->getSize().width/2,m_pEquipItem[i]->getSize().height/2));	
			m_pEquipItem[i]->addChild(pGridIcon);	
			pGridIcon->setTag(1);
			pGridIcon->addTouchEventListener(this, toucheventselector(RoleAttriUI_cl::equipCallBack));
		}
	}

	GodDevice* goddevice = gHero->GetGodDeviceManager().GetIsDressGodPtr();
	if(goddevice)
	{
		ItemCfg* itemcfg = goddevice->GetItemData();
		if(itemcfg)
		{
			//神器未处理
			m_pEquipItem[0]->removeAllChildren();
			ImageView* godIcon = ImageView::create();
			godIcon->loadTexture(ICON_PATH_ITEM+itemcfg->icon);
			godIcon->setPosition(Point(m_pEquipItem[0]->getSize().width/2,m_pEquipItem[0]->getSize().height/2));	
			m_pEquipItem[0]->addChild(godIcon);
			godIcon->setTouchEnabled(true);
			godIcon->addTouchEventListener(this, toucheventselector(RoleAttriUI_cl::goddeviceCallBack));
		}
	}
}

void RoleAttriUI_cl::RefreshRoleEquip(pk::GS2C_EquipGetItem_Ret *value)
{
	if(value)
	{
		CItemGridArray* pGridsData = gGridsManager->getGridsData(emGrids_Role);
		for (size_t i = 0; i < value->equipItems.size(); i++)
		{
			m_pEquipItem[value->equipItems[i].part]->removeAllChildren();
			CItemGrid* pItemGrid = pGridsData->GetItemGrid(value->equipItems[i].part);
			if(!pItemGrid) continue;
			CGridIcon* pGridIcon = CGridIcon::create(pItemGrid->GetItem(),value->equipItems[i].part,emGrids_Role);
			if (pGridIcon)
			{
				pGridIcon->setPosition(Point(m_pEquipItem[value->equipItems[i].part]->getSize().width/2,m_pEquipItem[value->equipItems[i].part]->getSize().height/2));	
				m_pEquipItem[value->equipItems[i].part]->addChild(pGridIcon);	
				pGridIcon->setTag(1);
				pGridIcon->addTouchEventListener(this, toucheventselector(RoleAttriUI_cl::equipCallBack));
			}
		}
	}
}

void RoleAttriUI_cl::addEquipTouchEvent(CGridIcon* grid)
{
	if(grid)
	{
		grid->addTouchEventListener(this, toucheventselector(RoleAttriUI_cl::equipCallBack));
	}
}

void RoleAttriUI_cl::freshShow()
{
	//属性界面
	if(m_curUIidx == ATTRI_TAG)
	{
		if(m_pAttackText) m_pAttackText->setString(INT_TO_STRING(gHero->GetPropertyInt(RoleProperty_Fight_Max)));
		// 0:hp 1:magic 2:attack(s) 3: defence 4:strength_at 5:strengt_sk
		if(m_pLabel[0]) m_pLabel[0]->setText(INT_TO_STRING(gHero->GetPropertyInt(RoleProperty_HP)));
		if(m_pLabel[1]) m_pLabel[1]->setText(INT_TO_STRING(gHero->GetPropertyInt(RoleProperty_MP)));
		/******************************************************************************************************
		秒伤=（物理伤害+火伤害+冰伤害+电伤害+毒伤害）*（1+攻击加速）*（1+暴击率*暴击伤害系数）*100/weaponfix
		weaponfix在equipbase表中
		*******************************************************************************************************/
		int millHurt = (gHero->GetPropertyInt(RoleProperty_phy_dam) 
						+ gHero->GetPropertyInt(RoleProperty_fire_dam)
						+ gHero->GetPropertyInt(RoleProperty_cold_dam)
						+ gHero->GetPropertyInt(RoleProperty_elec_dam)
						+ gHero->GetPropertyInt(RoleProperty_toxin_dam))
						*(1 +  gHero->GetPropertyInt(RoleProperty_atk_speed_increase))
						*(1 + gHero->GetPropertyInt(RoleProperty_crit) * gHero->GetPropertyInt(RoleProperty_crit_dam_factor))
						*100/100;
		if(m_pLabel[2]) m_pLabel[2]->setText(INT_TO_STRING(millHurt));
		if(m_pLabel[3]) m_pLabel[3]->setText(INT_TO_STRING(gHero->GetPropertyInt(RoleProperty_armor)));
		if(m_pLabel[4]) m_pLabel[4]->setText(INT_TO_STRING(gHero->GetPropertyInt(RoleProperty_base_dam_increase)));
		if(m_pLabel[5]) m_pLabel[5]->setText(INT_TO_STRING(gHero->GetPropertyInt(RoleProperty_skill_power)));
	}
	else
	{

	}
}


int RoleAttriUI_cl::getEquipNum()
{
	int cnt = 0;
	for (int i = 0; i < 4; i++)
	{
		CGridIcon * item = dynamic_cast<CGridIcon*>( m_pEquipItem[i]->getChildByTag(1));
		if(item)
		{
			cnt += 1;
		}
	}
	return cnt;
}


void RoleAttriUI_cl::callBack(Ref * _ref, TouchEventType _type)
{
	if(_type == TOUCH_EVENT_ENDED)
	{
		auto tag = ((Button*)_ref)->getTag();
		switch (tag)
		{
		case ATTRI_TAG:
			setBtnShowByIdx(tag);
			setPanelShowByIdx(tag);
			break;
		case EQUIP_TAG:
			setBtnShowByIdx(tag);
			setPanelShowByIdx(tag);
			break;
		case PACKSGE_TAG:
			gGameUILayer->close(this);
			gGameUILayer->open(IDU_RolePackage);
			break;
		case CLOSE_TAG:
			gGameUILayer->close(this);
			break;
		case DETAIL_TAG:
			if(m_pPanel[2]) m_pPanel[2]->setEnabled(true);
			freshShow();
			gCocosAudio->PlayEffect(127);
			break;
		case DETAIL_CL:
			if(m_pPanel[2]) m_pPanel[2]->setEnabled(false);
			gCocosAudio->PlayEffect(127);
			break;
		default:
			break;
		}
	}
}

void RoleAttriUI_cl::goddeviceCallBack(Ref* pSender, TouchEventType type)
{
	if(type == TOUCH_EVENT_BEGAN)
	{
		Point point = CCommonUI::getWorldPosition((ImageView*)pSender);
		GodDevice* goddevice = gHero->GetGodDeviceManager().GetIsDressGodPtr();
		ItemTipsUI::show(goddevice, point, this);
	}
}

void RoleAttriUI_cl::equipCallBack(Ref* _ref, TouchEventType _type)
{
	CGridIcon * item = dynamic_cast<CGridIcon*>(_ref);
	if(!item) return;
	m_curEidx = item->getParent()->getTag();
	if(_type == TOUCH_EVENT_BEGAN)
	{
		if(m_longTime == 0.f && m_longTouched)
		{
			this->schedule(schedule_selector(RoleAttriUI_cl::updateTime));
		}
		Point point = CCommonUI::getWorldPosition(item);
		ItemTipsUI::show(item->GetItem(), point, this);
	}
	else if(_type == TOUCH_EVENT_MOVED)
	{
		if(m_isLongTouch && m_pMoveSprite)
		{
			m_pMoveSprite->setPosition(item->getTouchMovePos());
			checkBagIsOverlap();
		}
	}
	else if(_type == TOUCH_EVENT_ENDED)
	{
		if(m_longTime >= 0.016f && m_longTouched)
		{
			this->unschedule(schedule_selector(RoleAttriUI_cl::updateTime));
			m_longTime = 0.f;
		}
		if(m_doubleTouched)
		{
			float millTime = getMilliSecond();
			if(m_delayTime == 0.f)
			{
				m_delayTime = millTime; 
			}
			else if(millTime - m_delayTime <= DELAYTIME) //双击事件
			{
				millTime = 0.f;
				for (auto iter: m_takeoff)
				{
					if(iter == m_curEidx)
						return;
				}
				m_takeoff.push_back(m_curEidx);
			}
			else
			{
				m_delayTime = 0.f;
			}
		}
		if(m_pMoveSprite)
		{
			m_pMoveSprite->removeFromParent();
			m_pMoveSprite = nullptr;
		}
	}
	else if(_type == TOUCH_EVENT_CANCELED)
	{
		if(checkBagIsOverlap())
		{
			CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,STR_ROLEBAG_ADMINUNLOADING,[&](bool type){
					CGridIcon * item = dynamic_cast<CGridIcon*>( m_pEquipItem[m_curEidx]->getChildByTag(1));
				if(type)
				{
					gHero->UnEquip((EquipColumnType)m_curEidx);
				}
			},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
				this,NULL,CMessageBoxUI::Scene_Game);
		}
		else
		{
			item->setVisible(true);
		}
		if(m_pMoveSprite)
		{
			m_pMoveSprite->removeFromParent();
			m_pMoveSprite = nullptr;
		}
	}
}


void RoleAttriUI_cl::operatCallBack(Ref* _ref, TouchEventType _type)
{
	if(_type == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(_ref)->getTag();
		switch (tag)
		{
		case EqiupOP_TAG: 
			{
				gHero->Equip(dynamic_cast<ScrollGrids_cl*>(m_pScroll)->getSelectIndex());
			}
			break;
		case DisBoardOP_TAG:
			{
				if(m_takeoff.size() == 0)
				{
					CMessageBoxUI::Show(CMessageBoxUI::MBM_OK,STR_ROLEBAG_NOGIVEUP,nullptr,STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
						nullptr,NULL,CMessageBoxUI::Scene_Game);
					return;
				}
				CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,STR_ROLEBAG_ADMINUNLOADING,[&](bool type){
					if(type)
					{
						for (size_t i = 0; i < m_takeoff.size(); i++)
						{
							gHero->UnEquip((EquipColumnType)m_takeoff[i]);
						}
						m_takeoff.clear();
						m_delayTime = 0.f;
					}
				},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
					nullptr,NULL,CMessageBoxUI::Scene_Game);
			}
			break;
		default:
			break;
		}
	}
}


bool RoleAttriUI_cl::checkBagIsOverlap()
{
	if(m_pMoveSprite)
	{
		Size size = m_pMoveSprite->getContentSize();
		Point point = m_pMoveSprite->getPosition();
		Rect rect = Rect(point.x - size.width/2, point.y - size.height/2, size.width, size.height);
		
		if(m_scrollRect.intersectsRect(rect))
		{
			return true;
		}
	}
	return false;
}

void RoleAttriUI_cl::updateTime(float fd)
{
	m_longTime += fd;
	if(m_longTime >= LONGTIME)
	{
		this->unschedule(schedule_selector(RoleAttriUI_cl::updateTime));
		m_isLongTouch = true;
		m_longTime = 0.f;
		if(m_pMoveSprite == nullptr && m_pEquipItem[m_curEidx])
		{
			m_pMoveSprite = ImageView::create();
			CGridIcon * item = dynamic_cast<CGridIcon*>( m_pEquipItem[m_curEidx]->getChildByTag(1));
			m_pMoveSprite->loadTexture(item->getIconPath(), item->getTextureType());
			m_pMoveSprite->setPosition(item->getTouchStartPos());
			this->addChild(m_pMoveSprite);
		}
	}
}
#include "RolePackageUI.h"
#include "GameScene/GameUILayer.h"
#include "RoleAttriUI.h"
#include "CustomCtrl/ScrollGrids.h"
#include "GameScene/GridsManager.h"
#include "GameScene/Hero.h"

#define   GRIDMAX          64

enum RoleBagB_TGA
{
	ATTRI_BTN_TAG,  
	EQUIP_BTN_TAG,
	BAG_BTN_TAG,
	TYPE_EQUIP_TAG,
	TYPE_GOODS_TAG,
	TYPE_PICTURE_TAG,
	TYPE_SUNDRY_TAG,
	SALE_TAG,
	CLEAN_TAG,
	Close_TAG,
};


RolePackageUI_cl::RolePackageUI_cl():GameUI(IDU_RolePackage, JSONFILE_ROLEPACKAGE)
	,m_curTypeIdx(0)
	,m_jb(0)
{
	for (int i = 0 ; i < 4; i++)
	{
		m_pScorllView[i] = nullptr;
		m_pSlider[i]     = nullptr;
		m_numText[i]     = nullptr;
		m_childCount[i]  = 0;
	}
}

RolePackageUI_cl::~RolePackageUI_cl()
{

}


bool RolePackageUI_cl::onInit()
{
	if(!m_pWidget)  return false;
	
	//按钮结构：0 属性, 1 装备, 2 背包, 3 T装备, 4 T材料, 5 T图纸, 6 T杂项, 7 Op出售, 8 Op整理

	for (int i = 0; i < 9; i ++)
	{
		auto btn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, FORMAT_TO_STRING("Button_%d", i)));
		if(btn){ btn->setTag(i); btn->addTouchEventListener(this, toucheventselector(RolePackageUI_cl::callBack));}
		if(i == 2 && btn) btn->setButtonShowType(Press_TYPE);
	}

	m_pScorllView[0] = dynamic_cast<ScrollView*>(Helper::seekWidgetByName(m_pWidget,"ScrollView"));
	m_pSlider[0]     = dynamic_cast<Slider*>(Helper::seekWidgetByName(m_pWidget, "Slider"));
	if(m_pScorllView[0] && m_pSlider[0])
	{
		m_pScorllView[1] = dynamic_cast<ScrollView*>(m_pScorllView[0]->clone());
		m_pScorllView[2] = dynamic_cast<ScrollView*>(m_pScorllView[0]->clone());
		m_pScorllView[3] = dynamic_cast<ScrollView*>(m_pScorllView[0]->clone());
		m_pSlider[1]     = dynamic_cast<Slider*>(m_pSlider[0]->clone());
		m_pSlider[2]     = dynamic_cast<Slider*>(m_pSlider[0]->clone());
		m_pSlider[3]     = dynamic_cast<Slider*>(m_pSlider[0]->clone());
		m_pWidget->getChildByName("Panel_parent")->addChild(m_pScorllView[1]);
		m_pWidget->getChildByName("Panel_parent")->addChild(m_pSlider[1]);
		m_pWidget->getChildByName("Panel_parent")->addChild(m_pScorllView[2]);
		m_pWidget->getChildByName("Panel_parent")->addChild(m_pSlider[2]);
		m_pWidget->getChildByName("Panel_parent")->addChild(m_pScorllView[3]);
		m_pWidget->getChildByName("Panel_parent")->addChild(m_pSlider[3]);
		setShowByType(TYPE_EQUIP_TAG);
		initScrollView();
	}

	m_numText[0] = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget,"Lable_index"));
	if(m_numText[0])
	{
		m_numText[1] = dynamic_cast<Text*>(m_numText[0]->clone());
		m_numText[2] = dynamic_cast<Text*>(m_numText[0]->clone());
		m_numText[3] = dynamic_cast<Text*>(m_numText[0]->clone());
		m_numText[0]->getParent()->addChild(m_numText[1]);
		m_numText[0]->getParent()->addChild(m_numText[2]);
		m_numText[0]->getParent()->addChild(m_numText[3]);
	}

	m_jbText = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget, "Label_jb"));
	if(m_jbText)
	{
		m_jb = gHero->GetMoney();
		m_jbText->setText(INT_TO_STRING(m_jb));
	}
	//关闭
	auto closebtn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, "Button_close"));
	if(closebtn)
	{
		closebtn->setTag(Close_TAG);
		closebtn->addTouchEventListener(this, toucheventselector(RolePackageUI_cl::callBack));
	}
	return true;
}

void RolePackageUI_cl::onOpen()
{
	for (int i = 0; i < 4; i++)
	{
		if(m_pSlider[i] && m_pScorllView[i])
		m_pSlider[i]->setList(m_pScorllView[i], Slider::ListType::SCROLLVIEW_TYPE);
	}
	this->unscheduleUpdate();
	this->scheduleUpdate();
}

void RolePackageUI_cl::initScrollView()
{
	emGridsType type = emGrids_None;
	for (int i = 0; i < 4; i++)
	{
		if(m_pScorllView[i] && m_pSlider[i])
		{
			//1:装备背包  2:杂物背包 3: 材料背包 4:图纸背包
			switch (i)
			{
			case 0:
				type = emGrids_BagEquip;
				break;
			case 1:
				type = emGrids_BagMaterial;
				break;
			case 2:
				type = emGrids_BagTuZi;
				break;
			case 3:
				type = emGrids_BagZaWu;
				break;
			default:
				break;
			}
			ScrollGrids_cl* pUI = ScrollGrids_cl::create(type,64,8,m_pScorllView[i], this);
			m_pSlider[i]->setList(m_pScorllView[i], Slider::ListType::SCROLLVIEW_TYPE);
			gGridsManager->addScrollUI(pUI, type);
		}
	}
}

void RolePackageUI_cl::setShowByType(int _type)
{
	for (int i = 0; i < 4; i++)
	{
		if(m_pScorllView[i]) m_pScorllView[i]->setEnabled(false);
		if(m_pSlider[i]) m_pSlider[i]->setEnabled(false);
		auto btn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, FORMAT_TO_STRING("Button_%d", i + 3)));
		if(btn)btn->setButtonShowType(Normal_TYPE);
		if(m_numText[i]) m_numText[i]->setEnabled(false);
	}
	if(m_pScorllView[_type - 3]) m_pScorllView[_type - 3]->setEnabled(true);
	if(m_pSlider[_type - 3]) m_pSlider[_type - 3]->setEnabled(true);
	if(m_numText[_type - 3]) m_numText[_type - 3]->setEnabled(true);
	auto btn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, FORMAT_TO_STRING("Button_%d", _type)));
	if(btn)btn->setButtonShowType(Press_TYPE);
	m_curTypeIdx = _type - 3;
}

void RolePackageUI_cl::callBack( Ref* _ref, TouchEventType _type )
{
	if(_type == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(_ref)->getTag();
		switch (tag)
		{
		case ATTRI_BTN_TAG:
			{
				RoleAttriUI_cl*  roleLayer = dynamic_cast<RoleAttriUI_cl*>(gGameUILayer->open(IDU_RoleAttri));
				if(roleLayer) {roleLayer->setBtnShowByIdx(0); roleLayer->setPanelShowByIdx(0);}
				gGameUILayer->close(this);
			}
			break;
		case EQUIP_BTN_TAG:
			{
				RoleAttriUI_cl*  roleLayer = dynamic_cast<RoleAttriUI_cl*>(gGameUILayer->open(IDU_RoleAttri));
				if(roleLayer) {roleLayer->setBtnShowByIdx(1); roleLayer->setPanelShowByIdx(1);}
				gGameUILayer->close(this);
			}
			break;
		case BAG_BTN_TAG:
			break;
		case TYPE_EQUIP_TAG:
		case TYPE_GOODS_TAG:
		case TYPE_PICTURE_TAG:
		case TYPE_SUNDRY_TAG:
			setShowByType(tag);
			break;
		case SALE_TAG:
			{
				dynamic_cast<ScrollGrids_cl*>(m_pScorllView[m_curTypeIdx])->saleSelectItem();
			}
			break;
		case CLEAN_TAG:
			{
				dynamic_cast<ScrollGrids_cl*>(m_pScorllView[m_curTypeIdx])->cleanBag();
			}
			break;
		case  Close_TAG:
			gGameUILayer->close(this);
			break;
		default:
			break;
		}
	}
}

void RolePackageUI_cl::freshShow()
{

}

void RolePackageUI_cl::update( float dt )
{
	if(m_pScorllView[m_curTypeIdx - 3])
	{
		const int cnt = dynamic_cast<ScrollGrids_cl*>(m_pScorllView[m_curTypeIdx - 3])->getChildrenCount();
		if(cnt != m_childCount[m_curTypeIdx - 3] && m_numText[m_curTypeIdx -3])
		{
			 m_numText[m_curTypeIdx -3]->setText(FORMAT_TO_STRING("%d/%d",cnt, GRIDMAX));
			 m_childCount[m_curTypeIdx - 3] = cnt;
		}
	}
	if(m_jbText && gHero->GetMoney() != m_jb)
	{
		m_jb = gHero->GetMoney();
		m_jbText->setText(INT_TO_STRING(m_jb));
	}
}

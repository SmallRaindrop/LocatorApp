#include "ManufactureUI.h"
#include "GameScene/GameUILayer.h"
#include "Net/NetDispatcher.h"
#include "GameScene/GameManager.h"
#include "cocostudio/CCSGUIReader.h"

#define  MANUFACTURE_ACTIONTIME 3.0f           //制造动画总时间    
#define  BLUENINGRIDS            12
#define  REMAINTIEM              300           //不能加速的剩余时间

enum MainBtnTag
{
	MainBtnTag_ManuFacture,       //制造
	MainBtnTag_LINE,              //生产线
	MainBtnTag_TUZHI,             //图纸
	MainBtnTag_Material,          //材料
	MainBtnTag_Close,             //关闭
};

enum ManufactureOptionTag
{
	ManufactureOptionTag_PushTag,      //放入图纸按钮
	ManufactureOptionTag_StartTag,     //开始制造
};

enum BluePringSignTag
{
	BluePringSignTag_ALL,          //全部
	BluePringSignTag_Weapon,       //武器
	BluePringSignTag_Armor,        //防具
	BluePringSignTag_Relic,        //神器
	BluePringSignTag_Pet,          //宠物
	BluePringSignTag_Other,        //杂项
	BluePringSignTag_Sale,         //出售
	BluePringSignTag_Buy,          //回购
};

enum MaterialOptionTag
{
	MaterialOptionTag_Sale,         //出售
	MaterialOptionTag_Buy,          //回购
};


bool FastTipsUI_cl::initdata(int id)
{
	if(!Layer::init()&& id == -1)
		return false;
	this->setTouchEnabled(true);
	m_id = id;
	Widget* layer = GUIReader::getInstance()->widgetFromJsonFile(JsonFile_ManufactureJiDuUI);
	if(!layer) return false;
	layer->addTouchEventListener(this, toucheventselector(FastTipsUI_cl::callback));
	layer->setTouchEnabled(true);

	m_pGold = dynamic_cast<Text*>(layer->getChildByName("Label_tips"));
	m_point = m_pGold->getPosition();
	m_pGold->removeFromParent();
	m_pGold = RichTextEx::create();
	layer->addChild(dynamic_cast<RichTextEx*>(m_pGold));
	

	ManufactureData_v& data = gDataPool->getManufactureData();

	ImageView* bg = dynamic_cast<ImageView*>(layer->getChildByName("Image_11"));
	m_rect = bg->getBoundingBox();

	//头像
	ImageView * icon = dynamic_cast<ImageView*>(layer->getChildByName("Image_icon"));

	Text* iconname = dynamic_cast<Text*>(layer->getChildByName("Label_iconname"));
	iconname->setText(data[id]->iconname);
	Text* targetname = dynamic_cast<Text*>(layer->getChildByName("Label_name")); 
	targetname->setText(data[id]->targetname);
	m_pLoadingbar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(layer,"ProgressBar"));
	m_pLoadingbar->setPercent(data[id]->percent);
	Button* btn = dynamic_cast<Button*>(layer->getChildByName("Button_0"));
	btn->setButtonSpriteGray();
	if(data[id]->serverData.eliminateCdFlag == 0)
	{
		btn->addTouchEventListener(this, toucheventselector(FastTipsUI_cl::fastCallback));
	}
	else if(data[id]->leftTime <= REMAINTIEM || data[id]->serverData.eliminateCdFlag != 0)
	{
		btn->setButtonShowType(Press_TYPE);
	}
	

	this->addChild(layer);
	setFastGold();
	return true;
}


void FastTipsUI_cl::setFastGold()
{
	ManufactureData_v& data = gDataPool->getManufactureData();
	if(data[m_id]->leftTime <= REMAINTIEM)
	{
		dynamic_cast<RichTextEx*>(m_pGold)->setVisible(false);
	}
	else
	{
		dynamic_cast<RichTextEx*>(m_pGold)->ParseAndLayout(FORMAT_TO_STRING(STR_MANUF_FASTTEXT, data[m_id]->curGold));
		Size size = m_pGold->getVirtualRendererSize();
		dynamic_cast<RichTextEx*>(m_pGold)->setPosition(Point(m_point.x + size.width/2, m_point.y));
	}

	m_pLoadingbar->setPercent(data[m_id]->percent);
}


void FastTipsUI_cl::callback(Ref * pSneder, TouchEventType touchevent)
{
	if(touchevent == TOUCH_EVENT_ENDED)
	{
		Widget* widget = dynamic_cast<Widget*>(pSneder);
		Point pos = widget->getTouchEndPos();
		if(!m_rect.containsPoint(pos))
		{
			ManufactureUI_cl* pUI = dynamic_cast<ManufactureUI_cl*>(gGameUILayer->getActiveUI(IDU_ManufactureUI));
			if(pUI)
			{
				pUI->m_pFastTips = nullptr;
			}
			this->runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([&](){
				this->removeFromParent();
			}), nullptr));
			
		}
	}
}


void FastTipsUI_cl::fastCallback(Ref* pSender, TouchEventType touchevent)
{
	if(touchevent == TOUCH_EVENT_ENDED)
	{
		ManufactureData_v& data = gDataPool->getManufactureData();
		pk::C2GS_Eliminate_Cd cmd;
		cmd.itemDataId = data[m_id]->serverData.itemDataId;
		cmd.Send(gNetSocket);
		dynamic_cast<Button*>(pSender)->setButtonShowType(Disable_TYPE);
		ManufactureUI_cl* pUI = dynamic_cast<ManufactureUI_cl*>(gGameUILayer->getActiveUI(IDU_ManufactureUI));
		if(pUI)
		{
			pUI->m_pFastTips = nullptr;
		}
		this->removeFromParent();
	}
}


FastTipsUI_cl * FastTipsUI_cl::create(int id)
{
	FastTipsUI_cl* ret = new FastTipsUI_cl();
	if(ret && ret->initdata(id))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

ManufactureUI_cl::ManufactureUI_cl():GameUI(IDU_ManufactureUI, JsonFile_ManufactureUI)
	,m_pageIndex(0)
	,m_bSelectBlueprint(false)
	,m_pCurBlueprint(nullptr)
	,m_blueprintID(-1)
	,m_bActionRet(false)
	,m_pLineScroll(nullptr)
	,m_pLineSlider(nullptr)
	,m_pLineChild(nullptr)
	,m_lineStartPos(0.f,0.f)
	,m_lineDisX(0)
	,m_lineDisY(0)
	,m_blueSign(0)
	,m_pMaterialScroll(nullptr)
	,m_pMaterialSlider(nullptr)
	,m_pBlueItem(nullptr)
	,m_pFastTips(nullptr)
{
	for (int i = 0; i < 8; i++)
	{
		if(i < 2)
		{
			m_pOptionBtn[i] = nullptr;
			m_pMaterialBtn[i] = nullptr;
		}
		if(i < 4) m_pPanel[i] = nullptr;
		if(i < 5) 
		{
			m_pNeed[i] = nullptr;
			m_pButton[i] = nullptr;
			m_pBlueTypeArrary[i] = new CItemGridArray();
		}
		if(i < 6)
		{
			m_pMaterialIcon[i] = nullptr;
			m_pMaterialCount[i] = nullptr;
			m_pBlueScroll[i] = nullptr;
			m_pBlueSlider[i] = nullptr;
		}
		m_pBlueBtn[i] = nullptr;
	}
	m_vLineWidget.clear();
}

ManufactureUI_cl::~ManufactureUI_cl()
{
	if(m_pLineChild)
	{
		m_pLineChild->release();
		m_pLineChild = nullptr;
	}
	for (auto iter : m_vLineWidget)
	{
		iter->release();
	}
	m_vLineWidget.clear();

	for (int i = 0; i <5; i++)
	{
		if(m_pBlueTypeArrary[i])
		{
			delete m_pBlueTypeArrary[i];
			m_pBlueTypeArrary[i] = nullptr;
		}

	}
}

bool ManufactureUI_cl::onInit()
{
	if(!m_pWidget) return false;
	m_pPanel[0] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget, "Panel_zhizao"));
	m_pPanel[1] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget, "Panel_line"));
	m_pPanel[2] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget, "Panel_tuzhi"));
	m_pPanel[3] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget, "Panel_material"));
	
	for (int i = 0; i < 5;i++)
	{
		m_pButton[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, FORMAT_TO_STRING("Button_%d", i)));
		m_pButton[i]->setTag(i);
		m_pButton[i]->addTouchEventListener(this, toucheventselector(ManufactureUI_cl::callback));
	}
	initManufacture();
	initLine();
	initBluePrint();
	initMaterial();
	changePanel();
	openNewLineRet();
	return true;
}

void ManufactureUI_cl::onOpen()
{
	m_bSelectBlueprint = false;
	m_pageIndex = MainBtnTag_ManuFacture;
	if(!m_pCurBlueprint)
	{
		for (int i = 0; i < 6; i++)
		{
			if(i >=2 && i < 5)
			m_pNeed[i]->setVisible(false);
			m_pMaterialIcon[i]->setVisible(false);
			m_pMaterialCount[i]->setVisible(false);
		}
	}
	pushBlueprintByItem(m_pBlueItem);
}

void ManufactureUI_cl::initManufacture()
{
	if(!m_pPanel[0]) return ;
	m_pOptionBtn[0] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanel[0], "Button_pushtuzhi"));
	m_pOptionBtn[1] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanel[0], "Button_start"));
	for (int i = 0; i < 6; i++)
	{
		m_pMaterialIcon[i] = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pPanel[0], FORMAT_TO_STRING("Image_material%d", i)));
		m_pMaterialIcon[i]->setTag(i);
		m_pMaterialIcon[i]->addTouchEventListener(this, toucheventselector(ManufactureUI_cl::manufactureMaterialCallback));

		m_pMaterialCount[i] = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pPanel[0], FORMAT_TO_STRING("Label_material%d", i)));
		if(i < 2)
		{
			if(m_pOptionBtn[i])
			{
				m_pOptionBtn[i]->setTag(i);
				m_pOptionBtn[i]->setButtonSpriteGray();
				m_pOptionBtn[i]->addTouchEventListener(this, toucheventselector(ManufactureUI_cl::manufactureOptionCallback));
			}
		}

		if(i < 5)
		{
			m_pNeed[i] = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pPanel[0], FORMAT_TO_STRING("Label_need%d", i)));
			if(i >= 2 && i<5)
			{
				Point pos = m_pNeed[i]->getPosition();
				m_pNeed[i]->removeFromParent();
				m_pNeed[i] = RichTextEx::create();
				dynamic_cast<RichTextEx*>(m_pNeed[i])->setPosition(pos);
				m_pPanel[0]->addChild(dynamic_cast<RichTextEx*>(m_pNeed[i]));
			}
		}
	}
}

void ManufactureUI_cl::initLine()
{
	if(!m_pPanel[1]) return;
	m_pLineScroll = dynamic_cast<ScrollView*>(Helper::seekWidgetByName(m_pPanel[1], "ScrollView"));
	m_pLineSlider = dynamic_cast<Slider*>(Helper::seekWidgetByName(m_pPanel[1], "Slider"));
	ImageView* child = dynamic_cast<ImageView*>(m_pLineScroll->getChildren().at(0));
	m_pLineChild = dynamic_cast<ImageView*>(child->clone());
	m_pLineChild->retain();
	m_lineStartPos = child->getPosition();
	m_lineDisX = m_pLineScroll->getChildren().at(1)->getPositionX() - m_lineStartPos.x;
	m_lineDisY = m_lineStartPos.y - m_pLineScroll->getChildren().at(2)->getPositionY();

	child = nullptr;
	m_pLineScroll->removeAllChildren();
	m_pLineSlider->setList(m_pLineScroll);
}

void ManufactureUI_cl::initBluePrint()
{
	if(!m_pPanel[2]) return;
	//操作按钮
	for (int i  = 0 ; i < 8; i++)
	{
		if(i < 6)
		m_pBlueBtn[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanel[2], FORMAT_TO_STRING("Button_sign%d", i)));
		else
		{
			m_pBlueBtn[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanel[2], FORMAT_TO_STRING("Button_%d", i-6)));
			m_pBlueBtn[i]->setButtonSpriteGray();
		}
		m_pBlueBtn[i]->setTag(i);
		m_pBlueBtn[i]->addTouchEventListener(this, toucheventselector(ManufactureUI_cl::blueCallback));
	}
	m_pBlueBtn[0]->setButtonShowType(Press_TYPE);
	m_pBlueScroll[0] = dynamic_cast<ScrollView*>(Helper::seekWidgetByName(m_pPanel[2], "ScrollView"));
	m_pBlueSlider[0] = dynamic_cast<Slider*>(Helper::seekWidgetByName(m_pPanel[2], "Slider"));
	
	if(m_pBlueSlider[0] && m_pBlueScroll[0])
	{
		for (int i = 1; i < 6; i++)
		{
			m_pBlueScroll[i] = dynamic_cast<ScrollView*>(m_pBlueScroll[0]->clone());
			m_pBlueScroll[i]->setPosition(m_pBlueScroll[0]->getPosition());
			m_pPanel[2]->addChild(m_pBlueScroll[i]);
			m_pBlueSlider[i] = dynamic_cast<Slider*>(m_pBlueSlider[0]->clone());
			m_pBlueSlider[i]->setPosition(m_pBlueSlider[0]->getPosition());
			m_pPanel[2]->addChild(m_pBlueSlider[i]);
			ScrollGrids_cl* scroll = ScrollGrids_cl::createWithOutData(emGrids_BagTuZi, BLUENINGRIDS, 2, m_pBlueScroll[i], this, false);
			scroll->registerFunc(bind(&ManufactureUI_cl::oneTouchCallback,this, std::placeholders::_1), ONE_TOUCH_EVENT);
			m_pBlueSlider[i]->setList(m_pBlueScroll[i]);
			m_pBlueScroll[i]->setEnabled(false);
			m_pBlueSlider[i]->setEnabled(false);
		}
		ScrollGrids_cl * scroll = ScrollGrids_cl::create(emGrids_BagTuZi, BLUENINGRIDS, 2, m_pBlueScroll[0], this, false);
		scroll->registerFunc(bind(&ManufactureUI_cl::oneTouchCallback,this, std::placeholders::_1), ONE_TOUCH_EVENT);
		m_pBlueSlider[0]->setList(m_pBlueScroll[0]);
		gGridsManager->addScrollUI(scroll, emGrids_BagTuZi);

	}
}

void ManufactureUI_cl::initMaterial()
{
	if(!m_pPanel[3]) return ;
	m_pMaterialScroll = dynamic_cast<ScrollView*>(Helper::seekWidgetByName(m_pPanel[3], "ScrollView"));
	m_pMaterialSlider = dynamic_cast<Slider*>(Helper::seekWidgetByName(m_pPanel[3], "Slider"));
	ScrollGrids_cl* scroll = ScrollGrids_cl::createWithOutData(emGrids_BagMaterial, 27, 3, m_pMaterialScroll, this, false);
	gGridsManager->addScrollUI(scroll, emGrids_BagMaterial);
	m_pMaterialSlider->setList(m_pMaterialScroll);

	for (int i = 0; i < 2; i++)
	{
		m_pMaterialBtn[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanel[3], FORMAT_TO_STRING("Button_%d", i)));
		m_pMaterialBtn[i]->setTag(i);
		m_pMaterialBtn[i]->setButtonSpriteGray();
		m_pMaterialBtn[i]->addTouchEventListener(this, toucheventselector(ManufactureUI_cl::materialCallback));
	}
}

void ManufactureUI_cl::changePanel()
{
	for (int i = 0; i < 4; i++)
	{
		m_pPanel[i]->setEnabled(false);
		m_pButton[i]->setButtonShowType(Normal_TYPE);
	}
	if(m_pPanel[m_pageIndex])
	{
		if(m_pageIndex == MainBtnTag_ManuFacture)
		{
			m_bSelectBlueprint = false;
			(dynamic_cast<Text*>(m_pNeed[0]))->setText(FORMAT_TO_STRING("%lld",gHero->GetMoney()));
			(dynamic_cast<Text*>(m_pNeed[1]))->setText(FORMAT_TO_STRING("%d",gHero->GetGold()));
		}
		else if(m_pageIndex == MainBtnTag_Material)
		{
			CItemGridArray* ret = gGridsManager->getGridsData(emGrids_BagMaterial);
			dynamic_cast<ScrollGrids_cl*>(m_pMaterialScroll)->resetData(ret);
		}
		m_pPanel[m_pageIndex]->setEnabled(true);
		m_pButton[m_pageIndex]->setButtonShowType(Press_TYPE);
	}
	changeBluePrintPanel();
}

void ManufactureUI_cl::changeBluePrintPanel()
{
	for (int i = 0; i < 6; i++)
	{
		m_pBlueSlider[i]->setEnabled(false);
		m_pBlueScroll[i]->setEnabled(false);
		m_pBlueBtn[i]->setButtonShowType(Normal_TYPE);
	}
	if(m_pBlueScroll[m_blueSign] && m_pBlueSlider[m_blueSign] && m_pageIndex == MainBtnTag_TUZHI)
	{
		CItemGridArray* ret  = getCurTypeBluePrint(m_blueSign);
		if(ret)
		dynamic_cast<ScrollGrids_cl*>(m_pBlueScroll[m_blueSign])->resetData(ret);
		m_pBlueSlider[m_blueSign]->setEnabled(true);
		m_pBlueScroll[m_blueSign]->setEnabled(true);
		m_pBlueBtn[m_blueSign]->setButtonShowType(Press_TYPE);
	}
}


void ManufactureUI_cl::setMaterialShow(int idx, string& str)
{
	if(str == "") return ;
	string id = str.substr(0, str.find(","));
	string num = str.substr(str.find(",")+1);
	ItemCfg* itemdata = ItemData.get(atoi(id.c_str()));
	if(itemdata)
	{
		m_pMaterialIcon[idx]->loadTexture(ICON_PATH_ITEM+itemdata->icon);
		m_pMaterialIcon[idx]->setVisible(true);
	}
	CItem* item = gGridsManager->findItemByDataID(emGrids_BagMaterial, atoi(id.c_str()));
	if(item)
	{
		m_pMaterialCount[idx]->setText(FORMAT_TO_STRING("%d/%d",item->getCount(), atoi(num.c_str())));
	}
	else
	{
		m_pMaterialCount[idx]->setText(FORMAT_TO_STRING("%d/%d",0, atoi(num.c_str())));
	}
	m_pMaterialCount[idx]->setVisible(true);
}

Widget* ManufactureUI_cl::createLineChildById(int id)
{
	ManufactureData_v& data = gDataPool->getManufactureData();
	if((int)data.size() <= id) return nullptr;
	if(id < (int)m_vLineWidget.size()) return m_vLineWidget.at(id);
	Widget* widget = m_pLineChild->clone();
	
	widget->addTouchEventListener(this, toucheventselector(ManufactureUI_cl::callbackShowBarTips));

	//进度条 
	LoadingBar* bar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(widget, "ProgressBar_63"));
	bar->setPercent(data[id]->percent);
	
	if(data[id]->leftTime == 0)
	{
		//完成按钮
		Button * btn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "Button_finish"));
		btn->setEnabled(true);
		btn->setTag(data[id]->serverData.itemDataId);
		btn->addTouchEventListener(this, toucheventselector(ManufactureUI_cl::getLineCallback));
		btn->setButtonSpriteGray();
		ImageView* fastimage = dynamic_cast<ImageView*>(Helper::seekWidgetByName(widget, "Image_fastneed"));
		fastimage->setVisible(false);
	}
	else
	{
		Button * btn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "Button_finish"));
		btn->setEnabled(false);
		btn->setTag(data[id]->serverData.itemDataId);
		btn->setButtonSpriteGray();
		btn->addTouchEventListener(this, toucheventselector(ManufactureUI_cl::getLineCallback));
		ImageView* fastimage = dynamic_cast<ImageView*>(Helper::seekWidgetByName(widget, "Image_fastneed"));
		fastimage->setVisible(true);
		//加速砖石
		Text*    gold = dynamic_cast<Text*>(Helper::seekWidgetByName(widget, "Label_fastneed"));
		gold->setText(INT_TO_STRING(data[id]->curGold));
	}


	//倒计时
	Text*    timerText = dynamic_cast<Text*>(Helper::seekWidgetByName(widget, "Label_time"));
	timerText->setText(SecondsToTime(data[id]->leftTime, 1));

	//制造名字
	Text*    TargetName = dynamic_cast<Text*>(Helper::seekWidgetByName(widget, "Label_targetname"));
	TargetName->setText(data[id]->targetname);
	//icon名字
	Text*    iconName = dynamic_cast<Text*>(Helper::seekWidgetByName(widget, "Label_iconname"));
	iconName->setText(data[id]->iconname);
	widget->retain();
	m_vLineWidget.push_back(widget);
	return widget;
}

void ManufactureUI_cl::freshLineById(int id)
{
	ManufactureData_v& data = gDataPool->getManufactureData();
	if(id >= (int)data.size()) return;
	if(id >= (int)m_vLineWidget.size()) 
	{
		openNewLineRet();
		return;
	}
	Widget* widget = m_vLineWidget.at(id);
	//进度条 
	LoadingBar* bar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(widget, "ProgressBar_63"));
	bar->setPercent(data[id]->percent);

	if(data[id]->leftTime == 0)
	{
		//完成按钮
		Button * btn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "Button_finish"));
		btn->setEnabled(true);
		ImageView* fastimage = dynamic_cast<ImageView*>(Helper::seekWidgetByName(widget, "Image_fastneed"));
		fastimage->setVisible(false);
	}
	else
	{
		Button * btn = dynamic_cast<Button*>(Helper::seekWidgetByName(widget, "Button_finish"));
		btn->setEnabled(false);
		ImageView* fastimage = dynamic_cast<ImageView*>(Helper::seekWidgetByName(widget, "Image_fastneed"));
		fastimage->setVisible(true);
		//加速砖石
		Text*    gold = dynamic_cast<Text*>(Helper::seekWidgetByName(widget, "Label_fastneed"));
		gold->setText(INT_TO_STRING(data[id]->curGold));
	}

	Text*    timerText = dynamic_cast<Text*>(Helper::seekWidgetByName(widget, "Label_time"));
	timerText->setText(SecondsToTime(data[id]->leftTime, 1));

}

void ManufactureUI_cl::update(float fd)
{
	ManufactureData_v& data = gDataPool->getManufactureData();
	for (size_t i = 0; i < data.size(); i++)
	{
		if(data[i]->leftTime > 0)
		{
			data[i]->leftTime = data[i]->serverData.remainSeconds - gGameManager->GetCurrTimeMS()/1000 + data[i]->startTime;
			data[i]->leftTime = data[i]->leftTime >0 ? data[i]->leftTime:0;
			if(data[i]->serverData.eliminateCdFlag == 0)
			{
				int gold = (data[i]->baseGold/data[i]->productTime * 3600)*(data[i]->leftTime/3600);
				data[i]->curGold = MAX(gold, data[i]->minGold);
			}
			data[i]->percent = (float)(data[i]->productTime-data[i]->leftTime)/data[i]->productTime * 100;
			freshLineById(i);
		}
		if(m_pFastTips)
		{
			m_pFastTips->setFastGold();
		}
	}
}

CItemGridArray* ManufactureUI_cl::getCurTypeBluePrint(int type)
{
	CItemGridArray* ret = nullptr;
	switch (type)
	{
	case BluePringSignTag_ALL:
		ret = gGridsManager->getGridsData(emGrids_BagTuZi);
		break;
	case BluePringSignTag_Weapon:
		{
			m_pBlueTypeArrary[0]->clearItemGridList();
			CItemGridArray* blue = gGridsManager->getGridsData(emGrids_BagTuZi);
			for (auto iter: blue->getItemGridsList())
			{
				if(iter->GetItem() && iter->GetItem()->getSubType() == SubType_TUZHI_WEAPON)
				{
					m_pBlueTypeArrary[0]->addItemToList(iter);
				}
			}
			ret = m_pBlueTypeArrary[0];
		}
		break;
	case BluePringSignTag_Armor:
		{
			{
				m_pBlueTypeArrary[0]->clearItemGridList();
				CItemGridArray* blue = gGridsManager->getGridsData(emGrids_BagTuZi);
				for (auto iter: blue->getItemGridsList())
				{
					if(iter->GetItem() && iter->GetItem()->getSubType() == SubType_TUZHI_AROMR)
					{
						m_pBlueTypeArrary[0]->addItemToList(iter);
					}
				}
				ret = m_pBlueTypeArrary[1];
			}
		}
		break;
	case BluePringSignTag_Relic:
		{
			m_pBlueTypeArrary[0]->clearItemGridList();
			CItemGridArray* blue = gGridsManager->getGridsData(emGrids_BagTuZi);
			for (auto iter: blue->getItemGridsList())
			{
				if(iter->GetItem() && iter->GetItem()->getSubType() == SubType_TUZHI_RELIC)
				{
					m_pBlueTypeArrary[0]->addItemToList(iter);
				}
			}
			ret = m_pBlueTypeArrary[2];
		}
		break;
	case BluePringSignTag_Pet:
		{
			m_pBlueTypeArrary[0]->clearItemGridList();
			CItemGridArray* blue = gGridsManager->getGridsData(emGrids_BagTuZi);
			for (auto iter: blue->getItemGridsList())
			{
				if(iter->GetItem() && iter->GetItem()->getSubType() == SubType_TUZHI_PET)
				{
					m_pBlueTypeArrary[0]->addItemToList(iter);
				}
			}
			ret = m_pBlueTypeArrary[3];
		}
		break;
	case BluePringSignTag_Other:
		{
			m_pBlueTypeArrary[0]->clearItemGridList();
			CItemGridArray* blue = gGridsManager->getGridsData(emGrids_BagTuZi);
			for (auto iter: blue->getItemGridsList())
			{
				if(iter->GetItem() && iter->GetItem()->getSubType() == SubType_TUZHI_OTHER)
				{
					m_pBlueTypeArrary[0]->addItemToList(iter);
				}
			}
			ret = m_pBlueTypeArrary[4];
		}
		break;
	default:
		break;
	}
	return ret;
}

void ManufactureUI_cl::pushBlueprintByID(int id)
{
	CItem * item = gGridsManager->findItemByDataID(emGrids_BagTuZi, id);
	pushBlueprintByItem(item);
}

void ManufactureUI_cl::pushBlueprintByItem(CItem* item)
{
	if(item)
	{
		m_blueprintID = item->getDataID();
		BluePrintCfg* data = BluePrintData.get(m_blueprintID);
		if(data)
		{
			setMaterialShow(0, data->material_1);
			setMaterialShow(1, data->material_2);
			setMaterialShow(2, data->material_3);
			setMaterialShow(3, data->material_4);
			setMaterialShow(4, data->material_5);
			setMaterialShow(5, data->material_6);

			ItemCfg* targetCfg = ItemData.get(data->item_id);
			for (int i = 2; i < 5; i++)
			{
				m_pNeed[i]->setVisible(true);
			}
			if(targetCfg)
			{
				(dynamic_cast<RichTextEx*>(m_pNeed[2]))->ParseAndLayout(FORMAT_TO_STRING(STR_MANUF_HAVETARGET, targetCfg->name.c_str(), 0));	
				Size size = (dynamic_cast<RichTextEx*>(m_pNeed[2]))->getVirtualRendererSize();
				(dynamic_cast<RichTextEx*>(m_pNeed[2]))->setPosition(Point((dynamic_cast<RichTextEx*>(m_pNeed[2]))->getPositionX() + size.width/2, (dynamic_cast<RichTextEx*>(m_pNeed[2]))->getPositionY()));
			}
			else
			{
				(dynamic_cast<RichTextEx*>(m_pNeed[2]))->ParseAndLayout(FORMAT_TO_STRING(STR_MANUF_HAVETARGET, "", 0));	
				Size size = (dynamic_cast<RichTextEx*>(m_pNeed[2]))->getVirtualRendererSize();
				(dynamic_cast<RichTextEx*>(m_pNeed[2]))->setPosition(Point((dynamic_cast<RichTextEx*>(m_pNeed[2]))->getPositionX() + size.width/2, (dynamic_cast<RichTextEx*>(m_pNeed[2]))->getPositionY()));
			}
			(dynamic_cast<RichTextEx*>(m_pNeed[3]))->ParseAndLayout(FORMAT_TO_STRING(STR_MANUF_NEEDTIME, data->time/3600));
			(dynamic_cast<RichTextEx*>(m_pNeed[4]))->ParseAndLayout(FORMAT_TO_STRING(STR_MANUF_NEEDGOLD, data->gold));

			Size size1 = (dynamic_cast<RichTextEx*>(m_pNeed[3]))->getVirtualRendererSize();
			(dynamic_cast<RichTextEx*>(m_pNeed[3]))->setPosition(Point((dynamic_cast<RichTextEx*>(m_pNeed[3]))->getPositionX() + size1.width/2, (dynamic_cast<RichTextEx*>(m_pNeed[3]))->getPositionY()));

			Size size2 = (dynamic_cast<RichTextEx*>(m_pNeed[4]))->getVirtualRendererSize();
			(dynamic_cast<RichTextEx*>(m_pNeed[4]))->setPosition(Point((dynamic_cast<RichTextEx*>(m_pNeed[4]))->getPositionX() + size2.width/2, (dynamic_cast<RichTextEx*>(m_pNeed[4]))->getPositionY()));
		}

	
	}
	m_pageIndex = MainBtnTag_ManuFacture;
	changePanel();
}


void ManufactureUI_cl::callback(Ref* _ref, TouchEventType touchevent)
{
	if(touchevent == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(_ref)->getTag();
		switch (tag)
		{
		case MainBtnTag_ManuFacture:
		case MainBtnTag_LINE:
		case MainBtnTag_TUZHI:
		case MainBtnTag_Material:
			if(!m_bSelectBlueprint && !m_bActionRet)
			{
				m_pageIndex = tag;
				changePanel();
			}
			else
			{
				m_pButton[MainBtnTag_TUZHI]->setButtonShowType(Press_TYPE);
			}
			break;
		case MainBtnTag_Close:
			if(!m_bActionRet && !m_bSelectBlueprint)
			gGameUILayer->close(this);
			else if(m_bSelectBlueprint)
			{
				m_pageIndex = MainBtnTag_ManuFacture;
				changePanel();
			}
			break;
		default:
			break;
		}
	}
}

void ManufactureUI_cl::manufactureMaterialCallback(Ref* _ref, TouchEventType touchevent)
{
	if(touchevent == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<ImageView*>(_ref)->getTag();
		
	}
}

void ManufactureUI_cl::manufactureOptionCallback(Ref* _ref, TouchEventType touchevent)
{
	if(touchevent == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Widget*>(_ref)->getTag();
		switch (tag)
		{
		case ManufactureOptionTag_PushTag:
			m_bSelectBlueprint = true;
			m_pageIndex = MainBtnTag_TUZHI;
			changePanel();
			break;
		case ManufactureOptionTag_StartTag:
			{
				if(m_blueprintID != -1)
				{
					pk::C2GS_New_Manufacture_Element cmd;
					cmd.itemDataId = m_blueprintID;
					cmd.Send(gNetSocket);
					m_bActionRet = true;
				}

			}
			break;
		default:
			break;
		}
	}
}

void ManufactureUI_cl::getLineCallback(Ref* _ref, TouchEventType touchevent)
{
	if(touchevent == TOUCH_EVENT_ENDED)
	{
		int tagdata = dynamic_cast<Button*>(_ref)->getTag();
		pk::C2GS_Gain_Item cmd;
		cmd.itemDataId = tagdata;
		cmd.Send(gNetSocket);
	}
}

void ManufactureUI_cl::blueCallback(Ref* _ref, TouchEventType touchevent)
{
	if(touchevent == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(_ref)->getTag();
		switch (tag)
		{
		case BluePringSignTag_ALL:
		case BluePringSignTag_Weapon:
		case BluePringSignTag_Armor:
		case BluePringSignTag_Relic:
		case BluePringSignTag_Pet:
		case BluePringSignTag_Other:
			m_blueSign = tag;
			changeBluePrintPanel();
			break;
		case BluePringSignTag_Sale:
			if(m_pBlueItem)
			{
				if(m_pCurBlueprint) m_pCurBlueprint->removeFromParent();
				m_pCurBlueprint = CGridIcon::create(m_pBlueItem,m_pBlueItem->getIndex(), emGrids_BagTuZi);
				m_pOptionBtn[0]->setEnabled(false);
				m_pPanel[0]->addChild(m_pCurBlueprint);
				m_pCurBlueprint->setPosition(m_pOptionBtn[0]->getPosition());
				m_pCurBlueprint->setTag(ManufactureOptionTag_PushTag);
				m_pCurBlueprint->addTouchEventListener(this, toucheventselector(ManufactureUI_cl::manufactureOptionCallback));
				m_bSelectBlueprint = false;
				pushBlueprintByItem(m_pBlueItem);
			}
			m_pBlueItem = nullptr;
			break;
		case BluePringSignTag_Buy:
			break;
		default:
			break;
		}
	}
}

void ManufactureUI_cl::materialCallback(Ref* _ref, TouchEventType touchevent)
{
	if(touchevent == TOUCH_EVENT_ENDED)
	{

	}
}

void ManufactureUI_cl::callbackShowBarTips(Ref* _ref, TouchEventType touchevent)
{
	if(touchevent == TOUCH_EVENT_ENDED)
	{
		int id = dynamic_cast<Widget*>(_ref)->getTag();
		m_pFastTips = FastTipsUI_cl::create(id);
		this->addChild(m_pFastTips);
	}
}

void ManufactureUI_cl::oneTouchCallback(CItem* item)
{
	if(item)
	{
		m_pBlueItem = item;
	}
}

void ManufactureUI_cl::startManufactureRet(int right)
{
	//
	if(right > 0)
	{
		m_bActionRet = false;
	}
	else
	{
		//动画事件
		m_bActionRet = false;
		for (int i = 0; i < 6; i++)
		{
			if(i >=2 && i < 5)
				m_pNeed[i]->setVisible(false);
			m_pMaterialIcon[i]->setVisible(false);
			m_pMaterialCount[i]->setVisible(false);
		}
		m_pOptionBtn[0]->setEnabled(true);
		m_pCurBlueprint->removeFromParent();
		m_pCurBlueprint = nullptr;
		openNewLineRet();
	}
}

void ManufactureUI_cl::openNewLineRet()
{
	ManufactureData_v& data = gDataPool->getManufactureData();
	//设置高度
	int height = ceil((int)data.size()/2);
	Point startpos = Point::ZERO;
	m_pLineScroll->getInnerContainer()->removeAllChildren();
	if(height > 3)
	{
		Size size = m_pLineScroll->getInnerContainer()->getSize();
		m_pLineScroll->getInnerContainer()->setSize(Size(size.width, m_lineDisY* height));
		startpos = Point(m_lineStartPos.x, m_lineDisY*height - m_lineDisY);
	}
	else
	{
		startpos = m_lineStartPos;
	}
	int  idx = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		Widget* widget = createLineChildById(i);
		if(widget)
		{
			widget->setPosition(Point(startpos.x + m_lineDisX * (i%2), startpos.y - m_lineDisY * (i/2)));
			widget->setTag(i);
			m_pLineScroll->getInnerContainer()->addChild(widget);
		}
	}
}

void ManufactureUI_cl::getLineRet(int dataid)
{
	int idx = 0;
	ManufactureData_v& data = gDataPool->getManufactureData();
	for (size_t i = 0; i < data.size(); i++)
	{
		if(data[i]->serverData.itemDataId == dataid)
		{
			remove(m_vLineWidget.begin(), m_vLineWidget.end(), m_vLineWidget[idx]);
			break;
		}
		idx += 1;
	}
	gDataPool->removeManuFactureData(dataid);
	openNewLineRet();
}

#include "SkyBookUI.h"
#include "GameScene/GameUILayer.h"
#include "MessageBoxUI.h"
#include "Net/NetDispatcher.h"

#define  ALLBAG_GRIDS                    64
#define  SINGBAG_GRIDS                   64

#define  INLAY_CHILD                     12          //镶嵌格子内节点TAG值
#define  REFINED_CHILD                   12          //祭炼格子内节点TAG值
#define  LONGTIMER                       200.f       //记录长按时间

#define  Syn_MAX                         4           //合成节点的最大值

enum CalcLayerBtn
{
	ZERO_TAG,
	ONE_TAG,
	TWO_TAG,
	THREE_TAG,
	FOUR_TAG,
	FIVE_TAG,
	SIX_TAG,
	SEVEN_TAG,
	EIGHT_TAG,
	NINE_TAG,
	MAX_TAG,
	RESET_TAG,
	CANCLE_TAG,
	ADMIN_TAG,
};

enum LayerType_em
{
	Relic_Layer_Type,                   //神器界面
	Weapon_Layer_Type,                  //武器界面
	Pet_Layer_Type,                     //宠物界面
	Refined_Layer_Type,                 //祭炼界面
	Synthetic_Layer_Type,               //合成界面
	Bag_Layer_Type,                     //背包界面

	Close_UI_Type,                      //关闭天书
};

//操作状态 针对打开标签背包
enum OptionStutas_em
{
	OptionStutas_Init,                  //初始值
	OptionStutas_Inlay,                 //镶嵌状态
	OptionStutas_Refined_UnSelect,      //祭炼未放入状态
	OptionStutas_Refined_Selected,      //祭炼放入状态
	OptionStutas_Synthetic,             //合成状态
	OptionStutas_Bag,                   //无标签背包
};

/*---------------------------------------------------------------------*/
/*                       镶嵌界面                                      */
/*---------------------------------------------------------------------*/

enum InlayOptionTag
{
	Unload_TAG,                        //卸下
	Capacity_TAG,                      //容量强化
	Hole_TAG,                          //孔位强化
};

/*---------------------------------------------------------------------*/
/*                       祭炼界面                                      */
/*---------------------------------------------------------------------*/

enum RefinedOptionTag
{
	Refined_TAG,                         //祭炼按钮
	RefinedPush_TAG,                     //放入
	RefinedCancel_TAG,                   //取消
};


/*---------------------------------------------------------------------*/
/*                       合成界面                                      */
/*---------------------------------------------------------------------*/

enum SyntheticOptionTag
{
	Synthetic_TAG,                      //合成按钮
	SyntheticPush_TAG,                  //放入
	SyntheticCancel_TAG,                //取消
};

/*---------------------------------------------------------------------*/
/*                       背包界面                                      */
/*---------------------------------------------------------------------*/

enum BagOptionTag
{
	Sign_Refined_TAG,                   //已镶嵌
	Sign_All_TAG,                       //全部
	Sign_Relic_TAG,                     //神器
	Sign_Weapon_TAG,                    //武器
	Sign_Pet_TAG,                       //宠物

	BagPush_TAG  = 0,                   //放入
	BagCancel_TAG,                      //取消
};

SkyBookCalcUI_cl::SkyBookCalcUI_cl():GameUI(IDU_SkyBookCalcUI, JsonFile_SkyBookCalcUI)
{
	m_count = 0;
}

SkyBookCalcUI_cl::~SkyBookCalcUI_cl()
{

}

bool SkyBookCalcUI_cl::onInit()
{
	if(!Layer::init()) return false;
	pUI = dynamic_cast<SkyBookUI_cl*>(gGameUILayer->getActiveUI(IDU_SkyBookUI));
	m_pText = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget, "Label"));
	m_pText->setText("0");
	//按钮
	//0-9 表示数字按钮 10 最大按钮 11 重置 12取消 13 确定
	for (int i = 0; i < 14; i++)
	{
		Button* btn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, FORMAT_TO_STRING("Button_%d", i)));
		btn->setTag(i);
		btn->addTouchEventListener(this, toucheventselector(SkyBookCalcUI_cl::callback));
	}
	return true;
}

void SkyBookCalcUI_cl::onOpen()
{
	m_count = 0;
	m_pText->setText("0");
	for(auto iter: pUI->m_vSelectMaterial)
	{
		if(iter.index == pUI->m_pBagSelectBook->getIndex())
		{
			m_count = iter.count;
			m_pText->setText("0");
			break;
		}
	}
}

void SkyBookCalcUI_cl::callback(Ref* pSender, TouchEventType touchtype)
{
	if(touchtype == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		switch (tag)
		{
		case ZERO_TAG:
		case ONE_TAG:
		case TWO_TAG:
		case THREE_TAG:
		case FOUR_TAG:
		case FIVE_TAG:
		case SIX_TAG:
		case SEVEN_TAG:
		case EIGHT_TAG:
		case NINE_TAG:
			{
				if(m_count == 0)
					m_count = tag;
				else
				{
					m_count = m_count*10 + tag;
					if(pUI && pUI->m_pBagSelectBook)
					m_count = m_count>pUI->m_pBagSelectBook->getCount()? pUI->m_pBagSelectBook->getCount():m_count;
				}
			}
			break;
		case MAX_TAG:
			{
				if(pUI)
				{
					m_count = pUI->m_pBagSelectBook->getCount();
				}
			}
			break;
		case RESET_TAG:
			m_count = 0;
			break;
		case CANCLE_TAG:
			m_count = 0;
			break;
		case ADMIN_TAG:
			{
				if(pUI && pUI->m_pBagSelectBook)
				{
					m_count = m_count>pUI->m_pBagSelectBook->getCount()? pUI->m_pBagSelectBook->getCount():m_count;
					if(pUI->m_CurOptionStutas == OptionStutas_Synthetic)  //合成界面
					{
						m_count = m_count > Syn_MAX?Syn_MAX:m_count;
						if(pUI->m_vSelectBook.size() >= 4) m_count = 0;
						else
						{
							m_count = m_count>Syn_MAX-(int)pUI->m_vSelectBook.size()?Syn_MAX-(int)pUI->m_vSelectBook.size():m_count;
						}
						//检测是否有相同的
						bool exist = false;
						int  cnt = 0; //计算原本选择的个数
						for (auto iter:pUI->m_vSelectBook)
						{
							if(iter == pUI->m_pBagSelectBook)
							{
								exist = true;
								cnt += 1;
							}
						}
						if(cnt > m_count && cnt < (int)pUI->m_vSelectBook.size())   //原本中多了
						{
							int idx = 0;
							for (auto iter = pUI->m_vSelectBook.begin(); iter != pUI->m_vSelectBook.end(), idx < cnt; iter++)
							{
								if((*iter) == pUI->m_pBagSelectBook)
								{
									iter = pUI->m_vSelectBook.erase(iter);
									idx += 1;
									exist = true;
								}
							}
						}
						else if(cnt < m_count)
						{
							for (int i = 0; i < m_count-cnt; i++)
							{
								pUI->m_vSelectBook.push_back(pUI->m_pBagSelectBook);
								exist = true;
							}
						}
						if(!exist)
						{
							for (int i = 0; i < m_count; i++)
							{
								pUI->m_vSelectBook.push_back(pUI->m_pBagSelectBook);
							}
						}
					}

					bool exist = false;
					if(pUI->m_vSelectMaterial.size() > 0)
					{
						for(auto iter: pUI->m_vSelectMaterial)
						{
							if(iter.index == pUI->m_pBagSelectBook->getIndex())
							{
								if(iter.count > m_count)
								{
									pUI->m_curTotalBook -= (iter.count - m_count);
								}
								else
								{
									pUI->m_curTotalBook += (m_count - iter.count);
								}
								iter.count = m_count;
								exist = true;
								break;
							}
						}
					}
					if(!exist)
					{
						pk::tian_shu_material material;
						material.count = m_count;
						material.index = pUI->m_pBagSelectBook->getIndex();
						pUI->m_vSelectMaterial.push_back(material);
						pUI->m_curTotalBook += m_count;
					}

				}
			}
			break;
		default:
			break;
		}
		m_pText->setText(INT_TO_STRING(m_count));
		if(tag == CANCLE_TAG || tag == ADMIN_TAG)
		{
			gGameUILayer->close(this);
		}
	}
}

SkyBookUI_cl::SkyBookUI_cl():GameUI(IDU_SkyBookUI, JsonFile_SkyBookUI)
	,m_isShowSign(false)
	,m_isOpened(false)
	,m_curIndex(0)
	,m_pCapacityText(nullptr)
	,m_pInlayList(nullptr)
	,m_pRefinedGrid(nullptr)
	,m_pRefinedBar(nullptr)
	,m_pRefinedTSName(nullptr)
	,m_pSyntheicName(nullptr)
	,m_pSyntheicList(nullptr)
	,m_pBagScroll(nullptr)
	,m_pBagSlider(nullptr)
	,m_pBagSelectName(nullptr)
	,m_pBagSelectList(nullptr)
	,m_curConfigIdx(0)
	,m_isCapacity(false)
	,m_isHole(false)
	,m_curSlot(-1)
	,m_curBagSignIdx(0)
	,m_pBagSelectBook(nullptr)
	,m_CurOptionStutas(OptionStutas_Init)
	,m_curTotalBook(0)
	,m_islongTouched(false)
	,m_pMoveBook(nullptr)
	,m_fLongTime(0.f)
	,m_isGiveUp(false)
	,m_curInsertId(-1)
	,m_totalCapacity(0)
	,m_curCapacity(0)
{
	m_vSelectBook.clear();
	m_vSelectMaterial.clear();
	
	for (int i = 0; i < 9; i++)
	{
		m_pInlayGrids[i] = nullptr;
		if(i < 2)
		{
			m_pRefinedLists[i]    = nullptr;
			m_pBagOptionBtn[i] = nullptr;
		}
		if(i < 3)
		{
			m_pInlayOpBtns[i] = nullptr;
			m_pConfigBtn[i]    = nullptr;
			m_pRefinedOpBtn[i]   = nullptr;
			m_pSyntheicOpBtn[i]   = nullptr;
		}
		if(i< 4)
		{
			m_pStarText[i]     = nullptr;
		}
		if(i< 5)
		{
			m_pSyntheicGrids[i] = nullptr;
			m_pBagSignBtn[i]    = nullptr;
			m_pBagSignScroll[i] = nullptr;
			m_pBagSignSlider[i] = nullptr;
		}
		if(i < 6)
		{
			m_pPanle[i] = nullptr;
			m_pButton[i] = nullptr;
		}
	}
}

SkyBookUI_cl::~SkyBookUI_cl()
{
	m_vSelectBook.clear();
}

bool SkyBookUI_cl::onInit()
{
	if(!m_pWidget) return false;
	for (int i = 0; i < 6; i++)
	{
		m_pButton[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, FORMAT_TO_STRING("Button_0_%d", i)));
		m_pButton[i]->setTag(i);
		m_pButton[i]->addTouchEventListener(this, toucheventselector(SkyBookUI_cl::callBack));
	}
	
	//获取对象指针
	initRefinedLayer();
	initInlayLayer();
	initSyntheticLayer();
	initBagLayer();

	//设置显示状态
	showBtnStatus();

	//关闭按钮
	Button*  pClosed = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, "Button_xx"));
	pClosed->setTag(Close_UI_Type);
	pClosed->addTouchEventListener(this, toucheventselector(SkyBookUI_cl::callBack));

	//初始化数据
	inlayConfigBtnChange();

	return true;
}

void SkyBookUI_cl::onOpen()
{
	for (int i = 0; i < 5; i++)
	{
		if(m_pBagSignSlider[i] && m_pBagSignScroll[i])
			m_pBagSignSlider[i]->setList(m_pBagSignScroll[i], Slider::ListType::SCROLLVIEW_TYPE);
	}
}

void SkyBookUI_cl::initInlayLayer()
{
	m_pPanle[0] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget, "Panel_xq"));
	if(!m_pPanle[0]) return ;

	//获取镶嵌格子指针
	for (int i = 0; i < 9; i++)
	{
		//获取配置按钮和操作按钮
		if(i < 3)
		{
			m_pConfigBtn[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanle[0], FORMAT_TO_STRING("Button_config_%d", i)));
			m_pConfigBtn[i]->setTag(i);
			m_pConfigBtn[i]->setButtonSpriteGray();
			m_pConfigBtn[i]->addTouchEventListener(this, toucheventselector(SkyBookUI_cl::inlayConfigCallback));

			m_pInlayOpBtns[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanle[0], FORMAT_TO_STRING("Button_xqop_%d", i)));
			m_pInlayOpBtns[i]->setTag(i);
			m_pInlayOpBtns[i]->setButtonSpriteGray();
			m_pInlayOpBtns[i]->addTouchEventListener(this, toucheventselector(SkyBookUI_cl::inlayOptionCallback));
		}
		m_pInlayGrids[i] = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pPanle[0], FORMAT_TO_STRING("grid_%d", i)));
		m_pInlayGrids[i]->addTouchEventListener(this, toucheventselector(SkyBookUI_cl::inlayGridCallback));
		m_pInlayGrids[i]->setTag(i);
	}

	m_pCapacityText = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pPanle[0], "Label_capacity"));
	m_pInlayList   = dynamic_cast<ListView*>(Helper::seekWidgetByName(m_pPanle[0], "ListView_xqattr"));
}

void SkyBookUI_cl::initRefinedLayer()
{
	m_pPanle[1] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget, "Panel_jl"));
	if(!m_pPanle[1]) return ;
	//要祭炼的格子指针
	m_pRefinedGrid = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pPanle[1], "grid_jl"));
	m_pRefinedGrid->setTouchEnabled(true);
	m_pRefinedGrid->addTouchEventListener(this, toucheventselector(SkyBookUI_cl::refinedGridCallback));

	//祭炼的进度条
	m_pRefinedBar  = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(m_pPanle[1], "ProgressBar_jl"));

	for (int i = 0; i < 4; i++)
	{
		//祭炼的星级标签   
		//左边文本0-1 0为初始星级 1为炼后星级
		//右边文本2-3 2为初始星级 3为炼后星级
		m_pStarText[i] = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pPanle[1],FORMAT_TO_STRING("Label_jlscore%d", i)));

		//祭炼的操作按钮    
		//0 为祭炼按钮 1为放入 2为取消
		if(i < 3)
		{
			m_pRefinedOpBtn[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanle[1], FORMAT_TO_STRING("Button_jl%d", i)));
			m_pRefinedOpBtn[i]->setTag(i);
			m_pRefinedOpBtn[i]->setButtonSpriteGray();
			m_pRefinedOpBtn[i]->addTouchEventListener(this, toucheventselector(SkyBookUI_cl::refinedOptionsCallback));
		}

		if(i < 2)
		{
			//祭炼属性列表
			//0 为对比属性列表
			//1 为材料列表
			m_pRefinedLists[i]  = dynamic_cast<ListView*>(Helper::seekWidgetByName(m_pPanle[1], FORMAT_TO_STRING("ListView_jl_%d", i)));
		}
	}


	//祭炼天书名字
	m_pRefinedTSName = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pPanle[1], "Label_jltianshutile"));
}

void SkyBookUI_cl::initSyntheticLayer()
{
	m_pPanle[2] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget, "Panel_hc"));
	if(!m_pPanle[2]) return ;

	//合成后的天书名字
	m_pSyntheicName = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pPanle[2], "Label_hctsname"));

	//
	m_pSyntheicList = dynamic_cast<ListView*>(Helper::seekWidgetByName(m_pPanle[2], "ListView_hc"));
	for (int i  = 0; i < 5; i++)
	{
		//合成
		//合成格子指针
		//0-3 为材料格子 5为目标格子
		m_pSyntheicGrids[i] = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pPanle[2], FORMAT_TO_STRING("Image_hc%d", i)));

		//合成的操作按钮    
		//0 为合成按钮 1为放入 2为取消
		if(i < 3)
		{
			m_pSyntheicOpBtn[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanle[2], FORMAT_TO_STRING("Button_hc%d", i)));
			m_pSyntheicOpBtn[i]->setTag(i);
			m_pSyntheicOpBtn[i]->setButtonSpriteGray();
			m_pSyntheicOpBtn[i]->addTouchEventListener(this, toucheventselector(SkyBookUI_cl::syntheicOptionCallback));
		}
	}
}

void SkyBookUI_cl::initBagLayer()
{
	m_pPanle[3] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget, "Panel_bb"));
	if(!m_pPanle[3]) return ;
	m_pPanle[4] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pPanle[3], "Panel_signbb"));
	m_pPanle[5] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pPanle[3], "Panel_all"));

	for (int i = 0; i < 5; i++)
	{
		//背包
		//背包标签界面
		//0已镶嵌 1全部 2神器 3武器 4 宠物  
		m_pBagSignBtn[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanle[4], FORMAT_TO_STRING("Button_11_%d", i)));
		m_pBagSignBtn[i]->setTag(i);
		m_pBagSignBtn[i]->addTouchEventListener(this, toucheventselector(SkyBookUI_cl::bagSignBtnCallback));

		//标签背包容器
		//0已镶嵌 1全部 2神器 3武器 4 宠物  
		if(!m_pBagSignScroll[0])
		{
			m_pBagSignScroll[0] = dynamic_cast<ScrollView*>(Helper::seekWidgetByName(m_pPanle[4], "ScrollView_sign"));
		}

		//标签背包滑块
		if(!m_pBagSignSlider[0])
		{
			m_pBagSignSlider[0] = dynamic_cast<Slider*>(Helper::seekWidgetByName(m_pPanle[4], "Slider_120"));
		}
		if(i >0 && m_pBagSignScroll[0] && m_pBagSignSlider[0])
		{
			m_pBagSignScroll[i] = dynamic_cast<ScrollView*>(m_pBagSignScroll[0]->clone());
			m_pBagSignSlider[i] = dynamic_cast<Slider*>(m_pBagSignSlider[0]->clone());
			m_pBagSignScroll[i]->setPosition(m_pBagSignScroll[0]->getPosition());
			m_pBagSignSlider[i]->setPosition(m_pBagSignSlider[0]->getPosition());
			m_pPanle[4]->addChild(m_pBagSignSlider[i]);
			m_pPanle[4]->addChild(m_pBagSignScroll[i]);
			ScrollGrids_cl* pScroll = ScrollGrids_cl::createWithOutData(emGrids_BagBook, SINGBAG_GRIDS, 2, m_pBagSignScroll[i], this, false);
			m_pBagSignSlider[i]->setList(m_pBagSignScroll[i], Slider::ListType::SCROLLVIEW_TYPE);
			pScroll->registerFunc(std::bind(&SkyBookUI_cl::signBagOneTouch, this, std::placeholders::_1),ONE_TOUCH_EVENT);
			pScroll->registerFunc(std::bind(&SkyBookUI_cl::signBagDoubleTouch,this, std::placeholders::_1),DOUBLE_TOUCH_EVENT);
		}
		if(i < 2)
		{
			//背包操作按钮
			m_pBagOptionBtn[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanle[3], FORMAT_TO_STRING("Button_bb_%d", i)));
			m_pBagOptionBtn[i]->setTag(i);
			m_pBagOptionBtn[i]->setButtonSpriteGray();
			m_pBagOptionBtn[i]->addTouchEventListener(this, toucheventselector(SkyBookUI_cl::bagOptionCallback));
		}
	}

	ScrollGrids_cl* pScroll = ScrollGrids_cl::createWithOutData(emGrids_BagBook, SINGBAG_GRIDS, 2, m_pBagSignScroll[0], this, false);
	m_pBagSignSlider[0]->setList(m_pBagSignScroll[0], Slider::ListType::SCROLLVIEW_TYPE);
	pScroll->registerFunc(std::bind(&SkyBookUI_cl::signBagOneTouch, this,std::placeholders::_1),ONE_TOUCH_EVENT);
	pScroll->registerFunc(std::bind(&SkyBookUI_cl::signBagDoubleTouch, this, std::placeholders::_1),DOUBLE_TOUCH_EVENT);


	//背包无标签界面
	m_pBagScroll = dynamic_cast<ScrollView*>(Helper::seekWidgetByName(m_pPanle[5], "ScrollView_all"));

	//背包无标签滑块
	m_pBagSlider = dynamic_cast<Slider*>(Helper::seekWidgetByName(m_pPanle[5], "Slider_129"));

	pScroll = ScrollGrids_cl::createWithOutData(emGrids_BagBook, ALLBAG_GRIDS, 2, m_pBagScroll, this, false);
	m_pBagSlider->setList(m_pBagScroll, Slider::ListType::SCROLLVIEW_TYPE);
	pScroll->registerFunc(std::bind(&SkyBookUI_cl::signBagOneTouch, this,std::placeholders::_1),ONE_TOUCH_EVENT);
	pScroll->registerFunc(std::bind(&SkyBookUI_cl::signBagDoubleTouch, this, std::placeholders::_1),DOUBLE_TOUCH_EVENT);
	gGridsManager->addScrollUI(pScroll, emGrids_BagBook);

	//背包选择天书名字
	m_pBagSelectName = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pPanle[3], "Label_bbtsname"));

	//背包选择天书属性列表
	m_pBagSelectList = dynamic_cast<ListView*>(Helper::seekWidgetByName(m_pPanle[3], "ListView_bb"));
	
}

void SkyBookUI_cl::inlayConfigBtnChange()
{
	for (int i = 0; i < 9; i++)
	{
		if(i < 3)
		{
			m_pConfigBtn[i]->setButtonShowType(Normal_TYPE);
		}
		m_pInlayGrids[i]->removeAllChildren();
	}
	m_pConfigBtn[m_curConfigIdx]->setButtonShowType(Press_TYPE);
	vector<pk::EquipTianshu> datalist;
	switch (m_curIndex)
	{
	case Relic_Layer_Type:datalist = gDataPool->getCurRelicConfig();break;
	case Weapon_Layer_Type:datalist = gDataPool->getCurWeaponConfig(); break;
	case Pet_Layer_Type:datalist = gDataPool->getCurPetConfig();break;
	default:
		break;
	}
	if(datalist.size() == 0 || (int)datalist.size()<= m_curConfigIdx) return;
	CItemGridArray* pGrids = gGridsManager->getGridsData(emGrids_BagBook);
	for (int i = 0; i < (int)datalist[m_curConfigIdx].tianShuList.size(); i++)
	{
		int solt = datalist[m_curConfigIdx].tianShuList[i].solt;
		int dataid = datalist[m_curConfigIdx].tianShuList[i].tianShuDataId;
		CItem* item = pGrids->GetItemByDataID(dataid);
		if(item)
		{
			CGridIcon* pGridIcon = CGridIcon::create(item,i,emGrids_BagBook);
			if(pGridIcon && m_pInlayGrids[solt])
			{
				m_pInlayGrids[solt]->removeAllChildren();
				pGridIcon->setTag(INLAY_CHILD);
				m_pInlayGrids[solt]->addChild(pGridIcon);
				pGridIcon->setShowNum(false);
				pGridIcon->setPosition(Point(m_pInlayGrids[solt]->getSize().width/2, m_pInlayGrids[solt]->getSize().height/2));
			}
		}
	}

	m_pInlayList->removeAllItems();
	freshCapacity();
}

void SkyBookUI_cl::freshInlaydData()
{
	switch (m_curIndex)
	{
	case Relic_Layer_Type:      //神器
		break;
	case Weapon_Layer_Type:     //武器
		{
			CItem* itemgrid = gDataPool->getHeroWeapon();
			if(itemgrid)
			{
				m_curConfigIdx = itemgrid->getCurItemInfo().tian_shu_use_index - 1;
			}
		}
		break;
	case Pet_Layer_Type:        //宠物
		break;
	default:
		break;
	}
}

void SkyBookUI_cl::freshCapacity()
{
	switch (m_curIndex)
	{
	case Relic_Layer_Type:
		break;
	case Weapon_Layer_Type:
		{
			const ItemInfo& info = gDataPool->getHeroWeapon()->getCurItemInfo();
			EquipBaseCfg*	data =  EquipBaseData.get(info.dataId);
			int capacity = 0;
			if(data)
			{
				capacity = data->base_capacity;
				if(info.content_lv == 1)
				{
					capacity = capacity * 2;
				}
				for (auto iter: info.soltStrengList)
				{
					if(iter.solt == 0)  //特殊孔位
					{
						CGridIcon* icon = dynamic_cast<CGridIcon*>(m_pInlayGrids[0]->getChildByTag(INLAY_CHILD));
						if(icon && icon->GetItem())
						{
							EquipBaseCfg*	itemdata =  EquipBaseData.get(icon->GetItem()->getItemInfo().dataId);
							if(itemdata)
							{
								if(iter.strengLv == 1) //已强化
								{
									capacity += itemdata->base_capacity * 2; 
								}
								else
								{
									capacity += itemdata->base_capacity;
								}
							}
						}
					}
				}
			}
			m_totalCapacity = capacity;
			//当前使用容量
			vector<pk::EquipTianshuDetail> tianshu;
			for (auto iter: info.tianShuList)
			{
				if(iter.index == (m_curConfigIdx+1))
				{
					tianshu = iter.tianShuList;
					break;
				}
			}
			int tempCapacity = 0;
			for (auto iter: tianshu)
			{
				EquipBaseCfg*	itemdata =  EquipBaseData.get(iter.tianShuDataId);
				if(itemdata)
				{
					int capacity1 = itemdata->base_capacity;
					for (auto slotIter: info.soltStrengList)
					{
						if(slotIter.solt == iter.solt && slotIter.strengLv == 1)
						{
							capacity1 = itemdata->base_capacity/2;
						}
					}

					tempCapacity += capacity1;
				}
			}
			m_curCapacity = tempCapacity;
		}
		break;
	case Pet_Layer_Type:
		break;
	default:
		break;
	}

	m_pCapacityText->setText(FORMAT_TO_STRING("%d/%d", m_curCapacity, m_totalCapacity));
}

void SkyBookUI_cl::showLayerByIndex()
{
	for (int i = 0; i < 4; i++)
	{
		m_pPanle[i]->setEnabled(false);
	}
	if(m_curIndex <= Pet_Layer_Type)
	{
		m_pPanle[0]->setEnabled(true);
	}
	else if(m_curIndex == Bag_Layer_Type)
	{
		m_pPanle[m_curIndex-Pet_Layer_Type]->setEnabled(true);
		m_pPanle[4]->setEnabled(false);
		m_pPanle[5]->setEnabled(false);
		if(m_isShowSign)
		{
			m_pPanle[4]->setEnabled(true);
		}
		else  //没有标签
		{
			if(m_lastIndex <= Pet_Layer_Type)  //弹出对应的镶嵌天书
			{
				DataPool_cl::ShowConditions_st st;
				st.IsSubType = true;
				st.IsCurInlay = true;
				st._type = (DataPool_cl::SignBook)(m_lastIndex + 1);
				dynamic_cast<ScrollGrids_cl*>(m_pBagScroll)->resetData(gDataPool->saparateDataFromBag(st));
			}
			else
			{
				dynamic_cast<ScrollGrids_cl*>(m_pBagScroll)->resetData(gGridsManager->getGridsData(emGrids_BagBook));
			}
			m_pPanle[5]->setEnabled(true);
		}
	}
	else
	{
		m_pPanle[m_curIndex-Pet_Layer_Type]->setEnabled(true);
	}
}

void SkyBookUI_cl::showBtnStatus()
{
	for (int i = 0; i < 6; i++)
	{
		m_pButton[i]->setButtonShowType(Normal_TYPE);
	}
	if(m_pButton[m_curIndex])
	{
		m_pButton[m_curIndex]->setButtonShowType(Press_TYPE);
	}
	showLayerByIndex();
}


void SkyBookUI_cl::checkInsertRectOther()
{
	Rect moveRect = Rect(m_pMoveBook->getPositionX() - m_pMoveBook->getSize().width/2, 
						 m_pMoveBook->getPositionY() - m_pMoveBook->getSize().height/2,
						 m_pMoveBook->getSize().width,
						 m_pMoveBook->getSize().height);
	for (int i = 1; i < 9; i++)
	{
		if(m_curSlot != i)
		{
			Rect rect = m_pInlayGrids[i]->getBoundingBox();
			if(rect.intersectsRect(moveRect))
			{
				m_curInsertId = i;
				return ;
			}
		}
	}
}

void SkyBookUI_cl::callBack( Ref * pSender, TouchEventType touchtype )
{
	if(touchtype == TOUCH_EVENT_ENDED)
	{
		m_CurOptionStutas = OptionStutas_Init;
		m_vSelectMaterial.clear();
		m_vSelectBook.clear();
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		if(tag != Close_UI_Type)
		{
			m_curIndex = tag;
			m_lastIndex = m_curIndex;
			showBtnStatus();
		}
		switch (tag)
		{
		case Relic_Layer_Type:
		case Weapon_Layer_Type:
		case Pet_Layer_Type:
			m_curSlot = -1;  //选择孔位初始化
			freshInlaydData();
			inlayConfigBtnChange();
			break;
		case Refined_Layer_Type:
			break;
		case Synthetic_Layer_Type:
			break;
		case Bag_Layer_Type:
			m_CurOptionStutas = OptionStutas_Bag;
			break;
		case Close_UI_Type:
			gGameUILayer->close(this);
			break;
		default:
			break;
		}
	}
}

void SkyBookUI_cl::inlayGridCallback( Ref* pSender, TouchEventType touchtype )
{
	if(touchtype == TOUCH_EVENT_BEGAN)
	{
		if(m_fLongTime == 0)
		{
			this->schedule(schedule_selector(SkyBookUI_cl::updateLongTimer));
		}
	}
	else if(touchtype == TOUCH_EVENT_MOVED)
	{
		if(m_pMoveBook && m_islongTouched)
		{
			m_pMoveBook->setPosition(m_pInlayGrids[m_curSlot]->getTouchMovePos());
			checkInsertRectOther();
		}
	}
	else if(touchtype == TOUCH_EVENT_ENDED)
	{
		ImageView* grid = dynamic_cast<ImageView*>(pSender);
		int tag = grid->getTag();
		m_curSlot = tag;
		if(m_isHole && m_curSlot != -1 && m_curIndex <= Pet_Layer_Type) //开启孔位强化
		{
			pk::C2GS_TianShuEquipSoltLvUp_Req cmd;
			cmd.solt = m_curSlot;
			cmd.type = m_curIndex;
			cmd.Send(gNetSocket);
		}
		if(m_isGiveUp && m_pInlayGrids[m_curSlot]->getChildrenCount()!=0 && m_curIndex <= Pet_Layer_Type)  //卸下操作
		{
			pk::C2GS_TianShuTakeOff_Req cmd;
			cmd.index = m_curConfigIdx + 1;
			cmd.solt = m_curSlot;
			cmd.type = m_curIndex;
			cmd.Send(gNetSocket);
		}
		else     //镶嵌
		{
			switch (m_curIndex)
			{
			case Relic_Layer_Type:if(!gHero->GetGodDeviceManager().GetIsDressGodPtr())return; break;
			case Weapon_Layer_Type:if(!gDataPool->getHeroWeapon())return;break;
			case Pet_Layer_Type:return;
			default:
				break;
			}

			if(grid->getChildrenCount() == 0)  //当前没有镶嵌
			{
				m_CurOptionStutas = OptionStutas_Inlay;
				setMianBtn(false);
			}
			else
			{
				//TODO:改变未选择的状态格子
			}
		}

		if(m_fLongTime > 0.f)
		{
			this->unschedule(schedule_selector(SkyBookUI_cl::updateLongTimer));
			m_fLongTime = 0.f;
		}
	}
	else if(touchtype == TOUCH_EVENT_CANCELED)
	{
		if(m_islongTouched)
		{
			m_islongTouched = false;
			if(m_curInsertId != m_curSlot) //当前格子不相等
			{
				pk::GS2C_TianShuChangeSolt_Req cmd;
				cmd.index = dynamic_cast<CGridIcon*>(m_pInlayGrids[m_curSlot]->getChildByTag(INLAY_CHILD))->GetItem()->getCurItemInfo().index;
				cmd.solt = m_curSlot;
				cmd.newsolt = m_curInsertId;
				cmd.type = m_curIndex;
				cmd.Send(gNetSocket);
			}
			else
			{
				m_pInlayGrids[m_curSlot]->getChildByTag(INLAY_CHILD)->setVisible(true);
			}
		}
		if(m_fLongTime > 0.f)
		{
			this->unschedule(schedule_selector(SkyBookUI_cl::updateLongTimer));
			m_fLongTime = 0.f;
		}
	}
}

void SkyBookUI_cl::inlayOptionCallback( Ref* pSender, TouchEventType touchtype )
{
	if(touchtype == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		switch (tag)
		{
		case Unload_TAG:
			{
				m_isGiveUp = true;
			}
			break;
		case Capacity_TAG:
			{
				if(m_curSlot != -1 && m_curIndex <= Pet_Layer_Type)
				{
					pk::C2GS_TianShuEquipContentLvUp_Req cmd;
					cmd.type = m_curIndex;
					cmd.Send(gNetSocket);
				}
			}
			break;
		case Hole_TAG:
			{
				m_isHole = true;
			}
			break;
		default:
			break;
		}
	}
}

void SkyBookUI_cl::inlayConfigCallback( Ref* pSender, TouchEventType touchtype )
{
	if(touchtype == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		pk::GS2C_TianShuChangeIndex_Req cmd;
		cmd.index = tag + 1;
		cmd.type = m_curIndex;
		cmd.Send(gNetSocket);
	}
}

void SkyBookUI_cl::refinedOptionsCallback( Ref* pSender, TouchEventType touchtype )
{
	if(touchtype == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		switch (tag)
		{
		case Refined_TAG:
			sendRefinedMsg();
			break;
		case RefinedPush_TAG:
			{
				if(m_pRefinedGrid->getChildrenCount() == 0) //没有节点
				{
					m_CurOptionStutas = OptionStutas_Refined_UnSelect;
				}
				else
				{
					m_CurOptionStutas = OptionStutas_Refined_Selected;
				}
				setMianBtn(true);
			}
			break;
		case RefinedCancel_TAG:
			break;
		default:
			break;
		}
	}
}

void SkyBookUI_cl::refinedGridCallback(Ref* pSender, TouchEventType touchtype)
{
	if(touchtype == TOUCH_EVENT_ENDED)
	{
		if(m_pRefinedGrid->getChildrenCount() == 0) //没有节点
		{
			m_CurOptionStutas = OptionStutas_Refined_UnSelect;
		}
		else
		{
			m_CurOptionStutas = OptionStutas_Refined_Selected;
		}
		setMianBtn(true);
	}
}

void SkyBookUI_cl::syntheicOptionCallback( Ref* pSender, TouchEventType touchtype )
{
	if(touchtype == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		switch (tag)
		{
		case Synthetic_TAG:
			{
				pk::C2GS_TianShuCompose_Req cmd;
				cmd.materialList = m_vSelectMaterial;
				cmd.Send(gNetSocket);
			}
			break;
		case SyntheticPush_TAG:
			m_CurOptionStutas = OptionStutas_Synthetic;
			setMianBtn(true);
			break;
		case SyntheticCancel_TAG:
			break;
		default:
			break;
		}
	}
}

void SkyBookUI_cl::bagSignBtnCallback( Ref* pSender, TouchEventType touchtype )
{
	if(touchtype == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		switch (tag)
		{
		case Sign_Refined_TAG:
			break;
		case Sign_All_TAG:
			break;
		case Sign_Relic_TAG:
			break;
		case Sign_Weapon_TAG:
			break;
		case Sign_Pet_TAG:
			break;
		default:
			break;
		}
		m_curBagSignIdx = tag;
		showBagLayerBySign();
	}
}

void SkyBookUI_cl::bagOptionCallback( Ref* pSender, TouchEventType touchtype )
{
	if(touchtype == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		switch (tag)
		{
		case BagPush_TAG:
			{
				if(m_lastIndex <= Pet_Layer_Type)  //镶嵌
				{
					sendInlayMsg();
				}
				else if(m_lastIndex == Refined_Layer_Type)  //祭炼放入
				{
					if(m_pRefinedGrid->getChildrenCount() == 0)
					{
						m_pRefinedGrid->removeAllChildren();
						CGridIcon* pGridIcon = CGridIcon::create(m_pBagSelectBook,m_pBagSelectBook->getIndex(),emGrids_BagBook);
						if (pGridIcon)
						{
							pGridIcon->setTag(REFINED_CHILD);
							m_pRefinedGrid->addChild(pGridIcon);
							pGridIcon->setPosition(Point(m_pRefinedGrid->getSize().width/2,m_pRefinedGrid->getSize().height/2));		
						}
					}else
					{
						m_pRefinedLists[1]->removeAllItems();
						for (size_t i  = 0; i < m_vSelectMaterial.size(); i++)
						{
							Widget * materialchild = gCtrlAllocator->LoadCtrl("Panel_jlsxChild1"); 
							Text* name = dynamic_cast<Text*>(materialchild->getChildByName("Label_name"));
							Text* num = dynamic_cast<Text*>(materialchild->getChildByName("Label_val"));
							CItem* item = gGridsManager->getGirdItem(emGrids_BagBook,m_vSelectMaterial[i].index);
							name->setText(item->getItemData()->name);
							num->setText(INT_TO_STRING(m_vSelectMaterial[i].count));
							m_pRefinedLists[i]->pushBackCustomItem(materialchild);
						}
					}
				}
				else if(m_lastIndex == Synthetic_Layer_Type) //合成放入
				{
					if(m_curTotalBook > Syn_MAX) //检测是否超出最大
					{
						CMessageBoxUI::Show(CMessageBoxUI::MBM_OK, "", nullptr, STR_MESSAGEBOX_COMFIRM.c_str(), STR_MESSAGEBOX_CANCEL.c_str());
					}
					else
					{
						for (int i = 0; i < (int)m_vSelectBook.size(); i++)
						{
							m_pSyntheicGrids[i]->removeAllChildren();
							CGridIcon* pGridIcon = CGridIcon::create(m_vSelectBook[i],m_vSelectBook[i]->getIndex(),emGrids_BagBook);
							if (pGridIcon)
							{
								m_pSyntheicGrids[i]->addChild(pGridIcon);
								pGridIcon->setPosition(Point(m_pSyntheicGrids[i]->getSize().width/2,m_pSyntheicGrids[i]->getSize().height/2));		
							}

						}
					}

				}
				setMianBtn(false);
			}
			break;
		case BagCancel_TAG:
			setMianBtn(false);
			break;
		default:
			break;
		}
	}
}

void SkyBookUI_cl::setMianBtn( bool val )
{
	m_isOpened = !m_isOpened;
	if(val)
	{
		m_isShowSign = val;
		if(m_isOpened)
		{
			m_lastIndex = m_curIndex;
			m_curIndex = Bag_Layer_Type;
		}
	}
	else
	{
		m_isShowSign = val;
		if(!m_isOpened)
		m_curIndex = m_lastIndex;
		else
		{
			m_lastIndex = m_curIndex;
			m_curIndex = Bag_Layer_Type;
		}
	}
	showLayerByIndex();
	for (int i = 0; i < 6;i++)
	{
		if(m_isOpened)
		{
			m_pButton[i]->setButtonShowType(Disable_TYPE);
		}
		else
		{
			m_pButton[i]->setButtonShowType(Normal_TYPE);
		}
	}
	if(!m_isOpened)
		m_pButton[m_curIndex]->setButtonShowType(Press_TYPE);
	else if(val)
	{
		showBagLayerBySign();
	}

	// 设置按钮状态标志
	if(m_lastIndex <= Pet_Layer_Type)
	m_pBagOptionBtn[0]->setTitleText(STR_Btn_Text_Inlay);
	else
	{
		m_pBagOptionBtn[0]->setTitleText(STR_Btn_Text_Push);
	}
}

int SkyBookUI_cl::getSignBagType(int param)
{
	//返回标签背包类型
	//param 0 是表示：已镶嵌、全部、神器、武器、宠物
	//      1 是表示：全部、神器、武器、宠物、材料
	if(param == 0)
	{
		switch (m_curBagSignIdx)
		{
		case 0:return DataPool_cl::SignBook_InlayedBook;
		case 1:return DataPool_cl::SingBook_All;
		case 2:return DataPool_cl::SignBook_RelicBook;
		case 3:return DataPool_cl::SignBook_WeaponBook;
		case 4:return DataPool_cl::SignBook_PetBook;
		default:
			break;
		}
	}
	else
	{
		switch (m_curBagSignIdx)
		{
		case 0:return DataPool_cl::SingBook_All;
		case 1:return DataPool_cl::SignBook_RelicBook;
		case 2:return DataPool_cl::SignBook_WeaponBook;
		case 3:return DataPool_cl::SignBook_PetBook;
		case 4:return DataPool_cl::SignBook_MaterialBook;
		default:
			break;
		}
	}
	return -1;
}

void SkyBookUI_cl::showBagLayerBySign()
{
	//祭炼：
	//a. 祭炼格子没有天书 显示列表为
	//已镶嵌、全部、神器、武器、宠物
	//b. 祭炼格子有天书  显示列表为
	//全部、神器、武器、宠物、材料

	//合成：
	//显示列表为
	//全部、神器、武器、宠物、材料
	DataPool_cl::ShowConditions_st st;
	string str[5] = {}; 
	if(m_lastIndex == Refined_Layer_Type)
	{
		if(m_pRefinedGrid->getChildByTag(REFINED_CHILD))
		{
			st._type = (DataPool_cl::SignBook)getSignBagType(1);
			st.IsShowUp = true;
			st.IsCurInlay = true;
			st.IsSubType = true;
			str[0] = STR_TS_BTN_ALL;
			str[1] = STR_TS_BTN_RELIC;
			str[2] = STR_TS_BTN_WEAPON;
			str[3] = STR_TS_BTN_PET;
			str[4] = STR_TS_BTN_MATERIAL;
		}
		else
		{
			st._type = (DataPool_cl::SignBook)getSignBagType(0);
			st.IsSubType = true;
			str[0] = STR_TS_BTN_INLAYED;
			str[1] = STR_TS_BTN_ALL;
			str[2] = STR_TS_BTN_RELIC;
			str[3] = STR_TS_BTN_WEAPON;
			str[4] = STR_TS_BTN_PET;
		}
	}
	else if(m_lastIndex == Synthetic_Layer_Type)
	{
		st._type = (DataPool_cl::SignBook)getSignBagType(1);
		st.IsCurInlay = true;
		st.IsOtherInlay = true;
		st.IsShowUp = true;
		st.IsSubType = true;
		st.exp      = true;
		str[0] = STR_TS_BTN_ALL;
		str[1] = STR_TS_BTN_RELIC;
		str[2] = STR_TS_BTN_WEAPON;
		str[3] = STR_TS_BTN_PET;
		str[4] = STR_TS_BTN_MATERIAL;
	}

	for (int i = 0; i < 5; i++)
	{
		m_pBagSignBtn[i]->setButtonShowType(Normal_TYPE);
		m_pBagSignSlider[i]->setEnabled(false);
		m_pBagSignScroll[i]->setEnabled(false);
		m_pBagSignBtn[i]->setTitleText(str[i]);
	}
	if(m_pBagSignScroll[m_curBagSignIdx] && m_pBagSignSlider[m_curBagSignIdx])
	{
		m_pBagSignScroll[m_curBagSignIdx]->setEnabled(true);
		m_pBagSignSlider[m_curBagSignIdx]->setEnabled(true);
		m_pBagSignBtn[m_curBagSignIdx]->setButtonShowType(Press_TYPE);
		dynamic_cast<ScrollGrids_cl*>(m_pBagSignScroll[m_curBagSignIdx])->resetData(gDataPool->saparateDataFromBag(st));
	}
}

void SkyBookUI_cl::signBagOneTouch( CItem* item )
{
	CCLOG("signBagOneTouch");
	if(!item) return ;
	m_pBagSelectBook = item;
	//读取item信息
	m_pBagSelectName->setText(item->getItemData()->name);

	//背包选择天书属性列表
	m_pBagSelectList->removeAllItems();
	switch (m_CurOptionStutas)
	{
	case OptionStutas_Init:
		m_pBagSelectBook = nullptr;
		break;
	case OptionStutas_Inlay:
		break;
	case OptionStutas_Refined_UnSelect:
		m_pBagSelectBook = item;
		break;
	case OptionStutas_Refined_Selected:
		gGameUILayer->open(IDU_SkyBookCalcUI);
		break;
	case OptionStutas_Synthetic:
		gGameUILayer->open(IDU_SkyBookCalcUI);
		break;
	case OptionStutas_Bag:
		m_vSelectBook.push_back(item);
		break;
	default:
		break;
	}
}

void SkyBookUI_cl::signBagDoubleTouch( CItem* item )
{
	CCLOG("signBagDoubleTouch");
	if(!item) return ;
	m_pBagSelectBook = item;
	if (m_curIndex <= Pet_Layer_Type)
	{
		CGridIcon* pGridIcon = CGridIcon::create(item,item->getIndex(),emGrids_BagBook);
		if (pGridIcon)
		{
			m_pInlayGrids[m_curSlot]->addChild(pGridIcon);
			pGridIcon->setTag(INLAY_CHILD);
			pGridIcon->setShowNum(false);
			pGridIcon->setPosition(Point(m_pInlayGrids[m_curSlot]->getSize().width/2,m_pInlayGrids[m_curSlot]->getSize().height/2));		
		}
		sendInlayMsg();
	}
}

void SkyBookUI_cl::sendInlayMsg()
{
	if(!m_pBagSelectBook) return;
	pk::C2GS_TianShuSet_Req cmd;
	cmd.solt = m_curSlot;
	cmd.index = m_curConfigIdx + 1;
	cmd.bag_index = m_pBagSelectBook->getIndex();
	cmd.type = m_lastIndex;
	cmd.Send(gNetSocket);
}

void SkyBookUI_cl::sendRefinedMsg()
{
	if(m_pRefinedGrid->getChildrenCount() == 0)
	{
		CMessageBoxUI::Show(CMessageBoxUI::MBM_OK, STR_Text_RefinedBook, 
			nullptr,
			STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
			this,NULL,CMessageBoxUI::Scene_Game);
		return ;
	}
	if((int)m_vSelectMaterial.size() == 0)
	{
		CMessageBoxUI::Show(CMessageBoxUI::MBM_OK, STR_Text_RefinedBook, 
			nullptr,
			STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
			this,NULL,CMessageBoxUI::Scene_Game);
		return;
	}
	pk::C2GS_TianShuLvUp_Req cmd;
	CGridIcon* pgridicon = dynamic_cast<CGridIcon*>(m_pRefinedGrid->getChildByTag(REFINED_CHILD));
	if(!pgridicon) return;
	cmd.index = pgridicon->GetItem()->getIndex();
	cmd.materialList =  m_vSelectMaterial;
	cmd.Send(gNetSocket);
}


void SkyBookUI_cl::updateChangeConfigRet(pk::C2GS_TianShuChangeIndex_Ret* value)
{
	if(!value) return ;
	if(value->retCode == 1)//切换配置成功
	{
		m_curConfigIdx = value->index - 1;   //服务器是从1开始的,本地配置从0开始
		inlayConfigBtnChange();
	}
	else
	{

	}

}

void SkyBookUI_cl::updateChangeHoleRet(pk::C2GS_TianShuChangeSolt_Ret* value)
{
	if(!value) return;
	if(m_pInlayGrids[m_curInsertId]->getChildByTag(INLAY_CHILD)) //目标格子有
	{
		CGridIcon* gridIcon1 = dynamic_cast<CGridIcon*>(m_pInlayGrids[m_curSlot]->getChildByTag(INLAY_CHILD));
		CGridIcon* gridIcon2 = dynamic_cast<CGridIcon*>(m_pInlayGrids[m_curInsertId]->getChildByTag(INLAY_CHILD));
		CItem* item1 = gridIcon1->GetItem();
		CItem* item2 = gridIcon2->GetItem();
		if(item2 && item1)
		{
			vector<pk::EquipTianshuDetail> data;
			switch (m_curIndex)
			{
			case Relic_Layer_Type:
				break;
			case Weapon_Layer_Type:
				data = gDataPool->getHeroWeapon()->getItemInfo().tianShuList[m_curConfigIdx].tianShuList;
				break;
			case Pet_Layer_Type:
				break;
			default:
				break;
			}
			for (auto iter: data)
			{
				if(iter.solt == m_curSlot)
				{
					iter.solt = m_curInsertId;
				}
				else if(iter.solt == m_curInsertId)
				{
					iter.solt = m_curSlot;
				}
			}
			gridIcon1 = CGridIcon::create(item1, item1->getItemInfo().index, emGrids_BagBook);
			gridIcon2 = CGridIcon::create(item2, item2->getItemInfo().index, emGrids_BagBook);
			m_pInlayGrids[m_curSlot]->removeAllChildren();
			m_pInlayGrids[m_curInsertId]->removeAllChildren();
			if(gridIcon1&& gridIcon2)
			{
				m_pInlayGrids[m_curInsertId]->addChild(gridIcon1);
				gridIcon1->setTag(INLAY_CHILD);
				gridIcon1->setShowNum(false);
				gridIcon1->setPosition(Point(m_pInlayGrids[m_curInsertId]->getSize().width/2, m_pInlayGrids[m_curInsertId]->getSize().height/2));

				m_pInlayGrids[m_curSlot]->addChild(gridIcon2);
				gridIcon2->setTag(INLAY_CHILD);
				gridIcon2->setShowNum(false);
				gridIcon2->setPosition(Point(m_pInlayGrids[m_curSlot]->getSize().width/2, m_pInlayGrids[m_curSlot]->getSize().height/2));
			}
		}
	}
	else
	{
		CGridIcon* gridIcon1 = dynamic_cast<CGridIcon*>(m_pInlayGrids[m_curSlot]->getChildByTag(INLAY_CHILD));
		vector<pk::EquipTianshuDetail> data;
		switch (m_curIndex)
		{
		case Relic_Layer_Type:
			break;
		case Weapon_Layer_Type:
			data = gDataPool->getHeroWeapon()->getItemInfo().tianShuList[m_curConfigIdx].tianShuList;
			break;
		case Pet_Layer_Type:
			break;
		default:
			break;
		}
		for (auto iter: data)
		{
			if(iter.solt == m_curSlot)
			{
				iter.solt = m_curInsertId;
				return;
			}
		}
		CGridIcon* girdIcon2 = CGridIcon::create(gridIcon1->GetItem(), gridIcon1->GetItem()->getItemInfo().index, emGrids_BagBook);
		m_pInlayGrids[m_curSlot]->removeAllChildren();
		if(girdIcon2)
		{
			m_pInlayGrids[m_curInsertId]->addChild(girdIcon2);
			girdIcon2->setTag(INLAY_CHILD);
			girdIcon2->setShowNum(false);
			girdIcon2->setPosition(Point(m_pInlayGrids[m_curInsertId]->getSize().width/2, m_pInlayGrids[m_curInsertId]->getSize().height/2));
		}
		
	}
	m_curInsertId = -1;
}

void SkyBookUI_cl::upgradeSkyBook( int8 lv, int16 exp )
{
	m_pStarText[0]->setText(FORMAT_TO_STRING(STR_Text_Star, lv));
	m_pStarText[1]->setText(FORMAT_TO_STRING(STR_Text_Star, (lv+1)));
	m_vSelectMaterial.clear();
}

void SkyBookUI_cl::showNewSkyBook( int16 dataid )
{
	//显示新的天书
	CItem* item = gGridsManager->findItemByDataID(emGrids_BagBook, dataid);
	if(item)
	{
		CGridIcon* pGridIcon = CGridIcon::create(item,item->getIndex(),emGrids_BagBook);
		if (pGridIcon)
		{
			m_pSyntheicGrids[5]->addChild(pGridIcon);
			pGridIcon->setPosition(Point(m_pSyntheicGrids[5]->getSize().width/2,m_pSyntheicGrids[5]->getSize().height/2));		
		}
	}

}

void SkyBookUI_cl::updateCapacity( int8 _type )
{
	switch (m_curIndex)
	{
	case Relic_Layer_Type:
		break;
	case Weapon_Layer_Type:
		gDataPool->getHeroWeapon()->getItemInfo().content_lv = 1;
		break;
	case Pet_Layer_Type:
		break;
	default:
		break;
	}
	freshCapacity();
}

void SkyBookUI_cl::updateHole( int8 _type, int8 solt )
{
	switch (_type)
	{
	case Relic_Layer_Type:
		break;
	case Weapon_Layer_Type:
		{
			for (size_t i = 0; i < gDataPool->getHeroWeapon()->getItemInfo().soltStrengList.size(); i++)
			{
				if(gDataPool->getHeroWeapon()->getItemInfo().soltStrengList[i].solt == solt)
				{
					gDataPool->getHeroWeapon()->getItemInfo().soltStrengList[i].strengLv = 1;
					break;
				}
				if(i == gDataPool->getHeroWeapon()->getItemInfo().soltStrengList.size() - 1)
				{
					pk::TianshuSoltStreng st;
					st.solt = _type;
					st.strengLv = 1;
					gDataPool->getHeroWeapon()->getItemInfo().soltStrengList.push_back(st);
					break;
				}
			}
		}
		break;
	case Pet_Layer_Type:
		break;
	default:
		break;
	}
	freshCapacity();
}

void SkyBookUI_cl::updateInlay( pk::GS2C_TianShuSet_Ret* value )
{
	if(!value) return;
	if(value->type == Relic_Layer_Type) //神器
	{

	}
	else if(value->type == Pet_Layer_Type)  //宠物
	{

	}
	else //武器
	{  
		CItem * pItem = gDataPool->getHeroWeapon();
		if(pItem)
		{
			pItem->getItemInfo().tianShuList = value->tianShuList;
		}
		if(m_pBagSelectBook)
		{
			CGridIcon* pGridIcon = CGridIcon::create(m_pBagSelectBook,m_pBagSelectBook->getIndex(),emGrids_BagBook);
			if (pGridIcon)
			{
				m_pInlayGrids[m_curSlot]->addChild(pGridIcon);
				pGridIcon->setTag(INLAY_CHILD);
				pGridIcon->setShowNum(false);
				pGridIcon->setPosition(Point(m_pInlayGrids[m_curSlot]->getSize().width/2,m_pInlayGrids[m_curSlot]->getSize().height/2));		
			}
			m_pBagSelectBook->InitBagItem(&(value->newTianShu));
			m_pBagSelectBook = nullptr;
		}
	}
}

void SkyBookUI_cl::updateLongTimer( float fd )
{
	m_fLongTime += fd;
	if(m_fLongTime >= LONGTIMER)
	{
		this->unschedule(schedule_selector(SkyBookUI_cl::updateLongTimer));
		m_fLongTime = 0.f;
		m_islongTouched = true;
		if(!m_pMoveBook) m_pMoveBook->removeFromParent();
		m_pMoveBook = ImageView::create();
		CGridIcon * itemgrid = dynamic_cast<CGridIcon*>(m_pInlayGrids[m_curSlot]->getChildByTag(INLAY_CHILD));
		if(itemgrid && itemgrid->GetItem())
		{
			m_pMoveBook->loadTexture(itemgrid->getFilePath(), itemgrid->getTextureType());
			this->addChild(m_pMoveBook);
			m_pMoveBook->setPosition(m_pInlayGrids[m_curSlot]->getTouchStartPos());
			itemgrid->setVisible(false);
		}
	}
}

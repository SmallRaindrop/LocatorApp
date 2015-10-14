/*
 *模块:制造界面
 *作者:Tangbo
 *时间:2015/9/15
 */
#pragma once

#include "GameUI.h"

//加速提示界面
class FastTipsUI_cl:public Layer
{
public:
	
	FastTipsUI_cl():m_id(-1),m_pLoadingbar(nullptr),m_pGold(nullptr)
	{

	}

	bool initdata(int id);

	static FastTipsUI_cl* create(int id);

	void   callback(Ref * pSneder, TouchEventType touchevent);

	void   fastCallback(Ref* pSender, TouchEventType touchevent);

	//设置显示金币
	void   setFastGold();

private:

	int      m_id;               //当前数据下标

	LoadingBar*  m_pLoadingbar;

	Widget*      m_pGold;            //加速提示

	Rect         m_rect;

	Point        m_point;
};

class ManufactureUI_cl:public GameUI
{
public:
	ManufactureUI_cl();
	~ManufactureUI_cl();
	friend class FastTipsUI_cl;
	bool onInit();
	void onOpen();

	/*初始化模块*/

	//初始化制造界面
	void initManufacture();

	//初始化生成线界面
	void initLine();

	//初始化图纸界面
	void initBluePrint();

	//初始化材料界面
	void initMaterial();

	/*操作函数*/
	void changePanel();

	void changeBluePrintPanel();

	//放入图纸，初始化数据
	void pushBlueprintByID(int id);
	void pushBlueprintByItem(CItem* item);

	/*回调模块*/

	//主按钮回调事件
	void  callback(Ref* _ref, TouchEventType touchevent);

	//制造界面操作按钮回调
	void  manufactureOptionCallback(Ref* _ref, TouchEventType touchevent);

	//制造界面材料回调
	void  manufactureMaterialCallback(Ref* _ref, TouchEventType touchevent);

	//领取生产线回调
	void  getLineCallback(Ref* _ref, TouchEventType touchevent);

	//图纸界面返回
	void  blueCallback(Ref* _ref, TouchEventType touchevent);

	//材料界面返回
	void  materialCallback(Ref* _ref, TouchEventType touchevent);

	//显示生产线进度提示
	void callbackShowBarTips(Ref* _ref, TouchEventType touchevent);

	//图纸背包格子点击回调事件
	void  oneTouchCallback(CItem* item);

	/*网络模块*/
	//开始制造回调
	void  startManufactureRet(int right);

	//开启新的生产线回调
	void  openNewLineRet();

	//领取生产线回调
	void  getLineRet(int dataid);

protected:

	//设置材料显示
	//idx:材料下标  str:材料的id和num
	void  setMaterialShow(int idx, string& str);

	//创建生产线节点
	Widget*  createLineChildById(int id);

	//更新节点
	void freshLineById(int id);

	//更新每个节点的显示
	void  update(float fd);

	//图纸分类
	CItemGridArray* getCurTypeBluePrint(int type);

private:

	/*记录模块*/
	//当前界面下标
	int            m_pageIndex; 

	//当前是否选图纸
	bool           m_bSelectBlueprint;

	//制造id
	int            m_blueprintID;

	//是否等待制造动画回调
	bool           m_bActionRet;

	/*节点指针*/
	//四个层容器节点
	//0制造 1生产线 2图纸 3材料
	Layout*        m_pPanel[4];

	//主按钮
	//0制造 1生产线 2图纸 3材料 4关闭
	Button*        m_pButton[5];

	//制造界面数据  顺时针环形数据 以最上边的数据为起点
	ImageView*     m_pMaterialIcon[6];

	//制造材料数   顺时针环形数据 以最上边的数据为起点
	Text*          m_pMaterialCount[6];

	//制造操作按钮  0放入图纸 1开始制造
	Button*        m_pOptionBtn[2];

	//制造所需的物品  0角色金币 1角色元宝 2目标个数 3制造时间 4所需金币
	Widget*          m_pNeed[5];

	//当前制造图纸
	ImageView*     m_pCurBlueprint;

	//当前格子选择的图纸
	CItem*         m_pBlueItem;


	//生成线的容器
	ScrollView*    m_pLineScroll;

	//生产线的滑块
	Slider*        m_pLineSlider;

	//单个生产线 作为缓存节点
	ImageView*     m_pLineChild;

	//默认起始位置
	Point          m_lineStartPos;

	//生产线节点的横向间隔
	int            m_lineDisX;

	//生产线节点的纵向间隔
	int            m_lineDisY;

	//存放生产线节点
	vector<Widget*> m_vLineWidget;

	//图纸容器  0全部 1武器 2防具 3神器 4宠物 5杂物
	ScrollView*    m_pBlueScroll[6];

	//图纸滑块  0全部 1武器 2防具 3神器 4宠物 5杂物
	Slider*        m_pBlueSlider[6];

	//图纸操作按钮 0全部 1武器 2防具 3神器 4宠物 5杂物 6出售 7回购
	Button*        m_pBlueBtn[8];

	//图纸操作按钮 0武器 1防具 2神器 3宠物 4杂物
	CItemGridArray* m_pBlueTypeArrary[5];

	//图纸标签
	int           m_blueSign;

	//材料
	ScrollView*    m_pMaterialScroll;

	//材料滑块
	Slider*        m_pMaterialSlider;

	//材料操作按钮 0出售 1回购
	Button*        m_pMaterialBtn[2];

	FastTipsUI_cl*  m_pFastTips;
};
/*
 模块:天书界面
 作者:TangBo
 时间:2015/8/31
 **/
#pragma  once
#include "GameUI.h"

class SkyBookUI_cl;
 
class SkyBookCalcUI_cl:public GameUI
{
public: 
	friend class SkyBookUI_cl;
	SkyBookCalcUI_cl();
	~SkyBookCalcUI_cl();
	bool onInit();

	void onOpen();

	void callback(Ref* pSender, TouchEventType touchtype);

	CC_SYNTHESIZE(int, m_count, CurCount);

private:
	SkyBookUI_cl * pUI;
	Text*       m_pText;
};


class SkyBookUI_cl:public GameUI
{
public:
	friend class SkyBookCalcUI_cl;
	SkyBookUI_cl();
	~SkyBookUI_cl();

	bool onInit();
	void onOpen();

	//镶嵌界面
	void initInlayLayer();

	//祭炼界面
	void initRefinedLayer();

	//合成界面
	void initSyntheticLayer();

	//背包界面
	void initBagLayer();



	//镶嵌界面配置按钮,状态切换
	void inlayConfigBtnChange();

	//根据当前镶嵌类型刷新数据界面
	void freshInlaydData();

	//刷新容量
	void freshCapacity();

	//检测是否与其他格子相撞
	void checkInsertRectOther();

	//显示对应的天书系统界面
	void showLayerByIndex();

	//按钮状态显示
	void showBtnStatus();

	//主按钮回调
	void callBack(Ref * pSender, TouchEventType touchtype);

	//镶嵌格子触摸回调
	void inlayGridCallback(Ref* pSender, TouchEventType touchtype);

	//镶嵌界面操作按钮回调
	void inlayOptionCallback(Ref* pSender, TouchEventType touchtype);

	//镶嵌界面配置按钮回调
	void inlayConfigCallback(Ref* pSender, TouchEventType touchtype);

	//祭炼界面操作按钮回调
	void refinedOptionsCallback(Ref* pSender, TouchEventType touchtype);

	//祭炼界面格子回调
	void refinedGridCallback(Ref* pSender, TouchEventType touchtype);

	//合成界面操作按钮回调
	void syntheicOptionCallback(Ref* pSender, TouchEventType touchtype);

	//背包标签按钮回调
	void bagSignBtnCallback(Ref* pSender, TouchEventType touchtype);

	//背包操作按钮回调
	void bagOptionCallback(Ref* pSender, TouchEventType touchtype);

	//跳转到背包界面, 设置主控制按钮 
	//val true显示标签页 false 没有标签
	void setMianBtn(bool val);

	//返回标签背包类型
	//param 0 是表示：已镶嵌、全部、神器、武器、宠物
	//      1 是表示：全部、神器、武器、宠物、材料
	int  getSignBagType(int param);

	//更改背包标签显示
	void showBagLayerBySign();

public:        //网络消息

	/**********发送网络消息**********/
	//发送镶嵌消息
	void          sendInlayMsg();

	//发送祭炼消息
	void          sendRefinedMsg();

	/********网络回调事件********/

	//更新天书配置返回
	void updateChangeConfigRet(pk::C2GS_TianShuChangeIndex_Ret* value);

	//更新孔位切换返回
	void updateChangeHoleRet(pk::C2GS_TianShuChangeSolt_Ret* value);

	//天书升级函数
	void upgradeSkyBook(int8 lv, int16 exp);

	//显示合成天书
	void showNewSkyBook(int16 dataid);

	//更新装备天书容量强化 _type 强化的类型
	void updateCapacity(int8 _type);

	//更新装备天书孔位强化
	void updateHole(int8 _type, int8 solt);

	//更新镶嵌
	void updateInlay(pk::GS2C_TianShuSet_Ret* value);

	//长按时间定时器
	void updateLongTimer(float fd);

public:           //背包自定义事件

	//背包单点事件
	void       signBagOneTouch(CItem* item);

	//背包双击事件
	void       signBagDoubleTouch(CItem* item);

private:

	//是否含有标签显示
	bool                m_isShowSign;

	//当前背包是否打开  setMianBtn中使用
	bool               m_isOpened;

	//当前选择的标签页
	int                 m_curIndex;

	//记录上次显示界面idx
	int                 m_lastIndex;

	//当前操作状态
	int                 m_CurOptionStutas;

	//当前是否满足长按事件 对于镶嵌界面格子按钮
	bool                m_islongTouched;

	//当前移动天书
	ImageView*          m_pMoveBook;

	//长按事件记录
	float               m_fLongTime;

	//当前撞到的格子id
	int                 m_curInsertId;

	//天书界面的容器层
	//0   为镶嵌界面 神器 武器 宠物
	//1-2 为祭炼界面 合成界面
	//3   为背包界面  
	//4-5 为背包界面的子界面  4有标签页 5没有标签页
	Layout*             m_pPanle[6];

	//主按钮
	//0神器 1武器 2宠物 3祭炼 4合成 5背包
	Button*             m_pButton[6];


	//镶嵌的格子指针
	//格子顺序:0-8  0个位特殊位置 其他的为普通位置
	ImageView*          m_pInlayGrids[9];

	//镶嵌的配置按钮
	Button*             m_pConfigBtn[3];

	//镶嵌的操作按钮    0卸下 1容量强化 2孔位强化
	Button*             m_pInlayOpBtns[3];

	//镶嵌的容量文本
	Text*               m_pCapacityText;

	//镶嵌属性list列表
	ListView*           m_pInlayList;

	//镶嵌使用配置id
	int8                m_curConfigIdx;

	//当前选择的孔位 默认值是-1，表示没有选择  每次操作后都要重新复赋值
	int                 m_curSlot;

	//总容量
	int                 m_totalCapacity;

	//当前容量
	int                 m_curCapacity;

	//是否开启容量强化
	bool                m_isCapacity;

	//是否开启孔位强化
	bool                m_isHole;

	//是否卸下操作
	bool                m_isGiveUp;


	//祭炼
	//要祭炼的格子指针
	ImageView*          m_pRefinedGrid;

	//祭炼的进度条
	LoadingBar*         m_pRefinedBar;

	//祭炼的星级标签   
	//左边文本0-1 0为初始星级 1为炼后星级
	//右边文本2-3 2为初始星级 3为炼后星级
	Text*               m_pStarText[4];

	//祭炼天书名字
	Text*               m_pRefinedTSName;

	//祭炼的操作按钮    
	//0 为祭炼按钮 1为放入 2为取消
	Button*             m_pRefinedOpBtn[3];

	//祭炼属性列表
	//0 为对比属性列表
	//1 为材料列表
	ListView*           m_pRefinedLists[2];

	//合成
	//合成格子指针
	//0-3 为材料格子 5为目标格子
	ImageView*          m_pSyntheicGrids[5];

	//合成的操作按钮    
	//0 为合成按钮 1为放入 2为取消
	Button*             m_pSyntheicOpBtn[3];

	//合成后的天书名字
	Text*               m_pSyntheicName;

	//合成后天书属性列表
	ListView*           m_pSyntheicList;

	//背包
	//背包标签界面
	//0已镶嵌 1全部 2神器 3武器 4 宠物  
	Button*             m_pBagSignBtn[5];
	//标签背包容器
	//0已镶嵌 1全部 2神器 3武器 4 宠物  
	ScrollView*         m_pBagSignScroll[5];
	//标签背包滑块
	Slider*             m_pBagSignSlider[5];

	//背包无标签界面
	ScrollView*         m_pBagScroll;

	//背包无标签滑块
	Slider*             m_pBagSlider;

	//背包选择天书名字
	Text*               m_pBagSelectName;

	//背包选择天书属性列表
	ListView*           m_pBagSelectList;
	
	//背包操作按钮
	//[0] 是左边  [1] 右边
	Button*             m_pBagOptionBtn[2];

	//背包当前选择的标签
	int                 m_curBagSignIdx;

	//记录当前选择天书的总数
	int                 m_curTotalBook;

	//当前背包选择天书
	CItem*              m_pBagSelectBook;

	//当前选中的天书容器
	vector<CItem*>      m_vSelectBook;

	//祭炼材料天书
	vector<pk::tian_shu_material> m_vSelectMaterial;
};
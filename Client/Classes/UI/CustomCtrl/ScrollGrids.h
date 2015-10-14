/*
 * 模块：创建背包格子,用于替换cocos编辑的滑动层
 * 作者：Tangbo
 * 时间：2015/8/20
 */
#pragma  once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "UIScrollView.h"
#include "UI/GameUIDef.h"
#include "../../Net/pk_trade.h"
#include "GridIcon.h"
#include "Net/pk_item.h"
#include "GameScene/ItemGrid.h"

USING_NS_CC;
using namespace cocos2d::ui;

struct GridIcon_st
{
	GridIcon_st(){
		gridIcon = nullptr;
		bgIcon   = nullptr;
	}
	CGridIcon *   gridIcon;          //道具图标
	Widget    *   bgIcon;            //背景图标

};

//处理事件
enum ItemTouchEvent
{
	LONG_TOUCH_EVENT,               //长按事件
	ONE_TOUCH_EVENT,                //单击事件
	DOUBLE_TOUCH_EVENT,             //双击事件

	ITEMEVENT_MAX,
};

struct EquipNode_st
{
	EquipNode_st()
	{
		equipnode = nullptr;
		rect = Rect::ZERO;
	}
	Widget*         equipnode;       //装备节点
	Rect            rect;            //区域
};

struct SelectItem_st
{
	pk::C2GS_NpcShopSell sell;
	int                  index;
};

typedef  vector<SelectItem_st>  Sale_V;                     //卖出道具类型
typedef  vector<GridIcon_st>           ItemIcon_V;          //道具显示类型
typedef  vector<EquipNode_st>          EquipNode_V;
typedef  std::function<void(CItem*)>   funct_s;

class ScrollGrids_cl:public ScrollView
{
public:

	//初始化
	/* Param: _gridType     创建类型
	          _totalGrid    创建格子总数
			  _lineGrid     传入滑动层一行的格子数
			  _scroll       传入要替换的滑动层
			  _parent       层节点，不传默认_scroll的父节点
			  _limit        是否限制大小
	*/
	bool init(emGridsType _gridType, int _totalGrid, int _lineGrid, ScrollView* &_scroll, Node * _parent, bool _limit);

	//创建新的滑动层,替换传入对象  并初始化数据
	/* Param: _gridType     创建类型
	          _totalGrid    创建格子总数
			  _lineGrid     传入滑动层一行的格子数
			  _scroll       传入要替换的滑动层
			  _parent       层节点,不传默认_scroll的父节点
			  _times        是否限制大小 默认是限制
	*/
	static ScrollGrids_cl* create(emGridsType _gridType, int _totalGrid, int _lineGrid, ScrollView* &_scroll, Node * _parent = nullptr, bool _limit = true);

	//创建新的滑动层,替换传入对象  不初始化数据
	/* Param: _gridType     创建类型
	          _totalGrid    创建格子总数
			  _lineGrid     传入滑动层一行的格子数
			  _scroll       传入要替换的滑动层
			  _parent       层节点,不传默认_scroll的父节点
			  _times        是否限制大小 默认是限制
	*/
	static ScrollGrids_cl* createWithOutData(emGridsType _gridType, int _totalGrid, int _lineGrid, ScrollView* &_scroll, Node * _parent = nullptr, bool _limit = true);

	//初始化容器层节点创建数据
	void    initCreateData();

	//重置界面
	void   reset();

	//根据传入值初始重置界面  删除格子
	void   resetByData(CItemGridArray* pGridsData);

	//根据传入值初始重置界面 不删除格子
	void   resetData(CItemGridArray* pGridsData);

	inline int	  getSelectIndex(){ return m_selectIndex; }


	//开启双击时间计算
	void   updateTime(float fd);

	//删除某个道具
	void   removeItemByIndex(int index);

	//增加某个道具
	void   addItemByIndex(int index);


	//卖出
	void   saleSelectItem();

	//整理
	void   cleanBag();

	//处理服务器是否卖出道具返回数据
	void   delwithItem(int _itemId);

	//格子点击事件回调
	void   clickGrid(Ref * _ref, TouchEventType _type);

	//双击事件
	void   doubleEvent();


	//添加穿戴装备区域
	void   addAreaEquip(EquipNode_V & _vec);
	void   addAreaEquip(Widget* _widget);

	//检测是否相交
	void   checkIntersectsRect();

	//注册事件
	void   registerFunc(funct_s _func, ItemTouchEvent _event);

	//得到节点数
	const int    getChildrenCount(){return m_childrenCnt;}

	//针对个人属性界面装备栏,服务器返回刷新
	void         freshRoleEquip(pk::GS2C_EquipExchangeRet* value);

	void	packupSelectEquip(int _cnt);

protected:
	ScrollGrids_cl();
	~ScrollGrids_cl();

	//参数定义
	CC_SYNTHESIZE_READONLY(int, m_totalPrice, TotalPrice);              //卖出总价格          
	CC_SYNTHESIZE_READONLY(Sale_V, m_vSelectItem, SelectItems);         //当前选中
	CC_SYNTHESIZE_READONLY(int,m_totalGrids, TotalGrids);               //总的格子数
	CC_SYNTHESIZE_READONLY(ItemIcon_V,m_itemIconVec, ItemIconVec);      //背包格子容器
	CC_SYNTHESIZE_READONLY(int,m_selectIndex,SelectIndex);              //选择节点idx

	CC_SYNTHESIZE(bool, m_isdoubled, IsDoubled);                        //设置是否开启双击标志
	CC_SYNTHESIZE(bool, m_OneSelected, OneSelect);                      //是否单选模式 true 单选
	CC_SYNTHESIZE(bool, m_longTouched, LongTouched);                    //是否支持长按

private:
	
	emGridsType                m_gridType;                 //创建格子背包类型
	int                        m_lineGrids;                //一行的格子数
	int                        m_disX;                     //横向间隔
	int                        m_disY;                     //竖向间隔
	Point                      m_startPos;                 //创建初始位置
	bool                       m_blimit;                   //是否显示格子数
	float                      m_delayTime;                //判断双击时间
	float                      m_longTime;                 //长按时间
	Widget*                    m_childnode;                //滑动层的单个节点
	Node*                      m_parent;                   //父节点
	ImageView*                 m_pEquip;                   //移动道具节点
	int                        m_recordcnt;                //记录是否完成卖道具
	bool                       m_isLongTouch;              //是否是长按  
	EquipNode_st*              m_changWidget;              //可穿戴节点的id
	bool                       m_isOverEquip;              //装备是否相交
	EquipNode_V                m_vEquipNode;               //穿戴装备与节点
	bool                       m_isDelete;                 //是否删除
	int                        m_childrenCnt;              //滑动层节点数


	CItemGridArray*            m_curShowItemArr;           //当前要显示的格子容器数据指针

	funct_s                    m_func[ITEMEVENT_MAX];      //传回函数
};

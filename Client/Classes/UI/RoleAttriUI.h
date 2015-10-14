/*
 * 模块：角色属性和装备界面
 * 作者：Tangbo
 */
#pragma once
#include "GameUI.h"
#include "Net/pk_item.h"


class RoleAttriUI_cl:public GameUI
{
public:

	RoleAttriUI_cl();
	~RoleAttriUI_cl();

	bool            onInit();
	void            onOpen();

	//更改标签按钮显示
	void            setBtnShowByIdx(int idx);

	//更改显示装备和属性值界面
	void            setPanelShowByIdx(int idx);

	//初始化详细属性界面
	void            initDetailData();

	//初始化Role Equip
	void            initRoleEquip();
	//刷新人物装备栏
	void            RefreshRoleEquip(pk::GS2C_EquipGetItem_Ret *value);

	//添加触摸事件
	void            addEquipTouchEvent(CGridIcon* grid);

	//得到当前的装备为装数
	int             getEquipNum();

	//主按钮返回事件
	void            callBack(Ref * _ref, TouchEventType _type);

	//装备按钮返回事件
	void            equipCallBack(Ref* _ref, TouchEventType _type);

	//神器装备回调
	void            goddeviceCallBack(Ref* pSender, TouchEventType type);

	//背包操作按钮回调事件
	void            operatCallBack(Ref* _ref, TouchEventType _type);

	//刷新显示
	void            freshShow();

	//检测精灵是否拖到背包区域
	//param：_spr 临时创建装备精灵指针
	bool            checkBagIsOverlap();

	void            updateTime(float fd);

	//获取个人属性装备滑动层节点
	inline ScrollView* getRoleEquipRoll(){return m_pScroll;} 

private:

	//标签按钮
	Button *           m_pSignBtn[3]; 

	//神器与装备  0:神器 1:武器  2-4:法宝    
	Button *           m_pEquipItem[6];

	//层节点      0:属性 1:背包 2:详细属性
	Layout *           m_pPanel[3];

	//属性节点    0:hp 1:magic 2:attack 3: defence 4:strength_at 5:strengt_sk
	Text *             m_pLabel[6];

	//战力节点
	Label *             m_pAttackText;

	//装备背包滑动层
	ScrollView*        m_pScroll;

	//滑块节点
	Slider*            m_pSlider;

	//当前选择装备id
	int                m_curEidx;

	//当前的界面id
	int                m_curUIidx;

	//是否长按
	bool               m_isLongTouch;

	//长按时间(秒)
	float              m_longTime;

	//双击时间
	float              m_delayTime;

	//装备移动
	ImageView*         m_pMoveSprite;

	//背包的滑动层区域
	Rect               m_scrollRect;   

	//要卸下的装备id
	vector<int>        m_takeoff;

	//是否支持双击
	bool               m_doubleTouched;

	//是否支持长按
	bool               m_longTouched;
 };


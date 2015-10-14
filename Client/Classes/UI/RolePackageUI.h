/*
 * 模块:角色背包界面模块
 * 作者：Tangbo
 */
#pragma once
#include "GameUI.h"
#include "Net/pk_trade.h"


typedef   vector<pk::C2GS_NpcShopSell>  SaleItem_v;

class RolePackageUI_cl:public GameUI
{
public:
	RolePackageUI_cl();
	~RolePackageUI_cl();

	bool            onInit();
	void            onOpen();


	//初始化容器层数据
	void           initScrollView();


	//设置类型显示
	void            setShowByType(int _type);

	//按钮回调
	void            callBack(Ref* _ref, TouchEventType _type);

	//刷新显示
	void            freshShow();

	//更新
	void            update(float dt);

private:
	
	//界面层滑动层指针
	ScrollView *              m_pScorllView[4];    

	//滑块指针
	Slider     *              m_pSlider[4];

	//当前显示类型
	int                       m_curTypeIdx;

	//选中的物品
	SaleItem_v                m_vSaleItem[4];

	//显示节点计数
	Text*                     m_numText[4];

	//金币
	Text*                     m_jbText;

	//记录每个层容器节点个数
	int                       m_childCount[4];

	//记录金币数
	__int64                       m_jb;
};
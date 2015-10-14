/*模块: 申请军团界面
 *作者: Tangbo
 *时间: 2015/9/29
 */
#pragma once
#include "GameUI.h"


class AddLegionUI_cl:public GameUI
{
public:
	AddLegionUI_cl();
	~AddLegionUI_cl();

	bool onInit();

	//更改界面显示
	void    changeShow();

	//更新军团列表
	void    updateLegionList(Legion_V * vec = nullptr);

	//搜索成员
	Legion_V searchMember();

	//标签按钮回调
	void    callbackSign(Ref* pSender, TouchEventType event);

	//控制按钮回调
	void    callbackOption(Ref* pSender, TouchEventType event);

	//搜索按钮回调
	void    callbackSearch(Ref* pSender, TouchEventType event);

	//创建军团输入框回调
	void    callbackCreateInput(Ref* textfield, TextFiledEventType event);

	//搜索军团名字输入框回调
	void    callbackSearchInput(Ref* textfield, TextFiledEventType event);

private:

	//当前界面显示的index
	int        m_nIndex;

	//层容器指针  0信息 1军团列表 2创建军团
	Widget*    m_pPanel[3];

	//标签按钮  0信息 1军团 2关闭
	Button*    m_pSignBtn[3];

	//军团列表
	ListView*  m_pLegionList;

	//创建军团的输入控件
	TextField* m_pLegionName;

	//搜索军团的输入控件
	TextField* m_pSearchName;
};
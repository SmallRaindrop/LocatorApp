#pragma once

#include "GameUI.h"
#include "Net/pk_friend.h"

class FriendUI_cl: public GameUI
{
public:
	FriendUI_cl();
	~FriendUI_cl();

	bool onInit();

	void onOpen();

	void onClose();

	//初始化按钮
	//param : _idx 选择按钮的下标
	void setSelectBtnByIdx(int _idx);

	//设置节点数据
	void setChildShowDate(Widget * child, pk::Friend_Info* _info);

	//显示那个列表
	void setShowByIndex(int _index);

	//初始化好友列表
	void initFriendList();

	//刷新好友列表
	void freshFriendList();

	//初始化黑名单列表
	void initBlackList();

	//刷新黑名单列表
	void freshBlackList();

	//初始化最近列表
	void initRelativeList();

	//刷新最近列表
	void freshRelativeList();

	//好友类型回调函数
	void callBack(Ref * pSender, TouchEventType _type);

	//好友操作界面回调
	void callBackFriendB(Ref * pSender, TouchEventType _type);

	//好友操作界面回调
	void callBackBlackB(Ref * pSender, TouchEventType _type);

	//好友操作界面回调
	void callBackRelativeB(Ref * pSender, TouchEventType _type);

	//list回调
	void callBackList(Ref * pSender, TouchEventType _type);

private:

	Button*                  m_selectbtn[3];                 //列表选择按钮

	ListView*                m_pViewList[3];                 //listview:0好友, 1黑名单, 2最近玩家
	Layout*                  m_pBtnPanel[3];                 //option:0好友, 1黑名单, 2最近玩家 
	Slider*                  m_pSlider[3];                   //滑块
	Widget*                  m_selectChild[3];               //选择的节点
	float                    m_fpercent[3];                  //三个列表bar的位置
	int                      m_index;                        //当前选择
	int64                    m_selectPid[3];         
	string                   m_selectPname[3];
	int64                    m_curplayerid;                  //当前的选择的playerid
	string                   m_curpname;                     //当前玩家名字
};
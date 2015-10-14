/****************************************************************************
 聊天数据管理器
 彭龙华
 2015-10-08
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "Net/pk_item.h"


#define MAX_MSG_CACHE_SIZE 100

//聊天频道,和服务器频道ID保持一致
typedef enum _channelType
{
	ChannelType_World = 1,	//世界
	ChannelType_Guild,		//军团
	ChannelType_Team,		//队伍
	ChannelType_Map,		//同一张地图
	ChannelType_System,		//系统
	ChannelType_Horn,		//喇叭
	ChannelType_Personal,	//私聊
	ChannelType_Team_Msg,	//组队
	ChannelType_Count,
}ChannelType;

//单条信息
typedef struct _msgItem
{
	pk::GS2C_Chat content;	//单条消息
	bool bIsMine;			//是玩家自己发送的？
}MsgItem;

//单个频道
typedef struct _channel
{
	_channel()	{bUnread = false;}

	vector<MsgItem> msg;		//频道所有消息
	bool bUnread;
	string playerName;
	int64	channelId;			//客户端频道ID
}Channel;

class CChatDataMgr
{

public:
	CChatDataMgr();
	~CChatDataMgr();

	//保存聊天消息 私聊使用玩家ID，作为channel id
	MsgItem* AddMsg(int64 nChannelId, pk::GS2C_Chat chatContent,bool bIsMyWords = false);

	//增加私聊频道
	void AddChannel(int64 nChannelId, string playerName);

	//获取频道
	Channel* GetChannel(int64 nChannelId);

	//删除频道
	void RemoveChannel(int64 nChannelId);

	//设置频道未读标志
	void SetChannelReaded(int64 nChannelId, bool bReaded);

	int GetUnreadChannelNum();

	queue<MsgItem>*	GetMsgOfMainUI() { return &m_msgOfMainUI; }

private:
	//所有频道 <客户端频道ID，频道>
	map<int64, Channel> channels;
	//显示在主界面上的消息
	queue<MsgItem> m_msgOfMainUI;
};
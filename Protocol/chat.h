
// -define(ChannelType_World, 1).     %%世界
// -define(ChannelType_Guild, 2).     %%公会
// -define(ChannelType_Team, 3).      %%队伍
// -define(ChannelType_Map, 4).       %%同一张地图
// -define(ChannelType_System, 5).    %%系统
// -define(ChannelType_Horn, 6).      %%喇叭
// -define(ChannelType_Horn, 7).      %%私聊

struct ItemLink
{
	int8 bagType;  //背包类型, 1:装备, 2:杂物, 3:材料
	int64 itemId; //物品id
};

// 客户端请求发送聊天消息
struct C2GS_Chat ->
{
	int8	channelId;  //频道
	string	message;    //消息
	vector<ItemLink> vec;   //物品id列表
};

struct C2GS_Private_Chat ->
{
	int64   playerId;
	string  message;
};

struct GS2C_Monster_ChatMsg <-
{
	int64   monsterId; //
	int32   strId;//
	int32   displayMs;
};
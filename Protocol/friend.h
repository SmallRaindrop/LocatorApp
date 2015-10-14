
struct Friend_Info
{
	int64 playerId;  //玩家id
	string name;     //玩家名字
	int32 level;     //玩家等级
	int32 career;    //玩家职业
	int32 sex;       //玩家性别
	int8  online;    //是否在线, 1:在线, 0:不在线
	int8  type;      //1:好友,2:仇人,3:黑名单,4:临时好友
	int8  isInTeam;  //是否在队伍中
	int8  isVip;     //是否是vip
};

struct GS2C_All_Friend_Info <-
{
	vector<Friend_Info> vec;
};

// GS通知客户端系统消息
struct GS2C_Friend_Info <-
{
	Friend_Info st;
};

// 客户端请求发送聊天消息
struct C2GS_Add_Friend ->
{
	int64 playerId;  //玩家id
	int8  type; //1:好友,2:仇人,3:黑名单
};

// -1:好友列表已满
// -2:已经在列表中
// -3:对方不存在
// 1: 加好友成功
struct GS2C_Add_Friend_Result <-
{
	int32 retCode; //返回值
};

struct C2GS_Remove_Friend ->
{
	int64 playerId; //玩家id
	int8  type; //1:好友,2:仇人,3:黑名单
};

struct GS2C_Remove_Friend_Result <-
{
	int32 retCode;  //-1:失败, 1:成功
	int64 playerId; //玩家id
	int8  type; //1:好友,2:仇人,3:黑名单
};

struct C2GS_Request_Friend_State ->
{
};

struct friend_State
{
	int64 playerId;
	int32 level;
	int8 isInTeam;
};

struct GS2C_Request_Friend_State_Result <-
{
	vector<friend_State> vec;
};

//请求临时好友信息
struct C2GS_Palyer_Touch_List_Req ->
{
	vector<int64> playerList
};

struct GS2C_Palyer_Touch_List_Ret <-
{
	vector<Friend_Info> player_list;
};
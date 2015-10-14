// define msg between client and loginserver

// 登录验证（测试平台）
struct C2LS_Login_Test ->
{
	string	account;
	int16	platformID;
	string	sign;
	string	deviceIMEI;
	string	screenSize;
	int32     channelId;
};

// 登录验证返回
struct LS2C_Login_Ret <-
{
	int8	result;
	int64	userID;
};

// 请求服务器列表信息
struct C2LS_RequestGameServerList ->
{

};

// 服务器列表信息结构
struct GameServerInfo
{
	int32	id;
	string	name;
	int32	status;
	string  desc;
	int8	isExist; //1:存在角色；0：不存在角色
	int8	career,//  1 战士 Career_Soldier; 2 道士 Career_DaoShi  ; 3 法师 Career_FaShi  
	int8	sex;//1:男 0:女
	int32	level; //角色等级
	string	playerName; //角色的名字
	int8    isNew;      // 是否是新服
	string  regionName;  // 区名
};

// 返回服务器列表
struct LS2C_GameServerList_Ret <-
{
	int8    regionCnt;   // 最多几个区
	vector<GameServerInfo>	gameServers;
};

// 选择游戏服务器，请求服务器信息
struct C2LS_RequestSelGameServer ->
{
	int32	serverID;
};

// 返回服务器信息
struct LS2C_SelGameServer_Ret <-
{
	int32		retCode;
	string		ip;
	int16		port;
	string		sign;
};

//返回上一级
struct C2LS_BackPreStatus ->
{
};
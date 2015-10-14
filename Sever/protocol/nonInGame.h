// -> client to server
// <- server to client
// <-> client & server

// 请求登录gameserver
struct C2GS_Login ->
{
	int64		accountID;
	string		sign;
	int32		version;
};

struct UserPlayerData
{
	int64	playerID;
	string	name;
	int32	level;
	int8	career;
	int8	sex;
};

// 登录返回，成功返回角色列表
struct GS2C_Login_Ret <-
{
	int32		retCode;
	vector<UserPlayerData>	player_list;
};

// 请求创建角色
struct C2GS_CreatePlayer ->
{
	string	name;
	int8	career;//  1 战士 Career_Soldier; 2 道士 Career_DaoShi  ; 3 法师 Career_FaShi  
	int8	sex;//1:男 0:女
};

// 请求创建角色返回，成功返回角色信息
struct GS2C_CreatePlayer_Ret <-
{
	int32	retCode;
	vector<UserPlayerData>	player_list;
};

// 删除角色
struct C2GS_DeletePlayer ->
{
	int64	playerID;
};

// 请求创建角色返回，成功返回角色信息
struct GS2C_DeletePlayer_Ret <-
{
	int32	retCode;
	vector<UserPlayerData>	player_list;
};

// 请求进入游戏
struct C2GS_EnterGame ->
{
	int64	playerID;
};

// 小退，返回选择角色界面
struct GS2C_ReturnToSelectRoleDlg_Ret <-
{
	int32		retCode; //0: 成功  非0：出错或超时,请关闭client
	vector<UserPlayerData>	player_list;
};

// 玩家请求进入游戏后，服务器首先会发送玩家相关数据到客户端，此消息指明数据发送完毕
struct GS2C_SendPlayerDataComplete <-
{
	int32 mapDataId;//地图的配置id， 如果mapDataId等于0，请不要加载
	int16	x;   // in logical, player current position
	int16	y;   // in logical, player current position
};

// 客户端加载完数据后会发送进入地图请求
struct C2GS_EnterMap ->
{
};






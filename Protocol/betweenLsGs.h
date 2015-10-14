// GS请求注册自己
struct GS2LS_Register_Request <->
{
	int32	serverID;
	string  sign;
};

// GS注册返回
struct LS2GS_Register_Ret <->
{
	int32	retCode;
};

// LS请求账号在该服的用户信息
struct LS2GS_GetPlayerInfo_Request <->
{
	int64		userID;
};

// LS请求账号在该服的用户信息
struct GS2LS_GetPlayerInfo_Ret <->
{
	int64	accountID; // 账号ID
	int64	userID; // 角色ID
	int8	isExist;
	int8	career,//  1 战士 Career_Soldier; 2 道士 Career_DaoShi  ; 3 法师 Career_FaShi  
	int8	sex;//1:男 0:女
	int32	level; //角色等级
	string	name; //角色的名字
};

// LS通知GS玩家准备登录
struct LS2GS_UserReadyToLogin <->
{
	int32	platId;
	int64	accountID;
	string	account;
	string	sign;
};

// 玩家登录GS给LS通知
struct GS2LS_UserLogin <->
{
	int32	platId;
	int64	accountID;
	string	account;
	string	sign;
};

// 玩家退出GS给LS通知
struct GS2LS_UserLogout <->
{
	int64		userID;
};

// LS通知GS踢出玩家
struct LS2GS_UserKick <->
{
	int64		userID;
};

// 充值信息
struct LS2GS_PayInfo_Request <->
{
	string		webPid;
	string		op;
};

// 充值信息返回
struct GS2LS_PayInfo_Ret <->
{
	string		webPid;
	string		orderId;
	int8		retCode;
};

// 后台GM命令
struct LS2GS_GM_CMD_Request <->
{
	string		webPid;
	string		op;
};

struct GS2LS_GM_CMD_Ret <->
{
	string		webPid;
	string		name;
	int8		retCode;
};

// 踢玩家下线
struct LS2GS_Kick_Player_Off_Request <->
{
	string		webPid;
	string		name;
};

struct GS2LS_Kick_Player_Off_Ret <->
{
	string		webPid;
	string		name;
	int8		retCode;
};

// 系统公告
struct LS2GS_Announcement_Request <->
{
	string		webPid;
	string		msg;
};

struct GS2LS_Announcement_Ret <->
{
	string		webPid;
	int8		retCode;
};

// 后台控制活动的开启或关闭
struct LS2GS_control_activity_Request <->
{
	string		webPid;
	string		op;
};

struct GS2LS_control_activity_Ret <->
{
	string		webPid;
	int8		retCode;
};

struct GS2LS_kickOutUser <->
{
	int64 userId;
};

struct GS2LS_upadateOnlinePlayerCnt <->
{
	int32 onlinePlayerCnt;
};

struct LS2GS_Forbid_Chat_Request <->
{
	string webPid;
	string name;
	int32 time;
	int8 flag;
};

struct GS2LS_Forbid_Chat_Request_Ret <->
{
	string		webPid;
	int8		retCode;	
};

struct LS2GS_SET_GM_Request <->
{
	string		webPid;
	string		name;
	int8        flag;
};

struct GS2LS_SET_GM_Request_Ret <->
{
	string		webPid;
	int8		retCode;	
};

#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct GS2LS_Register_Request
{
	int32 serverID;
	string sign;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_Register_Request(stNetMsg& msg,GS2LS_Register_Request& value);
bool OnGS2LS_Register_Request(GS2LS_Register_Request* value);
void ReadGS2LS_Register_Request(stNetMsg& msg,GS2LS_Register_Request& value);

struct LS2GS_Register_Ret
{
	int32 retCode;
	void Send(IOSocket* pIOSock);
};
void WriteLS2GS_Register_Ret(stNetMsg& msg,LS2GS_Register_Ret& value);
bool OnLS2GS_Register_Ret(LS2GS_Register_Ret* value);
void ReadLS2GS_Register_Ret(stNetMsg& msg,LS2GS_Register_Ret& value);

struct LS2GS_GetPlayerInfo_Request
{
	int64 userID;
	void Send(IOSocket* pIOSock);
};
void WriteLS2GS_GetPlayerInfo_Request(stNetMsg& msg,LS2GS_GetPlayerInfo_Request& value);
bool OnLS2GS_GetPlayerInfo_Request(LS2GS_GetPlayerInfo_Request* value);
void ReadLS2GS_GetPlayerInfo_Request(stNetMsg& msg,LS2GS_GetPlayerInfo_Request& value);

struct GS2LS_GetPlayerInfo_Ret
{
	int64 accountID;
	int64 userID;
	int8 isExist;
	int8 career;
	int8 sex;
	int32 level;
	string name;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_GetPlayerInfo_Ret(stNetMsg& msg,GS2LS_GetPlayerInfo_Ret& value);
bool OnGS2LS_GetPlayerInfo_Ret(GS2LS_GetPlayerInfo_Ret* value);
void ReadGS2LS_GetPlayerInfo_Ret(stNetMsg& msg,GS2LS_GetPlayerInfo_Ret& value);

struct LS2GS_UserReadyToLogin
{
	int32 platId;
	int64 accountID;
	string account;
	string sign;
	void Send(IOSocket* pIOSock);
};
void WriteLS2GS_UserReadyToLogin(stNetMsg& msg,LS2GS_UserReadyToLogin& value);
bool OnLS2GS_UserReadyToLogin(LS2GS_UserReadyToLogin* value);
void ReadLS2GS_UserReadyToLogin(stNetMsg& msg,LS2GS_UserReadyToLogin& value);

struct GS2LS_UserLogin
{
	int32 platId;
	int64 accountID;
	string account;
	string sign;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_UserLogin(stNetMsg& msg,GS2LS_UserLogin& value);
bool OnGS2LS_UserLogin(GS2LS_UserLogin* value);
void ReadGS2LS_UserLogin(stNetMsg& msg,GS2LS_UserLogin& value);

struct GS2LS_UserLogout
{
	int64 userID;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_UserLogout(stNetMsg& msg,GS2LS_UserLogout& value);
bool OnGS2LS_UserLogout(GS2LS_UserLogout* value);
void ReadGS2LS_UserLogout(stNetMsg& msg,GS2LS_UserLogout& value);

struct LS2GS_UserKick
{
	int64 userID;
	void Send(IOSocket* pIOSock);
};
void WriteLS2GS_UserKick(stNetMsg& msg,LS2GS_UserKick& value);
bool OnLS2GS_UserKick(LS2GS_UserKick* value);
void ReadLS2GS_UserKick(stNetMsg& msg,LS2GS_UserKick& value);

struct LS2GS_PayInfo_Request
{
	string webPid;
	string op;
	void Send(IOSocket* pIOSock);
};
void WriteLS2GS_PayInfo_Request(stNetMsg& msg,LS2GS_PayInfo_Request& value);
bool OnLS2GS_PayInfo_Request(LS2GS_PayInfo_Request* value);
void ReadLS2GS_PayInfo_Request(stNetMsg& msg,LS2GS_PayInfo_Request& value);

struct GS2LS_PayInfo_Ret
{
	string webPid;
	string orderId;
	int8 retCode;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_PayInfo_Ret(stNetMsg& msg,GS2LS_PayInfo_Ret& value);
bool OnGS2LS_PayInfo_Ret(GS2LS_PayInfo_Ret* value);
void ReadGS2LS_PayInfo_Ret(stNetMsg& msg,GS2LS_PayInfo_Ret& value);

struct LS2GS_GM_CMD_Request
{
	string webPid;
	string op;
	void Send(IOSocket* pIOSock);
};
void WriteLS2GS_GM_CMD_Request(stNetMsg& msg,LS2GS_GM_CMD_Request& value);
bool OnLS2GS_GM_CMD_Request(LS2GS_GM_CMD_Request* value);
void ReadLS2GS_GM_CMD_Request(stNetMsg& msg,LS2GS_GM_CMD_Request& value);

struct GS2LS_GM_CMD_Ret
{
	string webPid;
	string name;
	int8 retCode;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_GM_CMD_Ret(stNetMsg& msg,GS2LS_GM_CMD_Ret& value);
bool OnGS2LS_GM_CMD_Ret(GS2LS_GM_CMD_Ret* value);
void ReadGS2LS_GM_CMD_Ret(stNetMsg& msg,GS2LS_GM_CMD_Ret& value);

struct LS2GS_Kick_Player_Off_Request
{
	string webPid;
	string name;
	void Send(IOSocket* pIOSock);
};
void WriteLS2GS_Kick_Player_Off_Request(stNetMsg& msg,LS2GS_Kick_Player_Off_Request& value);
bool OnLS2GS_Kick_Player_Off_Request(LS2GS_Kick_Player_Off_Request* value);
void ReadLS2GS_Kick_Player_Off_Request(stNetMsg& msg,LS2GS_Kick_Player_Off_Request& value);

struct GS2LS_Kick_Player_Off_Ret
{
	string webPid;
	string name;
	int8 retCode;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_Kick_Player_Off_Ret(stNetMsg& msg,GS2LS_Kick_Player_Off_Ret& value);
bool OnGS2LS_Kick_Player_Off_Ret(GS2LS_Kick_Player_Off_Ret* value);
void ReadGS2LS_Kick_Player_Off_Ret(stNetMsg& msg,GS2LS_Kick_Player_Off_Ret& value);

struct LS2GS_Announcement_Request
{
	string webPid;
	string msg;
	void Send(IOSocket* pIOSock);
};
void WriteLS2GS_Announcement_Request(stNetMsg& msg,LS2GS_Announcement_Request& value);
bool OnLS2GS_Announcement_Request(LS2GS_Announcement_Request* value);
void ReadLS2GS_Announcement_Request(stNetMsg& msg,LS2GS_Announcement_Request& value);

struct GS2LS_Announcement_Ret
{
	string webPid;
	int8 retCode;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_Announcement_Ret(stNetMsg& msg,GS2LS_Announcement_Ret& value);
bool OnGS2LS_Announcement_Ret(GS2LS_Announcement_Ret* value);
void ReadGS2LS_Announcement_Ret(stNetMsg& msg,GS2LS_Announcement_Ret& value);

struct LS2GS_control_activity_Request
{
	string webPid;
	string op;
	void Send(IOSocket* pIOSock);
};
void WriteLS2GS_control_activity_Request(stNetMsg& msg,LS2GS_control_activity_Request& value);
bool OnLS2GS_control_activity_Request(LS2GS_control_activity_Request* value);
void ReadLS2GS_control_activity_Request(stNetMsg& msg,LS2GS_control_activity_Request& value);

struct GS2LS_control_activity_Ret
{
	string webPid;
	int8 retCode;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_control_activity_Ret(stNetMsg& msg,GS2LS_control_activity_Ret& value);
bool OnGS2LS_control_activity_Ret(GS2LS_control_activity_Ret* value);
void ReadGS2LS_control_activity_Ret(stNetMsg& msg,GS2LS_control_activity_Ret& value);

struct GS2LS_kickOutUser
{
	int64 userId;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_kickOutUser(stNetMsg& msg,GS2LS_kickOutUser& value);
bool OnGS2LS_kickOutUser(GS2LS_kickOutUser* value);
void ReadGS2LS_kickOutUser(stNetMsg& msg,GS2LS_kickOutUser& value);

struct GS2LS_upadateOnlinePlayerCnt
{
	int32 onlinePlayerCnt;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_upadateOnlinePlayerCnt(stNetMsg& msg,GS2LS_upadateOnlinePlayerCnt& value);
bool OnGS2LS_upadateOnlinePlayerCnt(GS2LS_upadateOnlinePlayerCnt* value);
void ReadGS2LS_upadateOnlinePlayerCnt(stNetMsg& msg,GS2LS_upadateOnlinePlayerCnt& value);

struct LS2GS_Forbid_Chat_Request
{
	string webPid;
	string name;
	int32 time;
	int8 flag;
	void Send(IOSocket* pIOSock);
};
void WriteLS2GS_Forbid_Chat_Request(stNetMsg& msg,LS2GS_Forbid_Chat_Request& value);
bool OnLS2GS_Forbid_Chat_Request(LS2GS_Forbid_Chat_Request* value);
void ReadLS2GS_Forbid_Chat_Request(stNetMsg& msg,LS2GS_Forbid_Chat_Request& value);

struct GS2LS_Forbid_Chat_Request_Ret
{
	string webPid;
	int8 retCode;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_Forbid_Chat_Request_Ret(stNetMsg& msg,GS2LS_Forbid_Chat_Request_Ret& value);
bool OnGS2LS_Forbid_Chat_Request_Ret(GS2LS_Forbid_Chat_Request_Ret* value);
void ReadGS2LS_Forbid_Chat_Request_Ret(stNetMsg& msg,GS2LS_Forbid_Chat_Request_Ret& value);

struct LS2GS_SET_GM_Request
{
	string webPid;
	string name;
	int8 flag;
	void Send(IOSocket* pIOSock);
};
void WriteLS2GS_SET_GM_Request(stNetMsg& msg,LS2GS_SET_GM_Request& value);
bool OnLS2GS_SET_GM_Request(LS2GS_SET_GM_Request* value);
void ReadLS2GS_SET_GM_Request(stNetMsg& msg,LS2GS_SET_GM_Request& value);

struct GS2LS_SET_GM_Request_Ret
{
	string webPid;
	int8 retCode;
	void Send(IOSocket* pIOSock);
};
void WriteGS2LS_SET_GM_Request_Ret(stNetMsg& msg,GS2LS_SET_GM_Request_Ret& value);
bool OnGS2LS_SET_GM_Request_Ret(GS2LS_SET_GM_Request_Ret* value);
void ReadGS2LS_SET_GM_Request_Ret(stNetMsg& msg,GS2LS_SET_GM_Request_Ret& value);


};


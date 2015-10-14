
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct C2LS_Login_Test
{
	string account;
	int16 platformID;
	string sign;
	string deviceIMEI;
	string screenSize;
	int32 channelId;
	void Send(IOSocket* pIOSock);
};
void WriteC2LS_Login_Test(stNetMsg& msg,C2LS_Login_Test& value);
void ReadC2LS_Login_Test(stNetMsg& msg,C2LS_Login_Test& value);

struct LS2C_Login_Ret
{
	int8 result;
	int64 userID;
};
void WriteLS2C_Login_Ret(stNetMsg& msg,LS2C_Login_Ret& value);
bool OnLS2C_Login_Ret(LS2C_Login_Ret* value);
void ReadLS2C_Login_Ret(stNetMsg& msg,LS2C_Login_Ret& value);

struct C2LS_RequestGameServerList
{
	void Send(IOSocket* pIOSock);
};
void WriteC2LS_RequestGameServerList(stNetMsg& msg,C2LS_RequestGameServerList& value);
void ReadC2LS_RequestGameServerList(stNetMsg& msg,C2LS_RequestGameServerList& value);

struct GameServerInfo
{
	int32 id;
	string name;
	int32 status;
	string desc;
	int8 isExist;
	int8 career;
	int8 sex;
	int32 level;
	string playerName;
	int8 isNew;
	string regionName;
};
void WriteGameServerInfo(stNetMsg& msg,GameServerInfo& value);
void ReadGameServerInfo(stNetMsg& msg,GameServerInfo& value);

struct LS2C_GameServerList_Ret
{
	int8 regionCnt;
	vector<GameServerInfo> gameServers;
};
void WriteLS2C_GameServerList_Ret(stNetMsg& msg,LS2C_GameServerList_Ret& value);
bool OnLS2C_GameServerList_Ret(LS2C_GameServerList_Ret* value);
void ReadLS2C_GameServerList_Ret(stNetMsg& msg,LS2C_GameServerList_Ret& value);

struct C2LS_RequestSelGameServer
{
	int32 serverID;
	void Send(IOSocket* pIOSock);
};
void WriteC2LS_RequestSelGameServer(stNetMsg& msg,C2LS_RequestSelGameServer& value);
void ReadC2LS_RequestSelGameServer(stNetMsg& msg,C2LS_RequestSelGameServer& value);

struct LS2C_SelGameServer_Ret
{
	int32 retCode;
	string ip;
	int16 port;
	string sign;
};
void WriteLS2C_SelGameServer_Ret(stNetMsg& msg,LS2C_SelGameServer_Ret& value);
bool OnLS2C_SelGameServer_Ret(LS2C_SelGameServer_Ret* value);
void ReadLS2C_SelGameServer_Ret(stNetMsg& msg,LS2C_SelGameServer_Ret& value);

struct C2LS_BackPreStatus
{
	void Send(IOSocket* pIOSock);
};
void WriteC2LS_BackPreStatus(stNetMsg& msg,C2LS_BackPreStatus& value);
void ReadC2LS_BackPreStatus(stNetMsg& msg,C2LS_BackPreStatus& value);


};


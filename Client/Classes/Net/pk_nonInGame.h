
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct C2GS_Login
{
	int64 accountID;
	string sign;
	int32 version;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Login(stNetMsg& msg,C2GS_Login& value);
void ReadC2GS_Login(stNetMsg& msg,C2GS_Login& value);

struct UserPlayerData
{
	int64 playerID;
	string name;
	int32 level;
	int8 career;
	int8 sex;
};
void WriteUserPlayerData(stNetMsg& msg,UserPlayerData& value);
void ReadUserPlayerData(stNetMsg& msg,UserPlayerData& value);

struct GS2C_Login_Ret
{
	int32 retCode;
	vector<UserPlayerData> player_list;
};
void WriteGS2C_Login_Ret(stNetMsg& msg,GS2C_Login_Ret& value);
bool OnGS2C_Login_Ret(GS2C_Login_Ret* value);
void ReadGS2C_Login_Ret(stNetMsg& msg,GS2C_Login_Ret& value);

struct C2GS_CreatePlayer
{
	string name;
	int8 career;
	int8 sex;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_CreatePlayer(stNetMsg& msg,C2GS_CreatePlayer& value);
void ReadC2GS_CreatePlayer(stNetMsg& msg,C2GS_CreatePlayer& value);

struct GS2C_CreatePlayer_Ret
{
	int32 retCode;
	vector<UserPlayerData> player_list;
};
void WriteGS2C_CreatePlayer_Ret(stNetMsg& msg,GS2C_CreatePlayer_Ret& value);
bool OnGS2C_CreatePlayer_Ret(GS2C_CreatePlayer_Ret* value);
void ReadGS2C_CreatePlayer_Ret(stNetMsg& msg,GS2C_CreatePlayer_Ret& value);

struct C2GS_DeletePlayer
{
	int64 playerID;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_DeletePlayer(stNetMsg& msg,C2GS_DeletePlayer& value);
void ReadC2GS_DeletePlayer(stNetMsg& msg,C2GS_DeletePlayer& value);

struct GS2C_DeletePlayer_Ret
{
	int32 retCode;
	vector<UserPlayerData> player_list;
};
void WriteGS2C_DeletePlayer_Ret(stNetMsg& msg,GS2C_DeletePlayer_Ret& value);
bool OnGS2C_DeletePlayer_Ret(GS2C_DeletePlayer_Ret* value);
void ReadGS2C_DeletePlayer_Ret(stNetMsg& msg,GS2C_DeletePlayer_Ret& value);

struct C2GS_EnterGame
{
	int64 playerID;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_EnterGame(stNetMsg& msg,C2GS_EnterGame& value);
void ReadC2GS_EnterGame(stNetMsg& msg,C2GS_EnterGame& value);

struct GS2C_ReturnToSelectRoleDlg_Ret
{
	int32 retCode;
	vector<UserPlayerData> player_list;
};
void WriteGS2C_ReturnToSelectRoleDlg_Ret(stNetMsg& msg,GS2C_ReturnToSelectRoleDlg_Ret& value);
bool OnGS2C_ReturnToSelectRoleDlg_Ret(GS2C_ReturnToSelectRoleDlg_Ret* value);
void ReadGS2C_ReturnToSelectRoleDlg_Ret(stNetMsg& msg,GS2C_ReturnToSelectRoleDlg_Ret& value);

struct GS2C_SendPlayerDataComplete
{
	int32 mapDataId;
	int16 x;
	int16 y;
};
void WriteGS2C_SendPlayerDataComplete(stNetMsg& msg,GS2C_SendPlayerDataComplete& value);
bool OnGS2C_SendPlayerDataComplete(GS2C_SendPlayerDataComplete* value);
void ReadGS2C_SendPlayerDataComplete(stNetMsg& msg,GS2C_SendPlayerDataComplete& value);

struct C2GS_EnterMap
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_EnterMap(stNetMsg& msg,C2GS_EnterMap& value);
void ReadC2GS_EnterMap(stNetMsg& msg,C2GS_EnterMap& value);


};


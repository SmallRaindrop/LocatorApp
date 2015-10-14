
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct Friend_Info
{
	int64 playerId;
	string name;
	int32 level;
	int32 career;
	int32 sex;
	int8 online;
	int8 type;
	int8 isInTeam;
	int8 isVip;
};
void WriteFriend_Info(stNetMsg& msg,Friend_Info& value);
void ReadFriend_Info(stNetMsg& msg,Friend_Info& value);

struct GS2C_All_Friend_Info
{
	vector<Friend_Info> vec;
};
void WriteGS2C_All_Friend_Info(stNetMsg& msg,GS2C_All_Friend_Info& value);
bool OnGS2C_All_Friend_Info(GS2C_All_Friend_Info* value);
void ReadGS2C_All_Friend_Info(stNetMsg& msg,GS2C_All_Friend_Info& value);

struct GS2C_Friend_Info
{
	Friend_Info st;
};
void WriteGS2C_Friend_Info(stNetMsg& msg,GS2C_Friend_Info& value);
bool OnGS2C_Friend_Info(GS2C_Friend_Info* value);
void ReadGS2C_Friend_Info(stNetMsg& msg,GS2C_Friend_Info& value);

struct C2GS_Add_Friend
{
	int64 playerId;
	int8 type;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Add_Friend(stNetMsg& msg,C2GS_Add_Friend& value);
void ReadC2GS_Add_Friend(stNetMsg& msg,C2GS_Add_Friend& value);

struct GS2C_Add_Friend_Result
{
	int32 retCode;
};
void WriteGS2C_Add_Friend_Result(stNetMsg& msg,GS2C_Add_Friend_Result& value);
bool OnGS2C_Add_Friend_Result(GS2C_Add_Friend_Result* value);
void ReadGS2C_Add_Friend_Result(stNetMsg& msg,GS2C_Add_Friend_Result& value);

struct C2GS_Remove_Friend
{
	int64 playerId;
	int8 type;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Remove_Friend(stNetMsg& msg,C2GS_Remove_Friend& value);
void ReadC2GS_Remove_Friend(stNetMsg& msg,C2GS_Remove_Friend& value);

struct GS2C_Remove_Friend_Result
{
	int32 retCode;
	int64 playerId;
	int8 type;
};
void WriteGS2C_Remove_Friend_Result(stNetMsg& msg,GS2C_Remove_Friend_Result& value);
bool OnGS2C_Remove_Friend_Result(GS2C_Remove_Friend_Result* value);
void ReadGS2C_Remove_Friend_Result(stNetMsg& msg,GS2C_Remove_Friend_Result& value);

struct C2GS_Request_Friend_State
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Request_Friend_State(stNetMsg& msg,C2GS_Request_Friend_State& value);
void ReadC2GS_Request_Friend_State(stNetMsg& msg,C2GS_Request_Friend_State& value);

struct friend_State
{
	int64 playerId;
	int32 level;
	int8 isInTeam;
};
void Writefriend_State(stNetMsg& msg,friend_State& value);
void Readfriend_State(stNetMsg& msg,friend_State& value);

struct GS2C_Request_Friend_State_Result
{
	vector<friend_State> vec;
};
void WriteGS2C_Request_Friend_State_Result(stNetMsg& msg,GS2C_Request_Friend_State_Result& value);
bool OnGS2C_Request_Friend_State_Result(GS2C_Request_Friend_State_Result* value);
void ReadGS2C_Request_Friend_State_Result(stNetMsg& msg,GS2C_Request_Friend_State_Result& value);

struct C2GS_Palyer_Touch_List_Req
{
	vector<int64> playerList;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Palyer_Touch_List_Req(stNetMsg& msg,C2GS_Palyer_Touch_List_Req& value);
void ReadC2GS_Palyer_Touch_List_Req(stNetMsg& msg,C2GS_Palyer_Touch_List_Req& value);

struct GS2C_Palyer_Touch_List_Ret
{
	vector<Friend_Info> player_list;
};
void WriteGS2C_Palyer_Touch_List_Ret(stNetMsg& msg,GS2C_Palyer_Touch_List_Ret& value);
bool OnGS2C_Palyer_Touch_List_Ret(GS2C_Palyer_Touch_List_Ret* value);
void ReadGS2C_Palyer_Touch_List_Ret(stNetMsg& msg,GS2C_Palyer_Touch_List_Ret& value);


};


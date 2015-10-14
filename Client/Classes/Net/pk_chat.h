
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct ItemLink
{
	int8 bagType;
	int64 itemId;
};
void WriteItemLink(stNetMsg& msg,ItemLink& value);
void ReadItemLink(stNetMsg& msg,ItemLink& value);

struct C2GS_Chat
{
	int8 channelId;
	string message;
	vector<ItemLink> vec;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Chat(stNetMsg& msg,C2GS_Chat& value);
void ReadC2GS_Chat(stNetMsg& msg,C2GS_Chat& value);

struct C2GS_Private_Chat
{
	int64 playerId;
	string message;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Private_Chat(stNetMsg& msg,C2GS_Private_Chat& value);
void ReadC2GS_Private_Chat(stNetMsg& msg,C2GS_Private_Chat& value);

struct GS2C_Monster_ChatMsg
{
	int64 monsterId;
	int32 strId;
	int32 displayMs;
};
void WriteGS2C_Monster_ChatMsg(stNetMsg& msg,GS2C_Monster_ChatMsg& value);
bool OnGS2C_Monster_ChatMsg(GS2C_Monster_ChatMsg* value);
void ReadGS2C_Monster_ChatMsg(stNetMsg& msg,GS2C_Monster_ChatMsg& value);


};



#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct C2GS_RequestTrade
{
	int64 desPlayerId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_RequestTrade(stNetMsg& msg,C2GS_RequestTrade& value);
void ReadC2GS_RequestTrade(stNetMsg& msg,C2GS_RequestTrade& value);

struct GS2C_RequestTrade
{
	int64 tradeId;
	string requestName;
};
void WriteGS2C_RequestTrade(stNetMsg& msg,GS2C_RequestTrade& value);
bool OnGS2C_RequestTrade(GS2C_RequestTrade* value);
void ReadGS2C_RequestTrade(stNetMsg& msg,GS2C_RequestTrade& value);

struct C2GS_ReponseTrade
{
	int64 tradeId;
	int8 reponse;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ReponseTrade(stNetMsg& msg,C2GS_ReponseTrade& value);
void ReadC2GS_ReponseTrade(stNetMsg& msg,C2GS_ReponseTrade& value);

struct GS2C_ReponseTrade_Result
{
	int8 retCode;
	string name;
	int64 tradeId;
};
void WriteGS2C_ReponseTrade_Result(stNetMsg& msg,GS2C_ReponseTrade_Result& value);
bool OnGS2C_ReponseTrade_Result(GS2C_ReponseTrade_Result* value);
void ReadGS2C_ReponseTrade_Result(stNetMsg& msg,GS2C_ReponseTrade_Result& value);

struct GS2C_RequestTrade_Result
{
	int8 retCode;
	int64 tradeId;
};
void WriteGS2C_RequestTrade_Result(stNetMsg& msg,GS2C_RequestTrade_Result& value);
bool OnGS2C_RequestTrade_Result(GS2C_RequestTrade_Result* value);
void ReadGS2C_RequestTrade_Result(stNetMsg& msg,GS2C_RequestTrade_Result& value);

struct C2GS_CannelTrade
{
	int64 tradeId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_CannelTrade(stNetMsg& msg,C2GS_CannelTrade& value);
void ReadC2GS_CannelTrade(stNetMsg& msg,C2GS_CannelTrade& value);

struct GS2C_CannelTrade
{
	int64 playerId;
	int64 tradeId;
};
void WriteGS2C_CannelTrade(stNetMsg& msg,GS2C_CannelTrade& value);
bool OnGS2C_CannelTrade(GS2C_CannelTrade* value);
void ReadGS2C_CannelTrade(stNetMsg& msg,GS2C_CannelTrade& value);

struct tradeItem
{
	int8 bagType;
	int32 index;
	int64 itemId;
	int32 itemCnt;
};
void WritetradeItem(stNetMsg& msg,tradeItem& value);
void ReadtradeItem(stNetMsg& msg,tradeItem& value);

struct C2GS_InputItem
{
	int64 tradeId;
	int32 coin;
	vector<tradeItem> vec;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_InputItem(stNetMsg& msg,C2GS_InputItem& value);
void ReadC2GS_InputItem(stNetMsg& msg,C2GS_InputItem& value);

struct GS2C_InputItem
{
	int8 retCode;
};
void WriteGS2C_InputItem(stNetMsg& msg,GS2C_InputItem& value);
bool OnGS2C_InputItem(GS2C_InputItem* value);
void ReadGS2C_InputItem(stNetMsg& msg,GS2C_InputItem& value);

struct C2GS_LockTrade
{
	int32 coin;
	vector<tradeItem> vec;
	int64 tradeId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_LockTrade(stNetMsg& msg,C2GS_LockTrade& value);
void ReadC2GS_LockTrade(stNetMsg& msg,C2GS_LockTrade& value);

struct GS2C_LockTrade_Result
{
	int8 retCode;
	int64 tradeId;
};
void WriteGS2C_LockTrade_Result(stNetMsg& msg,GS2C_LockTrade_Result& value);
bool OnGS2C_LockTrade_Result(GS2C_LockTrade_Result* value);
void ReadGS2C_LockTrade_Result(stNetMsg& msg,GS2C_LockTrade_Result& value);

struct C2GS_StartTrade
{
	int64 tradeId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_StartTrade(stNetMsg& msg,C2GS_StartTrade& value);
void ReadC2GS_StartTrade(stNetMsg& msg,C2GS_StartTrade& value);

struct GS2C_StartTrade
{
	int8 retCode;
	int64 tradeId;
};
void WriteGS2C_StartTrade(stNetMsg& msg,GS2C_StartTrade& value);
bool OnGS2C_StartTrade(GS2C_StartTrade* value);
void ReadGS2C_StartTrade(stNetMsg& msg,GS2C_StartTrade& value);

struct C2GS_NpcShopBuy
{
	int64 npcId;
	int32 npcDataId;
	int32 itemDataId;
	int32 itemCnt;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_NpcShopBuy(stNetMsg& msg,C2GS_NpcShopBuy& value);
void ReadC2GS_NpcShopBuy(stNetMsg& msg,C2GS_NpcShopBuy& value);

struct GS2C_NpcShopBuy_Result
{
	int8 retCode;
};
void WriteGS2C_NpcShopBuy_Result(stNetMsg& msg,GS2C_NpcShopBuy_Result& value);
bool OnGS2C_NpcShopBuy_Result(GS2C_NpcShopBuy_Result* value);
void ReadGS2C_NpcShopBuy_Result(stNetMsg& msg,GS2C_NpcShopBuy_Result& value);

struct C2GS_NpcShopSell
{
	int64 itemId;
	int32 itemDataId;
	int8 bagType;
	int32 itemCnt;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_NpcShopSell(stNetMsg& msg,C2GS_NpcShopSell& value);
void ReadC2GS_NpcShopSell(stNetMsg& msg,C2GS_NpcShopSell& value);

struct GS2C_NpcShopSell_Result
{
	int8 retCode;
};
void WriteGS2C_NpcShopSell_Result(stNetMsg& msg,GS2C_NpcShopSell_Result& value);
bool OnGS2C_NpcShopSell_Result(GS2C_NpcShopSell_Result* value);
void ReadGS2C_NpcShopSell_Result(stNetMsg& msg,GS2C_NpcShopSell_Result& value);

struct C2GS_PortableShopBuy
{
	int32 itemDataId;
	int32 itemCnt;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PortableShopBuy(stNetMsg& msg,C2GS_PortableShopBuy& value);
void ReadC2GS_PortableShopBuy(stNetMsg& msg,C2GS_PortableShopBuy& value);

struct GS2C_PortableShopBuy_Result
{
	int8 retCode;
};
void WriteGS2C_PortableShopBuy_Result(stNetMsg& msg,GS2C_PortableShopBuy_Result& value);
bool OnGS2C_PortableShopBuy_Result(GS2C_PortableShopBuy_Result* value);
void ReadGS2C_PortableShopBuy_Result(stNetMsg& msg,GS2C_PortableShopBuy_Result& value);


};


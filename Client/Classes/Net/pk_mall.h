
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct mallInfo
{
	int32 id;
	int32 itemId;
	int32 item_type;
	int32 sale_type;
	int32 number;
	int32 discount;
	int32 price;
	int32 price_discount;
	int32 price_lucky;
	vector<int32> price_vip_vec;
};
void WritemallInfo(stNetMsg& msg,mallInfo& value);
void ReadmallInfo(stNetMsg& msg,mallInfo& value);

struct GS2C_MallInfo
{
	vector<mallInfo> mallVec;
};
void WriteGS2C_MallInfo(stNetMsg& msg,GS2C_MallInfo& value);
bool OnGS2C_MallInfo(GS2C_MallInfo* value);
void ReadGS2C_MallInfo(stNetMsg& msg,GS2C_MallInfo& value);

struct GS2C_MallHot9
{
	vector<int32> vec;
};
void WriteGS2C_MallHot9(stNetMsg& msg,GS2C_MallHot9& value);
bool OnGS2C_MallHot9(GS2C_MallHot9* value);
void ReadGS2C_MallHot9(stNetMsg& msg,GS2C_MallHot9& value);

struct GS2C_MallLuckyPrice
{
	vector<int32> vec;
};
void WriteGS2C_MallLuckyPrice(stNetMsg& msg,GS2C_MallLuckyPrice& value);
bool OnGS2C_MallLuckyPrice(GS2C_MallLuckyPrice* value);
void ReadGS2C_MallLuckyPrice(stNetMsg& msg,GS2C_MallLuckyPrice& value);

struct C2GS_Common_Buy
{
	int32 id;
	int32 cnt;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Common_Buy(stNetMsg& msg,C2GS_Common_Buy& value);
void ReadC2GS_Common_Buy(stNetMsg& msg,C2GS_Common_Buy& value);

struct GS2C_Common_Buy_Result
{
	int8 retCode;
};
void WriteGS2C_Common_Buy_Result(stNetMsg& msg,GS2C_Common_Buy_Result& value);
bool OnGS2C_Common_Buy_Result(GS2C_Common_Buy_Result* value);
void ReadGS2C_Common_Buy_Result(stNetMsg& msg,GS2C_Common_Buy_Result& value);

struct C2GS_Lucky_Buy
{
	int32 id;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Lucky_Buy(stNetMsg& msg,C2GS_Lucky_Buy& value);
void ReadC2GS_Lucky_Buy(stNetMsg& msg,C2GS_Lucky_Buy& value);

struct GS2C_Lucky_Buy_Result
{
	int8 retCode;
	int32 id;
};
void WriteGS2C_Lucky_Buy_Result(stNetMsg& msg,GS2C_Lucky_Buy_Result& value);
bool OnGS2C_Lucky_Buy_Result(GS2C_Lucky_Buy_Result* value);
void ReadGS2C_Lucky_Buy_Result(stNetMsg& msg,GS2C_Lucky_Buy_Result& value);

struct C2GS_Mall_Refresh
{
	int64 playerId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Mall_Refresh(stNetMsg& msg,C2GS_Mall_Refresh& value);
void ReadC2GS_Mall_Refresh(stNetMsg& msg,C2GS_Mall_Refresh& value);

struct GS2C_Mall_Refresh_Result
{
	int8 retCode;
};
void WriteGS2C_Mall_Refresh_Result(stNetMsg& msg,GS2C_Mall_Refresh_Result& value);
bool OnGS2C_Mall_Refresh_Result(GS2C_Mall_Refresh_Result* value);
void ReadGS2C_Mall_Refresh_Result(stNetMsg& msg,GS2C_Mall_Refresh_Result& value);

struct C2GS_vip_Buy
{
	int32 id;
	int32 cnt;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_vip_Buy(stNetMsg& msg,C2GS_vip_Buy& value);
void ReadC2GS_vip_Buy(stNetMsg& msg,C2GS_vip_Buy& value);

struct GS2C_vip_Buy_Result
{
	int8 retCode;
};
void WriteGS2C_vip_Buy_Result(stNetMsg& msg,GS2C_vip_Buy_Result& value);
bool OnGS2C_vip_Buy_Result(GS2C_vip_Buy_Result* value);
void ReadGS2C_vip_Buy_Result(stNetMsg& msg,GS2C_vip_Buy_Result& value);


};


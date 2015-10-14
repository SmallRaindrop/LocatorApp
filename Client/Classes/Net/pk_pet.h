
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct GS2C_PET_EXP_UPDATE
{
	int32 exp;
};
void WriteGS2C_PET_EXP_UPDATE(stNetMsg& msg,GS2C_PET_EXP_UPDATE& value);
bool OnGS2C_PET_EXP_UPDATE(GS2C_PET_EXP_UPDATE* value);
void ReadGS2C_PET_EXP_UPDATE(stNetMsg& msg,GS2C_PET_EXP_UPDATE& value);

struct C2GS_CALL_PET_Req
{
	int64 id;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_CALL_PET_Req(stNetMsg& msg,C2GS_CALL_PET_Req& value);
void ReadC2GS_CALL_PET_Req(stNetMsg& msg,C2GS_CALL_PET_Req& value);

struct GS2C_CALL_PET_Ret
{
	int64 call_id;
	int64 call_back_id;
};
void WriteGS2C_CALL_PET_Ret(stNetMsg& msg,GS2C_CALL_PET_Ret& value);
bool OnGS2C_CALL_PET_Ret(GS2C_CALL_PET_Ret* value);
void ReadGS2C_CALL_PET_Ret(stNetMsg& msg,GS2C_CALL_PET_Ret& value);

struct C2GS_CALL_BACK_PET_Req
{
	int64 id;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_CALL_BACK_PET_Req(stNetMsg& msg,C2GS_CALL_BACK_PET_Req& value);
void ReadC2GS_CALL_BACK_PET_Req(stNetMsg& msg,C2GS_CALL_BACK_PET_Req& value);

struct GS2C_CALL_BACK_PET_Ret
{
	int64 id;
};
void WriteGS2C_CALL_BACK_PET_Ret(stNetMsg& msg,GS2C_CALL_BACK_PET_Ret& value);
bool OnGS2C_CALL_BACK_PET_Ret(GS2C_CALL_BACK_PET_Ret* value);
void ReadGS2C_CALL_BACK_PET_Ret(stNetMsg& msg,GS2C_CALL_BACK_PET_Ret& value);

struct GS2C_PET_MAP_UPDATE
{
	int64 id;
	int16 level;
	int32 hp;
	int32 mp;
	int32 hp_max;
	int32 mp_max;
};
void WriteGS2C_PET_MAP_UPDATE(stNetMsg& msg,GS2C_PET_MAP_UPDATE& value);
bool OnGS2C_PET_MAP_UPDATE(GS2C_PET_MAP_UPDATE* value);
void ReadGS2C_PET_MAP_UPDATE(stNetMsg& msg,GS2C_PET_MAP_UPDATE& value);

struct C2GS_PET_STRENG_Req
{
	int64 id;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PET_STRENG_Req(stNetMsg& msg,C2GS_PET_STRENG_Req& value);
void ReadC2GS_PET_STRENG_Req(stNetMsg& msg,C2GS_PET_STRENG_Req& value);

struct GS2C_PET_STRENG_Ret
{
	int8 retCode;
};
void WriteGS2C_PET_STRENG_Ret(stNetMsg& msg,GS2C_PET_STRENG_Ret& value);
bool OnGS2C_PET_STRENG_Ret(GS2C_PET_STRENG_Ret* value);
void ReadGS2C_PET_STRENG_Ret(stNetMsg& msg,GS2C_PET_STRENG_Ret& value);

struct C2GS_PET_FEED_Req
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PET_FEED_Req(stNetMsg& msg,C2GS_PET_FEED_Req& value);
void ReadC2GS_PET_FEED_Req(stNetMsg& msg,C2GS_PET_FEED_Req& value);

struct GS2C_PET_FEED_Ret
{
	int8 retCode;
};
void WriteGS2C_PET_FEED_Ret(stNetMsg& msg,GS2C_PET_FEED_Ret& value);
bool OnGS2C_PET_FEED_Ret(GS2C_PET_FEED_Ret* value);
void ReadGS2C_PET_FEED_Ret(stNetMsg& msg,GS2C_PET_FEED_Ret& value);


};



#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct playTime
{
	int32 startTime;
	int32 endTime;
};
void WriteplayTime(stNetMsg& msg,playTime& value);
void ReadplayTime(stNetMsg& msg,playTime& value);

struct buttonBase
{
	int32 type;
	int32 id;
};
void WritebuttonBase(stNetMsg& msg,buttonBase& value);
void ReadbuttonBase(stNetMsg& msg,buttonBase& value);

struct activeCenterBaseInfo
{
	int32 id;
	int32 remainTime;
};
void WriteactiveCenterBaseInfo(stNetMsg& msg,activeCenterBaseInfo& value);
void ReadactiveCenterBaseInfo(stNetMsg& msg,activeCenterBaseInfo& value);

struct GS2C_ActiveCenterBaseInfo
{
	vector<activeCenterBaseInfo> vec;
};
void WriteGS2C_ActiveCenterBaseInfo(stNetMsg& msg,GS2C_ActiveCenterBaseInfo& value);
bool OnGS2C_ActiveCenterBaseInfo(GS2C_ActiveCenterBaseInfo* value);
void ReadGS2C_ActiveCenterBaseInfo(stNetMsg& msg,GS2C_ActiveCenterBaseInfo& value);

struct activeBaseInfo
{
	int32 id;
	int32 cnt;
	int32 completeCnt;
};
void WriteactiveBaseInfo(stNetMsg& msg,activeBaseInfo& value);
void ReadactiveBaseInfo(stNetMsg& msg,activeBaseInfo& value);

struct GS2C_InActive
{
	vector<activeBaseInfo> vec;
};
void WriteGS2C_InActive(stNetMsg& msg,GS2C_InActive& value);
bool OnGS2C_InActive(GS2C_InActive* value);
void ReadGS2C_InActive(stNetMsg& msg,GS2C_InActive& value);

struct GS2C_Guture
{
	vector<activeBaseInfo> vec;
};
void WriteGS2C_Guture(stNetMsg& msg,GS2C_Guture& value);
bool OnGS2C_Guture(GS2C_Guture* value);
void ReadGS2C_Guture(stNetMsg& msg,GS2C_Guture& value);

struct GS2C_Completed
{
	vector<activeBaseInfo> vec;
};
void WriteGS2C_Completed(stNetMsg& msg,GS2C_Completed& value);
bool OnGS2C_Completed(GS2C_Completed* value);
void ReadGS2C_Completed(stNetMsg& msg,GS2C_Completed& value);

struct GS2C_UpdateActive
{
	int32 id;
	int32 cnt;
	int32 totalCnt;
};
void WriteGS2C_UpdateActive(stNetMsg& msg,GS2C_UpdateActive& value);
bool OnGS2C_UpdateActive(GS2C_UpdateActive* value);
void ReadGS2C_UpdateActive(stNetMsg& msg,GS2C_UpdateActive& value);

struct C2GS_RequestEnterActive
{
	int32 id;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_RequestEnterActive(stNetMsg& msg,C2GS_RequestEnterActive& value);
void ReadC2GS_RequestEnterActive(stNetMsg& msg,C2GS_RequestEnterActive& value);

struct GS2C_RequestEnterActive
{
	int8 retCode;
};
void WriteGS2C_RequestEnterActive(stNetMsg& msg,GS2C_RequestEnterActive& value);
bool OnGS2C_RequestEnterActive(GS2C_RequestEnterActive* value);
void ReadGS2C_RequestEnterActive(stNetMsg& msg,GS2C_RequestEnterActive& value);

struct C2GS_OpenActiveUI
{
	int64 playerId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_OpenActiveUI(stNetMsg& msg,C2GS_OpenActiveUI& value);
void ReadC2GS_OpenActiveUI(stNetMsg& msg,C2GS_OpenActiveUI& value);

struct C2GS_LevelAward_Req
{
	int32 level;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_LevelAward_Req(stNetMsg& msg,C2GS_LevelAward_Req& value);
void ReadC2GS_LevelAward_Req(stNetMsg& msg,C2GS_LevelAward_Req& value);

struct C2GS_LoginAward_Req
{
	int32 cfgId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_LoginAward_Req(stNetMsg& msg,C2GS_LoginAward_Req& value);
void ReadC2GS_LoginAward_Req(stNetMsg& msg,C2GS_LoginAward_Req& value);


};


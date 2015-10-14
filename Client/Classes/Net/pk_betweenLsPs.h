
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct LS2PS_Register_Request
{
	int32 serverID;
	string sign;
	void Send(IOSocket* pIOSock);
};
void WriteLS2PS_Register_Request(stNetMsg& msg,LS2PS_Register_Request& value);
bool OnLS2PS_Register_Request(LS2PS_Register_Request* value);
void ReadLS2PS_Register_Request(stNetMsg& msg,LS2PS_Register_Request& value);

struct PS2LS_Register_Ret
{
	int8 retCode;
	void Send(IOSocket* pIOSock);
};
void WritePS2LS_Register_Ret(stNetMsg& msg,PS2LS_Register_Ret& value);
bool OnPS2LS_Register_Ret(PS2LS_Register_Ret* value);
void ReadPS2LS_Register_Ret(stNetMsg& msg,PS2LS_Register_Ret& value);

struct PS2LS_PayInfo_Request
{
	string orderId;
	string gameId;
	string serverId;
	int32 platformId;
	string accountId;
	string payWay;
	string amount;
	void Send(IOSocket* pIOSock);
};
void WritePS2LS_PayInfo_Request(stNetMsg& msg,PS2LS_PayInfo_Request& value);
bool OnPS2LS_PayInfo_Request(PS2LS_PayInfo_Request* value);
void ReadPS2LS_PayInfo_Request(stNetMsg& msg,PS2LS_PayInfo_Request& value);

struct LS2PS_PayInfo_Ret
{
	string orderId;
	int8 retCode;
	void Send(IOSocket* pIOSock);
};
void WriteLS2PS_PayInfo_Ret(stNetMsg& msg,LS2PS_PayInfo_Ret& value);
bool OnLS2PS_PayInfo_Ret(LS2PS_PayInfo_Ret* value);
void ReadLS2PS_PayInfo_Ret(stNetMsg& msg,LS2PS_PayInfo_Ret& value);


};


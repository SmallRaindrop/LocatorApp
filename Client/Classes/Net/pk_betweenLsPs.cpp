#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteLS2PS_Register_Request(stNetMsg& msg,LS2PS_Register_Request& value)
{
	msg << value.serverID;
	msg << value.sign;
	msg.command(MSG_LS2PS_Register_Request);
}
void LS2PS_Register_Request::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2PS_Register_Request(msg_s,*this);
	EndSend();
}
void ReadLS2PS_Register_Request(stNetMsg& msg,LS2PS_Register_Request& value)
{
	msg >> value.serverID;
	msg >> value.sign;
}
void WritePS2LS_Register_Ret(stNetMsg& msg,PS2LS_Register_Ret& value)
{
	msg << value.retCode;
	msg.command(MSG_PS2LS_Register_Ret);
}
void PS2LS_Register_Ret::Send(IOSocket* pIOSock){
	BeginSend();
	WritePS2LS_Register_Ret(msg_s,*this);
	EndSend();
}
void ReadPS2LS_Register_Ret(stNetMsg& msg,PS2LS_Register_Ret& value)
{
	msg >> value.retCode;
}
void WritePS2LS_PayInfo_Request(stNetMsg& msg,PS2LS_PayInfo_Request& value)
{
	msg << value.orderId;
	msg << value.gameId;
	msg << value.serverId;
	msg << value.platformId;
	msg << value.accountId;
	msg << value.payWay;
	msg << value.amount;
	msg.command(MSG_PS2LS_PayInfo_Request);
}
void PS2LS_PayInfo_Request::Send(IOSocket* pIOSock){
	BeginSend();
	WritePS2LS_PayInfo_Request(msg_s,*this);
	EndSend();
}
void ReadPS2LS_PayInfo_Request(stNetMsg& msg,PS2LS_PayInfo_Request& value)
{
	msg >> value.orderId;
	msg >> value.gameId;
	msg >> value.serverId;
	msg >> value.platformId;
	msg >> value.accountId;
	msg >> value.payWay;
	msg >> value.amount;
}
void WriteLS2PS_PayInfo_Ret(stNetMsg& msg,LS2PS_PayInfo_Ret& value)
{
	msg << value.orderId;
	msg << value.retCode;
	msg.command(MSG_LS2PS_PayInfo_Ret);
}
void LS2PS_PayInfo_Ret::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2PS_PayInfo_Ret(msg_s,*this);
	EndSend();
}
void ReadLS2PS_PayInfo_Ret(stNetMsg& msg,LS2PS_PayInfo_Ret& value)
{
	msg >> value.orderId;
	msg >> value.retCode;
}

};


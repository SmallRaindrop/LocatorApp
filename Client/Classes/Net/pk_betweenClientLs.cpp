#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteC2LS_Login_Test(stNetMsg& msg,C2LS_Login_Test& value)
{
	msg << value.account;
	msg << value.platformID;
	msg << value.sign;
	msg << value.deviceIMEI;
	msg << value.screenSize;
	msg << value.channelId;
	msg.command(MSG_C2LS_Login_Test);
}
void C2LS_Login_Test::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2LS_Login_Test(msg_s,*this);
	EndSend();
}
void ReadC2LS_Login_Test(stNetMsg& msg,C2LS_Login_Test& value)
{
	msg >> value.account;
	msg >> value.platformID;
	msg >> value.sign;
	msg >> value.deviceIMEI;
	msg >> value.screenSize;
	msg >> value.channelId;
}
void WriteLS2C_Login_Ret(stNetMsg& msg,LS2C_Login_Ret& value)
{
	msg << value.result;
	msg << value.userID;
	msg.command(MSG_LS2C_Login_Ret);
}
void ReadLS2C_Login_Ret(stNetMsg& msg,LS2C_Login_Ret& value)
{
	msg >> value.result;
	msg >> value.userID;
}
void WriteC2LS_RequestGameServerList(stNetMsg& msg,C2LS_RequestGameServerList& value)
{
	msg.command(MSG_C2LS_RequestGameServerList);
}
void C2LS_RequestGameServerList::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2LS_RequestGameServerList(msg_s,*this);
	EndSend();
}
void ReadC2LS_RequestGameServerList(stNetMsg& msg,C2LS_RequestGameServerList& value)
{
}
void WriteGameServerInfo(stNetMsg& msg,GameServerInfo& value)
{
	msg << value.id;
	msg << value.name;
	msg << value.status;
	msg << value.desc;
	msg << value.isExist;
	msg << value.career;
	msg << value.sex;
	msg << value.level;
	msg << value.playerName;
	msg << value.isNew;
	msg << value.regionName;
}
void ReadGameServerInfo(stNetMsg& msg,GameServerInfo& value)
{
	msg >> value.id;
	msg >> value.name;
	msg >> value.status;
	msg >> value.desc;
	msg >> value.isExist;
	msg >> value.career;
	msg >> value.sex;
	msg >> value.level;
	msg >> value.playerName;
	msg >> value.isNew;
	msg >> value.regionName;
}
void WriteLS2C_GameServerList_Ret(stNetMsg& msg,LS2C_GameServerList_Ret& value)
{
	msg << value.regionCnt;
	WriteArray(msg,GameServerInfo,value.gameServers);
	msg.command(MSG_LS2C_GameServerList_Ret);
}
void ReadLS2C_GameServerList_Ret(stNetMsg& msg,LS2C_GameServerList_Ret& value)
{
	msg >> value.regionCnt;
	ReadArray(msg,GameServerInfo,value.gameServers);
}
void WriteC2LS_RequestSelGameServer(stNetMsg& msg,C2LS_RequestSelGameServer& value)
{
	msg << value.serverID;
	msg.command(MSG_C2LS_RequestSelGameServer);
}
void C2LS_RequestSelGameServer::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2LS_RequestSelGameServer(msg_s,*this);
	EndSend();
}
void ReadC2LS_RequestSelGameServer(stNetMsg& msg,C2LS_RequestSelGameServer& value)
{
	msg >> value.serverID;
}
void WriteLS2C_SelGameServer_Ret(stNetMsg& msg,LS2C_SelGameServer_Ret& value)
{
	msg << value.retCode;
	msg << value.ip;
	msg << value.port;
	msg << value.sign;
	msg.command(MSG_LS2C_SelGameServer_Ret);
}
void ReadLS2C_SelGameServer_Ret(stNetMsg& msg,LS2C_SelGameServer_Ret& value)
{
	msg >> value.retCode;
	msg >> value.ip;
	msg >> value.port;
	msg >> value.sign;
}
void WriteC2LS_BackPreStatus(stNetMsg& msg,C2LS_BackPreStatus& value)
{
	msg.command(MSG_C2LS_BackPreStatus);
}
void C2LS_BackPreStatus::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2LS_BackPreStatus(msg_s,*this);
	EndSend();
}
void ReadC2LS_BackPreStatus(stNetMsg& msg,C2LS_BackPreStatus& value)
{
}

};


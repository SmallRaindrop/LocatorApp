#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteGS2LS_Register_Request(stNetMsg& msg,GS2LS_Register_Request& value)
{
	msg << value.serverID;
	msg << value.sign;
	msg.command(MSG_GS2LS_Register_Request);
}
void GS2LS_Register_Request::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_Register_Request(msg_s,*this);
	EndSend();
}
void ReadGS2LS_Register_Request(stNetMsg& msg,GS2LS_Register_Request& value)
{
	msg >> value.serverID;
	msg >> value.sign;
}
void WriteLS2GS_Register_Ret(stNetMsg& msg,LS2GS_Register_Ret& value)
{
	msg << value.retCode;
	msg.command(MSG_LS2GS_Register_Ret);
}
void LS2GS_Register_Ret::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2GS_Register_Ret(msg_s,*this);
	EndSend();
}
void ReadLS2GS_Register_Ret(stNetMsg& msg,LS2GS_Register_Ret& value)
{
	msg >> value.retCode;
}
void WriteLS2GS_GetPlayerInfo_Request(stNetMsg& msg,LS2GS_GetPlayerInfo_Request& value)
{
	msg << value.userID;
	msg.command(MSG_LS2GS_GetPlayerInfo_Request);
}
void LS2GS_GetPlayerInfo_Request::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2GS_GetPlayerInfo_Request(msg_s,*this);
	EndSend();
}
void ReadLS2GS_GetPlayerInfo_Request(stNetMsg& msg,LS2GS_GetPlayerInfo_Request& value)
{
	msg >> value.userID;
}
void WriteGS2LS_GetPlayerInfo_Ret(stNetMsg& msg,GS2LS_GetPlayerInfo_Ret& value)
{
	msg << value.accountID;
	msg << value.userID;
	msg << value.isExist;
	msg << value.career;
	msg << value.sex;
	msg << value.level;
	msg << value.name;
	msg.command(MSG_GS2LS_GetPlayerInfo_Ret);
}
void GS2LS_GetPlayerInfo_Ret::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_GetPlayerInfo_Ret(msg_s,*this);
	EndSend();
}
void ReadGS2LS_GetPlayerInfo_Ret(stNetMsg& msg,GS2LS_GetPlayerInfo_Ret& value)
{
	msg >> value.accountID;
	msg >> value.userID;
	msg >> value.isExist;
	msg >> value.career;
	msg >> value.sex;
	msg >> value.level;
	msg >> value.name;
}
void WriteLS2GS_UserReadyToLogin(stNetMsg& msg,LS2GS_UserReadyToLogin& value)
{
	msg << value.platId;
	msg << value.accountID;
	msg << value.account;
	msg << value.sign;
	msg.command(MSG_LS2GS_UserReadyToLogin);
}
void LS2GS_UserReadyToLogin::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2GS_UserReadyToLogin(msg_s,*this);
	EndSend();
}
void ReadLS2GS_UserReadyToLogin(stNetMsg& msg,LS2GS_UserReadyToLogin& value)
{
	msg >> value.platId;
	msg >> value.accountID;
	msg >> value.account;
	msg >> value.sign;
}
void WriteGS2LS_UserLogin(stNetMsg& msg,GS2LS_UserLogin& value)
{
	msg << value.platId;
	msg << value.accountID;
	msg << value.account;
	msg << value.sign;
	msg.command(MSG_GS2LS_UserLogin);
}
void GS2LS_UserLogin::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_UserLogin(msg_s,*this);
	EndSend();
}
void ReadGS2LS_UserLogin(stNetMsg& msg,GS2LS_UserLogin& value)
{
	msg >> value.platId;
	msg >> value.accountID;
	msg >> value.account;
	msg >> value.sign;
}
void WriteGS2LS_UserLogout(stNetMsg& msg,GS2LS_UserLogout& value)
{
	msg << value.userID;
	msg.command(MSG_GS2LS_UserLogout);
}
void GS2LS_UserLogout::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_UserLogout(msg_s,*this);
	EndSend();
}
void ReadGS2LS_UserLogout(stNetMsg& msg,GS2LS_UserLogout& value)
{
	msg >> value.userID;
}
void WriteLS2GS_UserKick(stNetMsg& msg,LS2GS_UserKick& value)
{
	msg << value.userID;
	msg.command(MSG_LS2GS_UserKick);
}
void LS2GS_UserKick::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2GS_UserKick(msg_s,*this);
	EndSend();
}
void ReadLS2GS_UserKick(stNetMsg& msg,LS2GS_UserKick& value)
{
	msg >> value.userID;
}
void WriteLS2GS_PayInfo_Request(stNetMsg& msg,LS2GS_PayInfo_Request& value)
{
	msg << value.webPid;
	msg << value.op;
	msg.command(MSG_LS2GS_PayInfo_Request);
}
void LS2GS_PayInfo_Request::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2GS_PayInfo_Request(msg_s,*this);
	EndSend();
}
void ReadLS2GS_PayInfo_Request(stNetMsg& msg,LS2GS_PayInfo_Request& value)
{
	msg >> value.webPid;
	msg >> value.op;
}
void WriteGS2LS_PayInfo_Ret(stNetMsg& msg,GS2LS_PayInfo_Ret& value)
{
	msg << value.webPid;
	msg << value.orderId;
	msg << value.retCode;
	msg.command(MSG_GS2LS_PayInfo_Ret);
}
void GS2LS_PayInfo_Ret::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_PayInfo_Ret(msg_s,*this);
	EndSend();
}
void ReadGS2LS_PayInfo_Ret(stNetMsg& msg,GS2LS_PayInfo_Ret& value)
{
	msg >> value.webPid;
	msg >> value.orderId;
	msg >> value.retCode;
}
void WriteLS2GS_GM_CMD_Request(stNetMsg& msg,LS2GS_GM_CMD_Request& value)
{
	msg << value.webPid;
	msg << value.op;
	msg.command(MSG_LS2GS_GM_CMD_Request);
}
void LS2GS_GM_CMD_Request::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2GS_GM_CMD_Request(msg_s,*this);
	EndSend();
}
void ReadLS2GS_GM_CMD_Request(stNetMsg& msg,LS2GS_GM_CMD_Request& value)
{
	msg >> value.webPid;
	msg >> value.op;
}
void WriteGS2LS_GM_CMD_Ret(stNetMsg& msg,GS2LS_GM_CMD_Ret& value)
{
	msg << value.webPid;
	msg << value.name;
	msg << value.retCode;
	msg.command(MSG_GS2LS_GM_CMD_Ret);
}
void GS2LS_GM_CMD_Ret::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_GM_CMD_Ret(msg_s,*this);
	EndSend();
}
void ReadGS2LS_GM_CMD_Ret(stNetMsg& msg,GS2LS_GM_CMD_Ret& value)
{
	msg >> value.webPid;
	msg >> value.name;
	msg >> value.retCode;
}
void WriteLS2GS_Kick_Player_Off_Request(stNetMsg& msg,LS2GS_Kick_Player_Off_Request& value)
{
	msg << value.webPid;
	msg << value.name;
	msg.command(MSG_LS2GS_Kick_Player_Off_Request);
}
void LS2GS_Kick_Player_Off_Request::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2GS_Kick_Player_Off_Request(msg_s,*this);
	EndSend();
}
void ReadLS2GS_Kick_Player_Off_Request(stNetMsg& msg,LS2GS_Kick_Player_Off_Request& value)
{
	msg >> value.webPid;
	msg >> value.name;
}
void WriteGS2LS_Kick_Player_Off_Ret(stNetMsg& msg,GS2LS_Kick_Player_Off_Ret& value)
{
	msg << value.webPid;
	msg << value.name;
	msg << value.retCode;
	msg.command(MSG_GS2LS_Kick_Player_Off_Ret);
}
void GS2LS_Kick_Player_Off_Ret::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_Kick_Player_Off_Ret(msg_s,*this);
	EndSend();
}
void ReadGS2LS_Kick_Player_Off_Ret(stNetMsg& msg,GS2LS_Kick_Player_Off_Ret& value)
{
	msg >> value.webPid;
	msg >> value.name;
	msg >> value.retCode;
}
void WriteLS2GS_Announcement_Request(stNetMsg& msg,LS2GS_Announcement_Request& value)
{
	msg << value.webPid;
	msg << value.msg;
	msg.command(MSG_LS2GS_Announcement_Request);
}
void LS2GS_Announcement_Request::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2GS_Announcement_Request(msg_s,*this);
	EndSend();
}
void ReadLS2GS_Announcement_Request(stNetMsg& msg,LS2GS_Announcement_Request& value)
{
	msg >> value.webPid;
	msg >> value.msg;
}
void WriteGS2LS_Announcement_Ret(stNetMsg& msg,GS2LS_Announcement_Ret& value)
{
	msg << value.webPid;
	msg << value.retCode;
	msg.command(MSG_GS2LS_Announcement_Ret);
}
void GS2LS_Announcement_Ret::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_Announcement_Ret(msg_s,*this);
	EndSend();
}
void ReadGS2LS_Announcement_Ret(stNetMsg& msg,GS2LS_Announcement_Ret& value)
{
	msg >> value.webPid;
	msg >> value.retCode;
}
void WriteLS2GS_control_activity_Request(stNetMsg& msg,LS2GS_control_activity_Request& value)
{
	msg << value.webPid;
	msg << value.op;
	msg.command(MSG_LS2GS_control_activity_Request);
}
void LS2GS_control_activity_Request::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2GS_control_activity_Request(msg_s,*this);
	EndSend();
}
void ReadLS2GS_control_activity_Request(stNetMsg& msg,LS2GS_control_activity_Request& value)
{
	msg >> value.webPid;
	msg >> value.op;
}
void WriteGS2LS_control_activity_Ret(stNetMsg& msg,GS2LS_control_activity_Ret& value)
{
	msg << value.webPid;
	msg << value.retCode;
	msg.command(MSG_GS2LS_control_activity_Ret);
}
void GS2LS_control_activity_Ret::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_control_activity_Ret(msg_s,*this);
	EndSend();
}
void ReadGS2LS_control_activity_Ret(stNetMsg& msg,GS2LS_control_activity_Ret& value)
{
	msg >> value.webPid;
	msg >> value.retCode;
}
void WriteGS2LS_kickOutUser(stNetMsg& msg,GS2LS_kickOutUser& value)
{
	msg << value.userId;
	msg.command(MSG_GS2LS_kickOutUser);
}
void GS2LS_kickOutUser::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_kickOutUser(msg_s,*this);
	EndSend();
}
void ReadGS2LS_kickOutUser(stNetMsg& msg,GS2LS_kickOutUser& value)
{
	msg >> value.userId;
}
void WriteGS2LS_upadateOnlinePlayerCnt(stNetMsg& msg,GS2LS_upadateOnlinePlayerCnt& value)
{
	msg << value.onlinePlayerCnt;
	msg.command(MSG_GS2LS_upadateOnlinePlayerCnt);
}
void GS2LS_upadateOnlinePlayerCnt::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_upadateOnlinePlayerCnt(msg_s,*this);
	EndSend();
}
void ReadGS2LS_upadateOnlinePlayerCnt(stNetMsg& msg,GS2LS_upadateOnlinePlayerCnt& value)
{
	msg >> value.onlinePlayerCnt;
}
void WriteLS2GS_Forbid_Chat_Request(stNetMsg& msg,LS2GS_Forbid_Chat_Request& value)
{
	msg << value.webPid;
	msg << value.name;
	msg << value.time;
	msg << value.flag;
	msg.command(MSG_LS2GS_Forbid_Chat_Request);
}
void LS2GS_Forbid_Chat_Request::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2GS_Forbid_Chat_Request(msg_s,*this);
	EndSend();
}
void ReadLS2GS_Forbid_Chat_Request(stNetMsg& msg,LS2GS_Forbid_Chat_Request& value)
{
	msg >> value.webPid;
	msg >> value.name;
	msg >> value.time;
	msg >> value.flag;
}
void WriteGS2LS_Forbid_Chat_Request_Ret(stNetMsg& msg,GS2LS_Forbid_Chat_Request_Ret& value)
{
	msg << value.webPid;
	msg << value.retCode;
	msg.command(MSG_GS2LS_Forbid_Chat_Request_Ret);
}
void GS2LS_Forbid_Chat_Request_Ret::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_Forbid_Chat_Request_Ret(msg_s,*this);
	EndSend();
}
void ReadGS2LS_Forbid_Chat_Request_Ret(stNetMsg& msg,GS2LS_Forbid_Chat_Request_Ret& value)
{
	msg >> value.webPid;
	msg >> value.retCode;
}
void WriteLS2GS_SET_GM_Request(stNetMsg& msg,LS2GS_SET_GM_Request& value)
{
	msg << value.webPid;
	msg << value.name;
	msg << value.flag;
	msg.command(MSG_LS2GS_SET_GM_Request);
}
void LS2GS_SET_GM_Request::Send(IOSocket* pIOSock){
	BeginSend();
	WriteLS2GS_SET_GM_Request(msg_s,*this);
	EndSend();
}
void ReadLS2GS_SET_GM_Request(stNetMsg& msg,LS2GS_SET_GM_Request& value)
{
	msg >> value.webPid;
	msg >> value.name;
	msg >> value.flag;
}
void WriteGS2LS_SET_GM_Request_Ret(stNetMsg& msg,GS2LS_SET_GM_Request_Ret& value)
{
	msg << value.webPid;
	msg << value.retCode;
	msg.command(MSG_GS2LS_SET_GM_Request_Ret);
}
void GS2LS_SET_GM_Request_Ret::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2LS_SET_GM_Request_Ret(msg_s,*this);
	EndSend();
}
void ReadGS2LS_SET_GM_Request_Ret(stNetMsg& msg,GS2LS_SET_GM_Request_Ret& value)
{
	msg >> value.webPid;
	msg >> value.retCode;
}

};


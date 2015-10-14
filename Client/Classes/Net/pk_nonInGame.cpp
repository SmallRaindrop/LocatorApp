#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteC2GS_Login(stNetMsg& msg,C2GS_Login& value)
{
	msg << value.accountID;
	msg << value.sign;
	msg << value.version;
	msg.command(MSG_C2GS_Login);
}
void C2GS_Login::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Login(msg_s,*this);
	EndSend();
}
void ReadC2GS_Login(stNetMsg& msg,C2GS_Login& value)
{
	msg >> value.accountID;
	msg >> value.sign;
	msg >> value.version;
}
void WriteUserPlayerData(stNetMsg& msg,UserPlayerData& value)
{
	msg << value.playerID;
	msg << value.name;
	msg << value.level;
	msg << value.career;
	msg << value.sex;
}
void ReadUserPlayerData(stNetMsg& msg,UserPlayerData& value)
{
	msg >> value.playerID;
	msg >> value.name;
	msg >> value.level;
	msg >> value.career;
	msg >> value.sex;
}
void WriteGS2C_Login_Ret(stNetMsg& msg,GS2C_Login_Ret& value)
{
	msg << value.retCode;
	WriteArray(msg,UserPlayerData,value.player_list);
	msg.command(MSG_GS2C_Login_Ret);
}
void ReadGS2C_Login_Ret(stNetMsg& msg,GS2C_Login_Ret& value)
{
	msg >> value.retCode;
	ReadArray(msg,UserPlayerData,value.player_list);
}
void WriteC2GS_CreatePlayer(stNetMsg& msg,C2GS_CreatePlayer& value)
{
	msg << value.name;
	msg << value.career;
	msg << value.sex;
	msg.command(MSG_C2GS_CreatePlayer);
}
void C2GS_CreatePlayer::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_CreatePlayer(msg_s,*this);
	EndSend();
}
void ReadC2GS_CreatePlayer(stNetMsg& msg,C2GS_CreatePlayer& value)
{
	msg >> value.name;
	msg >> value.career;
	msg >> value.sex;
}
void WriteGS2C_CreatePlayer_Ret(stNetMsg& msg,GS2C_CreatePlayer_Ret& value)
{
	msg << value.retCode;
	WriteArray(msg,UserPlayerData,value.player_list);
	msg.command(MSG_GS2C_CreatePlayer_Ret);
}
void ReadGS2C_CreatePlayer_Ret(stNetMsg& msg,GS2C_CreatePlayer_Ret& value)
{
	msg >> value.retCode;
	ReadArray(msg,UserPlayerData,value.player_list);
}
void WriteC2GS_DeletePlayer(stNetMsg& msg,C2GS_DeletePlayer& value)
{
	msg << value.playerID;
	msg.command(MSG_C2GS_DeletePlayer);
}
void C2GS_DeletePlayer::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_DeletePlayer(msg_s,*this);
	EndSend();
}
void ReadC2GS_DeletePlayer(stNetMsg& msg,C2GS_DeletePlayer& value)
{
	msg >> value.playerID;
}
void WriteGS2C_DeletePlayer_Ret(stNetMsg& msg,GS2C_DeletePlayer_Ret& value)
{
	msg << value.retCode;
	WriteArray(msg,UserPlayerData,value.player_list);
	msg.command(MSG_GS2C_DeletePlayer_Ret);
}
void ReadGS2C_DeletePlayer_Ret(stNetMsg& msg,GS2C_DeletePlayer_Ret& value)
{
	msg >> value.retCode;
	ReadArray(msg,UserPlayerData,value.player_list);
}
void WriteC2GS_EnterGame(stNetMsg& msg,C2GS_EnterGame& value)
{
	msg << value.playerID;
	msg.command(MSG_C2GS_EnterGame);
}
void C2GS_EnterGame::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_EnterGame(msg_s,*this);
	EndSend();
}
void ReadC2GS_EnterGame(stNetMsg& msg,C2GS_EnterGame& value)
{
	msg >> value.playerID;
}
void WriteGS2C_ReturnToSelectRoleDlg_Ret(stNetMsg& msg,GS2C_ReturnToSelectRoleDlg_Ret& value)
{
	msg << value.retCode;
	WriteArray(msg,UserPlayerData,value.player_list);
	msg.command(MSG_GS2C_ReturnToSelectRoleDlg_Ret);
}
void ReadGS2C_ReturnToSelectRoleDlg_Ret(stNetMsg& msg,GS2C_ReturnToSelectRoleDlg_Ret& value)
{
	msg >> value.retCode;
	ReadArray(msg,UserPlayerData,value.player_list);
}
void WriteGS2C_SendPlayerDataComplete(stNetMsg& msg,GS2C_SendPlayerDataComplete& value)
{
	msg << value.mapDataId;
	msg << value.x;
	msg << value.y;
	msg.command(MSG_GS2C_SendPlayerDataComplete);
}
void ReadGS2C_SendPlayerDataComplete(stNetMsg& msg,GS2C_SendPlayerDataComplete& value)
{
	msg >> value.mapDataId;
	msg >> value.x;
	msg >> value.y;
}
void WriteC2GS_EnterMap(stNetMsg& msg,C2GS_EnterMap& value)
{
	msg.command(MSG_C2GS_EnterMap);
}
void C2GS_EnterMap::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_EnterMap(msg_s,*this);
	EndSend();
}
void ReadC2GS_EnterMap(stNetMsg& msg,C2GS_EnterMap& value)
{
}

};


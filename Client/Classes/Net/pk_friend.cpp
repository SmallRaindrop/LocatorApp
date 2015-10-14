#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteFriend_Info(stNetMsg& msg,Friend_Info& value)
{
	msg << value.playerId;
	msg << value.name;
	msg << value.level;
	msg << value.career;
	msg << value.sex;
	msg << value.online;
	msg << value.type;
	msg << value.isInTeam;
	msg << value.isVip;
}
void ReadFriend_Info(stNetMsg& msg,Friend_Info& value)
{
	msg >> value.playerId;
	msg >> value.name;
	msg >> value.level;
	msg >> value.career;
	msg >> value.sex;
	msg >> value.online;
	msg >> value.type;
	msg >> value.isInTeam;
	msg >> value.isVip;
}
void WriteGS2C_All_Friend_Info(stNetMsg& msg,GS2C_All_Friend_Info& value)
{
	WriteArray(msg,Friend_Info,value.vec);
	msg.command(MSG_GS2C_All_Friend_Info);
}
void ReadGS2C_All_Friend_Info(stNetMsg& msg,GS2C_All_Friend_Info& value)
{
	ReadArray(msg,Friend_Info,value.vec);
}
void WriteGS2C_Friend_Info(stNetMsg& msg,GS2C_Friend_Info& value)
{
	WriteFriend_Info(msg, value.st);
	msg.command(MSG_GS2C_Friend_Info);
}
void ReadGS2C_Friend_Info(stNetMsg& msg,GS2C_Friend_Info& value)
{
	ReadFriend_Info(msg, value.st);
}
void WriteC2GS_Add_Friend(stNetMsg& msg,C2GS_Add_Friend& value)
{
	msg << value.playerId;
	msg << value.type;
	msg.command(MSG_C2GS_Add_Friend);
}
void C2GS_Add_Friend::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Add_Friend(msg_s,*this);
	EndSend();
}
void ReadC2GS_Add_Friend(stNetMsg& msg,C2GS_Add_Friend& value)
{
	msg >> value.playerId;
	msg >> value.type;
}
void WriteGS2C_Add_Friend_Result(stNetMsg& msg,GS2C_Add_Friend_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_Add_Friend_Result);
}
void ReadGS2C_Add_Friend_Result(stNetMsg& msg,GS2C_Add_Friend_Result& value)
{
	msg >> value.retCode;
}
void WriteC2GS_Remove_Friend(stNetMsg& msg,C2GS_Remove_Friend& value)
{
	msg << value.playerId;
	msg << value.type;
	msg.command(MSG_C2GS_Remove_Friend);
}
void C2GS_Remove_Friend::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Remove_Friend(msg_s,*this);
	EndSend();
}
void ReadC2GS_Remove_Friend(stNetMsg& msg,C2GS_Remove_Friend& value)
{
	msg >> value.playerId;
	msg >> value.type;
}
void WriteGS2C_Remove_Friend_Result(stNetMsg& msg,GS2C_Remove_Friend_Result& value)
{
	msg << value.retCode;
	msg << value.playerId;
	msg << value.type;
	msg.command(MSG_GS2C_Remove_Friend_Result);
}
void ReadGS2C_Remove_Friend_Result(stNetMsg& msg,GS2C_Remove_Friend_Result& value)
{
	msg >> value.retCode;
	msg >> value.playerId;
	msg >> value.type;
}
void WriteC2GS_Request_Friend_State(stNetMsg& msg,C2GS_Request_Friend_State& value)
{
	msg.command(MSG_C2GS_Request_Friend_State);
}
void C2GS_Request_Friend_State::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Request_Friend_State(msg_s,*this);
	EndSend();
}
void ReadC2GS_Request_Friend_State(stNetMsg& msg,C2GS_Request_Friend_State& value)
{
}
void Writefriend_State(stNetMsg& msg,friend_State& value)
{
	msg << value.playerId;
	msg << value.level;
	msg << value.isInTeam;
}
void Readfriend_State(stNetMsg& msg,friend_State& value)
{
	msg >> value.playerId;
	msg >> value.level;
	msg >> value.isInTeam;
}
void WriteGS2C_Request_Friend_State_Result(stNetMsg& msg,GS2C_Request_Friend_State_Result& value)
{
	WriteArray(msg,friend_State,value.vec);
	msg.command(MSG_GS2C_Request_Friend_State_Result);
}
void ReadGS2C_Request_Friend_State_Result(stNetMsg& msg,GS2C_Request_Friend_State_Result& value)
{
	ReadArray(msg,friend_State,value.vec);
}
void WriteC2GS_Palyer_Touch_List_Req(stNetMsg& msg,C2GS_Palyer_Touch_List_Req& value)
{
	msg << value.playerList;
	msg.command(MSG_C2GS_Palyer_Touch_List_Req);
}
void C2GS_Palyer_Touch_List_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Palyer_Touch_List_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_Palyer_Touch_List_Req(stNetMsg& msg,C2GS_Palyer_Touch_List_Req& value)
{
	msg >> value.playerList;
}
void WriteGS2C_Palyer_Touch_List_Ret(stNetMsg& msg,GS2C_Palyer_Touch_List_Ret& value)
{
	WriteArray(msg,Friend_Info,value.player_list);
	msg.command(MSG_GS2C_Palyer_Touch_List_Ret);
}
void ReadGS2C_Palyer_Touch_List_Ret(stNetMsg& msg,GS2C_Palyer_Touch_List_Ret& value)
{
	ReadArray(msg,Friend_Info,value.player_list);
}

};


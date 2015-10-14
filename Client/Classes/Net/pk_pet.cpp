#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteGS2C_PET_EXP_UPDATE(stNetMsg& msg,GS2C_PET_EXP_UPDATE& value)
{
	msg << value.exp;
	msg.command(MSG_GS2C_PET_EXP_UPDATE);
}
void ReadGS2C_PET_EXP_UPDATE(stNetMsg& msg,GS2C_PET_EXP_UPDATE& value)
{
	msg >> value.exp;
}
void WriteC2GS_CALL_PET_Req(stNetMsg& msg,C2GS_CALL_PET_Req& value)
{
	msg << value.id;
	msg.command(MSG_C2GS_CALL_PET_Req);
}
void C2GS_CALL_PET_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_CALL_PET_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_CALL_PET_Req(stNetMsg& msg,C2GS_CALL_PET_Req& value)
{
	msg >> value.id;
}
void WriteGS2C_CALL_PET_Ret(stNetMsg& msg,GS2C_CALL_PET_Ret& value)
{
	msg << value.call_id;
	msg << value.call_back_id;
	msg.command(MSG_GS2C_CALL_PET_Ret);
}
void ReadGS2C_CALL_PET_Ret(stNetMsg& msg,GS2C_CALL_PET_Ret& value)
{
	msg >> value.call_id;
	msg >> value.call_back_id;
}
void WriteC2GS_CALL_BACK_PET_Req(stNetMsg& msg,C2GS_CALL_BACK_PET_Req& value)
{
	msg << value.id;
	msg.command(MSG_C2GS_CALL_BACK_PET_Req);
}
void C2GS_CALL_BACK_PET_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_CALL_BACK_PET_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_CALL_BACK_PET_Req(stNetMsg& msg,C2GS_CALL_BACK_PET_Req& value)
{
	msg >> value.id;
}
void WriteGS2C_CALL_BACK_PET_Ret(stNetMsg& msg,GS2C_CALL_BACK_PET_Ret& value)
{
	msg << value.id;
	msg.command(MSG_GS2C_CALL_BACK_PET_Ret);
}
void ReadGS2C_CALL_BACK_PET_Ret(stNetMsg& msg,GS2C_CALL_BACK_PET_Ret& value)
{
	msg >> value.id;
}
void WriteGS2C_PET_MAP_UPDATE(stNetMsg& msg,GS2C_PET_MAP_UPDATE& value)
{
	msg << value.id;
	msg << value.level;
	msg << value.hp;
	msg << value.mp;
	msg << value.hp_max;
	msg << value.mp_max;
	msg.command(MSG_GS2C_PET_MAP_UPDATE);
}
void ReadGS2C_PET_MAP_UPDATE(stNetMsg& msg,GS2C_PET_MAP_UPDATE& value)
{
	msg >> value.id;
	msg >> value.level;
	msg >> value.hp;
	msg >> value.mp;
	msg >> value.hp_max;
	msg >> value.mp_max;
}
void WriteC2GS_PET_STRENG_Req(stNetMsg& msg,C2GS_PET_STRENG_Req& value)
{
	msg << value.id;
	msg.command(MSG_C2GS_PET_STRENG_Req);
}
void C2GS_PET_STRENG_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PET_STRENG_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_PET_STRENG_Req(stNetMsg& msg,C2GS_PET_STRENG_Req& value)
{
	msg >> value.id;
}
void WriteGS2C_PET_STRENG_Ret(stNetMsg& msg,GS2C_PET_STRENG_Ret& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_PET_STRENG_Ret);
}
void ReadGS2C_PET_STRENG_Ret(stNetMsg& msg,GS2C_PET_STRENG_Ret& value)
{
	msg >> value.retCode;
}
void WriteC2GS_PET_FEED_Req(stNetMsg& msg,C2GS_PET_FEED_Req& value)
{
	msg.command(MSG_C2GS_PET_FEED_Req);
}
void C2GS_PET_FEED_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PET_FEED_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_PET_FEED_Req(stNetMsg& msg,C2GS_PET_FEED_Req& value)
{
}
void WriteGS2C_PET_FEED_Ret(stNetMsg& msg,GS2C_PET_FEED_Ret& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_PET_FEED_Ret);
}
void ReadGS2C_PET_FEED_Ret(stNetMsg& msg,GS2C_PET_FEED_Ret& value)
{
	msg >> value.retCode;
}

};


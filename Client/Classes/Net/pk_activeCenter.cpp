#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteplayTime(stNetMsg& msg,playTime& value)
{
	msg << value.startTime;
	msg << value.endTime;
}
void ReadplayTime(stNetMsg& msg,playTime& value)
{
	msg >> value.startTime;
	msg >> value.endTime;
}
void WritebuttonBase(stNetMsg& msg,buttonBase& value)
{
	msg << value.type;
	msg << value.id;
}
void ReadbuttonBase(stNetMsg& msg,buttonBase& value)
{
	msg >> value.type;
	msg >> value.id;
}
void WriteactiveCenterBaseInfo(stNetMsg& msg,activeCenterBaseInfo& value)
{
	msg << value.id;
	msg << value.remainTime;
}
void ReadactiveCenterBaseInfo(stNetMsg& msg,activeCenterBaseInfo& value)
{
	msg >> value.id;
	msg >> value.remainTime;
}
void WriteGS2C_ActiveCenterBaseInfo(stNetMsg& msg,GS2C_ActiveCenterBaseInfo& value)
{
	WriteArray(msg,activeCenterBaseInfo,value.vec);
	msg.command(MSG_GS2C_ActiveCenterBaseInfo);
}
void ReadGS2C_ActiveCenterBaseInfo(stNetMsg& msg,GS2C_ActiveCenterBaseInfo& value)
{
	ReadArray(msg,activeCenterBaseInfo,value.vec);
}
void WriteactiveBaseInfo(stNetMsg& msg,activeBaseInfo& value)
{
	msg << value.id;
	msg << value.cnt;
	msg << value.completeCnt;
}
void ReadactiveBaseInfo(stNetMsg& msg,activeBaseInfo& value)
{
	msg >> value.id;
	msg >> value.cnt;
	msg >> value.completeCnt;
}
void WriteGS2C_InActive(stNetMsg& msg,GS2C_InActive& value)
{
	WriteArray(msg,activeBaseInfo,value.vec);
	msg.command(MSG_GS2C_InActive);
}
void ReadGS2C_InActive(stNetMsg& msg,GS2C_InActive& value)
{
	ReadArray(msg,activeBaseInfo,value.vec);
}
void WriteGS2C_Guture(stNetMsg& msg,GS2C_Guture& value)
{
	WriteArray(msg,activeBaseInfo,value.vec);
	msg.command(MSG_GS2C_Guture);
}
void ReadGS2C_Guture(stNetMsg& msg,GS2C_Guture& value)
{
	ReadArray(msg,activeBaseInfo,value.vec);
}
void WriteGS2C_Completed(stNetMsg& msg,GS2C_Completed& value)
{
	WriteArray(msg,activeBaseInfo,value.vec);
	msg.command(MSG_GS2C_Completed);
}
void ReadGS2C_Completed(stNetMsg& msg,GS2C_Completed& value)
{
	ReadArray(msg,activeBaseInfo,value.vec);
}
void WriteGS2C_UpdateActive(stNetMsg& msg,GS2C_UpdateActive& value)
{
	msg << value.id;
	msg << value.cnt;
	msg << value.totalCnt;
	msg.command(MSG_GS2C_UpdateActive);
}
void ReadGS2C_UpdateActive(stNetMsg& msg,GS2C_UpdateActive& value)
{
	msg >> value.id;
	msg >> value.cnt;
	msg >> value.totalCnt;
}
void WriteC2GS_RequestEnterActive(stNetMsg& msg,C2GS_RequestEnterActive& value)
{
	msg << value.id;
	msg.command(MSG_C2GS_RequestEnterActive);
}
void C2GS_RequestEnterActive::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_RequestEnterActive(msg_s,*this);
	EndSend();
}
void ReadC2GS_RequestEnterActive(stNetMsg& msg,C2GS_RequestEnterActive& value)
{
	msg >> value.id;
}
void WriteGS2C_RequestEnterActive(stNetMsg& msg,GS2C_RequestEnterActive& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_RequestEnterActive);
}
void ReadGS2C_RequestEnterActive(stNetMsg& msg,GS2C_RequestEnterActive& value)
{
	msg >> value.retCode;
}
void WriteC2GS_OpenActiveUI(stNetMsg& msg,C2GS_OpenActiveUI& value)
{
	msg << value.playerId;
	msg.command(MSG_C2GS_OpenActiveUI);
}
void C2GS_OpenActiveUI::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_OpenActiveUI(msg_s,*this);
	EndSend();
}
void ReadC2GS_OpenActiveUI(stNetMsg& msg,C2GS_OpenActiveUI& value)
{
	msg >> value.playerId;
}
void WriteC2GS_LevelAward_Req(stNetMsg& msg,C2GS_LevelAward_Req& value)
{
	msg << value.level;
	msg.command(MSG_C2GS_LevelAward_Req);
}
void C2GS_LevelAward_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_LevelAward_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_LevelAward_Req(stNetMsg& msg,C2GS_LevelAward_Req& value)
{
	msg >> value.level;
}
void WriteC2GS_LoginAward_Req(stNetMsg& msg,C2GS_LoginAward_Req& value)
{
	msg << value.cfgId;
	msg.command(MSG_C2GS_LoginAward_Req);
}
void C2GS_LoginAward_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_LoginAward_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_LoginAward_Req(stNetMsg& msg,C2GS_LoginAward_Req& value)
{
	msg >> value.cfgId;
}

};


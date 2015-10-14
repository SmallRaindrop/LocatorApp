#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteMail_Item(stNetMsg& msg,Mail_Item& value)
{
	msg << value.bagType;
	msg << value.itemId;
	msg << value.index;
	msg << value.itemCnt;
}
void ReadMail_Item(stNetMsg& msg,Mail_Item& value)
{
	msg >> value.bagType;
	msg >> value.itemId;
	msg >> value.index;
	msg >> value.itemCnt;
}
void WriteC2GS_Send_Mail(stNetMsg& msg,C2GS_Send_Mail& value)
{
	msg << value.receivePlayerId;
	msg << value.mailTitle;
	msg << value.mailContent;
	msg << value.money;
	WriteArray(msg,Mail_Item,value.vec);
	msg.command(MSG_C2GS_Send_Mail);
}
void C2GS_Send_Mail::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Send_Mail(msg_s,*this);
	EndSend();
}
void ReadC2GS_Send_Mail(stNetMsg& msg,C2GS_Send_Mail& value)
{
	msg >> value.receivePlayerId;
	msg >> value.mailTitle;
	msg >> value.mailContent;
	msg >> value.money;
	ReadArray(msg,Mail_Item,value.vec);
}
void WriteGS2C_Send_Mail_Result(stNetMsg& msg,GS2C_Send_Mail_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_Send_Mail_Result);
}
void ReadGS2C_Send_Mail_Result(stNetMsg& msg,GS2C_Send_Mail_Result& value)
{
	msg >> value.retCode;
}
void WriteC2GS_Read_Mail(stNetMsg& msg,C2GS_Read_Mail& value)
{
	msg << value.mailId;
	msg.command(MSG_C2GS_Read_Mail);
}
void C2GS_Read_Mail::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Read_Mail(msg_s,*this);
	EndSend();
}
void ReadC2GS_Read_Mail(stNetMsg& msg,C2GS_Read_Mail& value)
{
	msg >> value.mailId;
}
void WriteGS2C_Read_Mail_Result(stNetMsg& msg,GS2C_Read_Mail_Result& value)
{
	msg << value.retCode;
	msg << value.mailId;
	msg.command(MSG_GS2C_Read_Mail_Result);
}
void ReadGS2C_Read_Mail_Result(stNetMsg& msg,GS2C_Read_Mail_Result& value)
{
	msg >> value.retCode;
	msg >> value.mailId;
}
void WriteC2GS_Delete_Mail(stNetMsg& msg,C2GS_Delete_Mail& value)
{
	msg << value.mailId;
	msg.command(MSG_C2GS_Delete_Mail);
}
void C2GS_Delete_Mail::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Delete_Mail(msg_s,*this);
	EndSend();
}
void ReadC2GS_Delete_Mail(stNetMsg& msg,C2GS_Delete_Mail& value)
{
	msg >> value.mailId;
}
void WriteGS2C_Delete_Mail_Result(stNetMsg& msg,GS2C_Delete_Mail_Result& value)
{
	msg << value.retCode;
	msg << value.mailId;
	msg.command(MSG_GS2C_Delete_Mail_Result);
}
void ReadGS2C_Delete_Mail_Result(stNetMsg& msg,GS2C_Delete_Mail_Result& value)
{
	msg >> value.retCode;
	msg >> value.mailId;
}
void WriteC2GS_Delete_Mail_List(stNetMsg& msg,C2GS_Delete_Mail_List& value)
{
	msg << value.mailIdList;
	msg.command(MSG_C2GS_Delete_Mail_List);
}
void C2GS_Delete_Mail_List::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Delete_Mail_List(msg_s,*this);
	EndSend();
}
void ReadC2GS_Delete_Mail_List(stNetMsg& msg,C2GS_Delete_Mail_List& value)
{
	msg >> value.mailIdList;
}
void WriteGS2C_Delete_Mail_List_Result(stNetMsg& msg,GS2C_Delete_Mail_List_Result& value)
{
	msg << value.retCode;
	msg << value.mailIdList;
	msg.command(MSG_GS2C_Delete_Mail_List_Result);
}
void ReadGS2C_Delete_Mail_List_Result(stNetMsg& msg,GS2C_Delete_Mail_List_Result& value)
{
	msg >> value.retCode;
	msg >> value.mailIdList;
}
void WriteC2GS_Get_Attach(stNetMsg& msg,C2GS_Get_Attach& value)
{
	msg << value.mailId;
	msg.command(MSG_C2GS_Get_Attach);
}
void C2GS_Get_Attach::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Get_Attach(msg_s,*this);
	EndSend();
}
void ReadC2GS_Get_Attach(stNetMsg& msg,C2GS_Get_Attach& value)
{
	msg >> value.mailId;
}
void WriteGS2C_Get_Attach_Result(stNetMsg& msg,GS2C_Get_Attach_Result& value)
{
	msg << value.retCode;
	msg << value.mailId;
	msg.command(MSG_GS2C_Get_Attach_Result);
}
void ReadGS2C_Get_Attach_Result(stNetMsg& msg,GS2C_Get_Attach_Result& value)
{
	msg >> value.retCode;
	msg >> value.mailId;
}
void WriteC2GS_Get_Attach_List(stNetMsg& msg,C2GS_Get_Attach_List& value)
{
	msg << value.mailIdList;
	msg.command(MSG_C2GS_Get_Attach_List);
}
void C2GS_Get_Attach_List::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Get_Attach_List(msg_s,*this);
	EndSend();
}
void ReadC2GS_Get_Attach_List(stNetMsg& msg,C2GS_Get_Attach_List& value)
{
	msg >> value.mailIdList;
}
void WriteGS2C_Get_Attach_List_Result(stNetMsg& msg,GS2C_Get_Attach_List_Result& value)
{
	msg << value.retCode;
	msg << value.mailIdList;
	msg.command(MSG_GS2C_Get_Attach_List_Result);
}
void ReadGS2C_Get_Attach_List_Result(stNetMsg& msg,GS2C_Get_Attach_List_Result& value)
{
	msg >> value.retCode;
	msg >> value.mailIdList;
}

};


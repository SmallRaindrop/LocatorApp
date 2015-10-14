#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WritemallInfo(stNetMsg& msg,mallInfo& value)
{
	msg << value.id;
	msg << value.itemId;
	msg << value.item_type;
	msg << value.sale_type;
	msg << value.number;
	msg << value.discount;
	msg << value.price;
	msg << value.price_discount;
	msg << value.price_lucky;
	msg << value.price_vip_vec;
}
void ReadmallInfo(stNetMsg& msg,mallInfo& value)
{
	msg >> value.id;
	msg >> value.itemId;
	msg >> value.item_type;
	msg >> value.sale_type;
	msg >> value.number;
	msg >> value.discount;
	msg >> value.price;
	msg >> value.price_discount;
	msg >> value.price_lucky;
	msg >> value.price_vip_vec;
}
void WriteGS2C_MallInfo(stNetMsg& msg,GS2C_MallInfo& value)
{
	WriteArray(msg,mallInfo,value.mallVec);
	msg.command(MSG_GS2C_MallInfo);
}
void ReadGS2C_MallInfo(stNetMsg& msg,GS2C_MallInfo& value)
{
	ReadArray(msg,mallInfo,value.mallVec);
}
void WriteGS2C_MallHot9(stNetMsg& msg,GS2C_MallHot9& value)
{
	msg << value.vec;
	msg.command(MSG_GS2C_MallHot9);
}
void ReadGS2C_MallHot9(stNetMsg& msg,GS2C_MallHot9& value)
{
	msg >> value.vec;
}
void WriteGS2C_MallLuckyPrice(stNetMsg& msg,GS2C_MallLuckyPrice& value)
{
	msg << value.vec;
	msg.command(MSG_GS2C_MallLuckyPrice);
}
void ReadGS2C_MallLuckyPrice(stNetMsg& msg,GS2C_MallLuckyPrice& value)
{
	msg >> value.vec;
}
void WriteC2GS_Common_Buy(stNetMsg& msg,C2GS_Common_Buy& value)
{
	msg << value.id;
	msg << value.cnt;
	msg.command(MSG_C2GS_Common_Buy);
}
void C2GS_Common_Buy::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Common_Buy(msg_s,*this);
	EndSend();
}
void ReadC2GS_Common_Buy(stNetMsg& msg,C2GS_Common_Buy& value)
{
	msg >> value.id;
	msg >> value.cnt;
}
void WriteGS2C_Common_Buy_Result(stNetMsg& msg,GS2C_Common_Buy_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_Common_Buy_Result);
}
void ReadGS2C_Common_Buy_Result(stNetMsg& msg,GS2C_Common_Buy_Result& value)
{
	msg >> value.retCode;
}
void WriteC2GS_Lucky_Buy(stNetMsg& msg,C2GS_Lucky_Buy& value)
{
	msg << value.id;
	msg.command(MSG_C2GS_Lucky_Buy);
}
void C2GS_Lucky_Buy::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Lucky_Buy(msg_s,*this);
	EndSend();
}
void ReadC2GS_Lucky_Buy(stNetMsg& msg,C2GS_Lucky_Buy& value)
{
	msg >> value.id;
}
void WriteGS2C_Lucky_Buy_Result(stNetMsg& msg,GS2C_Lucky_Buy_Result& value)
{
	msg << value.retCode;
	msg << value.id;
	msg.command(MSG_GS2C_Lucky_Buy_Result);
}
void ReadGS2C_Lucky_Buy_Result(stNetMsg& msg,GS2C_Lucky_Buy_Result& value)
{
	msg >> value.retCode;
	msg >> value.id;
}
void WriteC2GS_Mall_Refresh(stNetMsg& msg,C2GS_Mall_Refresh& value)
{
	msg << value.playerId;
	msg.command(MSG_C2GS_Mall_Refresh);
}
void C2GS_Mall_Refresh::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Mall_Refresh(msg_s,*this);
	EndSend();
}
void ReadC2GS_Mall_Refresh(stNetMsg& msg,C2GS_Mall_Refresh& value)
{
	msg >> value.playerId;
}
void WriteGS2C_Mall_Refresh_Result(stNetMsg& msg,GS2C_Mall_Refresh_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_Mall_Refresh_Result);
}
void ReadGS2C_Mall_Refresh_Result(stNetMsg& msg,GS2C_Mall_Refresh_Result& value)
{
	msg >> value.retCode;
}
void WriteC2GS_vip_Buy(stNetMsg& msg,C2GS_vip_Buy& value)
{
	msg << value.id;
	msg << value.cnt;
	msg.command(MSG_C2GS_vip_Buy);
}
void C2GS_vip_Buy::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_vip_Buy(msg_s,*this);
	EndSend();
}
void ReadC2GS_vip_Buy(stNetMsg& msg,C2GS_vip_Buy& value)
{
	msg >> value.id;
	msg >> value.cnt;
}
void WriteGS2C_vip_Buy_Result(stNetMsg& msg,GS2C_vip_Buy_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_vip_Buy_Result);
}
void ReadGS2C_vip_Buy_Result(stNetMsg& msg,GS2C_vip_Buy_Result& value)
{
	msg >> value.retCode;
}

};


#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteC2GS_RequestTrade(stNetMsg& msg,C2GS_RequestTrade& value)
{
	msg << value.desPlayerId;
	msg.command(MSG_C2GS_RequestTrade);
}
void C2GS_RequestTrade::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_RequestTrade(msg_s,*this);
	EndSend();
}
void ReadC2GS_RequestTrade(stNetMsg& msg,C2GS_RequestTrade& value)
{
	msg >> value.desPlayerId;
}
void WriteGS2C_RequestTrade(stNetMsg& msg,GS2C_RequestTrade& value)
{
	msg << value.tradeId;
	msg << value.requestName;
	msg.command(MSG_GS2C_RequestTrade);
}
void ReadGS2C_RequestTrade(stNetMsg& msg,GS2C_RequestTrade& value)
{
	msg >> value.tradeId;
	msg >> value.requestName;
}
void WriteC2GS_ReponseTrade(stNetMsg& msg,C2GS_ReponseTrade& value)
{
	msg << value.tradeId;
	msg << value.reponse;
	msg.command(MSG_C2GS_ReponseTrade);
}
void C2GS_ReponseTrade::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ReponseTrade(msg_s,*this);
	EndSend();
}
void ReadC2GS_ReponseTrade(stNetMsg& msg,C2GS_ReponseTrade& value)
{
	msg >> value.tradeId;
	msg >> value.reponse;
}
void WriteGS2C_ReponseTrade_Result(stNetMsg& msg,GS2C_ReponseTrade_Result& value)
{
	msg << value.retCode;
	msg << value.name;
	msg << value.tradeId;
	msg.command(MSG_GS2C_ReponseTrade_Result);
}
void ReadGS2C_ReponseTrade_Result(stNetMsg& msg,GS2C_ReponseTrade_Result& value)
{
	msg >> value.retCode;
	msg >> value.name;
	msg >> value.tradeId;
}
void WriteGS2C_RequestTrade_Result(stNetMsg& msg,GS2C_RequestTrade_Result& value)
{
	msg << value.retCode;
	msg << value.tradeId;
	msg.command(MSG_GS2C_RequestTrade_Result);
}
void ReadGS2C_RequestTrade_Result(stNetMsg& msg,GS2C_RequestTrade_Result& value)
{
	msg >> value.retCode;
	msg >> value.tradeId;
}
void WriteC2GS_CannelTrade(stNetMsg& msg,C2GS_CannelTrade& value)
{
	msg << value.tradeId;
	msg.command(MSG_C2GS_CannelTrade);
}
void C2GS_CannelTrade::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_CannelTrade(msg_s,*this);
	EndSend();
}
void ReadC2GS_CannelTrade(stNetMsg& msg,C2GS_CannelTrade& value)
{
	msg >> value.tradeId;
}
void WriteGS2C_CannelTrade(stNetMsg& msg,GS2C_CannelTrade& value)
{
	msg << value.playerId;
	msg << value.tradeId;
	msg.command(MSG_GS2C_CannelTrade);
}
void ReadGS2C_CannelTrade(stNetMsg& msg,GS2C_CannelTrade& value)
{
	msg >> value.playerId;
	msg >> value.tradeId;
}
void WritetradeItem(stNetMsg& msg,tradeItem& value)
{
	msg << value.bagType;
	msg << value.index;
	msg << value.itemId;
	msg << value.itemCnt;
}
void ReadtradeItem(stNetMsg& msg,tradeItem& value)
{
	msg >> value.bagType;
	msg >> value.index;
	msg >> value.itemId;
	msg >> value.itemCnt;
}
void WriteC2GS_InputItem(stNetMsg& msg,C2GS_InputItem& value)
{
	msg << value.tradeId;
	msg << value.coin;
	WriteArray(msg,tradeItem,value.vec);
	msg.command(MSG_C2GS_InputItem);
}
void C2GS_InputItem::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_InputItem(msg_s,*this);
	EndSend();
}
void ReadC2GS_InputItem(stNetMsg& msg,C2GS_InputItem& value)
{
	msg >> value.tradeId;
	msg >> value.coin;
	ReadArray(msg,tradeItem,value.vec);
}
void WriteGS2C_InputItem(stNetMsg& msg,GS2C_InputItem& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_InputItem);
}
void ReadGS2C_InputItem(stNetMsg& msg,GS2C_InputItem& value)
{
	msg >> value.retCode;
}
void WriteC2GS_LockTrade(stNetMsg& msg,C2GS_LockTrade& value)
{
	msg << value.coin;
	WriteArray(msg,tradeItem,value.vec);
	msg << value.tradeId;
	msg.command(MSG_C2GS_LockTrade);
}
void C2GS_LockTrade::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_LockTrade(msg_s,*this);
	EndSend();
}
void ReadC2GS_LockTrade(stNetMsg& msg,C2GS_LockTrade& value)
{
	msg >> value.coin;
	ReadArray(msg,tradeItem,value.vec);
	msg >> value.tradeId;
}
void WriteGS2C_LockTrade_Result(stNetMsg& msg,GS2C_LockTrade_Result& value)
{
	msg << value.retCode;
	msg << value.tradeId;
	msg.command(MSG_GS2C_LockTrade_Result);
}
void ReadGS2C_LockTrade_Result(stNetMsg& msg,GS2C_LockTrade_Result& value)
{
	msg >> value.retCode;
	msg >> value.tradeId;
}
void WriteC2GS_StartTrade(stNetMsg& msg,C2GS_StartTrade& value)
{
	msg << value.tradeId;
	msg.command(MSG_C2GS_StartTrade);
}
void C2GS_StartTrade::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_StartTrade(msg_s,*this);
	EndSend();
}
void ReadC2GS_StartTrade(stNetMsg& msg,C2GS_StartTrade& value)
{
	msg >> value.tradeId;
}
void WriteGS2C_StartTrade(stNetMsg& msg,GS2C_StartTrade& value)
{
	msg << value.retCode;
	msg << value.tradeId;
	msg.command(MSG_GS2C_StartTrade);
}
void ReadGS2C_StartTrade(stNetMsg& msg,GS2C_StartTrade& value)
{
	msg >> value.retCode;
	msg >> value.tradeId;
}
void WriteC2GS_NpcShopBuy(stNetMsg& msg,C2GS_NpcShopBuy& value)
{
	msg << value.npcId;
	msg << value.npcDataId;
	msg << value.itemDataId;
	msg << value.itemCnt;
	msg.command(MSG_C2GS_NpcShopBuy);
}
void C2GS_NpcShopBuy::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_NpcShopBuy(msg_s,*this);
	EndSend();
}
void ReadC2GS_NpcShopBuy(stNetMsg& msg,C2GS_NpcShopBuy& value)
{
	msg >> value.npcId;
	msg >> value.npcDataId;
	msg >> value.itemDataId;
	msg >> value.itemCnt;
}
void WriteGS2C_NpcShopBuy_Result(stNetMsg& msg,GS2C_NpcShopBuy_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_NpcShopBuy_Result);
}
void ReadGS2C_NpcShopBuy_Result(stNetMsg& msg,GS2C_NpcShopBuy_Result& value)
{
	msg >> value.retCode;
}
void WriteC2GS_NpcShopSell(stNetMsg& msg,C2GS_NpcShopSell& value)
{
	msg << value.itemId;
	msg << value.itemDataId;
	msg << value.bagType;
	msg << value.itemCnt;
	msg.command(MSG_C2GS_NpcShopSell);
}
void C2GS_NpcShopSell::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_NpcShopSell(msg_s,*this);
	EndSend();
}
void ReadC2GS_NpcShopSell(stNetMsg& msg,C2GS_NpcShopSell& value)
{
	msg >> value.itemId;
	msg >> value.itemDataId;
	msg >> value.bagType;
	msg >> value.itemCnt;
}
void WriteGS2C_NpcShopSell_Result(stNetMsg& msg,GS2C_NpcShopSell_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_NpcShopSell_Result);
}
void ReadGS2C_NpcShopSell_Result(stNetMsg& msg,GS2C_NpcShopSell_Result& value)
{
	msg >> value.retCode;
}
void WriteC2GS_PortableShopBuy(stNetMsg& msg,C2GS_PortableShopBuy& value)
{
	msg << value.itemDataId;
	msg << value.itemCnt;
	msg.command(MSG_C2GS_PortableShopBuy);
}
void C2GS_PortableShopBuy::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PortableShopBuy(msg_s,*this);
	EndSend();
}
void ReadC2GS_PortableShopBuy(stNetMsg& msg,C2GS_PortableShopBuy& value)
{
	msg >> value.itemDataId;
	msg >> value.itemCnt;
}
void WriteGS2C_PortableShopBuy_Result(stNetMsg& msg,GS2C_PortableShopBuy_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_PortableShopBuy_Result);
}
void ReadGS2C_PortableShopBuy_Result(stNetMsg& msg,GS2C_PortableShopBuy_Result& value)
{
	msg >> value.retCode;
}

};


#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WritesaleItem(stNetMsg& msg,saleItem& value)
{
	msg << value.bagType;
	msg << value.index;
	msg << value.itemId;
	msg << value.itemCnt;
}
void ReadsaleItem(stNetMsg& msg,saleItem& value)
{
	msg >> value.bagType;
	msg >> value.index;
	msg >> value.itemId;
	msg >> value.itemCnt;
}
void WriteC2GS_PutOnItem(stNetMsg& msg,C2GS_PutOnItem& value)
{
	WritesaleItem(msg, value.item);
	msg << value.npcId;
	msg << value.npcDataId;
	msg << value.price;
	msg.command(MSG_C2GS_PutOnItem);
}
void C2GS_PutOnItem::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PutOnItem(msg_s,*this);
	EndSend();
}
void ReadC2GS_PutOnItem(stNetMsg& msg,C2GS_PutOnItem& value)
{
	ReadsaleItem(msg, value.item);
	msg >> value.npcId;
	msg >> value.npcDataId;
	msg >> value.price;
}
void WriteC2GS_PutOnGold(stNetMsg& msg,C2GS_PutOnGold& value)
{
	msg << value.npcId;
	msg << value.npcDataId;
	msg << value.price;
	msg << value.goldType;
	msg.command(MSG_C2GS_PutOnGold);
}
void C2GS_PutOnGold::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PutOnGold(msg_s,*this);
	EndSend();
}
void ReadC2GS_PutOnGold(stNetMsg& msg,C2GS_PutOnGold& value)
{
	msg >> value.npcId;
	msg >> value.npcDataId;
	msg >> value.price;
	msg >> value.goldType;
}
void WriteGS2C_PutOnGold_Result(stNetMsg& msg,GS2C_PutOnGold_Result& value)
{
	msg << value.retCode;
	msg << value.saleId;
	msg << value.goldType;
	msg.command(MSG_GS2C_PutOnGold_Result);
}
void ReadGS2C_PutOnGold_Result(stNetMsg& msg,GS2C_PutOnGold_Result& value)
{
	msg >> value.retCode;
	msg >> value.saleId;
	msg >> value.goldType;
}
void WriteC2GS_TakeDown(stNetMsg& msg,C2GS_TakeDown& value)
{
	msg << value.saleId;
	msg.command(MSG_C2GS_TakeDown);
}
void C2GS_TakeDown::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_TakeDown(msg_s,*this);
	EndSend();
}
void ReadC2GS_TakeDown(stNetMsg& msg,C2GS_TakeDown& value)
{
	msg >> value.saleId;
}
void WriteGS2C_TakeDown_Result(stNetMsg& msg,GS2C_TakeDown_Result& value)
{
	msg << value.retCode;
	msg << value.saleId;
	msg.command(MSG_GS2C_TakeDown_Result);
}
void ReadGS2C_TakeDown_Result(stNetMsg& msg,GS2C_TakeDown_Result& value)
{
	msg >> value.retCode;
	msg >> value.saleId;
}
void WriteC2GS_Buy(stNetMsg& msg,C2GS_Buy& value)
{
	msg << value.saleId;
	msg.command(MSG_C2GS_Buy);
}
void C2GS_Buy::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Buy(msg_s,*this);
	EndSend();
}
void ReadC2GS_Buy(stNetMsg& msg,C2GS_Buy& value)
{
	msg >> value.saleId;
}
void WriteGS2C_Buy(stNetMsg& msg,GS2C_Buy& value)
{
	msg << value.saleId;
	msg << value.buyPlayerId;
	msg << value.buyPlayerName;
	msg.command(MSG_GS2C_Buy);
}
void ReadGS2C_Buy(stNetMsg& msg,GS2C_Buy& value)
{
	msg >> value.saleId;
	msg >> value.buyPlayerId;
	msg >> value.buyPlayerName;
}
void WriteGS2C_Buy_Result(stNetMsg& msg,GS2C_Buy_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_Buy_Result);
}
void ReadGS2C_Buy_Result(stNetMsg& msg,GS2C_Buy_Result& value)
{
	msg >> value.retCode;
}
void WriteC2GS_Filter_Item(stNetMsg& msg,C2GS_Filter_Item& value)
{
	msg << value.sub_type;
	msg << value.carrer;
	msg << value.grade;
	msg << value.quality;
	msg.command(MSG_C2GS_Filter_Item);
}
void C2GS_Filter_Item::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Filter_Item(msg_s,*this);
	EndSend();
}
void ReadC2GS_Filter_Item(stNetMsg& msg,C2GS_Filter_Item& value)
{
	msg >> value.sub_type;
	msg >> value.carrer;
	msg >> value.grade;
	msg >> value.quality;
}
void WriteC2GS_Filter_Item_Next_Page(stNetMsg& msg,C2GS_Filter_Item_Next_Page& value)
{
	msg << value.page;
	msg.command(MSG_C2GS_Filter_Item_Next_Page);
}
void C2GS_Filter_Item_Next_Page::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Filter_Item_Next_Page(msg_s,*this);
	EndSend();
}
void ReadC2GS_Filter_Item_Next_Page(stNetMsg& msg,C2GS_Filter_Item_Next_Page& value)
{
	msg >> value.page;
}
void WriteC2GS_Filter_Gold(stNetMsg& msg,C2GS_Filter_Gold& value)
{
	msg << value.goldType;
	msg.command(MSG_C2GS_Filter_Gold);
}
void C2GS_Filter_Gold::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Filter_Gold(msg_s,*this);
	EndSend();
}
void ReadC2GS_Filter_Gold(stNetMsg& msg,C2GS_Filter_Gold& value)
{
	msg >> value.goldType;
}
void WriteC2GS_Filter_Gold_Next_Page(stNetMsg& msg,C2GS_Filter_Gold_Next_Page& value)
{
	msg << value.page;
	msg.command(MSG_C2GS_Filter_Gold_Next_Page);
}
void C2GS_Filter_Gold_Next_Page::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Filter_Gold_Next_Page(msg_s,*this);
	EndSend();
}
void ReadC2GS_Filter_Gold_Next_Page(stNetMsg& msg,C2GS_Filter_Gold_Next_Page& value)
{
	msg >> value.page;
}
void Writesale_filter_gold(stNetMsg& msg,sale_filter_gold& value)
{
	msg << value.price;
	msg << value.goldType;
	msg << value.saleId;
}
void Readsale_filter_gold(stNetMsg& msg,sale_filter_gold& value)
{
	msg >> value.price;
	msg >> value.goldType;
	msg >> value.saleId;
}
void WriteGS2C_Filter_Gold_Result(stNetMsg& msg,GS2C_Filter_Gold_Result& value)
{
	msg << value.isNextPage;
	msg << value.totalPage;
	WriteArray(msg,sale_filter_gold,value.saleVec);
	msg.command(MSG_GS2C_Filter_Gold_Result);
}
void ReadGS2C_Filter_Gold_Result(stNetMsg& msg,GS2C_Filter_Gold_Result& value)
{
	msg >> value.isNextPage;
	msg >> value.totalPage;
	ReadArray(msg,sale_filter_gold,value.saleVec);
}
void WriteC2GS_Find_Item(stNetMsg& msg,C2GS_Find_Item& value)
{
	msg << value.itemName;
	msg.command(MSG_C2GS_Find_Item);
}
void C2GS_Find_Item::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Find_Item(msg_s,*this);
	EndSend();
}
void ReadC2GS_Find_Item(stNetMsg& msg,C2GS_Find_Item& value)
{
	msg >> value.itemName;
}
void WriteC2GS_Find_Item_Next_Page(stNetMsg& msg,C2GS_Find_Item_Next_Page& value)
{
	msg << value.page;
	msg.command(MSG_C2GS_Find_Item_Next_Page);
}
void C2GS_Find_Item_Next_Page::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Find_Item_Next_Page(msg_s,*this);
	EndSend();
}
void ReadC2GS_Find_Item_Next_Page(stNetMsg& msg,C2GS_Find_Item_Next_Page& value)
{
	msg >> value.page;
}
void WriteGS2C_Delete_Sale(stNetMsg& msg,GS2C_Delete_Sale& value)
{
	msg << value.saleId;
	msg.command(MSG_GS2C_Delete_Sale);
}
void ReadGS2C_Delete_Sale(stNetMsg& msg,GS2C_Delete_Sale& value)
{
	msg >> value.saleId;
}

};


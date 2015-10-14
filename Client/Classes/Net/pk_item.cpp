#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteEquipTianshuDetail(stNetMsg& msg,EquipTianshuDetail& value)
{
	msg << value.solt;
	msg << value.tianShuDataId;
	msg << value.tianShuLv;
}
void ReadEquipTianshuDetail(stNetMsg& msg,EquipTianshuDetail& value)
{
	msg >> value.solt;
	msg >> value.tianShuDataId;
	msg >> value.tianShuLv;
}
void WriteEquipTianshu(stNetMsg& msg,EquipTianshu& value)
{
	msg << value.index;
	WriteArray(msg,EquipTianshuDetail,value.tianShuList);
}
void ReadEquipTianshu(stNetMsg& msg,EquipTianshu& value)
{
	msg >> value.index;
	ReadArray(msg,EquipTianshuDetail,value.tianShuList);
}
void WriteTianshuSoltStreng(stNetMsg& msg,TianshuSoltStreng& value)
{
	msg << value.solt;
	msg << value.strengLv;
}
void ReadTianshuSoltStreng(stNetMsg& msg,TianshuSoltStreng& value)
{
	msg >> value.solt;
	msg >> value.strengLv;
}
void WriteEquipItem(stNetMsg& msg,EquipItem& value)
{
	msg << value.part;
	msg << value.id;
	msg << value.isBind;
	msg << value.equipDataId;
	msg << value.refineLevel;
	msg << value.enhanceLevel;
	msg << value.score;
	WriteArray(msg,EquipTianshu,value.tianShuList);
	msg << value.content_lv;
	WriteArray(msg,TianshuSoltStreng,value.soltStrengList);
	msg << value.tian_shu_use_index;
}
void ReadEquipItem(stNetMsg& msg,EquipItem& value)
{
	msg >> value.part;
	msg >> value.id;
	msg >> value.isBind;
	msg >> value.equipDataId;
	msg >> value.refineLevel;
	msg >> value.enhanceLevel;
	msg >> value.score;
	ReadArray(msg,EquipTianshu,value.tianShuList);
	msg >> value.content_lv;
	ReadArray(msg,TianshuSoltStreng,value.soltStrengList);
	msg >> value.tian_shu_use_index;
}
void WriteGS2C_EquipGetItem_Ret(stNetMsg& msg,GS2C_EquipGetItem_Ret& value)
{
	WriteArray(msg,EquipItem,value.equipItems);
	msg.command(MSG_GS2C_EquipGetItem_Ret);
}
void ReadGS2C_EquipGetItem_Ret(stNetMsg& msg,GS2C_EquipGetItem_Ret& value)
{
	ReadArray(msg,EquipItem,value.equipItems);
}
void WriteC2GS_EquipItem(stNetMsg& msg,C2GS_EquipItem& value)
{
	msg << value.index;
	msg << value.part;
	msg.command(MSG_C2GS_EquipItem);
}
void C2GS_EquipItem::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_EquipItem(msg_s,*this);
	EndSend();
}
void ReadC2GS_EquipItem(stNetMsg& msg,C2GS_EquipItem& value)
{
	msg >> value.index;
	msg >> value.part;
}
void WriteC2GS_UnequipItem(stNetMsg& msg,C2GS_UnequipItem& value)
{
	msg << value.part;
	msg.command(MSG_C2GS_UnequipItem);
}
void C2GS_UnequipItem::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_UnequipItem(msg_s,*this);
	EndSend();
}
void ReadC2GS_UnequipItem(stNetMsg& msg,C2GS_UnequipItem& value)
{
	msg >> value.part;
}
void WriteGS2C_EquipExchangeRet(stNetMsg& msg,GS2C_EquipExchangeRet& value)
{
	msg << value.isEquip;
	msg << value.part;
	msg << value.index;
	msg.command(MSG_GS2C_EquipExchangeRet);
}
void ReadGS2C_EquipExchangeRet(stNetMsg& msg,GS2C_EquipExchangeRet& value)
{
	msg >> value.isEquip;
	msg >> value.part;
	msg >> value.index;
}
void WriteC2GS_BagGetItems(stNetMsg& msg,C2GS_BagGetItems& value)
{
	msg << value.bagType;
	msg.command(MSG_C2GS_BagGetItems);
}
void C2GS_BagGetItems::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_BagGetItems(msg_s,*this);
	EndSend();
}
void ReadC2GS_BagGetItems(stNetMsg& msg,C2GS_BagGetItems& value)
{
	msg >> value.bagType;
}
void WriteTianShuSet(stNetMsg& msg,TianShuSet& value)
{
	msg << value.id;
	msg << value.type;
	msg << value.index;
}
void ReadTianShuSet(stNetMsg& msg,TianShuSet& value)
{
	msg >> value.id;
	msg >> value.type;
	msg >> value.index;
}
void WriteBagItem(stNetMsg& msg,BagItem& value)
{
	msg << value.index;
	msg << value.id;
	msg << value.itemDataId;
	msg << value.count;
	msg << value.isBind;
	msg << value.strengthenLevel;
	msg << value.refineLevel;
	msg << value.enhanceLevel;
	msg << value.score;
	WriteArray(msg,EquipTianshu,value.tianShuList);
	msg << value.content_lv;
	WriteArray(msg,TianshuSoltStreng,value.soltStrengList);
	msg << value.tian_shu_exp;
	WriteArray(msg,TianShuSet,value.tian_shu_set_list);
}
void ReadBagItem(stNetMsg& msg,BagItem& value)
{
	msg >> value.index;
	msg >> value.id;
	msg >> value.itemDataId;
	msg >> value.count;
	msg >> value.isBind;
	msg >> value.strengthenLevel;
	msg >> value.refineLevel;
	msg >> value.enhanceLevel;
	msg >> value.score;
	ReadArray(msg,EquipTianshu,value.tianShuList);
	msg >> value.content_lv;
	ReadArray(msg,TianshuSoltStreng,value.soltStrengList);
	msg >> value.tian_shu_exp;
	ReadArray(msg,TianShuSet,value.tian_shu_set_list);
}
void WriteGS2C_BagGetItems_Ret(stNetMsg& msg,GS2C_BagGetItems_Ret& value)
{
	msg << value.bagType;
	msg << value.bagGridNum;
	WriteArray(msg,BagItem,value.getBagItems);
	msg.command(MSG_GS2C_BagGetItems_Ret);
}
void ReadGS2C_BagGetItems_Ret(stNetMsg& msg,GS2C_BagGetItems_Ret& value)
{
	msg >> value.bagType;
	msg >> value.bagGridNum;
	ReadArray(msg,BagItem,value.getBagItems);
}
void WriteGS2C_BagAddItem(stNetMsg& msg,GS2C_BagAddItem& value)
{
	msg << value.bagType;
	msg << value.reason;
	WriteBagItem(msg, value.addItem);
	msg.command(MSG_GS2C_BagAddItem);
}
void ReadGS2C_BagAddItem(stNetMsg& msg,GS2C_BagAddItem& value)
{
	msg >> value.bagType;
	msg >> value.reason;
	ReadBagItem(msg, value.addItem);
}
void WriteGS2C_ItemCntChange(stNetMsg& msg,GS2C_ItemCntChange& value)
{
	msg << value.bagType;
	msg << value.index;
	msg << value.newCount;
	msg << value.oldCount;
	msg.command(MSG_GS2C_ItemCntChange);
}
void ReadGS2C_ItemCntChange(stNetMsg& msg,GS2C_ItemCntChange& value)
{
	msg >> value.bagType;
	msg >> value.index;
	msg >> value.newCount;
	msg >> value.oldCount;
}
void WriteGSWithC_BagDeleteItems(stNetMsg& msg,GSWithC_BagDeleteItems& value)
{
	msg << value.bagType;
	msg << value.indexs;
	msg.command(MSG_GSWithC_BagDeleteItems);
}
void GSWithC_BagDeleteItems::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGSWithC_BagDeleteItems(msg_s,*this);
	EndSend();
}
void ReadGSWithC_BagDeleteItems(stNetMsg& msg,GSWithC_BagDeleteItems& value)
{
	msg >> value.bagType;
	msg >> value.indexs;
}
void WriteGSWithC_ExchangeBagItem(stNetMsg& msg,GSWithC_ExchangeBagItem& value)
{
	msg << value.bagType;
	msg << value.index1;
	msg << value.index2;
	msg.command(MSG_GSWithC_ExchangeBagItem);
}
void GSWithC_ExchangeBagItem::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGSWithC_ExchangeBagItem(msg_s,*this);
	EndSend();
}
void ReadGSWithC_ExchangeBagItem(stNetMsg& msg,GSWithC_ExchangeBagItem& value)
{
	msg >> value.bagType;
	msg >> value.index1;
	msg >> value.index2;
}
void WriteC2GS_BagSort(stNetMsg& msg,C2GS_BagSort& value)
{
	msg << value.bagType;
	msg.command(MSG_C2GS_BagSort);
}
void C2GS_BagSort::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_BagSort(msg_s,*this);
	EndSend();
}
void ReadC2GS_BagSort(stNetMsg& msg,C2GS_BagSort& value)
{
	msg >> value.bagType;
}
void WriteGS2C_SignalItemInfo(stNetMsg& msg,GS2C_SignalItemInfo& value)
{
	msg << value.id;
	msg << value.itemDataId;
	msg << value.count;
	msg << value.isBind;
	msg << value.refineLevel;
	msg << value.enhanceLevel;
	msg << value.score;
	msg.command(MSG_GS2C_SignalItemInfo);
}
void ReadGS2C_SignalItemInfo(stNetMsg& msg,GS2C_SignalItemInfo& value)
{
	msg >> value.id;
	msg >> value.itemDataId;
	msg >> value.count;
	msg >> value.isBind;
	msg >> value.refineLevel;
	msg >> value.enhanceLevel;
	msg >> value.score;
}
void WriteMail_Info(stNetMsg& msg,Mail_Info& value)
{
	msg << value.mailId;
	msg << value.mailSendTime;
	msg << value.mailReadState;
	msg << value.mailType;
	msg << value.mailSendName;
	msg << value.mailTitle;
	msg << value.mailContent;
	msg << value.money;
	WriteArray(msg,GS2C_SignalItemInfo,value.vec);
}
void ReadMail_Info(stNetMsg& msg,Mail_Info& value)
{
	msg >> value.mailId;
	msg >> value.mailSendTime;
	msg >> value.mailReadState;
	msg >> value.mailType;
	msg >> value.mailSendName;
	msg >> value.mailTitle;
	msg >> value.mailContent;
	msg >> value.money;
	ReadArray(msg,GS2C_SignalItemInfo,value.vec);
}
void WriteGS2C_All_Mail_Info(stNetMsg& msg,GS2C_All_Mail_Info& value)
{
	WriteArray(msg,Mail_Info,value.vec);
	msg.command(MSG_GS2C_All_Mail_Info);
}
void ReadGS2C_All_Mail_Info(stNetMsg& msg,GS2C_All_Mail_Info& value)
{
	ReadArray(msg,Mail_Info,value.vec);
}
void WriteGS2C_Send_Mail(stNetMsg& msg,GS2C_Send_Mail& value)
{
	WriteMail_Info(msg, value.st);
	msg.command(MSG_GS2C_Send_Mail);
}
void ReadGS2C_Send_Mail(stNetMsg& msg,GS2C_Send_Mail& value)
{
	ReadMail_Info(msg, value.st);
}
void WriteGS2C_Chat(stNetMsg& msg,GS2C_Chat& value)
{
	msg << value.channelId;
	msg << value.isVip;
	msg << value.senderId;
	msg << value.senderName;
	msg << value.message;
	WriteArray(msg,GS2C_SignalItemInfo,value.vec);
	msg.command(MSG_GS2C_Chat);
}
void ReadGS2C_Chat(stNetMsg& msg,GS2C_Chat& value)
{
	msg >> value.channelId;
	msg >> value.isVip;
	msg >> value.senderId;
	msg >> value.senderName;
	msg >> value.message;
	ReadArray(msg,GS2C_SignalItemInfo,value.vec);
}
void WriteC2GS_LookOverPlayerEquip(stNetMsg& msg,C2GS_LookOverPlayerEquip& value)
{
	msg << value.playerId;
	msg.command(MSG_C2GS_LookOverPlayerEquip);
}
void C2GS_LookOverPlayerEquip::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_LookOverPlayerEquip(msg_s,*this);
	EndSend();
}
void ReadC2GS_LookOverPlayerEquip(stNetMsg& msg,C2GS_LookOverPlayerEquip& value)
{
	msg >> value.playerId;
}
void WriteGS2C_LookOverPlayerEquip_Result(stNetMsg& msg,GS2C_LookOverPlayerEquip_Result& value)
{
	msg << value.retCode;
	msg << value.playerId;
	msg << value.playerName;
	msg << value.leagueName;
	msg << value.level;
	msg << value.career;
	msg << value.sex;
	msg << value.weapon;
	msg << value.armor;
	msg << value.wing;
	WriteArray(msg,EquipItem,value.equipItems);
	msg.command(MSG_GS2C_LookOverPlayerEquip_Result);
}
void ReadGS2C_LookOverPlayerEquip_Result(stNetMsg& msg,GS2C_LookOverPlayerEquip_Result& value)
{
	msg >> value.retCode;
	msg >> value.playerId;
	msg >> value.playerName;
	msg >> value.leagueName;
	msg >> value.level;
	msg >> value.career;
	msg >> value.sex;
	msg >> value.weapon;
	msg >> value.armor;
	msg >> value.wing;
	ReadArray(msg,EquipItem,value.equipItems);
}
void WriteEquipId(stNetMsg& msg,EquipId& value)
{
	msg << value.equipId;
	msg << value.cnt;
}
void ReadEquipId(stNetMsg& msg,EquipId& value)
{
	msg >> value.equipId;
	msg >> value.cnt;
}
void WriteC2GS_SelectEquipCompose(stNetMsg& msg,C2GS_SelectEquipCompose& value)
{
	msg << value.equipComposeOrder;
	msg.command(MSG_C2GS_SelectEquipCompose);
}
void C2GS_SelectEquipCompose::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SelectEquipCompose(msg_s,*this);
	EndSend();
}
void ReadC2GS_SelectEquipCompose(stNetMsg& msg,C2GS_SelectEquipCompose& value)
{
	msg >> value.equipComposeOrder;
}
void WriteGS2C_SelectEquipCompose(stNetMsg& msg,GS2C_SelectEquipCompose& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_SelectEquipCompose);
}
void ReadGS2C_SelectEquipCompose(stNetMsg& msg,GS2C_SelectEquipCompose& value)
{
	msg >> value.retCode;
}
void WriteC2GS_ConfirmEquipComposeOrder(stNetMsg& msg,C2GS_ConfirmEquipComposeOrder& value)
{
	msg << value.equipComposeOrder;
	msg.command(MSG_C2GS_ConfirmEquipComposeOrder);
}
void C2GS_ConfirmEquipComposeOrder::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ConfirmEquipComposeOrder(msg_s,*this);
	EndSend();
}
void ReadC2GS_ConfirmEquipComposeOrder(stNetMsg& msg,C2GS_ConfirmEquipComposeOrder& value)
{
	msg >> value.equipComposeOrder;
}
void WriteC2GS_UseItem(stNetMsg& msg,C2GS_UseItem& value)
{
	msg << value.bagType;
	msg << value.index;
	msg << value.itemId;
	msg.command(MSG_C2GS_UseItem);
}
void C2GS_UseItem::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_UseItem(msg_s,*this);
	EndSend();
}
void ReadC2GS_UseItem(stNetMsg& msg,C2GS_UseItem& value)
{
	msg >> value.bagType;
	msg >> value.index;
	msg >> value.itemId;
}
void WriteGS2C_UseItem_Result(stNetMsg& msg,GS2C_UseItem_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_UseItem_Result);
}
void ReadGS2C_UseItem_Result(stNetMsg& msg,GS2C_UseItem_Result& value)
{
	msg >> value.retCode;
}
void WriteC2GS_StartEquipStrengthen(stNetMsg& msg,C2GS_StartEquipStrengthen& value)
{
	msg << value.equipId;
	msg << value.isUseLuckyStone;
	msg << value.isAutoBuyLuckyStone;
	msg << value.isAutoBuyStrengthenStone;
	msg << value.isTenStrengthen;
	msg.command(MSG_C2GS_StartEquipStrengthen);
}
void C2GS_StartEquipStrengthen::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_StartEquipStrengthen(msg_s,*this);
	EndSend();
}
void ReadC2GS_StartEquipStrengthen(stNetMsg& msg,C2GS_StartEquipStrengthen& value)
{
	msg >> value.equipId;
	msg >> value.isUseLuckyStone;
	msg >> value.isAutoBuyLuckyStone;
	msg >> value.isAutoBuyStrengthenStone;
	msg >> value.isTenStrengthen;
}
void WriteGS2C_StartEquipStrengthen(stNetMsg& msg,GS2C_StartEquipStrengthen& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_StartEquipStrengthen);
}
void ReadGS2C_StartEquipStrengthen(stNetMsg& msg,GS2C_StartEquipStrengthen& value)
{
	msg >> value.retCode;
}
void WriteGS2C_EquipLevelChange(stNetMsg& msg,GS2C_EquipLevelChange& value)
{
	msg << value.id;
	msg << value.level;
	msg << value.score;
	msg.command(MSG_GS2C_EquipLevelChange);
}
void ReadGS2C_EquipLevelChange(stNetMsg& msg,GS2C_EquipLevelChange& value)
{
	msg >> value.id;
	msg >> value.level;
	msg >> value.score;
}
void WriteGS2C_DesPlayer_LockTrade_Result(stNetMsg& msg,GS2C_DesPlayer_LockTrade_Result& value)
{
	msg << value.coin;
	WriteArray(msg,GS2C_SignalItemInfo,value.vec);
	msg.command(MSG_GS2C_DesPlayer_LockTrade_Result);
}
void ReadGS2C_DesPlayer_LockTrade_Result(stNetMsg& msg,GS2C_DesPlayer_LockTrade_Result& value)
{
	msg >> value.coin;
	ReadArray(msg,GS2C_SignalItemInfo,value.vec);
}
void WriteGS2C_InputItem_Result(stNetMsg& msg,GS2C_InputItem_Result& value)
{
	msg << value.coin;
	WriteArray(msg,GS2C_SignalItemInfo,value.vec);
	msg.command(MSG_GS2C_InputItem_Result);
}
void ReadGS2C_InputItem_Result(stNetMsg& msg,GS2C_InputItem_Result& value)
{
	msg >> value.coin;
	ReadArray(msg,GS2C_SignalItemInfo,value.vec);
}
void WriteC2GS_SetBagGrid(stNetMsg& msg,C2GS_SetBagGrid& value)
{
	msg << value.bagType;
	msg.command(MSG_C2GS_SetBagGrid);
}
void C2GS_SetBagGrid::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SetBagGrid(msg_s,*this);
	EndSend();
}
void ReadC2GS_SetBagGrid(stNetMsg& msg,C2GS_SetBagGrid& value)
{
	msg >> value.bagType;
}
void WriteGS2C_SetBagGrid(stNetMsg& msg,GS2C_SetBagGrid& value)
{
	msg << value.bagType;
	msg << value.newNum;
	msg << value.retCode;
	msg.command(MSG_GS2C_SetBagGrid);
}
void ReadGS2C_SetBagGrid(stNetMsg& msg,GS2C_SetBagGrid& value)
{
	msg >> value.bagType;
	msg >> value.newNum;
	msg >> value.retCode;
}
void WriteC2GS_SplitItem(stNetMsg& msg,C2GS_SplitItem& value)
{
	msg << value.bagType;
	msg << value.itemCnt;
	msg << value.itemId;
	msg << value.splitItemCnt;
	msg.command(MSG_C2GS_SplitItem);
}
void C2GS_SplitItem::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SplitItem(msg_s,*this);
	EndSend();
}
void ReadC2GS_SplitItem(stNetMsg& msg,C2GS_SplitItem& value)
{
	msg >> value.bagType;
	msg >> value.itemCnt;
	msg >> value.itemId;
	msg >> value.splitItemCnt;
}
void WriteGS2C_SplitItem(stNetMsg& msg,GS2C_SplitItem& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_SplitItem);
}
void ReadGS2C_SplitItem(stNetMsg& msg,GS2C_SplitItem& value)
{
	msg >> value.retCode;
}
void WriteGS2C_Tip_Msg(stNetMsg& msg,GS2C_Tip_Msg& value)
{
	msg << value.tipId;
	msg << value.args;
	WriteArray(msg,GS2C_SignalItemInfo,value.vec);
	msg.command(MSG_GS2C_Tip_Msg);
}
void ReadGS2C_Tip_Msg(stNetMsg& msg,GS2C_Tip_Msg& value)
{
	msg >> value.tipId;
	msg >> value.args;
	ReadArray(msg,GS2C_SignalItemInfo,value.vec);
}
void WriteC2GS_DropItem(stNetMsg& msg,C2GS_DropItem& value)
{
	msg << value.bagType;
	msg << value.index;
	msg << value.itemId;
	msg.command(MSG_C2GS_DropItem);
}
void C2GS_DropItem::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_DropItem(msg_s,*this);
	EndSend();
}
void ReadC2GS_DropItem(stNetMsg& msg,C2GS_DropItem& value)
{
	msg >> value.bagType;
	msg >> value.index;
	msg >> value.itemId;
}
void WriteGS2C_Sale_PutOnItem_Result(stNetMsg& msg,GS2C_Sale_PutOnItem_Result& value)
{
	msg << value.retCode;
	msg << value.saleId;
	WriteGS2C_SignalItemInfo(msg, value.saleItem);
	msg.command(MSG_GS2C_Sale_PutOnItem_Result);
}
void ReadGS2C_Sale_PutOnItem_Result(stNetMsg& msg,GS2C_Sale_PutOnItem_Result& value)
{
	msg >> value.retCode;
	msg >> value.saleId;
	ReadGS2C_SignalItemInfo(msg, value.saleItem);
}
void Writesale_filter_item(stNetMsg& msg,sale_filter_item& value)
{
	msg << value.price;
	msg << value.saleId;
	WriteGS2C_SignalItemInfo(msg, value.saleItem);
}
void Readsale_filter_item(stNetMsg& msg,sale_filter_item& value)
{
	msg >> value.price;
	msg >> value.saleId;
	ReadGS2C_SignalItemInfo(msg, value.saleItem);
}
void WriteGS2C_Sale_Filter_Item_Result(stNetMsg& msg,GS2C_Sale_Filter_Item_Result& value)
{
	msg << value.isNextPage;
	msg << value.totalPage;
	WriteArray(msg,sale_filter_item,value.saleVec);
	msg.command(MSG_GS2C_Sale_Filter_Item_Result);
}
void ReadGS2C_Sale_Filter_Item_Result(stNetMsg& msg,GS2C_Sale_Filter_Item_Result& value)
{
	msg >> value.isNextPage;
	msg >> value.totalPage;
	ReadArray(msg,sale_filter_item,value.saleVec);
}
void WriteGS2C_Sale_Find_Item_Result(stNetMsg& msg,GS2C_Sale_Find_Item_Result& value)
{
	msg << value.isNextPage;
	msg << value.totalPage;
	WriteArray(msg,sale_filter_item,value.saleVec);
	msg.command(MSG_GS2C_Sale_Find_Item_Result);
}
void ReadGS2C_Sale_Find_Item_Result(stNetMsg& msg,GS2C_Sale_Find_Item_Result& value)
{
	msg >> value.isNextPage;
	msg >> value.totalPage;
	ReadArray(msg,sale_filter_item,value.saleVec);
}
void Writemy_sale_item(stNetMsg& msg,my_sale_item& value)
{
	msg << value.price;
	msg << value.remainTime;
	msg << value.saleId;
	WriteGS2C_SignalItemInfo(msg, value.saleItem);
}
void Readmy_sale_item(stNetMsg& msg,my_sale_item& value)
{
	msg >> value.price;
	msg >> value.remainTime;
	msg >> value.saleId;
	ReadGS2C_SignalItemInfo(msg, value.saleItem);
}
void Writemy_sale_gold(stNetMsg& msg,my_sale_gold& value)
{
	msg << value.price;
	msg << value.remainTime;
	msg << value.saleId;
	msg << value.goldType;
}
void Readmy_sale_gold(stNetMsg& msg,my_sale_gold& value)
{
	msg >> value.price;
	msg >> value.remainTime;
	msg >> value.saleId;
	msg >> value.goldType;
}
void WriteGS2C_Sale_My_Sale_Item(stNetMsg& msg,GS2C_Sale_My_Sale_Item& value)
{
	WriteArray(msg,my_sale_item,value.mySaleVec);
	msg.command(MSG_GS2C_Sale_My_Sale_Item);
}
void ReadGS2C_Sale_My_Sale_Item(stNetMsg& msg,GS2C_Sale_My_Sale_Item& value)
{
	ReadArray(msg,my_sale_item,value.mySaleVec);
}
void WriteGS2C_Sale_My_Sale_Gold(stNetMsg& msg,GS2C_Sale_My_Sale_Gold& value)
{
	WriteArray(msg,my_sale_gold,value.mySaleVec);
	msg.command(MSG_GS2C_Sale_My_Sale_Gold);
}
void ReadGS2C_Sale_My_Sale_Gold(stNetMsg& msg,GS2C_Sale_My_Sale_Gold& value)
{
	ReadArray(msg,my_sale_gold,value.mySaleVec);
}
void WriteGS2C_SubmitTaskChain(stNetMsg& msg,GS2C_SubmitTaskChain& value)
{
	msg << value.retCode;
	msg << value.taskChainCnt;
	msg << value.loopCnt;
	msg << value.startNpcDataId;
	msg << value.endNpcDataId;
	msg << value.taskId;
	msg << value.exp;
	msg << value.coin;
	msg << value.bindCoin;
	msg << value.honor;
	WriteArray(msg,GS2C_SignalItemInfo,value.awardItem);
	WriteArray(msg,GS2C_SignalItemInfo,value.awardRandItem);
	msg.command(MSG_GS2C_SubmitTaskChain);
}
void ReadGS2C_SubmitTaskChain(stNetMsg& msg,GS2C_SubmitTaskChain& value)
{
	msg >> value.retCode;
	msg >> value.taskChainCnt;
	msg >> value.loopCnt;
	msg >> value.startNpcDataId;
	msg >> value.endNpcDataId;
	msg >> value.taskId;
	msg >> value.exp;
	msg >> value.coin;
	msg >> value.bindCoin;
	msg >> value.honor;
	ReadArray(msg,GS2C_SignalItemInfo,value.awardItem);
	ReadArray(msg,GS2C_SignalItemInfo,value.awardRandItem);
}
void WritetaskChainProgress(stNetMsg& msg,taskChainProgress& value)
{
	msg << value.targetType;
	msg << value.targetCnt;
	msg << value.curCnt;
}
void ReadtaskChainProgress(stNetMsg& msg,taskChainProgress& value)
{
	msg >> value.targetType;
	msg >> value.targetCnt;
	msg >> value.curCnt;
}
void WriteGS2C_AcceptedTaskChain(stNetMsg& msg,GS2C_AcceptedTaskChain& value)
{
	msg << value.taskId;
	msg << value.startNpcDataId;
	msg << value.endNpcDataId;
	msg << value.taskChainCnt;
	msg << value.loopCnt;
	WriteArray(msg,taskChainProgress,value.progress);
	msg << value.exp;
	msg << value.coin;
	msg << value.bindCoin;
	msg << value.honor;
	WriteArray(msg,GS2C_SignalItemInfo,value.awardItem);
	WriteArray(msg,GS2C_SignalItemInfo,value.awardRandItem);
	msg.command(MSG_GS2C_AcceptedTaskChain);
}
void ReadGS2C_AcceptedTaskChain(stNetMsg& msg,GS2C_AcceptedTaskChain& value)
{
	msg >> value.taskId;
	msg >> value.startNpcDataId;
	msg >> value.endNpcDataId;
	msg >> value.taskChainCnt;
	msg >> value.loopCnt;
	ReadArray(msg,taskChainProgress,value.progress);
	msg >> value.exp;
	msg >> value.coin;
	msg >> value.bindCoin;
	msg >> value.honor;
	ReadArray(msg,GS2C_SignalItemInfo,value.awardItem);
	ReadArray(msg,GS2C_SignalItemInfo,value.awardRandItem);
}
void WriteC2GS_TianShuSet_Req(stNetMsg& msg,C2GS_TianShuSet_Req& value)
{
	msg << value.index;
	msg << value.type;
	msg << value.solt;
	msg << value.bag_index;
	msg.command(MSG_C2GS_TianShuSet_Req);
}
void C2GS_TianShuSet_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_TianShuSet_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_TianShuSet_Req(stNetMsg& msg,C2GS_TianShuSet_Req& value)
{
	msg >> value.index;
	msg >> value.type;
	msg >> value.solt;
	msg >> value.bag_index;
}
void WriteGS2C_TianShuSet_Ret(stNetMsg& msg,GS2C_TianShuSet_Ret& value)
{
	msg << value.retCode;
	msg << value.type;
	WriteArray(msg,EquipTianshu,value.tianShuList);
	WriteBagItem(msg, value.newTianShu);
	msg.command(MSG_GS2C_TianShuSet_Ret);
}
void ReadGS2C_TianShuSet_Ret(stNetMsg& msg,GS2C_TianShuSet_Ret& value)
{
	msg >> value.retCode;
	msg >> value.type;
	ReadArray(msg,EquipTianshu,value.tianShuList);
	ReadBagItem(msg, value.newTianShu);
}
void WriteGS2C_TianShuUpate(stNetMsg& msg,GS2C_TianShuUpate& value)
{
	WriteBagItem(msg, value.newTianShu);
	msg.command(MSG_GS2C_TianShuUpate);
}
void ReadGS2C_TianShuUpate(stNetMsg& msg,GS2C_TianShuUpate& value)
{
	ReadBagItem(msg, value.newTianShu);
}
void WriteGS2C_EquipTianShuUpate(stNetMsg& msg,GS2C_EquipTianShuUpate& value)
{
	WriteEquipItem(msg, value.newEquip);
	msg.command(MSG_GS2C_EquipTianShuUpate);
}
void ReadGS2C_EquipTianShuUpate(stNetMsg& msg,GS2C_EquipTianShuUpate& value)
{
	ReadEquipItem(msg, value.newEquip);
}
void WriteC2GS_TianShuTakeOff_Req(stNetMsg& msg,C2GS_TianShuTakeOff_Req& value)
{
	msg << value.index;
	msg << value.type;
	msg << value.solt;
	msg.command(MSG_C2GS_TianShuTakeOff_Req);
}
void C2GS_TianShuTakeOff_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_TianShuTakeOff_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_TianShuTakeOff_Req(stNetMsg& msg,C2GS_TianShuTakeOff_Req& value)
{
	msg >> value.index;
	msg >> value.type;
	msg >> value.solt;
}
void WriteGS2C_TianShuTakeOff_Ret(stNetMsg& msg,GS2C_TianShuTakeOff_Ret& value)
{
	msg << value.retCode;
	msg << value.type;
	WriteArray(msg,EquipTianshu,value.tianShuList);
	msg.command(MSG_GS2C_TianShuTakeOff_Ret);
}
void ReadGS2C_TianShuTakeOff_Ret(stNetMsg& msg,GS2C_TianShuTakeOff_Ret& value)
{
	msg >> value.retCode;
	msg >> value.type;
	ReadArray(msg,EquipTianshu,value.tianShuList);
}
void Writetian_shu_material(stNetMsg& msg,tian_shu_material& value)
{
	msg << value.index;
	msg << value.count;
}
void Readtian_shu_material(stNetMsg& msg,tian_shu_material& value)
{
	msg >> value.index;
	msg >> value.count;
}
void WriteC2GS_TianShuLvUp_Req(stNetMsg& msg,C2GS_TianShuLvUp_Req& value)
{
	msg << value.index;
	WriteArray(msg,tian_shu_material,value.materialList);
	msg.command(MSG_C2GS_TianShuLvUp_Req);
}
void C2GS_TianShuLvUp_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_TianShuLvUp_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_TianShuLvUp_Req(stNetMsg& msg,C2GS_TianShuLvUp_Req& value)
{
	msg >> value.index;
	ReadArray(msg,tian_shu_material,value.materialList);
}
void WriteGS2C_TianShuLvUp_Ret(stNetMsg& msg,GS2C_TianShuLvUp_Ret& value)
{
	msg << value.retCode;
	msg << value.newLv;
	msg << value.newExp;
	msg.command(MSG_GS2C_TianShuLvUp_Ret);
}
void ReadGS2C_TianShuLvUp_Ret(stNetMsg& msg,GS2C_TianShuLvUp_Ret& value)
{
	msg >> value.retCode;
	msg >> value.newLv;
	msg >> value.newExp;
}
void WriteC2GS_TianShuCompose_Req(stNetMsg& msg,C2GS_TianShuCompose_Req& value)
{
	WriteArray(msg,tian_shu_material,value.materialList);
	msg.command(MSG_C2GS_TianShuCompose_Req);
}
void C2GS_TianShuCompose_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_TianShuCompose_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_TianShuCompose_Req(stNetMsg& msg,C2GS_TianShuCompose_Req& value)
{
	ReadArray(msg,tian_shu_material,value.materialList);
}
void WriteGS2C_TianShuCompose_Ret(stNetMsg& msg,GS2C_TianShuCompose_Ret& value)
{
	msg << value.retCode;
	msg << value.itemDataId;
	msg.command(MSG_GS2C_TianShuCompose_Ret);
}
void ReadGS2C_TianShuCompose_Ret(stNetMsg& msg,GS2C_TianShuCompose_Ret& value)
{
	msg >> value.retCode;
	msg >> value.itemDataId;
}
void WriteC2GS_TianShuEquipContentLvUp_Req(stNetMsg& msg,C2GS_TianShuEquipContentLvUp_Req& value)
{
	msg << value.type;
	msg.command(MSG_C2GS_TianShuEquipContentLvUp_Req);
}
void C2GS_TianShuEquipContentLvUp_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_TianShuEquipContentLvUp_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_TianShuEquipContentLvUp_Req(stNetMsg& msg,C2GS_TianShuEquipContentLvUp_Req& value)
{
	msg >> value.type;
}
void WriteGS2C_TianShuEquipContentLvUp_Ret(stNetMsg& msg,GS2C_TianShuEquipContentLvUp_Ret& value)
{
	msg << value.retCode;
	msg << value.type;
	msg.command(MSG_GS2C_TianShuEquipContentLvUp_Ret);
}
void ReadGS2C_TianShuEquipContentLvUp_Ret(stNetMsg& msg,GS2C_TianShuEquipContentLvUp_Ret& value)
{
	msg >> value.retCode;
	msg >> value.type;
}
void WriteC2GS_TianShuEquipSoltLvUp_Req(stNetMsg& msg,C2GS_TianShuEquipSoltLvUp_Req& value)
{
	msg << value.type;
	msg << value.solt;
	msg.command(MSG_C2GS_TianShuEquipSoltLvUp_Req);
}
void C2GS_TianShuEquipSoltLvUp_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_TianShuEquipSoltLvUp_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_TianShuEquipSoltLvUp_Req(stNetMsg& msg,C2GS_TianShuEquipSoltLvUp_Req& value)
{
	msg >> value.type;
	msg >> value.solt;
}
void WriteGS2C_TianShuEquipSoltLvUp_Ret(stNetMsg& msg,GS2C_TianShuEquipSoltLvUp_Ret& value)
{
	msg << value.retCode;
	msg << value.type;
	msg << value.solt;
	msg.command(MSG_GS2C_TianShuEquipSoltLvUp_Ret);
}
void ReadGS2C_TianShuEquipSoltLvUp_Ret(stNetMsg& msg,GS2C_TianShuEquipSoltLvUp_Ret& value)
{
	msg >> value.retCode;
	msg >> value.type;
	msg >> value.solt;
}
void WriteGS2C_TianShuChangeIndex_Req(stNetMsg& msg,GS2C_TianShuChangeIndex_Req& value)
{
	msg << value.type;
	msg << value.index;
	msg.command(MSG_GS2C_TianShuChangeIndex_Req);
}
void GS2C_TianShuChangeIndex_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2C_TianShuChangeIndex_Req(msg_s,*this);
	EndSend();
}
void ReadGS2C_TianShuChangeIndex_Req(stNetMsg& msg,GS2C_TianShuChangeIndex_Req& value)
{
	msg >> value.type;
	msg >> value.index;
}
void WriteC2GS_TianShuChangeIndex_Ret(stNetMsg& msg,C2GS_TianShuChangeIndex_Ret& value)
{
	msg << value.retCode;
	msg << value.type;
	msg << value.index;
	msg.command(MSG_C2GS_TianShuChangeIndex_Ret);
}
void ReadC2GS_TianShuChangeIndex_Ret(stNetMsg& msg,C2GS_TianShuChangeIndex_Ret& value)
{
	msg >> value.retCode;
	msg >> value.type;
	msg >> value.index;
}
void WriteGS2C_TianShuChangeSolt_Req(stNetMsg& msg,GS2C_TianShuChangeSolt_Req& value)
{
	msg << value.type;
	msg << value.index;
	msg << value.solt;
	msg << value.newsolt;
	msg.command(MSG_GS2C_TianShuChangeSolt_Req);
}
void GS2C_TianShuChangeSolt_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGS2C_TianShuChangeSolt_Req(msg_s,*this);
	EndSend();
}
void ReadGS2C_TianShuChangeSolt_Req(stNetMsg& msg,GS2C_TianShuChangeSolt_Req& value)
{
	msg >> value.type;
	msg >> value.index;
	msg >> value.solt;
	msg >> value.newsolt;
}
void WriteC2GS_TianShuChangeSolt_Ret(stNetMsg& msg,C2GS_TianShuChangeSolt_Ret& value)
{
	msg << value.retCode;
	msg << value.type;
	msg << value.index;
	msg << value.solt;
	msg << value.newsolt;
	msg.command(MSG_C2GS_TianShuChangeSolt_Ret);
}
void ReadC2GS_TianShuChangeSolt_Ret(stNetMsg& msg,C2GS_TianShuChangeSolt_Ret& value)
{
	msg >> value.retCode;
	msg >> value.type;
	msg >> value.index;
	msg >> value.solt;
	msg >> value.newsolt;
}
void WritePlayerGodDevice(stNetMsg& msg,PlayerGodDevice& value)
{
	msg << value.isDress;
	msg << value.godDeviceCfgId;
	msg << value.refineLevel;
	msg << value.enhanceLevel;
	msg << value.equipId;
	WriteArray(msg,EquipTianshu,value.tianShuList);
	msg << value.content_lv;
	WriteArray(msg,TianshuSoltStreng,value.soltStrengList);
	msg << value.tian_shu_use_index;
}
void ReadPlayerGodDevice(stNetMsg& msg,PlayerGodDevice& value)
{
	msg >> value.isDress;
	msg >> value.godDeviceCfgId;
	msg >> value.refineLevel;
	msg >> value.enhanceLevel;
	msg >> value.equipId;
	ReadArray(msg,EquipTianshu,value.tianShuList);
	msg >> value.content_lv;
	ReadArray(msg,TianshuSoltStreng,value.soltStrengList);
	msg >> value.tian_shu_use_index;
}
void WriteGS2C_PlayerGodDeviceList(stNetMsg& msg,GS2C_PlayerGodDeviceList& value)
{
	WriteArray(msg,PlayerGodDevice,value.playerGodDeviceList);
	msg.command(MSG_GS2C_PlayerGodDeviceList);
}
void ReadGS2C_PlayerGodDeviceList(stNetMsg& msg,GS2C_PlayerGodDeviceList& value)
{
	ReadArray(msg,PlayerGodDevice,value.playerGodDeviceList);
}
void WriteC2GS_GainGodDevice(stNetMsg& msg,C2GS_GainGodDevice& value)
{
	msg << value.godDeviceCfgId;
	msg.command(MSG_C2GS_GainGodDevice);
}
void C2GS_GainGodDevice::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_GainGodDevice(msg_s,*this);
	EndSend();
}
void ReadC2GS_GainGodDevice(stNetMsg& msg,C2GS_GainGodDevice& value)
{
	msg >> value.godDeviceCfgId;
}
void WriteGS2C_GainGodDevice_Ret(stNetMsg& msg,GS2C_GainGodDevice_Ret& value)
{
	msg << value.errorCode;
	WriteArray(msg,PlayerGodDevice,value.playerGainGodDevice);
	msg.command(MSG_GS2C_GainGodDevice_Ret);
}
void ReadGS2C_GainGodDevice_Ret(stNetMsg& msg,GS2C_GainGodDevice_Ret& value)
{
	msg >> value.errorCode;
	ReadArray(msg,PlayerGodDevice,value.playerGainGodDevice);
}
void WriteC2GS_ChangeGodDevice(stNetMsg& msg,C2GS_ChangeGodDevice& value)
{
	msg << value.index;
	msg.command(MSG_C2GS_ChangeGodDevice);
}
void C2GS_ChangeGodDevice::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ChangeGodDevice(msg_s,*this);
	EndSend();
}
void ReadC2GS_ChangeGodDevice(stNetMsg& msg,C2GS_ChangeGodDevice& value)
{
	msg >> value.index;
}
void WriteGS2C_ChangeGodDevice_Ret(stNetMsg& msg,GS2C_ChangeGodDevice_Ret& value)
{
	msg << value.errorCode;
	msg << value.oldIndex;
	msg << value.newIndex;
	msg.command(MSG_GS2C_ChangeGodDevice_Ret);
}
void ReadGS2C_ChangeGodDevice_Ret(stNetMsg& msg,GS2C_ChangeGodDevice_Ret& value)
{
	msg >> value.errorCode;
	msg >> value.oldIndex;
	msg >> value.newIndex;
}
void WriteGS2C_UpdateGodDevice_Ret(stNetMsg& msg,GS2C_UpdateGodDevice_Ret& value)
{
	WritePlayerGodDevice(msg, value.playerGodDevice);
	msg.command(MSG_GS2C_UpdateGodDevice_Ret);
}
void ReadGS2C_UpdateGodDevice_Ret(stNetMsg& msg,GS2C_UpdateGodDevice_Ret& value)
{
	ReadPlayerGodDevice(msg, value.playerGodDevice);
}
void WriteC2GS_Enhance(stNetMsg& msg,C2GS_Enhance& value)
{
	msg << value.type;
	msg << value.equipId;
	msg.command(MSG_C2GS_Enhance);
}
void C2GS_Enhance::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Enhance(msg_s,*this);
	EndSend();
}
void ReadC2GS_Enhance(stNetMsg& msg,C2GS_Enhance& value)
{
	msg >> value.type;
	msg >> value.equipId;
}
void WriteGS2C_Enhance_Ret(stNetMsg& msg,GS2C_Enhance_Ret& value)
{
	msg << value.type;
	msg << value.equipId;
	msg << value.inWhere;
	msg << value.enhanceLevel;
	msg.command(MSG_GS2C_Enhance_Ret);
}
void ReadGS2C_Enhance_Ret(stNetMsg& msg,GS2C_Enhance_Ret& value)
{
	msg >> value.type;
	msg >> value.equipId;
	msg >> value.inWhere;
	msg >> value.enhanceLevel;
}
void WriteC2GS_Refine(stNetMsg& msg,C2GS_Refine& value)
{
	msg << value.type;
	msg << value.equipId;
	msg << value.isRefineMaxLevel;
	msg.command(MSG_C2GS_Refine);
}
void C2GS_Refine::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Refine(msg_s,*this);
	EndSend();
}
void ReadC2GS_Refine(stNetMsg& msg,C2GS_Refine& value)
{
	msg >> value.type;
	msg >> value.equipId;
	msg >> value.isRefineMaxLevel;
}
void WriteC2GS_Refine_All(stNetMsg& msg,C2GS_Refine_All& value)
{
	msg.command(MSG_C2GS_Refine_All);
}
void C2GS_Refine_All::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Refine_All(msg_s,*this);
	EndSend();
}
void ReadC2GS_Refine_All(stNetMsg& msg,C2GS_Refine_All& value)
{
}
void WritePlayerRefine(stNetMsg& msg,PlayerRefine& value)
{
	msg << value.type;
	msg << value.equipId;
	msg << value.inWhere;
	msg << value.refineLevel;
}
void ReadPlayerRefine(stNetMsg& msg,PlayerRefine& value)
{
	msg >> value.type;
	msg >> value.equipId;
	msg >> value.inWhere;
	msg >> value.refineLevel;
}
void WriteGS2C_Refine_Ret(stNetMsg& msg,GS2C_Refine_Ret& value)
{
	msg << value.errorCode;
	WriteArray(msg,PlayerRefine,value.playerRefineList);
	msg.command(MSG_GS2C_Refine_Ret);
}
void ReadGS2C_Refine_Ret(stNetMsg& msg,GS2C_Refine_Ret& value)
{
	msg >> value.errorCode;
	ReadArray(msg,PlayerRefine,value.playerRefineList);
}
void WriteManufacture_Element(stNetMsg& msg,Manufacture_Element& value)
{
	msg << value.itemDataId;
	msg << value.eliminateCdFlag;
	msg << value.remainSeconds;
	msg << value.isDone;
}
void ReadManufacture_Element(stNetMsg& msg,Manufacture_Element& value)
{
	msg >> value.itemDataId;
	msg >> value.eliminateCdFlag;
	msg >> value.remainSeconds;
	msg >> value.isDone;
}
void WriteGS2C_ManufactureList_Ret(stNetMsg& msg,GS2C_ManufactureList_Ret& value)
{
	WriteArray(msg,Manufacture_Element,value.manufactureList);
	msg.command(MSG_GS2C_ManufactureList_Ret);
}
void ReadGS2C_ManufactureList_Ret(stNetMsg& msg,GS2C_ManufactureList_Ret& value)
{
	ReadArray(msg,Manufacture_Element,value.manufactureList);
}
void WriteC2GS_New_Manufacture_Element(stNetMsg& msg,C2GS_New_Manufacture_Element& value)
{
	msg << value.itemDataId;
	msg.command(MSG_C2GS_New_Manufacture_Element);
}
void C2GS_New_Manufacture_Element::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_New_Manufacture_Element(msg_s,*this);
	EndSend();
}
void ReadC2GS_New_Manufacture_Element(stNetMsg& msg,C2GS_New_Manufacture_Element& value)
{
	msg >> value.itemDataId;
}
void WriteGS2C_New_Manufacture_Element_Ret(stNetMsg& msg,GS2C_New_Manufacture_Element_Ret& value)
{
	msg << value.errorCode;
	WriteManufacture_Element(msg, value.manufactureElement);
	msg.command(MSG_GS2C_New_Manufacture_Element_Ret);
}
void ReadGS2C_New_Manufacture_Element_Ret(stNetMsg& msg,GS2C_New_Manufacture_Element_Ret& value)
{
	msg >> value.errorCode;
	ReadManufacture_Element(msg, value.manufactureElement);
}
void WriteC2GS_Eliminate_Cd(stNetMsg& msg,C2GS_Eliminate_Cd& value)
{
	msg << value.itemDataId;
	msg.command(MSG_C2GS_Eliminate_Cd);
}
void C2GS_Eliminate_Cd::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Eliminate_Cd(msg_s,*this);
	EndSend();
}
void ReadC2GS_Eliminate_Cd(stNetMsg& msg,C2GS_Eliminate_Cd& value)
{
	msg >> value.itemDataId;
}
void WriteGS2C_Eliminate_Cd_Ret(stNetMsg& msg,GS2C_Eliminate_Cd_Ret& value)
{
	msg << value.errorCode;
	WriteManufacture_Element(msg, value.manufactureElement);
	msg.command(MSG_GS2C_Eliminate_Cd_Ret);
}
void ReadGS2C_Eliminate_Cd_Ret(stNetMsg& msg,GS2C_Eliminate_Cd_Ret& value)
{
	msg >> value.errorCode;
	ReadManufacture_Element(msg, value.manufactureElement);
}
void WriteC2GS_Gain_Item(stNetMsg& msg,C2GS_Gain_Item& value)
{
	msg << value.itemDataId;
	msg.command(MSG_C2GS_Gain_Item);
}
void C2GS_Gain_Item::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Gain_Item(msg_s,*this);
	EndSend();
}
void ReadC2GS_Gain_Item(stNetMsg& msg,C2GS_Gain_Item& value)
{
	msg >> value.itemDataId;
}
void WriteGS2C_Gain_Item_Ret(stNetMsg& msg,GS2C_Gain_Item_Ret& value)
{
	msg << value.itemDataId;
	msg << value.errorCode;
	msg.command(MSG_GS2C_Gain_Item_Ret);
}
void ReadGS2C_Gain_Item_Ret(stNetMsg& msg,GS2C_Gain_Item_Ret& value)
{
	msg >> value.itemDataId;
	msg >> value.errorCode;
}
void WriteFightProperty(stNetMsg& msg,FightProperty& value)
{
	msg << value.phy_dam;
	msg << value.fire_dam;
	msg << value.code_dam;
	msg << value.elec_dam;
	msg << value.toxin_dam;
	msg << value.base_dam_increase;
	msg << value.all_dam_increase;
	msg << value.all_dam_reduce;
	msg << value.atk_power;
	msg << value.hp_max;
	msg << value.hp_r;
	msg << value.hp_rp;
	msg << value.by_cure_factor;
	msg << value.mp_max;
	msg << value.mp_r;
	msg << value.speed;
	msg << value.armor;
	msg << value.phy_res;
	msg << value.fire_res;
	msg << value.cold_res;
	msg << value.elec_res;
	msg << value.toxin_res;
	msg << value.tough;
	msg << value.penetrate;
	msg << value.thickness;
	msg << value.crit_p;
	msg << value.crit_hurt;
	msg << value.accurate_p;
	msg << value.dodge_p;
	msg << value.trigger_p;
	msg << value.atk_speed_increase;
	msg << value.mp_efficiency;
	msg << value.skill_duration;
	msg << value.skill_power;
	msg << value.skill_rang;
	msg << value.hp_ball;
	msg << value.mp_ball;
	msg << value.armor_reduce;
	msg.command(MSG_FightProperty);
}
void ReadFightProperty(stNetMsg& msg,FightProperty& value)
{
	msg >> value.phy_dam;
	msg >> value.fire_dam;
	msg >> value.code_dam;
	msg >> value.elec_dam;
	msg >> value.toxin_dam;
	msg >> value.base_dam_increase;
	msg >> value.all_dam_increase;
	msg >> value.all_dam_reduce;
	msg >> value.atk_power;
	msg >> value.hp_max;
	msg >> value.hp_r;
	msg >> value.hp_rp;
	msg >> value.by_cure_factor;
	msg >> value.mp_max;
	msg >> value.mp_r;
	msg >> value.speed;
	msg >> value.armor;
	msg >> value.phy_res;
	msg >> value.fire_res;
	msg >> value.cold_res;
	msg >> value.elec_res;
	msg >> value.toxin_res;
	msg >> value.tough;
	msg >> value.penetrate;
	msg >> value.thickness;
	msg >> value.crit_p;
	msg >> value.crit_hurt;
	msg >> value.accurate_p;
	msg >> value.dodge_p;
	msg >> value.trigger_p;
	msg >> value.atk_speed_increase;
	msg >> value.mp_efficiency;
	msg >> value.skill_duration;
	msg >> value.skill_power;
	msg >> value.skill_rang;
	msg >> value.hp_ball;
	msg >> value.mp_ball;
	msg >> value.armor_reduce;
}
void WritePetInfo(stNetMsg& msg,PetInfo& value)
{
	msg << value.id;
	msg << value.dataId;
	msg << value.level;
	msg << value.exp;
	msg << value.strengLv;
	msg << value.isActive;
	WriteFightProperty(msg, value.prop);
	WriteArray(msg,EquipTianshu,value.tianShuList);
	msg << value.content_lv;
	WriteArray(msg,TianshuSoltStreng,value.soltStrengList);
	msg << value.tian_shu_use_index;
}
void ReadPetInfo(stNetMsg& msg,PetInfo& value)
{
	msg >> value.id;
	msg >> value.dataId;
	msg >> value.level;
	msg >> value.exp;
	msg >> value.strengLv;
	msg >> value.isActive;
	ReadFightProperty(msg, value.prop);
	ReadArray(msg,EquipTianshu,value.tianShuList);
	msg >> value.content_lv;
	ReadArray(msg,TianshuSoltStreng,value.soltStrengList);
	msg >> value.tian_shu_use_index;
}
void WriteGS2C_AllPets(stNetMsg& msg,GS2C_AllPets& value)
{
	WriteArray(msg,PetInfo,value.pets);
	msg.command(MSG_GS2C_AllPets);
}
void ReadGS2C_AllPets(stNetMsg& msg,GS2C_AllPets& value)
{
	ReadArray(msg,PetInfo,value.pets);
}
void WriteGS2C_UpdatePetInfo(stNetMsg& msg,GS2C_UpdatePetInfo& value)
{
	msg << value.id;
	msg << value.dataId;
	msg << value.level;
	msg << value.exp;
	msg << value.strengLv;
	msg << value.isActive;
	WriteFightProperty(msg, value.prop);
	WriteArray(msg,EquipTianshu,value.tianShuList);
	msg << value.content_lv;
	WriteArray(msg,TianshuSoltStreng,value.soltStrengList);
	msg << value.tian_shu_use_index;
	msg.command(MSG_GS2C_UpdatePetInfo);
}
void ReadGS2C_UpdatePetInfo(stNetMsg& msg,GS2C_UpdatePetInfo& value)
{
	msg >> value.id;
	msg >> value.dataId;
	msg >> value.level;
	msg >> value.exp;
	msg >> value.strengLv;
	msg >> value.isActive;
	ReadFightProperty(msg, value.prop);
	ReadArray(msg,EquipTianshu,value.tianShuList);
	msg >> value.content_lv;
	ReadArray(msg,TianshuSoltStreng,value.soltStrengList);
	msg >> value.tian_shu_use_index;
}

};


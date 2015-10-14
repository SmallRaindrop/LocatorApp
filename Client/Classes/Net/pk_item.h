
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct EquipTianshuDetail
{
	int8 solt;
	int32 tianShuDataId;
	int32 tianShuLv;
};
void WriteEquipTianshuDetail(stNetMsg& msg,EquipTianshuDetail& value);
void ReadEquipTianshuDetail(stNetMsg& msg,EquipTianshuDetail& value);

struct EquipTianshu
{
	int8 index;
	vector<EquipTianshuDetail> tianShuList;
};
void WriteEquipTianshu(stNetMsg& msg,EquipTianshu& value);
void ReadEquipTianshu(stNetMsg& msg,EquipTianshu& value);

struct TianshuSoltStreng
{
	int8 solt;
	int8 strengLv;
};
void WriteTianshuSoltStreng(stNetMsg& msg,TianshuSoltStreng& value);
void ReadTianshuSoltStreng(stNetMsg& msg,TianshuSoltStreng& value);

struct EquipItem
{
	int8 part;
	int64 id;
	int8 isBind;
	int32 equipDataId;
	int8 refineLevel;
	int8 enhanceLevel;
	int32 score;
	vector<EquipTianshu> tianShuList;
	int8 content_lv;
	vector<TianshuSoltStreng> soltStrengList;
	int8 tian_shu_use_index;
};
void WriteEquipItem(stNetMsg& msg,EquipItem& value);
void ReadEquipItem(stNetMsg& msg,EquipItem& value);

struct GS2C_EquipGetItem_Ret
{
	vector<EquipItem> equipItems;
};
void WriteGS2C_EquipGetItem_Ret(stNetMsg& msg,GS2C_EquipGetItem_Ret& value);
bool OnGS2C_EquipGetItem_Ret(GS2C_EquipGetItem_Ret* value);
void ReadGS2C_EquipGetItem_Ret(stNetMsg& msg,GS2C_EquipGetItem_Ret& value);

struct C2GS_EquipItem
{
	int16 index;
	int8 part;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_EquipItem(stNetMsg& msg,C2GS_EquipItem& value);
void ReadC2GS_EquipItem(stNetMsg& msg,C2GS_EquipItem& value);

struct C2GS_UnequipItem
{
	int8 part;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_UnequipItem(stNetMsg& msg,C2GS_UnequipItem& value);
void ReadC2GS_UnequipItem(stNetMsg& msg,C2GS_UnequipItem& value);

struct GS2C_EquipExchangeRet
{
	int8 isEquip;
	int8 part;
	int16 index;
};
void WriteGS2C_EquipExchangeRet(stNetMsg& msg,GS2C_EquipExchangeRet& value);
bool OnGS2C_EquipExchangeRet(GS2C_EquipExchangeRet* value);
void ReadGS2C_EquipExchangeRet(stNetMsg& msg,GS2C_EquipExchangeRet& value);

struct C2GS_BagGetItems
{
	int8 bagType;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_BagGetItems(stNetMsg& msg,C2GS_BagGetItems& value);
void ReadC2GS_BagGetItems(stNetMsg& msg,C2GS_BagGetItems& value);

struct TianShuSet
{
	int64 id;
	int64 type;
	int8 index;
};
void WriteTianShuSet(stNetMsg& msg,TianShuSet& value);
void ReadTianShuSet(stNetMsg& msg,TianShuSet& value);

struct BagItem
{
	int16 index;
	int64 id;
	int32 itemDataId;
	int16 count;
	int8 isBind;
	int8 strengthenLevel;
	int8 refineLevel;
	int8 enhanceLevel;
	int32 score;
	vector<EquipTianshu> tianShuList;
	int8 content_lv;
	vector<TianshuSoltStreng> soltStrengList;
	int16 tian_shu_exp;
	vector<TianShuSet> tian_shu_set_list;
};
void WriteBagItem(stNetMsg& msg,BagItem& value);
void ReadBagItem(stNetMsg& msg,BagItem& value);

struct GS2C_BagGetItems_Ret
{
	int8 bagType;
	int16 bagGridNum;
	vector<BagItem> getBagItems;
};
void WriteGS2C_BagGetItems_Ret(stNetMsg& msg,GS2C_BagGetItems_Ret& value);
bool OnGS2C_BagGetItems_Ret(GS2C_BagGetItems_Ret* value);
void ReadGS2C_BagGetItems_Ret(stNetMsg& msg,GS2C_BagGetItems_Ret& value);

struct GS2C_BagAddItem
{
	int8 bagType;
	int8 reason;
	BagItem addItem;
};
void WriteGS2C_BagAddItem(stNetMsg& msg,GS2C_BagAddItem& value);
bool OnGS2C_BagAddItem(GS2C_BagAddItem* value);
void ReadGS2C_BagAddItem(stNetMsg& msg,GS2C_BagAddItem& value);

struct GS2C_ItemCntChange
{
	int8 bagType;
	int16 index;
	int16 newCount;
	int16 oldCount;
};
void WriteGS2C_ItemCntChange(stNetMsg& msg,GS2C_ItemCntChange& value);
bool OnGS2C_ItemCntChange(GS2C_ItemCntChange* value);
void ReadGS2C_ItemCntChange(stNetMsg& msg,GS2C_ItemCntChange& value);

struct GSWithC_BagDeleteItems
{
	int8 bagType;
	vector<int16> indexs;
	void Send(IOSocket* pIOSock);
};
void WriteGSWithC_BagDeleteItems(stNetMsg& msg,GSWithC_BagDeleteItems& value);
bool OnGSWithC_BagDeleteItems(GSWithC_BagDeleteItems* value);
void ReadGSWithC_BagDeleteItems(stNetMsg& msg,GSWithC_BagDeleteItems& value);

struct GSWithC_ExchangeBagItem
{
	int8 bagType;
	int8 index1;
	int8 index2;
	void Send(IOSocket* pIOSock);
};
void WriteGSWithC_ExchangeBagItem(stNetMsg& msg,GSWithC_ExchangeBagItem& value);
bool OnGSWithC_ExchangeBagItem(GSWithC_ExchangeBagItem* value);
void ReadGSWithC_ExchangeBagItem(stNetMsg& msg,GSWithC_ExchangeBagItem& value);

struct C2GS_BagSort
{
	int8 bagType;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_BagSort(stNetMsg& msg,C2GS_BagSort& value);
void ReadC2GS_BagSort(stNetMsg& msg,C2GS_BagSort& value);

struct GS2C_SignalItemInfo
{
	int64 id;
	int32 itemDataId;
	int16 count;
	int8 isBind;
	int8 refineLevel;
	int8 enhanceLevel;
	int32 score;
};
void WriteGS2C_SignalItemInfo(stNetMsg& msg,GS2C_SignalItemInfo& value);
bool OnGS2C_SignalItemInfo(GS2C_SignalItemInfo* value);
void ReadGS2C_SignalItemInfo(stNetMsg& msg,GS2C_SignalItemInfo& value);

struct Mail_Info
{
	int64 mailId;
	int32 mailSendTime;
	int32 mailReadState;
	int8 mailType;
	string mailSendName;
	string mailTitle;
	string mailContent;
	int32 money;
	vector<GS2C_SignalItemInfo> vec;
};
void WriteMail_Info(stNetMsg& msg,Mail_Info& value);
void ReadMail_Info(stNetMsg& msg,Mail_Info& value);

struct GS2C_All_Mail_Info
{
	vector<Mail_Info> vec;
};
void WriteGS2C_All_Mail_Info(stNetMsg& msg,GS2C_All_Mail_Info& value);
bool OnGS2C_All_Mail_Info(GS2C_All_Mail_Info* value);
void ReadGS2C_All_Mail_Info(stNetMsg& msg,GS2C_All_Mail_Info& value);

struct GS2C_Send_Mail
{
	Mail_Info st;
};
void WriteGS2C_Send_Mail(stNetMsg& msg,GS2C_Send_Mail& value);
bool OnGS2C_Send_Mail(GS2C_Send_Mail* value);
void ReadGS2C_Send_Mail(stNetMsg& msg,GS2C_Send_Mail& value);

struct GS2C_Chat
{
	int8 channelId;
	int8 isVip;
	int64 senderId;
	string senderName;
	string message;
	vector<GS2C_SignalItemInfo> vec;
};
void WriteGS2C_Chat(stNetMsg& msg,GS2C_Chat& value);
bool OnGS2C_Chat(GS2C_Chat* value);
void ReadGS2C_Chat(stNetMsg& msg,GS2C_Chat& value);

struct C2GS_LookOverPlayerEquip
{
	int64 playerId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_LookOverPlayerEquip(stNetMsg& msg,C2GS_LookOverPlayerEquip& value);
void ReadC2GS_LookOverPlayerEquip(stNetMsg& msg,C2GS_LookOverPlayerEquip& value);

struct GS2C_LookOverPlayerEquip_Result
{
	int8 retCode;
	int64 playerId;
	string playerName;
	string leagueName;
	int16 level;
	int8 career;
	int8 sex;
	int32 weapon;
	int32 armor;
	int32 wing;
	vector<EquipItem> equipItems;
};
void WriteGS2C_LookOverPlayerEquip_Result(stNetMsg& msg,GS2C_LookOverPlayerEquip_Result& value);
bool OnGS2C_LookOverPlayerEquip_Result(GS2C_LookOverPlayerEquip_Result* value);
void ReadGS2C_LookOverPlayerEquip_Result(stNetMsg& msg,GS2C_LookOverPlayerEquip_Result& value);

struct EquipId
{
	int64 equipId;
	int32 cnt;
};
void WriteEquipId(stNetMsg& msg,EquipId& value);
void ReadEquipId(stNetMsg& msg,EquipId& value);

struct C2GS_SelectEquipCompose
{
	int8 equipComposeOrder;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SelectEquipCompose(stNetMsg& msg,C2GS_SelectEquipCompose& value);
void ReadC2GS_SelectEquipCompose(stNetMsg& msg,C2GS_SelectEquipCompose& value);

struct GS2C_SelectEquipCompose
{
	int8 retCode;
};
void WriteGS2C_SelectEquipCompose(stNetMsg& msg,GS2C_SelectEquipCompose& value);
bool OnGS2C_SelectEquipCompose(GS2C_SelectEquipCompose* value);
void ReadGS2C_SelectEquipCompose(stNetMsg& msg,GS2C_SelectEquipCompose& value);

struct C2GS_ConfirmEquipComposeOrder
{
	int8 equipComposeOrder;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ConfirmEquipComposeOrder(stNetMsg& msg,C2GS_ConfirmEquipComposeOrder& value);
void ReadC2GS_ConfirmEquipComposeOrder(stNetMsg& msg,C2GS_ConfirmEquipComposeOrder& value);

struct C2GS_UseItem
{
	int8 bagType;
	int32 index;
	int64 itemId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_UseItem(stNetMsg& msg,C2GS_UseItem& value);
void ReadC2GS_UseItem(stNetMsg& msg,C2GS_UseItem& value);

struct GS2C_UseItem_Result
{
	int8 retCode;
};
void WriteGS2C_UseItem_Result(stNetMsg& msg,GS2C_UseItem_Result& value);
bool OnGS2C_UseItem_Result(GS2C_UseItem_Result* value);
void ReadGS2C_UseItem_Result(stNetMsg& msg,GS2C_UseItem_Result& value);

struct C2GS_StartEquipStrengthen
{
	int64 equipId;
	int8 isUseLuckyStone;
	int8 isAutoBuyLuckyStone;
	int8 isAutoBuyStrengthenStone;
	int8 isTenStrengthen;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_StartEquipStrengthen(stNetMsg& msg,C2GS_StartEquipStrengthen& value);
void ReadC2GS_StartEquipStrengthen(stNetMsg& msg,C2GS_StartEquipStrengthen& value);

struct GS2C_StartEquipStrengthen
{
	int8 retCode;
};
void WriteGS2C_StartEquipStrengthen(stNetMsg& msg,GS2C_StartEquipStrengthen& value);
bool OnGS2C_StartEquipStrengthen(GS2C_StartEquipStrengthen* value);
void ReadGS2C_StartEquipStrengthen(stNetMsg& msg,GS2C_StartEquipStrengthen& value);

struct GS2C_EquipLevelChange
{
	int64 id;
	int32 level;
	int32 score;
};
void WriteGS2C_EquipLevelChange(stNetMsg& msg,GS2C_EquipLevelChange& value);
bool OnGS2C_EquipLevelChange(GS2C_EquipLevelChange* value);
void ReadGS2C_EquipLevelChange(stNetMsg& msg,GS2C_EquipLevelChange& value);

struct GS2C_DesPlayer_LockTrade_Result
{
	int32 coin;
	vector<GS2C_SignalItemInfo> vec;
};
void WriteGS2C_DesPlayer_LockTrade_Result(stNetMsg& msg,GS2C_DesPlayer_LockTrade_Result& value);
bool OnGS2C_DesPlayer_LockTrade_Result(GS2C_DesPlayer_LockTrade_Result* value);
void ReadGS2C_DesPlayer_LockTrade_Result(stNetMsg& msg,GS2C_DesPlayer_LockTrade_Result& value);

struct GS2C_InputItem_Result
{
	int32 coin;
	vector<GS2C_SignalItemInfo> vec;
};
void WriteGS2C_InputItem_Result(stNetMsg& msg,GS2C_InputItem_Result& value);
bool OnGS2C_InputItem_Result(GS2C_InputItem_Result* value);
void ReadGS2C_InputItem_Result(stNetMsg& msg,GS2C_InputItem_Result& value);

struct C2GS_SetBagGrid
{
	int8 bagType;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SetBagGrid(stNetMsg& msg,C2GS_SetBagGrid& value);
void ReadC2GS_SetBagGrid(stNetMsg& msg,C2GS_SetBagGrid& value);

struct GS2C_SetBagGrid
{
	int8 bagType;
	int32 newNum;
	int8 retCode;
};
void WriteGS2C_SetBagGrid(stNetMsg& msg,GS2C_SetBagGrid& value);
bool OnGS2C_SetBagGrid(GS2C_SetBagGrid* value);
void ReadGS2C_SetBagGrid(stNetMsg& msg,GS2C_SetBagGrid& value);

struct C2GS_SplitItem
{
	int8 bagType;
	int32 itemCnt;
	int64 itemId;
	int32 splitItemCnt;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SplitItem(stNetMsg& msg,C2GS_SplitItem& value);
void ReadC2GS_SplitItem(stNetMsg& msg,C2GS_SplitItem& value);

struct GS2C_SplitItem
{
	int8 retCode;
};
void WriteGS2C_SplitItem(stNetMsg& msg,GS2C_SplitItem& value);
bool OnGS2C_SplitItem(GS2C_SplitItem* value);
void ReadGS2C_SplitItem(stNetMsg& msg,GS2C_SplitItem& value);

struct GS2C_Tip_Msg
{
	int32 tipId;
	string args;
	vector<GS2C_SignalItemInfo> vec;
};
void WriteGS2C_Tip_Msg(stNetMsg& msg,GS2C_Tip_Msg& value);
bool OnGS2C_Tip_Msg(GS2C_Tip_Msg* value);
void ReadGS2C_Tip_Msg(stNetMsg& msg,GS2C_Tip_Msg& value);

struct C2GS_DropItem
{
	int8 bagType;
	int32 index;
	int64 itemId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_DropItem(stNetMsg& msg,C2GS_DropItem& value);
void ReadC2GS_DropItem(stNetMsg& msg,C2GS_DropItem& value);

struct GS2C_Sale_PutOnItem_Result
{
	int8 retCode;
	int64 saleId;
	GS2C_SignalItemInfo saleItem;
};
void WriteGS2C_Sale_PutOnItem_Result(stNetMsg& msg,GS2C_Sale_PutOnItem_Result& value);
bool OnGS2C_Sale_PutOnItem_Result(GS2C_Sale_PutOnItem_Result* value);
void ReadGS2C_Sale_PutOnItem_Result(stNetMsg& msg,GS2C_Sale_PutOnItem_Result& value);

struct sale_filter_item
{
	int32 price;
	int64 saleId;
	GS2C_SignalItemInfo saleItem;
};
void Writesale_filter_item(stNetMsg& msg,sale_filter_item& value);
void Readsale_filter_item(stNetMsg& msg,sale_filter_item& value);

struct GS2C_Sale_Filter_Item_Result
{
	int8 isNextPage;
	int32 totalPage;
	vector<sale_filter_item> saleVec;
};
void WriteGS2C_Sale_Filter_Item_Result(stNetMsg& msg,GS2C_Sale_Filter_Item_Result& value);
bool OnGS2C_Sale_Filter_Item_Result(GS2C_Sale_Filter_Item_Result* value);
void ReadGS2C_Sale_Filter_Item_Result(stNetMsg& msg,GS2C_Sale_Filter_Item_Result& value);

struct GS2C_Sale_Find_Item_Result
{
	int8 isNextPage;
	int32 totalPage;
	vector<sale_filter_item> saleVec;
};
void WriteGS2C_Sale_Find_Item_Result(stNetMsg& msg,GS2C_Sale_Find_Item_Result& value);
bool OnGS2C_Sale_Find_Item_Result(GS2C_Sale_Find_Item_Result* value);
void ReadGS2C_Sale_Find_Item_Result(stNetMsg& msg,GS2C_Sale_Find_Item_Result& value);

struct my_sale_item
{
	int32 price;
	int32 remainTime;
	int64 saleId;
	GS2C_SignalItemInfo saleItem;
};
void Writemy_sale_item(stNetMsg& msg,my_sale_item& value);
void Readmy_sale_item(stNetMsg& msg,my_sale_item& value);

struct my_sale_gold
{
	int32 price;
	int32 remainTime;
	int64 saleId;
	int32 goldType;
};
void Writemy_sale_gold(stNetMsg& msg,my_sale_gold& value);
void Readmy_sale_gold(stNetMsg& msg,my_sale_gold& value);

struct GS2C_Sale_My_Sale_Item
{
	vector<my_sale_item> mySaleVec;
};
void WriteGS2C_Sale_My_Sale_Item(stNetMsg& msg,GS2C_Sale_My_Sale_Item& value);
bool OnGS2C_Sale_My_Sale_Item(GS2C_Sale_My_Sale_Item* value);
void ReadGS2C_Sale_My_Sale_Item(stNetMsg& msg,GS2C_Sale_My_Sale_Item& value);

struct GS2C_Sale_My_Sale_Gold
{
	vector<my_sale_gold> mySaleVec;
};
void WriteGS2C_Sale_My_Sale_Gold(stNetMsg& msg,GS2C_Sale_My_Sale_Gold& value);
bool OnGS2C_Sale_My_Sale_Gold(GS2C_Sale_My_Sale_Gold* value);
void ReadGS2C_Sale_My_Sale_Gold(stNetMsg& msg,GS2C_Sale_My_Sale_Gold& value);

struct GS2C_SubmitTaskChain
{
	int8 retCode;
	int16 taskChainCnt;
	int16 loopCnt;
	int32 startNpcDataId;
	int32 endNpcDataId;
	int32 taskId;
	int32 exp;
	int32 coin;
	int32 bindCoin;
	int32 honor;
	vector<GS2C_SignalItemInfo> awardItem;
	vector<GS2C_SignalItemInfo> awardRandItem;
};
void WriteGS2C_SubmitTaskChain(stNetMsg& msg,GS2C_SubmitTaskChain& value);
bool OnGS2C_SubmitTaskChain(GS2C_SubmitTaskChain* value);
void ReadGS2C_SubmitTaskChain(stNetMsg& msg,GS2C_SubmitTaskChain& value);

struct taskChainProgress
{
	int8 targetType;
	int32 targetCnt;
	int32 curCnt;
};
void WritetaskChainProgress(stNetMsg& msg,taskChainProgress& value);
void ReadtaskChainProgress(stNetMsg& msg,taskChainProgress& value);

struct GS2C_AcceptedTaskChain
{
	int32 taskId;
	int32 startNpcDataId;
	int32 endNpcDataId;
	int16 taskChainCnt;
	int16 loopCnt;
	vector<taskChainProgress> progress;
	int32 exp;
	int32 coin;
	int32 bindCoin;
	int32 honor;
	vector<GS2C_SignalItemInfo> awardItem;
	vector<GS2C_SignalItemInfo> awardRandItem;
};
void WriteGS2C_AcceptedTaskChain(stNetMsg& msg,GS2C_AcceptedTaskChain& value);
bool OnGS2C_AcceptedTaskChain(GS2C_AcceptedTaskChain* value);
void ReadGS2C_AcceptedTaskChain(stNetMsg& msg,GS2C_AcceptedTaskChain& value);

struct C2GS_TianShuSet_Req
{
	int8 index;
	int64 type;
	int8 solt;
	int16 bag_index;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_TianShuSet_Req(stNetMsg& msg,C2GS_TianShuSet_Req& value);
void ReadC2GS_TianShuSet_Req(stNetMsg& msg,C2GS_TianShuSet_Req& value);

struct GS2C_TianShuSet_Ret
{
	int8 retCode;
	int64 type;
	vector<EquipTianshu> tianShuList;
	BagItem newTianShu;
};
void WriteGS2C_TianShuSet_Ret(stNetMsg& msg,GS2C_TianShuSet_Ret& value);
bool OnGS2C_TianShuSet_Ret(GS2C_TianShuSet_Ret* value);
void ReadGS2C_TianShuSet_Ret(stNetMsg& msg,GS2C_TianShuSet_Ret& value);

struct GS2C_TianShuUpate
{
	BagItem newTianShu;
};
void WriteGS2C_TianShuUpate(stNetMsg& msg,GS2C_TianShuUpate& value);
bool OnGS2C_TianShuUpate(GS2C_TianShuUpate* value);
void ReadGS2C_TianShuUpate(stNetMsg& msg,GS2C_TianShuUpate& value);

struct GS2C_EquipTianShuUpate
{
	EquipItem newEquip;
};
void WriteGS2C_EquipTianShuUpate(stNetMsg& msg,GS2C_EquipTianShuUpate& value);
bool OnGS2C_EquipTianShuUpate(GS2C_EquipTianShuUpate* value);
void ReadGS2C_EquipTianShuUpate(stNetMsg& msg,GS2C_EquipTianShuUpate& value);

struct C2GS_TianShuTakeOff_Req
{
	int8 index;
	int64 type;
	int8 solt;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_TianShuTakeOff_Req(stNetMsg& msg,C2GS_TianShuTakeOff_Req& value);
void ReadC2GS_TianShuTakeOff_Req(stNetMsg& msg,C2GS_TianShuTakeOff_Req& value);

struct GS2C_TianShuTakeOff_Ret
{
	int8 retCode;
	int64 type;
	vector<EquipTianshu> tianShuList;
};
void WriteGS2C_TianShuTakeOff_Ret(stNetMsg& msg,GS2C_TianShuTakeOff_Ret& value);
bool OnGS2C_TianShuTakeOff_Ret(GS2C_TianShuTakeOff_Ret* value);
void ReadGS2C_TianShuTakeOff_Ret(stNetMsg& msg,GS2C_TianShuTakeOff_Ret& value);

struct tian_shu_material
{
	int16 index;
	int16 count;
};
void Writetian_shu_material(stNetMsg& msg,tian_shu_material& value);
void Readtian_shu_material(stNetMsg& msg,tian_shu_material& value);

struct C2GS_TianShuLvUp_Req
{
	int16 index;
	vector<tian_shu_material> materialList;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_TianShuLvUp_Req(stNetMsg& msg,C2GS_TianShuLvUp_Req& value);
void ReadC2GS_TianShuLvUp_Req(stNetMsg& msg,C2GS_TianShuLvUp_Req& value);

struct GS2C_TianShuLvUp_Ret
{
	int8 retCode;
	int8 newLv;
	int16 newExp;
};
void WriteGS2C_TianShuLvUp_Ret(stNetMsg& msg,GS2C_TianShuLvUp_Ret& value);
bool OnGS2C_TianShuLvUp_Ret(GS2C_TianShuLvUp_Ret* value);
void ReadGS2C_TianShuLvUp_Ret(stNetMsg& msg,GS2C_TianShuLvUp_Ret& value);

struct C2GS_TianShuCompose_Req
{
	vector<tian_shu_material> materialList;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_TianShuCompose_Req(stNetMsg& msg,C2GS_TianShuCompose_Req& value);
void ReadC2GS_TianShuCompose_Req(stNetMsg& msg,C2GS_TianShuCompose_Req& value);

struct GS2C_TianShuCompose_Ret
{
	int8 retCode;
	int16 itemDataId;
};
void WriteGS2C_TianShuCompose_Ret(stNetMsg& msg,GS2C_TianShuCompose_Ret& value);
bool OnGS2C_TianShuCompose_Ret(GS2C_TianShuCompose_Ret* value);
void ReadGS2C_TianShuCompose_Ret(stNetMsg& msg,GS2C_TianShuCompose_Ret& value);

struct C2GS_TianShuEquipContentLvUp_Req
{
	int64 type;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_TianShuEquipContentLvUp_Req(stNetMsg& msg,C2GS_TianShuEquipContentLvUp_Req& value);
void ReadC2GS_TianShuEquipContentLvUp_Req(stNetMsg& msg,C2GS_TianShuEquipContentLvUp_Req& value);

struct GS2C_TianShuEquipContentLvUp_Ret
{
	int8 retCode;
	int64 type;
};
void WriteGS2C_TianShuEquipContentLvUp_Ret(stNetMsg& msg,GS2C_TianShuEquipContentLvUp_Ret& value);
bool OnGS2C_TianShuEquipContentLvUp_Ret(GS2C_TianShuEquipContentLvUp_Ret* value);
void ReadGS2C_TianShuEquipContentLvUp_Ret(stNetMsg& msg,GS2C_TianShuEquipContentLvUp_Ret& value);

struct C2GS_TianShuEquipSoltLvUp_Req
{
	int64 type;
	int8 solt;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_TianShuEquipSoltLvUp_Req(stNetMsg& msg,C2GS_TianShuEquipSoltLvUp_Req& value);
void ReadC2GS_TianShuEquipSoltLvUp_Req(stNetMsg& msg,C2GS_TianShuEquipSoltLvUp_Req& value);

struct GS2C_TianShuEquipSoltLvUp_Ret
{
	int8 retCode;
	int64 type;
	int8 solt;
};
void WriteGS2C_TianShuEquipSoltLvUp_Ret(stNetMsg& msg,GS2C_TianShuEquipSoltLvUp_Ret& value);
bool OnGS2C_TianShuEquipSoltLvUp_Ret(GS2C_TianShuEquipSoltLvUp_Ret* value);
void ReadGS2C_TianShuEquipSoltLvUp_Ret(stNetMsg& msg,GS2C_TianShuEquipSoltLvUp_Ret& value);

struct GS2C_TianShuChangeIndex_Req
{
	int64 type;
	int8 index;
	void Send(IOSocket* pIOSock);
};
void WriteGS2C_TianShuChangeIndex_Req(stNetMsg& msg,GS2C_TianShuChangeIndex_Req& value);
void ReadGS2C_TianShuChangeIndex_Req(stNetMsg& msg,GS2C_TianShuChangeIndex_Req& value);

struct C2GS_TianShuChangeIndex_Ret
{
	int8 retCode;
	int64 type;
	int8 index;
};
void WriteC2GS_TianShuChangeIndex_Ret(stNetMsg& msg,C2GS_TianShuChangeIndex_Ret& value);
bool OnC2GS_TianShuChangeIndex_Ret(C2GS_TianShuChangeIndex_Ret* value);
void ReadC2GS_TianShuChangeIndex_Ret(stNetMsg& msg,C2GS_TianShuChangeIndex_Ret& value);

struct GS2C_TianShuChangeSolt_Req
{
	int64 type;
	int8 index;
	int8 solt;
	int8 newsolt;
	void Send(IOSocket* pIOSock);
};
void WriteGS2C_TianShuChangeSolt_Req(stNetMsg& msg,GS2C_TianShuChangeSolt_Req& value);
void ReadGS2C_TianShuChangeSolt_Req(stNetMsg& msg,GS2C_TianShuChangeSolt_Req& value);

struct C2GS_TianShuChangeSolt_Ret
{
	int8 retCode;
	int64 type;
	int8 index;
	int8 solt;
	int8 newsolt;
};
void WriteC2GS_TianShuChangeSolt_Ret(stNetMsg& msg,C2GS_TianShuChangeSolt_Ret& value);
bool OnC2GS_TianShuChangeSolt_Ret(C2GS_TianShuChangeSolt_Ret* value);
void ReadC2GS_TianShuChangeSolt_Ret(stNetMsg& msg,C2GS_TianShuChangeSolt_Ret& value);

struct PlayerGodDevice
{
	int8 isDress;
	int32 godDeviceCfgId;
	int8 refineLevel;
	int8 enhanceLevel;
	int64 equipId;
	vector<EquipTianshu> tianShuList;
	int8 content_lv;
	vector<TianshuSoltStreng> soltStrengList;
	int8 tian_shu_use_index;
};
void WritePlayerGodDevice(stNetMsg& msg,PlayerGodDevice& value);
void ReadPlayerGodDevice(stNetMsg& msg,PlayerGodDevice& value);

struct GS2C_PlayerGodDeviceList
{
	vector<PlayerGodDevice> playerGodDeviceList;
};
void WriteGS2C_PlayerGodDeviceList(stNetMsg& msg,GS2C_PlayerGodDeviceList& value);
bool OnGS2C_PlayerGodDeviceList(GS2C_PlayerGodDeviceList* value);
void ReadGS2C_PlayerGodDeviceList(stNetMsg& msg,GS2C_PlayerGodDeviceList& value);

struct C2GS_GainGodDevice
{
	int16 godDeviceCfgId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_GainGodDevice(stNetMsg& msg,C2GS_GainGodDevice& value);
void ReadC2GS_GainGodDevice(stNetMsg& msg,C2GS_GainGodDevice& value);

struct GS2C_GainGodDevice_Ret
{
	int8 errorCode;
	vector<PlayerGodDevice> playerGainGodDevice;
};
void WriteGS2C_GainGodDevice_Ret(stNetMsg& msg,GS2C_GainGodDevice_Ret& value);
bool OnGS2C_GainGodDevice_Ret(GS2C_GainGodDevice_Ret* value);
void ReadGS2C_GainGodDevice_Ret(stNetMsg& msg,GS2C_GainGodDevice_Ret& value);

struct C2GS_ChangeGodDevice
{
	int8 index;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ChangeGodDevice(stNetMsg& msg,C2GS_ChangeGodDevice& value);
void ReadC2GS_ChangeGodDevice(stNetMsg& msg,C2GS_ChangeGodDevice& value);

struct GS2C_ChangeGodDevice_Ret
{
	int8 errorCode;
	int8 oldIndex;
	int8 newIndex;
};
void WriteGS2C_ChangeGodDevice_Ret(stNetMsg& msg,GS2C_ChangeGodDevice_Ret& value);
bool OnGS2C_ChangeGodDevice_Ret(GS2C_ChangeGodDevice_Ret* value);
void ReadGS2C_ChangeGodDevice_Ret(stNetMsg& msg,GS2C_ChangeGodDevice_Ret& value);

struct GS2C_UpdateGodDevice_Ret
{
	PlayerGodDevice playerGodDevice;
};
void WriteGS2C_UpdateGodDevice_Ret(stNetMsg& msg,GS2C_UpdateGodDevice_Ret& value);
bool OnGS2C_UpdateGodDevice_Ret(GS2C_UpdateGodDevice_Ret* value);
void ReadGS2C_UpdateGodDevice_Ret(stNetMsg& msg,GS2C_UpdateGodDevice_Ret& value);

struct C2GS_Enhance
{
	int8 type;
	int64 equipId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Enhance(stNetMsg& msg,C2GS_Enhance& value);
void ReadC2GS_Enhance(stNetMsg& msg,C2GS_Enhance& value);

struct GS2C_Enhance_Ret
{
	int8 type;
	int64 equipId;
	int8 inWhere;
	int8 enhanceLevel;
};
void WriteGS2C_Enhance_Ret(stNetMsg& msg,GS2C_Enhance_Ret& value);
bool OnGS2C_Enhance_Ret(GS2C_Enhance_Ret* value);
void ReadGS2C_Enhance_Ret(stNetMsg& msg,GS2C_Enhance_Ret& value);

struct C2GS_Refine
{
	int8 type;
	int64 equipId;
	int8 isRefineMaxLevel;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Refine(stNetMsg& msg,C2GS_Refine& value);
void ReadC2GS_Refine(stNetMsg& msg,C2GS_Refine& value);

struct C2GS_Refine_All
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Refine_All(stNetMsg& msg,C2GS_Refine_All& value);
void ReadC2GS_Refine_All(stNetMsg& msg,C2GS_Refine_All& value);

struct PlayerRefine
{
	int8 type;
	int64 equipId;
	int8 inWhere;
	int8 refineLevel;
};
void WritePlayerRefine(stNetMsg& msg,PlayerRefine& value);
void ReadPlayerRefine(stNetMsg& msg,PlayerRefine& value);

struct GS2C_Refine_Ret
{
	int16 errorCode;
	vector<PlayerRefine> playerRefineList;
};
void WriteGS2C_Refine_Ret(stNetMsg& msg,GS2C_Refine_Ret& value);
bool OnGS2C_Refine_Ret(GS2C_Refine_Ret* value);
void ReadGS2C_Refine_Ret(stNetMsg& msg,GS2C_Refine_Ret& value);

struct Manufacture_Element
{
	int32 itemDataId;
	int8 eliminateCdFlag;
	int32 remainSeconds;
	int8 isDone;
};
void WriteManufacture_Element(stNetMsg& msg,Manufacture_Element& value);
void ReadManufacture_Element(stNetMsg& msg,Manufacture_Element& value);

struct GS2C_ManufactureList_Ret
{
	vector<Manufacture_Element> manufactureList;
};
void WriteGS2C_ManufactureList_Ret(stNetMsg& msg,GS2C_ManufactureList_Ret& value);
bool OnGS2C_ManufactureList_Ret(GS2C_ManufactureList_Ret* value);
void ReadGS2C_ManufactureList_Ret(stNetMsg& msg,GS2C_ManufactureList_Ret& value);

struct C2GS_New_Manufacture_Element
{
	int32 itemDataId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_New_Manufacture_Element(stNetMsg& msg,C2GS_New_Manufacture_Element& value);
void ReadC2GS_New_Manufacture_Element(stNetMsg& msg,C2GS_New_Manufacture_Element& value);

struct GS2C_New_Manufacture_Element_Ret
{
	int16 errorCode;
	Manufacture_Element manufactureElement;
};
void WriteGS2C_New_Manufacture_Element_Ret(stNetMsg& msg,GS2C_New_Manufacture_Element_Ret& value);
bool OnGS2C_New_Manufacture_Element_Ret(GS2C_New_Manufacture_Element_Ret* value);
void ReadGS2C_New_Manufacture_Element_Ret(stNetMsg& msg,GS2C_New_Manufacture_Element_Ret& value);

struct C2GS_Eliminate_Cd
{
	int32 itemDataId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Eliminate_Cd(stNetMsg& msg,C2GS_Eliminate_Cd& value);
void ReadC2GS_Eliminate_Cd(stNetMsg& msg,C2GS_Eliminate_Cd& value);

struct GS2C_Eliminate_Cd_Ret
{
	int16 errorCode;
	Manufacture_Element manufactureElement;
};
void WriteGS2C_Eliminate_Cd_Ret(stNetMsg& msg,GS2C_Eliminate_Cd_Ret& value);
bool OnGS2C_Eliminate_Cd_Ret(GS2C_Eliminate_Cd_Ret* value);
void ReadGS2C_Eliminate_Cd_Ret(stNetMsg& msg,GS2C_Eliminate_Cd_Ret& value);

struct C2GS_Gain_Item
{
	int32 itemDataId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Gain_Item(stNetMsg& msg,C2GS_Gain_Item& value);
void ReadC2GS_Gain_Item(stNetMsg& msg,C2GS_Gain_Item& value);

struct GS2C_Gain_Item_Ret
{
	int32 itemDataId;
	int16 errorCode;
};
void WriteGS2C_Gain_Item_Ret(stNetMsg& msg,GS2C_Gain_Item_Ret& value);
bool OnGS2C_Gain_Item_Ret(GS2C_Gain_Item_Ret* value);
void ReadGS2C_Gain_Item_Ret(stNetMsg& msg,GS2C_Gain_Item_Ret& value);

struct FightProperty
{
	int32 phy_dam;
	int32 fire_dam;
	int32 code_dam;
	int32 elec_dam;
	int32 toxin_dam;
	int16 base_dam_increase;
	int32 all_dam_increase;
	int32 all_dam_reduce;
	int32 atk_power;
	int64 hp_max;
	int32 hp_r;
	int32 hp_rp;
	int32 by_cure_factor;
	int32 mp_max;
	int32 mp_r;
	int16 speed;
	int32 armor;
	int16 phy_res;
	int16 fire_res;
	int16 cold_res;
	int16 elec_res;
	int16 toxin_res;
	int16 tough;
	int16 penetrate;
	int16 thickness;
	int32 crit_p;
	int32 crit_hurt;
	int32 accurate_p;
	int32 dodge_p;
	int32 trigger_p;
	int16 atk_speed_increase;
	int16 mp_efficiency;
	int16 skill_duration;
	int32 skill_power;
	int16 skill_rang;
	int32 hp_ball;
	int32 mp_ball;
	int16 armor_reduce;
};
void WriteFightProperty(stNetMsg& msg,FightProperty& value);
bool OnFightProperty(FightProperty* value);
void ReadFightProperty(stNetMsg& msg,FightProperty& value);

struct PetInfo
{
	int64 id;
	int32 dataId;
	int16 level;
	int32 exp;
	int16 strengLv;
	int8 isActive;
	FightProperty prop;
	vector<EquipTianshu> tianShuList;
	int8 content_lv;
	vector<TianshuSoltStreng> soltStrengList;
	int8 tian_shu_use_index;
};
void WritePetInfo(stNetMsg& msg,PetInfo& value);
void ReadPetInfo(stNetMsg& msg,PetInfo& value);

struct GS2C_AllPets
{
	vector<PetInfo> pets;
};
void WriteGS2C_AllPets(stNetMsg& msg,GS2C_AllPets& value);
bool OnGS2C_AllPets(GS2C_AllPets* value);
void ReadGS2C_AllPets(stNetMsg& msg,GS2C_AllPets& value);

struct GS2C_UpdatePetInfo
{
	int64 id;
	int32 dataId;
	int16 level;
	int32 exp;
	int16 strengLv;
	int8 isActive;
	FightProperty prop;
	vector<EquipTianshu> tianShuList;
	int8 content_lv;
	vector<TianshuSoltStreng> soltStrengList;
	int8 tian_shu_use_index;
};
void WriteGS2C_UpdatePetInfo(stNetMsg& msg,GS2C_UpdatePetInfo& value);
bool OnGS2C_UpdatePetInfo(GS2C_UpdatePetInfo* value);
void ReadGS2C_UpdatePetInfo(stNetMsg& msg,GS2C_UpdatePetInfo& value);


};


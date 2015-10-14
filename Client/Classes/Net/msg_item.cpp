#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_item(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_EquipGetItem_Ret);
 		CMD_DEAL(GS2C_EquipExchangeRet);
 		CMD_DEAL(GS2C_BagGetItems_Ret);
 		CMD_DEAL(GS2C_BagAddItem);
 		CMD_DEAL(GS2C_ItemCntChange);
 		CMD_DEAL(GSWithC_BagDeleteItems);
 		CMD_DEAL(GSWithC_ExchangeBagItem);
 		CMD_DEAL(GS2C_SignalItemInfo);
 		CMD_DEAL(GS2C_All_Mail_Info);
 		CMD_DEAL(GS2C_Send_Mail);
 		CMD_DEAL(GS2C_Chat);
 		CMD_DEAL(GS2C_LookOverPlayerEquip_Result);
 		CMD_DEAL(GS2C_SelectEquipCompose);
 		CMD_DEAL(GS2C_UseItem_Result);
 		CMD_DEAL(GS2C_StartEquipStrengthen);
 		CMD_DEAL(GS2C_EquipLevelChange);
 		CMD_DEAL(GS2C_DesPlayer_LockTrade_Result);
 		CMD_DEAL(GS2C_InputItem_Result);
 		CMD_DEAL(GS2C_SetBagGrid);
 		CMD_DEAL(GS2C_SplitItem);
 		CMD_DEAL(GS2C_Tip_Msg);
 		CMD_DEAL(GS2C_Sale_PutOnItem_Result);
 		CMD_DEAL(GS2C_Sale_Filter_Item_Result);
 		CMD_DEAL(GS2C_Sale_Find_Item_Result);
 		CMD_DEAL(GS2C_Sale_My_Sale_Item);
 		CMD_DEAL(GS2C_Sale_My_Sale_Gold);
 		CMD_DEAL(GS2C_SubmitTaskChain);
 		CMD_DEAL(GS2C_AcceptedTaskChain);
 		CMD_DEAL(GS2C_TianShuSet_Ret);
 		CMD_DEAL(GS2C_TianShuUpate);
 		CMD_DEAL(GS2C_EquipTianShuUpate);
 		CMD_DEAL(GS2C_TianShuTakeOff_Ret);
 		CMD_DEAL(GS2C_TianShuLvUp_Ret);
 		CMD_DEAL(GS2C_TianShuCompose_Ret);
 		CMD_DEAL(GS2C_TianShuEquipContentLvUp_Ret);
 		CMD_DEAL(GS2C_TianShuEquipSoltLvUp_Ret);
 		CMD_DEAL(C2GS_TianShuChangeIndex_Ret);
 		CMD_DEAL(C2GS_TianShuChangeSolt_Ret);
 		CMD_DEAL(GS2C_PlayerGodDeviceList);
 		CMD_DEAL(GS2C_GainGodDevice_Ret);
 		CMD_DEAL(GS2C_ChangeGodDevice_Ret);
 		CMD_DEAL(GS2C_UpdateGodDevice_Ret);
 		CMD_DEAL(GS2C_Enhance_Ret);
 		CMD_DEAL(GS2C_Refine_Ret);
 		CMD_DEAL(GS2C_ManufactureList_Ret);
 		CMD_DEAL(GS2C_New_Manufacture_Element_Ret);
 		CMD_DEAL(GS2C_Eliminate_Cd_Ret);
 		CMD_DEAL(GS2C_Gain_Item_Ret);
 		CMD_DEAL(FightProperty);
 		CMD_DEAL(GS2C_AllPets);
 		CMD_DEAL(GS2C_UpdatePetInfo);
 	END_DEAL();
	return false;
}

#include "GameDef.h"
#include "pk_item.h"
#include "GameScene/Hero.h"
#include "UI/ChatMainUI.h"
#include "GameScene/GridsManager.h"
#include "GameScene/MessageCenter.h"
#include "UI/MainUINormal.h"
#include "UI/MainUIFight.h"
#include "GameScene/TaskMgr.h"
#include "UI/TaskDialog.h"
#include "UI/RoleAttriUI.h"
#include "UI/SkyBookUI.h"
#include "UI/GodDeviceUI.h"
#include "UI/StrengthenUI.h"
#include "UI/ManufactureUI.h"
#include "UI/HallTechUI.h"

namespace pk{

	bool OnGS2C_LookOverPlayerEquip_Result(GS2C_LookOverPlayerEquip_Result* value)
	{
		return true;
	}


	bool OnGS2C_EquipGetItem_Ret(GS2C_EquipGetItem_Ret *value)
	{
		gGridsManager->removeAllGrids(emGrids_Role);

		for ( size_t i = 0;i<value->equipItems.size(); ++i )
		{
			EquipItem* pEquipItem = &(value->equipItems[i]);
			CItem* pItem = CItem::Create(pEquipItem);
			if ( pItem )
			{
				gGridsManager->insertGrid(emGrids_Role,pEquipItem->part,pItem,true);

				// 更新角色外观
				if ( EquipColumn_Weapon == pEquipItem->part )
				{
					gHero->SetWeapon(pItem->getArtID());
				}
			}
		}

		// 更新角色UI
		RoleAttriUI_cl * pui = dynamic_cast<RoleAttriUI_cl*>(gGameUILayer->getActiveUI(IDU_RoleAttri));
		if(pui)
		{
			pui->RefreshRoleEquip(value);
		}

		return true;
	}

	bool OnGS2C_EquipExchangeRet(GS2C_EquipExchangeRet *value)
	{
		RoleAttriUI_cl* pUI = dynamic_cast<RoleAttriUI_cl*>(gGameUILayer->getActiveUI(IDU_RoleAttri));
		if(pUI)
		{
			((ScrollGrids_cl*)pUI->getRoleEquipRoll())->freshRoleEquip(value);
		}

		if ( value->isEquip == 0 )	// 卸下
		{
			gHero->OnUnEquiped(value->index,EquipColumnType(value->part));
		}
		else						// 穿上
		{
			gHero->OnEquiped(value->index,EquipColumnType(value->part));
		}
		
		return true;
	}

	//整理背包或初始化背包数据
	bool OnGS2C_BagGetItems_Ret(GS2C_BagGetItems_Ret *value)
	{
		gGridsManager->resetGrids((emGridsType)value->bagType,value->getBagItems,value->bagGridNum);
		return true;
	}

	bool OnGS2C_BagAddItem(GS2C_BagAddItem *value)
	{
		emGridsType type = (emGridsType)value->bagType;
		CItem* pItem = CItem::Create(&value->addItem);
		if(pItem)
		{
			pItem->setNewAdd(true);
			gGridsManager->insertGrid(type,value->addItem.index,pItem,true);
		}

		/*
		-define(Get_Item_Reason_Gm, 0).
		-define(Get_Item_Reason_Mail, 1).
		-define(Get_Item_Reason_Pickup, 2).
		-define(Get_Item_Reason_Bag_Sort, 3).
		-define(Get_Item_Reason_Trade, 4).
		-define(Get_Item_Reason_SplitItem, 5).
		-define(Get_Item_Reason_Task, 6).
		-define(Get_Item_Reason_NpcShop, 7).
		-define(Get_Item_Reason_Sale, 8).
		-define(Get_Item_Reason_Mall, 9).
		-define(Get_Item_Reason_Gobang, 10).
		-define(Get_Item_Reason_Battle, 11).
		-define(Get_Item_Reason_TaskChain, 12).
		-define(Get_Item_Reason_LevelAward, 13).
		-define(Get_Item_Reason_LoginAward, 14).
		*/

		return true;
	}
	bool OnGS2C_ItemCntChange(GS2C_ItemCntChange *value)
	{
		emGridsType type = (emGridsType)value->bagType;
		gGridsManager->newGridCnt(type,value->index,value->newCount);
		int newAddCnt = value->newCount - value->oldCount;
		if (newAddCnt > 0)
		{
			CItem* pItem = gGridsManager->getGirdItem(type,value->index);
			if(pItem)
			{
				pItem->setNewAdd(true);
				gMessageCenter->SystemMessage(97, pItem->getItemData()->name.c_str(), CCString::createWithFormat("%d", newAddCnt)->getCString());
			}
		}
		return true;
	}
	bool OnGSWithC_BagDeleteItems(GSWithC_BagDeleteItems*value)
	{
		for (size_t i=0; i<value->indexs.size(); ++i)
		{
			gGridsManager->deleteGrid((emGridsType)value->bagType,value->indexs[i]);
		}
		gCocosAudio->PlayEffect(40);
		return true;
	}
	bool OnGSWithC_ExchangeBagItem(GSWithC_ExchangeBagItem *value)
	{
		return true;
	}

	bool OnGS2C_SignalItemInfo(GS2C_SignalItemInfo* value)
	{
		return true;
	}

	bool OnGS2C_Chat(GS2C_Chat *value)
	{
		MsgItem* pMsgItem = nullptr;
		ChatMainUI *pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);

		switch (value->channelId)
		{
		case ChannelType_Personal:
			{
				//客户端处理自己发送的私聊消息
				if (value->senderId == gHero->GetId()) return true;
				pMsgItem = gChatDataMgr->AddMsg(value->senderId,*value,false);
				pChatUI->PrivateMsgArrive(pMsgItem);
			}
			break;
		case ChannelType_Horn:
			{
				if(MainUI::GetActiveMainUI()) MainUI::GetActiveMainUI()->updateHornMsg(value);
				pMsgItem = gChatDataMgr->AddMsg(ChannelType(value->channelId),*value,value->senderId == gHero->GetId());
				pChatUI->MsgArrive(pMsgItem);
			}
			break;
		default:
			{
				pMsgItem = gChatDataMgr->AddMsg(ChannelType(value->channelId),*value,value->senderId == gHero->GetId());
				pChatUI->MsgArrive(pMsgItem);
			}
			break;
		}

		CHallTechUI* pUI = dynamic_cast<CHallTechUI*>(gGameUILayer->getActiveUI(IDU_HallTechUI));
		if (pUI)
		{
			pUI->updateChatMsg(value);
		}

		return true;
	}


	bool OnGS2C_UseItem_Result(GS2C_UseItem_Result *value)
	{
		switch (value->retCode)
		{
		case 1:
			gCocosAudio->PlayEffect(39);
			break;
		}
		return true;
	}
	bool OnGS2C_StartEquipStrengthen(GS2C_StartEquipStrengthen *value)
	{
		switch (value->retCode)
		{
		case -1:
			gMessageCenter->SystemMessage(22);			
			break;
		}
		return true;
	}

	bool OnGS2C_EquipLevelChange(GS2C_EquipLevelChange *value)
	{
// 		CItem* pItem = NULL;
// 		pItem = gGridsManager->findItemInGrids(emGrids_BagEquip,value->id);
// 		if (pItem)
// 		{
// 			pItem->setStrengthLv(value->level);
// 		}
// 		else
// 		{
// 			pItem = gGridsManager->findItemInGrids(emGrids_Role,value->id);
// 			if (pItem)
// 			{
// 				pItem->setStrengthLv(value->level);
// 			}
// 		}
		return true;
	}

	//激活格子
	bool OnGS2C_SetBagGrid(GS2C_SetBagGrid* value)
	{
		if (value->retCode == 1)
		{
			gGridsManager->ActiveOneLineGrids((emGridsType)value->bagType);
			gMessageCenter->SystemMessage(85);
		}
		else if (value->retCode == -3)
		{
			gMessageCenter->SystemMessage(86);
		}
		return true;
	}

	bool OnGS2C_SplitItem(GS2C_SplitItem* value)
	{
		if ( value->retCode == 1 )
		{
			//拆分成功
			gMessageCenter->SystemMessage(87);
			gCocosAudio->PlayEffect(42);
		} 
		else if ( value->retCode == -2 )
		{
			//数量不够
			gMessageCenter->SystemMessage(52);
		}
		else if (value->retCode == -4)
		{
			//背包已满
			gMessageCenter->SystemMessage(88);
		}
		return true;
	}

	bool OnGS2C_Tip_Msg(GS2C_Tip_Msg *value)
	{
		vector<string> des;
		StringSplit(value->args, ",", des);

		if (value->vec.size() == 0)
		{
			gMessageCenter->SystemMessage(value->tipId, des);
		}
		else
		{
			string strMsg;
			FormatMsgByArgFromVector(value->tipId, des, strMsg);

			for (int i = 0; i < (int)value->vec.size(); i++)
			{
				int nOffset = string::npos;
				if (string::npos != (nOffset = strMsg.find("&@")))
				{
					strMsg.replace(nOffset, 2, CCString::createWithFormat("%s%lld&@", "&@ItemID=", value->vec[i].id)->getCString());
				}
			}

			pk::GS2C_Chat cmd = {5, 0, 0, "System", strMsg, value->vec};
			MsgItem* pMsgItem = gChatDataMgr->AddMsg(ChannelType_System,cmd,false);
			ChatMainUI *pChatUI = (ChatMainUI*)gGameUILayer->getUI(IDU_CHATMAINUI);
			if (pChatUI)
			{
				pChatUI->MsgArrive(pMsgItem);
			}
		}
		return true;
	}

	bool OnGS2C_Sale_PutOnItem_Result(GS2C_Sale_PutOnItem_Result* value)
	{
		return true;
	}

	bool OnGS2C_Sale_Filter_Item_Result(GS2C_Sale_Filter_Item_Result* value)
	{
		return true;
	}

	bool OnGS2C_Sale_Find_Item_Result(GS2C_Sale_Find_Item_Result* value)
	{	
		return true;
	}

	bool OnGS2C_Sale_My_Sale_Item(GS2C_Sale_My_Sale_Item* value)
	{
		return true;
	}

	bool OnGS2C_Sale_My_Sale_Gold(GS2C_Sale_My_Sale_Gold* value)
	{
		return true;
	}

	bool OnGS2C_SubmitTaskChain(GS2C_SubmitTaskChain *value)
	{
		bool bFirstTurn = true;
		Task *pTask = gTaskManager->GetChainTask();
		if (pTask)	// 某个任务提交后删除对应提交NPC处的任务
		{
			MapObjectList objList;
			gMap->getObjectManager()->getObjectsInView(mapObjectType_Npc, objList);
			for (size_t i = 0; i < objList.size(); i++)
			{
				vector<int> &tasks = ((CNpc*)objList[i])->GetTaskFin();
				vector<int>::iterator it;
				if ((it = find(tasks.begin(), tasks.end(), pTask->GetID())) != tasks.end())
				{
					tasks.erase(it);
				}
			}
			gTaskManager->FinishTaskChain(pTask->GetID());
			bFirstTurn = false;
		}

		pTask = gTaskManager->SetAcceptableChain(value);
		TaskAward *pAward = pTask->GetAward();
		pAward->nCoin = value->coin;
		pAward->nExp = value->exp;
		pAward->nHonour = value->honor;
		pAward->nCoinB = value->bindCoin;

		for (size_t i = 0; i < value->awardItem.size(); i++)
		{
			TaskAward::ItemAward item = {ItemData.get(value->awardItem[i].itemDataId), value->awardItem[i].count, value->awardItem[i].isBind > 0};
			pAward->vtrItems.push_back(item);
		}

		if (!bFirstTurn)
		TaskDialog::Open(pTask);

		CNpc::s_AddtionalTasks.clear();
		CNpc::s_AddtionalTasks.clear();
		CNpc::s_AddtionalTasks.insert(make_pair(pTask->GetStage(TS_ACCEPT)->nTargetID, pTask));	// 接和交拆分成两个任务分别缓存
		CNpc::s_AddtionalTasks.insert(make_pair(pTask->GetStage(TS_TURNIN)->nTargetID, pTask));

		return true;
	}

	bool OnGS2C_AcceptedTaskChain(GS2C_AcceptedTaskChain *value)
	{
		Task* pTask = gTaskManager->AddTask(value->taskId);
		if (value->progress.size()) pTask->SetTargetCurNum(value->progress[0].curCnt);

		TaskStage *pStage = pTask->GetStage(TS_ACCEPT);
		NpcCfg *pNPC = NpcCfgData.get(value->startNpcDataId);

		pStage->nMapID = pNPC->map;
		pStage->nTargetID = pNPC->id;
		pStage->strTargetName = pNPC->name;
		pStage->ptPos = Point(pNPC->posx, pNPC->posy);

		pNPC = NpcCfgData.get(value->endNpcDataId);
		pStage = pTask->GetStage(TS_TURNIN);
		pStage->nMapID = pNPC->map;
		pStage->nTargetID = pNPC->id;
		pStage->strTargetName = pNPC->name;
		pStage->ptPos = Point(pNPC->posx, pNPC->posy);
		pTask->SetCurTurn(value->loopCnt);

		TaskAward *pAward = pTask->GetAward();
		pAward->nCoin = value->coin;
		pAward->nExp = value->exp;
		pAward->nHonour = value->honor;
		pAward->nCoinB = value->bindCoin;

		for (size_t i = 0; i < value->awardItem.size(); i++)
		{
			TaskAward::ItemAward item = {ItemData.get(value->awardItem[i].itemDataId), value->awardItem[i].count, value->awardItem[i].isBind > 0};
			pAward->vtrItems.push_back(item);
		}

		CNpc::s_AddtionalTasks.insert(make_pair(pTask->GetStage(TS_TURNIN)->nTargetID, pTask));

		return true;
	}

	bool OnGS2C_SelectEquipCompose(struct GS2C_SelectEquipCompose *value)
	{
		//must modify
		return true;
	}


	///////////////////////////////////////////////////////////////////////
	//天书网络处理
	///////////////////////////////////////////////////////////////////////

	//返回天书镶嵌 
	bool OnGS2C_TianShuSet_Ret( GS2C_TianShuSet_Ret* value )
	{
 		if(value && value->retCode == 1) //镶嵌成功
 		{
			SkyBookUI_cl * pUI = dynamic_cast<SkyBookUI_cl*>(gGameUILayer->getActiveUI(IDU_SkyBookUI));
			if(pUI)
			{
				pUI->updateInlay(value);
			}
 		}
 		else if(value && value->retCode == -1)   //系统错误
 		{
 
 		}
		return true;
	}

	bool OnC2GS_TianShuChangeIndex_Ret(C2GS_TianShuChangeIndex_Ret* value)
	{
		if(!value) return false;
		SkyBookUI_cl * pUI = dynamic_cast<SkyBookUI_cl*>(gGameUILayer->getActiveUI(IDU_SkyBookUI));
		if(pUI)
		{
			pUI->updateChangeConfigRet(value);
		}
		return true;
	}

	bool OnC2GS_TianShuChangeSolt_Ret(C2GS_TianShuChangeSolt_Ret* value)
	{
		if(!value) return false;
		SkyBookUI_cl * pUI = dynamic_cast<SkyBookUI_cl*>(gGameUILayer->getActiveUI(IDU_SkyBookUI));
		if(pUI)
		{
			pUI->updateChangeHoleRet(value);
		}
		return true;
	}

	//更新天书
	bool OnGS2C_TianShuUpate( GS2C_TianShuUpate* value )
	{
		if(!value) return true;
		CItem * item = gGridsManager->findItemByDataID(value->newTianShu.itemDataId);
		if(item)
		{
			item->InitBagItem(&value->newTianShu);
		}
		return true;
	}

	//装备天书信息变化更新
	bool OnGS2C_EquipTianShuUpate( GS2C_EquipTianShuUpate* value )
	{
		if(!value) return false;
		CItem * item = gGridsManager->findItemByDataID(value->newEquip.equipDataId);
		if(item)
		{
			item->InitEquipItem(&value->newEquip);
		}
		return true;
	}

	//取下天书
	bool OnGS2C_TianShuTakeOff_Ret( GS2C_TianShuTakeOff_Ret* value )
	{
// 		if(!value) return false;
// 		if(value->retCode == 1)
// 		{
// 			CItem * item = gGridsManager->findItemByDataID(value->newEquip.equipDataId);
// 			if(item)
// 			{
// 				item->InitEquipItem(&value->newEquip);
// 			}
// 		}
// 		else //-1: 超重不能取下
// 		{
// 
// 		}
		return true;
	}

	//天书升级
	bool OnGS2C_TianShuLvUp_Ret( GS2C_TianShuLvUp_Ret* value )
	{
		if(!value) return false;
		//-1: 材料数量不足,-2:已经是最大等级,-3:金钱不足 1:成功
		if(value->retCode == 1)
		{
			SkyBookUI_cl * pUI = dynamic_cast<SkyBookUI_cl*>(gGameUILayer->getActiveUI(IDU_SkyBookUI));
			if(pUI)
			{
				pUI->upgradeSkyBook(value->newLv, value->newExp);
			}
		}
		else if(value->retCode == -1)
		{

		}
		else if(value->retCode == -2)
		{

		}
		else if(value->retCode == -3)
		{

		}
		return true;
	}

	//天书合成
	bool OnGS2C_TianShuCompose_Ret( GS2C_TianShuCompose_Ret* value )
	{
		if(!value) return false;
		//-1: 金钱不足, 1:成功
		if(value->retCode == 1)
		{
			SkyBookUI_cl * pUI = dynamic_cast<SkyBookUI_cl*>(gGameUILayer->getActiveUI(IDU_SkyBookUI));
			if(pUI)
			{
				pUI->showNewSkyBook(value->itemDataId);
			}
		}
		else
		{

		}
		return true;
	}

	//装备天书容量强化
	bool OnGS2C_TianShuEquipContentLvUp_Ret( GS2C_TianShuEquipContentLvUp_Ret* value )
	{
 		if(!value) return false;
 		//-2: 金钱不足，-1材料不足，1:成功
 		if(value->retCode)
 		{
 			SkyBookUI_cl * pUI = dynamic_cast<SkyBookUI_cl*>(gGameUILayer->getActiveUI(IDU_SkyBookUI));
 			if(pUI)
 			{
 				pUI->updateCapacity(value->type);
 			}
 		}
 		else if(value->retCode == -1)
 		{
 		}
 		else
 		{
 		}
		return true;
	}

	//装备天书孔位强化
	bool OnGS2C_TianShuEquipSoltLvUp_Ret( GS2C_TianShuEquipSoltLvUp_Ret* value )
	{
		if(!value) return false;
		//-2: 金钱不足，-1材料不足，1:成功
		if(value->retCode == 1)
		{
			SkyBookUI_cl * pUI = dynamic_cast<SkyBookUI_cl*>(gGameUILayer->getActiveUI(IDU_SkyBookUI));
			if(pUI)
			{
				pUI->updateHole(value->type, value->solt);
			}
		}
		else if(value->retCode == -1)
		{

		}
		else
		{

		}
		return true;
	}

	///////////////////////////////////////////////////////////////////////
	//神器网络处理
	///////////////////////////////////////////////////////////////////////

	// 获得神器列表回调
	bool OnGS2C_PlayerGodDeviceList(GS2C_PlayerGodDeviceList* value)
	{
		for ( size_t i = 0;i<value->playerGodDeviceList.size();++i )
		{
			PlayerGodDevice info = value->playerGodDeviceList[i];
			gHero->AddGodDevice(info.godDeviceCfgId,info.isDress,info.refineLevel,info.enhanceLevel,info.equipId,info.tianShuList,info.content_lv,info.soltStrengList,info.tian_shu_use_index);
		}
		
		return true;
	}

	// 切换神器回调
	bool OnGS2C_ChangeGodDevice_Ret(GS2C_ChangeGodDevice_Ret* value)
	{
		switch (value->errorCode)
		{
		case 0:
			{	
				gHero->GetGodDeviceByIndex(value->oldIndex)->SetIsDress(0);
				gHero->GetGodDeviceByIndex(value->newIndex)->SetIsDress(1);

				CGodDeviceUI* pUI = dynamic_cast<CGodDeviceUI*>(gGameUILayer->getActiveUI(IDU_GodDeviceUI));
				if (pUI)
				{
					pUI->updateGodDeviceList();
				}

				break;
			}
		default:
			LOGE("OnGS2C_ChangeGodDevice_Ret Error，retCode:%d",value->errorCode);
			break;
		}
		return true;
	}

	// 新得到神器回调
	bool OnGS2C_GainGodDevice_Ret(GS2C_GainGodDevice_Ret* value)
	{
		switch (value->errorCode)
		{
		case 0:
			{
				gHero->ClearGodDevice();
				for ( size_t i = 0;i<value->playerGainGodDevice.size();++i )
				{
					PlayerGodDevice info = value->playerGainGodDevice[i];
					gHero->AddGodDevice(info.godDeviceCfgId,info.isDress,info.refineLevel,info.enhanceLevel,info.equipId,info.tianShuList,info.content_lv,info.soltStrengList,info.tian_shu_use_index);
				}

				CGodDeviceUI* pUI = dynamic_cast<CGodDeviceUI*>(gGameUILayer->getActiveUI(IDU_GodDeviceUI));
				if (pUI)
				{
					pUI->updateGodDeviceList();
				}
				break;
			}
		default:
			LOGE("OnGS2C_GainGodDevice_Ret Error，retCode:%d",value->errorCode);
			break;
		}
		return true;
	}

	bool OnGS2C_UpdateGodDevice_Ret(GS2C_UpdateGodDevice_Ret* value)
	{

		return true;
	}

	// 装备和神器进阶
	bool OnGS2C_Enhance_Ret(GS2C_Enhance_Ret* value)
	{
		if (value->type == 1)
		{
			gHero->GetGodDeviceManager().GetIsDressGodPtr()->SetEnhanceLevel(value->enhanceLevel);
		}else
		{
			if (value->inWhere == 1) // 背包
			{
				gGridsManager->findItemInGrids(emGrids_BagEquip,value->equipId)->setEnhanceLv(value->enhanceLevel);
			}else if(value->inWhere == 2)// 角色身上
			{
				gGridsManager->findItemInGrids(emGrids_Role,value->equipId)->setEnhanceLv(value->enhanceLevel);
			}
		}
		LOGE("OnGS2C_Enhance_Ret succeed.");
		CStrengthenUI* pUI = dynamic_cast<CStrengthenUI*>(gGameUILayer->getActiveUI(IDU_StrengthenUI));
		if (pUI)
		{
			pUI->updatejinjie();
		}
		return true;
	}

	bool OnGS2C_Refine_Ret(GS2C_Refine_Ret* value)
	{
		if (value->errorCode == 0)
		{
			LOGE("GS2C_Refine_Ret succeed.");
			for (size_t i = 0;i<value->playerRefineList.size();i++)
			{
				PlayerRefine item_ = value->playerRefineList[i];
				if (item_.type == 1)
				{
					gHero->GetGodDeviceManager().GetIsDressGodPtr()->SetRefineLevel(item_.refineLevel);
				}else
				{
					if (item_.inWhere == 1) // 背包
					{
						gGridsManager->findItemInGrids(emGrids_BagEquip,item_.equipId)->setRefinedLv(item_.refineLevel);
					}else if(item_.inWhere == 2)// 角色身上
					{
						gGridsManager->findItemInGrids(emGrids_Role,item_.equipId)->setRefinedLv(item_.refineLevel);
					}
				}
			}

			CStrengthenUI* pUI = dynamic_cast<CStrengthenUI*>(gGameUILayer->getActiveUI(IDU_StrengthenUI));
			if (pUI)
			{
				pUI->updatejinglian();
			}
		}else
		{
			LOGE("GS2C_Refine_Ret Failed.%d",value->errorCode);
		}
		
		return true;
	}

	//初始化制造数据
	bool OnGS2C_ManufactureList_Ret( GS2C_ManufactureList_Ret* value )
	{
		if(!value) return false;
		gDataPool->initManuFactureList(value);
		return true;
	}

	//开启新的一条制造数据
	bool OnGS2C_New_Manufacture_Element_Ret( GS2C_New_Manufacture_Element_Ret* value )
	{
		gDataPool->addManuFactureData(value);
		ManufactureUI_cl* pUI = dynamic_cast<ManufactureUI_cl*>(gGameUILayer->getActiveUI(IDU_ManufactureUI));
		if(pUI)
		{
			pUI->startManufactureRet(value->errorCode);
		}
		return true;
	}

	//消除某一条制造的cd
	bool OnGS2C_Eliminate_Cd_Ret( GS2C_Eliminate_Cd_Ret* value )
	{
		if(!value) return false;
		gDataPool->cancelManuFactureCD(value);
		return true;
	}

	//完成某一条制造
	bool OnGS2C_Gain_Item_Ret( GS2C_Gain_Item_Ret* value )
	{
		if(!value) return false;
		if(value->errorCode == 0)
		{
			ManufactureUI_cl* pUI = dynamic_cast<ManufactureUI_cl*>(gGameUILayer->getActiveUI(IDU_ManufactureUI));
			if(pUI)
			{
				pUI->getLineRet(value->itemDataId);
			}
		}
		return true;
	}

	bool OnFightProperty(FightProperty* value)
	{
		return true;
	}

	bool OnGS2C_AllPets(GS2C_AllPets* value)
	{

		gHero->GetPetItemManager().Clear();

		for (size_t i = 0;i<value->pets.size();++i)
		{
			pk::PetInfo petInfo_ = value->pets[i];
			gHero->GetPetItemManager().Insert(petInfo_.id, petInfo_.dataId, petInfo_.level, petInfo_.exp, petInfo_.strengLv, petInfo_.isActive,
				 petInfo_.prop, petInfo_.tianShuList, petInfo_.content_lv, petInfo_.soltStrengList, petInfo_.tian_shu_use_index);
		}

		return true;
	}

	bool OnGS2C_UpdatePetInfo(GS2C_UpdatePetInfo* value)
	{
		CPetItem*  m_petData = gHero->GetPetItemManager().GetByID(value->id);
		if (m_petData!=nullptr)
		{
			m_petData->updateProperty(value->id, value->dataId, value->level, value->exp, value->strengLv, value->isActive,
				value->prop, value->tianShuList, value->content_lv, value->soltStrengList, value->tian_shu_use_index);
		}
		return true;
	}
}


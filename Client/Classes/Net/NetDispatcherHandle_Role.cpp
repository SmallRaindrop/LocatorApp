#include "GameDef.h"
#include "pk_role.h"
#include "pk_nonInGame.h"
#include "NetDispatcher.h"
#include "GameScene/Hero.h"
#include "GameScene/GameDataManager.h"
#include "GameScene/MessageCenter.h"
#include "UI/Relive.h"
#include "UI/MainUINormal.h"
#include "UI/MainUIFight.h"
#include "Log.h"
#include "UI/ReviveUI.h"
#include "UI/GodDeviceUI.h"
#include "UI/HallTechTreeUI.h"

namespace pk
{
	bool OnGS2C_PlayerProperty(GS2C_PlayerProperty *value)
	{
		gHero->setProperty(value);

		for ( size_t i = 0;i<value->skill_list.size();++i )
		{
			PlayerSkillInfo info = value->skill_list[i];
			CSkill* pSkill = gHero->AddSkill(info.skillId);
			if ( pSkill )
			{
				pSkill->SetCDTime(info.cdtime);
			}
		}
		
		for ( size_t i = 0;i<value->buff_list.size();++i )
		{
			PlayerBuffInfo info = value->buff_list[i];
			if (BuffData.get(info.buffDataId)->icon == "")
			{
				continue;
			}
			gHero->AddBuff(info.id,info.buffDataId,info.duration);
		}

		C2GS_EnterMap cmd;
		cmd.Send(gNetSocket);

		LOGI("request enter map ...");
		return true;
	}

	bool OnGS2C_PlayerFightProperty(GS2C_PlayerFightProperty * value)
	{    
		gHero->setFightProperty(value);

		return true;
	}

	bool OnGS2C_PlayerSingleProperty(GS2C_PlayerSingleProperty* value)   //玩家自己属性的改变;
	{
		gHero->setSingleProperty(RoleProperty(value->type),value->value);
		return true;
	}

	bool OnGS2C_PlayerSinglePropertyStr(GS2C_PlayerSinglePropertyStr* value)   //玩家自己属性的改变;
	{ 
		gHero->GetData()->SetProperty(RoleProperty(value->type),value->value);
		return true;
	}

	bool  OnGS2C_PlayerSinglePropertySync(GS2C_PlayerSinglePropertySync * value)  //广播其他玩家的属性改变;
	{ 
		if(value->playerID == gHero->GetId())
		{
			gHero->setSingleProperty(RoleProperty(value->type),value->value);
		}
		else
		{
			RoleFighter* pRole = GetMapRole(value->playerID);
			if ( pRole )
			{
				pRole->SetProperty(RoleProperty(value->type),value->value);
				pRole->SetProperty(RoleProperty(value->type),(int)value->value);
			}
		}
		return true;
	}
	bool  OnGS2C_PlayerSinglePropertyStrSync(GS2C_PlayerSinglePropertyStrSync* value)
	{
		RoleFighter* pRole = GetMapRole(value->playerID);
		if ( pRole )
		{
			pRole->SetProperty(RoleProperty(value->type),value->value);
		}
		return true;
	}
	bool OnGS2C_PlayerMultiplePropertySync(GS2C_PlayerMultiplePropertySync *value)
	{
		RoleFighter* pRole = GetMapRole(value->playerID);
		if ( pRole )
		{
			for ( size_t i = 0;i<value->playerProperties.size();++i )
			{
				PlayerProperty* pData = &(value->playerProperties[i]);
				pRole->SetProperty(RoleProperty(pData->type),pData->value);
				pRole->SetProperty(RoleProperty(pData->type),(int)pData->value);
			}
		}
		return true;
	}

	bool OnGS2U_UseSkill(GS2U_UseSkill* value)
	{
		// caster can be player or monster  GetMapRole
		RoleFighter* pRole = GetMapRole(value->casterId);
		if ( pRole && pRole != gHero)
		{
			SkillCfg* pSkillData = SkillData.get(value->skillId);
			if ( pSkillData )
			{
				pRole->MagicAttack(pSkillData,value->targetId,value->offsetX,value->offsetY);
			}
		}
		return true;
	}

	bool OnGS2U_RoleEffect(GS2U_RoleEffect* value)
	{
		for ( size_t i = 0;i<value->effects.size(); ++i )
		{
			pk::RoleEffectInfo* pRoleEffectInfo = &value->effects[i];
			if ( pRoleEffectInfo )
			{
				MapObject * pObject = gMap->getObjectManager()->getObject(pRoleEffectInfo->targetId);
				if(pObject)
				{
					MapObjectType pType = (MapObjectType)pObject->GetType();
					switch (pType)
					{
					case mapObjectType_None:
						break;
					case mapObjectType_Mask:
						break;
					case mapObjectType_Effect:
						break;
					case mapObjectType_Item:
						{
							CMapItem* pItem = dynamic_cast<CMapItem*>(pObject);
							if ( pItem )
							{
								auto logicPoint = pItem->getPosition();
								if(pItem->GetItemData()->drop_art != "")
								{
									gMap->ShowEffect(pItem->getDispArtID(),pItem->getDispArtName(),logicPoint,0.5f);
								}
								
								pItem->LeaveMap();
							}
							RoleFighter * pRole = GetMapRole(pRoleEffectInfo->castId);
							if(pRole)
							{
								TIME_COST_BEGIN;
								pRole->ShowRoleEffect(pRoleEffectInfo);
								TIME_COST_LOG_IF("ShowRoleEffect",1);
							}
							break;
						}
					case mapObjectType_Chests:
					case mapObjectType_Npc:
					case mapObjectType_Monster:
					case mapObjectType_Player:
						{
							RoleFighter* pRole = dynamic_cast<RoleFighter*>(pObject);
							if ( pRole )
							{
								TIME_COST_BEGIN;
								pRole->ShowRoleEffect(pRoleEffectInfo);
								TIME_COST_LOG_IF("ShowRoleEffect",1);
							}
							break;
						}
					case mapObjectType_Max:
						break;
					default:
						break;
					}
				}


			}
		}
		return true;
	}


	bool OnGS2U_BufferAttach(GS2U_BufferAttach* value)
	{ 
		gHero->AddBuff(value->id,value->buffDataId,value->duration);
		if ( MainUI::GetActiveMainUI() )
		{
			MainUI::GetActiveMainUI()->updateBuff();
		}
		return true;
	}

	bool OnGS2U_BufferRemove(GS2U_BufferRemove* value)
	{ 
		gHero->RemoveBuff(value->id);
		if ( MainUI::GetActiveMainUI() )
		{
			MainUI::GetActiveMainUI()->updateBuff();
		}
		return true;
	}

	bool OnGS2U_AddSkillList(GS2U_AddSkillList* value)
	{
		for ( size_t i = 0;i<value->skill_list.size();++i )
		{
			PlayerSkillInfo info = value->skill_list[i];
			CSkill* pSkill = gHero->AddSkill(info.skillId);
			if ( pSkill )
			{
				pSkill->SetCDTime(info.cdtime);
			}

			if ( !pSkill->IsPassive() )
			{
				gCocosAudio->PlayEffect(47);
				gMessageCenter->SystemMessage(138,pSkill->GetData()->name.c_str());
			}
		}

		if( MainUI::GetActiveMainUI() )
		{
			MainUI::GetActiveMainUI()->updateSkillBtns();
		}

		CGodDeviceUI* pUI = dynamic_cast<CGodDeviceUI*>(gGameUILayer->getActiveUI(IDU_GodDeviceUI));
		if (pUI)
		{
			pUI->updateGodDeviceList();
		}

		return true;
	}

	bool OnGS2U_RemoveSkillList(GS2U_RemoveSkillList * value)
	{
		for ( size_t i = 0;i<value->skill_id_list.size();++i )
		{
			gHero->RemoveSkill(value->skill_id_list[i]);
		}

		if( MainUI::GetActiveMainUI() )
		{
			MainUI::GetActiveMainUI()->updateSkillBtns();
		}

		CGodDeviceUI* pUI = dynamic_cast<CGodDeviceUI*>(gGameUILayer->getActiveUI(IDU_GodDeviceUI));
		if (pUI)
		{
			pUI->updateGodDeviceList();
		}
		return true;
	}

	

	bool OnGS2U_LevelChangeSkillList(GS2U_LevelChangeSkillList * value)
	{
		for ( size_t i = 0;i<value->skill_list.size();++i )
		{
			PlayerSkillInfo info = value->skill_list[i];
			CSkill* pSkill = gHero->GetSkill(info.skillId);
			if ( pSkill )
			{
				pSkill->SetLevel(info.level);

				if ( !pSkill->IsPassive() )
				{
					gCocosAudio->PlayEffect(47);
					gMessageCenter->SystemMessage(139,pSkill->GetData()->name.c_str(),info.level);
				}
			}
		}

		if( MainUI::GetActiveMainUI() )
		{
			MainUI::GetActiveMainUI()->updateSkillBtns();
		}

		CGodDeviceUI* pUI = dynamic_cast<CGodDeviceUI*>(gGameUILayer->getActiveUI(IDU_GodDeviceUI));
		if (pUI)
		{
			pUI->updateGodDeviceList();
		}
		return true;
	}

	
	bool OnGS2C_CdUseItem(GS2C_CdUseItem* value)
	{
		return true;
	}

	bool OnGS2C_NextAttack_Is_GongSha(GS2C_NextAttack_Is_GongSha *value)
	{
		return true;
	}

	bool OnGS2C_SkillShortCutConfig(GS2C_SkillShortCutConfig* value)
	{
		return true;
	}

	bool OnGS2C_RecoverLife_Ret(GS2C_RecoverLife_Ret *value)
	{
		switch (value->retCode)
		{
		case 0:
			gHero->SetProperty(RoleProperty_RecoverCount,value->recoverCount);	                //免费复活次数
			break;
		case 1:
			gMessageCenter->SystemMessage(220);
			break;
		case 2:
			gMessageCenter->SystemMessage(217);
			break;
		case 3:
			gMessageCenter->SystemMessage(22);
			break;
		}
		return true;
	}

	bool OnGS2C_WingInfo(GS2C_WingInfo  *value)
	{

		return true;
	}

	bool OnGS2C_AddWing(GS2C_AddWing *value)
	{

		return true;
	}

	bool OnGS2C_ReplaceWing(GS2C_ReplaceWing *value)
	{

		return true;
	}


	bool OnGS2C_PlayerFightingCapacityChange(GS2C_PlayerFightingCapacityChange *)
	{
		//must modify
		return true;
	}

	bool OnGS2U_UseTransferSkill(struct GS2U_UseTransferSkill *)
	{
		return true;
	}

	bool OnGS2C_HelpRecover_Ret(GS2C_HelpRecover_Ret* value)
	{
		RoleFighter* role_fighter_ = GetMapRole(value->playerID);
		if (role_fighter_ == nullptr)
		{
			LOGE("OnGS2C_HelpRecover_Ret role_fighter_ == nullptr");
			return false;
		}
		role_fighter_->SetDeadVirtualHelpNum((int)value->helpNum);
		role_fighter_->SetDeadVirtualRestTime((float)value->restTime);
		role_fighter_->SetDeadVirtualRestPoint((int)value->restPoint);
		role_fighter_->SetDeadVirtualPercent();
		return true;
	}

	bool OnGS2C_HallTechOpenList(GS2C_HallTechOpenList *openList)
	{
		gHero->GetHallTechManager().Clear();
		
		for (size_t i = 0;i<openList->openList.size();++i)
		{
		 	pk::hallTech hallTech_ = openList->openList[i];
			gHero->GetHallTechManager().Insert(hallTech_.id,hallTech_.lv,(double)(hallTech_.nextLvTime));
		}
		return true;
	}

	bool OnGS2C_HallTechLvUp_Ret(GS2C_HallTechLvUp_Ret *value)
	{
		//retCode;-1:升级中，-2，已经最大等级，-3，条件不足，-4金钱不足，-5材料不足，0: 成功  
		CHallTechTreeUI* pUI = dynamic_cast<CHallTechTreeUI*>(gGameUILayer->getActiveUI(IDU_HallTechTreeUI));
		switch (value->retCode)
		{
		case 0:
			if (gHero->GetHallTechManager().Get(value->id) == nullptr)
			{
				gHero->GetHallTechManager().Insert(value->id,0,(double)(value->nextLvTime));
			}else
			{
				gHero->GetHallTechManager().Get(value->id)->SetNextLvTime((double)(value->nextLvTime));
			}

			if (pUI)
			{
				pUI->UpdateAll();
			}

			break;
		case -1:
			//升级中
			break;
		case -2:
			//已经最大等级
			break;
		case -3:
			//条件不足
			break;
		case -4:
			//金钱不足
			break;
		case -5:
			//材料不足
			break;
		default:
			break;
		}
		return true;
	}

	bool OnGS2C_HallTechLvUp(GS2C_HallTechLvUp *value)
	{
		gHero->GetHallTechManager().Get(value->id)->SetLevel(value->lv);
		gHero->GetHallTechManager().Get(value->id)->SetNextLvTime(0.0);

		CHallTechTreeUI* pUI = dynamic_cast<CHallTechTreeUI*>(gGameUILayer->getActiveUI(IDU_HallTechTreeUI));
		if (pUI)
		{
			pUI->UpdateAll();
		}
		return true;
	}
}
	
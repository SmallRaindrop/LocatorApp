#include "GameDef.h"
#include "pk_map.h"
#include "pk_move.h"
#include "GameScene/GameManager.h"
#include "GameScene/GameDataManager.h"
#include "GameScene/Player.h"
#include "GameScene/Hero.h"
#include "GameScene/GameMap.h"
#include "GameScene/Monster.h"
#include "GameScene/MapItem.h"
#include "GameScene/NPC.h"
#include "GameScene/GameUILayer.h"
#include "Net/NetDispatcher.h"
#include "GameScene/GameLayer.h"
#include "GameScene/MessageCenter.h"
#include "UI/TeamUI.h"
#include "GameScene/BeyondMap.h"
#include "UI/MainUINormal.h"
#include "UI/MessageBoxUI.h"
#include "UI/MainUIFight.h"
#include "UI/LoadingUI.h"
#include "UI/WaveEnd.h"
#include "ui/CopyEnd.h"
#include "UI/UIWorldMap.h"
#include "DataPool.h"
#include "GameScene/Bullet.h"
#include "UI/copyMapUI.h"
#include "GameScene/Chests.h"
#include "GameScene/IndicatorLayer.h"
#include "UI/FreeFightScoreUI.h"
#include "UI/FreeFightCheckOut.h"
#include "UI/CopyMapUIFreeFight.h"
#include "UI/CopyMapUIContendFor.h"
#include "UI/CopyMapUISurvive.h"

namespace pk{

	bool OnGS2C_LookupPlayerPosRet(GS2C_LookupPlayerPosRet *value)
	{
		return true;
	}

	bool OnGS2C_LookupTeamPos(GS2C_LookupTeamPos *value)
	{
		return true;
	}

	bool OnGS2C_ChangeMap(struct pk::GS2C_ChangeMap *value)
	{
		if ( gLoadingUI->IsActive() )
		{
			gLoadingUI->SetPercent(50.f,2.0f);
		}
		else
		{
			gLoadingUI->Show(LOADRES_TYPE);
		}
		LOGD("==============OnGS2C_ChangeMap[%d][%d,%d]=================",value->mapDataID,value->x,value->y);
		gHero->ChangeMap(value->mapDataID,value->x,value->y);
		return true;
	}

	bool OnGS2C_LookInfoDynamicTransferDoor(GS2C_LookInfoDynamicTransferDoor *value)
	{
		// add dynamicTransferDoor to m_doors
		GameMap* pMap = gGameLayer->getCurrMap();
		if (!pMap->getRegionManager()->addDynamicTransferDoorIfNotExist(value->id,value->x,value->y,value->cx,value->cy))
		{
			//gMap->addEffect(1001001,value->x+value->cx/2,value->y+value->cy/2,false);
		}

		return true;
	}
	bool OnGS2C_LookInfoPet(GS2C_LookInfoPet *value)
	{
		return true;
	}

	bool OnGS2C_PetStopMove(GS2C_PetStopMove *value)
	{
		return true;
	}
	bool OnGS2C_PetMoveInfo(GS2C_PetMoveInfo *value)
	{
		return true;
	}

	bool  OnGS2C_RoleTeleport(GS2C_RoleTeleport *value)
	{
		if ( !gMap )
		{
			return true;
		}

		RoleFighter* pRole = GetMapRole(value->id);
		if ( pRole )
		{
			pRole->StopTo(value->posX,value->posY);

			if ( gHero == pRole )
			{
				gMap->updateView();
			}
		}
		
		
		return true;
	}


	bool  OnGS2C_SkillPushRoleList(GS2C_SkillPushRoleList *value)
	{
		return true;
	}



	bool OnGS2C_LookInfoItem(struct pk::GS2C_LookInfoItem *value)
	{
		if ( !gMap )
		{
			return false;
		}

		CMapItem* pMapItem = CMapItem::create();
		if ( pMapItem  && value->ownerId == gHero->GetId())
		{
			pMapItem->SetId(value->id);
			pMapItem->SetDataID(value->item_data_id);
			pMapItem->SetOwnerID(value->ownerId);
			pMapItem->EnterMap(gMap,value->x,value->y);

			// fix bug : 打怪掉落道具时，若人物正好在某个掉落道具的上方，则必须走出再走回才可拾取到该道具
			if (value->x == gHero->GetCellX() && value->y == gHero->GetCellY() && (!gHero->IsMoving() ) )
			{			
				C2GS_PickUpItem cmd;
				cmd.id = value->id;
				cmd.Send(gNetSocket);
				gCocosAudio->PlayEffect(13);
			}
		}
		return true;
	}


	bool OnGS2C_LookInfoNpc(struct pk::GS2C_LookInfoNpc *value)
	{
		if ( !gMap )
		{
			return false;
		}

		CNpc* pNPC = CNpc::create();
		if ( pNPC )
		{
			pNPC->SetId(value->id);
			//pNPC->SetDataID(value->npc_data_id);
			pNPC->SetDataID(1000000);

			pNPC->EnterMap(gMap,value->x,value->y);
		}

		return true;
	}

	bool OnGS2C_LookInfoMonster(struct pk::GS2C_LookInfoMonster *value)
	{	
		if ( !gMap )
		{
			return false;
		}

		TIME_COST_BEGIN;
		CMonster* pMonster = CMonster::create();
		TIME_COST_LOG_IF("OnGS2C_LookInfoMonster CMonster::create",3);
		if ( pMonster )
		{
			pMonster->SetId(value->id);
			pMonster->SetDataID(value->monster_data_id);
			pMonster->SetMoveSpeed(value->moveSpeed);
			pMonster->SetStateFlag(value->status);
			pMonster->SetCamp(value->camp);
			pMonster->SetProperty(RoleProperty_HP,value->hp);
			pMonster->SetProperty(RoleProperty_hp_max,value->hpMax);
			pMonster->SetProperty(RoleProperty_MP,value->mp);
			pMonster->SetProperty(RoleProperty_mp_max,value->mpMax);
			pMonster->EnterMap(gMap,value->x,value->y);
			TIME_COST_LOG_IF("OnGS2C_LookInfoMonster CMonster::EnterMap",3);
			if ( value->posInfos.size() > 0 )
			{
				APath path;
				CHero::PosInfoToPath(value->x,value->y,value->posInfos,path);
				pMonster->Move(path,value->movedMs);
			}
		}

		return true;
	}

	bool OnGS2C_LookInfoPlayer(struct pk::GS2C_LookInfoPlayer *value)
	{
		if ( !gMap )
		{
			return false;
		}

		CPlayer* pPlayer = CPlayer::create();
		if ( pPlayer )
		{
			pPlayer->SetId(value->id);
			pPlayer->SetRoleName(value->name);

			pPlayer->SetMoveSpeed(value->moveSpeed);
			pPlayer->SetCamp(value->camp);
			pPlayer->SetLevel(value->level);
			pPlayer->SetCareer(value->career);
			pPlayer->SetProperty(RoleProperty_Sex,value->sex);
			pPlayer->SetProperty(RoleProperty_HP,value->hp);
			pPlayer->SetProperty(RoleProperty_hp_max,value->hpMax);
			pPlayer->SetProperty(RoleProperty_MP,value->mp);
			pPlayer->SetProperty(RoleProperty_mp_max,value->mpMax);
			pPlayer->SetProperty(RoleProperty_VipLevel,value->vipLevel);
			pPlayer->SetProperty(RoleProperty_GuildID,value->guildId);
			pPlayer->SetProperty(RoleProperty_Achievement,value->achievementId);
			pPlayer->SetProperty(RoleProperty_Cloth,value->armor);
			pPlayer->SetProperty(RoleProperty_Weapon,value->weapon);
			pPlayer->SetProperty(RoleProperty_Wing,value->wing);

			LOGE("OnGS2C_LookInfoPlayer success");
			LOGE("value->helpNum:%d  value->restTime:%f  value->restPoint:%d  value->deadRestTime:%f",(int)value->helpNum,(float)value->restTime,(int)value->restPoint,(float)value->deadRestTime);

			pPlayer->EnterMap(gMap,value->x,value->y);
			if ( value->posInfos.size() > 0 )
			{
				APath path;
				CHero::PosInfoToPath(value->x,value->y,value->posInfos,path);
				pPlayer->Move(path,value->movedMs);
			}
			
			pPlayer->SetProperty(RoleProperty_StateFlag,value->status);
			pPlayer->SetDeadVirtualDeadRestTime((float)value->deadRestTime);
			pPlayer->SetDeadVirtualHelpNum((int)value->helpNum);
			pPlayer->SetDeadVirtualRestTime((float)value->restTime);
			pPlayer->SetDeadVirtualRestPoint((int)value->restPoint);
			pPlayer->SetDeadVirtualPercent();

		}

		return true;
	}

	bool OnGS2C_PlayerStopMove(struct pk::GS2C_PlayerStopMove *value)
	{
		CCLOG("Player stop move [%d][%d]",value->posX,value->posY);
		if ( !gMap )
		{
			return true;
		}

		CPlayer* pPlayer = GetMapPlayer(value->id);
		if ( pPlayer )
		{
			if ( pPlayer != gHero )
			{
				pPlayer->StopTo(value->posX,value->posY);
			}

			pPlayer->enableGhostShadow(false);
		}
		return true;
	}

	bool OnGS2C_ActorDisapearList(struct pk::GS2C_ActorDisapearList *value)
	{
		if ( !gMap )
		{
			return true;
		}

		for ( size_t i = 0;i<value->info_list.size(); ++i )
		{
			PlayerID id = value->info_list[i];
			MapObject* pObject = GetMapObject(id);
			if ( pObject )
			{
				pObject->LeaveMap();
			}
		}

		return true;
	}

	bool OnGS2C_PlayerMoveInfo(struct pk::GS2C_PlayerMoveInfo *value)
	{
		CPlayer* pPlayer = GetMapPlayer(value->id);
		if ( pPlayer )
		{
			APath path;
			CHero::PosInfoToPath(value->posX,value->posY,value->posInfos,path);
			pPlayer->Move(path);
		}
		return true;
	}

	bool  OnGS2C_MonsterStopMove(GS2C_MonsterStopMove *value)
	{
		if ( !gMap )
		{
			return true;
		}

		CMonster* pMonster = GetMapMonster(value->id);
		if ( pMonster)
		{
			////just for test
			//if(pMonster->GetPropertyInt(RoleProperty_Cloth) == 9006)
			//{
			//	CCLOG("stopmove,cur:(%d,%d),step:(%d,%d), posX:%d,posY:%d",	pMonster->GetCellX(),pMonster->GetCellY(),
			//		pMonster->GetStepX(),pMonster->GetStepY(), 
			//		value->posX,value->posY);
			//}

			pMonster->StopTo(value->posX,value->posY);
		}
		return true;
	}

	bool  OnGS2C_MonsterMoveInfo(GS2C_MonsterMoveInfo *value)
	{
		CMonster* pMonster = GetMapMonster(value->id);

		if ( pMonster )
		{
			////just for test
			//if(pMonster->GetPropertyInt(RoleProperty_Cloth) == 9006)
			//{
			//	CCLOG("move info,cur posX:%d,posY:%d", value->posX,value->posY);
			//	for ( size_t i = 0;i<value->posInfos.size();++i )
			//	{
			//		pk::PosInfo pt = value->posInfos[i];
			//		CCLOG("		path,(%d,%d)", pt.x,pt.y);				
			//	}
			//}

			APath path;
			CHero::PosInfoToPath(value->posX,value->posY,value->posInfos,path);
			pMonster->Move(path);
		}
		return true;
	}

	bool OnGS2C_UpdatPlayerCopyCDInfo(GS2C_UpdatPlayerCopyCDInfo  *value)
	{
		return true;
	}

	bool OnGS2C_AllCopyCDInfo(GS2C_AllCopyCDInfo *value)
	{
		return true;
	}

	bool  OnGS2C_CopyMapClose_Countdown(GS2C_CopyMapClose_Countdown *value)
	{
		return false;
	}

	bool OnGS2C_LookInfoTrap(GS2C_LookInfoTrap *value)
	{
		return true;
	}

	bool OnGS2C_MissileDamage(GS2C_MissileDamage *value)
	{
		return true;
	}
	




	/*副本初始化*/
	bool OnGS2C_CopyInitInfo(GS2C_CopyInitInfo* value)
	{
		if (gCopyDataMgr->GetCopyMapUI()) gCopyDataMgr->GetCopyMapUI()->UpdateCopyInitInfo(value);
		return true;
	}

	/*副本进度*/
	bool OnGS2C_UpdateCopyProgress(GS2C_UpdateCopyProgress *value)
	{
		if (gCopyDataMgr->GetCopyMapUI()) gCopyDataMgr->GetCopyMapUI()->UpdateCopyProgress(value);
		return true;
	}

	/*怪物波数*/
	bool OnGS2C_MonsterSpawnRemind(GS2C_MonsterSpawnRemind* value)
	{
		if (gCopyDataMgr->GetCopyMapUI()) gCopyDataMgr->GetCopyMapUI()->updateMonsterWave(value);
		return true;
	}

	bool OnGS2C_COPY_SUCC_TIME(GS2C_COPY_SUCC_TIME* value)
	{
		if(gCopyDataMgr->GetCopyMapUI()) gCopyDataMgr->GetCopyMapUI()->UpdateCountTime(value);
		return true;
	}

	bool OnGS2C_LivePoint(GS2C_LivePoint* value)
	{
		CCopyMapUISurvive* pCopySurvive = (CCopyMapUISurvive*)gGameUILayer->getUI(IDU_CopyUISurvive);
		if(pCopySurvive)
		{
			pCopySurvive->updateLivePoint(value);
		}
		return true;
	}

	/*5波结板5秒后收到此消息*/
	bool  OnGS2C_CopyMapCompleted(GS2C_CopyMapCompleted *value)
	{
		//	int8  isContinue;  1: 继续  0:结束副本
		gGameUILayer->close(IDU_WaveEnd);
		switch (value->successNum)
		{
		case 0:
			//副本失败
			{
				gHero->LeaveCopyWithEffect();
			}
			break;
		case 1:
			//副本阶段成功
			{
				if (value->isContinue)
				{
					//继续战斗
				} 
				else
				{
					//离开发逿
					gHero->LeaveCopyWithEffect();
				}
			}
			break;
		case 2:
			//通关副本
			{
				gHero->LeaveCopyWithEffect();
			}
			break;
		}
		return true;
	}

	bool OnGS2C_SetBlockSections(GS2C_SetBlockSections *value)
	{
		pk::BlockSectionInfo blockInfo;
		for (size_t i=0; i<value->blockSectionInfo.size(); ++i)
		{
			blockInfo = value->blockSectionInfo[i];
			for (int x=blockInfo.x; x<=blockInfo.x+blockInfo.dx; ++x)
			{
				for (int y=blockInfo.y; y<=blockInfo.y+blockInfo.dy; ++y)
				{
					gMap->getTerrain()->setCellMask(x,y,1);
				}
			}
		}
		gMap->initAStar();
		return true;
	}

	bool OnGS2C_ClearBlockSections(GS2C_ClearBlockSections *value)
	{
		pk::BlockSectionInfo blockInfo;
		for (size_t i=0; i<value->blockSectionInfo.size(); ++i)
		{
			blockInfo = value->blockSectionInfo[i];
			for (int x=blockInfo.x; x<=blockInfo.x+blockInfo.dx; ++x)
			{
				for (int y=blockInfo.y; y<=blockInfo.y+blockInfo.dy; ++y)
				{
					gMap->getTerrain()->setCellMask(x,y,0);
				}
			}
		}
		gMap->initAStar();
		return true;
	}

	bool OnGS2C_OpenDoor_Ret(GS2C_OpenDoor_Ret* value)
	{
		//播放开门特效
		return true;
	}

	bool OnGS2C_LookupCurMapBossPosRet(GS2C_LookupCurMapBossPosRet* value)
	{
		CSuperMove::Start(value->mapDataID,value->x,value->y);
		return true;
	}

	bool OnGS2C_ForbiddenArea_Exp(GS2C_ForbiddenArea_Exp* value)
	{
		return true;
	}

	bool OnGS2C_LookInfoVirtualPlayer(struct GS2C_LookInfoVirtualPlayer *)
	{
		return true;
	}

	bool OnGS2C_PlayerEvade(struct pk::GS2C_PlayerEvade *value)
	{
		if ( !gMap )
		{
			return true;
		}

		RoleFighter* pRole = GetMapRole(value->id);
		if ( pRole && pRole != gHero )
		{
			pRole->Evade(value->desPosX,value->desPosY);
		}

		return true;
	}

	/*打完5波怪,弹框，继续战斗或者退出战斗*/
	bool OnGS2C_GiveSelectionToContinueCopy(GS2C_GiveSelectionToContinueCopy* value)
	{
		//5波奖势
		CWaveEnd::s_waveRewards[value->steps] = *value;
		//队员初始未选择
		for (unsigned int i=0; i<CTeamUI::s_teamInfo.member_list.size(); ++i)
		{
			CTeamUI::s_teamInfo.member_list[i].isContinue = -1;
		}
		gGameUILayer->open(IDU_WaveEnd);
		return true;
	}

	//收到C2GS_ReplySelectionToContinueCopy后，服务器广播此消息给地图内的所有玩家
	bool OnGS2C_ReplySelectionToContinueCopy(GS2C_ReplySelectionToContinueCopy *value)
	{
		for (unsigned int i=0; i<CTeamUI::s_teamInfo.member_list.size(); ++i)
		{
			if (CTeamUI::s_teamInfo.member_list[i].id == value->playerId)
			{
				CTeamUI::s_teamInfo.member_list[i].isContinue = value->isContinue;
				break;
			}
		}
		CWaveEnd* pUI = (CWaveEnd*)gGameUILayer->getActiveUI(IDU_WaveEnd);
		if(pUI) pUI->UpdateSelection();
		return true;
	}

	//副本结算
	bool OnGS2C_CopyMapCheckOut(GS2C_CopyMapCheckOut *value)
	{
		//清除副本5波累计奖势
		CWaveEnd::s_waveRewards.clear();

		CCopyEnd* pUI = (CCopyEnd*)gGameUILayer->open(IDU_CopyEnd);
		if(pUI)
		{
			pUI->updateCheckOut(value);
		}

		return true;
	}

	bool OnGS2C_Missile(GS2C_Missile* value)
	{
		RoleFighter* pCaster = GetMapRole(value->ownerId);
		if ( pCaster )
		{
			SkillCfg* pSkill = SkillData.get(value->skillId);
			if ( !pSkill )
			{
				LOGE("======OnGS2C_Missile error skillid[%d].",value->skillId);
			}

			int x = value->targetX;
			int y = value->targetY;
			pCaster->GetMap()->getTerrain()->cell2World(x,y);
			Point pos(x+value->offsetX,y+value->offsetY);
			gBulletMgr->CreateBullet(value->id,value->dataId,pCaster,pSkill,pos,value->multiNum);
		}

		return true;
	}

	//发起者请求进入副本后
	bool OnGS2C_ReqEnterCopyMap_Ret(GS2C_ReqEnterCopyMap_Ret* value)
	{
		switch (value->retCode)
		{
		//发起成功
		case 0:
			{
				gMacthMachine->SetMatchInvitedPlayerId(gHero->GetId());
				gMacthMachine->MatchStart();
				CUIWorldMap* pWorldMapUI = (CUIWorldMap*)gGameUILayer->getActiveUI(IDU_WORLDMAPUI);
				if(pWorldMapUI) pWorldMapUI->ShowMatch();
				CMainUINormal* pMainUINormal = (CMainUINormal*)gGameUILayer->getActiveUI(IDU_MainUINormal);
				if(pMainUINormal) pMainUINormal->ShowMatchStatus();
			}
			break;
		default:
			break;
		}
		return true;
	}

	//队员开始准备
	bool OnGS2C_BeginePrepareEnterCopy(GS2C_BeginePrepareEnterCopy* value)
	{
		//开始60秒倒计时
		gMacthMachine->SetMatchInvitedPlayerId(value->sponsorId);
		gMacthMachine->MatchStart();
		gMacthMachine->SetMatchCountSeconds(60.0f);
		gMacthMachine->SetMatchCopyMapIdToEnter(value->copyMapDataId);
		gMacthMachine->SetMatchMode(MatchMode(value->enterType));
		gMacthMachine->SetMatchPrepared(false);

		CUIWorldMap* pWorldMapUI = (CUIWorldMap*)gGameUILayer->getActiveUI(IDU_WORLDMAPUI);
		if(pWorldMapUI) pWorldMapUI->ShowMatch();
		CMainUINormal* pMainUINormal = (CMainUINormal*)gGameUILayer->getActiveUI(IDU_MainUINormal);
		if(pMainUINormal) pMainUINormal->ShowMatchStatus();
		return true;
	}

	//所有准备完毕
	bool OnGS2C_AllPrepareEnterCopy(GS2C_AllPrepareEnterCopy* value)
	{
		//开始5秒倒计时
		gMacthMachine->SetMatchCountSeconds(5.0f);
		return true;
	}

	//取消进去副本
	bool OnGS2C_CancelEnterCopyMap(GS2C_CancelEnterCopyMap* value)
	{
		gMacthMachine->MatchEnd();
		return true;
	}
	//取消进去副本
	bool OnGS2C_CancelMatchEnter(GS2C_CancelMatchEnter* value)
	{
		gMacthMachine->MatchEnd();
		return true;
	}

	//立即进入副本
	bool OnGS2C_ExitMatchEnterCopyMapNow(GS2C_ExitMatchEnterCopyMapNow* value)
	{
		//开始5秒倒计时
		gMacthMachine->SetMatchCountSeconds(5.0f);
		gMacthMachine->SetMatchMode(MachMode_End);
		return true;
	}

	//匹配成功
	bool OnGS2C_MatchEnterCopySuccess(GS2C_MatchEnterCopySuccess* value)
	{
		gMacthMachine->SetMatchCountSeconds(0.0f);
		gMacthMachine->SetMatchMode(MachMode_End);
		return true;
	}

	bool OnGS2C_OPEN_MAP_LIST(GS2C_OPEN_MAP_LIST* value)
	{
		gCopyDataMgr->InitPlacesLockInfo(value);
		return true;
	}

	bool OnGS2C_OPEN_MAP_UPDATE_OR_ADD(GS2C_OPEN_MAP_UPDATE_OR_ADD* value)
	{
		gCopyDataMgr->UpdatePlacesLockInfo(value);
		return true;
	}

	bool OnGS2C_LookInfoTreas(GS2C_LookInfoTreas* value)
	{
		if ( !gMap )
		{
			return false;
		}

		CChests* pChests = CChests::create();
		if ( pChests )
		{
			pChests->SetId(value->id);
			pChests->SetDataID(value->dataId);
			pChests->SetCamp(RoleCamp_None);
			pChests->SetChestsStatus(CChests::ChestsStatus(value->status));
			pChests->SetDestroyLeftTime(value->disTime);
			pChests->EnterMap(gMap,value->x,value->y);
		}

		return true;
	}

	bool OnGS2C_OPEN_TREAS_Ret(GS2C_OPEN_TREAS_Ret* value)
	{
		if (value->retCode == 0)
		{
			CChests* pChests = dynamic_cast<CChests*>(gMap->getObjectManager()->getObject(value->id));
			if(!pChests) return false;
			pChests->SetChestsStatus(CChests::ChestsStatus(value->open_state));
		}
		return true;
	}

	bool OnGS2C_TREAS_STATE(GS2C_TREAS_STATE* value)
	{
		CChests* pChests = dynamic_cast<CChests*>(gMap->getObjectManager()->getObject(value->id));
		if(!pChests) return false;
		pChests->SetChestsStatus(CChests::ChestsStatus(value->status));
		pChests->SetDestroyLeftTime(value->disTime);
		return true;
	}

	bool OnGS2C_GUIDE_LIST(GS2C_GUIDE_LIST* value)
	{
		gIndicatorLayer->SetDynamicIndicators(value);
		return true;
	}

	bool OnGS2C_FreeFightCopyPhaseInfo(GS2C_FreeFightCopyPhaseInfo* value)
	{
		//1:等待2:倒计时3:开始
		switch (value->phase)
		{
		case 1:
			MessagePrompt("Waiting for the free fight to start!");
			break;
		case 2:
			{
				CCopyMapFreeFight* pFreeFightUI = (CCopyMapFreeFight*)gGameUILayer->getUI(IDU_CopyFreeFight);
				if(pFreeFightUI)
				{
					pFreeFightUI->OnStartCountDown();
					pFreeFightUI->StartCountSeconds(value->countDownSecs);
				}
			}
			break;
		case 3:
			MessagePrompt("Fight start!");
			break;
		default:
			break;
		}
		return true;
	}

	bool OnGS2C_FreeFightCopyScoreBoard(GS2C_FreeFightCopyScoreBoard* value)
	{
		CFreeFightScoreUI* pFreeFightScoreUI = (CFreeFightScoreUI*)(gGameUILayer->open(IDU_FreeFightScore));
		if (pFreeFightScoreUI)
		{
			pFreeFightScoreUI->UpdateScore(value);
		}
		return true;
	}

	bool OnGS2C_FreeFightCopyCheckout(GS2C_FreeFightCopyCheckout* value)
	{
		CFreeFightCheckOut* pFreeFightCheckOut = (CFreeFightCheckOut*)gGameUILayer->open(IDU_FreeFightCheckOut);
		if (pFreeFightCheckOut)
		{
			pFreeFightCheckOut->setCheckOutData(value);
		}
		return true;
	}

	bool OnGS2C_FreeFightCopyCloseTimerStart(GS2C_FreeFightCopyCloseTimerStart* value)
	{
		CCopyMapFreeFight* pFreeFightUI = (CCopyMapFreeFight*)gGameUILayer->getUI(IDU_CopyFreeFight);
		if(pFreeFightUI)
		{
			pFreeFightUI->OnEndCountDown();
			pFreeFightUI->StartCountSeconds(value->countDownSecs);
		}
		return true;
	}

	bool OnGS2C_FreeFightCopyCloseTimerCancel(GS2C_FreeFightCopyCloseTimerCancel* value)
	{
		CCopyMapFreeFight* pFreeFightUI = (CCopyMapFreeFight*)gGameUILayer->getUI(IDU_CopyFreeFight);
		if(pFreeFightUI)
		{
			pFreeFightUI->EndCountSeconds();
		}
		return true;
	}

	//争夺副本
	bool OnGS2C_ContentionInfo(GS2C_ContentionInfo* value)
	{
		CCopyMapContendFor* pContendFor = (CCopyMapContendFor*)gGameUILayer->getUI(IDU_CopyUIContendFor);
		if(pContendFor)
		{
			pContendFor->UpdateContendForInfo(value);
		}
		return true;
	}
}
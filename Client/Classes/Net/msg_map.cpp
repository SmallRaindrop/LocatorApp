#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_map(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_ChangeMap);
 		CMD_DEAL(GS2C_LookupPlayerPosRet);
 		CMD_DEAL(GS2C_LookupCurMapBossPosRet);
 		CMD_DEAL(GS2C_LookupTeamPos);
 		CMD_DEAL(GS2C_ReqEnterCopyMap_Ret);
 		CMD_DEAL(GS2C_BeginePrepareEnterCopy);
 		CMD_DEAL(GS2C_AllPrepareEnterCopy);
 		CMD_DEAL(GS2C_CancelEnterCopyMap);
 		CMD_DEAL(GS2C_ExitMatchEnterCopyMapNow);
 		CMD_DEAL(GS2C_CancelMatchEnter);
 		CMD_DEAL(GS2C_MatchEnterCopySuccess);
 		CMD_DEAL(GS2C_CopyMapCompleted);
 		CMD_DEAL(GS2C_CopyMapCheckOut);
 		CMD_DEAL(GS2C_AllCopyCDInfo);
 		CMD_DEAL(GS2C_UpdatPlayerCopyCDInfo);
 		CMD_DEAL(GS2C_CopyMapClose_Countdown);
 		CMD_DEAL(GS2C_CopyInitInfo);
 		CMD_DEAL(GS2C_UpdateCopyProgress);
 		CMD_DEAL(GS2C_MonsterSpawnRemind);
 		CMD_DEAL(GS2C_GiveSelectionToContinueCopy);
 		CMD_DEAL(GS2C_ReplySelectionToContinueCopy);
 		CMD_DEAL(GS2C_Missile);
 		CMD_DEAL(GS2C_MissileDamage);
 		CMD_DEAL(GS2C_SetBlockSections);
 		CMD_DEAL(GS2C_ClearBlockSections);
 		CMD_DEAL(GS2C_OpenDoor_Ret);
 		CMD_DEAL(GS2C_ForbiddenArea_Exp);
 		CMD_DEAL(GS2C_COPY_SUCC_TIME);
 		CMD_DEAL(GS2C_OPEN_MAP_LIST);
 		CMD_DEAL(GS2C_OPEN_MAP_UPDATE_OR_ADD);
 		CMD_DEAL(GS2C_OPEN_TREAS_Ret);
 		CMD_DEAL(GS2C_TREAS_STATE);
 		CMD_DEAL(GS2C_GUIDE_LIST);
 		CMD_DEAL(GS2C_FreeFightCopyPhaseInfo);
 		CMD_DEAL(GS2C_FreeFightCopyScoreBoard);
 		CMD_DEAL(GS2C_FreeFightCopyCloseTimerStart);
 		CMD_DEAL(GS2C_FreeFightCopyCloseTimerCancel);
 		CMD_DEAL(GS2C_FreeFightCopyCheckout);
 		CMD_DEAL(GS2C_LivePoint);
 		CMD_DEAL(GS2C_ContentionInfo);
 	END_DEAL();
	return false;
}

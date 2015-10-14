
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_map(stNetMsg& msg);
const int MSG_C2GS_PickUpItem			= 13001;
const int MSG_GS2C_ChangeMap			= 13002;
const int MSG_C2GS_LookupPlayerPos			= 13003;
const int MSG_GS2C_LookupPlayerPosRet			= 13004;
const int MSG_C2GS_LookupCurMapBossPos			= 13005;
const int MSG_GS2C_LookupCurMapBossPosRet			= 13006;
const int MSG_C2GS_LookupTeamPos			= 13008;
const int MSG_GS2C_LookupTeamPos			= 13009;
const int MSG_C2GS_TransferMapInLookupPos			= 13010;
const int MSG_C2GS_ReqChangeMapInTransport			= 13011;
const int MSG_C2GS_ReqChangeMapInDynamicTransport			= 13012;
const int MSG_C2GS_ReqChangeMapInWorldMap			= 13013;
const int MSG_C2GS_ReqChangeMapByNpc			= 13014;
const int MSG_C2GS_ReqEnterCopyMap			= 13015;
const int MSG_GS2C_ReqEnterCopyMap_Ret			= 13016;
const int MSG_GS2C_BeginePrepareEnterCopy			= 13017;
const int MSG_C2GS_PrepareCompleteEnterCopy			= 13018;
const int MSG_GS2C_AllPrepareEnterCopy			= 13019;
const int MSG_C2GS_SponsorCancelEnterCopyMap			= 13020;
const int MSG_GS2C_CancelEnterCopyMap			= 13021;
const int MSG_C2GS_SponsorExitMatchEnterCopyMapNow			= 13022;
const int MSG_C2GS_SponsorCancelMatchEnter			= 13023;
const int MSG_GS2C_ExitMatchEnterCopyMapNow			= 13024;
const int MSG_GS2C_CancelMatchEnter			= 13025;
const int MSG_GS2C_MatchEnterCopySuccess			= 13026;
const int MSG_C2GS_PlayerLeaveCopyMap			= 13027;
const int MSG_GS2C_CopyMapCompleted			= 13030;
const int MSG_GS2C_CopyMapCheckOut			= 13031;
const int MSG_GS2C_AllCopyCDInfo			= 13033;
const int MSG_GS2C_UpdatPlayerCopyCDInfo			= 13034;
const int MSG_GS2C_CopyMapClose_Countdown			= 13035;
const int MSG_GS2C_CopyInitInfo			= 13036;
const int MSG_GS2C_UpdateCopyProgress			= 13037;
const int MSG_GS2C_MonsterSpawnRemind			= 13038;
const int MSG_GS2C_GiveSelectionToContinueCopy			= 13039;
const int MSG_C2GS_ReplySelectionToContinueCopy			= 13040;
const int MSG_GS2C_ReplySelectionToContinueCopy			= 13041;
const int MSG_GS2C_Missile			= 13042;
const int MSG_C2GS_MissileDamage			= 13043;
const int MSG_GS2C_MissileDamage			= 13044;
const int MSG_GS2C_SetBlockSections			= 13046;
const int MSG_GS2C_ClearBlockSections			= 13047;
const int MSG_C2GS_OpenDoor_Req			= 13048;
const int MSG_GS2C_OpenDoor_Ret			= 13049;
const int MSG_GS2C_ForbiddenArea_Exp			= 13050;
const int MSG_GS2C_COPY_SUCC_TIME			= 13051;
const int MSG_GS2C_OPEN_MAP_LIST			= 13053;
const int MSG_GS2C_OPEN_MAP_UPDATE_OR_ADD			= 13054;
const int MSG_C2GS_OPEN_TREAS_Req			= 13055;
const int MSG_GS2C_OPEN_TREAS_Ret			= 13056;
const int MSG_GS2C_TREAS_STATE			= 13057;
const int MSG_C2GS_OPEN_TREAS_Succ_Req			= 13058;
const int MSG_GS2C_GUIDE_LIST			= 13060;
const int MSG_GS2C_FreeFightCopyPhaseInfo			= 13061;
const int MSG_C2GS_FreeFightCopyScoreBoard_Req			= 13062;
const int MSG_GS2C_FreeFightCopyScoreBoard			= 13064;
const int MSG_GS2C_FreeFightCopyCloseTimerStart			= 13065;
const int MSG_GS2C_FreeFightCopyCloseTimerCancel			= 13066;
const int MSG_GS2C_FreeFightCopyCheckout			= 13068;
const int MSG_GS2C_LivePoint			= 13069;
const int MSG_GS2C_ContentionInfo			= 13071;

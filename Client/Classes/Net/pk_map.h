
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct C2GS_PickUpItem
{
	int64 id;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PickUpItem(stNetMsg& msg,C2GS_PickUpItem& value);
void ReadC2GS_PickUpItem(stNetMsg& msg,C2GS_PickUpItem& value);

struct GS2C_ChangeMap
{
	int32 mapDataID;
	int64 mapId;
	int16 x;
	int16 y;
};
void WriteGS2C_ChangeMap(stNetMsg& msg,GS2C_ChangeMap& value);
bool OnGS2C_ChangeMap(GS2C_ChangeMap* value);
void ReadGS2C_ChangeMap(stNetMsg& msg,GS2C_ChangeMap& value);

struct C2GS_LookupPlayerPos
{
	int64 playerId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_LookupPlayerPos(stNetMsg& msg,C2GS_LookupPlayerPos& value);
void ReadC2GS_LookupPlayerPos(stNetMsg& msg,C2GS_LookupPlayerPos& value);

struct GS2C_LookupPlayerPosRet
{
	int64 playerId;
	int64 mapId;
	int32 mapDataID;
	int16 x;
	int16 y;
};
void WriteGS2C_LookupPlayerPosRet(stNetMsg& msg,GS2C_LookupPlayerPosRet& value);
bool OnGS2C_LookupPlayerPosRet(GS2C_LookupPlayerPosRet* value);
void ReadGS2C_LookupPlayerPosRet(stNetMsg& msg,GS2C_LookupPlayerPosRet& value);

struct C2GS_LookupCurMapBossPos
{
	int32 bossDataId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_LookupCurMapBossPos(stNetMsg& msg,C2GS_LookupCurMapBossPos& value);
void ReadC2GS_LookupCurMapBossPos(stNetMsg& msg,C2GS_LookupCurMapBossPos& value);

struct GS2C_LookupCurMapBossPosRet
{
	int8 retCode;
	int32 mapDataID;
	int16 x;
	int16 y;
};
void WriteGS2C_LookupCurMapBossPosRet(stNetMsg& msg,GS2C_LookupCurMapBossPosRet& value);
bool OnGS2C_LookupCurMapBossPosRet(GS2C_LookupCurMapBossPosRet* value);
void ReadGS2C_LookupCurMapBossPosRet(stNetMsg& msg,GS2C_LookupCurMapBossPosRet& value);

struct playerPos
{
	int64 playerId;
	int64 mapId;
	int32 mapDataID;
	int16 x;
	int16 y;
};
void WriteplayerPos(stNetMsg& msg,playerPos& value);
void ReadplayerPos(stNetMsg& msg,playerPos& value);

struct C2GS_LookupTeamPos
{
	int64 playerId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_LookupTeamPos(stNetMsg& msg,C2GS_LookupTeamPos& value);
void ReadC2GS_LookupTeamPos(stNetMsg& msg,C2GS_LookupTeamPos& value);

struct GS2C_LookupTeamPos
{
	vector<playerPos> vec;
};
void WriteGS2C_LookupTeamPos(stNetMsg& msg,GS2C_LookupTeamPos& value);
bool OnGS2C_LookupTeamPos(GS2C_LookupTeamPos* value);
void ReadGS2C_LookupTeamPos(stNetMsg& msg,GS2C_LookupTeamPos& value);

struct C2GS_TransferMapInLookupPos
{
	int64 mapId;
	int32 mapDataID;
	int16 x;
	int16 y;
	int8 isTransferWithTeam;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_TransferMapInLookupPos(stNetMsg& msg,C2GS_TransferMapInLookupPos& value);
void ReadC2GS_TransferMapInLookupPos(stNetMsg& msg,C2GS_TransferMapInLookupPos& value);

struct C2GS_ReqChangeMapInTransport
{
	int32 curMapDataID;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ReqChangeMapInTransport(stNetMsg& msg,C2GS_ReqChangeMapInTransport& value);
void ReadC2GS_ReqChangeMapInTransport(stNetMsg& msg,C2GS_ReqChangeMapInTransport& value);

struct C2GS_ReqChangeMapInDynamicTransport
{
	int32 curMapDataID;
	int64 doorId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ReqChangeMapInDynamicTransport(stNetMsg& msg,C2GS_ReqChangeMapInDynamicTransport& value);
void ReadC2GS_ReqChangeMapInDynamicTransport(stNetMsg& msg,C2GS_ReqChangeMapInDynamicTransport& value);

struct C2GS_ReqChangeMapInWorldMap
{
	int32 desMapDataID;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ReqChangeMapInWorldMap(stNetMsg& msg,C2GS_ReqChangeMapInWorldMap& value);
void ReadC2GS_ReqChangeMapInWorldMap(stNetMsg& msg,C2GS_ReqChangeMapInWorldMap& value);

struct C2GS_ReqChangeMapByNpc
{
	int64 id;
	int32 npcDataID;
	int16 npcTransferId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ReqChangeMapByNpc(stNetMsg& msg,C2GS_ReqChangeMapByNpc& value);
void ReadC2GS_ReqChangeMapByNpc(stNetMsg& msg,C2GS_ReqChangeMapByNpc& value);

struct C2GS_ReqEnterCopyMap
{
	int64 npcId;
	int32 npcDataID;
	int32 enterMapDataId;
	int8 enterType;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ReqEnterCopyMap(stNetMsg& msg,C2GS_ReqEnterCopyMap& value);
void ReadC2GS_ReqEnterCopyMap(stNetMsg& msg,C2GS_ReqEnterCopyMap& value);

struct GS2C_ReqEnterCopyMap_Ret
{
	int8 retCode;
};
void WriteGS2C_ReqEnterCopyMap_Ret(stNetMsg& msg,GS2C_ReqEnterCopyMap_Ret& value);
bool OnGS2C_ReqEnterCopyMap_Ret(GS2C_ReqEnterCopyMap_Ret* value);
void ReadGS2C_ReqEnterCopyMap_Ret(stNetMsg& msg,GS2C_ReqEnterCopyMap_Ret& value);

struct GS2C_BeginePrepareEnterCopy
{
	int64 npcId;
	int32 npcDataId;
	int32 copyMapDataId;
	int8 enterType;
	int64 sponsorId;
};
void WriteGS2C_BeginePrepareEnterCopy(stNetMsg& msg,GS2C_BeginePrepareEnterCopy& value);
bool OnGS2C_BeginePrepareEnterCopy(GS2C_BeginePrepareEnterCopy* value);
void ReadGS2C_BeginePrepareEnterCopy(stNetMsg& msg,GS2C_BeginePrepareEnterCopy& value);

struct C2GS_PrepareCompleteEnterCopy
{
	int64 sponsorId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PrepareCompleteEnterCopy(stNetMsg& msg,C2GS_PrepareCompleteEnterCopy& value);
void ReadC2GS_PrepareCompleteEnterCopy(stNetMsg& msg,C2GS_PrepareCompleteEnterCopy& value);

struct GS2C_AllPrepareEnterCopy
{
	int64 sponsorId;
};
void WriteGS2C_AllPrepareEnterCopy(stNetMsg& msg,GS2C_AllPrepareEnterCopy& value);
bool OnGS2C_AllPrepareEnterCopy(GS2C_AllPrepareEnterCopy* value);
void ReadGS2C_AllPrepareEnterCopy(stNetMsg& msg,GS2C_AllPrepareEnterCopy& value);

struct C2GS_SponsorCancelEnterCopyMap
{
	int32 curMapDataId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SponsorCancelEnterCopyMap(stNetMsg& msg,C2GS_SponsorCancelEnterCopyMap& value);
void ReadC2GS_SponsorCancelEnterCopyMap(stNetMsg& msg,C2GS_SponsorCancelEnterCopyMap& value);

struct GS2C_CancelEnterCopyMap
{
	int32 cancelReason;
};
void WriteGS2C_CancelEnterCopyMap(stNetMsg& msg,GS2C_CancelEnterCopyMap& value);
bool OnGS2C_CancelEnterCopyMap(GS2C_CancelEnterCopyMap* value);
void ReadGS2C_CancelEnterCopyMap(stNetMsg& msg,GS2C_CancelEnterCopyMap& value);

struct C2GS_SponsorExitMatchEnterCopyMapNow
{
	int32 curMapDataId;
	int32 enterMapDataId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SponsorExitMatchEnterCopyMapNow(stNetMsg& msg,C2GS_SponsorExitMatchEnterCopyMapNow& value);
void ReadC2GS_SponsorExitMatchEnterCopyMapNow(stNetMsg& msg,C2GS_SponsorExitMatchEnterCopyMapNow& value);

struct C2GS_SponsorCancelMatchEnter
{
	int32 curMapDataId;
	int32 enterMapDataId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SponsorCancelMatchEnter(stNetMsg& msg,C2GS_SponsorCancelMatchEnter& value);
void ReadC2GS_SponsorCancelMatchEnter(stNetMsg& msg,C2GS_SponsorCancelMatchEnter& value);

struct GS2C_ExitMatchEnterCopyMapNow
{
	int64 sponsorId;
};
void WriteGS2C_ExitMatchEnterCopyMapNow(stNetMsg& msg,GS2C_ExitMatchEnterCopyMapNow& value);
bool OnGS2C_ExitMatchEnterCopyMapNow(GS2C_ExitMatchEnterCopyMapNow* value);
void ReadGS2C_ExitMatchEnterCopyMapNow(stNetMsg& msg,GS2C_ExitMatchEnterCopyMapNow& value);

struct GS2C_CancelMatchEnter
{
	int64 sponsorId;
};
void WriteGS2C_CancelMatchEnter(stNetMsg& msg,GS2C_CancelMatchEnter& value);
bool OnGS2C_CancelMatchEnter(GS2C_CancelMatchEnter* value);
void ReadGS2C_CancelMatchEnter(stNetMsg& msg,GS2C_CancelMatchEnter& value);

struct GS2C_MatchEnterCopySuccess
{
	int32 enterMapDataId;
};
void WriteGS2C_MatchEnterCopySuccess(stNetMsg& msg,GS2C_MatchEnterCopySuccess& value);
bool OnGS2C_MatchEnterCopySuccess(GS2C_MatchEnterCopySuccess* value);
void ReadGS2C_MatchEnterCopySuccess(stNetMsg& msg,GS2C_MatchEnterCopySuccess& value);

struct C2GS_PlayerLeaveCopyMap
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PlayerLeaveCopyMap(stNetMsg& msg,C2GS_PlayerLeaveCopyMap& value);
void ReadC2GS_PlayerLeaveCopyMap(stNetMsg& msg,C2GS_PlayerLeaveCopyMap& value);

struct FightStatsInfo
{
	int64 playerId;
	string playerName;
	int8 damagePercent;
	int8 bearDamagePercent;
	int16 killCnt;
	int16 deadCnt;
	int16 reliveCnt;
};
void WriteFightStatsInfo(stNetMsg& msg,FightStatsInfo& value);
void ReadFightStatsInfo(stNetMsg& msg,FightStatsInfo& value);

struct ItemDataIdAndCnt
{
	int32 itemDataID;
	int32 cnt;
};
void WriteItemDataIdAndCnt(stNetMsg& msg,ItemDataIdAndCnt& value);
void ReadItemDataIdAndCnt(stNetMsg& msg,ItemDataIdAndCnt& value);

struct GS2C_CopyMapCompleted
{
	int8 successNum;
	int8 isContinue;
};
void WriteGS2C_CopyMapCompleted(stNetMsg& msg,GS2C_CopyMapCompleted& value);
bool OnGS2C_CopyMapCompleted(GS2C_CopyMapCompleted* value);
void ReadGS2C_CopyMapCompleted(stNetMsg& msg,GS2C_CopyMapCompleted& value);

struct GS2C_CopyMapCheckOut
{
	int8 successNum;
	vector<FightStatsInfo> fightStats;
	int32 seconds;
	int16 steps;
	int32 coin;
	int32 exp;
	vector<ItemDataIdAndCnt> itemInfos;
};
void WriteGS2C_CopyMapCheckOut(stNetMsg& msg,GS2C_CopyMapCheckOut& value);
bool OnGS2C_CopyMapCheckOut(GS2C_CopyMapCheckOut* value);
void ReadGS2C_CopyMapCheckOut(stNetMsg& msg,GS2C_CopyMapCheckOut& value);

struct PlayerCopyCDInfo
{
	int32 map_data_id;
	int8 enter_cnt;
	int8 remain_cnt;
};
void WritePlayerCopyCDInfo(stNetMsg& msg,PlayerCopyCDInfo& value);
void ReadPlayerCopyCDInfo(stNetMsg& msg,PlayerCopyCDInfo& value);

struct GS2C_AllCopyCDInfo
{
	vector<PlayerCopyCDInfo> copyCdInfos;
};
void WriteGS2C_AllCopyCDInfo(stNetMsg& msg,GS2C_AllCopyCDInfo& value);
bool OnGS2C_AllCopyCDInfo(GS2C_AllCopyCDInfo* value);
void ReadGS2C_AllCopyCDInfo(stNetMsg& msg,GS2C_AllCopyCDInfo& value);

struct GS2C_UpdatPlayerCopyCDInfo
{
	int32 map_data_id;
	int8 enter_cnt;
	int8 remain_cnt;
};
void WriteGS2C_UpdatPlayerCopyCDInfo(stNetMsg& msg,GS2C_UpdatPlayerCopyCDInfo& value);
bool OnGS2C_UpdatPlayerCopyCDInfo(GS2C_UpdatPlayerCopyCDInfo* value);
void ReadGS2C_UpdatPlayerCopyCDInfo(stNetMsg& msg,GS2C_UpdatPlayerCopyCDInfo& value);

struct GS2C_CopyMapClose_Countdown
{
	int8 second;
};
void WriteGS2C_CopyMapClose_Countdown(stNetMsg& msg,GS2C_CopyMapClose_Countdown& value);
bool OnGS2C_CopyMapClose_Countdown(GS2C_CopyMapClose_Countdown* value);
void ReadGS2C_CopyMapClose_Countdown(stNetMsg& msg,GS2C_CopyMapClose_Countdown& value);

struct GS2C_CopyInitInfo
{
	int16 copyStepId;
	int16 totalCnt;
	int16 curCnt;
	int16 remainSec;
	int16 mapDataID;
};
void WriteGS2C_CopyInitInfo(stNetMsg& msg,GS2C_CopyInitInfo& value);
bool OnGS2C_CopyInitInfo(GS2C_CopyInitInfo* value);
void ReadGS2C_CopyInitInfo(stNetMsg& msg,GS2C_CopyInitInfo& value);

struct GS2C_UpdateCopyProgress
{
	int16 copyStepId;
	int16 curCnt;
};
void WriteGS2C_UpdateCopyProgress(stNetMsg& msg,GS2C_UpdateCopyProgress& value);
bool OnGS2C_UpdateCopyProgress(GS2C_UpdateCopyProgress* value);
void ReadGS2C_UpdateCopyProgress(stNetMsg& msg,GS2C_UpdateCopyProgress& value);

struct GS2C_MonsterSpawnRemind
{
	int16 waveIndex;
	int16 delaySec;
	int16 isActive;
};
void WriteGS2C_MonsterSpawnRemind(stNetMsg& msg,GS2C_MonsterSpawnRemind& value);
bool OnGS2C_MonsterSpawnRemind(GS2C_MonsterSpawnRemind* value);
void ReadGS2C_MonsterSpawnRemind(stNetMsg& msg,GS2C_MonsterSpawnRemind& value);

struct GS2C_GiveSelectionToContinueCopy
{
	int16 steps;
	vector<ItemDataIdAndCnt> itemInfos;
};
void WriteGS2C_GiveSelectionToContinueCopy(stNetMsg& msg,GS2C_GiveSelectionToContinueCopy& value);
bool OnGS2C_GiveSelectionToContinueCopy(GS2C_GiveSelectionToContinueCopy* value);
void ReadGS2C_GiveSelectionToContinueCopy(stNetMsg& msg,GS2C_GiveSelectionToContinueCopy& value);

struct C2GS_ReplySelectionToContinueCopy
{
	int8 isContinue;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ReplySelectionToContinueCopy(stNetMsg& msg,C2GS_ReplySelectionToContinueCopy& value);
void ReadC2GS_ReplySelectionToContinueCopy(stNetMsg& msg,C2GS_ReplySelectionToContinueCopy& value);

struct GS2C_ReplySelectionToContinueCopy
{
	int64 playerId;
	int8 isContinue;
};
void WriteGS2C_ReplySelectionToContinueCopy(stNetMsg& msg,GS2C_ReplySelectionToContinueCopy& value);
bool OnGS2C_ReplySelectionToContinueCopy(GS2C_ReplySelectionToContinueCopy* value);
void ReadGS2C_ReplySelectionToContinueCopy(stNetMsg& msg,GS2C_ReplySelectionToContinueCopy& value);

struct GS2C_Missile
{
	int64 id;
	int64 ownerId;
	int32 skillId;
	int32 dataId;
	int16 targetX;
	int16 targetY;
	int16 offsetX;
	int16 offsetY;
	int8 multiNum;
};
void WriteGS2C_Missile(stNetMsg& msg,GS2C_Missile& value);
bool OnGS2C_Missile(GS2C_Missile* value);
void ReadGS2C_Missile(stNetMsg& msg,GS2C_Missile& value);

struct C2GS_MissileDamage
{
	int64 id;
	int64 targetId;
	int8 index;
	int16 targetX;
	int16 targetY;
	int8 isExplosion;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_MissileDamage(stNetMsg& msg,C2GS_MissileDamage& value);
void ReadC2GS_MissileDamage(stNetMsg& msg,C2GS_MissileDamage& value);

struct GS2C_MissileDamage
{
	int64 id;
	int64 targetId;
	int8 isExplosion;
	int8 index;
};
void WriteGS2C_MissileDamage(stNetMsg& msg,GS2C_MissileDamage& value);
bool OnGS2C_MissileDamage(GS2C_MissileDamage* value);
void ReadGS2C_MissileDamage(stNetMsg& msg,GS2C_MissileDamage& value);

struct BlockSectionInfo
{
	int16 x;
	int16 y;
	int8 dx;
	int8 dy;
};
void WriteBlockSectionInfo(stNetMsg& msg,BlockSectionInfo& value);
void ReadBlockSectionInfo(stNetMsg& msg,BlockSectionInfo& value);

struct GS2C_SetBlockSections
{
	vector<BlockSectionInfo> blockSectionInfo;
};
void WriteGS2C_SetBlockSections(stNetMsg& msg,GS2C_SetBlockSections& value);
bool OnGS2C_SetBlockSections(GS2C_SetBlockSections* value);
void ReadGS2C_SetBlockSections(stNetMsg& msg,GS2C_SetBlockSections& value);

struct GS2C_ClearBlockSections
{
	vector<BlockSectionInfo> blockSectionInfo;
};
void WriteGS2C_ClearBlockSections(stNetMsg& msg,GS2C_ClearBlockSections& value);
bool OnGS2C_ClearBlockSections(GS2C_ClearBlockSections* value);
void ReadGS2C_ClearBlockSections(stNetMsg& msg,GS2C_ClearBlockSections& value);

struct C2GS_OpenDoor_Req
{
	int64 id;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_OpenDoor_Req(stNetMsg& msg,C2GS_OpenDoor_Req& value);
void ReadC2GS_OpenDoor_Req(stNetMsg& msg,C2GS_OpenDoor_Req& value);

struct GS2C_OpenDoor_Ret
{
	int8 retCode;
	int64 id;
};
void WriteGS2C_OpenDoor_Ret(stNetMsg& msg,GS2C_OpenDoor_Ret& value);
bool OnGS2C_OpenDoor_Ret(GS2C_OpenDoor_Ret* value);
void ReadGS2C_OpenDoor_Ret(stNetMsg& msg,GS2C_OpenDoor_Ret& value);

struct GS2C_ForbiddenArea_Exp
{
	int32 exp;
};
void WriteGS2C_ForbiddenArea_Exp(stNetMsg& msg,GS2C_ForbiddenArea_Exp& value);
bool OnGS2C_ForbiddenArea_Exp(GS2C_ForbiddenArea_Exp* value);
void ReadGS2C_ForbiddenArea_Exp(stNetMsg& msg,GS2C_ForbiddenArea_Exp& value);

struct GS2C_COPY_SUCC_TIME
{
	int32 time;
};
void WriteGS2C_COPY_SUCC_TIME(stNetMsg& msg,GS2C_COPY_SUCC_TIME& value);
bool OnGS2C_COPY_SUCC_TIME(GS2C_COPY_SUCC_TIME* value);
void ReadGS2C_COPY_SUCC_TIME(stNetMsg& msg,GS2C_COPY_SUCC_TIME& value);

struct OpenMap
{
	int32 id;
	int8 state;
};
void WriteOpenMap(stNetMsg& msg,OpenMap& value);
void ReadOpenMap(stNetMsg& msg,OpenMap& value);

struct GS2C_OPEN_MAP_LIST
{
	vector<OpenMap> bigMapList;
	vector<OpenMap> smallMapList;
};
void WriteGS2C_OPEN_MAP_LIST(stNetMsg& msg,GS2C_OPEN_MAP_LIST& value);
bool OnGS2C_OPEN_MAP_LIST(GS2C_OPEN_MAP_LIST* value);
void ReadGS2C_OPEN_MAP_LIST(stNetMsg& msg,GS2C_OPEN_MAP_LIST& value);

struct GS2C_OPEN_MAP_UPDATE_OR_ADD
{
	int8 type;
	OpenMap map;
};
void WriteGS2C_OPEN_MAP_UPDATE_OR_ADD(stNetMsg& msg,GS2C_OPEN_MAP_UPDATE_OR_ADD& value);
bool OnGS2C_OPEN_MAP_UPDATE_OR_ADD(GS2C_OPEN_MAP_UPDATE_OR_ADD* value);
void ReadGS2C_OPEN_MAP_UPDATE_OR_ADD(stNetMsg& msg,GS2C_OPEN_MAP_UPDATE_OR_ADD& value);

struct C2GS_OPEN_TREAS_Req
{
	int64 id;
	int64 open_state;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_OPEN_TREAS_Req(stNetMsg& msg,C2GS_OPEN_TREAS_Req& value);
void ReadC2GS_OPEN_TREAS_Req(stNetMsg& msg,C2GS_OPEN_TREAS_Req& value);

struct GS2C_OPEN_TREAS_Ret
{
	int8 retCode;
	int64 id;
	int64 open_state;
};
void WriteGS2C_OPEN_TREAS_Ret(stNetMsg& msg,GS2C_OPEN_TREAS_Ret& value);
bool OnGS2C_OPEN_TREAS_Ret(GS2C_OPEN_TREAS_Ret* value);
void ReadGS2C_OPEN_TREAS_Ret(stNetMsg& msg,GS2C_OPEN_TREAS_Ret& value);

struct GS2C_TREAS_STATE
{
	int64 id;
	int8 status;
	int32 disTime;
};
void WriteGS2C_TREAS_STATE(stNetMsg& msg,GS2C_TREAS_STATE& value);
bool OnGS2C_TREAS_STATE(GS2C_TREAS_STATE* value);
void ReadGS2C_TREAS_STATE(stNetMsg& msg,GS2C_TREAS_STATE& value);

struct C2GS_OPEN_TREAS_Succ_Req
{
	int64 id;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_OPEN_TREAS_Succ_Req(stNetMsg& msg,C2GS_OPEN_TREAS_Succ_Req& value);
void ReadC2GS_OPEN_TREAS_Succ_Req(stNetMsg& msg,C2GS_OPEN_TREAS_Succ_Req& value);

struct GUIDE_INFO
{
	int16 x;
	int16 y;
};
void WriteGUIDE_INFO(stNetMsg& msg,GUIDE_INFO& value);
void ReadGUIDE_INFO(stNetMsg& msg,GUIDE_INFO& value);

struct GS2C_GUIDE_LIST
{
	vector<GUIDE_INFO> guides;
};
void WriteGS2C_GUIDE_LIST(stNetMsg& msg,GS2C_GUIDE_LIST& value);
bool OnGS2C_GUIDE_LIST(GS2C_GUIDE_LIST* value);
void ReadGS2C_GUIDE_LIST(stNetMsg& msg,GS2C_GUIDE_LIST& value);

struct GS2C_FreeFightCopyPhaseInfo
{
	int8 phase;
	int16 countDownSecs;
};
void WriteGS2C_FreeFightCopyPhaseInfo(stNetMsg& msg,GS2C_FreeFightCopyPhaseInfo& value);
bool OnGS2C_FreeFightCopyPhaseInfo(GS2C_FreeFightCopyPhaseInfo* value);
void ReadGS2C_FreeFightCopyPhaseInfo(stNetMsg& msg,GS2C_FreeFightCopyPhaseInfo& value);

struct C2GS_FreeFightCopyScoreBoard_Req
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_FreeFightCopyScoreBoard_Req(stNetMsg& msg,C2GS_FreeFightCopyScoreBoard_Req& value);
void ReadC2GS_FreeFightCopyScoreBoard_Req(stNetMsg& msg,C2GS_FreeFightCopyScoreBoard_Req& value);

struct scoreBoardItem
{
	string name;
	int32 level;
	int16 killCnt;
	int16 deadCnt;
};
void WritescoreBoardItem(stNetMsg& msg,scoreBoardItem& value);
void ReadscoreBoardItem(stNetMsg& msg,scoreBoardItem& value);

struct GS2C_FreeFightCopyScoreBoard
{
	int32 redCampScore;
	int32 blueCampScore;
	vector<scoreBoardItem> redVec;
	vector<scoreBoardItem> blueVec;
};
void WriteGS2C_FreeFightCopyScoreBoard(stNetMsg& msg,GS2C_FreeFightCopyScoreBoard& value);
bool OnGS2C_FreeFightCopyScoreBoard(GS2C_FreeFightCopyScoreBoard* value);
void ReadGS2C_FreeFightCopyScoreBoard(stNetMsg& msg,GS2C_FreeFightCopyScoreBoard& value);

struct GS2C_FreeFightCopyCloseTimerStart
{
	int16 countDownSecs;
};
void WriteGS2C_FreeFightCopyCloseTimerStart(stNetMsg& msg,GS2C_FreeFightCopyCloseTimerStart& value);
bool OnGS2C_FreeFightCopyCloseTimerStart(GS2C_FreeFightCopyCloseTimerStart* value);
void ReadGS2C_FreeFightCopyCloseTimerStart(stNetMsg& msg,GS2C_FreeFightCopyCloseTimerStart& value);

struct GS2C_FreeFightCopyCloseTimerCancel
{
	int8 reserve;
};
void WriteGS2C_FreeFightCopyCloseTimerCancel(stNetMsg& msg,GS2C_FreeFightCopyCloseTimerCancel& value);
bool OnGS2C_FreeFightCopyCloseTimerCancel(GS2C_FreeFightCopyCloseTimerCancel* value);
void ReadGS2C_FreeFightCopyCloseTimerCancel(stNetMsg& msg,GS2C_FreeFightCopyCloseTimerCancel& value);

struct freeFightCheckoutItem
{
	int64 id;
	string name;
	int32 level;
	int16 killCnt;
	int16 deadCnt;
	int32 bindCoin;
	int32 exp;
	int32 honor;
};
void WritefreeFightCheckoutItem(stNetMsg& msg,freeFightCheckoutItem& value);
void ReadfreeFightCheckoutItem(stNetMsg& msg,freeFightCheckoutItem& value);

struct GS2C_FreeFightCopyCheckout
{
	int8 winCamp;
	int32 redCampScore;
	int32 blueCampScore;
	vector<freeFightCheckoutItem> redVec;
	vector<freeFightCheckoutItem> blueVec;
};
void WriteGS2C_FreeFightCopyCheckout(stNetMsg& msg,GS2C_FreeFightCopyCheckout& value);
bool OnGS2C_FreeFightCopyCheckout(GS2C_FreeFightCopyCheckout* value);
void ReadGS2C_FreeFightCopyCheckout(stNetMsg& msg,GS2C_FreeFightCopyCheckout& value);

struct GS2C_LivePoint
{
	int16 livePoint;
};
void WriteGS2C_LivePoint(stNetMsg& msg,GS2C_LivePoint& value);
bool OnGS2C_LivePoint(GS2C_LivePoint* value);
void ReadGS2C_LivePoint(stNetMsg& msg,GS2C_LivePoint& value);

struct ContentionPoint
{
	int8 id;
	int16 x;
	int16 y;
	int8 r;
	int8 processOwner;
	int8 processType;
	int16 process;
};
void WriteContentionPoint(stNetMsg& msg,ContentionPoint& value);
void ReadContentionPoint(stNetMsg& msg,ContentionPoint& value);

struct GS2C_ContentionInfo
{
	int16 monsterPoint;
	int16 playerPoint;
	vector<ContentionPoint> contentionPoints;
};
void WriteGS2C_ContentionInfo(stNetMsg& msg,GS2C_ContentionInfo& value);
bool OnGS2C_ContentionInfo(GS2C_ContentionInfo* value);
void ReadGS2C_ContentionInfo(stNetMsg& msg,GS2C_ContentionInfo& value);


};


#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteC2GS_PickUpItem(stNetMsg& msg,C2GS_PickUpItem& value)
{
	msg << value.id;
	msg.command(MSG_C2GS_PickUpItem);
}
void C2GS_PickUpItem::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PickUpItem(msg_s,*this);
	EndSend();
}
void ReadC2GS_PickUpItem(stNetMsg& msg,C2GS_PickUpItem& value)
{
	msg >> value.id;
}
void WriteGS2C_ChangeMap(stNetMsg& msg,GS2C_ChangeMap& value)
{
	msg << value.mapDataID;
	msg << value.mapId;
	msg << value.x;
	msg << value.y;
	msg.command(MSG_GS2C_ChangeMap);
}
void ReadGS2C_ChangeMap(stNetMsg& msg,GS2C_ChangeMap& value)
{
	msg >> value.mapDataID;
	msg >> value.mapId;
	msg >> value.x;
	msg >> value.y;
}
void WriteC2GS_LookupPlayerPos(stNetMsg& msg,C2GS_LookupPlayerPos& value)
{
	msg << value.playerId;
	msg.command(MSG_C2GS_LookupPlayerPos);
}
void C2GS_LookupPlayerPos::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_LookupPlayerPos(msg_s,*this);
	EndSend();
}
void ReadC2GS_LookupPlayerPos(stNetMsg& msg,C2GS_LookupPlayerPos& value)
{
	msg >> value.playerId;
}
void WriteGS2C_LookupPlayerPosRet(stNetMsg& msg,GS2C_LookupPlayerPosRet& value)
{
	msg << value.playerId;
	msg << value.mapId;
	msg << value.mapDataID;
	msg << value.x;
	msg << value.y;
	msg.command(MSG_GS2C_LookupPlayerPosRet);
}
void ReadGS2C_LookupPlayerPosRet(stNetMsg& msg,GS2C_LookupPlayerPosRet& value)
{
	msg >> value.playerId;
	msg >> value.mapId;
	msg >> value.mapDataID;
	msg >> value.x;
	msg >> value.y;
}
void WriteC2GS_LookupCurMapBossPos(stNetMsg& msg,C2GS_LookupCurMapBossPos& value)
{
	msg << value.bossDataId;
	msg.command(MSG_C2GS_LookupCurMapBossPos);
}
void C2GS_LookupCurMapBossPos::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_LookupCurMapBossPos(msg_s,*this);
	EndSend();
}
void ReadC2GS_LookupCurMapBossPos(stNetMsg& msg,C2GS_LookupCurMapBossPos& value)
{
	msg >> value.bossDataId;
}
void WriteGS2C_LookupCurMapBossPosRet(stNetMsg& msg,GS2C_LookupCurMapBossPosRet& value)
{
	msg << value.retCode;
	msg << value.mapDataID;
	msg << value.x;
	msg << value.y;
	msg.command(MSG_GS2C_LookupCurMapBossPosRet);
}
void ReadGS2C_LookupCurMapBossPosRet(stNetMsg& msg,GS2C_LookupCurMapBossPosRet& value)
{
	msg >> value.retCode;
	msg >> value.mapDataID;
	msg >> value.x;
	msg >> value.y;
}
void WriteplayerPos(stNetMsg& msg,playerPos& value)
{
	msg << value.playerId;
	msg << value.mapId;
	msg << value.mapDataID;
	msg << value.x;
	msg << value.y;
}
void ReadplayerPos(stNetMsg& msg,playerPos& value)
{
	msg >> value.playerId;
	msg >> value.mapId;
	msg >> value.mapDataID;
	msg >> value.x;
	msg >> value.y;
}
void WriteC2GS_LookupTeamPos(stNetMsg& msg,C2GS_LookupTeamPos& value)
{
	msg << value.playerId;
	msg.command(MSG_C2GS_LookupTeamPos);
}
void C2GS_LookupTeamPos::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_LookupTeamPos(msg_s,*this);
	EndSend();
}
void ReadC2GS_LookupTeamPos(stNetMsg& msg,C2GS_LookupTeamPos& value)
{
	msg >> value.playerId;
}
void WriteGS2C_LookupTeamPos(stNetMsg& msg,GS2C_LookupTeamPos& value)
{
	WriteArray(msg,playerPos,value.vec);
	msg.command(MSG_GS2C_LookupTeamPos);
}
void ReadGS2C_LookupTeamPos(stNetMsg& msg,GS2C_LookupTeamPos& value)
{
	ReadArray(msg,playerPos,value.vec);
}
void WriteC2GS_TransferMapInLookupPos(stNetMsg& msg,C2GS_TransferMapInLookupPos& value)
{
	msg << value.mapId;
	msg << value.mapDataID;
	msg << value.x;
	msg << value.y;
	msg << value.isTransferWithTeam;
	msg.command(MSG_C2GS_TransferMapInLookupPos);
}
void C2GS_TransferMapInLookupPos::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_TransferMapInLookupPos(msg_s,*this);
	EndSend();
}
void ReadC2GS_TransferMapInLookupPos(stNetMsg& msg,C2GS_TransferMapInLookupPos& value)
{
	msg >> value.mapId;
	msg >> value.mapDataID;
	msg >> value.x;
	msg >> value.y;
	msg >> value.isTransferWithTeam;
}
void WriteC2GS_ReqChangeMapInTransport(stNetMsg& msg,C2GS_ReqChangeMapInTransport& value)
{
	msg << value.curMapDataID;
	msg.command(MSG_C2GS_ReqChangeMapInTransport);
}
void C2GS_ReqChangeMapInTransport::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ReqChangeMapInTransport(msg_s,*this);
	EndSend();
}
void ReadC2GS_ReqChangeMapInTransport(stNetMsg& msg,C2GS_ReqChangeMapInTransport& value)
{
	msg >> value.curMapDataID;
}
void WriteC2GS_ReqChangeMapInDynamicTransport(stNetMsg& msg,C2GS_ReqChangeMapInDynamicTransport& value)
{
	msg << value.curMapDataID;
	msg << value.doorId;
	msg.command(MSG_C2GS_ReqChangeMapInDynamicTransport);
}
void C2GS_ReqChangeMapInDynamicTransport::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ReqChangeMapInDynamicTransport(msg_s,*this);
	EndSend();
}
void ReadC2GS_ReqChangeMapInDynamicTransport(stNetMsg& msg,C2GS_ReqChangeMapInDynamicTransport& value)
{
	msg >> value.curMapDataID;
	msg >> value.doorId;
}
void WriteC2GS_ReqChangeMapInWorldMap(stNetMsg& msg,C2GS_ReqChangeMapInWorldMap& value)
{
	msg << value.desMapDataID;
	msg.command(MSG_C2GS_ReqChangeMapInWorldMap);
}
void C2GS_ReqChangeMapInWorldMap::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ReqChangeMapInWorldMap(msg_s,*this);
	EndSend();
}
void ReadC2GS_ReqChangeMapInWorldMap(stNetMsg& msg,C2GS_ReqChangeMapInWorldMap& value)
{
	msg >> value.desMapDataID;
}
void WriteC2GS_ReqChangeMapByNpc(stNetMsg& msg,C2GS_ReqChangeMapByNpc& value)
{
	msg << value.id;
	msg << value.npcDataID;
	msg << value.npcTransferId;
	msg.command(MSG_C2GS_ReqChangeMapByNpc);
}
void C2GS_ReqChangeMapByNpc::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ReqChangeMapByNpc(msg_s,*this);
	EndSend();
}
void ReadC2GS_ReqChangeMapByNpc(stNetMsg& msg,C2GS_ReqChangeMapByNpc& value)
{
	msg >> value.id;
	msg >> value.npcDataID;
	msg >> value.npcTransferId;
}
void WriteC2GS_ReqEnterCopyMap(stNetMsg& msg,C2GS_ReqEnterCopyMap& value)
{
	msg << value.npcId;
	msg << value.npcDataID;
	msg << value.enterMapDataId;
	msg << value.enterType;
	msg.command(MSG_C2GS_ReqEnterCopyMap);
}
void C2GS_ReqEnterCopyMap::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ReqEnterCopyMap(msg_s,*this);
	EndSend();
}
void ReadC2GS_ReqEnterCopyMap(stNetMsg& msg,C2GS_ReqEnterCopyMap& value)
{
	msg >> value.npcId;
	msg >> value.npcDataID;
	msg >> value.enterMapDataId;
	msg >> value.enterType;
}
void WriteGS2C_ReqEnterCopyMap_Ret(stNetMsg& msg,GS2C_ReqEnterCopyMap_Ret& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_ReqEnterCopyMap_Ret);
}
void ReadGS2C_ReqEnterCopyMap_Ret(stNetMsg& msg,GS2C_ReqEnterCopyMap_Ret& value)
{
	msg >> value.retCode;
}
void WriteGS2C_BeginePrepareEnterCopy(stNetMsg& msg,GS2C_BeginePrepareEnterCopy& value)
{
	msg << value.npcId;
	msg << value.npcDataId;
	msg << value.copyMapDataId;
	msg << value.enterType;
	msg << value.sponsorId;
	msg.command(MSG_GS2C_BeginePrepareEnterCopy);
}
void ReadGS2C_BeginePrepareEnterCopy(stNetMsg& msg,GS2C_BeginePrepareEnterCopy& value)
{
	msg >> value.npcId;
	msg >> value.npcDataId;
	msg >> value.copyMapDataId;
	msg >> value.enterType;
	msg >> value.sponsorId;
}
void WriteC2GS_PrepareCompleteEnterCopy(stNetMsg& msg,C2GS_PrepareCompleteEnterCopy& value)
{
	msg << value.sponsorId;
	msg.command(MSG_C2GS_PrepareCompleteEnterCopy);
}
void C2GS_PrepareCompleteEnterCopy::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PrepareCompleteEnterCopy(msg_s,*this);
	EndSend();
}
void ReadC2GS_PrepareCompleteEnterCopy(stNetMsg& msg,C2GS_PrepareCompleteEnterCopy& value)
{
	msg >> value.sponsorId;
}
void WriteGS2C_AllPrepareEnterCopy(stNetMsg& msg,GS2C_AllPrepareEnterCopy& value)
{
	msg << value.sponsorId;
	msg.command(MSG_GS2C_AllPrepareEnterCopy);
}
void ReadGS2C_AllPrepareEnterCopy(stNetMsg& msg,GS2C_AllPrepareEnterCopy& value)
{
	msg >> value.sponsorId;
}
void WriteC2GS_SponsorCancelEnterCopyMap(stNetMsg& msg,C2GS_SponsorCancelEnterCopyMap& value)
{
	msg << value.curMapDataId;
	msg.command(MSG_C2GS_SponsorCancelEnterCopyMap);
}
void C2GS_SponsorCancelEnterCopyMap::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SponsorCancelEnterCopyMap(msg_s,*this);
	EndSend();
}
void ReadC2GS_SponsorCancelEnterCopyMap(stNetMsg& msg,C2GS_SponsorCancelEnterCopyMap& value)
{
	msg >> value.curMapDataId;
}
void WriteGS2C_CancelEnterCopyMap(stNetMsg& msg,GS2C_CancelEnterCopyMap& value)
{
	msg << value.cancelReason;
	msg.command(MSG_GS2C_CancelEnterCopyMap);
}
void ReadGS2C_CancelEnterCopyMap(stNetMsg& msg,GS2C_CancelEnterCopyMap& value)
{
	msg >> value.cancelReason;
}
void WriteC2GS_SponsorExitMatchEnterCopyMapNow(stNetMsg& msg,C2GS_SponsorExitMatchEnterCopyMapNow& value)
{
	msg << value.curMapDataId;
	msg << value.enterMapDataId;
	msg.command(MSG_C2GS_SponsorExitMatchEnterCopyMapNow);
}
void C2GS_SponsorExitMatchEnterCopyMapNow::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SponsorExitMatchEnterCopyMapNow(msg_s,*this);
	EndSend();
}
void ReadC2GS_SponsorExitMatchEnterCopyMapNow(stNetMsg& msg,C2GS_SponsorExitMatchEnterCopyMapNow& value)
{
	msg >> value.curMapDataId;
	msg >> value.enterMapDataId;
}
void WriteC2GS_SponsorCancelMatchEnter(stNetMsg& msg,C2GS_SponsorCancelMatchEnter& value)
{
	msg << value.curMapDataId;
	msg << value.enterMapDataId;
	msg.command(MSG_C2GS_SponsorCancelMatchEnter);
}
void C2GS_SponsorCancelMatchEnter::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SponsorCancelMatchEnter(msg_s,*this);
	EndSend();
}
void ReadC2GS_SponsorCancelMatchEnter(stNetMsg& msg,C2GS_SponsorCancelMatchEnter& value)
{
	msg >> value.curMapDataId;
	msg >> value.enterMapDataId;
}
void WriteGS2C_ExitMatchEnterCopyMapNow(stNetMsg& msg,GS2C_ExitMatchEnterCopyMapNow& value)
{
	msg << value.sponsorId;
	msg.command(MSG_GS2C_ExitMatchEnterCopyMapNow);
}
void ReadGS2C_ExitMatchEnterCopyMapNow(stNetMsg& msg,GS2C_ExitMatchEnterCopyMapNow& value)
{
	msg >> value.sponsorId;
}
void WriteGS2C_CancelMatchEnter(stNetMsg& msg,GS2C_CancelMatchEnter& value)
{
	msg << value.sponsorId;
	msg.command(MSG_GS2C_CancelMatchEnter);
}
void ReadGS2C_CancelMatchEnter(stNetMsg& msg,GS2C_CancelMatchEnter& value)
{
	msg >> value.sponsorId;
}
void WriteGS2C_MatchEnterCopySuccess(stNetMsg& msg,GS2C_MatchEnterCopySuccess& value)
{
	msg << value.enterMapDataId;
	msg.command(MSG_GS2C_MatchEnterCopySuccess);
}
void ReadGS2C_MatchEnterCopySuccess(stNetMsg& msg,GS2C_MatchEnterCopySuccess& value)
{
	msg >> value.enterMapDataId;
}
void WriteC2GS_PlayerLeaveCopyMap(stNetMsg& msg,C2GS_PlayerLeaveCopyMap& value)
{
	msg.command(MSG_C2GS_PlayerLeaveCopyMap);
}
void C2GS_PlayerLeaveCopyMap::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PlayerLeaveCopyMap(msg_s,*this);
	EndSend();
}
void ReadC2GS_PlayerLeaveCopyMap(stNetMsg& msg,C2GS_PlayerLeaveCopyMap& value)
{
}
void WriteFightStatsInfo(stNetMsg& msg,FightStatsInfo& value)
{
	msg << value.playerId;
	msg << value.playerName;
	msg << value.damagePercent;
	msg << value.bearDamagePercent;
	msg << value.killCnt;
	msg << value.deadCnt;
	msg << value.reliveCnt;
}
void ReadFightStatsInfo(stNetMsg& msg,FightStatsInfo& value)
{
	msg >> value.playerId;
	msg >> value.playerName;
	msg >> value.damagePercent;
	msg >> value.bearDamagePercent;
	msg >> value.killCnt;
	msg >> value.deadCnt;
	msg >> value.reliveCnt;
}
void WriteItemDataIdAndCnt(stNetMsg& msg,ItemDataIdAndCnt& value)
{
	msg << value.itemDataID;
	msg << value.cnt;
}
void ReadItemDataIdAndCnt(stNetMsg& msg,ItemDataIdAndCnt& value)
{
	msg >> value.itemDataID;
	msg >> value.cnt;
}
void WriteGS2C_CopyMapCompleted(stNetMsg& msg,GS2C_CopyMapCompleted& value)
{
	msg << value.successNum;
	msg << value.isContinue;
	msg.command(MSG_GS2C_CopyMapCompleted);
}
void ReadGS2C_CopyMapCompleted(stNetMsg& msg,GS2C_CopyMapCompleted& value)
{
	msg >> value.successNum;
	msg >> value.isContinue;
}
void WriteGS2C_CopyMapCheckOut(stNetMsg& msg,GS2C_CopyMapCheckOut& value)
{
	msg << value.successNum;
	WriteArray(msg,FightStatsInfo,value.fightStats);
	msg << value.seconds;
	msg << value.steps;
	msg << value.coin;
	msg << value.exp;
	WriteArray(msg,ItemDataIdAndCnt,value.itemInfos);
	msg.command(MSG_GS2C_CopyMapCheckOut);
}
void ReadGS2C_CopyMapCheckOut(stNetMsg& msg,GS2C_CopyMapCheckOut& value)
{
	msg >> value.successNum;
	ReadArray(msg,FightStatsInfo,value.fightStats);
	msg >> value.seconds;
	msg >> value.steps;
	msg >> value.coin;
	msg >> value.exp;
	ReadArray(msg,ItemDataIdAndCnt,value.itemInfos);
}
void WritePlayerCopyCDInfo(stNetMsg& msg,PlayerCopyCDInfo& value)
{
	msg << value.map_data_id;
	msg << value.enter_cnt;
	msg << value.remain_cnt;
}
void ReadPlayerCopyCDInfo(stNetMsg& msg,PlayerCopyCDInfo& value)
{
	msg >> value.map_data_id;
	msg >> value.enter_cnt;
	msg >> value.remain_cnt;
}
void WriteGS2C_AllCopyCDInfo(stNetMsg& msg,GS2C_AllCopyCDInfo& value)
{
	WriteArray(msg,PlayerCopyCDInfo,value.copyCdInfos);
	msg.command(MSG_GS2C_AllCopyCDInfo);
}
void ReadGS2C_AllCopyCDInfo(stNetMsg& msg,GS2C_AllCopyCDInfo& value)
{
	ReadArray(msg,PlayerCopyCDInfo,value.copyCdInfos);
}
void WriteGS2C_UpdatPlayerCopyCDInfo(stNetMsg& msg,GS2C_UpdatPlayerCopyCDInfo& value)
{
	msg << value.map_data_id;
	msg << value.enter_cnt;
	msg << value.remain_cnt;
	msg.command(MSG_GS2C_UpdatPlayerCopyCDInfo);
}
void ReadGS2C_UpdatPlayerCopyCDInfo(stNetMsg& msg,GS2C_UpdatPlayerCopyCDInfo& value)
{
	msg >> value.map_data_id;
	msg >> value.enter_cnt;
	msg >> value.remain_cnt;
}
void WriteGS2C_CopyMapClose_Countdown(stNetMsg& msg,GS2C_CopyMapClose_Countdown& value)
{
	msg << value.second;
	msg.command(MSG_GS2C_CopyMapClose_Countdown);
}
void ReadGS2C_CopyMapClose_Countdown(stNetMsg& msg,GS2C_CopyMapClose_Countdown& value)
{
	msg >> value.second;
}
void WriteGS2C_CopyInitInfo(stNetMsg& msg,GS2C_CopyInitInfo& value)
{
	msg << value.copyStepId;
	msg << value.totalCnt;
	msg << value.curCnt;
	msg << value.remainSec;
	msg << value.mapDataID;
	msg.command(MSG_GS2C_CopyInitInfo);
}
void ReadGS2C_CopyInitInfo(stNetMsg& msg,GS2C_CopyInitInfo& value)
{
	msg >> value.copyStepId;
	msg >> value.totalCnt;
	msg >> value.curCnt;
	msg >> value.remainSec;
	msg >> value.mapDataID;
}
void WriteGS2C_UpdateCopyProgress(stNetMsg& msg,GS2C_UpdateCopyProgress& value)
{
	msg << value.copyStepId;
	msg << value.curCnt;
	msg.command(MSG_GS2C_UpdateCopyProgress);
}
void ReadGS2C_UpdateCopyProgress(stNetMsg& msg,GS2C_UpdateCopyProgress& value)
{
	msg >> value.copyStepId;
	msg >> value.curCnt;
}
void WriteGS2C_MonsterSpawnRemind(stNetMsg& msg,GS2C_MonsterSpawnRemind& value)
{
	msg << value.waveIndex;
	msg << value.delaySec;
	msg << value.isActive;
	msg.command(MSG_GS2C_MonsterSpawnRemind);
}
void ReadGS2C_MonsterSpawnRemind(stNetMsg& msg,GS2C_MonsterSpawnRemind& value)
{
	msg >> value.waveIndex;
	msg >> value.delaySec;
	msg >> value.isActive;
}
void WriteGS2C_GiveSelectionToContinueCopy(stNetMsg& msg,GS2C_GiveSelectionToContinueCopy& value)
{
	msg << value.steps;
	WriteArray(msg,ItemDataIdAndCnt,value.itemInfos);
	msg.command(MSG_GS2C_GiveSelectionToContinueCopy);
}
void ReadGS2C_GiveSelectionToContinueCopy(stNetMsg& msg,GS2C_GiveSelectionToContinueCopy& value)
{
	msg >> value.steps;
	ReadArray(msg,ItemDataIdAndCnt,value.itemInfos);
}
void WriteC2GS_ReplySelectionToContinueCopy(stNetMsg& msg,C2GS_ReplySelectionToContinueCopy& value)
{
	msg << value.isContinue;
	msg.command(MSG_C2GS_ReplySelectionToContinueCopy);
}
void C2GS_ReplySelectionToContinueCopy::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ReplySelectionToContinueCopy(msg_s,*this);
	EndSend();
}
void ReadC2GS_ReplySelectionToContinueCopy(stNetMsg& msg,C2GS_ReplySelectionToContinueCopy& value)
{
	msg >> value.isContinue;
}
void WriteGS2C_ReplySelectionToContinueCopy(stNetMsg& msg,GS2C_ReplySelectionToContinueCopy& value)
{
	msg << value.playerId;
	msg << value.isContinue;
	msg.command(MSG_GS2C_ReplySelectionToContinueCopy);
}
void ReadGS2C_ReplySelectionToContinueCopy(stNetMsg& msg,GS2C_ReplySelectionToContinueCopy& value)
{
	msg >> value.playerId;
	msg >> value.isContinue;
}
void WriteGS2C_Missile(stNetMsg& msg,GS2C_Missile& value)
{
	msg << value.id;
	msg << value.ownerId;
	msg << value.skillId;
	msg << value.dataId;
	msg << value.targetX;
	msg << value.targetY;
	msg << value.offsetX;
	msg << value.offsetY;
	msg << value.multiNum;
	msg.command(MSG_GS2C_Missile);
}
void ReadGS2C_Missile(stNetMsg& msg,GS2C_Missile& value)
{
	msg >> value.id;
	msg >> value.ownerId;
	msg >> value.skillId;
	msg >> value.dataId;
	msg >> value.targetX;
	msg >> value.targetY;
	msg >> value.offsetX;
	msg >> value.offsetY;
	msg >> value.multiNum;
}
void WriteC2GS_MissileDamage(stNetMsg& msg,C2GS_MissileDamage& value)
{
	msg << value.id;
	msg << value.targetId;
	msg << value.index;
	msg << value.targetX;
	msg << value.targetY;
	msg << value.isExplosion;
	msg.command(MSG_C2GS_MissileDamage);
}
void C2GS_MissileDamage::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_MissileDamage(msg_s,*this);
	EndSend();
}
void ReadC2GS_MissileDamage(stNetMsg& msg,C2GS_MissileDamage& value)
{
	msg >> value.id;
	msg >> value.targetId;
	msg >> value.index;
	msg >> value.targetX;
	msg >> value.targetY;
	msg >> value.isExplosion;
}
void WriteGS2C_MissileDamage(stNetMsg& msg,GS2C_MissileDamage& value)
{
	msg << value.id;
	msg << value.targetId;
	msg << value.isExplosion;
	msg << value.index;
	msg.command(MSG_GS2C_MissileDamage);
}
void ReadGS2C_MissileDamage(stNetMsg& msg,GS2C_MissileDamage& value)
{
	msg >> value.id;
	msg >> value.targetId;
	msg >> value.isExplosion;
	msg >> value.index;
}
void WriteBlockSectionInfo(stNetMsg& msg,BlockSectionInfo& value)
{
	msg << value.x;
	msg << value.y;
	msg << value.dx;
	msg << value.dy;
}
void ReadBlockSectionInfo(stNetMsg& msg,BlockSectionInfo& value)
{
	msg >> value.x;
	msg >> value.y;
	msg >> value.dx;
	msg >> value.dy;
}
void WriteGS2C_SetBlockSections(stNetMsg& msg,GS2C_SetBlockSections& value)
{
	WriteArray(msg,BlockSectionInfo,value.blockSectionInfo);
	msg.command(MSG_GS2C_SetBlockSections);
}
void ReadGS2C_SetBlockSections(stNetMsg& msg,GS2C_SetBlockSections& value)
{
	ReadArray(msg,BlockSectionInfo,value.blockSectionInfo);
}
void WriteGS2C_ClearBlockSections(stNetMsg& msg,GS2C_ClearBlockSections& value)
{
	WriteArray(msg,BlockSectionInfo,value.blockSectionInfo);
	msg.command(MSG_GS2C_ClearBlockSections);
}
void ReadGS2C_ClearBlockSections(stNetMsg& msg,GS2C_ClearBlockSections& value)
{
	ReadArray(msg,BlockSectionInfo,value.blockSectionInfo);
}
void WriteC2GS_OpenDoor_Req(stNetMsg& msg,C2GS_OpenDoor_Req& value)
{
	msg << value.id;
	msg.command(MSG_C2GS_OpenDoor_Req);
}
void C2GS_OpenDoor_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_OpenDoor_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_OpenDoor_Req(stNetMsg& msg,C2GS_OpenDoor_Req& value)
{
	msg >> value.id;
}
void WriteGS2C_OpenDoor_Ret(stNetMsg& msg,GS2C_OpenDoor_Ret& value)
{
	msg << value.retCode;
	msg << value.id;
	msg.command(MSG_GS2C_OpenDoor_Ret);
}
void ReadGS2C_OpenDoor_Ret(stNetMsg& msg,GS2C_OpenDoor_Ret& value)
{
	msg >> value.retCode;
	msg >> value.id;
}
void WriteGS2C_ForbiddenArea_Exp(stNetMsg& msg,GS2C_ForbiddenArea_Exp& value)
{
	msg << value.exp;
	msg.command(MSG_GS2C_ForbiddenArea_Exp);
}
void ReadGS2C_ForbiddenArea_Exp(stNetMsg& msg,GS2C_ForbiddenArea_Exp& value)
{
	msg >> value.exp;
}
void WriteGS2C_COPY_SUCC_TIME(stNetMsg& msg,GS2C_COPY_SUCC_TIME& value)
{
	msg << value.time;
	msg.command(MSG_GS2C_COPY_SUCC_TIME);
}
void ReadGS2C_COPY_SUCC_TIME(stNetMsg& msg,GS2C_COPY_SUCC_TIME& value)
{
	msg >> value.time;
}
void WriteOpenMap(stNetMsg& msg,OpenMap& value)
{
	msg << value.id;
	msg << value.state;
}
void ReadOpenMap(stNetMsg& msg,OpenMap& value)
{
	msg >> value.id;
	msg >> value.state;
}
void WriteGS2C_OPEN_MAP_LIST(stNetMsg& msg,GS2C_OPEN_MAP_LIST& value)
{
	WriteArray(msg,OpenMap,value.bigMapList);
	WriteArray(msg,OpenMap,value.smallMapList);
	msg.command(MSG_GS2C_OPEN_MAP_LIST);
}
void ReadGS2C_OPEN_MAP_LIST(stNetMsg& msg,GS2C_OPEN_MAP_LIST& value)
{
	ReadArray(msg,OpenMap,value.bigMapList);
	ReadArray(msg,OpenMap,value.smallMapList);
}
void WriteGS2C_OPEN_MAP_UPDATE_OR_ADD(stNetMsg& msg,GS2C_OPEN_MAP_UPDATE_OR_ADD& value)
{
	msg << value.type;
	WriteOpenMap(msg, value.map);
	msg.command(MSG_GS2C_OPEN_MAP_UPDATE_OR_ADD);
}
void ReadGS2C_OPEN_MAP_UPDATE_OR_ADD(stNetMsg& msg,GS2C_OPEN_MAP_UPDATE_OR_ADD& value)
{
	msg >> value.type;
	ReadOpenMap(msg, value.map);
}
void WriteC2GS_OPEN_TREAS_Req(stNetMsg& msg,C2GS_OPEN_TREAS_Req& value)
{
	msg << value.id;
	msg << value.open_state;
	msg.command(MSG_C2GS_OPEN_TREAS_Req);
}
void C2GS_OPEN_TREAS_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_OPEN_TREAS_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_OPEN_TREAS_Req(stNetMsg& msg,C2GS_OPEN_TREAS_Req& value)
{
	msg >> value.id;
	msg >> value.open_state;
}
void WriteGS2C_OPEN_TREAS_Ret(stNetMsg& msg,GS2C_OPEN_TREAS_Ret& value)
{
	msg << value.retCode;
	msg << value.id;
	msg << value.open_state;
	msg.command(MSG_GS2C_OPEN_TREAS_Ret);
}
void ReadGS2C_OPEN_TREAS_Ret(stNetMsg& msg,GS2C_OPEN_TREAS_Ret& value)
{
	msg >> value.retCode;
	msg >> value.id;
	msg >> value.open_state;
}
void WriteGS2C_TREAS_STATE(stNetMsg& msg,GS2C_TREAS_STATE& value)
{
	msg << value.id;
	msg << value.status;
	msg << value.disTime;
	msg.command(MSG_GS2C_TREAS_STATE);
}
void ReadGS2C_TREAS_STATE(stNetMsg& msg,GS2C_TREAS_STATE& value)
{
	msg >> value.id;
	msg >> value.status;
	msg >> value.disTime;
}
void WriteC2GS_OPEN_TREAS_Succ_Req(stNetMsg& msg,C2GS_OPEN_TREAS_Succ_Req& value)
{
	msg << value.id;
	msg.command(MSG_C2GS_OPEN_TREAS_Succ_Req);
}
void C2GS_OPEN_TREAS_Succ_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_OPEN_TREAS_Succ_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_OPEN_TREAS_Succ_Req(stNetMsg& msg,C2GS_OPEN_TREAS_Succ_Req& value)
{
	msg >> value.id;
}
void WriteGUIDE_INFO(stNetMsg& msg,GUIDE_INFO& value)
{
	msg << value.x;
	msg << value.y;
}
void ReadGUIDE_INFO(stNetMsg& msg,GUIDE_INFO& value)
{
	msg >> value.x;
	msg >> value.y;
}
void WriteGS2C_GUIDE_LIST(stNetMsg& msg,GS2C_GUIDE_LIST& value)
{
	WriteArray(msg,GUIDE_INFO,value.guides);
	msg.command(MSG_GS2C_GUIDE_LIST);
}
void ReadGS2C_GUIDE_LIST(stNetMsg& msg,GS2C_GUIDE_LIST& value)
{
	ReadArray(msg,GUIDE_INFO,value.guides);
}
void WriteGS2C_FreeFightCopyPhaseInfo(stNetMsg& msg,GS2C_FreeFightCopyPhaseInfo& value)
{
	msg << value.phase;
	msg << value.countDownSecs;
	msg.command(MSG_GS2C_FreeFightCopyPhaseInfo);
}
void ReadGS2C_FreeFightCopyPhaseInfo(stNetMsg& msg,GS2C_FreeFightCopyPhaseInfo& value)
{
	msg >> value.phase;
	msg >> value.countDownSecs;
}
void WriteC2GS_FreeFightCopyScoreBoard_Req(stNetMsg& msg,C2GS_FreeFightCopyScoreBoard_Req& value)
{
	msg.command(MSG_C2GS_FreeFightCopyScoreBoard_Req);
}
void C2GS_FreeFightCopyScoreBoard_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_FreeFightCopyScoreBoard_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_FreeFightCopyScoreBoard_Req(stNetMsg& msg,C2GS_FreeFightCopyScoreBoard_Req& value)
{
}
void WritescoreBoardItem(stNetMsg& msg,scoreBoardItem& value)
{
	msg << value.name;
	msg << value.level;
	msg << value.killCnt;
	msg << value.deadCnt;
}
void ReadscoreBoardItem(stNetMsg& msg,scoreBoardItem& value)
{
	msg >> value.name;
	msg >> value.level;
	msg >> value.killCnt;
	msg >> value.deadCnt;
}
void WriteGS2C_FreeFightCopyScoreBoard(stNetMsg& msg,GS2C_FreeFightCopyScoreBoard& value)
{
	msg << value.redCampScore;
	msg << value.blueCampScore;
	WriteArray(msg,scoreBoardItem,value.redVec);
	WriteArray(msg,scoreBoardItem,value.blueVec);
	msg.command(MSG_GS2C_FreeFightCopyScoreBoard);
}
void ReadGS2C_FreeFightCopyScoreBoard(stNetMsg& msg,GS2C_FreeFightCopyScoreBoard& value)
{
	msg >> value.redCampScore;
	msg >> value.blueCampScore;
	ReadArray(msg,scoreBoardItem,value.redVec);
	ReadArray(msg,scoreBoardItem,value.blueVec);
}
void WriteGS2C_FreeFightCopyCloseTimerStart(stNetMsg& msg,GS2C_FreeFightCopyCloseTimerStart& value)
{
	msg << value.countDownSecs;
	msg.command(MSG_GS2C_FreeFightCopyCloseTimerStart);
}
void ReadGS2C_FreeFightCopyCloseTimerStart(stNetMsg& msg,GS2C_FreeFightCopyCloseTimerStart& value)
{
	msg >> value.countDownSecs;
}
void WriteGS2C_FreeFightCopyCloseTimerCancel(stNetMsg& msg,GS2C_FreeFightCopyCloseTimerCancel& value)
{
	msg << value.reserve;
	msg.command(MSG_GS2C_FreeFightCopyCloseTimerCancel);
}
void ReadGS2C_FreeFightCopyCloseTimerCancel(stNetMsg& msg,GS2C_FreeFightCopyCloseTimerCancel& value)
{
	msg >> value.reserve;
}
void WritefreeFightCheckoutItem(stNetMsg& msg,freeFightCheckoutItem& value)
{
	msg << value.id;
	msg << value.name;
	msg << value.level;
	msg << value.killCnt;
	msg << value.deadCnt;
	msg << value.bindCoin;
	msg << value.exp;
	msg << value.honor;
}
void ReadfreeFightCheckoutItem(stNetMsg& msg,freeFightCheckoutItem& value)
{
	msg >> value.id;
	msg >> value.name;
	msg >> value.level;
	msg >> value.killCnt;
	msg >> value.deadCnt;
	msg >> value.bindCoin;
	msg >> value.exp;
	msg >> value.honor;
}
void WriteGS2C_FreeFightCopyCheckout(stNetMsg& msg,GS2C_FreeFightCopyCheckout& value)
{
	msg << value.winCamp;
	msg << value.redCampScore;
	msg << value.blueCampScore;
	WriteArray(msg,freeFightCheckoutItem,value.redVec);
	WriteArray(msg,freeFightCheckoutItem,value.blueVec);
	msg.command(MSG_GS2C_FreeFightCopyCheckout);
}
void ReadGS2C_FreeFightCopyCheckout(stNetMsg& msg,GS2C_FreeFightCopyCheckout& value)
{
	msg >> value.winCamp;
	msg >> value.redCampScore;
	msg >> value.blueCampScore;
	ReadArray(msg,freeFightCheckoutItem,value.redVec);
	ReadArray(msg,freeFightCheckoutItem,value.blueVec);
}
void WriteGS2C_LivePoint(stNetMsg& msg,GS2C_LivePoint& value)
{
	msg << value.livePoint;
	msg.command(MSG_GS2C_LivePoint);
}
void ReadGS2C_LivePoint(stNetMsg& msg,GS2C_LivePoint& value)
{
	msg >> value.livePoint;
}
void WriteContentionPoint(stNetMsg& msg,ContentionPoint& value)
{
	msg << value.id;
	msg << value.x;
	msg << value.y;
	msg << value.r;
	msg << value.processOwner;
	msg << value.processType;
	msg << value.process;
}
void ReadContentionPoint(stNetMsg& msg,ContentionPoint& value)
{
	msg >> value.id;
	msg >> value.x;
	msg >> value.y;
	msg >> value.r;
	msg >> value.processOwner;
	msg >> value.processType;
	msg >> value.process;
}
void WriteGS2C_ContentionInfo(stNetMsg& msg,GS2C_ContentionInfo& value)
{
	msg << value.monsterPoint;
	msg << value.playerPoint;
	WriteArray(msg,ContentionPoint,value.contentionPoints);
	msg.command(MSG_GS2C_ContentionInfo);
}
void ReadGS2C_ContentionInfo(stNetMsg& msg,GS2C_ContentionInfo& value)
{
	msg >> value.monsterPoint;
	msg >> value.playerPoint;
	ReadArray(msg,ContentionPoint,value.contentionPoints);
}

};


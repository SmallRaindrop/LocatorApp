#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteC2GS_SignalEnterBattleMap(stNetMsg& msg,C2GS_SignalEnterBattleMap& value)
{
	msg << value.npcId;
	msg << value.npcDataId;
	msg.command(MSG_C2GS_SignalEnterBattleMap);
}
void C2GS_SignalEnterBattleMap::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SignalEnterBattleMap(msg_s,*this);
	EndSend();
}
void ReadC2GS_SignalEnterBattleMap(stNetMsg& msg,C2GS_SignalEnterBattleMap& value)
{
	msg >> value.npcId;
	msg >> value.npcDataId;
}
void WriteGS2C_SignalEnterBattleMap(stNetMsg& msg,GS2C_SignalEnterBattleMap& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_SignalEnterBattleMap);
}
void ReadGS2C_SignalEnterBattleMap(stNetMsg& msg,GS2C_SignalEnterBattleMap& value)
{
	msg >> value.retCode;
}
void WriteC2GS_TeamRequestEnterMap(stNetMsg& msg,C2GS_TeamRequestEnterMap& value)
{
	msg << value.npcId;
	msg << value.npcDataId;
	msg.command(MSG_C2GS_TeamRequestEnterMap);
}
void C2GS_TeamRequestEnterMap::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_TeamRequestEnterMap(msg_s,*this);
	EndSend();
}
void ReadC2GS_TeamRequestEnterMap(stNetMsg& msg,C2GS_TeamRequestEnterMap& value)
{
	msg >> value.npcId;
	msg >> value.npcDataId;
}
void WriteGS2C_TeamRequestEnterMap(stNetMsg& msg,GS2C_TeamRequestEnterMap& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_TeamRequestEnterMap);
}
void ReadGS2C_TeamRequestEnterMap(stNetMsg& msg,GS2C_TeamRequestEnterMap& value)
{
	msg >> value.retCode;
}
void WriteGS2C_InviteEnterBattleMap(stNetMsg& msg,GS2C_InviteEnterBattleMap& value)
{
	msg << value.npcId;
	msg << value.npcDataId;
	msg << value.inviteId;
	msg << value.inviteName;
	msg.command(MSG_GS2C_InviteEnterBattleMap);
}
void ReadGS2C_InviteEnterBattleMap(stNetMsg& msg,GS2C_InviteEnterBattleMap& value)
{
	msg >> value.npcId;
	msg >> value.npcDataId;
	msg >> value.inviteId;
	msg >> value.inviteName;
}
void WriteC2GS_InviteEnterBattleMap(stNetMsg& msg,C2GS_InviteEnterBattleMap& value)
{
	msg << value.isAgree;
	msg << value.inviterId;
	msg << value.npcId;
	msg << value.npcDataId;
	msg.command(MSG_C2GS_InviteEnterBattleMap);
}
void C2GS_InviteEnterBattleMap::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_InviteEnterBattleMap(msg_s,*this);
	EndSend();
}
void ReadC2GS_InviteEnterBattleMap(stNetMsg& msg,C2GS_InviteEnterBattleMap& value)
{
	msg >> value.isAgree;
	msg >> value.inviterId;
	msg >> value.npcId;
	msg >> value.npcDataId;
}
void WriteGS2C_InviteerEnterBattleMap(stNetMsg& msg,GS2C_InviteerEnterBattleMap& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_InviteerEnterBattleMap);
}
void ReadGS2C_InviteerEnterBattleMap(stNetMsg& msg,GS2C_InviteerEnterBattleMap& value)
{
	msg >> value.retCode;
}
void WriteGS2C_InviteEnterBattleMap_Result(stNetMsg& msg,GS2C_InviteEnterBattleMap_Result& value)
{
	msg << value.retCode;
	msg << value.playerName;
	msg.command(MSG_GS2C_InviteEnterBattleMap_Result);
}
void ReadGS2C_InviteEnterBattleMap_Result(stNetMsg& msg,GS2C_InviteEnterBattleMap_Result& value)
{
	msg >> value.retCode;
	msg >> value.playerName;
}
void WriteGS2C_UpdateBattlePlayerCnt(stNetMsg& msg,GS2C_UpdateBattlePlayerCnt& value)
{
	msg << value.redPlayerCnt;
	msg << value.bluePlayerCnt;
	msg << value.remainTime;
	msg.command(MSG_GS2C_UpdateBattlePlayerCnt);
}
void ReadGS2C_UpdateBattlePlayerCnt(stNetMsg& msg,GS2C_UpdateBattlePlayerCnt& value)
{
	msg >> value.redPlayerCnt;
	msg >> value.bluePlayerCnt;
	msg >> value.remainTime;
}
void WritebattleBaseInfo(stNetMsg& msg,battleBaseInfo& value)
{
	msg << value.myScore;
	msg << value.redScore;
	msg << value.redKillPlayerCnt;
	msg << value.redKillBaseCnt;
	msg << value.redGatherCnt;
	msg << value.redKillMonster;
	msg << value.blueScore;
	msg << value.blueKillPlayerCnt;
	msg << value.blueKillBaseCnt;
	msg << value.blueGatherCnt;
	msg << value.blueKillMonster;
}
void ReadbattleBaseInfo(stNetMsg& msg,battleBaseInfo& value)
{
	msg >> value.myScore;
	msg >> value.redScore;
	msg >> value.redKillPlayerCnt;
	msg >> value.redKillBaseCnt;
	msg >> value.redGatherCnt;
	msg >> value.redKillMonster;
	msg >> value.blueScore;
	msg >> value.blueKillPlayerCnt;
	msg >> value.blueKillBaseCnt;
	msg >> value.blueGatherCnt;
	msg >> value.blueKillMonster;
}
void WriteGS2C_EndBattle(stNetMsg& msg,GS2C_EndBattle& value)
{
	msg << value.exp;
	msg << value.money;
	msg << value.honor;
	WritebattleBaseInfo(msg, value.st);
	msg.command(MSG_GS2C_EndBattle);
}
void ReadGS2C_EndBattle(stNetMsg& msg,GS2C_EndBattle& value)
{
	msg >> value.exp;
	msg >> value.money;
	msg >> value.honor;
	ReadbattleBaseInfo(msg, value.st);
}
void WriteGS2C_UpdateBattleInfo(stNetMsg& msg,GS2C_UpdateBattleInfo& value)
{
	msg << value.myScore;
	msg << value.redScore;
	msg << value.blueScore;
	msg << value.killPlayerCnt;
	msg << value.deadCnt;
	msg.command(MSG_GS2C_UpdateBattleInfo);
}
void ReadGS2C_UpdateBattleInfo(stNetMsg& msg,GS2C_UpdateBattleInfo& value)
{
	msg >> value.myScore;
	msg >> value.redScore;
	msg >> value.blueScore;
	msg >> value.killPlayerCnt;
	msg >> value.deadCnt;
}
void WriteC2GS_BuyBuff(stNetMsg& msg,C2GS_BuyBuff& value)
{
	msg << value.buffId;
	msg.command(MSG_C2GS_BuyBuff);
}
void C2GS_BuyBuff::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_BuyBuff(msg_s,*this);
	EndSend();
}
void ReadC2GS_BuyBuff(stNetMsg& msg,C2GS_BuyBuff& value)
{
	msg >> value.buffId;
}
void WriteGS2C_BuyBuff(stNetMsg& msg,GS2C_BuyBuff& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_BuyBuff);
}
void ReadGS2C_BuyBuff(stNetMsg& msg,GS2C_BuyBuff& value)
{
	msg >> value.retCode;
}
void WriteGS2C_TeamTimeOut(stNetMsg& msg,GS2C_TeamTimeOut& value)
{
	msg.command(MSG_GS2C_TeamTimeOut);
}
void ReadGS2C_TeamTimeOut(stNetMsg& msg,GS2C_TeamTimeOut& value)
{
}
void WriteGS2C_Open_Battle_Door(stNetMsg& msg,GS2C_Open_Battle_Door& value)
{
	msg << value.id;
	msg.command(MSG_GS2C_Open_Battle_Door);
}
void ReadGS2C_Open_Battle_Door(stNetMsg& msg,GS2C_Open_Battle_Door& value)
{
	msg >> value.id;
}
void WriteGS2C_OfflineExp(stNetMsg& msg,GS2C_OfflineExp& value)
{
	msg << value.normalProtOfflineExp;
	msg << value.vipExtraProtOfflineExp;
	msg << value.notProtOfflineExp;
	msg << value.robbedOfflineExp;
	msg.command(MSG_GS2C_OfflineExp);
}
void ReadGS2C_OfflineExp(stNetMsg& msg,GS2C_OfflineExp& value)
{
	msg >> value.normalProtOfflineExp;
	msg >> value.vipExtraProtOfflineExp;
	msg >> value.notProtOfflineExp;
	msg >> value.robbedOfflineExp;
}
void WriteC2GS_PickupOfflineExp(stNetMsg& msg,C2GS_PickupOfflineExp& value)
{
	msg.command(MSG_C2GS_PickupOfflineExp);
}
void C2GS_PickupOfflineExp::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PickupOfflineExp(msg_s,*this);
	EndSend();
}
void ReadC2GS_PickupOfflineExp(stNetMsg& msg,C2GS_PickupOfflineExp& value)
{
}
void WriteRobbedRecord(stNetMsg& msg,RobbedRecord& value)
{
	msg << value.robExp;
	msg << value.robTime;
	msg << value.id;
	msg << value.name;
	msg << value.career;
	msg << value.level;
	msg << value.fight;
	msg << value.guildId;
}
void ReadRobbedRecord(stNetMsg& msg,RobbedRecord& value)
{
	msg >> value.robExp;
	msg >> value.robTime;
	msg >> value.id;
	msg >> value.name;
	msg >> value.career;
	msg >> value.level;
	msg >> value.fight;
	msg >> value.guildId;
}
void WriteGS2C_RobbedOfflineExpDetailInfo(stNetMsg& msg,GS2C_RobbedOfflineExpDetailInfo& value)
{
	WriteArray(msg,RobbedRecord,value.robbedRecordList);
	msg.command(MSG_GS2C_RobbedOfflineExpDetailInfo);
}
void ReadGS2C_RobbedOfflineExpDetailInfo(stNetMsg& msg,GS2C_RobbedOfflineExpDetailInfo& value)
{
	ReadArray(msg,RobbedRecord,value.robbedRecordList);
}

};


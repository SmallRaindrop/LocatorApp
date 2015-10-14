#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteShortcutInfo(stNetMsg& msg,ShortcutInfo& value)
{
	msg << value.index;
	msg << value.type;
	msg << value.id;
}
void ReadShortcutInfo(stNetMsg& msg,ShortcutInfo& value)
{
	msg >> value.index;
	msg >> value.type;
	msg >> value.id;
}
void WriteGSWithC_Shortcuts(stNetMsg& msg,GSWithC_Shortcuts& value)
{
	WriteArray(msg,ShortcutInfo,value.shortcutInfos);
	msg.command(MSG_GSWithC_Shortcuts);
}
void GSWithC_Shortcuts::Send(IOSocket* pIOSock){
	BeginSend();
	WriteGSWithC_Shortcuts(msg_s,*this);
	EndSend();
}
void ReadGSWithC_Shortcuts(stNetMsg& msg,GSWithC_Shortcuts& value)
{
	ReadArray(msg,ShortcutInfo,value.shortcutInfos);
}
void WriteGS2C_Preference_Set_Info(stNetMsg& msg,GS2C_Preference_Set_Info& value)
{
	msg << value.teamSet;
	msg.command(MSG_GS2C_Preference_Set_Info);
}
void ReadGS2C_Preference_Set_Info(stNetMsg& msg,GS2C_Preference_Set_Info& value)
{
	msg >> value.teamSet;
}
void WriteVariantData(stNetMsg& msg,VariantData& value)
{
	msg << value.index;
	msg << value.value;
}
void ReadVariantData(stNetMsg& msg,VariantData& value)
{
	msg >> value.index;
	msg >> value.value;
}
void WriteGS2C_VariantDataSet(stNetMsg& msg,GS2C_VariantDataSet& value)
{
	msg << value.variant_type;
	WriteArray(msg,VariantData,value.info_list);
	msg.command(MSG_GS2C_VariantDataSet);
}
void ReadGS2C_VariantDataSet(stNetMsg& msg,GS2C_VariantDataSet& value)
{
	msg >> value.variant_type;
	ReadArray(msg,VariantData,value.info_list);
}
void WriteArenaPlayerEquipinfo(stNetMsg& msg,ArenaPlayerEquipinfo& value)
{
	msg << value.equipDataId;
	msg << value.part;
	msg << value.stars;
	msg << value.luck;
}
void ReadArenaPlayerEquipinfo(stNetMsg& msg,ArenaPlayerEquipinfo& value)
{
	msg >> value.equipDataId;
	msg >> value.part;
	msg >> value.stars;
	msg >> value.luck;
}
void WriteArenaPlayerInfo(stNetMsg& msg,ArenaPlayerInfo& value)
{
	msg << value.playerId;
	msg << value.name;
	msg << value.sex;
	msg << value.career;
	msg << value.level;
	msg << value.fight;
	msg << value.rank;
	WriteArray(msg,ArenaPlayerEquipinfo,value.equipList);
}
void ReadArenaPlayerInfo(stNetMsg& msg,ArenaPlayerInfo& value)
{
	msg >> value.playerId;
	msg >> value.name;
	msg >> value.sex;
	msg >> value.career;
	msg >> value.level;
	msg >> value.fight;
	msg >> value.rank;
	ReadArray(msg,ArenaPlayerEquipinfo,value.equipList);
}
void WriteArenaMsgInfo(stNetMsg& msg,ArenaMsgInfo& value)
{
	msg << value.name;
	msg << value.flag;
	msg << value.rank;
	msg << value.time;
}
void ReadArenaMsgInfo(stNetMsg& msg,ArenaMsgInfo& value)
{
	msg >> value.name;
	msg >> value.flag;
	msg >> value.rank;
	msg >> value.time;
}
void WriteC2GS_EnterArena_Req(stNetMsg& msg,C2GS_EnterArena_Req& value)
{
	msg.command(MSG_C2GS_EnterArena_Req);
}
void C2GS_EnterArena_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_EnterArena_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_EnterArena_Req(stNetMsg& msg,C2GS_EnterArena_Req& value)
{
}
void WriteGS2C_EnterArena_Ret(stNetMsg& msg,GS2C_EnterArena_Ret& value)
{
	msg << value.ret;
	msg.command(MSG_GS2C_EnterArena_Ret);
}
void ReadGS2C_EnterArena_Ret(stNetMsg& msg,GS2C_EnterArena_Ret& value)
{
	msg >> value.ret;
}
void WriteGS2C_ArenaInfo(stNetMsg& msg,GS2C_ArenaInfo& value)
{
	msg << value.curRank;
	msg << value.fight;
	msg << value.awardId;
	WriteArray(msg,ArenaPlayerInfo,value.arenaPlayerList);
	WriteArray(msg,ArenaMsgInfo,value.arenaMsgList);
	msg.command(MSG_GS2C_ArenaInfo);
}
void ReadGS2C_ArenaInfo(stNetMsg& msg,GS2C_ArenaInfo& value)
{
	msg >> value.curRank;
	msg >> value.fight;
	msg >> value.awardId;
	ReadArray(msg,ArenaPlayerInfo,value.arenaPlayerList);
	ReadArray(msg,ArenaMsgInfo,value.arenaMsgList);
}
void WriteC2GS_StartChallenge_Req(stNetMsg& msg,C2GS_StartChallenge_Req& value)
{
	msg << value.playerId;
	msg.command(MSG_C2GS_StartChallenge_Req);
}
void C2GS_StartChallenge_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_StartChallenge_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_StartChallenge_Req(stNetMsg& msg,C2GS_StartChallenge_Req& value)
{
	msg >> value.playerId;
}
void WriteGS2C_StartChallenge_Ret(stNetMsg& msg,GS2C_StartChallenge_Ret& value)
{
	msg << value.ret;
	msg.command(MSG_GS2C_StartChallenge_Ret);
}
void ReadGS2C_StartChallenge_Ret(stNetMsg& msg,GS2C_StartChallenge_Ret& value)
{
	msg >> value.ret;
}
void WriteC2GS_Start_Count_down_Req(stNetMsg& msg,C2GS_Start_Count_down_Req& value)
{
	msg.command(MSG_C2GS_Start_Count_down_Req);
}
void C2GS_Start_Count_down_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Start_Count_down_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_Start_Count_down_Req(stNetMsg& msg,C2GS_Start_Count_down_Req& value)
{
}
void WriteC2GS_Arena_Award_Req(stNetMsg& msg,C2GS_Arena_Award_Req& value)
{
	msg.command(MSG_C2GS_Arena_Award_Req);
}
void C2GS_Arena_Award_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Arena_Award_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_Arena_Award_Req(stNetMsg& msg,C2GS_Arena_Award_Req& value)
{
}
void WriteGS2C_Arena_Award_Ret(stNetMsg& msg,GS2C_Arena_Award_Ret& value)
{
	msg << value.ret;
	msg.command(MSG_GS2C_Arena_Award_Ret);
}
void ReadGS2C_Arena_Award_Ret(stNetMsg& msg,GS2C_Arena_Award_Ret& value)
{
	msg >> value.ret;
}
void WriteDefenseMonsterInfo(stNetMsg& msg,DefenseMonsterInfo& value)
{
	msg << value.id;
	msg << value.dataId;
	msg << value.isDead;
}
void ReadDefenseMonsterInfo(stNetMsg& msg,DefenseMonsterInfo& value)
{
	msg >> value.id;
	msg >> value.dataId;
	msg >> value.isDead;
}
void WriteGS2C_Update_TowerDefenseMonster(stNetMsg& msg,GS2C_Update_TowerDefenseMonster& value)
{
	WriteArray(msg,DefenseMonsterInfo,value.defenseMonsterInfos);
	msg.command(MSG_GS2C_Update_TowerDefenseMonster);
}
void ReadGS2C_Update_TowerDefenseMonster(stNetMsg& msg,GS2C_Update_TowerDefenseMonster& value)
{
	ReadArray(msg,DefenseMonsterInfo,value.defenseMonsterInfos);
}
void WriteGS2C_MonsterRefresh_Time(stNetMsg& msg,GS2C_MonsterRefresh_Time& value)
{
	msg << value.waveIndex;
	msg << value.delayMs;
	msg.command(MSG_GS2C_MonsterRefresh_Time);
}
void ReadGS2C_MonsterRefresh_Time(stNetMsg& msg,GS2C_MonsterRefresh_Time& value)
{
	msg >> value.waveIndex;
	msg >> value.delayMs;
}
void WriteC2GS_Upgrade_TowerDefenseMonster(stNetMsg& msg,C2GS_Upgrade_TowerDefenseMonster& value)
{
	msg << value.id;
	msg << value.dataId;
	msg.command(MSG_C2GS_Upgrade_TowerDefenseMonster);
}
void C2GS_Upgrade_TowerDefenseMonster::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Upgrade_TowerDefenseMonster(msg_s,*this);
	EndSend();
}
void ReadC2GS_Upgrade_TowerDefenseMonster(stNetMsg& msg,C2GS_Upgrade_TowerDefenseMonster& value)
{
	msg >> value.id;
	msg >> value.dataId;
}
void WriteC2GS_RecoverLife_TowerDefenseMonster(stNetMsg& msg,C2GS_RecoverLife_TowerDefenseMonster& value)
{
	msg << value.id;
	msg << value.dataId;
	msg.command(MSG_C2GS_RecoverLife_TowerDefenseMonster);
}
void C2GS_RecoverLife_TowerDefenseMonster::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_RecoverLife_TowerDefenseMonster(msg_s,*this);
	EndSend();
}
void ReadC2GS_RecoverLife_TowerDefenseMonster(stNetMsg& msg,C2GS_RecoverLife_TowerDefenseMonster& value)
{
	msg >> value.id;
	msg >> value.dataId;
}
void WriteGS2C_TowerDefense_Update_AwardInfo(stNetMsg& msg,GS2C_TowerDefense_Update_AwardInfo& value)
{
	msg << value.spiritNum;
	msg << value.awardExp;
	msg << value.awardCoin;
	msg.command(MSG_GS2C_TowerDefense_Update_AwardInfo);
}
void ReadGS2C_TowerDefense_Update_AwardInfo(stNetMsg& msg,GS2C_TowerDefense_Update_AwardInfo& value)
{
	msg >> value.spiritNum;
	msg >> value.awardExp;
	msg >> value.awardCoin;
}
void WriteGS2C_TowerDefenseCopy_Result(stNetMsg& msg,GS2C_TowerDefenseCopy_Result& value)
{
	msg << value.isSuccess;
	msg.command(MSG_GS2C_TowerDefenseCopy_Result);
}
void ReadGS2C_TowerDefenseCopy_Result(stNetMsg& msg,GS2C_TowerDefenseCopy_Result& value)
{
	msg >> value.isSuccess;
}
void WriteGS2C_ArenaCopy_Result(stNetMsg& msg,GS2C_ArenaCopy_Result& value)
{
	msg << value.isSuccess;
	msg.command(MSG_GS2C_ArenaCopy_Result);
}
void ReadGS2C_ArenaCopy_Result(stNetMsg& msg,GS2C_ArenaCopy_Result& value)
{
	msg >> value.isSuccess;
}
void WriteLogin_Notice(stNetMsg& msg,Login_Notice& value)
{
	msg << value.title;
	msg << value.content;
	msg << value.date;
	msg << value.signature;
}
void ReadLogin_Notice(stNetMsg& msg,Login_Notice& value)
{
	msg >> value.title;
	msg >> value.content;
	msg >> value.date;
	msg >> value.signature;
}
void WriteGS2C_Login_Notice(stNetMsg& msg,GS2C_Login_Notice& value)
{
	WriteArray(msg,Login_Notice,value.login_Notice_lists);
	msg.command(MSG_GS2C_Login_Notice);
}
void ReadGS2C_Login_Notice(stNetMsg& msg,GS2C_Login_Notice& value)
{
	ReadArray(msg,Login_Notice,value.login_Notice_lists);
}
void WriteC2GS_HeartBeat(stNetMsg& msg,C2GS_HeartBeat& value)
{
	msg.command(MSG_C2GS_HeartBeat);
}
void C2GS_HeartBeat::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_HeartBeat(msg_s,*this);
	EndSend();
}
void ReadC2GS_HeartBeat(stNetMsg& msg,C2GS_HeartBeat& value)
{
}
void WritePay_Info(stNetMsg& msg,Pay_Info& value)
{
	msg << value.id;
	msg << value.gameMoney;
	msg << value.ucMoney;
	msg << value.state;
}
void ReadPay_Info(stNetMsg& msg,Pay_Info& value)
{
	msg >> value.id;
	msg >> value.gameMoney;
	msg >> value.ucMoney;
	msg >> value.state;
}
void WriteGS2C_Pay_Info(stNetMsg& msg,GS2C_Pay_Info& value)
{
	WriteArray(msg,Pay_Info,value.pay_Info_lists);
	msg.command(MSG_GS2C_Pay_Info);
}
void ReadGS2C_Pay_Info(stNetMsg& msg,GS2C_Pay_Info& value)
{
	ReadArray(msg,Pay_Info,value.pay_Info_lists);
}
void WriteC2GS_Player_Get_Sign_In_Info(stNetMsg& msg,C2GS_Player_Get_Sign_In_Info& value)
{
	msg.command(MSG_C2GS_Player_Get_Sign_In_Info);
}
void C2GS_Player_Get_Sign_In_Info::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Player_Get_Sign_In_Info(msg_s,*this);
	EndSend();
}
void ReadC2GS_Player_Get_Sign_In_Info(stNetMsg& msg,C2GS_Player_Get_Sign_In_Info& value)
{
}
void WriteGS2C_Player_Sign_In_Info(stNetMsg& msg,GS2C_Player_Sign_In_Info& value)
{
	msg << value.isAlready;
	msg.command(MSG_GS2C_Player_Sign_In_Info);
}
void ReadGS2C_Player_Sign_In_Info(stNetMsg& msg,GS2C_Player_Sign_In_Info& value)
{
	msg >> value.isAlready;
}
void WriteC2GS_Player_Sign_In(stNetMsg& msg,C2GS_Player_Sign_In& value)
{
	msg.command(MSG_C2GS_Player_Sign_In);
}
void C2GS_Player_Sign_In::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Player_Sign_In(msg_s,*this);
	EndSend();
}
void ReadC2GS_Player_Sign_In(stNetMsg& msg,C2GS_Player_Sign_In& value)
{
}
void WriteGS2C_Player_Sign_In_Result(stNetMsg& msg,GS2C_Player_Sign_In_Result& value)
{
	msg << value.days;
	msg << value.retCode;
	msg.command(MSG_GS2C_Player_Sign_In_Result);
}
void ReadGS2C_Player_Sign_In_Result(stNetMsg& msg,GS2C_Player_Sign_In_Result& value)
{
	msg >> value.days;
	msg >> value.retCode;
}
void WriteC2GS_Player_Again_Sign_In(stNetMsg& msg,C2GS_Player_Again_Sign_In& value)
{
	msg << value.days;
	msg.command(MSG_C2GS_Player_Again_Sign_In);
}
void C2GS_Player_Again_Sign_In::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Player_Again_Sign_In(msg_s,*this);
	EndSend();
}
void ReadC2GS_Player_Again_Sign_In(stNetMsg& msg,C2GS_Player_Again_Sign_In& value)
{
	msg >> value.days;
}
void WriteGS2C_Player_Again_Sign_In_Result(stNetMsg& msg,GS2C_Player_Again_Sign_In_Result& value)
{
	msg << value.days;
	msg << value.retCode;
	msg.command(MSG_GS2C_Player_Again_Sign_In_Result);
}
void ReadGS2C_Player_Again_Sign_In_Result(stNetMsg& msg,GS2C_Player_Again_Sign_In_Result& value)
{
	msg >> value.days;
	msg >> value.retCode;
}
void WriteC2GS_Player_Get_Award(stNetMsg& msg,C2GS_Player_Get_Award& value)
{
	msg << value.id;
	msg.command(MSG_C2GS_Player_Get_Award);
}
void C2GS_Player_Get_Award::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Player_Get_Award(msg_s,*this);
	EndSend();
}
void ReadC2GS_Player_Get_Award(stNetMsg& msg,C2GS_Player_Get_Award& value)
{
	msg >> value.id;
}
void WriteGS2C_Player_Get_Award_Result(stNetMsg& msg,GS2C_Player_Get_Award_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_Player_Get_Award_Result);
}
void ReadGS2C_Player_Get_Award_Result(stNetMsg& msg,GS2C_Player_Get_Award_Result& value)
{
	msg >> value.retCode;
}
void WriteC2GS_Sign_In_One_Key_Get_Award(stNetMsg& msg,C2GS_Sign_In_One_Key_Get_Award& value)
{
	msg.command(MSG_C2GS_Sign_In_One_Key_Get_Award);
}
void C2GS_Sign_In_One_Key_Get_Award::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Sign_In_One_Key_Get_Award(msg_s,*this);
	EndSend();
}
void ReadC2GS_Sign_In_One_Key_Get_Award(stNetMsg& msg,C2GS_Sign_In_One_Key_Get_Award& value)
{
}
void WriteC2GS_System_Set_Request(stNetMsg& msg,C2GS_System_Set_Request& value)
{
	msg << value.type;
	msg << value.flag;
	msg.command(MSG_C2GS_System_Set_Request);
}
void C2GS_System_Set_Request::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_System_Set_Request(msg_s,*this);
	EndSend();
}
void ReadC2GS_System_Set_Request(stNetMsg& msg,C2GS_System_Set_Request& value)
{
	msg >> value.type;
	msg >> value.flag;
}
void WriteGS2C_System_Set_Request_Result(stNetMsg& msg,GS2C_System_Set_Request_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_System_Set_Request_Result);
}
void ReadGS2C_System_Set_Request_Result(stNetMsg& msg,GS2C_System_Set_Request_Result& value)
{
	msg >> value.retCode;
}
void WriteC2GS_MakeQuestion(stNetMsg& msg,C2GS_MakeQuestion& value)
{
	msg << value.playerId;
	msg.command(MSG_C2GS_MakeQuestion);
}
void C2GS_MakeQuestion::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_MakeQuestion(msg_s,*this);
	EndSend();
}
void ReadC2GS_MakeQuestion(stNetMsg& msg,C2GS_MakeQuestion& value)
{
	msg >> value.playerId;
}
void WriteGS2C_MakeQuestion(stNetMsg& msg,GS2C_MakeQuestion& value)
{
	msg << value.questionVec;
	msg.command(MSG_GS2C_MakeQuestion);
}
void ReadGS2C_MakeQuestion(stNetMsg& msg,GS2C_MakeQuestion& value)
{
	msg >> value.questionVec;
}
void WriteC2GS_Question(stNetMsg& msg,C2GS_Question& value)
{
	msg << value.id;
	msg << value.type;
	msg << value.answer;
	msg.command(MSG_C2GS_Question);
}
void C2GS_Question::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_Question(msg_s,*this);
	EndSend();
}
void ReadC2GS_Question(stNetMsg& msg,C2GS_Question& value)
{
	msg >> value.id;
	msg >> value.type;
	msg >> value.answer;
}
void WriteGS2C_Question(stNetMsg& msg,GS2C_Question& value)
{
	msg << value.errCnt;
	msg << value.rightCnt;
	msg << value.useTime;
	msg << value.remainTime;
	msg << value.retCode;
	msg.command(MSG_GS2C_Question);
}
void ReadGS2C_Question(stNetMsg& msg,GS2C_Question& value)
{
	msg >> value.errCnt;
	msg >> value.rightCnt;
	msg >> value.useTime;
	msg >> value.remainTime;
	msg >> value.retCode;
}
void WriteC2GS_ResetQuestErr(stNetMsg& msg,C2GS_ResetQuestErr& value)
{
	msg << value.cnt;
	msg.command(MSG_C2GS_ResetQuestErr);
}
void C2GS_ResetQuestErr::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ResetQuestErr(msg_s,*this);
	EndSend();
}
void ReadC2GS_ResetQuestErr(stNetMsg& msg,C2GS_ResetQuestErr& value)
{
	msg >> value.cnt;
}
void WriteGS2C_ResetQuestErr(stNetMsg& msg,GS2C_ResetQuestErr& value)
{
	msg << value.newErrCnt;
	msg << value.retCode;
	msg.command(MSG_GS2C_ResetQuestErr);
}
void ReadGS2C_ResetQuestErr(stNetMsg& msg,GS2C_ResetQuestErr& value)
{
	msg >> value.newErrCnt;
	msg >> value.retCode;
}
void WriteGS2C_Question_OnLine(stNetMsg& msg,GS2C_Question_OnLine& value)
{
	msg << value.errCnt;
	msg << value.rightCnt;
	msg << value.useTime;
	msg << value.remainTime;
	msg << value.lastScore;
	msg << value.weekScore;
	msg << value.questionVec;
	msg << value.finishQuestionVec;
	msg.command(MSG_GS2C_Question_OnLine);
}
void ReadGS2C_Question_OnLine(stNetMsg& msg,GS2C_Question_OnLine& value)
{
	msg >> value.errCnt;
	msg >> value.rightCnt;
	msg >> value.useTime;
	msg >> value.remainTime;
	msg >> value.lastScore;
	msg >> value.weekScore;
	msg >> value.questionVec;
	msg >> value.finishQuestionVec;
}
void WriteC2GS_FinishQuestion(stNetMsg& msg,C2GS_FinishQuestion& value)
{
	msg << value.playerId;
	msg.command(MSG_C2GS_FinishQuestion);
}
void C2GS_FinishQuestion::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_FinishQuestion(msg_s,*this);
	EndSend();
}
void ReadC2GS_FinishQuestion(stNetMsg& msg,C2GS_FinishQuestion& value)
{
	msg >> value.playerId;
}
void WriteGS2C_FinishQuestion(stNetMsg& msg,GS2C_FinishQuestion& value)
{
	msg << value.exp;
	msg << value.coin;
	msg << value.bindCoin;
	msg << value.score;
	msg << value.weekScore;
	msg.command(MSG_GS2C_FinishQuestion);
}
void ReadGS2C_FinishQuestion(stNetMsg& msg,GS2C_FinishQuestion& value)
{
	msg >> value.exp;
	msg >> value.coin;
	msg >> value.bindCoin;
	msg >> value.score;
	msg >> value.weekScore;
}
void WriteC2GS_RankList_Req(stNetMsg& msg,C2GS_RankList_Req& value)
{
	msg << value.rankType;
	msg.command(MSG_C2GS_RankList_Req);
}
void C2GS_RankList_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_RankList_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_RankList_Req(stNetMsg& msg,C2GS_RankList_Req& value)
{
	msg >> value.rankType;
}
void WriteRankInfo(stNetMsg& msg,RankInfo& value)
{
	msg << value.rank;
	msg << value.name;
	msg << value.sex;
	msg << value.career;
	msg << value.count;
}
void ReadRankInfo(stNetMsg& msg,RankInfo& value)
{
	msg >> value.rank;
	msg >> value.name;
	msg >> value.sex;
	msg >> value.career;
	msg >> value.count;
}
void WriteGS2C_RankList_Ret(stNetMsg& msg,GS2C_RankList_Ret& value)
{
	msg << value.retCode;
	msg << value.rankType;
	WriteArray(msg,RankInfo,value.rank_list);
	msg.command(MSG_GS2C_RankList_Ret);
}
void ReadGS2C_RankList_Ret(stNetMsg& msg,GS2C_RankList_Ret& value)
{
	msg >> value.retCode;
	msg >> value.rankType;
	ReadArray(msg,RankInfo,value.rank_list);
}
void WriteC2GS_BossRefreshList_Req(stNetMsg& msg,C2GS_BossRefreshList_Req& value)
{
	msg.command(MSG_C2GS_BossRefreshList_Req);
}
void C2GS_BossRefreshList_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_BossRefreshList_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_BossRefreshList_Req(stNetMsg& msg,C2GS_BossRefreshList_Req& value)
{
}
void WriteBossRefreshInfo(stNetMsg& msg,BossRefreshInfo& value)
{
	msg << value.isDead;
	msg << value.monsterDataId;
	msg << value.nextRefreshDownCountSec;
}
void ReadBossRefreshInfo(stNetMsg& msg,BossRefreshInfo& value)
{
	msg >> value.isDead;
	msg >> value.monsterDataId;
	msg >> value.nextRefreshDownCountSec;
}
void WriteGS2C_BossRefreshList_Ret(stNetMsg& msg,GS2C_BossRefreshList_Ret& value)
{
	WriteArray(msg,BossRefreshInfo,value.refresh_list);
	msg.command(MSG_GS2C_BossRefreshList_Ret);
}
void ReadGS2C_BossRefreshList_Ret(stNetMsg& msg,GS2C_BossRefreshList_Ret& value)
{
	ReadArray(msg,BossRefreshInfo,value.refresh_list);
}
void WriteC2GS_SaveNewHandGuildProgress(stNetMsg& msg,C2GS_SaveNewHandGuildProgress& value)
{
	msg << value.index;
	msg.command(MSG_C2GS_SaveNewHandGuildProgress);
}
void C2GS_SaveNewHandGuildProgress::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SaveNewHandGuildProgress(msg_s,*this);
	EndSend();
}
void ReadC2GS_SaveNewHandGuildProgress(stNetMsg& msg,C2GS_SaveNewHandGuildProgress& value)
{
	msg >> value.index;
}

};


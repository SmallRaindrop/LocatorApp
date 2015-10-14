
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct ShortcutInfo
{
	int8 index;
	int8 type;
	int64 id;
};
void WriteShortcutInfo(stNetMsg& msg,ShortcutInfo& value);
void ReadShortcutInfo(stNetMsg& msg,ShortcutInfo& value);

struct GSWithC_Shortcuts
{
	vector<ShortcutInfo> shortcutInfos;
	void Send(IOSocket* pIOSock);
};
void WriteGSWithC_Shortcuts(stNetMsg& msg,GSWithC_Shortcuts& value);
bool OnGSWithC_Shortcuts(GSWithC_Shortcuts* value);
void ReadGSWithC_Shortcuts(stNetMsg& msg,GSWithC_Shortcuts& value);

struct GS2C_Preference_Set_Info
{
	int8 teamSet;
};
void WriteGS2C_Preference_Set_Info(stNetMsg& msg,GS2C_Preference_Set_Info& value);
bool OnGS2C_Preference_Set_Info(GS2C_Preference_Set_Info* value);
void ReadGS2C_Preference_Set_Info(stNetMsg& msg,GS2C_Preference_Set_Info& value);

struct VariantData
{
	int8 index;
	int32 value;
};
void WriteVariantData(stNetMsg& msg,VariantData& value);
void ReadVariantData(stNetMsg& msg,VariantData& value);

struct GS2C_VariantDataSet
{
	int8 variant_type;
	vector<VariantData> info_list;
};
void WriteGS2C_VariantDataSet(stNetMsg& msg,GS2C_VariantDataSet& value);
bool OnGS2C_VariantDataSet(GS2C_VariantDataSet* value);
void ReadGS2C_VariantDataSet(stNetMsg& msg,GS2C_VariantDataSet& value);

struct ArenaPlayerEquipinfo
{
	int32 equipDataId;
	int8 part;
	int8 stars;
	int8 luck;
};
void WriteArenaPlayerEquipinfo(stNetMsg& msg,ArenaPlayerEquipinfo& value);
void ReadArenaPlayerEquipinfo(stNetMsg& msg,ArenaPlayerEquipinfo& value);

struct ArenaPlayerInfo
{
	int64 playerId;
	string name;
	int8 sex;
	int8 career;
	int32 level;
	int32 fight;
	int32 rank;
	vector<ArenaPlayerEquipinfo> equipList;
};
void WriteArenaPlayerInfo(stNetMsg& msg,ArenaPlayerInfo& value);
void ReadArenaPlayerInfo(stNetMsg& msg,ArenaPlayerInfo& value);

struct ArenaMsgInfo
{
	string name;
	int8 flag;
	int32 rank;
	int32 time;
};
void WriteArenaMsgInfo(stNetMsg& msg,ArenaMsgInfo& value);
void ReadArenaMsgInfo(stNetMsg& msg,ArenaMsgInfo& value);

struct C2GS_EnterArena_Req
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_EnterArena_Req(stNetMsg& msg,C2GS_EnterArena_Req& value);
void ReadC2GS_EnterArena_Req(stNetMsg& msg,C2GS_EnterArena_Req& value);

struct GS2C_EnterArena_Ret
{
	int32 ret;
};
void WriteGS2C_EnterArena_Ret(stNetMsg& msg,GS2C_EnterArena_Ret& value);
bool OnGS2C_EnterArena_Ret(GS2C_EnterArena_Ret* value);
void ReadGS2C_EnterArena_Ret(stNetMsg& msg,GS2C_EnterArena_Ret& value);

struct GS2C_ArenaInfo
{
	int32 curRank;
	int32 fight;
	int32 awardId;
	vector<ArenaPlayerInfo> arenaPlayerList;
	vector<ArenaMsgInfo> arenaMsgList;
};
void WriteGS2C_ArenaInfo(stNetMsg& msg,GS2C_ArenaInfo& value);
bool OnGS2C_ArenaInfo(GS2C_ArenaInfo* value);
void ReadGS2C_ArenaInfo(stNetMsg& msg,GS2C_ArenaInfo& value);

struct C2GS_StartChallenge_Req
{
	int64 playerId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_StartChallenge_Req(stNetMsg& msg,C2GS_StartChallenge_Req& value);
void ReadC2GS_StartChallenge_Req(stNetMsg& msg,C2GS_StartChallenge_Req& value);

struct GS2C_StartChallenge_Ret
{
	int32 ret;
};
void WriteGS2C_StartChallenge_Ret(stNetMsg& msg,GS2C_StartChallenge_Ret& value);
bool OnGS2C_StartChallenge_Ret(GS2C_StartChallenge_Ret* value);
void ReadGS2C_StartChallenge_Ret(stNetMsg& msg,GS2C_StartChallenge_Ret& value);

struct C2GS_Start_Count_down_Req
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Start_Count_down_Req(stNetMsg& msg,C2GS_Start_Count_down_Req& value);
void ReadC2GS_Start_Count_down_Req(stNetMsg& msg,C2GS_Start_Count_down_Req& value);

struct C2GS_Arena_Award_Req
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Arena_Award_Req(stNetMsg& msg,C2GS_Arena_Award_Req& value);
void ReadC2GS_Arena_Award_Req(stNetMsg& msg,C2GS_Arena_Award_Req& value);

struct GS2C_Arena_Award_Ret
{
	int32 ret;
};
void WriteGS2C_Arena_Award_Ret(stNetMsg& msg,GS2C_Arena_Award_Ret& value);
bool OnGS2C_Arena_Award_Ret(GS2C_Arena_Award_Ret* value);
void ReadGS2C_Arena_Award_Ret(stNetMsg& msg,GS2C_Arena_Award_Ret& value);

struct DefenseMonsterInfo
{
	int64 id;
	int32 dataId;
	int8 isDead;
};
void WriteDefenseMonsterInfo(stNetMsg& msg,DefenseMonsterInfo& value);
void ReadDefenseMonsterInfo(stNetMsg& msg,DefenseMonsterInfo& value);

struct GS2C_Update_TowerDefenseMonster
{
	vector<DefenseMonsterInfo> defenseMonsterInfos;
};
void WriteGS2C_Update_TowerDefenseMonster(stNetMsg& msg,GS2C_Update_TowerDefenseMonster& value);
bool OnGS2C_Update_TowerDefenseMonster(GS2C_Update_TowerDefenseMonster* value);
void ReadGS2C_Update_TowerDefenseMonster(stNetMsg& msg,GS2C_Update_TowerDefenseMonster& value);

struct GS2C_MonsterRefresh_Time
{
	int8 waveIndex;
	int32 delayMs;
};
void WriteGS2C_MonsterRefresh_Time(stNetMsg& msg,GS2C_MonsterRefresh_Time& value);
bool OnGS2C_MonsterRefresh_Time(GS2C_MonsterRefresh_Time* value);
void ReadGS2C_MonsterRefresh_Time(stNetMsg& msg,GS2C_MonsterRefresh_Time& value);

struct C2GS_Upgrade_TowerDefenseMonster
{
	int64 id;
	int32 dataId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Upgrade_TowerDefenseMonster(stNetMsg& msg,C2GS_Upgrade_TowerDefenseMonster& value);
void ReadC2GS_Upgrade_TowerDefenseMonster(stNetMsg& msg,C2GS_Upgrade_TowerDefenseMonster& value);

struct C2GS_RecoverLife_TowerDefenseMonster
{
	int64 id;
	int32 dataId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_RecoverLife_TowerDefenseMonster(stNetMsg& msg,C2GS_RecoverLife_TowerDefenseMonster& value);
void ReadC2GS_RecoverLife_TowerDefenseMonster(stNetMsg& msg,C2GS_RecoverLife_TowerDefenseMonster& value);

struct GS2C_TowerDefense_Update_AwardInfo
{
	int32 spiritNum;
	int32 awardExp;
	int32 awardCoin;
};
void WriteGS2C_TowerDefense_Update_AwardInfo(stNetMsg& msg,GS2C_TowerDefense_Update_AwardInfo& value);
bool OnGS2C_TowerDefense_Update_AwardInfo(GS2C_TowerDefense_Update_AwardInfo* value);
void ReadGS2C_TowerDefense_Update_AwardInfo(stNetMsg& msg,GS2C_TowerDefense_Update_AwardInfo& value);

struct GS2C_TowerDefenseCopy_Result
{
	int8 isSuccess;
};
void WriteGS2C_TowerDefenseCopy_Result(stNetMsg& msg,GS2C_TowerDefenseCopy_Result& value);
bool OnGS2C_TowerDefenseCopy_Result(GS2C_TowerDefenseCopy_Result* value);
void ReadGS2C_TowerDefenseCopy_Result(stNetMsg& msg,GS2C_TowerDefenseCopy_Result& value);

struct GS2C_ArenaCopy_Result
{
	int8 isSuccess;
};
void WriteGS2C_ArenaCopy_Result(stNetMsg& msg,GS2C_ArenaCopy_Result& value);
bool OnGS2C_ArenaCopy_Result(GS2C_ArenaCopy_Result* value);
void ReadGS2C_ArenaCopy_Result(stNetMsg& msg,GS2C_ArenaCopy_Result& value);

struct Login_Notice
{
	string title;
	string content;
	string date;
	string signature;
};
void WriteLogin_Notice(stNetMsg& msg,Login_Notice& value);
void ReadLogin_Notice(stNetMsg& msg,Login_Notice& value);

struct GS2C_Login_Notice
{
	vector<Login_Notice> login_Notice_lists;
};
void WriteGS2C_Login_Notice(stNetMsg& msg,GS2C_Login_Notice& value);
bool OnGS2C_Login_Notice(GS2C_Login_Notice* value);
void ReadGS2C_Login_Notice(stNetMsg& msg,GS2C_Login_Notice& value);

struct C2GS_HeartBeat
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_HeartBeat(stNetMsg& msg,C2GS_HeartBeat& value);
void ReadC2GS_HeartBeat(stNetMsg& msg,C2GS_HeartBeat& value);

struct Pay_Info
{
	int8 id;
	int32 gameMoney;
	int32 ucMoney;
	int8 state;
};
void WritePay_Info(stNetMsg& msg,Pay_Info& value);
void ReadPay_Info(stNetMsg& msg,Pay_Info& value);

struct GS2C_Pay_Info
{
	vector<Pay_Info> pay_Info_lists;
};
void WriteGS2C_Pay_Info(stNetMsg& msg,GS2C_Pay_Info& value);
bool OnGS2C_Pay_Info(GS2C_Pay_Info* value);
void ReadGS2C_Pay_Info(stNetMsg& msg,GS2C_Pay_Info& value);

struct C2GS_Player_Get_Sign_In_Info
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Player_Get_Sign_In_Info(stNetMsg& msg,C2GS_Player_Get_Sign_In_Info& value);
void ReadC2GS_Player_Get_Sign_In_Info(stNetMsg& msg,C2GS_Player_Get_Sign_In_Info& value);

struct GS2C_Player_Sign_In_Info
{
	int8 isAlready;
};
void WriteGS2C_Player_Sign_In_Info(stNetMsg& msg,GS2C_Player_Sign_In_Info& value);
bool OnGS2C_Player_Sign_In_Info(GS2C_Player_Sign_In_Info* value);
void ReadGS2C_Player_Sign_In_Info(stNetMsg& msg,GS2C_Player_Sign_In_Info& value);

struct C2GS_Player_Sign_In
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Player_Sign_In(stNetMsg& msg,C2GS_Player_Sign_In& value);
void ReadC2GS_Player_Sign_In(stNetMsg& msg,C2GS_Player_Sign_In& value);

struct GS2C_Player_Sign_In_Result
{
	int32 days;
	int8 retCode;
};
void WriteGS2C_Player_Sign_In_Result(stNetMsg& msg,GS2C_Player_Sign_In_Result& value);
bool OnGS2C_Player_Sign_In_Result(GS2C_Player_Sign_In_Result* value);
void ReadGS2C_Player_Sign_In_Result(stNetMsg& msg,GS2C_Player_Sign_In_Result& value);

struct C2GS_Player_Again_Sign_In
{
	int32 days;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Player_Again_Sign_In(stNetMsg& msg,C2GS_Player_Again_Sign_In& value);
void ReadC2GS_Player_Again_Sign_In(stNetMsg& msg,C2GS_Player_Again_Sign_In& value);

struct GS2C_Player_Again_Sign_In_Result
{
	int32 days;
	int8 retCode;
};
void WriteGS2C_Player_Again_Sign_In_Result(stNetMsg& msg,GS2C_Player_Again_Sign_In_Result& value);
bool OnGS2C_Player_Again_Sign_In_Result(GS2C_Player_Again_Sign_In_Result* value);
void ReadGS2C_Player_Again_Sign_In_Result(stNetMsg& msg,GS2C_Player_Again_Sign_In_Result& value);

struct C2GS_Player_Get_Award
{
	int8 id;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Player_Get_Award(stNetMsg& msg,C2GS_Player_Get_Award& value);
void ReadC2GS_Player_Get_Award(stNetMsg& msg,C2GS_Player_Get_Award& value);

struct GS2C_Player_Get_Award_Result
{
	int8 retCode;
};
void WriteGS2C_Player_Get_Award_Result(stNetMsg& msg,GS2C_Player_Get_Award_Result& value);
bool OnGS2C_Player_Get_Award_Result(GS2C_Player_Get_Award_Result* value);
void ReadGS2C_Player_Get_Award_Result(stNetMsg& msg,GS2C_Player_Get_Award_Result& value);

struct C2GS_Sign_In_One_Key_Get_Award
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Sign_In_One_Key_Get_Award(stNetMsg& msg,C2GS_Sign_In_One_Key_Get_Award& value);
void ReadC2GS_Sign_In_One_Key_Get_Award(stNetMsg& msg,C2GS_Sign_In_One_Key_Get_Award& value);

struct C2GS_System_Set_Request
{
	int32 type;
	int32 flag;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_System_Set_Request(stNetMsg& msg,C2GS_System_Set_Request& value);
void ReadC2GS_System_Set_Request(stNetMsg& msg,C2GS_System_Set_Request& value);

struct GS2C_System_Set_Request_Result
{
	int8 retCode;
};
void WriteGS2C_System_Set_Request_Result(stNetMsg& msg,GS2C_System_Set_Request_Result& value);
bool OnGS2C_System_Set_Request_Result(GS2C_System_Set_Request_Result* value);
void ReadGS2C_System_Set_Request_Result(stNetMsg& msg,GS2C_System_Set_Request_Result& value);

struct C2GS_MakeQuestion
{
	int64 playerId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_MakeQuestion(stNetMsg& msg,C2GS_MakeQuestion& value);
void ReadC2GS_MakeQuestion(stNetMsg& msg,C2GS_MakeQuestion& value);

struct GS2C_MakeQuestion
{
	vector<int32> questionVec;
};
void WriteGS2C_MakeQuestion(stNetMsg& msg,GS2C_MakeQuestion& value);
bool OnGS2C_MakeQuestion(GS2C_MakeQuestion* value);
void ReadGS2C_MakeQuestion(stNetMsg& msg,GS2C_MakeQuestion& value);

struct C2GS_Question
{
	int32 id;
	int8 type;
	int8 answer;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Question(stNetMsg& msg,C2GS_Question& value);
void ReadC2GS_Question(stNetMsg& msg,C2GS_Question& value);

struct GS2C_Question
{
	int8 errCnt;
	int8 rightCnt;
	int32 useTime;
	int32 remainTime;
	int8 retCode;
};
void WriteGS2C_Question(stNetMsg& msg,GS2C_Question& value);
bool OnGS2C_Question(GS2C_Question* value);
void ReadGS2C_Question(stNetMsg& msg,GS2C_Question& value);

struct C2GS_ResetQuestErr
{
	int32 cnt;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ResetQuestErr(stNetMsg& msg,C2GS_ResetQuestErr& value);
void ReadC2GS_ResetQuestErr(stNetMsg& msg,C2GS_ResetQuestErr& value);

struct GS2C_ResetQuestErr
{
	int16 newErrCnt;
	int8 retCode;
};
void WriteGS2C_ResetQuestErr(stNetMsg& msg,GS2C_ResetQuestErr& value);
bool OnGS2C_ResetQuestErr(GS2C_ResetQuestErr* value);
void ReadGS2C_ResetQuestErr(stNetMsg& msg,GS2C_ResetQuestErr& value);

struct GS2C_Question_OnLine
{
	int8 errCnt;
	int8 rightCnt;
	int32 useTime;
	int32 remainTime;
	int32 lastScore;
	int32 weekScore;
	vector<int32> questionVec;
	vector<int32> finishQuestionVec;
};
void WriteGS2C_Question_OnLine(stNetMsg& msg,GS2C_Question_OnLine& value);
bool OnGS2C_Question_OnLine(GS2C_Question_OnLine* value);
void ReadGS2C_Question_OnLine(stNetMsg& msg,GS2C_Question_OnLine& value);

struct C2GS_FinishQuestion
{
	int64 playerId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_FinishQuestion(stNetMsg& msg,C2GS_FinishQuestion& value);
void ReadC2GS_FinishQuestion(stNetMsg& msg,C2GS_FinishQuestion& value);

struct GS2C_FinishQuestion
{
	int32 exp;
	int32 coin;
	int32 bindCoin;
	int32 score;
	int32 weekScore;
};
void WriteGS2C_FinishQuestion(stNetMsg& msg,GS2C_FinishQuestion& value);
bool OnGS2C_FinishQuestion(GS2C_FinishQuestion* value);
void ReadGS2C_FinishQuestion(stNetMsg& msg,GS2C_FinishQuestion& value);

struct C2GS_RankList_Req
{
	int8 rankType;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_RankList_Req(stNetMsg& msg,C2GS_RankList_Req& value);
void ReadC2GS_RankList_Req(stNetMsg& msg,C2GS_RankList_Req& value);

struct RankInfo
{
	int8 rank;
	string name;
	int8 sex;
	int8 career;
	int32 count;
};
void WriteRankInfo(stNetMsg& msg,RankInfo& value);
void ReadRankInfo(stNetMsg& msg,RankInfo& value);

struct GS2C_RankList_Ret
{
	int32 retCode;
	int8 rankType;
	vector<RankInfo> rank_list;
};
void WriteGS2C_RankList_Ret(stNetMsg& msg,GS2C_RankList_Ret& value);
bool OnGS2C_RankList_Ret(GS2C_RankList_Ret* value);
void ReadGS2C_RankList_Ret(stNetMsg& msg,GS2C_RankList_Ret& value);

struct C2GS_BossRefreshList_Req
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_BossRefreshList_Req(stNetMsg& msg,C2GS_BossRefreshList_Req& value);
void ReadC2GS_BossRefreshList_Req(stNetMsg& msg,C2GS_BossRefreshList_Req& value);

struct BossRefreshInfo
{
	int8 isDead;
	int32 monsterDataId;
	int32 nextRefreshDownCountSec;
};
void WriteBossRefreshInfo(stNetMsg& msg,BossRefreshInfo& value);
void ReadBossRefreshInfo(stNetMsg& msg,BossRefreshInfo& value);

struct GS2C_BossRefreshList_Ret
{
	vector<BossRefreshInfo> refresh_list;
};
void WriteGS2C_BossRefreshList_Ret(stNetMsg& msg,GS2C_BossRefreshList_Ret& value);
bool OnGS2C_BossRefreshList_Ret(GS2C_BossRefreshList_Ret* value);
void ReadGS2C_BossRefreshList_Ret(stNetMsg& msg,GS2C_BossRefreshList_Ret& value);

struct C2GS_SaveNewHandGuildProgress
{
	int32 index;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SaveNewHandGuildProgress(stNetMsg& msg,C2GS_SaveNewHandGuildProgress& value);
void ReadC2GS_SaveNewHandGuildProgress(stNetMsg& msg,C2GS_SaveNewHandGuildProgress& value);


};


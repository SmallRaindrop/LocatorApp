
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_others(stNetMsg& msg);
const int MSG_GSWithC_Shortcuts			= 20002;
const int MSG_GS2C_Preference_Set_Info			= 20003;
const int MSG_GS2C_VariantDataSet			= 20005;
const int MSG_C2GS_EnterArena_Req			= 20009;
const int MSG_GS2C_EnterArena_Ret			= 20010;
const int MSG_GS2C_ArenaInfo			= 20011;
const int MSG_C2GS_StartChallenge_Req			= 20012;
const int MSG_GS2C_StartChallenge_Ret			= 20013;
const int MSG_C2GS_Start_Count_down_Req			= 20014;
const int MSG_C2GS_Arena_Award_Req			= 20015;
const int MSG_GS2C_Arena_Award_Ret			= 20016;
const int MSG_GS2C_Update_TowerDefenseMonster			= 20018;
const int MSG_GS2C_MonsterRefresh_Time			= 20019;
const int MSG_C2GS_Upgrade_TowerDefenseMonster			= 20020;
const int MSG_C2GS_RecoverLife_TowerDefenseMonster			= 20021;
const int MSG_GS2C_TowerDefense_Update_AwardInfo			= 20022;
const int MSG_GS2C_TowerDefenseCopy_Result			= 20023;
const int MSG_GS2C_ArenaCopy_Result			= 20024;
const int MSG_GS2C_Login_Notice			= 20026;
const int MSG_C2GS_HeartBeat			= 20027;
const int MSG_GS2C_Pay_Info			= 20029;
const int MSG_C2GS_Player_Get_Sign_In_Info			= 20030;
const int MSG_GS2C_Player_Sign_In_Info			= 20031;
const int MSG_C2GS_Player_Sign_In			= 20032;
const int MSG_GS2C_Player_Sign_In_Result			= 20033;
const int MSG_C2GS_Player_Again_Sign_In			= 20034;
const int MSG_GS2C_Player_Again_Sign_In_Result			= 20035;
const int MSG_C2GS_Player_Get_Award			= 20036;
const int MSG_GS2C_Player_Get_Award_Result			= 20037;
const int MSG_C2GS_Sign_In_One_Key_Get_Award			= 20038;
const int MSG_C2GS_System_Set_Request			= 20039;
const int MSG_GS2C_System_Set_Request_Result			= 20040;
const int MSG_C2GS_MakeQuestion			= 20041;
const int MSG_GS2C_MakeQuestion			= 20042;
const int MSG_C2GS_Question			= 20043;
const int MSG_GS2C_Question			= 20044;
const int MSG_C2GS_ResetQuestErr			= 20045;
const int MSG_GS2C_ResetQuestErr			= 20046;
const int MSG_GS2C_Question_OnLine			= 20047;
const int MSG_C2GS_FinishQuestion			= 20048;
const int MSG_GS2C_FinishQuestion			= 20049;
const int MSG_C2GS_RankList_Req			= 20050;
const int MSG_GS2C_RankList_Ret			= 20052;
const int MSG_C2GS_BossRefreshList_Req			= 20053;
const int MSG_GS2C_BossRefreshList_Ret			= 20055;
const int MSG_C2GS_SaveNewHandGuildProgress			= 20056;

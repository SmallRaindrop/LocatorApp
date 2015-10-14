#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_others(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GSWithC_Shortcuts);
 		CMD_DEAL(GS2C_Preference_Set_Info);
 		CMD_DEAL(GS2C_VariantDataSet);
 		CMD_DEAL(GS2C_EnterArena_Ret);
 		CMD_DEAL(GS2C_ArenaInfo);
 		CMD_DEAL(GS2C_StartChallenge_Ret);
 		CMD_DEAL(GS2C_Arena_Award_Ret);
 		CMD_DEAL(GS2C_Update_TowerDefenseMonster);
 		CMD_DEAL(GS2C_MonsterRefresh_Time);
 		CMD_DEAL(GS2C_TowerDefense_Update_AwardInfo);
 		CMD_DEAL(GS2C_TowerDefenseCopy_Result);
 		CMD_DEAL(GS2C_ArenaCopy_Result);
 		CMD_DEAL(GS2C_Login_Notice);
 		CMD_DEAL(GS2C_Pay_Info);
 		CMD_DEAL(GS2C_Player_Sign_In_Info);
 		CMD_DEAL(GS2C_Player_Sign_In_Result);
 		CMD_DEAL(GS2C_Player_Again_Sign_In_Result);
 		CMD_DEAL(GS2C_Player_Get_Award_Result);
 		CMD_DEAL(GS2C_System_Set_Request_Result);
 		CMD_DEAL(GS2C_MakeQuestion);
 		CMD_DEAL(GS2C_Question);
 		CMD_DEAL(GS2C_ResetQuestErr);
 		CMD_DEAL(GS2C_Question_OnLine);
 		CMD_DEAL(GS2C_FinishQuestion);
 		CMD_DEAL(GS2C_RankList_Ret);
 		CMD_DEAL(GS2C_BossRefreshList_Ret);
 	END_DEAL();
	return false;
}

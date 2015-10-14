#include "GameDef.h"
#include "pk_others.h"
#include "GameScene/GameVariable.h"
#include "GameScene/Hero.h"
#include "GameScene/MessageCenter.h"
#include "../GameScene/GameUILayer.h"

namespace pk
{
	bool  OnGSWithC_Shortcuts(struct GSWithC_Shortcuts *value)
	{
		return true;
	}

	bool  OnGS2C_Preference_Set_Info(GS2C_Preference_Set_Info *value)
	{
		return true;
	}

	bool OnGS2C_VariantDataSet(GS2C_VariantDataSet *value)
	{
		return true;
	}


	//Arena
	bool OnGS2C_EnterArena_Ret(struct pk::GS2C_EnterArena_Ret *value)
	{
		return true;
	}

	bool OnGS2C_ArenaInfo(struct pk::GS2C_ArenaInfo *value)
	{
		return true;
	}

	bool OnGS2C_StartChallenge_Ret(struct pk::GS2C_StartChallenge_Ret *value)
	{
		return true;
	}

	bool OnGS2C_Arena_Award_Ret(struct pk::GS2C_Arena_Award_Ret *value)
	{
		return true;
	}



	// TowerDefense
	bool OnGS2C_Update_TowerDefenseMonster(GS2C_Update_TowerDefenseMonster *value)
	{
		return true;
	}

	bool OnGS2C_MonsterRefresh_Time(struct pk::GS2C_MonsterRefresh_Time *value)
	{
		return true;
	} 

	bool OnGS2C_TowerDefense_Update_AwardInfo(GS2C_TowerDefense_Update_AwardInfo* value)
	{
		return true;
	}
	bool OnGS2C_TowerDefenseCopy_Result(GS2C_TowerDefenseCopy_Result* value)
	{
		return true;
	}

	bool OnGS2C_ArenaCopy_Result(GS2C_ArenaCopy_Result* value)
	{
		return true;
	}

	bool OnGS2C_Login_Notice(GS2C_Login_Notice* value)
	{
		return true;
	}

	bool OnGS2C_Pay_Info(GS2C_Pay_Info* value)
	{
		return true;
	}


	bool OnGS2C_Player_Sign_In_Info(GS2C_Player_Sign_In_Info* value)
	{
		return true;
	}

	bool OnGS2C_Player_Sign_In_Result(GS2C_Player_Sign_In_Result* value)
	{
		return true;
	}

	bool OnGS2C_Player_Again_Sign_In_Result(GS2C_Player_Again_Sign_In_Result* value)
	{
		return true;
	}

	bool OnGS2C_Player_Get_Award_Result(GS2C_Player_Get_Award_Result* value)
	{
		return true;
	}

	bool OnGS2C_System_Set_Request_Result(GS2C_System_Set_Request_Result* value)
	{
		return true;
	}

	bool OnGS2C_MakeQuestion(GS2C_MakeQuestion* value)
	{
		return true;
	}

	bool OnGS2C_Question(GS2C_Question* value)
	{
		return true;
	}

	bool OnGS2C_ResetQuestErr(GS2C_ResetQuestErr* value)
	{
		return true;
	}

	bool OnGS2C_Question_OnLine(GS2C_Question_OnLine* value)
	{
		return true;
	}

	bool OnGS2C_FinishQuestion(GS2C_FinishQuestion* value)
	{
		return true;
	}

	bool OnGS2C_RankList_Ret(GS2C_RankList_Ret* value)
	{
		return true;
	}

	bool OnGS2C_BossRefreshList_Ret(GS2C_BossRefreshList_Ret *value)
	{
		return true;
	}

}

#include "pk_battle.h"

namespace pk{

	bool OnGS2C_InviteEnterBattleMap(GS2C_InviteEnterBattleMap *value)
	{
		return true;
	}

	bool OnGS2C_SignalEnterBattleMap(GS2C_SignalEnterBattleMap *value)
	{
		return true;
	}

	bool OnGS2C_TeamRequestEnterMap(GS2C_TeamRequestEnterMap *value)
	{
		return true;
	}

	bool OnGS2C_InviteerEnterBattleMap(GS2C_InviteerEnterBattleMap *value)
	{
		return true;
	}

	bool OnGS2C_InviteEnterBattleMap_Result(GS2C_InviteEnterBattleMap_Result *value)
	{
		return true;
	}

	bool OnGS2C_UpdateBattlePlayerCnt(GS2C_UpdateBattlePlayerCnt *value)
	{
		return true;
	}

	bool OnGS2C_EndBattle(GS2C_EndBattle *value)
	{
		return true;
	}

	bool OnGS2C_UpdateBattleInfo(GS2C_UpdateBattleInfo *value)
	{
		return true;
	}

	bool OnGS2C_BuyBuff(GS2C_BuyBuff *value)
	{

		return true;
	}

	bool OnGS2C_TeamTimeOut(GS2C_TeamTimeOut *value)
	{
		return true;
	}

	bool OnGS2C_Open_Battle_Door(GS2C_Open_Battle_Door *value)
	{
		return true;
	}

	bool OnGS2C_OfflineExp(struct GS2C_OfflineExp *)
	{
		//must modify
		return true;
	}

	bool OnGS2C_RobbedOfflineExpDetailInfo(GS2C_RobbedOfflineExpDetailInfo *value)
	{
		//must modify
		return true;
	}

}


#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_battle(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_SignalEnterBattleMap);
 		CMD_DEAL(GS2C_TeamRequestEnterMap);
 		CMD_DEAL(GS2C_InviteEnterBattleMap);
 		CMD_DEAL(GS2C_InviteerEnterBattleMap);
 		CMD_DEAL(GS2C_InviteEnterBattleMap_Result);
 		CMD_DEAL(GS2C_UpdateBattlePlayerCnt);
 		CMD_DEAL(GS2C_EndBattle);
 		CMD_DEAL(GS2C_UpdateBattleInfo);
 		CMD_DEAL(GS2C_BuyBuff);
 		CMD_DEAL(GS2C_TeamTimeOut);
 		CMD_DEAL(GS2C_Open_Battle_Door);
 		CMD_DEAL(GS2C_OfflineExp);
 		CMD_DEAL(GS2C_RobbedOfflineExpDetailInfo);
 	END_DEAL();
	return false;
}

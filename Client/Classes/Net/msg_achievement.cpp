#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_achievement(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_FinishAndUnFinishAchievementList);
 		CMD_DEAL(GS2C_AchieveProgressChange);
 		CMD_DEAL(GS2C_AddAchievement);
 		CMD_DEAL(GS2C_UseAchievement);
 		CMD_DEAL(GS2C_UpdateAchievementFinishCnt);
 	END_DEAL();
	return false;
}

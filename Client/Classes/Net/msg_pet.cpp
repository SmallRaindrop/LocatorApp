#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_pet(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_PET_EXP_UPDATE);
 		CMD_DEAL(GS2C_CALL_PET_Ret);
 		CMD_DEAL(GS2C_CALL_BACK_PET_Ret);
 		CMD_DEAL(GS2C_PET_MAP_UPDATE);
 		CMD_DEAL(GS2C_PET_STRENG_Ret);
 		CMD_DEAL(GS2C_PET_FEED_Ret);
 	END_DEAL();
	return false;
}

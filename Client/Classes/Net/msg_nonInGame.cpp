#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_nonInGame(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_Login_Ret);
 		CMD_DEAL(GS2C_CreatePlayer_Ret);
 		CMD_DEAL(GS2C_DeletePlayer_Ret);
 		CMD_DEAL(GS2C_ReturnToSelectRoleDlg_Ret);
 		CMD_DEAL(GS2C_SendPlayerDataComplete);
 	END_DEAL();
	return false;
}

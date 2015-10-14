#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_betweenClientLs(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(LS2C_Login_Ret);
 		CMD_DEAL(LS2C_GameServerList_Ret);
 		CMD_DEAL(LS2C_SelGameServer_Ret);
 	END_DEAL();
	return false;
}

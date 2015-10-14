#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_betweenLsPs(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(LS2PS_Register_Request);
 		CMD_DEAL(PS2LS_Register_Ret);
 		CMD_DEAL(PS2LS_PayInfo_Request);
 		CMD_DEAL(LS2PS_PayInfo_Ret);
 	END_DEAL();
	return false;
}

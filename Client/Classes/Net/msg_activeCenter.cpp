#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_activeCenter(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_ActiveCenterBaseInfo);
 		CMD_DEAL(GS2C_InActive);
 		CMD_DEAL(GS2C_Guture);
 		CMD_DEAL(GS2C_Completed);
 		CMD_DEAL(GS2C_UpdateActive);
 		CMD_DEAL(GS2C_RequestEnterActive);
 	END_DEAL();
	return false;
}

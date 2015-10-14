#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_chat(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_Monster_ChatMsg);
 	END_DEAL();
	return false;
}

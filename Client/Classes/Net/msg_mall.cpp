#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_mall(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_MallInfo);
 		CMD_DEAL(GS2C_MallHot9);
 		CMD_DEAL(GS2C_MallLuckyPrice);
 		CMD_DEAL(GS2C_Common_Buy_Result);
 		CMD_DEAL(GS2C_Lucky_Buy_Result);
 		CMD_DEAL(GS2C_Mall_Refresh_Result);
 		CMD_DEAL(GS2C_vip_Buy_Result);
 	END_DEAL();
	return false;
}

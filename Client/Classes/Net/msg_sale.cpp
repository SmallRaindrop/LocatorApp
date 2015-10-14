#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_sale(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_PutOnGold_Result);
 		CMD_DEAL(GS2C_TakeDown_Result);
 		CMD_DEAL(GS2C_Buy);
 		CMD_DEAL(GS2C_Buy_Result);
 		CMD_DEAL(GS2C_Filter_Gold_Result);
 		CMD_DEAL(GS2C_Delete_Sale);
 	END_DEAL();
	return false;
}

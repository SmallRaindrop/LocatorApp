#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_friend(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_All_Friend_Info);
 		CMD_DEAL(GS2C_Friend_Info);
 		CMD_DEAL(GS2C_Add_Friend_Result);
 		CMD_DEAL(GS2C_Remove_Friend_Result);
 		CMD_DEAL(GS2C_Request_Friend_State_Result);
 		CMD_DEAL(GS2C_Palyer_Touch_List_Ret);
 	END_DEAL();
	return false;
}

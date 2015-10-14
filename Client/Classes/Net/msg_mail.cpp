#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_mail(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_Send_Mail_Result);
 		CMD_DEAL(GS2C_Read_Mail_Result);
 		CMD_DEAL(GS2C_Delete_Mail_Result);
 		CMD_DEAL(GS2C_Delete_Mail_List_Result);
 		CMD_DEAL(GS2C_Get_Attach_Result);
 		CMD_DEAL(GS2C_Get_Attach_List_Result);
 	END_DEAL();
	return false;
}

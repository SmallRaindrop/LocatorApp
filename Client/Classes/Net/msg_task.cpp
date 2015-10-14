#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_task(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_AccpetTask_Result);
 		CMD_DEAL(GS2C_CannelTask_Result);
 		CMD_DEAL(GS2C_SubmitTask_Result);
 		CMD_DEAL(GS2C_AcceptTaskList);
 		CMD_DEAL(GS2C_CompleteTaskList);
 		CMD_DEAL(GS2C_TaskProgressChange);
 		CMD_DEAL(GS2C_CompleteGather_Result);
 		CMD_DEAL(GS2C_AccpetTaskChain);
 		CMD_DEAL(GS2C_CannelTaskChain);
 	END_DEAL();
	return false;
}

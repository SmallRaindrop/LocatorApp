
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_task(stNetMsg& msg);
const int MSG_C2GS_AccpetTask			= 23002;
const int MSG_GS2C_AccpetTask_Result			= 23003;
const int MSG_C2GS_CannelTask			= 23004;
const int MSG_GS2C_CannelTask_Result			= 23005;
const int MSG_C2GS_SubmitTask			= 23006;
const int MSG_GS2C_SubmitTask_Result			= 23007;
const int MSG_GS2C_AcceptTaskList			= 23009;
const int MSG_GS2C_CompleteTaskList			= 23011;
const int MSG_GS2C_TaskProgressChange			= 23012;
const int MSG_C2GS_CompleteGather			= 23013;
const int MSG_GS2C_CompleteGather_Result			= 23014;
const int MSG_C2GS_AccpetTaskChain			= 23015;
const int MSG_GS2C_AccpetTaskChain			= 23016;
const int MSG_C2GS_SubmitTaskChain			= 23017;
const int MSG_C2GS_CannelTaskChain			= 23018;
const int MSG_GS2C_CannelTaskChain			= 23019;

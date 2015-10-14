
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_activeCenter(stNetMsg& msg);
const int MSG_GS2C_ActiveCenterBaseInfo			= 27004;
const int MSG_GS2C_InActive			= 27006;
const int MSG_GS2C_Guture			= 27007;
const int MSG_GS2C_Completed			= 27008;
const int MSG_GS2C_UpdateActive			= 27009;
const int MSG_C2GS_RequestEnterActive			= 27010;
const int MSG_GS2C_RequestEnterActive			= 27011;
const int MSG_C2GS_OpenActiveUI			= 27012;
const int MSG_C2GS_LevelAward_Req			= 27013;
const int MSG_C2GS_LoginAward_Req			= 27014;


#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_betweenLsPs(stNetMsg& msg);
const int MSG_LS2PS_Register_Request			= 31001;
const int MSG_PS2LS_Register_Ret			= 31002;
const int MSG_PS2LS_PayInfo_Request			= 31003;
const int MSG_LS2PS_PayInfo_Ret			= 31004;

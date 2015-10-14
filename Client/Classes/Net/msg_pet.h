
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_pet(stNetMsg& msg);
const int MSG_GS2C_PET_EXP_UPDATE			= 30001;
const int MSG_C2GS_CALL_PET_Req			= 30002;
const int MSG_GS2C_CALL_PET_Ret			= 30003;
const int MSG_C2GS_CALL_BACK_PET_Req			= 30004;
const int MSG_GS2C_CALL_BACK_PET_Ret			= 30005;
const int MSG_GS2C_PET_MAP_UPDATE			= 30006;
const int MSG_C2GS_PET_STRENG_Req			= 30007;
const int MSG_GS2C_PET_STRENG_Ret			= 30008;
const int MSG_C2GS_PET_FEED_Req			= 30009;
const int MSG_GS2C_PET_FEED_Ret			= 30010;

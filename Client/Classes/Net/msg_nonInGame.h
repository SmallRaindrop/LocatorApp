
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_nonInGame(stNetMsg& msg);
const int MSG_C2GS_Login			= 25001;
const int MSG_GS2C_Login_Ret			= 25003;
const int MSG_C2GS_CreatePlayer			= 25004;
const int MSG_GS2C_CreatePlayer_Ret			= 25005;
const int MSG_C2GS_DeletePlayer			= 25006;
const int MSG_GS2C_DeletePlayer_Ret			= 25007;
const int MSG_C2GS_EnterGame			= 25008;
const int MSG_GS2C_ReturnToSelectRoleDlg_Ret			= 25009;
const int MSG_GS2C_SendPlayerDataComplete			= 25010;
const int MSG_C2GS_EnterMap			= 25011;


#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_betweenClientLs(stNetMsg& msg);
const int MSG_C2LS_Login_Test			= 10001;
const int MSG_LS2C_Login_Ret			= 10002;
const int MSG_C2LS_RequestGameServerList			= 10003;
const int MSG_LS2C_GameServerList_Ret			= 10005;
const int MSG_C2LS_RequestSelGameServer			= 10006;
const int MSG_LS2C_SelGameServer_Ret			= 10007;
const int MSG_C2LS_BackPreStatus			= 10008;

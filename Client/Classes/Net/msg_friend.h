
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_friend(stNetMsg& msg);
const int MSG_GS2C_All_Friend_Info			= 17002;
const int MSG_GS2C_Friend_Info			= 17003;
const int MSG_C2GS_Add_Friend			= 17004;
const int MSG_GS2C_Add_Friend_Result			= 17005;
const int MSG_C2GS_Remove_Friend			= 17006;
const int MSG_GS2C_Remove_Friend_Result			= 17007;
const int MSG_C2GS_Request_Friend_State			= 17008;
const int MSG_GS2C_Request_Friend_State_Result			= 17010;
const int MSG_C2GS_Palyer_Touch_List_Req			= 17011;
const int MSG_GS2C_Palyer_Touch_List_Ret			= 17012;

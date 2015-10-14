
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_mall(stNetMsg& msg);
const int MSG_GS2C_MallInfo			= 26002;
const int MSG_GS2C_MallHot9			= 26003;
const int MSG_GS2C_MallLuckyPrice			= 26004;
const int MSG_C2GS_Common_Buy			= 26005;
const int MSG_GS2C_Common_Buy_Result			= 26006;
const int MSG_C2GS_Lucky_Buy			= 26007;
const int MSG_GS2C_Lucky_Buy_Result			= 26008;
const int MSG_C2GS_Mall_Refresh			= 26009;
const int MSG_GS2C_Mall_Refresh_Result			= 26010;
const int MSG_C2GS_vip_Buy			= 26011;
const int MSG_GS2C_vip_Buy_Result			= 26012;

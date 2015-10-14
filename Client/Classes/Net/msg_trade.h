
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_trade(stNetMsg& msg);
const int MSG_C2GS_RequestTrade			= 21001;
const int MSG_GS2C_RequestTrade			= 21002;
const int MSG_C2GS_ReponseTrade			= 21003;
const int MSG_GS2C_ReponseTrade_Result			= 21004;
const int MSG_GS2C_RequestTrade_Result			= 21005;
const int MSG_C2GS_CannelTrade			= 21006;
const int MSG_GS2C_CannelTrade			= 21007;
const int MSG_C2GS_InputItem			= 21009;
const int MSG_GS2C_InputItem			= 21010;
const int MSG_C2GS_LockTrade			= 21011;
const int MSG_GS2C_LockTrade_Result			= 21012;
const int MSG_C2GS_StartTrade			= 21013;
const int MSG_GS2C_StartTrade			= 21014;
const int MSG_C2GS_NpcShopBuy			= 21015;
const int MSG_GS2C_NpcShopBuy_Result			= 21016;
const int MSG_C2GS_NpcShopSell			= 21017;
const int MSG_GS2C_NpcShopSell_Result			= 21018;
const int MSG_C2GS_PortableShopBuy			= 21019;
const int MSG_GS2C_PortableShopBuy_Result			= 21020;

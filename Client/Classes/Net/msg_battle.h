
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_battle(stNetMsg& msg);
const int MSG_C2GS_SignalEnterBattleMap			= 28001;
const int MSG_GS2C_SignalEnterBattleMap			= 28002;
const int MSG_C2GS_TeamRequestEnterMap			= 28003;
const int MSG_GS2C_TeamRequestEnterMap			= 28004;
const int MSG_GS2C_InviteEnterBattleMap			= 28005;
const int MSG_C2GS_InviteEnterBattleMap			= 28006;
const int MSG_GS2C_InviteerEnterBattleMap			= 28007;
const int MSG_GS2C_InviteEnterBattleMap_Result			= 28008;
const int MSG_GS2C_UpdateBattlePlayerCnt			= 28009;
const int MSG_GS2C_EndBattle			= 28011;
const int MSG_GS2C_UpdateBattleInfo			= 28012;
const int MSG_C2GS_BuyBuff			= 28013;
const int MSG_GS2C_BuyBuff			= 28014;
const int MSG_GS2C_TeamTimeOut			= 28015;
const int MSG_GS2C_Open_Battle_Door			= 28016;
const int MSG_GS2C_OfflineExp			= 28017;
const int MSG_C2GS_PickupOfflineExp			= 28018;
const int MSG_GS2C_RobbedOfflineExpDetailInfo			= 28020;

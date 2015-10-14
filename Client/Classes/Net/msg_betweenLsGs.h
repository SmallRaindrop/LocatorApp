
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_betweenLsGs(stNetMsg& msg);
const int MSG_GS2LS_Register_Request			= 11001;
const int MSG_LS2GS_Register_Ret			= 11002;
const int MSG_LS2GS_GetPlayerInfo_Request			= 11003;
const int MSG_GS2LS_GetPlayerInfo_Ret			= 11004;
const int MSG_LS2GS_UserReadyToLogin			= 11005;
const int MSG_GS2LS_UserLogin			= 11006;
const int MSG_GS2LS_UserLogout			= 11007;
const int MSG_LS2GS_UserKick			= 11008;
const int MSG_LS2GS_PayInfo_Request			= 11009;
const int MSG_GS2LS_PayInfo_Ret			= 11010;
const int MSG_LS2GS_GM_CMD_Request			= 11011;
const int MSG_GS2LS_GM_CMD_Ret			= 11012;
const int MSG_LS2GS_Kick_Player_Off_Request			= 11013;
const int MSG_GS2LS_Kick_Player_Off_Ret			= 11014;
const int MSG_LS2GS_Announcement_Request			= 11015;
const int MSG_GS2LS_Announcement_Ret			= 11016;
const int MSG_LS2GS_control_activity_Request			= 11017;
const int MSG_GS2LS_control_activity_Ret			= 11018;
const int MSG_GS2LS_kickOutUser			= 11019;
const int MSG_GS2LS_upadateOnlinePlayerCnt			= 11020;
const int MSG_LS2GS_Forbid_Chat_Request			= 11021;
const int MSG_GS2LS_Forbid_Chat_Request_Ret			= 11022;
const int MSG_LS2GS_SET_GM_Request			= 11023;
const int MSG_GS2LS_SET_GM_Request_Ret			= 11024;

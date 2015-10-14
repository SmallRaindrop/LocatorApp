#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_betweenLsGs(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2LS_Register_Request);
 		CMD_DEAL(LS2GS_Register_Ret);
 		CMD_DEAL(LS2GS_GetPlayerInfo_Request);
 		CMD_DEAL(GS2LS_GetPlayerInfo_Ret);
 		CMD_DEAL(LS2GS_UserReadyToLogin);
 		CMD_DEAL(GS2LS_UserLogin);
 		CMD_DEAL(GS2LS_UserLogout);
 		CMD_DEAL(LS2GS_UserKick);
 		CMD_DEAL(LS2GS_PayInfo_Request);
 		CMD_DEAL(GS2LS_PayInfo_Ret);
 		CMD_DEAL(LS2GS_GM_CMD_Request);
 		CMD_DEAL(GS2LS_GM_CMD_Ret);
 		CMD_DEAL(LS2GS_Kick_Player_Off_Request);
 		CMD_DEAL(GS2LS_Kick_Player_Off_Ret);
 		CMD_DEAL(LS2GS_Announcement_Request);
 		CMD_DEAL(GS2LS_Announcement_Ret);
 		CMD_DEAL(LS2GS_control_activity_Request);
 		CMD_DEAL(GS2LS_control_activity_Ret);
 		CMD_DEAL(GS2LS_kickOutUser);
 		CMD_DEAL(GS2LS_upadateOnlinePlayerCnt);
 		CMD_DEAL(LS2GS_Forbid_Chat_Request);
 		CMD_DEAL(GS2LS_Forbid_Chat_Request_Ret);
 		CMD_DEAL(LS2GS_SET_GM_Request);
 		CMD_DEAL(GS2LS_SET_GM_Request_Ret);
 	END_DEAL();
	return false;
}

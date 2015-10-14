#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_team(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_TeamInvite_Msg);
 		CMD_DEAL(GS2C_JoinTeam_Req);
 		CMD_DEAL(GS2C_TeamInfo);
 		CMD_DEAL(GS2C_AddTeamMember);
 		CMD_DEAL(GS2C_RemoveTeamMember);
 		CMD_DEAL(GS2C_RemoveTeam);
 		CMD_DEAL(GS2C_ChangePermitAllMemberCanInvite);
 		CMD_DEAL(GS2C_ChangeTeamSet_Ret);
 		CMD_DEAL(GS2C_GetOldTeamer_Ret);
 		CMD_DEAL(GS2C_TeamMemberState);
 	END_DEAL();
	return false;
}

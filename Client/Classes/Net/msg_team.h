
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_team(stNetMsg& msg);
const int MSG_C2GS_CreateTeam_Req			= 19001;
const int MSG_C2GS_InviteTeam_Req			= 19002;
const int MSG_GS2C_TeamInvite_Msg			= 19003;
const int MSG_GS2C_JoinTeam_Req			= 19004;
const int MSG_C2GS_AcceptOrRefuseTeamInvite			= 19005;
const int MSG_C2GS_ApproveOrRefuseJoinTeam			= 19006;
const int MSG_GS2C_TeamInfo			= 19008;
const int MSG_GS2C_AddTeamMember			= 19009;
const int MSG_GS2C_RemoveTeamMember			= 19010;
const int MSG_C2GS_ExitTeam_Req			= 19011;
const int MSG_GS2C_RemoveTeam			= 19012;
const int MSG_C2GS_ChangePermitAllMemberCanInvite_Req			= 19013;
const int MSG_GS2C_ChangePermitAllMemberCanInvite			= 19014;
const int MSG_GS2C_ChangeTeamSet_Ret			= 19015;
const int MSG_C2GS_TeamKickOutPlayer			= 19016;
const int MSG_C2GS_GetOldTeamer_Req			= 19018;
const int MSG_GS2C_GetOldTeamer_Ret			= 19019;
const int MSG_GS2C_TeamMemberState			= 19020;

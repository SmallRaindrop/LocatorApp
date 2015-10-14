#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteC2GS_CreateTeam_Req(stNetMsg& msg,C2GS_CreateTeam_Req& value)
{
	msg << value.teamMemberMaxCount;
	msg.command(MSG_C2GS_CreateTeam_Req);
}
void C2GS_CreateTeam_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_CreateTeam_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_CreateTeam_Req(stNetMsg& msg,C2GS_CreateTeam_Req& value)
{
	msg >> value.teamMemberMaxCount;
}
void WriteC2GS_InviteTeam_Req(stNetMsg& msg,C2GS_InviteTeam_Req& value)
{
	msg << value.inviteeId;
	msg.command(MSG_C2GS_InviteTeam_Req);
}
void C2GS_InviteTeam_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_InviteTeam_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_InviteTeam_Req(stNetMsg& msg,C2GS_InviteTeam_Req& value)
{
	msg >> value.inviteeId;
}
void WriteGS2C_TeamInvite_Msg(stNetMsg& msg,GS2C_TeamInvite_Msg& value)
{
	msg << value.inviterId;
	msg << value.inviterName;
	msg << value.inviterLevel;
	msg << value.inviterCareer;
	msg.command(MSG_GS2C_TeamInvite_Msg);
}
void ReadGS2C_TeamInvite_Msg(stNetMsg& msg,GS2C_TeamInvite_Msg& value)
{
	msg >> value.inviterId;
	msg >> value.inviterName;
	msg >> value.inviterLevel;
	msg >> value.inviterCareer;
}
void WriteGS2C_JoinTeam_Req(stNetMsg& msg,GS2C_JoinTeam_Req& value)
{
	msg << value.inviterId;
	msg << value.inviterName;
	msg << value.inviterLevel;
	msg << value.inviterCareer;
	msg.command(MSG_GS2C_JoinTeam_Req);
}
void ReadGS2C_JoinTeam_Req(stNetMsg& msg,GS2C_JoinTeam_Req& value)
{
	msg >> value.inviterId;
	msg >> value.inviterName;
	msg >> value.inviterLevel;
	msg >> value.inviterCareer;
}
void WriteC2GS_AcceptOrRefuseTeamInvite(stNetMsg& msg,C2GS_AcceptOrRefuseTeamInvite& value)
{
	msg << value.inviterId;
	msg << value.isAccept;
	msg.command(MSG_C2GS_AcceptOrRefuseTeamInvite);
}
void C2GS_AcceptOrRefuseTeamInvite::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_AcceptOrRefuseTeamInvite(msg_s,*this);
	EndSend();
}
void ReadC2GS_AcceptOrRefuseTeamInvite(stNetMsg& msg,C2GS_AcceptOrRefuseTeamInvite& value)
{
	msg >> value.inviterId;
	msg >> value.isAccept;
}
void WriteC2GS_ApproveOrRefuseJoinTeam(stNetMsg& msg,C2GS_ApproveOrRefuseJoinTeam& value)
{
	msg << value.inviterId;
	msg << value.isApprove;
	msg.command(MSG_C2GS_ApproveOrRefuseJoinTeam);
}
void C2GS_ApproveOrRefuseJoinTeam::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ApproveOrRefuseJoinTeam(msg_s,*this);
	EndSend();
}
void ReadC2GS_ApproveOrRefuseJoinTeam(stNetMsg& msg,C2GS_ApproveOrRefuseJoinTeam& value)
{
	msg >> value.inviterId;
	msg >> value.isApprove;
}
void WriteTeamMemberInfo(stNetMsg& msg,TeamMemberInfo& value)
{
	msg << value.id;
	msg << value.name;
	msg << value.level;
	msg << value.career;
	msg << value.sex;
	msg << value.hp;
	msg << value.maxhp;
}
void ReadTeamMemberInfo(stNetMsg& msg,TeamMemberInfo& value)
{
	msg >> value.id;
	msg >> value.name;
	msg >> value.level;
	msg >> value.career;
	msg >> value.sex;
	msg >> value.hp;
	msg >> value.maxhp;
}
void WriteGS2C_TeamInfo(stNetMsg& msg,GS2C_TeamInfo& value)
{
	msg << value.teamId;
	msg << value.leadId;
	msg << value.isPermitNum;
	WriteArray(msg,TeamMemberInfo,value.member_list);
	msg.command(MSG_GS2C_TeamInfo);
}
void ReadGS2C_TeamInfo(stNetMsg& msg,GS2C_TeamInfo& value)
{
	msg >> value.teamId;
	msg >> value.leadId;
	msg >> value.isPermitNum;
	ReadArray(msg,TeamMemberInfo,value.member_list);
}
void WriteGS2C_AddTeamMember(stNetMsg& msg,GS2C_AddTeamMember& value)
{
	WriteTeamMemberInfo(msg, value.member);
	msg.command(MSG_GS2C_AddTeamMember);
}
void ReadGS2C_AddTeamMember(stNetMsg& msg,GS2C_AddTeamMember& value)
{
	ReadTeamMemberInfo(msg, value.member);
}
void WriteGS2C_RemoveTeamMember(stNetMsg& msg,GS2C_RemoveTeamMember& value)
{
	msg << value.memberId;
	msg << value.leadId;
	msg << value.reason;
	msg.command(MSG_GS2C_RemoveTeamMember);
}
void ReadGS2C_RemoveTeamMember(stNetMsg& msg,GS2C_RemoveTeamMember& value)
{
	msg >> value.memberId;
	msg >> value.leadId;
	msg >> value.reason;
}
void WriteC2GS_ExitTeam_Req(stNetMsg& msg,C2GS_ExitTeam_Req& value)
{
	msg << value.teamId;
	msg.command(MSG_C2GS_ExitTeam_Req);
}
void C2GS_ExitTeam_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ExitTeam_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_ExitTeam_Req(stNetMsg& msg,C2GS_ExitTeam_Req& value)
{
	msg >> value.teamId;
}
void WriteGS2C_RemoveTeam(stNetMsg& msg,GS2C_RemoveTeam& value)
{
	msg << value.teamId;
	msg.command(MSG_GS2C_RemoveTeam);
}
void ReadGS2C_RemoveTeam(stNetMsg& msg,GS2C_RemoveTeam& value)
{
	msg >> value.teamId;
}
void WriteC2GS_ChangePermitAllMemberCanInvite_Req(stNetMsg& msg,C2GS_ChangePermitAllMemberCanInvite_Req& value)
{
	msg << value.isPermitNum;
	msg.command(MSG_C2GS_ChangePermitAllMemberCanInvite_Req);
}
void C2GS_ChangePermitAllMemberCanInvite_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ChangePermitAllMemberCanInvite_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_ChangePermitAllMemberCanInvite_Req(stNetMsg& msg,C2GS_ChangePermitAllMemberCanInvite_Req& value)
{
	msg >> value.isPermitNum;
}
void WriteGS2C_ChangePermitAllMemberCanInvite(stNetMsg& msg,GS2C_ChangePermitAllMemberCanInvite& value)
{
	msg << value.teamId;
	msg << value.isPermitNum;
	msg.command(MSG_GS2C_ChangePermitAllMemberCanInvite);
}
void ReadGS2C_ChangePermitAllMemberCanInvite(stNetMsg& msg,GS2C_ChangePermitAllMemberCanInvite& value)
{
	msg >> value.teamId;
	msg >> value.isPermitNum;
}
void WriteGS2C_ChangeTeamSet_Ret(stNetMsg& msg,GS2C_ChangeTeamSet_Ret& value)
{
	msg << value.teamSet;
	msg.command(MSG_GS2C_ChangeTeamSet_Ret);
}
void ReadGS2C_ChangeTeamSet_Ret(stNetMsg& msg,GS2C_ChangeTeamSet_Ret& value)
{
	msg >> value.teamSet;
}
void WriteC2GS_TeamKickOutPlayer(stNetMsg& msg,C2GS_TeamKickOutPlayer& value)
{
	msg << value.playerId;
	msg.command(MSG_C2GS_TeamKickOutPlayer);
}
void C2GS_TeamKickOutPlayer::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_TeamKickOutPlayer(msg_s,*this);
	EndSend();
}
void ReadC2GS_TeamKickOutPlayer(stNetMsg& msg,C2GS_TeamKickOutPlayer& value)
{
	msg >> value.playerId;
}
void WriteOldTeamerInfo(stNetMsg& msg,OldTeamerInfo& value)
{
	msg << value.id;
	msg << value.name;
	msg << value.level;
	msg << value.career;
	msg << value.sex;
}
void ReadOldTeamerInfo(stNetMsg& msg,OldTeamerInfo& value)
{
	msg >> value.id;
	msg >> value.name;
	msg >> value.level;
	msg >> value.career;
	msg >> value.sex;
}
void WriteC2GS_GetOldTeamer_Req(stNetMsg& msg,C2GS_GetOldTeamer_Req& value)
{
	msg.command(MSG_C2GS_GetOldTeamer_Req);
}
void C2GS_GetOldTeamer_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_GetOldTeamer_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_GetOldTeamer_Req(stNetMsg& msg,C2GS_GetOldTeamer_Req& value)
{
}
void WriteGS2C_GetOldTeamer_Ret(stNetMsg& msg,GS2C_GetOldTeamer_Ret& value)
{
	WriteArray(msg,OldTeamerInfo,value.teamerList);
	msg.command(MSG_GS2C_GetOldTeamer_Ret);
}
void ReadGS2C_GetOldTeamer_Ret(stNetMsg& msg,GS2C_GetOldTeamer_Ret& value)
{
	ReadArray(msg,OldTeamerInfo,value.teamerList);
}
void WriteGS2C_TeamMemberState(stNetMsg& msg,GS2C_TeamMemberState& value)
{
	msg << value.playerId;
	msg << value.online;
	msg << value.hp;
	msg << value.maxHp;
	msg.command(MSG_GS2C_TeamMemberState);
}
void ReadGS2C_TeamMemberState(stNetMsg& msg,GS2C_TeamMemberState& value)
{
	msg >> value.playerId;
	msg >> value.online;
	msg >> value.hp;
	msg >> value.maxHp;
}

};


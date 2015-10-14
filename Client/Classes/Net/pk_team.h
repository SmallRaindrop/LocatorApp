
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct C2GS_CreateTeam_Req
{
	int8 teamMemberMaxCount;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_CreateTeam_Req(stNetMsg& msg,C2GS_CreateTeam_Req& value);
void ReadC2GS_CreateTeam_Req(stNetMsg& msg,C2GS_CreateTeam_Req& value);

struct C2GS_InviteTeam_Req
{
	int64 inviteeId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_InviteTeam_Req(stNetMsg& msg,C2GS_InviteTeam_Req& value);
void ReadC2GS_InviteTeam_Req(stNetMsg& msg,C2GS_InviteTeam_Req& value);

struct GS2C_TeamInvite_Msg
{
	int64 inviterId;
	string inviterName;
	int16 inviterLevel;
	int8 inviterCareer;
};
void WriteGS2C_TeamInvite_Msg(stNetMsg& msg,GS2C_TeamInvite_Msg& value);
bool OnGS2C_TeamInvite_Msg(GS2C_TeamInvite_Msg* value);
void ReadGS2C_TeamInvite_Msg(stNetMsg& msg,GS2C_TeamInvite_Msg& value);

struct GS2C_JoinTeam_Req
{
	int64 inviterId;
	string inviterName;
	int16 inviterLevel;
	int8 inviterCareer;
};
void WriteGS2C_JoinTeam_Req(stNetMsg& msg,GS2C_JoinTeam_Req& value);
bool OnGS2C_JoinTeam_Req(GS2C_JoinTeam_Req* value);
void ReadGS2C_JoinTeam_Req(stNetMsg& msg,GS2C_JoinTeam_Req& value);

struct C2GS_AcceptOrRefuseTeamInvite
{
	int64 inviterId;
	int8 isAccept;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_AcceptOrRefuseTeamInvite(stNetMsg& msg,C2GS_AcceptOrRefuseTeamInvite& value);
void ReadC2GS_AcceptOrRefuseTeamInvite(stNetMsg& msg,C2GS_AcceptOrRefuseTeamInvite& value);

struct C2GS_ApproveOrRefuseJoinTeam
{
	int64 inviterId;
	int8 isApprove;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ApproveOrRefuseJoinTeam(stNetMsg& msg,C2GS_ApproveOrRefuseJoinTeam& value);
void ReadC2GS_ApproveOrRefuseJoinTeam(stNetMsg& msg,C2GS_ApproveOrRefuseJoinTeam& value);

struct TeamMemberInfo
{
	int64 id;
	string name;
	int16 level;
	int8 career;
	int8 sex;
	int32 hp;
	int32 maxhp;
};
void WriteTeamMemberInfo(stNetMsg& msg,TeamMemberInfo& value);
void ReadTeamMemberInfo(stNetMsg& msg,TeamMemberInfo& value);

struct GS2C_TeamInfo
{
	int64 teamId;
	int64 leadId;
	int8 isPermitNum;
	vector<TeamMemberInfo> member_list;
};
void WriteGS2C_TeamInfo(stNetMsg& msg,GS2C_TeamInfo& value);
bool OnGS2C_TeamInfo(GS2C_TeamInfo* value);
void ReadGS2C_TeamInfo(stNetMsg& msg,GS2C_TeamInfo& value);

struct GS2C_AddTeamMember
{
	TeamMemberInfo member;
};
void WriteGS2C_AddTeamMember(stNetMsg& msg,GS2C_AddTeamMember& value);
bool OnGS2C_AddTeamMember(GS2C_AddTeamMember* value);
void ReadGS2C_AddTeamMember(stNetMsg& msg,GS2C_AddTeamMember& value);

struct GS2C_RemoveTeamMember
{
	int64 memberId;
	int64 leadId;
	int8 reason;
};
void WriteGS2C_RemoveTeamMember(stNetMsg& msg,GS2C_RemoveTeamMember& value);
bool OnGS2C_RemoveTeamMember(GS2C_RemoveTeamMember* value);
void ReadGS2C_RemoveTeamMember(stNetMsg& msg,GS2C_RemoveTeamMember& value);

struct C2GS_ExitTeam_Req
{
	int64 teamId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ExitTeam_Req(stNetMsg& msg,C2GS_ExitTeam_Req& value);
void ReadC2GS_ExitTeam_Req(stNetMsg& msg,C2GS_ExitTeam_Req& value);

struct GS2C_RemoveTeam
{
	int64 teamId;
};
void WriteGS2C_RemoveTeam(stNetMsg& msg,GS2C_RemoveTeam& value);
bool OnGS2C_RemoveTeam(GS2C_RemoveTeam* value);
void ReadGS2C_RemoveTeam(stNetMsg& msg,GS2C_RemoveTeam& value);

struct C2GS_ChangePermitAllMemberCanInvite_Req
{
	int8 isPermitNum;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ChangePermitAllMemberCanInvite_Req(stNetMsg& msg,C2GS_ChangePermitAllMemberCanInvite_Req& value);
void ReadC2GS_ChangePermitAllMemberCanInvite_Req(stNetMsg& msg,C2GS_ChangePermitAllMemberCanInvite_Req& value);

struct GS2C_ChangePermitAllMemberCanInvite
{
	int64 teamId;
	int8 isPermitNum;
};
void WriteGS2C_ChangePermitAllMemberCanInvite(stNetMsg& msg,GS2C_ChangePermitAllMemberCanInvite& value);
bool OnGS2C_ChangePermitAllMemberCanInvite(GS2C_ChangePermitAllMemberCanInvite* value);
void ReadGS2C_ChangePermitAllMemberCanInvite(stNetMsg& msg,GS2C_ChangePermitAllMemberCanInvite& value);

struct GS2C_ChangeTeamSet_Ret
{
	int8 teamSet;
};
void WriteGS2C_ChangeTeamSet_Ret(stNetMsg& msg,GS2C_ChangeTeamSet_Ret& value);
bool OnGS2C_ChangeTeamSet_Ret(GS2C_ChangeTeamSet_Ret* value);
void ReadGS2C_ChangeTeamSet_Ret(stNetMsg& msg,GS2C_ChangeTeamSet_Ret& value);

struct C2GS_TeamKickOutPlayer
{
	int64 playerId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_TeamKickOutPlayer(stNetMsg& msg,C2GS_TeamKickOutPlayer& value);
void ReadC2GS_TeamKickOutPlayer(stNetMsg& msg,C2GS_TeamKickOutPlayer& value);

struct OldTeamerInfo
{
	int64 id;
	string name;
	int16 level;
	int8 career;
	int8 sex;
};
void WriteOldTeamerInfo(stNetMsg& msg,OldTeamerInfo& value);
void ReadOldTeamerInfo(stNetMsg& msg,OldTeamerInfo& value);

struct C2GS_GetOldTeamer_Req
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_GetOldTeamer_Req(stNetMsg& msg,C2GS_GetOldTeamer_Req& value);
void ReadC2GS_GetOldTeamer_Req(stNetMsg& msg,C2GS_GetOldTeamer_Req& value);

struct GS2C_GetOldTeamer_Ret
{
	vector<OldTeamerInfo> teamerList;
};
void WriteGS2C_GetOldTeamer_Ret(stNetMsg& msg,GS2C_GetOldTeamer_Ret& value);
bool OnGS2C_GetOldTeamer_Ret(GS2C_GetOldTeamer_Ret* value);
void ReadGS2C_GetOldTeamer_Ret(stNetMsg& msg,GS2C_GetOldTeamer_Ret& value);

struct GS2C_TeamMemberState
{
	int64 playerId;
	int8 online;
	int32 hp;
	int32 maxHp;
};
void WriteGS2C_TeamMemberState(stNetMsg& msg,GS2C_TeamMemberState& value);
bool OnGS2C_TeamMemberState(GS2C_TeamMemberState* value);
void ReadGS2C_TeamMemberState(stNetMsg& msg,GS2C_TeamMemberState& value);


};


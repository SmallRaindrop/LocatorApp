
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct guildList
{
	int64 guildId;
	string guildName;
	int16 guildLevel;
	string guildLeaderName;
	int32 curMementCnt;
	int32 maxMementCnt;
	int32 guildProsperity;
	string guildDeclaration;
};
void WriteguildList(stNetMsg& msg,guildList& value);
void ReadguildList(stNetMsg& msg,guildList& value);

struct C2GS_LookOverGuildInfo
{
	int64 playerId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_LookOverGuildInfo(stNetMsg& msg,C2GS_LookOverGuildInfo& value);
void ReadC2GS_LookOverGuildInfo(stNetMsg& msg,C2GS_LookOverGuildInfo& value);

struct GS2C_GuildList
{
	vector<guildList> vec;
};
void WriteGS2C_GuildList(stNetMsg& msg,GS2C_GuildList& value);
bool OnGS2C_GuildList(GS2C_GuildList* value);
void ReadGS2C_GuildList(stNetMsg& msg,GS2C_GuildList& value);

struct memberList
{
	int64 playerId;
	string memberName;
	int8 position;
	int32 level;
	int32 contribution;
	int8 isVip;
	int8 career;
	int8 isOnline;
};
void WritememberList(stNetMsg& msg,memberList& value);
void ReadmemberList(stNetMsg& msg,memberList& value);

struct guildSkill
{
	int32 skillType;
	int32 skillLevel;
};
void WriteguildSkill(stNetMsg& msg,guildSkill& value);
void ReadguildSkill(stNetMsg& msg,guildSkill& value);

struct GS2C_MemberList
{
	int64 guildId;
	string guildAnnouncement;
	vector<guildSkill> skillVec;
	vector<memberList> vec;
};
void WriteGS2C_MemberList(stNetMsg& msg,GS2C_MemberList& value);
bool OnGS2C_MemberList(GS2C_MemberList* value);
void ReadGS2C_MemberList(stNetMsg& msg,GS2C_MemberList& value);

struct applyList
{
	int64 playerId;
	string name;
	int32 level;
	int8 career;
	int8 isVip;
};
void WriteapplyList(stNetMsg& msg,applyList& value);
void ReadapplyList(stNetMsg& msg,applyList& value);

struct GS2C_ApplyList
{
	vector<applyList> vec;
};
void WriteGS2C_ApplyList(stNetMsg& msg,GS2C_ApplyList& value);
bool OnGS2C_ApplyList(GS2C_ApplyList* value);
void ReadGS2C_ApplyList(stNetMsg& msg,GS2C_ApplyList& value);

struct C2GS_CreateGuild
{
	string guildName;
	string guildDeclaration;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_CreateGuild(stNetMsg& msg,C2GS_CreateGuild& value);
void ReadC2GS_CreateGuild(stNetMsg& msg,C2GS_CreateGuild& value);

struct GS2C_CreateGuild_Result
{
	int8 retCode;
	guildList st;
};
void WriteGS2C_CreateGuild_Result(stNetMsg& msg,GS2C_CreateGuild_Result& value);
bool OnGS2C_CreateGuild_Result(GS2C_CreateGuild_Result* value);
void ReadGS2C_CreateGuild_Result(stNetMsg& msg,GS2C_CreateGuild_Result& value);

struct GS2C_CreateGuild
{
	guildList st;
};
void WriteGS2C_CreateGuild(stNetMsg& msg,GS2C_CreateGuild& value);
bool OnGS2C_CreateGuild(GS2C_CreateGuild* value);
void ReadGS2C_CreateGuild(stNetMsg& msg,GS2C_CreateGuild& value);

struct C2GS_RequestJoinGuild
{
	int64 guildId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_RequestJoinGuild(stNetMsg& msg,C2GS_RequestJoinGuild& value);
void ReadC2GS_RequestJoinGuild(stNetMsg& msg,C2GS_RequestJoinGuild& value);

struct GS2C_RequestJoinGuild
{
	applyList st;
};
void WriteGS2C_RequestJoinGuild(stNetMsg& msg,GS2C_RequestJoinGuild& value);
bool OnGS2C_RequestJoinGuild(GS2C_RequestJoinGuild* value);
void ReadGS2C_RequestJoinGuild(stNetMsg& msg,GS2C_RequestJoinGuild& value);

struct C2GS_ApproveRequestJoinGuild
{
	int8 respon;
	int64 requestPlayerId;
	int64 guildId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ApproveRequestJoinGuild(stNetMsg& msg,C2GS_ApproveRequestJoinGuild& value);
void ReadC2GS_ApproveRequestJoinGuild(stNetMsg& msg,C2GS_ApproveRequestJoinGuild& value);

struct GS2C_JoinGuild_Result
{
	memberList st;
};
void WriteGS2C_JoinGuild_Result(stNetMsg& msg,GS2C_JoinGuild_Result& value);
bool OnGS2C_JoinGuild_Result(GS2C_JoinGuild_Result* value);
void ReadGS2C_JoinGuild_Result(stNetMsg& msg,GS2C_JoinGuild_Result& value);

struct C2GS_UpgradeGuild
{
	int64 guildId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_UpgradeGuild(stNetMsg& msg,C2GS_UpgradeGuild& value);
void ReadC2GS_UpgradeGuild(stNetMsg& msg,C2GS_UpgradeGuild& value);

struct GS2C_UpgradeGuild_Result
{
	int8 retCode;
	int16 newLevel;
};
void WriteGS2C_UpgradeGuild_Result(stNetMsg& msg,GS2C_UpgradeGuild_Result& value);
bool OnGS2C_UpgradeGuild_Result(GS2C_UpgradeGuild_Result* value);
void ReadGS2C_UpgradeGuild_Result(stNetMsg& msg,GS2C_UpgradeGuild_Result& value);

struct GS2C_UpgradeGuild
{
	int16 level;
	int32 maxMementCnt;
	int32 guildProsperity;
};
void WriteGS2C_UpgradeGuild(stNetMsg& msg,GS2C_UpgradeGuild& value);
bool OnGS2C_UpgradeGuild(GS2C_UpgradeGuild* value);
void ReadGS2C_UpgradeGuild(stNetMsg& msg,GS2C_UpgradeGuild& value);

struct C2GS_ExitGuild
{
	int64 guildId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ExitGuild(stNetMsg& msg,C2GS_ExitGuild& value);
void ReadC2GS_ExitGuild(stNetMsg& msg,C2GS_ExitGuild& value);

struct GS2C_ExitGuild_Result
{
	int64 memberId;
};
void WriteGS2C_ExitGuild_Result(stNetMsg& msg,GS2C_ExitGuild_Result& value);
bool OnGS2C_ExitGuild_Result(GS2C_ExitGuild_Result* value);
void ReadGS2C_ExitGuild_Result(stNetMsg& msg,GS2C_ExitGuild_Result& value);

struct C2GS_KillOutPlayer
{
	int64 memberId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_KillOutPlayer(stNetMsg& msg,C2GS_KillOutPlayer& value);
void ReadC2GS_KillOutPlayer(stNetMsg& msg,C2GS_KillOutPlayer& value);

struct GS2C_KillOutPlayer_Result
{
	int64 memberId;
};
void WriteGS2C_KillOutPlayer_Result(stNetMsg& msg,GS2C_KillOutPlayer_Result& value);
bool OnGS2C_KillOutPlayer_Result(GS2C_KillOutPlayer_Result* value);
void ReadGS2C_KillOutPlayer_Result(stNetMsg& msg,GS2C_KillOutPlayer_Result& value);

struct C2GS_TransferLeader
{
	int64 memberId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_TransferLeader(stNetMsg& msg,C2GS_TransferLeader& value);
void ReadC2GS_TransferLeader(stNetMsg& msg,C2GS_TransferLeader& value);

struct GS2C_TransferLeader_Result
{
	int64 newLeader;
};
void WriteGS2C_TransferLeader_Result(stNetMsg& msg,GS2C_TransferLeader_Result& value);
bool OnGS2C_TransferLeader_Result(GS2C_TransferLeader_Result* value);
void ReadGS2C_TransferLeader_Result(stNetMsg& msg,GS2C_TransferLeader_Result& value);

struct C2GS_SetDeputyLeader
{
	int64 memberId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SetDeputyLeader(stNetMsg& msg,C2GS_SetDeputyLeader& value);
void ReadC2GS_SetDeputyLeader(stNetMsg& msg,C2GS_SetDeputyLeader& value);

struct GS2C_SetDeputyLeader_Result
{
	int64 memberId;
};
void WriteGS2C_SetDeputyLeader_Result(stNetMsg& msg,GS2C_SetDeputyLeader_Result& value);
bool OnGS2C_SetDeputyLeader_Result(GS2C_SetDeputyLeader_Result* value);
void ReadGS2C_SetDeputyLeader_Result(stNetMsg& msg,GS2C_SetDeputyLeader_Result& value);

struct C2GS_RemoveDeputyLeader
{
	int64 memberId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_RemoveDeputyLeader(stNetMsg& msg,C2GS_RemoveDeputyLeader& value);
void ReadC2GS_RemoveDeputyLeader(stNetMsg& msg,C2GS_RemoveDeputyLeader& value);

struct GS2C_RemoveDeputyLeader_Result
{
	int64 memberId;
};
void WriteGS2C_RemoveDeputyLeader_Result(stNetMsg& msg,GS2C_RemoveDeputyLeader_Result& value);
bool OnGS2C_RemoveDeputyLeader_Result(GS2C_RemoveDeputyLeader_Result* value);
void ReadGS2C_RemoveDeputyLeader_Result(stNetMsg& msg,GS2C_RemoveDeputyLeader_Result& value);

struct C2GS_UpdateAnnouncement
{
	string announcemnet;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_UpdateAnnouncement(stNetMsg& msg,C2GS_UpdateAnnouncement& value);
void ReadC2GS_UpdateAnnouncement(stNetMsg& msg,C2GS_UpdateAnnouncement& value);

struct GS2C_UpdateAnnouncement_Result
{
	string announcemnet;
};
void WriteGS2C_UpdateAnnouncement_Result(stNetMsg& msg,GS2C_UpdateAnnouncement_Result& value);
bool OnGS2C_UpdateAnnouncement_Result(GS2C_UpdateAnnouncement_Result* value);
void ReadGS2C_UpdateAnnouncement_Result(stNetMsg& msg,GS2C_UpdateAnnouncement_Result& value);

struct C2GS_GuildDonation
{
	int32 money;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_GuildDonation(stNetMsg& msg,C2GS_GuildDonation& value);
void ReadC2GS_GuildDonation(stNetMsg& msg,C2GS_GuildDonation& value);

struct GS2C_GuildDonation_Result
{
	int32 contribution;
	int32 guildProsperity;
	int64 memberId;
};
void WriteGS2C_GuildDonation_Result(stNetMsg& msg,GS2C_GuildDonation_Result& value);
bool OnGS2C_GuildDonation_Result(GS2C_GuildDonation_Result* value);
void ReadGS2C_GuildDonation_Result(stNetMsg& msg,GS2C_GuildDonation_Result& value);

struct GS2C_UpdateGuildProsperity
{
	int32 contribution;
	int64 memberId;
};
void WriteGS2C_UpdateGuildProsperity(stNetMsg& msg,GS2C_UpdateGuildProsperity& value);
bool OnGS2C_UpdateGuildProsperity(GS2C_UpdateGuildProsperity* value);
void ReadGS2C_UpdateGuildProsperity(stNetMsg& msg,GS2C_UpdateGuildProsperity& value);

struct GS2C_UpgradeSkill
{
	int32 guildProsperity;
	int32 skillType;
	int32 skillLevel;
};
void WriteGS2C_UpgradeSkill(stNetMsg& msg,GS2C_UpgradeSkill& value);
bool OnGS2C_UpgradeSkill(GS2C_UpgradeSkill* value);
void ReadGS2C_UpgradeSkill(stNetMsg& msg,GS2C_UpgradeSkill& value);

struct C2GS_DissolveGuild
{
	int64 guildId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_DissolveGuild(stNetMsg& msg,C2GS_DissolveGuild& value);
void ReadC2GS_DissolveGuild(stNetMsg& msg,C2GS_DissolveGuild& value);

struct GS2C_DissolveGuild_Result
{
	int8 retCode;
};
void WriteGS2C_DissolveGuild_Result(stNetMsg& msg,GS2C_DissolveGuild_Result& value);
bool OnGS2C_DissolveGuild_Result(GS2C_DissolveGuild_Result* value);
void ReadGS2C_DissolveGuild_Result(stNetMsg& msg,GS2C_DissolveGuild_Result& value);

struct C2GS_StudyGuildSkill
{
	int32 skillId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_StudyGuildSkill(stNetMsg& msg,C2GS_StudyGuildSkill& value);
void ReadC2GS_StudyGuildSkill(stNetMsg& msg,C2GS_StudyGuildSkill& value);

struct C2GS_UpgradeGuildSkill
{
	int32 skillId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_UpgradeGuildSkill(stNetMsg& msg,C2GS_UpgradeGuildSkill& value);
void ReadC2GS_UpgradeGuildSkill(stNetMsg& msg,C2GS_UpgradeGuildSkill& value);

struct C2GS_RequestGuildWar
{
	int64 guildId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_RequestGuildWar(stNetMsg& msg,C2GS_RequestGuildWar& value);
void ReadC2GS_RequestGuildWar(stNetMsg& msg,C2GS_RequestGuildWar& value);

struct GS2C_GuildWar
{
	int8 retCode;
	int8 isAttack;
	int64 guildId;
};
void WriteGS2C_GuildWar(stNetMsg& msg,GS2C_GuildWar& value);
bool OnGS2C_GuildWar(GS2C_GuildWar* value);
void ReadGS2C_GuildWar(stNetMsg& msg,GS2C_GuildWar& value);


};


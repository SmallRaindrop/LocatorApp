
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_guild(stNetMsg& msg);
const int MSG_C2GS_LookOverGuildInfo			= 22002;
const int MSG_GS2C_GuildList			= 22003;
const int MSG_GS2C_MemberList			= 22006;
const int MSG_GS2C_ApplyList			= 22008;
const int MSG_C2GS_CreateGuild			= 22009;
const int MSG_GS2C_CreateGuild_Result			= 22010;
const int MSG_GS2C_CreateGuild			= 22011;
const int MSG_C2GS_RequestJoinGuild			= 22012;
const int MSG_GS2C_RequestJoinGuild			= 22013;
const int MSG_C2GS_ApproveRequestJoinGuild			= 22014;
const int MSG_GS2C_JoinGuild_Result			= 22015;
const int MSG_C2GS_UpgradeGuild			= 22016;
const int MSG_GS2C_UpgradeGuild_Result			= 22017;
const int MSG_GS2C_UpgradeGuild			= 22018;
const int MSG_C2GS_ExitGuild			= 22019;
const int MSG_GS2C_ExitGuild_Result			= 22020;
const int MSG_C2GS_KillOutPlayer			= 22021;
const int MSG_GS2C_KillOutPlayer_Result			= 22022;
const int MSG_C2GS_TransferLeader			= 22023;
const int MSG_GS2C_TransferLeader_Result			= 22024;
const int MSG_C2GS_SetDeputyLeader			= 22025;
const int MSG_GS2C_SetDeputyLeader_Result			= 22026;
const int MSG_C2GS_RemoveDeputyLeader			= 22027;
const int MSG_GS2C_RemoveDeputyLeader_Result			= 22028;
const int MSG_C2GS_UpdateAnnouncement			= 22029;
const int MSG_GS2C_UpdateAnnouncement_Result			= 22030;
const int MSG_C2GS_GuildDonation			= 22031;
const int MSG_GS2C_GuildDonation_Result			= 22032;
const int MSG_GS2C_UpdateGuildProsperity			= 22033;
const int MSG_GS2C_UpgradeSkill			= 22034;
const int MSG_C2GS_DissolveGuild			= 22035;
const int MSG_GS2C_DissolveGuild_Result			= 22036;
const int MSG_C2GS_StudyGuildSkill			= 22037;
const int MSG_C2GS_UpgradeGuildSkill			= 22038;
const int MSG_C2GS_RequestGuildWar			= 22039;
const int MSG_GS2C_GuildWar			= 22040;

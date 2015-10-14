#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_guild(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_GuildList);
 		CMD_DEAL(GS2C_MemberList);
 		CMD_DEAL(GS2C_ApplyList);
 		CMD_DEAL(GS2C_CreateGuild_Result);
 		CMD_DEAL(GS2C_CreateGuild);
 		CMD_DEAL(GS2C_RequestJoinGuild);
 		CMD_DEAL(GS2C_JoinGuild_Result);
 		CMD_DEAL(GS2C_UpgradeGuild_Result);
 		CMD_DEAL(GS2C_UpgradeGuild);
 		CMD_DEAL(GS2C_ExitGuild_Result);
 		CMD_DEAL(GS2C_KillOutPlayer_Result);
 		CMD_DEAL(GS2C_TransferLeader_Result);
 		CMD_DEAL(GS2C_SetDeputyLeader_Result);
 		CMD_DEAL(GS2C_RemoveDeputyLeader_Result);
 		CMD_DEAL(GS2C_UpdateAnnouncement_Result);
 		CMD_DEAL(GS2C_GuildDonation_Result);
 		CMD_DEAL(GS2C_UpdateGuildProsperity);
 		CMD_DEAL(GS2C_UpgradeSkill);
 		CMD_DEAL(GS2C_DissolveGuild_Result);
 		CMD_DEAL(GS2C_GuildWar);
 	END_DEAL();
	return false;
}

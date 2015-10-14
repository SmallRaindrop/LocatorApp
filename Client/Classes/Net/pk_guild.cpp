#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteguildList(stNetMsg& msg,guildList& value)
{
	msg << value.guildId;
	msg << value.guildName;
	msg << value.guildLevel;
	msg << value.guildLeaderName;
	msg << value.curMementCnt;
	msg << value.maxMementCnt;
	msg << value.guildProsperity;
	msg << value.guildDeclaration;
}
void ReadguildList(stNetMsg& msg,guildList& value)
{
	msg >> value.guildId;
	msg >> value.guildName;
	msg >> value.guildLevel;
	msg >> value.guildLeaderName;
	msg >> value.curMementCnt;
	msg >> value.maxMementCnt;
	msg >> value.guildProsperity;
	msg >> value.guildDeclaration;
}
void WriteC2GS_LookOverGuildInfo(stNetMsg& msg,C2GS_LookOverGuildInfo& value)
{
	msg << value.playerId;
	msg.command(MSG_C2GS_LookOverGuildInfo);
}
void C2GS_LookOverGuildInfo::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_LookOverGuildInfo(msg_s,*this);
	EndSend();
}
void ReadC2GS_LookOverGuildInfo(stNetMsg& msg,C2GS_LookOverGuildInfo& value)
{
	msg >> value.playerId;
}
void WriteGS2C_GuildList(stNetMsg& msg,GS2C_GuildList& value)
{
	WriteArray(msg,guildList,value.vec);
	msg.command(MSG_GS2C_GuildList);
}
void ReadGS2C_GuildList(stNetMsg& msg,GS2C_GuildList& value)
{
	ReadArray(msg,guildList,value.vec);
}
void WritememberList(stNetMsg& msg,memberList& value)
{
	msg << value.playerId;
	msg << value.memberName;
	msg << value.position;
	msg << value.level;
	msg << value.contribution;
	msg << value.isVip;
	msg << value.career;
	msg << value.isOnline;
}
void ReadmemberList(stNetMsg& msg,memberList& value)
{
	msg >> value.playerId;
	msg >> value.memberName;
	msg >> value.position;
	msg >> value.level;
	msg >> value.contribution;
	msg >> value.isVip;
	msg >> value.career;
	msg >> value.isOnline;
}
void WriteguildSkill(stNetMsg& msg,guildSkill& value)
{
	msg << value.skillType;
	msg << value.skillLevel;
}
void ReadguildSkill(stNetMsg& msg,guildSkill& value)
{
	msg >> value.skillType;
	msg >> value.skillLevel;
}
void WriteGS2C_MemberList(stNetMsg& msg,GS2C_MemberList& value)
{
	msg << value.guildId;
	msg << value.guildAnnouncement;
	WriteArray(msg,guildSkill,value.skillVec);
	WriteArray(msg,memberList,value.vec);
	msg.command(MSG_GS2C_MemberList);
}
void ReadGS2C_MemberList(stNetMsg& msg,GS2C_MemberList& value)
{
	msg >> value.guildId;
	msg >> value.guildAnnouncement;
	ReadArray(msg,guildSkill,value.skillVec);
	ReadArray(msg,memberList,value.vec);
}
void WriteapplyList(stNetMsg& msg,applyList& value)
{
	msg << value.playerId;
	msg << value.name;
	msg << value.level;
	msg << value.career;
	msg << value.isVip;
}
void ReadapplyList(stNetMsg& msg,applyList& value)
{
	msg >> value.playerId;
	msg >> value.name;
	msg >> value.level;
	msg >> value.career;
	msg >> value.isVip;
}
void WriteGS2C_ApplyList(stNetMsg& msg,GS2C_ApplyList& value)
{
	WriteArray(msg,applyList,value.vec);
	msg.command(MSG_GS2C_ApplyList);
}
void ReadGS2C_ApplyList(stNetMsg& msg,GS2C_ApplyList& value)
{
	ReadArray(msg,applyList,value.vec);
}
void WriteC2GS_CreateGuild(stNetMsg& msg,C2GS_CreateGuild& value)
{
	msg << value.guildName;
	msg << value.guildDeclaration;
	msg.command(MSG_C2GS_CreateGuild);
}
void C2GS_CreateGuild::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_CreateGuild(msg_s,*this);
	EndSend();
}
void ReadC2GS_CreateGuild(stNetMsg& msg,C2GS_CreateGuild& value)
{
	msg >> value.guildName;
	msg >> value.guildDeclaration;
}
void WriteGS2C_CreateGuild_Result(stNetMsg& msg,GS2C_CreateGuild_Result& value)
{
	msg << value.retCode;
	WriteguildList(msg, value.st);
	msg.command(MSG_GS2C_CreateGuild_Result);
}
void ReadGS2C_CreateGuild_Result(stNetMsg& msg,GS2C_CreateGuild_Result& value)
{
	msg >> value.retCode;
	ReadguildList(msg, value.st);
}
void WriteGS2C_CreateGuild(stNetMsg& msg,GS2C_CreateGuild& value)
{
	WriteguildList(msg, value.st);
	msg.command(MSG_GS2C_CreateGuild);
}
void ReadGS2C_CreateGuild(stNetMsg& msg,GS2C_CreateGuild& value)
{
	ReadguildList(msg, value.st);
}
void WriteC2GS_RequestJoinGuild(stNetMsg& msg,C2GS_RequestJoinGuild& value)
{
	msg << value.guildId;
	msg.command(MSG_C2GS_RequestJoinGuild);
}
void C2GS_RequestJoinGuild::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_RequestJoinGuild(msg_s,*this);
	EndSend();
}
void ReadC2GS_RequestJoinGuild(stNetMsg& msg,C2GS_RequestJoinGuild& value)
{
	msg >> value.guildId;
}
void WriteGS2C_RequestJoinGuild(stNetMsg& msg,GS2C_RequestJoinGuild& value)
{
	WriteapplyList(msg, value.st);
	msg.command(MSG_GS2C_RequestJoinGuild);
}
void ReadGS2C_RequestJoinGuild(stNetMsg& msg,GS2C_RequestJoinGuild& value)
{
	ReadapplyList(msg, value.st);
}
void WriteC2GS_ApproveRequestJoinGuild(stNetMsg& msg,C2GS_ApproveRequestJoinGuild& value)
{
	msg << value.respon;
	msg << value.requestPlayerId;
	msg << value.guildId;
	msg.command(MSG_C2GS_ApproveRequestJoinGuild);
}
void C2GS_ApproveRequestJoinGuild::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ApproveRequestJoinGuild(msg_s,*this);
	EndSend();
}
void ReadC2GS_ApproveRequestJoinGuild(stNetMsg& msg,C2GS_ApproveRequestJoinGuild& value)
{
	msg >> value.respon;
	msg >> value.requestPlayerId;
	msg >> value.guildId;
}
void WriteGS2C_JoinGuild_Result(stNetMsg& msg,GS2C_JoinGuild_Result& value)
{
	WritememberList(msg, value.st);
	msg.command(MSG_GS2C_JoinGuild_Result);
}
void ReadGS2C_JoinGuild_Result(stNetMsg& msg,GS2C_JoinGuild_Result& value)
{
	ReadmemberList(msg, value.st);
}
void WriteC2GS_UpgradeGuild(stNetMsg& msg,C2GS_UpgradeGuild& value)
{
	msg << value.guildId;
	msg.command(MSG_C2GS_UpgradeGuild);
}
void C2GS_UpgradeGuild::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_UpgradeGuild(msg_s,*this);
	EndSend();
}
void ReadC2GS_UpgradeGuild(stNetMsg& msg,C2GS_UpgradeGuild& value)
{
	msg >> value.guildId;
}
void WriteGS2C_UpgradeGuild_Result(stNetMsg& msg,GS2C_UpgradeGuild_Result& value)
{
	msg << value.retCode;
	msg << value.newLevel;
	msg.command(MSG_GS2C_UpgradeGuild_Result);
}
void ReadGS2C_UpgradeGuild_Result(stNetMsg& msg,GS2C_UpgradeGuild_Result& value)
{
	msg >> value.retCode;
	msg >> value.newLevel;
}
void WriteGS2C_UpgradeGuild(stNetMsg& msg,GS2C_UpgradeGuild& value)
{
	msg << value.level;
	msg << value.maxMementCnt;
	msg << value.guildProsperity;
	msg.command(MSG_GS2C_UpgradeGuild);
}
void ReadGS2C_UpgradeGuild(stNetMsg& msg,GS2C_UpgradeGuild& value)
{
	msg >> value.level;
	msg >> value.maxMementCnt;
	msg >> value.guildProsperity;
}
void WriteC2GS_ExitGuild(stNetMsg& msg,C2GS_ExitGuild& value)
{
	msg << value.guildId;
	msg.command(MSG_C2GS_ExitGuild);
}
void C2GS_ExitGuild::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ExitGuild(msg_s,*this);
	EndSend();
}
void ReadC2GS_ExitGuild(stNetMsg& msg,C2GS_ExitGuild& value)
{
	msg >> value.guildId;
}
void WriteGS2C_ExitGuild_Result(stNetMsg& msg,GS2C_ExitGuild_Result& value)
{
	msg << value.memberId;
	msg.command(MSG_GS2C_ExitGuild_Result);
}
void ReadGS2C_ExitGuild_Result(stNetMsg& msg,GS2C_ExitGuild_Result& value)
{
	msg >> value.memberId;
}
void WriteC2GS_KillOutPlayer(stNetMsg& msg,C2GS_KillOutPlayer& value)
{
	msg << value.memberId;
	msg.command(MSG_C2GS_KillOutPlayer);
}
void C2GS_KillOutPlayer::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_KillOutPlayer(msg_s,*this);
	EndSend();
}
void ReadC2GS_KillOutPlayer(stNetMsg& msg,C2GS_KillOutPlayer& value)
{
	msg >> value.memberId;
}
void WriteGS2C_KillOutPlayer_Result(stNetMsg& msg,GS2C_KillOutPlayer_Result& value)
{
	msg << value.memberId;
	msg.command(MSG_GS2C_KillOutPlayer_Result);
}
void ReadGS2C_KillOutPlayer_Result(stNetMsg& msg,GS2C_KillOutPlayer_Result& value)
{
	msg >> value.memberId;
}
void WriteC2GS_TransferLeader(stNetMsg& msg,C2GS_TransferLeader& value)
{
	msg << value.memberId;
	msg.command(MSG_C2GS_TransferLeader);
}
void C2GS_TransferLeader::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_TransferLeader(msg_s,*this);
	EndSend();
}
void ReadC2GS_TransferLeader(stNetMsg& msg,C2GS_TransferLeader& value)
{
	msg >> value.memberId;
}
void WriteGS2C_TransferLeader_Result(stNetMsg& msg,GS2C_TransferLeader_Result& value)
{
	msg << value.newLeader;
	msg.command(MSG_GS2C_TransferLeader_Result);
}
void ReadGS2C_TransferLeader_Result(stNetMsg& msg,GS2C_TransferLeader_Result& value)
{
	msg >> value.newLeader;
}
void WriteC2GS_SetDeputyLeader(stNetMsg& msg,C2GS_SetDeputyLeader& value)
{
	msg << value.memberId;
	msg.command(MSG_C2GS_SetDeputyLeader);
}
void C2GS_SetDeputyLeader::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SetDeputyLeader(msg_s,*this);
	EndSend();
}
void ReadC2GS_SetDeputyLeader(stNetMsg& msg,C2GS_SetDeputyLeader& value)
{
	msg >> value.memberId;
}
void WriteGS2C_SetDeputyLeader_Result(stNetMsg& msg,GS2C_SetDeputyLeader_Result& value)
{
	msg << value.memberId;
	msg.command(MSG_GS2C_SetDeputyLeader_Result);
}
void ReadGS2C_SetDeputyLeader_Result(stNetMsg& msg,GS2C_SetDeputyLeader_Result& value)
{
	msg >> value.memberId;
}
void WriteC2GS_RemoveDeputyLeader(stNetMsg& msg,C2GS_RemoveDeputyLeader& value)
{
	msg << value.memberId;
	msg.command(MSG_C2GS_RemoveDeputyLeader);
}
void C2GS_RemoveDeputyLeader::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_RemoveDeputyLeader(msg_s,*this);
	EndSend();
}
void ReadC2GS_RemoveDeputyLeader(stNetMsg& msg,C2GS_RemoveDeputyLeader& value)
{
	msg >> value.memberId;
}
void WriteGS2C_RemoveDeputyLeader_Result(stNetMsg& msg,GS2C_RemoveDeputyLeader_Result& value)
{
	msg << value.memberId;
	msg.command(MSG_GS2C_RemoveDeputyLeader_Result);
}
void ReadGS2C_RemoveDeputyLeader_Result(stNetMsg& msg,GS2C_RemoveDeputyLeader_Result& value)
{
	msg >> value.memberId;
}
void WriteC2GS_UpdateAnnouncement(stNetMsg& msg,C2GS_UpdateAnnouncement& value)
{
	msg << value.announcemnet;
	msg.command(MSG_C2GS_UpdateAnnouncement);
}
void C2GS_UpdateAnnouncement::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_UpdateAnnouncement(msg_s,*this);
	EndSend();
}
void ReadC2GS_UpdateAnnouncement(stNetMsg& msg,C2GS_UpdateAnnouncement& value)
{
	msg >> value.announcemnet;
}
void WriteGS2C_UpdateAnnouncement_Result(stNetMsg& msg,GS2C_UpdateAnnouncement_Result& value)
{
	msg << value.announcemnet;
	msg.command(MSG_GS2C_UpdateAnnouncement_Result);
}
void ReadGS2C_UpdateAnnouncement_Result(stNetMsg& msg,GS2C_UpdateAnnouncement_Result& value)
{
	msg >> value.announcemnet;
}
void WriteC2GS_GuildDonation(stNetMsg& msg,C2GS_GuildDonation& value)
{
	msg << value.money;
	msg.command(MSG_C2GS_GuildDonation);
}
void C2GS_GuildDonation::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_GuildDonation(msg_s,*this);
	EndSend();
}
void ReadC2GS_GuildDonation(stNetMsg& msg,C2GS_GuildDonation& value)
{
	msg >> value.money;
}
void WriteGS2C_GuildDonation_Result(stNetMsg& msg,GS2C_GuildDonation_Result& value)
{
	msg << value.contribution;
	msg << value.guildProsperity;
	msg << value.memberId;
	msg.command(MSG_GS2C_GuildDonation_Result);
}
void ReadGS2C_GuildDonation_Result(stNetMsg& msg,GS2C_GuildDonation_Result& value)
{
	msg >> value.contribution;
	msg >> value.guildProsperity;
	msg >> value.memberId;
}
void WriteGS2C_UpdateGuildProsperity(stNetMsg& msg,GS2C_UpdateGuildProsperity& value)
{
	msg << value.contribution;
	msg << value.memberId;
	msg.command(MSG_GS2C_UpdateGuildProsperity);
}
void ReadGS2C_UpdateGuildProsperity(stNetMsg& msg,GS2C_UpdateGuildProsperity& value)
{
	msg >> value.contribution;
	msg >> value.memberId;
}
void WriteGS2C_UpgradeSkill(stNetMsg& msg,GS2C_UpgradeSkill& value)
{
	msg << value.guildProsperity;
	msg << value.skillType;
	msg << value.skillLevel;
	msg.command(MSG_GS2C_UpgradeSkill);
}
void ReadGS2C_UpgradeSkill(stNetMsg& msg,GS2C_UpgradeSkill& value)
{
	msg >> value.guildProsperity;
	msg >> value.skillType;
	msg >> value.skillLevel;
}
void WriteC2GS_DissolveGuild(stNetMsg& msg,C2GS_DissolveGuild& value)
{
	msg << value.guildId;
	msg.command(MSG_C2GS_DissolveGuild);
}
void C2GS_DissolveGuild::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_DissolveGuild(msg_s,*this);
	EndSend();
}
void ReadC2GS_DissolveGuild(stNetMsg& msg,C2GS_DissolveGuild& value)
{
	msg >> value.guildId;
}
void WriteGS2C_DissolveGuild_Result(stNetMsg& msg,GS2C_DissolveGuild_Result& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_DissolveGuild_Result);
}
void ReadGS2C_DissolveGuild_Result(stNetMsg& msg,GS2C_DissolveGuild_Result& value)
{
	msg >> value.retCode;
}
void WriteC2GS_StudyGuildSkill(stNetMsg& msg,C2GS_StudyGuildSkill& value)
{
	msg << value.skillId;
	msg.command(MSG_C2GS_StudyGuildSkill);
}
void C2GS_StudyGuildSkill::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_StudyGuildSkill(msg_s,*this);
	EndSend();
}
void ReadC2GS_StudyGuildSkill(stNetMsg& msg,C2GS_StudyGuildSkill& value)
{
	msg >> value.skillId;
}
void WriteC2GS_UpgradeGuildSkill(stNetMsg& msg,C2GS_UpgradeGuildSkill& value)
{
	msg << value.skillId;
	msg.command(MSG_C2GS_UpgradeGuildSkill);
}
void C2GS_UpgradeGuildSkill::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_UpgradeGuildSkill(msg_s,*this);
	EndSend();
}
void ReadC2GS_UpgradeGuildSkill(stNetMsg& msg,C2GS_UpgradeGuildSkill& value)
{
	msg >> value.skillId;
}
void WriteC2GS_RequestGuildWar(stNetMsg& msg,C2GS_RequestGuildWar& value)
{
	msg << value.guildId;
	msg.command(MSG_C2GS_RequestGuildWar);
}
void C2GS_RequestGuildWar::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_RequestGuildWar(msg_s,*this);
	EndSend();
}
void ReadC2GS_RequestGuildWar(stNetMsg& msg,C2GS_RequestGuildWar& value)
{
	msg >> value.guildId;
}
void WriteGS2C_GuildWar(stNetMsg& msg,GS2C_GuildWar& value)
{
	msg << value.retCode;
	msg << value.isAttack;
	msg << value.guildId;
	msg.command(MSG_GS2C_GuildWar);
}
void ReadGS2C_GuildWar(stNetMsg& msg,GS2C_GuildWar& value)
{
	msg >> value.retCode;
	msg >> value.isAttack;
	msg >> value.guildId;
}

};


#include "pk_guild.h"
#include "DataPool.h"

namespace pk{

	// 我新建一个工会后
	bool OnGS2C_CreateGuild_Result(GS2C_CreateGuild_Result *value)
	{
		return true;
	}

	// 别人新建一个工会
	bool OnGS2C_CreateGuild(GS2C_CreateGuild *value)
	{
		return true;
	}

	// 进游戏初始化工会列表
	bool OnGS2C_GuildList(GS2C_GuildList *value)
	{
		Legion_cl* legion = gDataPool->getLegionData();
		legion->initLegion(value->vec);
		return true;
	}

	// 进游戏初始化本工会成员
	bool OnGS2C_MemberList(GS2C_MemberList *value)
	{
		Legion_cl* legion = gDataPool->getLegionData();
		legion->initMemberList(value->vec);
		return true;
	}
	 
	// 进游戏初始化申请人
	bool OnGS2C_ApplyList(GS2C_ApplyList *value)
	{
		return true;
	}

	// 有新人申请
	bool OnGS2C_RequestJoinGuild(GS2C_RequestJoinGuild *value)
	{
		return true;
	}

	// 本会同意一个新人入会后
	bool OnGS2C_JoinGuild_Result(GS2C_JoinGuild_Result *value)
	{
		return true;
	}

	// 升级工会
	bool OnGS2C_UpgradeGuild_Result(GS2C_UpgradeGuild_Result *value)
	{
		return true;
	}

	// 某个工会升级后
	bool OnGS2C_UpgradeGuild(GS2C_UpgradeGuild *value)
	{
		return true;
	}

	// 某人/我 退出工会
	bool OnGS2C_ExitGuild_Result(GS2C_ExitGuild_Result *value)
	{
		return true;
	}

	// 某人/我 被踢了
	bool OnGS2C_KillOutPlayer_Result(GS2C_KillOutPlayer_Result *value)
	{
		return true;
	}

	// 转移会长
	bool OnGS2C_TransferLeader_Result(GS2C_TransferLeader_Result *value)
	{
		return true;
	}
	// 新公告
	bool OnGS2C_UpdateAnnouncement_Result(GS2C_UpdateAnnouncement_Result *value)
	{
		return true;
	}

	// 捐献后
	bool OnGS2C_GuildDonation_Result(GS2C_GuildDonation_Result *value)
	{
		return true;
	}

	// 某工会繁荣度变化
	bool OnGS2C_UpdateGuildProsperity(GS2C_UpdateGuildProsperity *value)
	{
		return true;
	}


	// 解散工会
	bool OnGS2C_DissolveGuild_Result(GS2C_DissolveGuild_Result *value)
	{
		return true;
	}

	// 有人宣战
	bool OnGS2C_GuildWar(GS2C_GuildWar *value)
	{
		return true;
	}

	bool OnGS2C_SetDeputyLeader_Result(GS2C_SetDeputyLeader_Result* value)
	{
		return true;
	}

	bool OnGS2C_RemoveDeputyLeader_Result(GS2C_RemoveDeputyLeader_Result* value)
	{
		return true;
	}

	bool OnGS2C_UpgradeSkill(GS2C_UpgradeSkill* value)
	{
		return true;
	}
}


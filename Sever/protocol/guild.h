//%%错误码
//-define(Create_Guild_Err_Of_Name_Is_Too_Long, -1). %%名字太长
//-define(Create_Guild_Err_Of_Announcement_Is_Too_Long, -2). %%宣言太长
//-define(Create_Guild_Err_Of_Name_Is_Exit, -3). %%帮会名字已经存在
//-define(Create_Guild_Err_Of_Guild_Is_Exit, -4). %%公会已经存在
//-define(Create_Guild_Err_Of_Money_Is_Not_Enough, -5). %%金钱不足
//-define(Create_Guild_Err_Of_Player_Level, -6). %%玩家等级不足
//-define(Create_Guild_Err_Of_Name_Or_Announcement_Is_Null, -7). %%名字或者宣言为空
//-define(Create_Guild_Err_Of_Item_Is_Not_Enough, -8). %%道具不足
//-define(Create_Guild_Err_Of_Max_Guild_Cnt, -9). %%帮会数量已经达到最大值
//-define(Create_Guild_Succ, 1). %%创建成功

//-define(KillOut_Member_Err_Of_Kill_Identity, -1). %%不是会长或者不是副会长
//-define(KillOut_Member_Err_Of_Member_Is_DeputyLeaer_Or_Leader, -2). %%副会长不能踢出会长或者副会长
//-define(KillOut_Member_Err_Of_Member_Is_Leaer, -3). %%会长不能踢出会长
//-define(KillOut_Member_Err_Of_Guild, -4). %%不是同一个公会
//-define(KillOut_Member_Succ, 1).
struct guildList 
{
	int64 guildId;
	string guildName; //公会名字
	int16 guildLevel;  //公会等级
	string guildLeaderName; //会长
	int32 curMementCnt; //当前公会人数
	int32 maxMementCnt; //最大公会人数
	int32 guildProsperity; //公会繁荣度
	string guildDeclaration; //公会宣言
};

//查看公会列表信息
struct C2GS_LookOverGuildInfo ->
{
	int64 playerId;
};

//公会列表
struct GS2C_GuildList <-
{
	vector<guildList> vec;
};

struct memberList
{
	int64 playerId;
	string memberName; //成员名字
	int8 position; //职位
	int32 level; //等级
	int32 contribution; //贡献度
	int8 isVip;
	int8 career;
	int8 isOnline;
};

struct guildSkill
{
	int32 skillType;
	int32 skillLevel;
};

//帮会成员列表
struct GS2C_MemberList <-
{
	int64 guildId;
	string guildAnnouncement; //公告
	vector<guildSkill> skillVec;
	vector<memberList> vec;
};

struct applyList
{
	int64 playerId;
	string name;
	int32 level;
	int8 career;
	int8 isVip;
};

struct GS2C_ApplyList <-
{
	vector<applyList> vec;
};

//请求创建帮会
struct C2GS_CreateGuild ->
{
	string guildName; //帮会名字
	string guildDeclaration; //帮会宣言
};

struct GS2C_CreateGuild_Result <-
{
	int8 retCode; //-1:名字太长, -2:宣言太长, -3:帮会名字已经存在, -4:公会已经存在, -5:金钱不足, -6:玩家等级不足, -7:名字或者宣言为空, -8:道具不足, -9:帮会数量已经达到最大值, -10:不在线 1:成功
	guildList st;
}

struct GS2C_CreateGuild <-
{
	guildList st;
};

//请求加入帮会
struct C2GS_RequestJoinGuild ->
{
	int64 guildId;
};

struct GS2C_RequestJoinGuild <-
{
	applyList st;
};

//同意或者拒绝
struct C2GS_ApproveRequestJoinGuild ->
{
	int8 respon; //0:拒绝, 1:接受
	int64 requestPlayerId; //0代表全部
	int64 guildId;
};

struct GS2C_JoinGuild_Result <-
{
	memberList st;
};

//升级帮会
struct C2GS_UpgradeGuild ->
{
	int64 guildId; //帮会id
};

struct GS2C_UpgradeGuild_Result <-
{
	//-1: 不是会长不能升级 -2: 帮会已经是最高等级 -3:帮会繁荣度不足 1:成功之路
	int8 retCode;
	int16 newLevel;
};

//广播消息
struct GS2C_UpgradeGuild <-
{
	int16 level;
	int32 maxMementCnt;
	int32 guildProsperity;
};

//退出帮会
struct C2GS_ExitGuild ->
{
	int64 guildId;
};

struct GS2C_ExitGuild_Result <-
{
	int64 memberId;
};

//踢出成员
struct C2GS_KillOutPlayer ->
{
	int64 memberId;
};

struct GS2C_KillOutPlayer_Result <-
{
	int64 memberId;
};

//转让会长
struct C2GS_TransferLeader ->
{
	int64 memberId;
};

struct GS2C_TransferLeader_Result <-
{
	int64 newLeader;
};

//设置副会长
struct C2GS_SetDeputyLeader ->
{
	int64 memberId;
};

struct GS2C_SetDeputyLeader_Result <-
{
	int64 memberId;
};

//移除副会长
struct C2GS_RemoveDeputyLeader ->
{
	int64 memberId;
};

struct GS2C_RemoveDeputyLeader_Result <-
{
	int64 memberId;
};

//更新公告
struct C2GS_UpdateAnnouncement ->
{
	string announcemnet;
};

struct GS2C_UpdateAnnouncement_Result <-
{
	string announcemnet;
};

//捐献
struct C2GS_GuildDonation ->
{
	int32 money;
};

struct GS2C_GuildDonation_Result <-
{
	int32 contribution; //贡献度
	int32 guildProsperity; //公会繁荣度
	int64 memberId; //捐献者
};

struct GS2C_UpdateGuildProsperity <-
{
	int32 contribution; //贡献度
	int64 memberId;
};

struct GS2C_UpgradeSkill <-
{
	int32 guildProsperity; //公会繁荣度
	int32 skillType;
	int32 skillLevel;
};

struct C2GS_DissolveGuild ->
{
	int64 guildId;
};

struct GS2C_DissolveGuild_Result <-
{
	int8 retCode; //1:成功, 0:失败
};

struct C2GS_StudyGuildSkill ->
{
	int32 skillId;
};

struct C2GS_UpgradeGuildSkill ->
{
	int32 skillId;
};

struct C2GS_RequestGuildWar ->
{
	int64 guildId;
};

struct GS2C_GuildWar <-
{
	int8 retCode; //1:开始, 0:结束
	int8 isAttack; //1:攻击者, 0:被攻击者
	int64 guildId;
};
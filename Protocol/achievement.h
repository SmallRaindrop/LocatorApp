struct achievementBase
{
	int32 achievementId;
	int32 sort; //-1代表排在10名后来，排名从1开始; 如果是未完成的成就则表示已经完成的人数，10表示已经完成了10次及以上
};

struct achievementProgress
{
	int32 achievementType;
	int32 cnt; //完成次数
};

struct GS2C_FinishAndUnFinishAchievementList <-
{
	vector<achievementBase> finishVec;//已完成的列表
	vector<achievementBase> unFinishVec;//未完成的列表
	vector<achievementProgress> progressVec;//按成就进度，那些不要记录进度的成就不包含在这个vec，进度为0的成就也不会包含在这个vec
};

struct GS2C_AchieveProgressChange <-
{
	int32 achievementType;
	int32 cnt; //完成次数
};

struct GS2C_AddAchievement <-
{
	achievementBase st;
};

struct C2GS_UseAchievement ->
{
	int32 achievementId;
};

struct GS2C_UseAchievement <-
{
	int8 retCode; //0,此成就未获得, 1成功
	int32 achievementId;
};

struct GS2C_UpdateAchievementFinishCnt <-
{
	int32 achievementId;
	int32 cnt;//获得此成就的人数
};

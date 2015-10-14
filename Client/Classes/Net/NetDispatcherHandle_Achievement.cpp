#include "pk_achievement.h"

namespace pk{

	//上线推送完成的成就
	bool OnGS2C_FinishAndUnFinishAchievementList(GS2C_FinishAndUnFinishAchievementList* value)
	{
		return true;
	}

	//达到某成就时，推送该成就
	bool OnGS2C_AddAchievement(GS2C_AddAchievement* value)
	{
		return true;
	}
	//使用或者取消成就
	bool OnGS2C_UseAchievement(GS2C_UseAchievement* value)
	{
		return true;
	}

	bool OnGS2C_UpdateAchievementFinishCnt(GS2C_UpdateAchievementFinishCnt* value)
	{
		return true;
	}

	bool OnGS2C_AchieveProgressChange(GS2C_AchieveProgressChange* value)
	{
		return true;
	}
}


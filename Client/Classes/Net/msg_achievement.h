
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_achievement(stNetMsg& msg);
const int MSG_GS2C_FinishAndUnFinishAchievementList			= 29003;
const int MSG_GS2C_AchieveProgressChange			= 29004;
const int MSG_GS2C_AddAchievement			= 29005;
const int MSG_C2GS_UseAchievement			= 29006;
const int MSG_GS2C_UseAchievement			= 29007;
const int MSG_GS2C_UpdateAchievementFinishCnt			= 29008;

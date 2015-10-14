
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct achievementBase
{
	int32 achievementId;
	int32 sort;
};
void WriteachievementBase(stNetMsg& msg,achievementBase& value);
void ReadachievementBase(stNetMsg& msg,achievementBase& value);

struct achievementProgress
{
	int32 achievementType;
	int32 cnt;
};
void WriteachievementProgress(stNetMsg& msg,achievementProgress& value);
void ReadachievementProgress(stNetMsg& msg,achievementProgress& value);

struct GS2C_FinishAndUnFinishAchievementList
{
	vector<achievementBase> finishVec;
	vector<achievementBase> unFinishVec;
	vector<achievementProgress> progressVec;
};
void WriteGS2C_FinishAndUnFinishAchievementList(stNetMsg& msg,GS2C_FinishAndUnFinishAchievementList& value);
bool OnGS2C_FinishAndUnFinishAchievementList(GS2C_FinishAndUnFinishAchievementList* value);
void ReadGS2C_FinishAndUnFinishAchievementList(stNetMsg& msg,GS2C_FinishAndUnFinishAchievementList& value);

struct GS2C_AchieveProgressChange
{
	int32 achievementType;
	int32 cnt;
};
void WriteGS2C_AchieveProgressChange(stNetMsg& msg,GS2C_AchieveProgressChange& value);
bool OnGS2C_AchieveProgressChange(GS2C_AchieveProgressChange* value);
void ReadGS2C_AchieveProgressChange(stNetMsg& msg,GS2C_AchieveProgressChange& value);

struct GS2C_AddAchievement
{
	achievementBase st;
};
void WriteGS2C_AddAchievement(stNetMsg& msg,GS2C_AddAchievement& value);
bool OnGS2C_AddAchievement(GS2C_AddAchievement* value);
void ReadGS2C_AddAchievement(stNetMsg& msg,GS2C_AddAchievement& value);

struct C2GS_UseAchievement
{
	int32 achievementId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_UseAchievement(stNetMsg& msg,C2GS_UseAchievement& value);
void ReadC2GS_UseAchievement(stNetMsg& msg,C2GS_UseAchievement& value);

struct GS2C_UseAchievement
{
	int8 retCode;
	int32 achievementId;
};
void WriteGS2C_UseAchievement(stNetMsg& msg,GS2C_UseAchievement& value);
bool OnGS2C_UseAchievement(GS2C_UseAchievement* value);
void ReadGS2C_UseAchievement(stNetMsg& msg,GS2C_UseAchievement& value);

struct GS2C_UpdateAchievementFinishCnt
{
	int32 achievementId;
	int32 cnt;
};
void WriteGS2C_UpdateAchievementFinishCnt(stNetMsg& msg,GS2C_UpdateAchievementFinishCnt& value);
bool OnGS2C_UpdateAchievementFinishCnt(GS2C_UpdateAchievementFinishCnt* value);
void ReadGS2C_UpdateAchievementFinishCnt(stNetMsg& msg,GS2C_UpdateAchievementFinishCnt& value);


};


#ifndef __GameDef_h_
#define __GameDef_h_

#include "zm.h"
#include "cocos2d.h"
USING_NS_CC;
#include "GameShared.h"

#define PI (3.1415926)

#ifdef _GameEditor

#else

#endif	// _GameEditor

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define atoll _atoi64
#endif

#define Default_Font_File "assets/fonts/DroidSansFallback.ttf"

#define gDirector	Director::getInstance()
#define gFileUtils	FileUtils::getInstance()
#define readFromFile(NAME)	Data data=gFileUtils->getDataFromFile(NAME);ByteArray reader(data.getBytes(),data.getSize());

#define TIME_COST_DEF
#ifdef TIME_COST_DEF
#define TIME_COST_BEGIN struct timeval now1;\
struct timeval now2;\
	gettimeofday(&now1, NULL);

#define TIME_RECLOCK_BEGIN gettimeofday(&now1, NULL);

#define TIME_COST_LOG(STR)	gettimeofday(&now2, NULL);\
{float fDeltaTime = (now2.tv_sec - now1.tv_sec) + (now2.tv_usec - now1.tv_usec) / 1000.0f;\
	LOGW("%s cost %.4f ms!",STR,fDeltaTime);}

#define TIME_COST_LOG_RECLOCK_BEGIN(STR)  TIME_COST_LOG(STR)\
	TIME_RECLOCK_BEGIN

#define TIME_COST_LOG_IF(STR,CT)	gettimeofday(&now2, NULL);\
{float fDeltaTime = (now2.tv_sec - now1.tv_sec) + (now2.tv_usec - now1.tv_usec) / 1000.0f;\
	if( fDeltaTime > CT ) LOGW("%s cost %.4f ms!",STR,fDeltaTime);}
#else
#define TIME_COST_BEGIN 

#define TIME_RECLOCK_BEGIN 

#define TIME_COST_LOG(STR)	

#define TIME_COST_LOG_RECLOCK_BEGIN(STR)  TIME_COST_LOG(STR)\
	TIME_RECLOCK_BEGIN

#define TIME_COST_LOG_IF(STR,CT)
#endif

#define FLOAT_TO_INT(F)	(int)(F)
#define FLOAT_TO_INT_5(F) ((F-(int)(F)>=0.5f)?(int)(F+1):(int)(F))

//调试模式，易发现错误地点
#define ReleaseMode			(1)
#define DebugMode			(0)
#define BREAK_IF(cond)           if(cond&&DebugMode) break

// 100-999为地图编号
// 1000-9999为一般动画编号
// 10000-99999为怪物及NPC编号
// 100000-999999为装备编号
// 1000000-9999999为道具编号
// 10000000-99999999为怪物及NPC模型动画编号
// 100000000-999999999为人物模型动画编号
// 1000000000-199999999为人物带坐骑动画编号

// 装备编号规则：职业+性别（0）+部位（00）+等级（00）+品质（0）
// 例如：女战士裸体，400000；男法师10级橙色法袍：201104;

// 道具编号规则：道具类型编号（0000）+编号（000）

// 模型动画编号规则：装备编号或者怪物编号或者NPC编号（000000）+动作编号（00）+方向（0）

typedef unsigned int	EquipmentID;
typedef __int64			AccountID;
typedef __int64			RoleID;
typedef __int64			PlayerID;
typedef __int64			ObjectID;



inline long GetCurrTimeMS()
{
	struct timeval now;
	gettimeofday(&now, nullptr);
	long ret = now.tv_sec*1000 + now.tv_usec / 1000;
	return ret;
}

inline long long GetCurrTimeMicroS()
{
	struct timeval now;
	gettimeofday(&now, nullptr);
	long long ret = now.tv_sec*1000000 + now.tv_usec;
	return ret;
}

#endif				// __GameDef_h_
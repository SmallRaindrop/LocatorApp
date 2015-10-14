/***
 * 模块：游戏地图相关定义
 * 作者：岳良友
 * 时间：2015-07-2
 * 说明：游戏地图类型定义
 */

#ifndef __GameMapTypes_h_
#define __GameMapTypes_h_

#include "StringDef.h"

typedef enum _gameMapPlayType
{
	GameMapPlayType_None,		// 0 无类型
	GameMapPlayType_Def,		// 1 防守
	GameMapPlayType_Kill,		// 2 歼灭
	GameMapPlayType_Catch,		// 3 捕获
	GameMapPlayType_Destroy,	// 4 破坏
	GameMapPlayType_XB,			// 5 寻宝
	GameMapPlayType_Save,		// 6 营救
	GameMapPlayType_Survive,	// 7 生存
	GameMapPlayType_ContendFor,	// 8 争夺
	GameMapPlayType_FreeFight = 20,			// 20 自由战斗
	GameMapPlayType_Count,
}GameMapPlayType;

enum GameMapFuncType
{
	GameMapFuncType_Normal,	// 0 常规地图
	GameMapFuncType_Fight,	// 1 战斗地图
};

enum GameMapType
{
	GameMapType_None,				
	GameMapType_Open,				// 1 开放地图
	GameMapType_MultiPlayers,		// 1 多人副本地图
	GameMapType_SiglePlayer,		// 1 单人副本地图
};

enum GameMapTaskType
{
	GameMapTaskType_None,	// 0 无
	GameMapTaskType_PT,		// 1 普通
	GameMapTaskType_XS,		// 2 悬赏
	GameMapTaskType_EM,		// 3 噩梦
	GameMapTaskType_CT,		// 4 冲突
};

enum GameMapEnemyType
{
	GameMapEnemyType_None,	// 0 无
	GameMapEnemyType_YG,	// 1 妖鬼
	GameMapEnemyType_SZ,	// 2 水族
	GameMapEnemyType_YG_SZ	// 3 妖鬼vs水族
};

#endif
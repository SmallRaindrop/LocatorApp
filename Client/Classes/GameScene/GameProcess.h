
/***
 * 模块：GameProcess
 * 作者：岳良友
 * 时间：2015-7-7
 * 说明：游戏历程管理 播放动画，剧情对话，执行引导等
 */

#include "Singleton.h"
#include "db.h"
#include <deque>

enum GameProcType
{
	GameProcType_Main,		// 主线 当前进程号并且满足条件时执行
	GameProcType_Branch,	// 分支 事件触发满足条件即执行
};

enum GameProcFuncType
{
	GameProcFuncType_Succ,		// 什么也不执行，直接成功
	GameProcFuncType_Animation,	// 播放动画
	GameProcFuncType_Drama,		// 剧情对话
	GameProcFuncType_Guide,		// 引导
	GameProcFuncType_SystemMsg,	// 系统提示
};

enum GameProcEvent
{
	GameProcEvent_None,			// 无事件触发 也可以是所有事件都触发
	GameProcEvent_Timer,		// 毎帧触发
	GameProcEvent_LevelUp,		// 升级
	GameProcEvent_AcceptTask,	// 接受任务
	GameProcEvent_SubmitTask,	// 提交任务
	GameProcEvent_EnterMap,		// 进入地图
	GameProcEvent_NpcView,		// 进入NPC视野
	GameProcEvent_MonsterView,	// 进入怪物视野

	GameProcEvent_LookInfoMonster = 3,	// 怪物进入视野
	GameProcEvent_GuideNext = 4,		// 完成一步引导
	GameProcEvent_TaskDialog = 6,		// 任务对话
	GameProcEvent_StudySkill = 9,		// 学习技能
	GameProcEvent_GetItem = 10,		// 获得新物品
	GameProcEvent_NewAchievement = 12,// 获得新成就
	GameProcEvent_MenuShow = 14,		// 主界面显示出来
	GameProcEvent_BagShow = 15,		// 打开背包界面
	GameProcEvent_StrengthShow = 16,	// 打开强化界面
	GameProcEvent_TipsShow = 17,		// TIPS显示 
	GameProcEvent_Max,
};

class GameProcess : public Singleton_Auto<GameProcess>
{
public:
	GameProcess();
	~GameProcess();

public:
	/* Name		：GetStepID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取当前进度记录ID
	 * Param	: none
	 * Return	: 当前进度记录ID
	 */
	inline int GetStepID(){ return m_nStepID; }

	/* Name		：SetStepID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置当前进度记录ID
	 * Param	: step 历程编号
	 * Return	: void
	 */
	inline void SetStepID(int step){ m_nStepID = step; Reload(); }

	/* Name		：PushEvent
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 抛出一个游戏历程事件
	 * Param	: event 事件编号
	 * Return	: void
	 */
	inline void PushEvent(GameProcEvent event){ m_dequeEvents.push_back(event); }
	inline void ClearEvent(){ m_dequeEvents.clear(); }
	inline GameProcEvent GetCurrEventID(){ return m_nEventID; }
	/* Name		：GetEvent
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取一个游戏历程事件
	 * Param	: none
	 * Return	: GameProcEvent 事件编号
	 */
	GameProcEvent GetEvent();

	/* Name		：TranslateEvent
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 处理一个游戏历程事件
	 * Param	: event 事件编号
	 * Return	: true 成功，false 失败
	 */
	bool TranslateEvent(GameProcEvent event);

	/* Name		：Reload
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 加载游戏历程数据
	 * Param	: none
	 * Return	: true 成功，false 失败
	 */
	bool Reload();

	/* Name		：Execute
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 执行游戏历程
	 * Param	: pData 历程数据
	 * Return	: bool 成功返回true 失败返回false
	 */
	bool Execute(GameProcCfg* pData);

	void Update(float dt);

protected:
	int				m_nStepID;			// 当前主线游戏历程ID
	GameProcCfg*	m_pGameProcData;
	GameProcEvent	m_nEventID;			// 当前处理事件
	deque<int>		m_dequeEvents;		// 事件列表
};

#define gGameProcess GameProcess::Instance()
#ifndef __TaskMgr_h_
#define __TaskMgr_h_

#include "GameDef.h"
#include "Singleton.h"
#include "GameDataManager.h"
#include "Net/pk_task.h"
#include "Net/pk_item.h"

enum NPCTaskState	// NPC身上的任务状态（有任务可交、进行中、可接？）
{
	NTS_NOTHING = 0,
	NTS_ONGOING,
	NTS_ACCEPTABLE,
	NTS_FINISHABLE,
};

enum eTaskState		// 单个任务的状态（可交、进行中、未接？）
{
	TS_NOT_ACCEPTED = 0,
	TS_ONGOING,
	TS_FINISHABLE,
	TS_FINISHED,
};

struct TaskStage	// 单个任务的阶段要做的事（接、做、交）
{
	int		nMapID;
	int		nTargetID;
	Point	ptPos;
	string	strTargetName;
};

struct TaskTarget
{
	string strName;
	int	nID;
	pk::taskProgress progress;	
};

struct TaskAward
{
	struct ItemAward
	{
		ItemCfg*	pItem;
		int			nNum;
		bool		nBind;
	};
	vector<ItemAward>	vtrItems;
	bool				bSelectable;
	int					nExp;
	int					nHonour;
	int					nCoin;
	int					nCoinB;
};

enum eTaskStage	// 标识任务三个阶段：接、做、交
{
	TS_ACCEPT,
	TS_DO,
	TS_TURNIN,

	TS_NOUSE
};

class Task
{
public:
	Task(int id);
	virtual ~Task(){};
	virtual bool CanFinish() = 0;
	TaskCfg*	 GetData()						{return m_pData;}
	int			 GetID()						{return m_pData->id;}
	int			 GetType()						{return m_pData->type;}
	string&		 GetName()						{return m_pData->title;}
	//接受任务剧情ID
	int			 GetAcceptDramaId()				{return m_pData->accept_drama;}
	//进入副本剧情ID
	int			 GetEnterCopyDramaId()			{return m_pData->enter_copy_drama;}
	//退出副本剧情ID
	int			 GetQuitCopyDramaId()			{return m_pData->quit_copy_drama;}

	eTaskStage	 GetCurStage();
	TaskStage*	 GetStage(eTaskStage nStage)	{return &m_arrTargets[nStage];}
	TaskTarget*	 GetTarget()					{return &m_Target;}
	TaskAward*	 GetAward()						{return &m_Award;}
	int			 GetCurTurn()					{return m_nTurn;};
	void		 SetCurTurn(int nNum)			{m_nTurn = nNum;};
	void		 SetTargetCurNum(int nNum);//		{m_Target.progress.curCnt = nNum;};
	void		 GoToTarget(eTaskStage nStage);
	string		 GetManagedTalkString(eTaskStage nStage);
	string		 GetManagedTargetString(eTaskStage nStage);
	int			 GetCopyID()					{return m_pData->copyid;}; //liyang 2015/8/31 得到关卡副本ID

private:
	string _manage_tring(string strText);

protected:
	TaskCfg*		m_pData;
	TaskStage		m_arrTargets[TS_NOUSE];	// 任务各阶段要到达的目的地
	TaskTarget		m_Target;				// 目前最大一个目标
	TaskAward		m_Award;
	int				m_nTurn;				// 第几环
};

class CommonTask : public Task
{
public:
	CommonTask(int id): Task(id){}
	virtual bool CanFinish();
};

// 特殊任务，比如加好友，建工会，跑，跳，攻击，无规律的任务
class SpecialTask : public Task
{
public:
	SpecialTask(int id): Task(id){}
	virtual bool CanFinish(){return true;}
};

class TasksIterator : public ForeachIterator<TaskCfg>
{
public:
	TasksIterator():m_pvtrLevelTask(), m_pvtrMainTask(), m_pvtrNPCTaskAcc(), m_pvtrNPCTaskFin(){m_nNPC = 0;}
	bool execute(TaskCfg* pItem)
	{
		if (m_pvtrLevelTask && pItem->autoget != 0)
		{
			(*m_pvtrLevelTask)[pItem->autoget] = pItem;
		}
		if (m_pvtrMainTask && pItem->type == 2)	// 主线
		{
			m_pvtrMainTask->push_back(pItem);
		}

		if (m_nNPC)
		{
			if (pItem->startnpc == m_nNPC)
				m_pvtrNPCTaskAcc->push_back(pItem->id);
			if (pItem->endnpc == m_nNPC)
				m_pvtrNPCTaskFin->push_back(pItem->id);
		}
		return true;
	}

public:
	map<int, TaskCfg*>*	m_pvtrLevelTask;
	vector<TaskCfg*>*	m_pvtrMainTask;
	vector<int>*		m_pvtrNPCTaskAcc;
	vector<int>*		m_pvtrNPCTaskFin;
	int					m_nNPC;
}; 


class TaskMgr : public Singleton_Auto<TaskMgr>
{
public:
	TaskMgr();
	~TaskMgr();

	//bool Initialize();
	void			Update(float dt);

	Task*			AddTask(int id);
	Task*			SetAcceptableChain(pk::GS2C_SubmitTaskChain *pTask);
	void			AddFinishedTask(pk::completeTask task);
	void			FinishTask(int id);
	void			FinishTaskChain(int id);
	bool			CanTaskBeAccepted(int id);
	bool			CanTaskBeFinished(int id);
	eTaskState		GetTaskState(int id);
	Task*			GetTask(int id);	// 接了，或者可接
	Task*			GetTaskOngoing(int id);
	vector<Task*>&	GetAllTasksOngoing();
	//获得副本相关的任务
	Task*			GetMapTask(int nMapId);
	TaskAward*		GetMapTaskAward(int nMapId);
	int&			GetTaskFinishedTimes(int id);
	NPCTaskState	GetTheseTaskState(vector<int> vtrTasks);
	bool			IsTaskChanged()	{return m_bTaskChanged;}
	void			TaskChanged();
	void			SetTsakProgress(int nTaskID, pk::taskProgress *pData);
	Task*			GetMainTask();
	Task*			GetChainTask();
	Task*			GetAcceptableMainTask()	{return m_pAcceptable;};
	Task*			GetAcceptableChain()	{return m_pAcceptableChain;};
	vector<Task*>&	GetAcceptableTask()		{return m_vtrAcceptable;};
	void			RemoveChainTask();
	void			AutoDoAfterMoveTo(int nTaskID, int nMap, Point pos)	{m_nTaskIDGoingTo = nTaskID; m_nMapGoingTo = nMap; m_ptPointGoingTo = pos;}
	void			Clear();
private:
	vector<Task*>::iterator	_get_task(int id);
	void					_find_acceptable();
private:
	Task*				m_pAcceptable;		// 可接的主线
	Task*				m_pAcceptableChain;
	vector<TaskCfg*>	m_vtrAllTask;		// 游戏世界所有任务，用来遍历判断可接的
	vector<Task*>		m_vtrAcceptable;	// 可接的所有任务
	vector<Task*>		m_vtrAccepted;		// 已接的所有任务
	map<int, int>		m_vtrFinished;		// id,次数
	map<int, TaskCfg*>	m_vtrLevelTask;		// 触发等级，任务
	bool				m_bTaskChanged;		// 用来刷新UI，不直接通知UI，UI来读取这个值
	int					m_nFrameCounter;	// 允许m_bTaskChanged被激发所保持的帧数

	// 控制做任务时到目标地点自动打怪、采集
	int					m_nMapGoingTo;		// 正直奔的地图
	Point				m_ptPointGoingTo;	// 正直奔的具体位置（到了开启挂机、采集
	int					m_nTaskIDGoingTo;	// 控制移动的任务
};

#define gTaskManager	TaskMgr::Instance()

#endif
#include "TaskMgr.h"
#include "Hero.h"
#include "Common/CommonDef.h"
#include "GameScene/BeyondMap.h"
#include "UI/TaskDialog.h"
#include "GameScene/Robot.h"
#include "GameScene/BeginnerGuide.h"
#include "UI/UIWorldMap.h"
#include "UI/DramaUi.h"


Task::Task(int id) : m_nTurn()
{
	m_pData = TaskData.get(id);
	if (m_pData)
	{
		// 目标
		NpcCfg *pNPC1 = NpcCfgData.get(m_pData->startnpc);
		NpcCfg *pNPC2 = NpcCfgData.get(m_pData->endnpc);
		if (pNPC1 && pNPC2)
		{
			m_arrTargets[0].nMapID = pNPC1->map;
			m_arrTargets[2].nMapID = pNPC2->map;
			m_arrTargets[0].ptPos = Point(pNPC1->posx, pNPC1->posy);
			m_arrTargets[2].ptPos = Point(pNPC2->posx, pNPC2->posy);
			m_arrTargets[0].strTargetName = pNPC1->name;
			m_arrTargets[2].strTargetName = pNPC2->name; 
			m_arrTargets[0].nTargetID = pNPC1->id;
			m_arrTargets[2].nTargetID = pNPC2->id; 

		}

		vector<string> des;
		m_arrTargets[1].strTargetName = m_pData->targetcontext;
		vector<string> des2;

		StringSplit(m_pData->targetpos, ",", des);

		if (des.size() == 3)
		{
			m_arrTargets[1].nMapID = atoi(des[0].c_str());
			m_arrTargets[1].ptPos = Point(atoi(des[1].c_str()), atoi(des[2].c_str()));
		}
		else
		{
			m_arrTargets[1].nMapID = 0;
		}
		m_Target.strName = m_pData->targetcontext;

		StringSplit(m_pData->target, ",", des2);

		if (des2.size() == 5)
		{
			m_Target.nID = atoi(des2[1].c_str());
			m_Target.progress.targetType = atoi(des2[0].c_str());
			m_Target.progress.targetCnt = atoi(des2[2].c_str());
			m_arrTargets[1].nTargetID = m_Target.nID;
		}
		else
		{
			m_Target.progress.targetType = 0;
			m_Target.progress.targetCnt = 0;
		}
		m_Target.progress.curCnt = 0;

		// 奖励
		des.clear();
		vector<int> desInt;
		m_Award.nExp	= m_pData->awardexp;
		m_Award.nHonour	= m_pData->awardhonour;
		m_Award.nCoin	= m_pData->awardcoin;
		m_Award.nCoinB	= m_pData->awardbindcoin;
		m_Award.bSelectable = (m_pData->selectawarditems.length() > 0);

		StringSplit(m_pData->awarditems, ";", des);
		StringSplit(m_pData->selectawarditems, ";", des);

		for (size_t i = 0; i < des.size(); i++)
		{
			StringSplitToInt(des[i], ",", desInt);
			TaskAward::ItemAward item = {ItemData.get(desInt[i * 3]), desInt[i * 3 + 1], desInt[i * 3 + 2] != 0};
			m_Award.vtrItems.push_back(item);
		}

		//string arrCareerAward[] = {m_pData->zhanshiawarditems, m_pData->daoshiawarditems, m_pData->gongjianawarditems};
		//des.clear(); desInt.clear();
		//StringSplit(arrCareerAward[gHero->GetCareer() - 1], ";", des);

		for (size_t i = 0; i < des.size(); i++)
		{
			StringSplitToInt(des[i], ",", desInt);
			TaskAward::ItemAward item = {ItemData.get(desInt[0]), desInt[1], desInt[2] != 0};
			m_Award.vtrItems.push_back(item);
		}

	}
}

void Task::SetTargetCurNum(int nNum)
{
	m_Target.progress.curCnt = nNum;

	if (m_Target.progress.curCnt == m_Target.progress.targetCnt)
	{
		if (m_pData->autoreturn != 0)
		{
			GoToTarget(TS_TURNIN);
			gRobot->SetRunning(false);
		}
		gCocosAudio->PlayEffect(117);
	}
}

eTaskStage Task::GetCurStage()	
{
	eTaskStage nStage = CanFinish() ? TS_TURNIN : TS_DO;

	return nStage;
}

void TaskAfterMove(__int64 pData)
{
	Task *pTask = ((Task*)pData);
	int nNPCID = pTask->GetStage(pTask->GetCurStage())->nTargetID;

	MapObjectList list;
	gMap->getObjectManager()->getObjects(mapObjectType_Npc, list);
	for (size_t i = 0; i < list.size(); i++)
	{
		if (list[i]->GetDataID() == nNPCID)
		{
			list[i]->onSelect(true);
			break;
		}
	}

	TaskDialog::Open(pTask);
}

void Task::GoToTarget(eTaskStage nStage)
{
	if ( !gMap )
	{
		return ;
	}

	if (nStage == TS_NOUSE)
	{
		nStage = GetCurStage();
	}

	// 如果是去打怪或者采集
	if(nStage == TS_DO && GetTarget()->progress.targetType == 8)
	{
		// 进入某个关卡副本
		CCLOG("");
		CUIWorldMap::ShowGameCopyToEnter(GetCopyID());
	}
	else if (nStage == TS_DO && (GetTarget()->progress.targetType == 2 || GetTarget()->progress.targetType == 3))
	{
		gHero->SelectTargetCancel();
		gTaskManager->AutoDoAfterMoveTo(GetID(), GetStage(TS_DO)->nMapID, GetStage(TS_DO)->ptPos);

		// go there
		CSuperMove::AfterMoveToDo data = {TaskAfterMove, *(int*)(void*)this};
		CSuperMove::Start(m_arrTargets[nStage].nMapID, m_arrTargets[nStage].ptPos.x, m_arrTargets[nStage].ptPos.y, nStage == TS_DO ? NULL : &data, 0);
	}
	else
	{
		// go there
		CSuperMove::AfterMoveToDo data = {TaskAfterMove, *(int*)(void*)this};
		CSuperMove::Start(m_arrTargets[nStage].nMapID, m_arrTargets[nStage].ptPos.x, m_arrTargets[nStage].ptPos.y, nStage == TS_DO ? NULL : &data, 3);
	}

}

string Task::_manage_tring(string strText)
{
	size_t pos = 0;
	do
	{
		pos = strText.find_first_of('#', pos);
		if (strText[pos + 1] == 'A')
		{
			strText.replace(pos, 2, GetStage(TS_ACCEPT)->strTargetName);
		}
		else if (strText[pos + 1] == 'F')
		{
			strText.replace(pos, 2, GetStage(TS_TURNIN)->strTargetName);
		}
	}
	while (pos != string::npos);

	return strText;
}

string Task::GetManagedTalkString(eTaskStage nStage)
{
	TaskCfg *pTaskCfg = GetData();
	string arrTaskDesc[3] = {pTaskCfg->acceptcontext, pTaskCfg->doingcontext, pTaskCfg->completecontext};
	string strTalk = arrTaskDesc[nStage];

	return _manage_tring(strTalk);
}

string Task::GetManagedTargetString(eTaskStage nStage)
{
	string strTalk = GetStage(TS_DO)->strTargetName;

	if (GetTarget()->progress.targetCnt && TS_ACCEPT != nStage)
	{
		if (GetTarget()->progress.curCnt == GetTarget()->progress.targetCnt)
			strTalk += (CCString::createWithFormat("(<C=0,255,80>%d</c> / <C=0,255,80>%d</c>)", 
			GetTarget()->progress.curCnt, GetTarget()->progress.targetCnt)->getCString());
		else
			strTalk += (CCString::createWithFormat("(<C=255,0,0>%d</c> / <C=0,255,80>%d</c>)", 
			GetTarget()->progress.curCnt, GetTarget()->progress.targetCnt)->getCString());
	}

	return _manage_tring(strTalk);
}


bool CommonTask::CanFinish()
{
	return (m_Target.progress.curCnt == m_Target.progress.targetCnt && m_pData->completelevel <= gHero->GetLevel());
}





TaskMgr::TaskMgr(): m_bTaskChanged(), m_pAcceptable(), m_pAcceptableChain(), m_nFrameCounter(2), m_nMapGoingTo(),
	m_nTaskIDGoingTo()
{
	TasksIterator it;
	it.m_pvtrLevelTask = &m_vtrLevelTask;
	it.m_pvtrMainTask = &m_vtrAllTask;
	TaskData.foreach(it);

	//_find_acceptable();
}

TaskMgr::~TaskMgr()
{
	Clear();
}

vector<Task*>::iterator	TaskMgr::_get_task(int id)
{
	vector<Task*>::iterator it;
	for (it = m_vtrAccepted.begin(); it != m_vtrAccepted.end(); it++)
	{
		if ((*it)->GetID() == id)
			return it;
	}

	return m_vtrAccepted.end();
}

Task* TaskMgr::GetMainTask()
{
	vector<Task*>::iterator it;
	for (it = m_vtrAccepted.begin(); it != m_vtrAccepted.end(); it++)
	{
		if ((*it)->GetData()->type == 2)
			return *it;
	}

	return NULL;
}

Task* TaskMgr::GetChainTask()
{
	if (m_pAcceptableChain)
		return m_pAcceptableChain;

	vector<Task*>::iterator it;
	for (it = m_vtrAccepted.begin(); it != m_vtrAccepted.end(); it++)
	{
		if ((*it)->GetData()->type == 4)
			return *it;
	}

	return NULL;
}

void TaskMgr::RemoveChainTask()
{
	vector<Task*>::iterator it;
	for (it = m_vtrAccepted.begin(); it != m_vtrAccepted.end(); it++)
	{
		if ((*it)->GetData()->type == 4)
		{
			m_vtrAccepted.erase(it);
			TaskChanged();
			break;
		}
	}
}

void TaskMgr::_find_acceptable()
{
	CC_SAFE_DELETE(m_pAcceptable);

	for (size_t i = 0; i < m_vtrAllTask.size(); i++)
	{
		if (CanTaskBeAccepted(m_vtrAllTask[i]->id))
		{
			Task *pTask = new CommonTask(m_vtrAllTask[i]->id);
			if (m_vtrAllTask[i]->type == 2)
			{
				m_pAcceptable = pTask;
				TaskChanged();
			}
			else
			{
				m_vtrAcceptable.push_back(pTask);
			}
		}
	}
}

eTaskState TaskMgr::GetTaskState(int id)
{
	if (GetTaskFinishedTimes(id))
		return TS_FINISHED;

	if (CanTaskBeFinished(id))
		return TS_FINISHABLE;

	if (GetTaskOngoing(id))
		return TS_ONGOING;

		return TS_NOT_ACCEPTED;
}

Task* TaskMgr::GetTask(int id)
{
	if (m_pAcceptable && m_pAcceptable->GetID() == id)
	{
		return m_pAcceptable;
	}

	if (m_pAcceptableChain && m_pAcceptableChain->GetID() == id)
	{
		return m_pAcceptableChain;
	}

	for (size_t i = 0; i < m_vtrAcceptable.size(); i++)
	{
		if (m_vtrAcceptable[i]->GetID() == id)
		{
			return m_vtrAcceptable[i];
		}
	}

	return GetTaskOngoing(id);
}

Task* TaskMgr::GetTaskOngoing(int id)
{
	vector<Task*>::iterator it = _get_task(id);
	return (it == m_vtrAccepted.end() ? NULL : *it);
}

vector<Task*>& TaskMgr::GetAllTasksOngoing()
{
	return m_vtrAccepted;
}

Task* TaskMgr::GetMapTask(int nMapId)
{
	vector<Task*>::iterator it;
	for (it = m_vtrAccepted.begin(); it != m_vtrAccepted.end(); it++)
	{
		if ((*it)->GetData()->copyid == nMapId)
		{
			return (*it);
		}
	}
	return nullptr;
}

TaskAward* TaskMgr::GetMapTaskAward(int nMapId)
{
	Task* pTask = GetMapTask(nMapId);
	if (pTask)
	{
		return pTask->GetAward();
	} 
	else
	{
		return NULL;
	}
}

int& TaskMgr::GetTaskFinishedTimes(int id)
{
	static int zero;
	zero = 0;
	map<int, int>::iterator it = m_vtrFinished.find(id);
	if (it != m_vtrFinished.end())
	{
		return it->second;
	}

	return zero;
}

void TaskMgr::TaskChanged()
{
	m_bTaskChanged = true;
	m_nFrameCounter = 2;
}

Task* TaskMgr::AddTask(int id)
{
	if (GetTaskOngoing(id))
	{
		CCAssert(false, "Task accepted already!");
		return NULL;
	}

	Task *pTask = NULL;
	if (m_pAcceptable && m_pAcceptable->GetID() == id)
	{
		pTask = m_pAcceptable;
		m_pAcceptable = NULL;
	}

	if (m_pAcceptableChain && m_pAcceptableChain->GetID() == id)
	{
		pTask = m_pAcceptableChain;
		m_pAcceptableChain = NULL;
	}

	for (size_t i = 0; i < m_vtrAcceptable.size(); i++)
	{
		if (m_vtrAcceptable[i]->GetID() == id)
		{
			pTask = m_vtrAcceptable[i];
			m_vtrAcceptable.erase(m_vtrAcceptable.begin() + i);
			break;
		}
	}

	m_vtrAccepted.push_back(pTask ? pTask : pTask = new CommonTask(id));

// 	if (pTask->GetData()->autogo != 0)
// 	{
// 		pTask->GoToTarget(TS_NOUSE);
// 	}

	TaskChanged();

	return pTask;
}

void TaskMgr::AddFinishedTask(pk::completeTask task)
{
	map<int, int>::iterator it = m_vtrFinished.find(task.taskId);
	if (it != m_vtrFinished.end())
	{
		(*it).second += task.completeCnt;
	}
	else
	{
		m_vtrFinished[task.taskId] = task.completeCnt;
	}

	m_pAcceptable = NULL;	// 之前有可能完成列表未加载导致可接任务判断失误
	TaskChanged();
}

Task* TaskMgr::SetAcceptableChain(pk::GS2C_SubmitTaskChain *pChain)
{
	CC_SAFE_DELETE(m_pAcceptableChain);

	if (pChain)
	{
		Task *pTask = new CommonTask(pChain->taskId);
		if (pTask->GetType() == 4)
		{
			m_pAcceptableChain = pTask;
			TaskStage *pStage = m_pAcceptableChain->GetStage(TS_ACCEPT);
			NpcCfg *pNPC = NpcCfgData.get(pChain->startNpcDataId);
			pStage->nMapID = pNPC->map;
			pStage->nTargetID = pNPC->id;
			pStage->strTargetName = pNPC->name;
			pStage->ptPos = Point(pNPC->posx, pNPC->posy);

			pStage = m_pAcceptableChain->GetStage(TS_TURNIN);
			pNPC = NpcCfgData.get(pChain->endNpcDataId);
			pStage->nMapID = pNPC->map;
			pStage->nTargetID = pNPC->id;
			pStage->strTargetName = pNPC->name;
			pStage->ptPos = Point(pNPC->posx, pNPC->posy);
			m_pAcceptableChain->SetCurTurn(pChain->loopCnt);

			TaskChanged();
			return pTask;
		}
		else
		{
			CC_SAFE_DELETE(pTask);
		}
	}

	return NULL;
}

void TaskMgr::FinishTask(int id)
{
	vector<Task*>::iterator it = _get_task(id);
	if (it == m_vtrAccepted.end())
	{
		CCAssert(false, "Task not accepted yet!");
		return;
	}
	pk::completeTask task = {(*it)->GetID(), 1};
	AddFinishedTask(task);

	delete *it;
	m_vtrAccepted.erase(it);

	_find_acceptable();
}

void TaskMgr::FinishTaskChain(int id)
{
	vector<Task*>::iterator it = _get_task(id);
	if (it == m_vtrAccepted.end())
	{
		CCAssert(false, "Task not accepted yet!");
		return;
	}

	delete *it;
	m_vtrAccepted.erase(it);
}

bool TaskMgr::CanTaskBeAccepted(int id)
{
	if (GetTaskOngoing(id))
		return false;

	TaskCfg *pTask = TaskData.get(id);
	if (pTask == NULL)
		return false;

	if (GetTaskFinishedTimes(id) > pTask->loopcnt)
	{
		MessageBox(CCString::createWithFormat("Task finished times(%d) > loopcnt(%d)", GetTaskFinishedTimes(id), pTask->loopcnt)->getCString(), "");
	}
	CCASSERT(GetTaskFinishedTimes(id) <= pTask->loopcnt, CCString::createWithFormat("Task finished times(%d) > loopcnt(%d)", GetTaskFinishedTimes(id), pTask->loopcnt)->getCString());

	if (GetTaskFinishedTimes(id) == pTask->loopcnt)
		return false;


	if (pTask->level > gHero->GetLevel())
		return false;

	if (pTask->career && pTask->career != gHero->GetCareer())
		return false;

	if (pTask->previd && GetTaskFinishedTimes(pTask->previd) == 0)
		return false;

	return true;
}

bool TaskMgr::CanTaskBeFinished(int id)
{
	Task *pTask = GetTaskOngoing(id);
	return pTask && pTask->CanFinish();
}

NPCTaskState TaskMgr::GetTheseTaskState(vector<int> vtrTasks)
{
	NPCTaskState state = NTS_NOTHING;

	for (size_t i = 0; i < vtrTasks.size(); i++)
	{
		int nTaskID = vtrTasks[i];
		if (CanTaskBeFinished(nTaskID))
		{
			state = (state < NTS_FINISHABLE ? NTS_FINISHABLE : state);
		}
		if (CanTaskBeAccepted(nTaskID))
		{
			state = (state < NTS_ACCEPTABLE ? NTS_ACCEPTABLE : state);
		}
		if (GetTaskOngoing(nTaskID))
		{
			state = (state < NTS_ONGOING ? NTS_ONGOING : state);
		}
	}

	return state;
}

void TaskMgr::SetTsakProgress(int nTaskID, pk::taskProgress *pData)
{
	GetTaskOngoing(nTaskID)->SetTargetCurNum(pData->curCnt);

	TaskChanged();
}

void TaskMgr::Clear()
{
	vector<Task*>::iterator it;
	for (it = m_vtrAccepted.begin(); it != m_vtrAccepted.end(); it++)
	{
		delete *it;
	}
	m_vtrAccepted.clear();
	for (it = m_vtrAcceptable.begin(); it != m_vtrAcceptable.end(); it++)
	{
		delete *it;
	}
	m_vtrAcceptable.clear();
	m_vtrFinished.clear();

	CC_SAFE_DELETE(m_pAcceptable);
}

void TaskMgr::Update(float dt)
{
	// m_bTaskChanged 保持true状态2帧后重置
	m_nFrameCounter = MAX(0, m_nFrameCounter - 1);
	if (m_nFrameCounter == 0)
	{
		m_bTaskChanged = false;
	}

	//TaskCfg *pAutoTask = m_vtrLevelTask[gHero->GetLevel()];
	//if (pAutoTask && GetTaskOngoing(pAutoTask->id) == NULL)
	//{
	//	AddTask(pAutoTask->id);
	//}

	// 到点，开打
	if (m_nMapGoingTo && gMap && gMap->getMapDataID() == m_nMapGoingTo && abs(gHero->GetCellX() - m_ptPointGoingTo.x) < 3 && abs(gHero->GetCellY() - m_ptPointGoingTo.y) < 3)
	{
		Task *pTask = GetTaskOngoing(m_nTaskIDGoingTo);
		if (pTask)
		{
			if (pTask->GetTarget()->progress.targetType == 2)
				gRobot->SetRunning(true);
			else // 采集
			{
				int nTarget = pTask->GetStage(TS_DO)->nTargetID;

				MapObjectList objList;
				gMap->getObjectManager()->getObjectsInView(mapObjectType_Npc, objList);
				MapObjectList::iterator it;
				for (it = objList.begin(); it != objList.end(); it++)
				{
					if ((*it)->GetDataID() == nTarget)
					{
						gHero->SelectTarget((RoleFighter*)(*it));
						break;
					}
				}
			}
		}
		m_nMapGoingTo = 0;
	}
	// 去任务点移动过程被终止，目标也需要清除，不然玩家自己走到那个点也会自动开启挂机
	if (!CSuperMove::Instance()->IsHungUp() && CSuperMove::Instance()->IsOver())
	{
		m_nMapGoingTo = 0;
	}

	if (m_pAcceptable == NULL && GetMainTask() == NULL)
	{
		//_find_acceptable();
	}
}
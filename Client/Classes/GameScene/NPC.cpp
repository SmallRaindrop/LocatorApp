#include "NPC.h"
#include "StringConverter.h"
#include "GameScene/GameDataManager.h"
#include "GameScene/GameUILayer.h"
#include "Net/NetDispatcher.h"
#include "UI/NpcDialog.h"
#include "UI/CustomCtrl/TimerProgressBar.h"
#include "RoleTitle.h"
#include "RoleTitleLayer.h"
#include "BeyondMap.h"
#include "Hero.h"

CNpc*			CNpc::s_pCurOptNPC;
CNpc*			CNpc::s_pCurCollecting;
map<int, Task*>	CNpc::s_AddtionalTasks;

vector<int>		NpcUI::s_vtrExclusiveUID;

CNpc::CNpc() : m_pCfgData(NULL), m_pCollectionProgressBar(NULL)
{
	m_eTaskState = NTS_NOTHING;
}

CNpc::~CNpc()
{
	if (s_pCurOptNPC == this)
	{
		s_pCurOptNPC = NULL;
	}
	if (s_pCurCollecting == this)
	{
		s_pCurCollecting = NULL;
	}

	if (m_pCollectionProgressBar)
	{
		m_pCollectionProgressBar->removeFromParentAndCleanup(true);
		m_pCollectionProgressBar = NULL;
	}
}

bool CNpc::init()
{
	if ( !initRole() )
	{
		return false;
	}

	m_pData = new NpcData;
	if ( !m_pData )
	{
		return false;
	}

	return true;
}

bool CNpc::initRole()
{
	if ( !RoleFighter::initRole() )
	{
		return false;
	}
	SetType(mapObjectType_Npc);
	return true;
}

void CNpc::SetDataID(int id)
{
	m_pCfgData = NpcCfgData.get(id);
	if ( m_pCfgData )
	{
		SetRoleName(m_pCfgData->name);
		// 设置外观
		SetProperty(RoleProperty_Cloth,m_pCfgData->art_id);
		SetBoundingInfo(m_pCfgData->body_size,m_pCfgData->body_size,m_pCfgData->height);
		if ( m_pCfgData->scale != 0 )
		{
			setScale((float)m_pCfgData->scale/100.f);
		}
		SetSkinEffect(m_pCfgData->skin);
		changeDir(DIR_S);

		// 初始化任务数据
		TasksIterator iter;
		iter.m_nNPC = id;
		iter.m_pvtrNPCTaskAcc = &m_vtrTaskAcc;
		iter.m_pvtrNPCTaskFin = &m_vtrTaskFin;
		TaskData.foreach(iter);

		if ( m_pRoleTitle )
		{
			m_pRoleTitle->SetRoleTitle(m_pCfgData->title);
			m_pRoleTitle->GetName()->setColor(Color3B::GREEN);
			m_pRoleTitle->GetTitle()->setColor(Color3B::YELLOW);
		}

		if(m_pCfgData->type == 2)
		{
			CheckForCollect();
			m_pRoleTitle->GetName()->setColor(Color3B(65, 251, 243));
		}
	}
}

void NpcAfterMove (__int64 pData)
{
	gGameUILayer->open(IDU_NPCDIALOG);
}

void AfterGoToCollect (__int64 pData)
{
	CNpc* pNpc = (CNpc*)(gMap->getObjectManager()->getObject(pData));
	if (pNpc)
	{
		pNpc->CollectStart();
	}
}

void CNpc::onSelect(bool param)
{
	RoleFighter::onSelect(param);

	if ( m_pCfgData )
	{
		s_pCurOptNPC = this;
		if(m_pCfgData->type == 2)
		{
			vector<Task*>& doingList=gTaskManager->GetAllTasksOngoing();
			for (vector<Task*>::iterator iter = doingList.begin(); iter != doingList.end(); iter++)
			{
				if ( !(*iter)->CanFinish() && (*iter)->GetTarget()->nID == GetDataID())
				{
					CSuperMove::AfterMoveToDo data = {AfterGoToCollect, GetId()};
					CSuperMove::Start(gMap->getMapDataID(), GetCellX(), GetCellY(), &data, 3);
					return;
				}
			}
		}
		CSuperMove::AfterMoveToDo data = {NpcAfterMove, GetId()};
		CSuperMove::Start(gMap->getMapDataID(), GetCellX(), GetCellY(), &data, m_pCfgData->viewrange);
	}
	else
	{
		s_pCurOptNPC = NULL;
	}
}

NPCTaskState CNpc::GetTaskState()
{
	NPCTaskState state = NTS_NOTHING;

	for (size_t i = 0; i < m_vtrTaskFin.size(); i++)
	{
		if (gTaskManager->CanTaskBeFinished(m_vtrTaskFin[i]))
		{
			return NTS_FINISHABLE;
		}

		if (gTaskManager->GetTaskOngoing(m_vtrTaskFin[i]))
			state = NTS_ONGOING;
	}
	for (size_t i = 0; i < m_vtrTaskAcc.size(); i++)
	{
		if (gTaskManager->CanTaskBeAccepted(m_vtrTaskAcc[i]))
		{
			return NTS_ACCEPTABLE;
		}
	}

	return state;
}

void CNpc::update(float dt)
{
	RoleFighter::update(dt);

	NPCTaskState state = GetTaskState();
	if (m_eTaskState != state)
	{
		m_eTaskState = state;
		m_pRoleTitle->SetNPCTaskState(m_eTaskState);
	}

	// 任务链刷新
	map<int, Task*>::iterator it = s_AddtionalTasks.find(GetDataID());
	if (it != s_AddtionalTasks.end())
	{
		if (it->second->GetStage(TS_ACCEPT)->nTargetID == GetDataID())
		{
			m_vtrTaskAcc.push_back(it->second->GetID());
			s_AddtionalTasks.erase(it);
		}
		else if (it->second->GetStage(TS_TURNIN)->nTargetID == GetDataID())
		{
			m_vtrTaskFin.push_back(it->second->GetID());
			s_AddtionalTasks.erase(it);
		}
	}
}

void CNpc::RefreshEquip()
{
	RoleFighter::RefreshEquip();
}



// 采集部分------------------------------

void CNpc::CheckForCollect()
{
	m_nCollectionTaskID = 0;

	vector<Task*>& doingList=gTaskManager->GetAllTasksOngoing();
	for (vector<Task*>::iterator iter = doingList.begin(); iter != doingList.end(); iter++)
	{
		if ((*iter)->GetTarget()->nID == GetDataID() )
		{
			m_nCollectionTaskID = (*iter)->GetData()->id;
			break;
		}
	}

	setVisible(m_nCollectionTaskID != 0);
	m_pRoleTitle->setVisible(m_nCollectionTaskID != 0);
}

void CNpc::CollectStart()
{
	if (s_pCurCollecting)
	{
		s_pCurCollecting->CollectInterrupt();
	}
	s_pCurCollecting = this;
	if (m_pCollectionProgressBar == NULL)
	{
		m_pCollectionProgressBar = TimerProgressBar::create();
		if (m_pCollectionProgressBar == NULL)
			return;

		m_pCollectionProgressBar->loadTexture("assets/ui/mainui/collection_Bar.png");
		m_pCollectionProgressBar->SetBGImg("Image_CollectionBar_BG");
	}
	m_pCollectionProgressBar->InitWithTarget(this, this, (SEL_SCHEDULE)&CNpc::CollectTimeOut, 3.f);
	if (m_pCollectionProgressBar->getParent() == NULL)
	{
		m_pCollectionProgressBar->setScale(0.6f);
		gRoleTitleLayer->addChild(m_pCollectionProgressBar);
	}
	m_pCollectionProgressBar->SetRunning(true);
	gCocosAudio->PlayEffect(116);
}

void CNpc::CollectInterrupt()
{
	if (m_pCollectionProgressBar)
	{
		m_pCollectionProgressBar->SetRunning(false);
	}
	s_pCurCollecting = NULL;
}

void CNpc::CollectTimeOut(float fNoUse)
{
	pk::C2GS_CompleteGather cmd = {GetId()};
	cmd.Send(gNetSocket);
}

void CNpc::CollectFinished()
{
	gCocosAudio->PlayEffect(131);
	m_pCollectionProgressBar->SetRunning(false);
	s_pCurCollecting = NULL;
    Task* pData = gTaskManager->GetTaskOngoing(m_nCollectionTaskID);
    if (pData==NULL)
    {
        return;
    }
    if (pData->CanFinish())
	{
		//gTaskManager->TraceTask(m_nCollectionTaskID);
	}
	else
	{
		CollectStart();
	}
}







void NpcUI::update(float dt)
{
	if (CNpc::s_pCurOptNPC)
	{
		int distance = Distance(gHero->GetCellX(),gHero->GetCellY(),CNpc::s_pCurOptNPC->GetCellX(),CNpc::s_pCurOptNPC->GetCellY());
		if ( distance > CNpc::s_pCurOptNPC->GetData()->viewrange )
		{
			gGameUILayer->close(this);
		}		
	}
	else
	{
		gGameUILayer->close(this);
	}
}


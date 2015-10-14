#include "CopyMapUI.h"
#include "GameScene/MessageCenter.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/TaskMgr.h"
#include "DramaUi.h"
#include "GameScene/IndicatorLayer.h"
#include "Net/NetDispatcher.h"

void CCopyMapUI::OpenCopyMapUI()
{
	CloseCopyMapUI();
	switch (gMap->getPlayType())
	{
	case GameMapPlayType_Kill:
	case GameMapPlayType_Catch:
	case GameMapPlayType_Destroy:
	case GameMapPlayType_XB:
	case GameMapPlayType_Save:
		gCopyDataMgr->SetCopyMapUI((CCopyMapUI*)gGameUILayer->open(IDU_CopyCommon));
		break;
	case GameMapPlayType_Def:
		gCopyDataMgr->SetCopyMapUI((CCopyMapUI*)gGameUILayer->open(IDU_CopyUIDef));
		break;
	case GameMapPlayType_Survive:
		gCopyDataMgr->SetCopyMapUI((CCopyMapUI*)gGameUILayer->open(IDU_CopyUISurvive));
		break;
	case GameMapPlayType_FreeFight:
		gCopyDataMgr->SetCopyMapUI((CCopyMapUI*)gGameUILayer->open(IDU_CopyFreeFight));
		break;
	case GameMapPlayType_ContendFor:
		gCopyDataMgr->SetCopyMapUI((CCopyMapUI*)gGameUILayer->open(IDU_CopyUIContendFor));
		break;
	default:
		break;
	}
	//gCopyDataMgr->SetCopyMapUI((CCopyMapUI*)gGameUILayer->open(gMap->getPlayType()+IDU_CopyUIStart));
}

void CCopyMapUI::CloseCopyMapUI()
{
	gGameUILayer->close(gCopyDataMgr->GetCopyMapUI());
	gGameUILayer->close(IDU_OneStrokeUI);
	gGameUILayer->close(IDU_OpenLock);
}

CCopyMapUI::CCopyMapUI(int idu,const std::string& strJsonFile)
	:GameUI(idu,strJsonFile)
	,m_pStepDataCfg(nullptr)
	,m_pMapDataCfg(nullptr)
	,m_pGoalNum(nullptr)
	,m_pCurNum(nullptr)
	,m_pCountSeconds(nullptr)
	,m_pGoalTitle(nullptr)
	,m_pCurTitle(nullptr)
	,m_pCountSecondsTitle(nullptr)
	,m_pWaveIdx(nullptr)
	,m_nCountSeconds(0)
	,m_nGoalNum(0)
	,m_nCurNum(0)
	,m_nWaveIdx(0)
	,m_bActive(false)
{
}

CCopyMapUI::~CCopyMapUI()
{
	m_pStepDataCfg = nullptr;
	m_pMapDataCfg = nullptr;
}

void CCopyMapUI::onClose()
{
	EndCountSeconds();
}

void CCopyMapUI::UpdateCopyInitInfo(pk::GS2C_CopyInitInfo* value)
{
	m_pStepDataCfg = CopyStepData.get(value->copyStepId);
	m_pMapDataCfg = MapData.get(value->mapDataID);
	if(!m_pMapDataCfg || !m_pStepDataCfg)
	{
		gGameUILayer->close(this);
		return;
	}

	SetGoalNum(value->totalCnt);
	SetCurNum(value->curCnt);
	StartCountSeconds(value->remainSec);

	CheckIfShowIndicator();

	Task* pTask = gTaskManager->GetMapTask(value->mapDataID);
	if (pTask)
	{
		DramaUI::PlayDrama(pTask->GetEnterCopyDramaId());
	}
	gCopyDataMgr->SetCopyDoingTask(pTask);
}

void CCopyMapUI::UpdateCopyProgress(pk::GS2C_UpdateCopyProgress* value)
{
	m_pStepDataCfg = CopyStepData.get(value->copyStepId);
	if (!m_pStepDataCfg)
	{
		gGameUILayer->close(this);
		return;
	}

	SetCurNum(value->curCnt);

	CheckIfShowIndicator();
}

void CCopyMapUI::updateMonsterWave(pk::GS2C_MonsterSpawnRemind* value)
{
	SetWaveIdx(value->waveIndex);
	StartCountSeconds(value->delaySec);
	m_bActive = (bool)value->isActive;
	if(m_bActive)
	{
		EndCountSeconds();
		OnActive();
	}
	else
	{
		BeforeActive();
	}
}

void CCopyMapUI::UpdateCountTime(pk::GS2C_COPY_SUCC_TIME* value)
{
	if(value == 0)
	{
		EndCountSeconds();
	}
	else
	{
		StartCountSeconds(value->time);
	}
}

void CCopyMapUI::SetGoalNum(int nGoalNum)
{
	m_nGoalNum = nGoalNum;
	if(m_pGoalNum)
	{
		m_pGoalNum->setText(CCString::createWithFormat("%d",m_nGoalNum)->getCString());
	}
}

void CCopyMapUI::SetCurNum(int nCurNum)
{
	m_nCurNum = nCurNum;
	if(m_pCurNum)
	{
		m_pCurNum->setText(CCString::createWithFormat("%d",m_nCurNum)->getCString());
	}
}

void CCopyMapUI::SetWaveIdx(int nWaveIdx)
{
	m_nWaveIdx = nWaveIdx;
	if(m_pWaveIdx)
	{
		m_pWaveIdx->setText(CCString::createWithFormat("%d",m_nWaveIdx)->getCString());
	}
}

void CCopyMapUI::StartCountSeconds(int nSeconds)
{
	if(!m_pCountSeconds || nSeconds<=0) return;

	EndCountSeconds();

	m_nCountSeconds = nSeconds;
	m_pCountSeconds->setEnabled(true);
	m_pCountSeconds->setText(SecondsToTime(m_nCountSeconds,1));
	schedule(schedule_selector(CCopyMapUI::ScheduleCountSeconds),1.0f,m_nCountSeconds,1.0f);
}

void CCopyMapUI::EndCountSeconds()
{
	if(!m_pCountSeconds) return;

	m_pCountSeconds->setEnabled(false);
	unschedule(schedule_selector(CCopyMapUI::ScheduleCountSeconds));
}

void CCopyMapUI::ScheduleCountSeconds(float dt)
{
	m_nCountSeconds--;
	if(m_nCountSeconds<0)
	{
		EndCountSeconds();
	}
	else
	{
		m_pCountSeconds->setText(SecondsToTime(m_nCountSeconds,1));
	}
}

void CCopyMapUI::CheckIfShowIndicator()
{
	if (m_pMapDataCfg->direct_target.empty())
	{
		gIndicatorLayer->RemoveStaticIndicators();
		return;
	}
	vector<string> indicatorCfgs;
	StringSplit(m_pMapDataCfg->direct_target,";",indicatorCfgs);
	for (size_t i=0; i<indicatorCfgs.size(); ++i)
	{
		vector<int> indicatorCfg;
		StringSplitToInt(indicatorCfgs[i],",",indicatorCfg);
		if(indicatorCfg.size()<5) continue;
		if (indicatorCfg[0] == m_pStepDataCfg->id )
		{
			gIndicatorLayer->AddStaticIndicator(indicatorCfg[1],indicatorCfg[2],indicatorCfg[3],indicatorCfg[4]);
		}
	}

}
#include "CMatchMachine.h"
#include "GameScene/GameUILayer.h"
#include "UI/TeamUI.h"
#include "UI/LoadingUI.h"

CMatchMachine::CMatchMachine()
{
	Init();
}

CMatchMachine::~CMatchMachine()
{
	Clear();
}

void CMatchMachine::Init()
{
	m_bMatchStarted = false;
	m_nMatchInvitedPlayerId = 0;
	m_fMatchCountSeconds = -1.0f;
	m_nMatchCopyMapIdToEnter = 0;
	m_nMatchMode = MatchMode_None;
	m_bMatchPrepared = false;
	m_fMatchWaitTime = 0.0f;
	m_nMatchStartTimeStamp = 0;
	m_fMatchCountSecondSum = 0.0f;
}

void CMatchMachine::Clear()
{
	SetMatchCopyMapIdToEnter(0);
	SetMatchMode(MachMode_End);
	SetMatchPrepared(false);
	SetMatchInvitedPlayerId(0);
	SetMatchCountSeconds(-1.0f);
	SetMatchStarted(false);
	SetMatchWaitTime(0.0f);
}

void CMatchMachine::Update(float dt)
{
	if (m_fMatchCountSeconds>=0.0f)
	{
		time_t nowTime;
		time(&nowTime);
		m_fMatchCountSeconds = m_fMatchCountSecondSum - (nowTime-m_nMatchStartTimeStamp);
	}
	else
	{
		if(!IsMatchStarted()) return;
		if ( GetMatchMode() == MatchMode_Match )
		{
			m_fMatchWaitTime += dt;
			return;
		};

		MatchEnd();
		if (gGameUILayer->isActive(IDU_WORLDMAPUI))
		{
			gGameUILayer->close(IDU_WORLDMAPUI);
		}
		gLoadingUI->Show(LOADRES_TYPE);
	}
}

void CMatchMachine::UpdateMatchStatus()
{
	int matchStatus = ((int)CTeamUI::GetTeamStatus()) | ((int)GetMatchMode()<<2);
	SetMatchStatus(MatchStatus(matchStatus));
}

void CMatchMachine::MatchEnd()
{
	Clear();
}
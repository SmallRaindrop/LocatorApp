#include "PKMode.h"
#include "GameScene/Player.h"
#include "GameScene/Hero.h"
#include "UI/TeamUI.h"

bool		m_PKLogic[3][6] = { 0, 1, 1, 1, 0, 0,
								1, 1, 1, 1, 0, 1,
								1, 1, 1, 1, 0, 0 };

ePKState CPKMode::GetHisPkState(CPlayer* pHim)
{
	ePKState state = PKS_WHITE;
	if (CTeamUI::GetTeamMember(pHim->GetId()))
	{
		state = PKS_YELLOW;
	}

	return state;
}

bool CPKMode::CanIFightHim(CPlayer* pHim)
{
	return true;
}
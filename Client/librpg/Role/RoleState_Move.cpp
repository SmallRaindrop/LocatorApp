#include "Role.h"
#include "RoleEvent.h"
#include "RoleState.h"

void MoveState::OnEnter(Role* pTarget)
{
	pTarget->playAction(RoleAction_Move);
	m_fDelay = 0.0f;
}

void MoveState::OnLeave(Role* pTarget)
{
	//pTarget->GetMoveMonitor().Terminate();
}

void MoveState::OnTimer(Role* pTarget,float dt)
{
	static const float TIMER = 0.1f;

	if ( !pTarget->updateMove(dt) )
	{
		m_fDelay += dt;
	}
	else
	{
		m_fDelay = 0.0f;
	}

	if ( m_fDelay > TIMER )
	{
		pTarget->EnterState(RoleState_Idle);
		m_fDelay = 0.0f;
	}
}

void MoveState::OnEvent(Role* pTarget,IStateEvent* event)
{
	if ( event->_type == RoleEvent_Attack )
	{
		AttackEvent* evt = dynamic_cast<AttackEvent*>(event);
		//pTarget->attack("2003002");
	}

	if ( event->_type == RoleEvent_Move )
	{
		MoveEvent* evt = dynamic_cast<MoveEvent*>(event);
		static int dir = 0;
		pTarget->MoveBy(__Dir((dir++)%8));
	}
}
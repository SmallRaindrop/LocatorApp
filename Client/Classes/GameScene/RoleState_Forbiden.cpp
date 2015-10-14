#include "Role.h"
#include "RoleState_Forbiden.h"
#include "RoleEvent.h"
#include "RoleFighter.h"

void ForbiddenState::OnEnter(Role* pTarget)
{
	RoleFighter* pFighter = dynamic_cast<RoleFighter*>(pTarget);
	if ( !pFighter )
	{
		pTarget->EnterState(RoleState_Idle);
		return ;
	}

	m_fElapsed = 0.0f;

}

void ForbiddenState::OnLeave(Role* pTarget)
{
	m_fElapsed = 0.0f;
}

void ForbiddenState::OnTimer(Role* pTarget,float dt)
{
	m_fElapsed += dt;

	if ( m_fElapsed > 0.5f )
	{
		pTarget->EnterState(RoleState_Idle);
		return ;
	}
}

void ForbiddenState::OnEvent(Role* pTarget,IStateEvent* event)
{
	if ( event->_type == RoleEvent_AttackEnd )
	{
		
	}
}
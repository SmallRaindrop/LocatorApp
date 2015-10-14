#include "Role.h"
#include "RoleState.h"
#include "RoleEvent.h"

void ReadyState::OnEnter(Role* pTarget)
{
	m_fDelayTime = 0.0f;
}

void ReadyState::OnLeave(Role* pTarget)
{

}

void ReadyState::OnTimer(Role* pTarget,float dt)
{
	static const float DELAY_TIME = 30.0f;
	m_fDelayTime += dt;
	if ( DELAY_TIME < m_fDelayTime )
	{
		pTarget->EnterState(RoleState_Idle);
	}
}

void ReadyState::OnEvent(Role* pTarget,IStateEvent* event)
{
	if ( event->_type == RoleEvent_Attack )
	{
		AttackEvent* evt = dynamic_cast<AttackEvent*>(event);
		//pTarget->attack("2003002");
	}

	if ( event->_type == RoleEvent_Move )
	{
		MoveEvent* evt = dynamic_cast<MoveEvent*>(event);
		//pTarget->MoveTo(evt->destX,evt->destY);
	}

	if ( event->_type == RoleEvent_Injured )
	{
		InjuredEvent* evt = dynamic_cast<InjuredEvent*>(event);
		pTarget->EnterState(RoleState_Injured);
	}
}
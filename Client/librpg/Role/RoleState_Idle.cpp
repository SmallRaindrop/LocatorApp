#include "Role.h"
#include "RoleState.h"
#include "RoleEvent.h"

void IdleState::OnEnter(Role* pTarget)
{
	pTarget->playAction(RoleAction_Stand);
}

void IdleState::OnLeave(Role* pTarget)
{

}

void IdleState::OnTimer(Role* pTarget,float dt)
{

}

void IdleState::OnEvent(Role* pTarget,IStateEvent* event)
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
#include "Role.h"
#include "RoleState_Injured.h"
#include "RoleEvent.h"

void InjuredState::OnEnter(Role* pTarget)
{
	pTarget->SetSkinEffect(SkinEffect_HighLight);
	pTarget->playAction(RoleAction_Injured);
	m_fElapsed = 0.0f;
}

void InjuredState::OnLeave(Role* pTarget)
{
	pTarget->SetSkinEffect(SkinEffect_None);
	m_fElapsed = 0.0f;
}

void InjuredState::OnTimer(Role* pTarget,float dt)
{
	if ( pTarget->getArmor()->getAnimation()->getCurrentFrameIndex() > 6 )
	{
		pTarget->SetSkinEffect(SkinEffect_None);
	}

	m_fElapsed += dt;

	if ( m_fElapsed > 0.5f )
	{
		pTarget->EnterState(RoleState_Idle);
		return ;
	}
}

void InjuredState::OnEvent(Role* pTarget,IStateEvent* event)
{
	if ( event->_type == RoleEvent_InjuredEnd )
	{
		pTarget->EnterState(RoleState_Idle);
	}
}
#include "Role.h"
#include "RoleState_Fight.h"
#include "RoleEvent.h"
#include "RoleFighter.h"
#include "SkillScriptFactory.h"

FightState::FightState() : IRoleState(RoleState_Fight),m_pSkillScript(NULL)
{

}

FightState::~FightState()
{
	CC_SAFE_DELETE(m_pSkillScript);
}

void FightState::OnEnter(Role* pTarget)
{
	RoleFighter* pFighter = dynamic_cast<RoleFighter*>(pTarget);
	if ( !pFighter )
	{
		pTarget->EnterState(RoleState_Idle);
		return ;
	}

	SkillCfg* pSkill = pFighter->GetActiveSkill();
	if ( !pSkill )
	{
		pTarget->EnterState(RoleState_Idle);
		return ;
	}

	// 取技能处理脚本
	m_pSkillScript = SkillScriptFactory::CreateScript(SkillType(pSkill->type));
	if ( !m_pSkillScript )
	{
		pTarget->EnterState(RoleState_Idle);
		return ;
	}

	if ( !m_pSkillScript->Execute(pFighter) )
	{
		pTarget->EnterState(RoleState_Idle);
		return ;
	}
}

void FightState::OnLeave(Role* pTarget)
{
	CC_SAFE_DELETE(m_pSkillScript);
}

void FightState::OnTimer(Role* pTarget,float dt)
{
	if ( !m_pSkillScript )
	{
		return ;
	}

	if ( m_pSkillScript->Process(dt) )
	{
		CC_SAFE_DELETE(m_pSkillScript);
		pTarget->EnterState(RoleState_Idle);
		return;
	}
}

void FightState::OnEvent(Role* pTarget,IStateEvent* event)
{
	if ( event->_type == RoleEvent_AttackEnd )
	{
		//pTarget->readyFight();
	}
}
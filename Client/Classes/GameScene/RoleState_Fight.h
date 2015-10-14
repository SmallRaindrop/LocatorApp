#pragma once

#include "RoleState.h"
#include "SkillScript.h"

/***
 * 模块：角色状态
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：角色战斗状态，处理释放技能，战斗规则
 */

class FightState : public IRoleState
{
public:
	FightState();
	~FightState();

	void OnEnter(Role* pTarget);
	void OnLeave(Role* pTarget);
	void OnTimer(Role* pTarget,float dt);
	void OnEvent(Role* pTarget,IStateEvent* event);

private:
	SkillScript* m_pSkillScript;	// 技能逻辑
};
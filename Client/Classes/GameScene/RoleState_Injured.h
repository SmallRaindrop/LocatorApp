#pragma once

#include "RoleState.h"

/***
 * 模块：角色状态
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：角色受伤硬直状态
 */
class InjuredState : public IRoleState
{
public:
	InjuredState() : IRoleState(RoleState_Injured){}
	~InjuredState(){}

	void OnEnter(Role* pTarget);
	void OnLeave(Role* pTarget);
	void OnTimer(Role* pTarget,float dt);
	void OnEvent(Role* pTarget,IStateEvent* event);

protected:
	float m_fElapsed;		// 计时器
};
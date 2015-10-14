#pragma once

#include "RoleState.h"

/***
 * 模块：角色状态
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：角色死亡状态
 */
class DeadState : public IRoleState
{
public:
	DeadState() : IRoleState(RoleState_Dead){}
	~DeadState(){}

	void OnEnter(Role* pTarget);
	void OnLeave(Role* pTarget);
	void OnTimer(Role* pTarget,float dt);
	void OnEvent(Role* pTarget,IStateEvent* event);

	void HitActionCallBack(Role* pTarget);

protected:

};
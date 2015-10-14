#pragma once
/***
 * 模块：角色限制状态
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：角色所有限制状态集合，受伤，眩晕，沉默等等
 */

#include "RoleState.h"

/***
 * 模块：角色状态
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：角色受限制状态，包括眩晕，冰冻等等受限制的状态
 */
class ForbiddenState : public IRoleState
{
public:
	ForbiddenState() : IRoleState(RoleState_Forbidden){}
	~ForbiddenState(){}

	void OnEnter(Role* pTarget);
	void OnLeave(Role* pTarget);
	void OnTimer(Role* pTarget,float dt);
	void OnEvent(Role* pTarget,IStateEvent* event);

protected:
	float m_fElapsed;		// 计时器
};
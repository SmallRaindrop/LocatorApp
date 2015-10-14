/***
 * 模块：角色状态
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：角色所有状态处理及定义，角色状态机组成部分
 */

#ifndef __RoleState_h_
#define __RoleState_h_

#include "StateMachine.h"
#include "Map/AStar.h"

enum RoleState
{
	RoleState_Idle,		// 空闲状态
	RoleState_Move,		// 移动状态
	RoleState_Fight,	// 战斗状态
	RoleState_Ready,	// 备战状态 
	RoleState_Injured,	// 受伤状态
	RoleState_Forbidden,// 限制状态
	RoleState_Dead,		// 死亡状态
};

class Role;

/***
 * 模块：角色状态
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：角色状态基类
 */
class IRoleState : public IState<Role>
{
public:
	IRoleState(int id) : IState(id){}
	virtual ~IRoleState(){}
};

/***
 * 模块：角色状态
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：角色休闲待机状态
 */
class IdleState : public IRoleState
{
public:
	IdleState() : IRoleState(RoleState_Idle){}
	~IdleState(){}

	void OnEnter(Role* pTarget);
	void OnLeave(Role* pTarget);
	void OnTimer(Role* pTarget,float dt);
	void OnEvent(Role* pTarget,IStateEvent* event);
};


/***
 * 模块：角色状态
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：角色移动状态
 */
class MoveState : public IRoleState
{
public:
	MoveState() : IRoleState(RoleState_Move),m_fDelay(0.0f){}
	~MoveState(){}

	void OnEnter(Role* pTarget);
	void OnLeave(Role* pTarget);
	void OnTimer(Role* pTarget,float dt);
	void OnEvent(Role* pTarget,IStateEvent* event);

protected:
	float m_fDelay;
};

/***
 * 模块：角色状态
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：战斗待机状态
 */
class ReadyState : public IRoleState
{
public:
	ReadyState() : IRoleState(RoleState_Ready){}
	~ReadyState(){}

	void OnEnter(Role* pTarget);
	void OnLeave(Role* pTarget);
	void OnTimer(Role* pTarget,float dt);
	void OnEvent(Role* pTarget,IStateEvent* event);

private:
	float m_fDelayTime;
};

#endif	// __RoleState_h_
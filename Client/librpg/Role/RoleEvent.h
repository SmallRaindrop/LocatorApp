#pragma once

#include "StateMachine.h"

// 状态事件，状态机由事件驱动
enum RoleEvent
{
	RoleEvent_Move,
	RoleEvent_Attack,
	RoleEvent_AttackEnd,
	RoleEvent_Injured,
	RoleEvent_InjuredEnd,
};

struct MoveEvent : public IStateEvent
{
	MoveEvent(int x,int y) : IStateEvent(RoleEvent_Move){ destX = x; destY = y; }
	~MoveEvent(){}

	int destX;
	int destY;
};

struct AttackEvent : public IStateEvent
{
	AttackEvent(Role* target) : IStateEvent(RoleEvent_Attack){ _target = target; }
	~AttackEvent(){}

	Role* _target;
};

struct AttackEndEvent : public IStateEvent
{
	AttackEndEvent() : IStateEvent(RoleEvent_AttackEnd){ }
	~AttackEndEvent(){}
};

struct InjuredEvent : public IStateEvent
{
	InjuredEvent(Role* atker,float time,int damage) : IStateEvent(RoleEvent_Injured),_atker(atker),_time(time),_damage(damage){ }
	~InjuredEvent(){}

	Role* _atker;
	float _time;
	int _damage;
};

struct InjuredEndEvent : public IStateEvent
{
	InjuredEndEvent() : IStateEvent(RoleEvent_InjuredEnd){ }
	~InjuredEndEvent(){}
};
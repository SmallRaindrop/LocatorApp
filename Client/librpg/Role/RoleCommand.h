/***
 * 模块：角色指令
 * 作者：岳良友
 * 时间：2015-07-2
 * 说明：角色指令数据定义
 * 每个角色必须通过指令去控制其行为
 */

#pragma once

// 指令
enum RoleCommandType
{
	RoleCommand_None,
	RoleCommand_Move,	// 移动指令
	RoleCommand_Attack,	// 攻击目标指令
	RoleCommand_Skill,	// 使用技能指令
	RoleCommand_Pursue,	// 追击目标指令
};

struct RoleCommand
{
	int type;

	union
	{
		struct 
		{
			int x;
			int y;
		}pos;			// 移动指令参数 移动目标点

		struct
		{
			int		skillid;	// 技能ID
			__int64 targetid;	// 目标ID
		}skill;			// 技能指令参数 
		

	}param;
};
/***
 * 作者：岳良友
 * 时间：2015-07-2
 * 说明：角色身上状态相关，角色身上特效定义
 */

#ifndef __RoleStatus_h_
#define __RoleStatus_h_

enum RoleStatus
{
	RoleStatus_None = 0,		// 无状态
};

// 状态标志 最大支持32个状态；用于控制逻辑，buff用于表现
enum RoleStateFlag
{
	RoleStateFlag_0,			// 无
	RoleStateFlag_TeamLeader,	// 1. 队长
	RoleStateFlag_Protect,		// 2. PK保护
	RoleStateFlag_Invincible,	// 3. 无敌：状态，受到的所有攻击无效，进入无敌状态时清除并免疫自身所有减益BUFF
	RoleStateFlag_Void,			// 4. 虚化：状态，不会被任何单位选中，进入虚化状态时，移除并免疫所有自身减益buff
	RoleStateFlag_Coma,			// 5. 昏迷：状态，不能使用技能，道具，不能移动，不能躲闪，但是可以被击退和抓取效果作用
	RoleStateFlag_Deform,		// 6. 形变：状态，被改变外形，不能使用技能，物品，仍然可以移动，不能躲闪
	RoleStateFlag_Fixed,		// 7. 定身：状态，不能移动，但是可以被击退和抓取效果作用
	RoleStateFlag_Silence,		// 8. 沉默：状态，不能使用非普通攻击的技能
	RoleStateFlag_Disarm,		// 9. 缴械：状态，不能使用普通攻击，但是可以使用非普通攻击的技能
	RoleStateFlag_Fear,			// 10.恐惧，不受控制的随机移动，不能使用技能，道具
	RoleStateFlag_Dead,			// 11.死亡
	RoleStateFlag_DeadVirtual,	// 12.濒死
	RoleStateFlag_Help,			// 13.拯救
};

#define RoleAction_Stand		"stand"
#define RoleAction_Move			"walk"
#define RoleAction_Evade		"evade"
#define RoleAction_Chant		"chant"
#define RoleAction_Injured		"gethit"
#define RoleAction_Death		"death"
#define RoleAction_Skill1		"skill_1"
#define RoleAction_Skill2		"skill_2"
#define RoleAction_Skill3		"skill_3"
#define RoleAction_Skill4		"skill_4"
#define RoleAction_Skill5		"skill_5"
#define RoleAction_Skill6		"skill_6"
#define RoleAction_Skill7		"skill_7"

#define RoleAction string

#endif //__RoleStatus_h_
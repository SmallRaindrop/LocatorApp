#ifndef __SkillType_h_
#define __SkillType_h_

#include "GameDef.h"

#define Normal_Attack_ID		1001			// 普通攻击ID

enum SkillTargetType
{
	SkillTarget_None,			// 无需指定目标
	SkillTarget_Target,			// 指定目标
	SkillTarget_Point,			// 指定地图上逻辑点
	SkillTarget_Self,			// 对自身使用
};

enum SkillType
{
	Skill_Normal1 = 11,				// 普通攻击
	Skill_Normal2 = 12,				// 普通攻击
	Skill_Normal3 = 13,				// 普通攻击
	Skill_MultiArrow = 23,			// 多重箭
};

// 填法
//	效果id，生效条件，效果几率，效果目标，p1，p2，p3
//	生效条件
//	1 直接生效
//	2 击中
//	3 暴击
//	效果几率为0～10000，大于10000时计算几率=填写值*武器修正/8000
//
//	效果目标：
//	1 技能选择的目标
//	2 释放者自己
//
//	效果id：
//	1.冲锋瞬移，施法者传送到目标临近格子，p1 位移的速度
//	2.创建buff，p1-3 填写buffid
//	3.清除可移除的减益buff
//	4.陷阱 如火墙 p1为trap data id
//	5.发射子弹，只能用逻辑点，自身位置的技能使用 如p1为missile data id，p2 发射延时
//	6.硬直
//	7.每击杀一个目标减少该技能冷却，p1填写毫秒数
enum SkillSpecialEffectID
{
	SkillSpecialEffect_None,
	SkillSpecialEffect_Faward,		// 冲锋瞬移
 	SkillSpecialEffect_Buff,		// 加buff，p1-3 填写buffid
	SkillSpecialEffect_Clr,			// 清除可移除的减益buff
	SkillSpecialEffect_Trap,		// 陷阱 如火墙 p1为trap data id
	SkillSpecialEffect_Missile,		// 发射子弹 如p1为missile data id
	SkillSpecialEffect_Injured,		// 硬直
	SkillSpecialEffect_Reduce_Cd,	// 减少技能CD
};

enum SkillSpecialEffectCond
{
	SkillSpecialEffectCond_None,
	SkillSpecialEffectCond_Direct,	//	1 直接生效
	SkillSpecialEffectCond_Hit,		//	2 击中
	SkillSpecialEffectCond_Crit,	//	3 暴击
};

enum SkillSpecialEffectTarget
{
	SkillSpecialEffectTarget_None,
	SkillSpecialEffectTarget_Hit,	//	1 技能选择的目标
	SkillSpecialEffectTarget_Self,	//	2 释放者自己
};

//	效果id，生效条件，效果几率，效果目标，p1，p2，p3
struct SkillSpecialEffect
{
	int	id;
	int	cond;
	int rate;
	int target;
	int p1;
	int p2;
	int p3;
};

//第一个技能替换攻击按钮
#define Fir_Skill_ZS			(30)
#define Fir_Skill_FS			(14)
#define Fir_Skill_GJ			(22)


#endif //__SkillType_h_
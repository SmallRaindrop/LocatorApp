/***
 * 模块：SkillScript
 * 作者：岳良友
 * 时间：2015-07-2
 * 说明：技能逻辑处理
 * 每一种类型的技能都包含一个技能处理脚步，不同技能类型处理脚步不同
 */

#ifndef __SkillScript_h_
#define __SkillScript_h_

#include "GameDef.h"
#include "RoleFighter.h"

enum SkillFlag
{
	SkillFlag_None,			// 无
	SkillFlag_SpecialEffect,// 释放技能特殊效果处理
	SkillFlag_Chant,		// 吟唱
	SkillFlag_Precast,		// 前摇
	SkillFlag_Complete,		// 后摇
};

class SkillScript
{
public:
	SkillScript();
	~SkillScript();

	/* Name		：IsSpecialEffectImme
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否是立即执行的特殊效果
	 * Param	: val 指定效果ID
	 * Return	: true 立即执行，false 前摇结束执行
	 */
	bool IsSpecialEffectImme(SkillSpecialEffectID val);

	/* Name		：Execute
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 逻辑处理入口
	 * Param	: pFighter 施法者
	 * Return	: true 参数可以执行，false 参数不可以执行
	 */
	virtual bool Execute(RoleFighter* pFighter);

	/* Name		：ExecuteSpecialEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 特殊效果逻辑处理入口
	 * Param	: none
	 * Return	: void
	 */
	virtual void ExecuteSpecialEffect();

	/* Name		：Process
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 逻辑处理接口
	 * Param	: dt 时间戳
	 * Return	: true 处理已完成，false 处理需继续
	 */
	virtual bool Process(float dt);

	/* Name		：ProcessSpecialEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 处理技能特殊效果
	 * Param	: dt 时间戳
	 * Return	: true 处理已完成，false 处理需继续
	 */
	virtual bool ProcessSpecialEffect(float dt);

	/* Name		：ProcessChant
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 吟唱逻辑处理接口
	 * Param	: dt 时间戳
	 * Return	: true 处理已完成，false 处理需继续
	 */
	virtual bool ProcessChant(float dt);

	/* Name		：ProcessPrecast
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 前摇逻辑处理接口
	 * Param	: dt 时间戳
	 * Return	: true 处理已完成，false 处理需继续
	 */
	virtual bool ProcessPrecast(float dt);

	/* Name		：ProcessComplete
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 后摇逻辑处理接口
	 * Param	: dt 时间戳
	 * Return	: true 处理已完成，false 处理需继续
	 */
	virtual bool ProcessComplete(float dt);

	/* Name		：Abort
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 主动打断技能释放
	 * Param	: none
	 * Return	: void
	 */
	virtual void Abort();

	/* Name		：IsAbort
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 技能是否已经被终止
	 * Param	: none
	 * Return	: true 已终止，false 未终止
	 */
	virtual bool IsAbort();

	/* Name		：Chant
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 吟唱技能
	 * Param	: none
	 * Return	: void
	 */
	virtual void Chant();

	/* Name		：IsChant
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否在吟唱
	 * Param	: none
	 * Return	: true 在吟唱，false 未吟唱
	 */
	virtual bool IsChant();

	/* Name		：Precast
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 开始技能前摇
	 * Param	: none
	 * Return	: void
	 */
	virtual void Precast();

	/* Name		：IsPrecast
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否在技能前摇
	 * Param	: none
	 * Return	: void
	 */
	virtual bool IsPrecast();

	/* Name		：Complete
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 开始技能后摇
	 * Param	: none
	 * Return	: void
	 */
	virtual void Complete();

	/* Name		：IsComplete
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否在技能后摇
	 * Param	: none
	 * Return	: true 后摇，false 不是后摇
	 */
	virtual bool IsComplete();

private:
	vector<SkillSpecialEffect> m_vSpecialEffects;
	Effect*			m_pChantEffect;	// 吟唱特效
	Effect*			m_pCastEffect;	// 施法特效
	RoleFighter*	m_pCaster;		// 技能施法者对象指针
	union
	{
		RoleFighter* fighter;
		struct 
		{
			int cx;
			int cy;
		}pos;						// 目标点
	}Target;

	float m_fTimer;					// 历程计时器
	int m_nFlag;					// 历程标记
};

#endif //__SkillScript_h_
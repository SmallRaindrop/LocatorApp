/***
 * 模块：角色特效
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：与角色动作绑定的特效，8方向
 */

#ifndef __RoleEffect_h_
#define __RoleEffect_h_

#include "Effect.h"

enum RoleEffectType
{
	RoleEffect_None,
	RoleEffect_Miss,				// 闪避
	RoleEffect_Injured,				// 受伤
	RoleEffect_Dead,				// 死亡
	RoleEffect_Damage,				// 普通攻击伤害或者BUFF伤害
	RoleEffect_Crit,				// 暴击伤害或者技能伤害
	RoleEffect_Revive,				// 复活
	RoleEffect_LevelUP,				// 升级
	RoleEffect_RecoverHP,			// 技能和BUFF回血效果
	RoleEffect_RecoverMP,			// 技能和BUFF回魔效果
	RoleEffect_RecoverHP_Ball,		// 吃血球回血效果
	RoleEffect_RecoverMP_Ball,		// 吃法球回魔效果
	RoleEffect_HitBack,				// 击退效果
};

class Role;
class RoleEffect;
typedef vector<RoleEffect*> RoleEffectList;

class RoleEffect : public Effect
{
public:
	RoleEffect();
	~RoleEffect();

	CREATE_FUNC(RoleEffect);

	static RoleEffect* createWithDataID(Role* pRole,int dataid,const string& name);
	
	static int createRoleEffectListByConfig(Role* pRole,const string& config,RoleEffectList& list);

	/* Name		：onAnimationEnd
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 动画结束回调
	 * Param	: none
	 * Return	: void
	 */
	void onAnimationEnd();

	/* Name		：play
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 播放动画
	 * Param	: none
	 * Return	: void
	 */
	void play();

	void setScale(float scale);

	inline void setRole(Role* pRole){ m_pRole = pRole; }
	inline Role* getRole(){ return m_pRole; }

protected:
	Role* m_pRole;
};

#endif //__RoleEffect_h_
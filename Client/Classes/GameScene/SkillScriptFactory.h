/***
 * 模块：SkillScriptFactory
 * 作者：岳良友
 * 时间：2015-07-2
 * 说明：技能逻辑工厂
 * 每一种类型的技能都包含一个技能处理脚步，不同技能类型处理脚步不同
 */

#ifndef __SkillScriptFactory_h_
#define __SkillScriptFactory_h_

#include "SkillScript.h"

class SkillScriptFactory
{
public:
	SkillScriptFactory();
	~SkillScriptFactory();

	/* Name		：CreateScript
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 创建技能逻辑处理对象
	 * Param	: type 技能类型
	 * Return	: SkillScript*
	 */
	static SkillScript* CreateScript(SkillType type);
};

#endif //__SkillScriptFactory_h_
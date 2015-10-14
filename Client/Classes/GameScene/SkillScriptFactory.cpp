#include "SkillScriptFactory.h"

SkillScriptFactory::SkillScriptFactory()
{

}

SkillScriptFactory::~SkillScriptFactory()
{

}

SkillScript* SkillScriptFactory::CreateScript(SkillType type)
{
	switch (type)
	{
	case Skill_Normal1: return new SkillScript;
		break;
	case Skill_Normal2: return new SkillScript;
		break;
	case Skill_Normal3: return new SkillScript;
		break;
	case Skill_MultiArrow: return new SkillScript;
		break;
	default: 
		break;
	}

	return new SkillScript;
}
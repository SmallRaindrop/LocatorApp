#include "SkillScript.h"
#include "Hero.h"
#include "GameMap.h"
#include "CoCosAudioManager.h"
#include "CommonDef.h"

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
SkillScript::SkillScript() : m_pChantEffect(NULL),m_pCastEffect(NULL),
	m_pCaster(NULL),m_nFlag(SkillFlag_None),m_fTimer(0.0f)
{

}

SkillScript::~SkillScript()
{
	Abort();
}

bool SkillScript::IsSpecialEffectImme(SkillSpecialEffectID val)
{
	switch (val)
	{
	case SkillSpecialEffect_None:return true;
	case SkillSpecialEffect_Faward:
	case SkillSpecialEffect_Buff:
	case SkillSpecialEffect_Clr:
	case SkillSpecialEffect_Trap:
	case SkillSpecialEffect_Missile:
	case SkillSpecialEffect_Injured:
	case SkillSpecialEffect_Reduce_Cd:return false;
	default:
		break;
	}

	return false;
}

bool SkillScript::Execute(RoleFighter* pFighter)
{
	SkillCfg* pSkill = pFighter->GetActiveSkill();
	if ( !pSkill )
	{
		LOGE(" pFighter->GetActiveSkill() is null .");
		return false;
	}

	// 检查技能特殊效果配置
	m_vSpecialEffects.clear();
	if ( !pSkill->specialeffects.empty() )
	{
		vector<string> effectParamsList;
		vector<string> effectParams;
		StringUtil::StringSplit(pSkill->specialeffects,";",effectParamsList);
		for ( size_t i = 0;i<effectParamsList.size();++i )
		{
			if ( effectParamsList[i].empty() )
			{
				continue;
			}
			if( 7 != StringUtil::StringSplit(effectParamsList[i],",",effectParams) )
			{
				LOGE(" skill[%d] specialeffects[%s] error!",pSkill->id,pSkill->specialeffects.c_str());
				return false;
			}
			SkillSpecialEffect effect;
			effect.id = atoi(effectParams[0].c_str());
			effect.cond = atoi(effectParams[1].c_str());
			effect.rate = atoi(effectParams[2].c_str());
			effect.target = atoi(effectParams[3].c_str());
			effect.p1 = atoi(effectParams[4].c_str());
			effect.p2 = atoi(effectParams[5].c_str());
			effect.p3 = atoi(effectParams[6].c_str());
			m_vSpecialEffects.push_back(effect);
		}
	}

	switch ( pSkill->targettype )
	{
	case SkillTarget_Target:
		{
			RoleFighter* pTarget = GetMapRole(pFighter->GetTargetID());
			if ( !pTarget )
			{
				LOGE("pFighter->GetTargetID() is Not exist. targetID[%d]",pFighter->GetTargetID());
				return false;
			}
			Target.fighter = pTarget;
			Target.pos.cx = pTarget->GetCellX();
			Target.pos.cy = pTarget->GetCellY();
		}
		break;
	case SkillTarget_Point:
		{
			Target.fighter = NULL;
			pFighter->ConvertToCell(pFighter->GetTargetID(),Target.pos.cx,Target.pos.cy);
		}
		break;
	case SkillTarget_Self:
		{
			Target.fighter = pFighter;
			Target.pos.cx = pFighter->GetCellX();
			Target.pos.cy = pFighter->GetCellY();
		}
		break;
	default:
		break;
	}

	pFighter->FaceToTarget(Target.pos.cx,Target.pos.cy);
	m_pCaster = pFighter;

	ExecuteSpecialEffect();
	return true;
}

void SkillScript::ExecuteSpecialEffect()
{
	for ( vector<SkillSpecialEffect>::iterator itr = m_vSpecialEffects.begin();itr != m_vSpecialEffects.end();++itr )
	{
		SkillSpecialEffect effect = *itr;
		SkillSpecialEffectID id = SkillSpecialEffectID(effect.id);
		if ( (m_nFlag == SkillFlag_None && IsSpecialEffectImme(id)) || (m_nFlag != SkillFlag_None && !IsSpecialEffectImme(id)) )
		{
			continue;
		}
		switch (id)
		{
		case SkillSpecialEffect_None:
			break;
		case SkillSpecialEffect_Faward:
			{
				int distance = m_pCaster->GetDistanceTo(Target.pos.cx,Target.pos.cy);
				if ( distance > 1 )	// 大于该距离冲锋
				{
					m_pCaster->Forward(Target.pos.cx,Target.pos.cy);
					m_nFlag = SkillFlag_SpecialEffect;
				}
			}
			break;
		case SkillSpecialEffect_Buff:
			break;
		case SkillSpecialEffect_Clr:
			break;
		case SkillSpecialEffect_Trap:
			break;
		case SkillSpecialEffect_Missile:
			break;
		case SkillSpecialEffect_Injured:
			break;
		case SkillSpecialEffect_Reduce_Cd:
			break;
		default:
			break;
		}
	}
}

bool SkillScript::ProcessSpecialEffect(float dt)
{
	for ( vector<SkillSpecialEffect>::iterator itr = m_vSpecialEffects.begin();itr != m_vSpecialEffects.end();++itr )
	{
		SkillSpecialEffect effect = *itr;
		SkillSpecialEffectID id = SkillSpecialEffectID(effect.id);
		switch (id)
		{
		case SkillSpecialEffect_None:
			break;
		case SkillSpecialEffect_Faward:
			{
				// 处理冲锋
				if( m_pCaster->updateFlash(dt) )
				{
					return false;
				}
				else
				{
					m_pCaster->enableGhostShadow(false);
					Chant();
					return false;
				}
			}
			break;
		case SkillSpecialEffect_Buff:
			break;
		case SkillSpecialEffect_Clr:
			break;
		case SkillSpecialEffect_Trap:
			break;
		case SkillSpecialEffect_Missile:
			break;
		case SkillSpecialEffect_Injured:
			break;
		case SkillSpecialEffect_Reduce_Cd:
			break;
		default:
			break;
		}
	}

	return true;
}

bool SkillScript::Process(float dt)
{
	if ( IsAbort() )
	{
		return true;
	}

	if ( m_nFlag == SkillFlag_SpecialEffect )
	{
		ProcessSpecialEffect(dt);
		return false;
	}

	if ( m_nFlag == SkillFlag_None )
	{
		Chant();
		return false;
	}

	// 处理吟唱
	if ( IsChant() )
	{
		return ProcessChant(dt);
	}

	if ( IsPrecast() )
	{
		return ProcessPrecast(dt);
	}

	if ( IsComplete() )
	{
		return ProcessComplete(dt);
	}

	Abort();
	return true;
}

bool SkillScript::IsAbort()
{
	return m_pCaster == NULL;
}

void SkillScript::Abort()
{
	if ( m_pChantEffect )
	{
		m_pChantEffect->removeFromParent();
		m_pChantEffect = NULL;
	}

	if ( m_pCastEffect )
	{
		m_pCastEffect->removeFromParent();
		m_pCastEffect = NULL;
	}
	
	m_nFlag = SkillFlag_None;
	m_pCaster = NULL;
}

bool SkillScript::IsChant()
{
	return m_nFlag == SkillFlag_Chant;
}

void SkillScript::Chant()
{
	m_fTimer = 0.0f;
	m_nFlag = SkillFlag_Chant;

	// 无需吟唱的技能直接进入前摇
	Precast();
}

bool SkillScript::ProcessChant(float dt)
{
	return false;
}

bool SkillScript::IsPrecast()
{
	return m_nFlag == SkillFlag_Precast;
}

void SkillScript::Precast()
{
	SkillCfg* pSkillData = m_pCaster->GetActiveSkill();

	// 施法总时间
	int duration = pSkillData->animationstart+pSkillData->animationend;
	// 播放施法动作
	m_pCaster->playAction(m_pCaster->GetActiveSkill()->castanimation,duration,0);

	// 播放施法特效
	if ( !pSkillData->castart.empty() )
	{
		m_pCaster->ShowEffectAsync(pSkillData->castart);
	}
	
	// 播放施法音效
	gCocosAudio->PlayEffect(m_pCaster->GetActiveSkill()->sound);

	// 计时器清0
	m_fTimer = 0.0f;

	// 修改标记
	m_nFlag = SkillFlag_Precast;
}

bool SkillScript::ProcessPrecast(float dt)
{
	m_fTimer += dt;

	if ( m_fTimer*1000 > m_pCaster->GetActiveSkill()->animationstart )
	{
		Complete();
	}

	return false;
}

bool SkillScript::IsComplete()
{
	return m_nFlag == SkillFlag_Complete;
}

void SkillScript::Complete()
{
	m_fTimer = 0.0f;

	m_nFlag = SkillFlag_Complete;

	// 震动屏幕
	if ( m_pCaster == gHero && m_pCaster->GetActiveSkill()->id == 7502)
	{
		gMap->shake(0.0f,4.0f,0.1f,4);
	}
}

bool SkillScript::ProcessComplete(float dt)
{
	m_fTimer += dt;

	if ( m_fTimer*1000 > m_pCaster->GetActiveSkill()->animationend )
	{
		Abort();
		return true;
	}

	return false;
}
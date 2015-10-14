#include "RoleEffect.h"
#include "Role.h"

RoleEffect* RoleEffect::createWithDataID(Role* pRole,int dataid,const string& name)
{
	RoleEffect* effect = RoleEffect::create();
	if ( effect )
	{
		effect->setDataID(dataid);
		effect->setName(name);
		effect->setRole(pRole);
		effect->setLoop(0);
		return effect;
	} 

	CC_SAFE_RELEASE(effect);
	return nullptr;
}

int RoleEffect::createRoleEffectListByConfig(Role* pRole,const string& config,RoleEffectList& list)
{
	list.clear();
	vector<string> effects;
	StringUtil::StringSplit(config,";",effects);
	for (size_t i = 0; i < effects.size(); i++)
	{
		if ( effects[i].empty() )
		{
			continue;
		}

		vector<string> params;
		StringUtil::StringSplit(effects[i],",",params);
		if ( params.size() == 5 )
		{
			int dataid = atoi(params[0].c_str());
			string name = params[1];
			int hpt = atoi(params[2].c_str());
			float scale = (float)atoi(params[3].c_str()) / 100.0f;
			int zorder = atoi(params[4].c_str());

			RoleEffect* pEffect = RoleEffect::createWithDataID(pRole,dataid,name);
			if ( pEffect )
			{
				pEffect->setScale(scale);
				pEffect->setHungingPoint(hpt);
				pEffect->setLocalZOrder(zorder);
				list.push_back(pEffect);
			}
		}
		else
		{
			LOGE("effect config error! param[%s]",config.c_str());
		}
	}


	return (int)list.size();
}

RoleEffect::RoleEffect() : m_pRole(NULL)
{

}

RoleEffect::~RoleEffect()
{

}

void RoleEffect::onAnimationEnd()
{
	this->removeFromParent();
}

void RoleEffect::setScale(float scale)
{
	if ( !m_pRole )
	{
		return ;
	}

	Node::setScale(scale);

	if ( m_pRole->getDir() < Role::FACES )
	{
		this->setScaleX(scale);
	}
	else
	{
		this->setScaleX(-scale);
	}
}

void RoleEffect::play()
{
	if ( !m_pArmature || m_sName.empty() || !m_pRole )
	{
		return ;
	}
	
	__String effectName;
	if ( string::npos != m_sName.find("dir_") )
	{
		if ( m_pRole->getDir() < Role::FACES )
		{
			effectName.initWithFormat("%s_%d",m_sName.c_str(),m_pRole->getDir());
			this->setScaleX(fabs(getScaleX()));
		}
		else
		{
			effectName.initWithFormat("%s_%d",m_sName.c_str(),DIR_MAX-m_pRole->getDir());
			this->setScaleX(-fabs(getScaleX()));
		}

		if ( m_pRole->getDir() == DIR_N || 
			m_pRole->getDir() == DIR_NE ||
			m_pRole->getDir() == DIR_NW )
		{
			this->setLocalZOrder(-10);
		}
		else
		{
			this->setLocalZOrder(10);
		}
	}
	else
	{
		effectName.initWithFormat("%s",m_sName.c_str());
	}

	float scale = m_pRole->getArmor()->getAnimation()->getSpeedScale();
	int frame = m_pRole->getArmor()->getAnimation()->getCurrentFrameIndex();
	m_pArmature->getAnimation()->setSpeedScale(scale);
	m_pArmature->getAnimation()->play(effectName.getCString(),-1,m_nLoop);
	frame = frame < m_pArmature->getAnimation()->getRawDuration() ? frame : m_pArmature->getAnimation()->getRawDuration()-1;	
	m_pArmature->getAnimation()->gotoAndPlay(frame);
	float duration = (m_pArmature->getAnimation()->getRawDuration()-frame)/60.0f*scale;
	this->runAction(Sequence::create(DelayTime::create(duration),CallFunc::create( CC_CALLBACK_0(RoleEffect::onAnimationEnd,this)),NULL));
}
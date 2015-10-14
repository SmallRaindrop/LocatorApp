#include "Effect.h"
#include "ArmatureManager.h"

int Effect::GetEffectListByConfig(const string& config,EffectList& list)
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

			Effect* pEffect = Effect::createWithDataID(dataid,false);
			if ( pEffect )
			{
				pEffect->setName(name);
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

Effect::Effect() : m_nDataID(0),m_nLoop(-1),m_pArmature(NULL),m_fDuration(0),m_nSkinEffectType(SkinEffect_None)
{

}

Effect::~Effect()
{
	unloadData();
}

Effect* Effect::createWithDataID(int id,bool bLoop /* = false */)
{
	Effect* effect = Effect::create();
	if ( effect )
	{
		effect->setDataID(id);
		effect->setLoop(bLoop?-1:0);
		return effect;
	} 

	CC_SAFE_RELEASE(effect);
	return nullptr;
}

void Effect::setDataID(int dataid)
{
	m_nDataID = dataid;

	/*__String str;
	str.initWithFormat("assets/effect/%d.ExportJson",getDataID());

	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(str.getCString(), this, schedule_selector(Effect::onDataLoaded));*/
	gArmatureManager->loadArmatureFileForEffect(dataid,this);
}

void Effect::loadData(const char* name)
{
	unloadData();

	m_pArmature = gArmatureManager->getArmature(name);
	if ( m_pArmature )
	{
		m_pArmature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Effect::onAnimationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		m_pArmature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Effect::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		m_pArmature->setSkinEffect(m_nSkinEffectType);
		this->addChild(m_pArmature);
	}

	play();
}

void Effect::unloadData()
{
	if ( m_pArmature )
	{
		m_pArmature->stopAllActions();
		m_pArmature->getAnimation()->stop();
		m_pArmature->removeFromParent();
		m_pArmature = NULL;
	}
}

void Effect::onNotifyCenter(int msg)
{
	if ( msg == m_nDataID )
	{
		__String str;
		str.initWithFormat("%d",getDataID());
		loadData(str.getCString());
	}

	// 收到通知，释放自己一次
	this->release();
}


void Effect::onAnimationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID)
{
	if ( MovementEventType::COMPLETE == movementType )
	{
		setVisible(false);
	}

	if ( MovementEventType::LOOP_COMPLETE == movementType )
	{
		return;
	}
}

void Effect::onFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);

	vector<string> events;
	StringUtil::StringSplit(evt,";",events);

	for ( size_t i = 0;i<events.size(); ++i )
	{
		string event = events[i];
		if ( event == "sound" )
		{
			//SimpleAudioEngine::getInstance()->playEffect("skill_ban_yue_zhan.mp3");
		}
		if ( event == "damage" )
		{
			
		}
	}

}

void Effect::setDuration(float duration)
{
	m_fDuration = duration;

	if ( m_pArmature )
	{
		float scale = m_fDuration > 0 ? ((float)m_pArmature->getAnimation()->getRawDuration()/60.0f/(float)m_fDuration) : 1.0f;
		m_pArmature->getAnimation()->setSpeedScale(scale);
	}
}

void Effect::setSkinEffect(SkinEffectType type)
{
	if ( m_pArmature )
	{
		m_pArmature->setSkinEffect(type);
	}
}

void Effect::playWithName(const string& name,int loop /* = -1 */)
{
	setName(name);
	setLoop(loop);
	play();
}

void Effect::play()
{
	if ( m_pArmature && !m_sName.empty() )
	{
		float scale = m_fDuration > 0 ? ((float)m_pArmature->getAnimation()->getRawDuration()/60.0f/(float)m_fDuration) : 1.0f;
		m_pArmature->getAnimation()->setSpeedScale(scale);
		m_pArmature->getAnimation()->play(m_sName,-1,m_nLoop);
	}
}
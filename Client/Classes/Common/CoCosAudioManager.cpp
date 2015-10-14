#include "CocosAudioManager.h"
#include "GameScene/GameDataManager.h"
#include "SimpleAudioEngine.h"
#include "GameScene/Hero.h"

CoCosAudioManager::CoCosAudioManager()
{
	m_bMusicEnable = true;
	m_bEffectEnable = true;
}

CoCosAudioManager::~CoCosAudioManager()
{
	ClearAudioData();
}

void CoCosAudioManager::SetMusicEnable(bool enable)
{
	if (enable)
	{
		gCocosAudio->PlayMusic(gMap->getMapData()->sound,true);
	} 
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	m_bMusicEnable = enable;
}

void CoCosAudioManager::SetEffectEnable(bool enable)
{
	if(!enable)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	}
	m_bEffectEnable = enable;
}

void CoCosAudioManager::PlayMusic(std::string path, bool loop)
{
	if(!m_bMusicEnable) return;
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(path.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(path.c_str(),loop);
}

void CoCosAudioManager::PlayEffect(int id)
{
	if(!m_bEffectEnable) return;
	AudioCfg* pCfg = AudioData.get(id);
	if(!pCfg) return;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(pCfg->file.c_str());
}

void CoCosAudioManager::SetMusicVolume(float volume)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}

void CoCosAudioManager::SetEffectVolume(float volume)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
}

void CoCosAudioManager::PauseAll()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void CoCosAudioManager::ResumeAll()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void CoCosAudioManager::ClearAudioData()
{
	// move to Appdelegate.cpp
	//CocosDenshion::SimpleAudioEngine::getInstance()->end();
}
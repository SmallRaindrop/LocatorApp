#include "GameManager.h"
#include "GameScene.h"
#include "LoginScene.h"
#include "Hero.h"
#include "GameLayer.h"
#include "GameUILayer.h"
#include "GameTipsLayer.h"
#include "RoleTitleLayer.h"
#include "VersionManager.h"
#include "Net/NetDispatcher.h"
#include "GameDataManager.h"
#include "ResPlistManager.h"
#include "MemoryMonitor.h"
#include "UI/ResMgr/CtrlAllocator.h"
#include "UpdateScene.h"
#include "TaskMgr.h"
#include "MessageCenter.h"
#include "UI/GamePrompt.h"
#include "ArmatureManager.h"
#include "SysTipsMgr.h"
#include "GameEffectLayer.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <direct.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#endif
#include "Robot.h"
#include "UI/LoadingUI.h"
#include "cocostudio/CCActionManagerEx.h"
#include "cocostudio/CCSGUIReader.h"
#include "SimpleAudioEngine.h"
#include "RootScene.h"

GameManager::GameManager() : m_ServerID(0),m_ServerTime(0),m_AccountID(0),m_PlayerID(0),m_StateFlag(GS_None)
{

}

GameManager::~GameManager()
{

}

long GameManager::GetCurrTimeMS()
{
	struct timeval now;
	gettimeofday(&now, nullptr);
	long ret = now.tv_sec*1000 + now.tv_usec / 1000;
	return ret;
}

long long GameManager::GetCurrTimeMicroS()
{
	struct timeval now;
	gettimeofday(&now, nullptr);
	long long ret = now.tv_sec*1000000 + now.tv_usec;
	return ret;
}

bool GameManager::CreateDirectory(const string& path)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (_mkdir(path.c_str()) && (errno != EEXIST)) {
		CCLOG("Unable to create directory[%s]",path.c_str());
		return false;
	}
	return true;
#else
	mode_t processMask = umask(0);
	int ret = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	umask(processMask);
	if (ret != 0 && (errno != EEXIST))
	{
		CCLOG("Unable to create directory[%s]",path.c_str());
		return false;
	}
	return true;
#endif
}

void GameManager::RemoveDirectory(const string& path)
{
	string cmd = "rmdir -rf ";
	cmd += path;
	cmd.erase(cmd.begin()+cmd.length()-1);
	system(cmd.c_str());
}

void GameManager::LogMachineInfo()
{
	LOGI("machine vendor	: %s",m_MachineInfo._vendor.c_str());
	LOGI("machine num		: %s",m_MachineInfo._num.c_str());
	LOGI("machine os version: %s",m_MachineInfo._os.c_str());
	LOGI("machine cpu vendor: %s",m_MachineInfo._cpu_vendor.c_str());
	LOGI("machine cpu name	: %s",m_MachineInfo._cpu_name.c_str());
	LOGI("machine cpu abi	: %s",m_MachineInfo._cpu_abi.c_str());
}

bool GameManager::Preload()
{
	// 加载游戏配置数据
	if( !gGameData->LoadConfigs() )
	{
		return false;
	}

	// 所有单例创建
	gResThread;
	gPlistManager;
	gCtrlAllocator;
	gArmatureManager;
	gGameLayer;
	gBulletMgr;
	gJoyStick;
	gGameTipsLayer;
	gSysTipsMgr;
	gEffectLayer;
	gPromptCenter;
	gRoleTitleLayer;
	gGridsManager;
	gHero;
	gRobot;
	gGameUILayer;
	gLoadingUI;
	return true;
}

void GameManager::Start()
{
	LOGI("Game start");
	gDirector->runWithScene(gRootScene);
	gGameManager->EnterState(GS_Update);
}

void GameManager::Exit()
{
	gRootScene->replaceScene(nullptr);

	LeaveGame();

	// 删除资源包文件
	gFileUtils->deleteMPQ();

	// 所有单例销毁
	gUpdateManager->Destroy();
	gHero->Destroy();
	gRobot->Destroy();
	gGameLayer->Destroy();
	gLoadingUI->Destroy();
	gGameUILayer->Destroy();
	gGameTipsLayer->Destroy();
	gRoleTitleLayer->Destroy();
	gPromptCenter->Destroy();
	gCtrlAllocator->Destroy();
	gBulletMgr->Destroy();
	gJoyStick->Destroy();
	gSysTipsMgr->Destroy();
	gEffectLayer->Destroy();
	gGridsManager->Destroy();
	gPlistManager->Destroy();
	gResThread->Destroy();
	gArmatureManager->Destroy();
	ObjectFactory::destroyInstance();
	ActionManagerEx::destroyInstance();
	GUIReader::destroyInstance();
	DictionaryHelper::destroyInstance();

	gDirector->end();
	gDirector->mainLoop();
	CocosDenshion::SimpleAudioEngine::getInstance()->end();

	Configuration::destroyInstance();
	PoolManager::destroyInstance();
	ScriptEngineManager::destroyInstance();
}

void GameManager::EnterState(GameState gs)
{
	LeaveState();

	switch (gs)
	{
	case GS_None:
		break;
	case GS_Update:EnterUpdate();
		break;
	case GS_Login:EnterLogin();
		break;
	case GS_Game:EnterGame();
		break;
	default:
		break;
	}

	SetStateFlag(gs);
}

void GameManager::LeaveState()
{
	switch (m_StateFlag)
	{
	case GS_None:
		break;
	case GS_Update:LeaveUpdate();
		break;
	case GS_Login:LeaveLogin();
		break;
	case GS_Game:LeaveGame();
		break;
	default:
		break;
	}
}

void GameManager::EnterUpdate()
{
	gRootScene->replaceScene(CUpdateScene::create());
}

void GameManager::LeaveUpdate()
{
	if ( m_StateFlag == GS_Update )
	{
		gRootScene->replaceScene(nullptr);
		SetStateFlag(GS_None);
	}
}

void GameManager::EnterGame()
{
	LOGI("Game Scene start ...");
	gPromptCenter->Clear();
	gRootScene->replaceScene(CGameScene::create());
}

void GameManager::LeaveGame()
{
	if ( m_StateFlag == GS_Game )
	{
		gGameUILayer->removeChildByTag(Menu_Tag);
		gGameUILayer->removeChildByTag(Menu4Player_Tag);
		gPlistManager->clear();
		gTaskManager->Clear();
		gNetDispatcher->DisConnect();
		gNetDispatcher->Clear();

		gRootScene->replaceScene(nullptr);
		SetStateFlag(GS_None);
	}
}

void GameManager::EnterLogin()
{
	LOGI("Game Login Scene start ...");
	gRootScene->replaceScene(CLoginScene::create());
}

void GameManager::LeaveLogin()
{
	if ( m_StateFlag == GS_Login )
	{
		gRootScene->replaceScene(nullptr);
		SetStateFlag(GS_None);
	}
}
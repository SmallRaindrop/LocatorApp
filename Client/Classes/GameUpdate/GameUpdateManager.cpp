#include "GameUpdateManager.h"
#include "GameUpdate.h"
#include "GameUpdateUI.h"
#include "GameScene/RootScene.h"
#include "GameScene/GameManager.h"
#include "Log.h"

UpdateManager::UpdateManager() : StateMachine(this),m_pUpdateUI(nullptr),m_extension(-1)
{

}

UpdateManager::~UpdateManager()
{

}

bool UpdateManager::Initialize()
{
	InsertState(new CUpdateStart);
	InsertState(new CUpdateList);
	InsertState(new CUpdateSucc);
	InsertState(new CUpdateFail);

	// 更新文字集
	Data ret;
	ret = gFileUtils->getDataFromFile("update/updateString.bin");
	if ( ret.isNull() || !UpdateStringTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("load /update/updateString.bin failed.");
		return false;
	}
	LOGI("==========UpdateManager::Initialize===========");

	return true;
}

void UpdateManager::OpenUpdateUI()
{
	if ( m_pUpdateUI )
	{
		CloseUpdateUI();
	}

	m_pUpdateUI = GameUpdateUI::create();
	if ( m_pUpdateUI )
	{
		gRootScene->getCurrScene()->addChild(m_pUpdateUI);
	}
}

void UpdateManager::CloseUpdateUI()
{
	if ( m_pUpdateUI )
	{
		m_pUpdateUI->removeFromParent();
		m_pUpdateUI = nullptr;
	}
}

void UpdateManager::OnUpdateComplete()
{
	// 创建资源包文件
	if( !gFileUtils->createMPQ(gGameManager->GetMpqFile()) )
	{
		LOGE("create mpq package failed!");
		return ;
	}

	// 预加载
	if ( !gGameManager->Preload() )
	{
		SetPromptString("Game Init Failed!");
		return;
	}

	// 关闭更新界面
	CloseUpdateUI();

	// 进入登录界面
	gGameManager->EnterLogin();
}

string UpdateManager::GetUpdateString(int val)
{
	UpdateStringCfg* pItem = UpdateStringTable.get(val);
	if ( pItem )
	{
		return pItem->value;
	}

	return "";
}

void UpdateManager::SetPromptString(int code,...)
{
	string format = GetUpdateString(code);
	va_list l;
	va_start(l, code);

	char buf[1024] = {};
	vsnprintf(buf, sizeof(buf), format.c_str(), l);
	SetPromptString(buf);
}

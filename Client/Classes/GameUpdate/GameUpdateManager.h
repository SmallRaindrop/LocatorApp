#ifndef __GameUpdateManager_h_
#define __GameUpdateManager_h_

#include "GameDef.h"
#include "GameScene/db.h"
#include "cfgTable.h"
#include "StateMachine.h"
#include "GameUpdateUI.h"

class UpdateManager : public StateMachine<UpdateManager>,public Singleton<UpdateManager>
{
public:
	UpdateManager();
	~UpdateManager();

public:
	bool Initialize();

	string GetUpdateString(int val);
	void SetPromptString(int code,...);

	void OpenUpdateUI();
	void CloseUpdateUI();

	void OnUpdateComplete();

	inline void	SetPromptString(const string& str){ m_pUpdateUI->GetTipsLabel()->setString(str); }

	inline GameUpdateUI* GetUpdateUI(){ return m_pUpdateUI; }

	inline void		SetExtension(int ext){ m_extension = ext; }
	inline int		GetExtension(){ return m_extension; }

protected:
	CCfgTable<UpdateStringCfg>	UpdateStringTable;	// 文字信息表
	GameUpdateUI*	m_pUpdateUI;					// 更新界面

	int				m_extension;
};

#define gUpdateManager UpdateManager::Instance()

#endif
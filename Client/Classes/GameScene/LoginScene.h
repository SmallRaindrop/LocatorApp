#ifndef __LoginScene_h_
#define __LoginScene_h_

#include "GameDef.h"
#include "UI/GameUI.h"

typedef enum login_ui_type
{
	login_ui_login,
	login_ui_serverlist,
	login_ui_createplayer,
	login_ui_selectplayer,
	login_ui_count
}LoginUIType;

class LoginLayer : public Layer
{
public:
	LoginLayer();
	~LoginLayer();

	bool init();
	void update(float dt);

	GameUI* OpenUI(LoginUIType type);

	CREATE_FUNC(LoginLayer);
protected:
	LoginUIType m_curShowType;
public:
	GameUI*			 m_pLoginUIs[login_ui_count];
};

class CLoginScene : public Scene
{
public:
	CLoginScene();
	~CLoginScene();

	bool init();  
	void update(float delta);

	void onEnter();
	void onExit();

	CREATE_FUNC(CLoginScene);

public:
	static LoginLayer*	gLoginLayer;
};

#endif // __LoginScene_h_
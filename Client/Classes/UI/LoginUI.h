/***
 * 模块：登录界面
 * 作者：sndy
 * 时间：2015-07-22
 * 说明：登录界面修改
 */

#ifndef __LoginUI_h_
#define __LoginUI_h_

#include "GameDef.h"
#include "GameUI.h"

class LoginUI : public GameUI
{
public:
	LoginUI();
	~LoginUI();

	bool onInit();
	void onOpen();

	void login();
	void onLoginBtnClicked(Ref *pSender, TouchEventType type);
	void loadUserCfg(void);
	void saveUserCfg(void);

	CREATE_FUNC(LoginUI);

private:
	std::string m_acount;
};

#endif
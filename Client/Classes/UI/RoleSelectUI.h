#ifndef __RoleSelectUI_h_
#define __RoleSelectUI_h_

#include "GameDef.h"
#include "GameUI.h"

class RoleSelectUI : public GameUI
{
public:
	RoleSelectUI();
	~RoleSelectUI();

	bool onInit();

	void onEnterGameBtnClicked(Ref *pSender, TouchEventType type);

	CREATE_FUNC(RoleSelectUI);
};

#endif
#ifndef __GameScene_h_
#define __GameScene_h_

#include "GameDef.h"

class CGameScene : public Scene
{
public:
	CGameScene();
	~CGameScene();

	bool init();
	void onEnter();
	void onExit();
	void update(float delta);

	CREATE_FUNC(CGameScene);

protected:
	float m_fMemoryInterval;
};

#endif // __GameScene_h_
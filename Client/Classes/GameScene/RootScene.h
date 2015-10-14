#ifndef __RootScene_h_
#define __RootScene_h_

#include "GameDef.h"
#include "db.h"
#include "cfgTable.h"
#include "GameUpdate/GameUpdateManager.h"
#include "UI/GameUI.h"

#define FPS_INTERVAL	0.2f	// 每100毫秒统计一次帧率

class CRootScene : public Scene
{
public:
	CRootScene();
	~CRootScene();

	bool init();  
	void update(float delta);

	void updateFPS(float delta);

	inline Scene* getCurrScene(){ return m_pCurrScene; }

	void replaceScene(Scene* pScene);

	static CRootScene* getInstance();

	CREATE_FUNC(CRootScene);

protected:
	Label* m_pLabel;
	LayerColor* m_pLayerWhite;
	LayerColor* m_pLayerBlack;

	Scene*	m_pCurrScene;

	static CRootScene* s_pRootScene; 
};

#define gRootScene CRootScene::getInstance()

#endif // !__RootScene_h_


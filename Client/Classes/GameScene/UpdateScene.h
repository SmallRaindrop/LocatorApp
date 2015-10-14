#ifndef __UpdateScene_h_
#define __UpdateScene_h_

#include "GameDef.h"
#include "db.h"
#include "cfgTable.h"
#include "GameUpdate/GameUpdateManager.h"
#include "UI/GameUI.h"

class CUpdateScene : public Scene
{
public:
	CUpdateScene();
	~CUpdateScene();

	bool init();  
	void update(float delta);

	CREATE_FUNC(CUpdateScene);

	void onLogoEnded(Node* pLogo);

protected:
	Layer*			m_pLayer;
};

#endif // !__UpdateScene_h_


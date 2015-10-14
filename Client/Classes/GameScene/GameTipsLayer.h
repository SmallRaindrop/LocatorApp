#ifndef __GameTipsLayer_h_
#define __GameTipsLayer_h_

#include "GameDef.h"
#include "UI/GameUI.h"
#include "Singleton.h"

class CGameTipsLayer : public Layer,public Singleton<CGameTipsLayer>
{
public:
	CGameTipsLayer();
	~CGameTipsLayer();

	bool initialize(); 
};

#define gGameTipsLayer	CGameTipsLayer::Instance()

#endif // __GameTipsLayer_h_
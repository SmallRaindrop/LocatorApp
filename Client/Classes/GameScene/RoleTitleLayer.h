#ifndef __RoleTitleLayer_h_
#define __RoleTitleLayer_h_

#include "GameDef.h"
#include "UI/GameUI.h"
#include "Singleton.h"

class CRoleTitleLayer : public Layer,public Singleton<CRoleTitleLayer>
{
public:
	CRoleTitleLayer();
	~CRoleTitleLayer();
};

#define gRoleTitleLayer	CRoleTitleLayer::Instance()

#endif // __RoleTitle_h_
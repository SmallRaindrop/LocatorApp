#ifndef __PK_MODE_h_
#define __PK_MODE_h_

#include "GameDef.h"
#include "Singleton.h"

enum ePKMode
{
	PKM_PEACEFUL,
	PKM_GLOBAL,
	PKM_GUILD
};

enum ePKState
{
	PKS_WHITE,
	PKS_GRAY,
	PKS_RED,
	PKS_BLUE,
	PKS_GREEN,
	PKS_YELLOW
};

class CPKMode : public Singleton_Auto<CPKMode>
{
public:
	CPKMode()	{}
	~CPKMode()	{}

	bool CanIFightHim(class CPlayer*);
	ePKState GetHisPkState(class CPlayer*);

private:
};

#define gPKMode CPKMode::Instance()

#endif //__PK_MODE_h_
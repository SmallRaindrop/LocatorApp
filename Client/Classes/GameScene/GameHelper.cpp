#include "GameHelper.h"
#include "GameDef.h"


void GameHelper::SetWaitMsgLayer( bool _show )
{
	WaitMessageUI::getInstance()->setShow(_show);
}

GameHelper::GameHelper()
{

}

GameHelper::~GameHelper()
{

}

bool GameHelper::IsDoubleClicked()
{
	static long s_nClickTime = 0;
	bool ret = false ;
	long tNow = GetCurrTimeMS();
	if ( s_nClickTime == 0 )
	{
		s_nClickTime = tNow;
	}
	else
	{
		if ( tNow - s_nClickTime < 300 )
		{
			ret = true;
		}
		else
		{
			s_nClickTime = tNow;
			ret = false;
		}
	}

	return ret;
}


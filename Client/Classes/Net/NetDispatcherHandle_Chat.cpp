#include "GameDef.h"
#include "pk_chat.h"
#include "pk_item.h"
#include "GameScene/MessageCenter.h"
#include "Common/CommonDef.h"
#include "GameScene/Monster.h"
#include "GameScene/Hero.h"

namespace pk{

	bool OnGS2C_Monster_ChatMsg(GS2C_Monster_ChatMsg *value)
	{
		CMonster* pMonster = GetMapMonster(value->monsterId);
		if ( pMonster )
		{
			pMonster->ShowMonsterChat(value->strId,value->displayMs);

		}

		return true;
	}
}


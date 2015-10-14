#include "GameDef.h"
#include "pk_pet.h"
#include "pk_item.h"

namespace pk
{
	bool OnGS2C_PET_EXP_UPDATE(GS2C_PET_EXP_UPDATE* value)
	{
		return true;
	}

	bool OnGS2C_CALL_PET_Ret(GS2C_CALL_PET_Ret* value)
	{
		return true;
	}

	bool OnGS2C_CALL_BACK_PET_Ret(GS2C_CALL_BACK_PET_Ret* value)
	{
		return true;
	}
	
	bool OnGS2C_PET_MAP_UPDATE(GS2C_PET_MAP_UPDATE* value)
	{
		return true;
	}

	bool OnGS2C_PET_STRENG_Ret(GS2C_PET_STRENG_Ret* value)
	{
		return true;
	}

	bool OnGS2C_PET_FEED_Ret(GS2C_PET_FEED_Ret* value)
	{
		return true;
	}
}
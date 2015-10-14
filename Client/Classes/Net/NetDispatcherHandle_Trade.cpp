#include "pk_trade.h"
#include "pk_item.h"

namespace pk{

bool OnGS2C_DesPlayer_LockTrade_Result(GS2C_DesPlayer_LockTrade_Result *value)
{
	return true;
}

bool OnGS2C_InputItem_Result(GS2C_InputItem_Result* value)
{
	return true;
}

bool OnGS2C_InputItem(GS2C_InputItem* value)
{
	return true;
}

bool OnGS2C_RequestTrade(GS2C_RequestTrade *value)
{	
	return true;
}
bool OnGS2C_ReponseTrade_Result(GS2C_ReponseTrade_Result *value)
{
	return true;
}
bool OnGS2C_RequestTrade_Result(GS2C_RequestTrade_Result *value)
{
	return true;
}
bool OnGS2C_CannelTrade(GS2C_CannelTrade *value)
{
	return true;
}
bool OnGS2C_LockTrade_Result(GS2C_LockTrade_Result *value)
{
	return true;
}

bool OnGS2C_StartTrade(GS2C_StartTrade *value)
{
	return true;
}

bool OnGS2C_NpcShopBuy_Result(GS2C_NpcShopBuy_Result *value)
{
	return true;
}

bool OnGS2C_NpcShopSell_Result(GS2C_NpcShopSell_Result *value)
{
	return true;
}

bool OnGS2C_PortableShopBuy_Result(GS2C_PortableShopBuy_Result* value)
{
	return true;
}
	
}


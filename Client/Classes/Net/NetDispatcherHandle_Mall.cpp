#include "pk_mall.h"

namespace pk{

	bool OnGS2C_MallInfo(GS2C_MallInfo *value)
	{
		return true;
	}


	bool OnGS2C_MallHot9(GS2C_MallHot9 *value)
	{
		return true;
	}

	bool OnGS2C_MallLuckyPrice(GS2C_MallLuckyPrice *value)
	{
		return true;
	}

	bool OnGS2C_Common_Buy_Result(GS2C_Common_Buy_Result *value)
	{
		return true;
	}

	bool OnGS2C_Lucky_Buy_Result(GS2C_Lucky_Buy_Result *value)
	{
		return true;
	}

	bool OnGS2C_Mall_Refresh_Result(GS2C_Mall_Refresh_Result *value)
	{
		return true;
	}

	bool OnGS2C_vip_Buy_Result(struct GS2C_vip_Buy_Result *)
	{
		//must modify
		return true;
	}
}


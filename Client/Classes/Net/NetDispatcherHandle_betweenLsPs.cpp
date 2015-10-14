#include "pk_betweenLsPs.h"
 
namespace pk
{
	bool OnLS2PS_Register_Request(LS2PS_Register_Request* value)
	{
		 return true;
	}

	bool OnPS2LS_Register_Ret(PS2LS_Register_Ret* value)
	{

		return true;
	}

	bool OnPS2LS_PayInfo_Request(PS2LS_PayInfo_Request* value)
	{
		return true;
	}

	bool OnLS2PS_PayInfo_Ret(LS2PS_PayInfo_Ret* value)
	{

		return true;
	}

}


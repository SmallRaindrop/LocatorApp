#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_trade(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_RequestTrade);
 		CMD_DEAL(GS2C_ReponseTrade_Result);
 		CMD_DEAL(GS2C_RequestTrade_Result);
 		CMD_DEAL(GS2C_CannelTrade);
 		CMD_DEAL(GS2C_InputItem);
 		CMD_DEAL(GS2C_LockTrade_Result);
 		CMD_DEAL(GS2C_StartTrade);
 		CMD_DEAL(GS2C_NpcShopBuy_Result);
 		CMD_DEAL(GS2C_NpcShopSell_Result);
 		CMD_DEAL(GS2C_PortableShopBuy_Result);
 	END_DEAL();
	return false;
}

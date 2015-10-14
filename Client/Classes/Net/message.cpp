#include "NetMsg.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage(stNetMsg& msg) 
{
	int cmd = msg.command();
	int protocolStartIndex = cmd / 1000;
	switch(protocolStartIndex)
	{
	case 27 :
		return DoMessage_activeCenter(msg);
	case 21 :
		return DoMessage_trade(msg);
	case 18 :
		return DoMessage_mail(msg);
	case 26 :
		return DoMessage_mall(msg);
	case 24 :
		return DoMessage_sale(msg);
	case 29 :
		return DoMessage_achievement(msg);
	case 25 :
		return DoMessage_nonInGame(msg);
	case 17 :
		return DoMessage_friend(msg);
	case 14 :
		return DoMessage_move(msg);
	case 22 :
		return DoMessage_guild(msg);
	case 10 :
		return DoMessage_betweenClientLs(msg);
	case 23 :
		return DoMessage_task(msg);
	case 15 :
		return DoMessage_chat(msg);
	case 11 :
		return DoMessage_betweenLsGs(msg);
	case 19 :
		return DoMessage_team(msg);
	case 16 :
		return DoMessage_item(msg);
	case 28 :
		return DoMessage_battle(msg);
	case 30 :
		return DoMessage_pet(msg);
	case 31 :
		return DoMessage_betweenLsPs(msg);
	case 20 :
		return DoMessage_others(msg);
	case 13 :
		return DoMessage_map(msg);
	case 12 :
		return DoMessage_role(msg);
	default:
		break;
	}
	return false;
}

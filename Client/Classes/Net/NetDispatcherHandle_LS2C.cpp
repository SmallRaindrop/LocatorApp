#include "GameDef.h"
#include "pk_betweenClientLs.h"
#include "pk_betweenLsGs.h"
#include "GameScene/GameManager.h"
#include "NetDispatcher.h"
#include "VersionManager.h"
#include "pk_nonInGame.h"
#include "GameScene/LoginScene.h"
#include "UI/ServerList.h"
#include "GameScene/MessageCenter.h"

namespace pk{

	bool OnLS2C_Login_Ret(LS2C_Login_Ret* value)
	{
		switch (value->result)
		{
		case 0:
			{
				gGameManager->SetAccountID(value->userID);
				// 请求服务器列表
				C2LS_RequestGameServerList cmd;
				cmd.Send(gNetSocket);
			}
			break;
		case 1:
			gMessageCenter->SystemMessage(805);
			break;
		case 2:
			gMessageCenter->SystemMessage(806);
			break;
		case 3:
			gMessageCenter->SystemMessage(807);
			break;
		case 4:
			gMessageCenter->SystemMessage(808);
			break;
		case 5:
			gMessageCenter->SystemMessage(809);
			break;
		case 6:
			gMessageCenter->SystemMessage(810);
			break;
		case 7:
			gMessageCenter->SystemMessage(811);
			break;
		//错误信息处理
		case -1:
			gMessageCenter->SystemMessage(820);
			break;
		case -2:
			gMessageCenter->SystemMessage(821);
			break;
		case -3:
			gMessageCenter->SystemMessage(822);
			break;
		case -4:
			gMessageCenter->SystemMessage(823);
			break;
		case -5:
			gMessageCenter->SystemMessage(824);
			break;
		case -6:
			gMessageCenter->SystemMessage(825);
			break;
		case -7:
			gMessageCenter->SystemMessage(826);
			break;
		case -8:
			gMessageCenter->SystemMessage(827);
			break;
		case -9:
			gMessageCenter->SystemMessage(828);
			break;
		case -10:
			gMessageCenter->SystemMessage(829);
			break;
		case -11:
			gMessageCenter->SystemMessage(830);
			break;
		case -12:
			gMessageCenter->SystemMessage(831);
			break;
		case -13:
			gMessageCenter->SystemMessage(832);
			break;
		case -14:
			gMessageCenter->SystemMessage(833);
			break;
		}

		return true;
	}

	bool OnLS2C_GameServerList_Ret(LS2C_GameServerList_Ret* value)
	{
		if ( value->gameServers.size() > 0 )
		{
			CServerList* pServerList = (CServerList*)(CLoginScene::gLoginLayer->OpenUI(login_ui_serverlist));
			pServerList->Show(value->regionCnt,value->gameServers);
		}
		return true;
	}

	bool OnLS2C_SelGameServer_Ret(LS2C_SelGameServer_Ret* value)
	{
		gNetDispatcher->DisConnect();
		switch (value->retCode)
		{
		case 0:
			{
				if ( gNetDispatcher->Connect(value->ip,value->port) )
				{
					gNetDispatcher->SetLine(NetLine_Game);
					gGameManager->SetSign(value->sign);
					C2GS_Login cmd;
					cmd.accountID = gGameManager->GetAccountID();
					cmd.sign = value->sign;
					cmd.version = gGameVersion->lvd().pro;
					cmd.Send(gNetSocket);
				}
			}
			break;
		case 1:
			gMessageCenter->SystemMessage(835);
			break;
		case 2:
			gMessageCenter->SystemMessage(836);
			break;
		case 3:
			gMessageCenter->SystemMessage(837);
			break;
		default:
			break;
		}

		return true;
	}

	bool OnGS2LS_UserLogin(struct pk::GS2LS_UserLogin *value)
	{
		return true;
	}

	bool OnGS2LS_UserLogout(struct pk::GS2LS_UserLogout *value)
	{
		return true;
	}

	bool OnGS2LS_kickOutUser(struct pk::GS2LS_kickOutUser *value)
	{
		return true;
	}

	bool OnGS2LS_upadateOnlinePlayerCnt(GS2LS_upadateOnlinePlayerCnt* value)
	{
		return true;
	}
	bool OnLS2GS_Forbid_Chat_Request(LS2GS_Forbid_Chat_Request* value)
	{
		return true;
	}
	bool OnGS2LS_Forbid_Chat_Request_Ret(GS2LS_Forbid_Chat_Request_Ret* value)
	{
		return true;
	}
	bool OnLS2GS_SET_GM_Request(LS2GS_SET_GM_Request* value)
	{
		return true;
	}
	bool OnGS2LS_SET_GM_Request_Ret(GS2LS_SET_GM_Request_Ret* value)
	{
		return true;
	}



	bool OnLS2GS_UserKick(LS2GS_UserKick* value)
	{
		return true;
	}

	bool OnLS2GS_PayInfo_Request(struct pk::LS2GS_PayInfo_Request* value)
	{
		return true;
	}

	bool OnGS2LS_PayInfo_Ret(struct pk::GS2LS_PayInfo_Ret* value)
	{
		return true;
	}

	bool OnLS2GS_Kick_Player_Off_Request(struct pk::LS2GS_Kick_Player_Off_Request * value)
	{
		return true;
	}

	bool OnGS2LS_Kick_Player_Off_Ret(struct pk::GS2LS_Kick_Player_Off_Ret * value)
	{
		return true;
	}

	bool OnLS2GS_Announcement_Request(struct pk::LS2GS_Announcement_Request * value)
	{

		return true;
	}

	bool OnGS2LS_Announcement_Ret(struct pk::GS2LS_Announcement_Ret * value)
	{
		return true;
	}


	bool OnGS2LS_GetPlayerInfo_Ret(struct pk::GS2LS_GetPlayerInfo_Ret *value)
	{
		return true;
	}

	bool OnLS2GS_UserReadyToLogin(struct pk::LS2GS_UserReadyToLogin *value)
	{
		return true;
	}

	bool OnGS2LS_Register_Request(struct pk::GS2LS_Register_Request *value)
	{
		return true;
	}

	bool OnLS2GS_Register_Ret(struct pk::LS2GS_Register_Ret *value)
	{
		return true;
	}

	bool OnLS2GS_GetPlayerInfo_Request(LS2GS_GetPlayerInfo_Request* value)
	{
		return true;
	}
	bool OnLS2GS_GM_CMD_Request(LS2GS_GM_CMD_Request* value)
	{
		return true;
	}
	bool OnGS2LS_GM_CMD_Ret(GS2LS_GM_CMD_Ret* value)
	{
		return true;
	}


	bool OnLS2GS_control_activity_Request(LS2GS_control_activity_Request *value)
	{
		return true;
	}

	bool OnGS2LS_control_activity_Ret(GS2LS_control_activity_Ret *value)
	{
		return true;
	}

}


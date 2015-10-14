#include "GameDef.h"
#include "pk_nonInGame.h"
#include "pk_role.h"
#include "NetDispatcher.h"
#include "GameScene/Hero.h"
#include "GameScene/GameManager.h"
#include "GameScene/LoginScene.h"
#include "UI/SelectPlayer.h"
#include "GameScene/MessageCenter.h"

namespace pk{
	// pk_role
	bool OnGS2C_Login_Ret(GS2C_Login_Ret* value)
	{
		if ( value->retCode == 0 )
		{
			if (value->player_list.empty())
			{
				CSelectPlayer* pSelectPlayer = (CSelectPlayer*)CLoginScene::gLoginLayer->OpenUI(login_ui_createplayer);
			} 
			else
			{
				CSelectPlayer* pSelectPlayer = (CSelectPlayer*)CLoginScene::gLoginLayer->OpenUI(login_ui_selectplayer);
				pSelectPlayer->Show(value->player_list);
			}
		}
		return true;
	}

	bool OnGS2C_CreatePlayer_Ret(GS2C_CreatePlayer_Ret* value)
	{
		switch (value->retCode)
		{
		case 0:
			{
				if( value->player_list.size() > 0 )
				{
					CSelectPlayer* pSelectPlayer = (CSelectPlayer*)CLoginScene::gLoginLayer->OpenUI(login_ui_selectplayer);
					//pSelectPlayer->ShowAfterCreate(value->player_list);	
					//gMessageCenter->SystemMessage(800);
					gGameManager->SetPlayerID(value->player_list[0].playerID);
					gHero->SetId(value->player_list[0].playerID);
					gGameManager->EnterState(GS_Game);
				}
			}
			break;
		case 1:
			gMessageCenter->SystemMessage(801);
			break;
		case 2:
			gMessageCenter->SystemMessage(802);
			break;
		case 3:
			gMessageCenter->SystemMessage(803);
			break;
		case 4:
			gMessageCenter->SystemMessage(804);
			break;
		}
		return true;
	}

	bool OnGS2C_KickOut(GS2C_KickOut* value)
	{
		switch (value->type)
		{
		case 0:
			gMessageCenter->SystemMessage(838);
			break;
		case 1:
			gMessageCenter->SystemMessage(839);
			break;
		case 2:
			gMessageCenter->SystemMessage(840);
			break;
		case 3:
			gMessageCenter->SystemMessage(841);
			break;
		case 4:
			gMessageCenter->SystemMessage(842);
			break;
		case 5:
			gMessageCenter->SystemMessage(843);
			break;
		case 6:
			gMessageCenter->SystemMessage(844);
			break;
		default:
			break;
		}
		return true;
	}

	bool OnGS2C_ReturnToSelectRoleDlg_Ret(GS2C_ReturnToSelectRoleDlg_Ret * value)
	{
		return true;
	}


	bool  OnGS2C_SendPlayerDataComplete(GS2C_SendPlayerDataComplete *value)
	{
		return true;
	}

	bool OnGS2C_DeletePlayer_Ret(GS2C_DeletePlayer_Ret* value)
	{
		if ( value->retCode == 0 )
		{
			CSelectPlayer* pSelectPlayer = (CSelectPlayer*)CLoginScene::gLoginLayer->OpenUI(login_ui_selectplayer);
			pSelectPlayer->Show(value->player_list);
		}
		return true;
	}
}


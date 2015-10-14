#include "GameDef.h"
#include "pk_friend.h"
#include "Common/DataPool.h"
#include "UI/FriendUI.h"
#include "GameScene/MessageCenter.h"
#include "GameScene/GameUILayer.h"

extern const char *arrFriendTypes[4];
namespace pk{



	//bool OnFriend_Info(Friend_Info* value)
	//{
	//	return true;
	//}

	bool OnGS2C_All_Friend_Info(GS2C_All_Friend_Info* value)
	{
		if(value)
		{
			gDataPool->sapratePDataList(value->vec);
		}
		
		return true;
	}
	bool OnGS2C_Friend_Info(GS2C_Friend_Info* value)
	{
		if(value)
		{
			Friend_Info pData = value->st;
			switch (pData.type)
			{
			case 1:     //好友
				{
					Friend_Info* player = gDataPool->getFriendPlayerInfo( pData.playerId);
					if(player && player->online != pData.online)
					{
						gDataPool->setPListDataByPtr(gDataPool->getFriendList(), player);
						gDataPool->sortPlayerByOnline(gDataPool->getFriendList());
					}
					else if(!player)
					{
						gDataPool->getFriendList().push_back(pData);
						gDataPool->sortPlayerByOnline(gDataPool->getFriendList());
					}
					auto pFriendui = (FriendUI_cl*)(gGameUILayer->getUI(IDU_Friend));
					if(pFriendui)
					pFriendui->freshFriendList();
					break;
				}
			case 2:     //仇人
				break;
			case 3:     //黑名单
				{
					Friend_Info* player = gDataPool->getFriendPlayerInfo(pData.playerId);
					if(player)
					{
						gDataPool->deletePListDataByID(gDataPool->getFriendList(),  pData.playerId);
						gDataPool->getBlackList().push_back(pData);
						gDataPool->sortPlayerByOnline(gDataPool->getFriendList());
						gDataPool->sortPlayerByOnline(gDataPool->getBlackList());
					}
					auto pFriendui = (FriendUI_cl*)(gGameUILayer->getUI(IDU_Friend));
					if(pFriendui)
					{
						pFriendui->freshFriendList();
						pFriendui->freshBlackList();
					}
					
					break;
				}
			case 4:     //陌生人
				break;
			default:
				break;
			}
		}

		return true;
	}

	bool OnGS2C_Add_Friend_Result(GS2C_Add_Friend_Result* value)
	{
		return true;
	}
	
	bool OnGS2C_Remove_Friend_Result(GS2C_Remove_Friend_Result* value)
	{
		if(value && value->retCode == 1)   //删除成功
		{
			if(value->type == 1) //好友
			{
				gDataPool->deletePListDataByID(gDataPool->getFriendList(), value->playerId);
				auto pFriendui = (FriendUI_cl*)(gGameUILayer->getUI(IDU_Friend));
				pFriendui->freshFriendList();
			}
			else if(value->type == 3 )//黑名单
			{
				gDataPool->deletePListDataByID(gDataPool->getBlackList(), value->playerId);
				auto pFriendui = (FriendUI_cl*)(gGameUILayer->getUI(IDU_Friend));
				pFriendui->freshBlackList();
			}
			
		}
		else
		{
			gMessageCenter->SystemMessage(1109);
		}

		
		return true;
	}

	bool OnGS2C_Request_Friend_State_Result(GS2C_Request_Friend_State_Result* value)
	{
		return true;
	}

	bool OnGS2C_Palyer_Touch_List_Ret(GS2C_Palyer_Touch_List_Ret* value)
	{
		gDataPool->setRelativeList(value->player_list);
		auto pFriendui = (FriendUI_cl*)(gGameUILayer->getUI(IDU_Friend));
		if(pFriendui)
		pFriendui->freshRelativeList();
		return true;
	}
}


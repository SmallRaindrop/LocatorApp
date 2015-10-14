#include "FriendUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "DataPool.h"
#include "Net/pk_friend.h"
#include "GameScene/GameUILayer.h"
#include "Net/pk_team.h"
#include "Net/NetDispatcher.h"
#include "ChatMainUI.h"
#include "MessageBoxUI.h"

enum SelectBtn_TAG
{
	Friend_TAG,
	Black_TAG,
	Relative_TAG,
	Close_TAG,
};


FriendUI_cl::FriendUI_cl():GameUI(IDU_Friend, JSONFILE_FRIENDUI),
	m_index(0),
	m_curplayerid(0),
	m_curpname("")
{
	for (int i = 0; i < 3; i++)
	{
		m_selectbtn[i] = nullptr;
		m_pViewList[i] = nullptr;
		m_pBtnPanel[i] = nullptr;
		m_fpercent[i]  = 0.f;
		m_selectChild[i] = nullptr;
		m_selectPid[i] = 0;
		m_selectPname[i] = "";
	}
}

FriendUI_cl::~FriendUI_cl()
{
	
}


bool FriendUI_cl::onInit()
{
	if(m_pWidget)
	{
		for (int i = 0; i < 3; i++)
		{
			m_selectbtn[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, FORMAT_TO_STRING("Button_%d", i)));
			m_selectbtn[i]->addTouchEventListener(this, toucheventselector(FriendUI_cl::callBack)); 
			m_selectbtn[i]->setTag(i);
		}
		setSelectBtnByIdx(Friend_TAG);
		auto closebtn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget,"Button_close"));
		closebtn->setTag(Close_TAG);
		closebtn->addTouchEventListener(this, toucheventselector(FriendUI_cl::callBack));
		m_pSlider[Friend_TAG] = dynamic_cast<Slider*>(Helper::seekWidgetByName(m_pWidget, "Slider"));
		m_pSlider[Friend_TAG]->setEnabled(false);
		if(m_pSlider[Friend_TAG])
		{
			m_pSlider[Black_TAG] = dynamic_cast<Slider*>(m_pSlider[Friend_TAG]->clone());
			m_pSlider[Relative_TAG] = dynamic_cast<Slider*>(m_pSlider[Friend_TAG]->clone());
			m_pWidget->getChildByName("Panel_1")->addChild(m_pSlider[Black_TAG]);
			m_pWidget->getChildByName("Panel_1")->addChild(m_pSlider[Relative_TAG]);
		}
		m_pViewList[Friend_TAG] = dynamic_cast<ListView*>(Helper::seekWidgetByName(m_pWidget,"ListView_friend"));
		if(m_pViewList[Friend_TAG])
		{
			m_pViewList[Friend_TAG]->setItemsMargin(3.f);
			m_pViewList[Black_TAG] = dynamic_cast<ListView*>(m_pViewList[0]->clone());
			m_pViewList[Relative_TAG] = dynamic_cast<ListView*>(m_pViewList[0]->clone());
			m_pWidget->getChildByName("Panel_1")->addChild(m_pViewList[Black_TAG]);
			m_pWidget->getChildByName("Panel_1")->addChild(m_pViewList[Relative_TAG]);
		}

		m_pBtnPanel[Friend_TAG] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget,"Panel_fb"));
		if(m_pBtnPanel[Friend_TAG])
		{
			m_pBtnPanel[Friend_TAG]->setEnabled(true);
		}
		m_pBtnPanel[Black_TAG] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget,"Panel_bb"));
		if(m_pBtnPanel[Black_TAG])
		{
			m_pBtnPanel[Black_TAG]->setEnabled(false);
		}
		m_pBtnPanel[Relative_TAG] = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget,"Panel_rb"));
		if(m_pBtnPanel[Relative_TAG])
		{
			m_pBtnPanel[Relative_TAG]->setEnabled(false);
		}
		for (int i = 0; i < 5; i++)
		{
			auto fbtn = dynamic_cast<Button*>(m_pBtnPanel[Friend_TAG]->getChildByName(FORMAT_TO_STRING("Button_1%d",i)));
			if(fbtn)
			{
				fbtn->setTag(i);
				fbtn->addTouchEventListener(this, toucheventselector(FriendUI_cl::callBackFriendB));
			}
			auto bbtn = dynamic_cast<Button*>(m_pBtnPanel[Black_TAG]->getChildByName(FORMAT_TO_STRING("Button_2%d",i)));
			if(bbtn)
			{
				bbtn->setTag(i);
				bbtn->addTouchEventListener(this, toucheventselector(FriendUI_cl::callBackBlackB));
			}
			auto rbtn = dynamic_cast<Button*>(m_pBtnPanel[Relative_TAG]->getChildByName(FORMAT_TO_STRING("Button_3%d",i)));
			if(rbtn)
			{
				rbtn->setTag(i);
				rbtn->addTouchEventListener(this, toucheventselector(FriendUI_cl::callBackRelativeB));
			}
		}
	}
	return true;
}

void FriendUI_cl::onOpen()
{
	pk::C2GS_Palyer_Touch_List_Req cmd;
	for (auto iter: gDataPool->getRelativeMapData())
	{
		cmd.playerList.push_back(iter.first);
	}
	cmd.Send(gNetSocket);
	initBlackList();
	initFriendList();
	initRelativeList();
	setSelectBtnByIdx(0);
	setShowByIndex(0);
}

void FriendUI_cl::onClose()
{
	for (int i = 0; i < 3; i++)
	{
		m_fpercent[i]  = 0.f;
		m_selectChild[i] = nullptr;
		m_selectPid[i] = 0;
		m_selectPname[i] = "";
	}
}

void FriendUI_cl::setSelectBtnByIdx(int _idx)
{
	for (int i = 0; i < 3; i++)
	{
		if(m_selectbtn[i])
			m_selectbtn[i]->setButtonShowType(Normal_TYPE);
	}
	if(m_selectbtn[_idx])
	{
		m_selectbtn[_idx]->setButtonShowType(Press_TYPE);
	}
}

void FriendUI_cl::setChildShowDate(Widget * child, pk::Friend_Info* _info)
{
	if(child)
	{
		auto name = dynamic_cast<Text*>(child->getChildByName("Label_name"));
		auto level = dynamic_cast<Text*>(child->getChildByName("Label_leve"));
		auto bg = dynamic_cast<ImageView*>(child->getChildByName("Image_bg"));
		if(name)
		{
			name->setText(_info->name);
		}
		if(level)
		{
			level->setText(FORMAT_TO_STRING("%d", _info->level));
		}
		if(bg)
		{
			bg->setVisible(false);
		}
		child->setTag64(_info->playerId);
	}
}

void FriendUI_cl::setShowByIndex(int _index)
{
	for (int i = 0; i < 3; i++)
	{
		m_pBtnPanel[i]->setEnabled(false);
		m_pViewList[i]->setEnabled(false);
		m_pSlider[i]->setEnabled(false);
	}
	if(m_pViewList[_index] && m_pBtnPanel[_index])
	{
		m_pBtnPanel[_index]->setEnabled(true);
		m_pViewList[_index]->setEnabled(true);
		if(m_pSlider[_index])
		{
			m_pSlider[_index]->setEnabled(true);
			m_pSlider[_index]->setList(m_pViewList[_index], Slider::ListType::LISTVIEW_TYPE);
		}
		m_index = _index;
		m_curplayerid = m_selectPid[_index];
		m_curpname = m_selectPname[_index];
	}

}

void FriendUI_cl::initFriendList()
{
	if(m_pViewList[Friend_TAG])
	{
		m_pViewList[Friend_TAG]->removeAllItems();
		auto vlist = gDataPool->getFriendList();
		auto node  = GUIReader::getInstance()->widgetFromJsonFile(JSONFILE_FRICHILD);
		if(node)
		{
			for (auto iter: vlist)
			{
				auto child = node->clone();
				setChildShowDate(child, &iter);
				child->addTouchEventListener(this, toucheventselector(FriendUI_cl::callBackList));
				m_pViewList[Friend_TAG]->pushBackCustomItem(child);
			}
		}
	}
}

void FriendUI_cl::freshFriendList()
{
	m_selectChild[Friend_TAG] = nullptr;
	initFriendList();
	auto item = m_pViewList[Friend_TAG]->getItem(0);
	if(item)
	{
		m_selectPid[Friend_TAG] = item->getTag();
		m_selectPname[Friend_TAG] = ((Text*)item->getChildByName("Label_name"))->getStringValue();
	}
	else
	{
		m_selectPid[Friend_TAG] = 0;
		m_selectPname[Friend_TAG] = "";
	}
}

void FriendUI_cl::initBlackList()
{
	if(m_pViewList[Black_TAG])
	{
		m_pViewList[Black_TAG]->removeAllItems();
		auto vlist = gDataPool->getBlackList();
		auto node  = GUIReader::getInstance()->widgetFromJsonFile(JSONFILE_FRICHILD);
		if(node)
		{
			for(auto iter: vlist)
			{
				auto child = node->clone();
				setChildShowDate(child, &iter);
				child->addTouchEventListener(this, toucheventselector(FriendUI_cl::callBackList));
				m_pViewList[Black_TAG]->pushBackCustomItem(child);
			}
		}
	}
}

void FriendUI_cl::freshBlackList()
{
	m_selectChild[Black_TAG] = nullptr;
	initBlackList();
	auto item = m_pViewList[Black_TAG]->getItem(0);
	if(item)
	{
		m_selectPid[Black_TAG] = item->getTag();
		m_selectPname[Black_TAG] = ((Text*)item->getChildByName("Label_name"))->getStringValue();
	}
	else
	{
		m_selectPid[Black_TAG] = 0;
		m_selectPname[Black_TAG] = "";
	}
}

void FriendUI_cl::initRelativeList()
{
	if(m_pViewList[Relative_TAG])
	{
		m_pViewList[Relative_TAG]->removeAllItems();
		auto vlist = gDataPool->getRelativeList();
		auto node  = GUIReader::getInstance()->widgetFromJsonFile(JSONFILE_FRICHILD);
		if(node)
		{
			for (auto iter: vlist)
			{
				auto child = node->clone();
				setChildShowDate(child, &iter);
				child->addTouchEventListener(this, toucheventselector(FriendUI_cl::callBackList));
				m_pViewList[Relative_TAG]->pushBackCustomItem(child);
			}
		}

	}
}

void FriendUI_cl::freshRelativeList()
{
	m_selectChild[Relative_TAG] = nullptr;
	initRelativeList();
	auto item = m_pViewList[Relative_TAG]->getItem(0);
	if(item)
	{
		m_selectPid[Relative_TAG] = item->getTag();
		m_selectPname[Relative_TAG] = ((Text*)item->getChildByName("Label_name"))->getStringValue();
	}
	else
	{
		m_selectPid[Relative_TAG] = 0;
		m_selectPname[Relative_TAG] = "";
	}
}

void FriendUI_cl::callBack( Ref * pSender, TouchEventType _type )
{
	if(_type == TOUCH_EVENT_ENDED)
	{
		auto pBtn = dynamic_cast<Button*>(pSender);
		if(pBtn)
		{
			int tag = pBtn->getTag();
			switch (tag)
			{
			case Friend_TAG:
			case Black_TAG:
			case Relative_TAG:
				setSelectBtnByIdx(tag);
				setShowByIndex(tag);
				break;
			case Close_TAG:
				gGameUILayer->close(this);
				break;
			default:
				break;
			}
		}
	}
}

void FriendUI_cl::callBackFriendB( Ref * pSender, TouchEventType _type )
{
	if(_type == TOUCH_EVENT_ENDED)
	{
		if(m_curplayerid == 0)
			return;
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		switch (tag)
		{
		case 0:       //查看
			{
				pk::C2GS_LookOverPlayerEquip cmd = {m_curplayerid};
				cmd.Send(gNetSocket);
			}
			break;
		case 1:       //私聊
			{
				//显示一个私聊频道
				if(m_curplayerid != 0 && m_curpname != "")
				{
					ChatMainUI* pUI = (ChatMainUI*)gGameUILayer->open(IDU_CHATMAINUI);
					if(pUI) pUI->ShowPrivateChannel(m_curplayerid,m_curpname);
					auto player = gDataPool->getFriendPlayerInfo(m_curplayerid);
					if(player)
					{
						gDataPool->addPlayerToRecentList(player);
						gDataPool->sortPlayerByOnline(gDataPool->getRelativeList());
						freshRelativeList();
					}
				}
			}
			break;
		case 2:       //组队
			{
				pk::C2GS_InviteTeam_Req cmd = {m_curplayerid};
				cmd.Send(gNetSocket);
			}
			break; 
		case 3:       //删除
			{
				CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,FORMAT_TO_STRING(STR_IsDelFriend, m_curpname.c_str()),[&](bool type){
					if(type)
					{
						pk::C2GS_Remove_Friend cmd = {m_curplayerid, 1};
						cmd.Send(gNetSocket);
					}
				},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
					this,NULL,CMessageBoxUI::Scene_Game);	
			}
			break;
		case 4:       //拉黑
			{
				CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,FORMAT_TO_STRING(STR_IsAddBlackP, m_curpname.c_str()),[&](bool type){
					if(type)
					{
						pk::C2GS_Add_Friend cmd = {m_curplayerid, 3};
						cmd.Send(gNetSocket);
					}
				},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
					this,NULL,CMessageBoxUI::Scene_Game);	

			}
			break;
		default:
			break;
		}
	}
}

void FriendUI_cl::callBackBlackB( Ref * pSender, TouchEventType _type )
{
	if(_type == TOUCH_EVENT_ENDED)
	{
		if(m_curplayerid == 0)
			return;
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		switch (tag)
		{
		case 0:         //查看
			{
				pk::C2GS_LookOverPlayerEquip cmd = {m_curplayerid};
				cmd.Send(gNetSocket);
			}
			break;
		case 1:         //移除
			{
				CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,FORMAT_TO_STRING(STR_DelBlackPlayer, m_curpname.c_str()),[&](bool type){
					if(type)
					{
						pk::C2GS_Remove_Friend cmd = {m_curplayerid, 3};
						cmd.Send(gNetSocket);
					}
				},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
					this,NULL,CMessageBoxUI::Scene_Game);	
			}
			break;
		default:
			break;
		}
	}
}

void FriendUI_cl::callBackRelativeB( Ref * pSender, TouchEventType _type )
{
	if(_type == TOUCH_EVENT_ENDED)
	{
		if(m_curplayerid == 0)
			return;
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		switch (tag)
		{
		case 0:       //查看
			{
				pk::C2GS_LookOverPlayerEquip cmd = {m_curplayerid};
				cmd.Send(gNetSocket);
			}
			break;
		case 1:       //私聊
			{
				//显示一个私聊频道
				if(m_curplayerid != 0 && m_curpname != "")
				{
					ChatMainUI* pUI = (ChatMainUI*)gGameUILayer->open(IDU_CHATMAINUI);
					if(pUI) pUI->ShowPrivateChannel(m_curplayerid,m_curpname);
				}
			}
			break;
		case 2:       //组队
			{
				pk::C2GS_InviteTeam_Req cmd = {m_curplayerid};
				cmd.Send(gNetSocket);
			}
			break; 
		case 3:       //加好友
			{
				CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,FORMAT_TO_STRING(STR_IsAddFriend, m_curpname.c_str()),[&](bool type){
					if(type)
					{
						pk::C2GS_Add_Friend cmd = {m_curplayerid, 1};
						cmd.Send(gNetSocket);
					}
				},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
					this,NULL,CMessageBoxUI::Scene_Game);	
			}
			break;
		case 4:       //拉黑
			{
				CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,FORMAT_TO_STRING(STR_IsAddBlackP, m_curpname.c_str()),[&](bool type){
					if(type)
					{
						pk::C2GS_Add_Friend cmd = {m_curplayerid, 3};
						cmd.Send(gNetSocket);
					}
				},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
					this,NULL,CMessageBoxUI::Scene_Game);	
			}
			break;
		default:
			break;
		}
	}
}

void FriendUI_cl::callBackList( Ref * pSender, TouchEventType _type )
{
	if(_type == TOUCH_EVENT_ENDED)
	{
		if(m_selectChild[m_index])
		{
			m_selectChild[m_index]->getChildByName("Image_bg")->setVisible(false);
		}
		dynamic_cast<Widget*>(pSender)->getChildByName("Image_bg")->setVisible(true);
		m_selectChild[m_index] = dynamic_cast<Widget*>(pSender);
		m_curplayerid = m_selectChild[m_index]->getTag64();
		m_curpname = ((Text*)m_selectChild[m_index]->getChildByName("Label_name"))->getStringValue();
		m_selectPid[m_index] = m_curplayerid;
		m_selectPname[m_index] = m_curpname;
	}
}


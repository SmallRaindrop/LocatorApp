#include "UICheckBox.h"
#include "ChatMainUI.h"
#include "Net/pk_chat.h"
#include "Net/NetDispatcher.h"
#include "UIHelper.h"
#include "../GameScene/Hero.h"
#include "../GameScene/db.h"
#include "../GameScene/GameDataManager.h"
#include "CustomCtrl/RadioButtonSet.h"
#include "CustomCtrl/MenuForPlayer.h"
#include "UI/CustomCtrl/ScrollMsgWindow.h"
#include "UI/TeamUI.h"
#include "GameScene/GridsManager.h"
#include "CustomCtrl/ScrollList.h"
#include "SysTipsMgr.h"

void	MakeChatContent(RichText *pTextIn, MsgRecord* pMyRecord)
{
	int tag = 1;
	Color3B clrText = Color3B(0xde, 0xd1, 0xa4);
	pTextIn->setColor(clrText);
	//显示文本,物品链接,表情
	size_t nCurpos = 0;
	size_t nLastPos = 0;
	while(true)
	{
		if(nCurpos >= pMyRecord->strMsgServer.length()) break;

		size_t itemPos = pMyRecord->strMsgServer.find("&@ItemID=", nCurpos);
		size_t expressionPos = pMyRecord->strMsgServer.find("@E", nCurpos);
		size_t txtPos = nCurpos;
		Text *pItemLink = NULL;
		ImageView* pExpressionImg = NULL;
		if(itemPos == string::npos && expressionPos == string::npos) break;
		bool bHasAll = (itemPos!=string::npos&&expressionPos!=string::npos);
		if( expressionPos == string::npos || (bHasAll&&itemPos<expressionPos) )
		{
			txtPos = itemPos;
			int itemPosStart = itemPos+9;
			int itemPosEnd = pMyRecord->strMsgServer.find("&@", itemPosStart);
			nLastPos = itemPosEnd+2;
			bool hasItemLink = false;
			if (itemPosEnd != itemPosStart && itemPosEnd != string::npos)	//to do 判断物品链接长度 太长的是非法
			{
				int64 nItemID = StringConverter::toLongLong(pMyRecord->strMsgServer.substr(itemPosStart, itemPosEnd));
				for(unsigned int i=0; i<pMyRecord->vtrLinks.size(); ++i)
				{
					if(nItemID == pMyRecord->vtrLinks[i].nItemID)
					{
						pItemLink = Text::create();
						pItemLink->setFontSize(16);
						pItemLink->setText("[" + pMyRecord->vtrLinks[i].strName + "]");
						break;
					}
				}
			}
			if(itemPosEnd == string::npos || itemPosEnd == itemPosStart || !hasItemLink)
			{
				txtPos = itemPosStart;
				nLastPos = txtPos+1;
			}
		}
		else if(itemPos == string::npos || (bHasAll&&expressionPos<itemPos))
		{
			txtPos = expressionPos;
			int expressionPosStart = expressionPos+2;
			int expressionPosEnd = pMyRecord->strMsgServer.find("@", expressionPosStart);
			nLastPos = expressionPosEnd+1;
			bool hasExpression = false;
			if (expressionPosEnd != expressionPosStart && expressionPosEnd != string::npos) //to do 判断表情长度 太长的是非法
			{
				int nExpressionId = StringConverter::toInt(pMyRecord->strMsgServer.substr(expressionPosStart, expressionPosEnd));
				string filePath = CCString::createWithFormat("%s#%d.png",ICON_PATH_EXPRESSION,nExpressionId)->getCString();
				if(FileUtils::getInstance()->isFileExist(filePath))
				{
					pExpressionImg = ImageView::create(filePath);
					hasExpression = true;
				}
				else
				{
					hasExpression = true;
				}
			}
			if(expressionPosEnd == string::npos || expressionPosEnd == expressionPosStart || !hasExpression)
			{
				txtPos = expressionPosStart;
				nLastPos = txtPos+1;
			}
		}
		// 创建普通文本段
		if (nCurpos < txtPos)
		{
			RichElementText* textE = RichElementText::create(tag++, clrText, 255, pMyRecord->strMsgServer.substr(nCurpos, txtPos - nCurpos).c_str(), Default_Font_File, 16);
			pTextIn->pushBackElement(textE);
		}
		// 创建道具链接
		if(pItemLink)
		{
			RichElementCustomNode* textName = RichElementCustomNode::create(tag++, Color3B::GREEN, 255, pItemLink);
			pTextIn->pushBackElement(textName);
		}
		//创建表情
		if(pExpressionImg)
		{
			RichElementCustomNode* expressionImg = RichElementCustomNode::create(tag++, Color3B::GREEN, 255, pExpressionImg);
			pTextIn->pushBackElement(expressionImg);
		}
		nCurpos = nLastPos;
	}

	if (nCurpos < pMyRecord->strMsgServer.length())
	{
		RichElementText* textE = RichElementText::create(tag++, clrText, 255, pMyRecord->strMsgServer.substr(nCurpos).c_str(),Default_Font_File, 16);
		pTextIn->pushBackElement(textE);
	}
	pTextIn->formatText();
}

#define MAX_CHANEL_MSG 30
#define MAX_LATEST_MSG 10
#define ITEM_LINK_TEXT(T)	("[" + T + "]")


ChatMainUI:: ChatMainUI() : 
	GameUI(IDU_CHATMAINUI,JSONFILE_CHATMAINUI),
	m_nCurSeverChId(ChannelType_World),
	m_nCurClientChId(ChannelType_World),
	m_pChannelClose(NULL),m_pCursor(NULL)
{

}

ChatMainUI:: ~ChatMainUI()
{
	m_showingChannels.clear();
	m_pDisplayedInput->removeAllElements();	

	if ( m_pCursor )
	{
		m_pCursor->stopAllActions();
		m_pCursor->release();
	}
}

bool ChatMainUI::onInit()
{
	if (!GameUI::onInit())
	{
		return false;
	}
	Widget *pMain = Helper::seekWidgetByName(m_pWidget, "MsgParent");
	//最近消息
	m_pListBG = Helper::seekWidgetByName(m_pWidget, "Image_list");
	m_pLastMsgs = CScrollTable::create(false, "RecentChatBtn");
	m_pLastMsgs->setSize(Size(714, 196));
	m_pLastMsgs->setPosition(Point(0,0));
	m_pLastMsgs->SetFontSize(16);
	m_pLastMsgs->SetSelectEvent(this, SEL_SelListIndexEvent(&ChatMainUI::clickLatestMenu));
	m_pLastMsgs->SetFormat(TCT_NODE_PTR, 10, 0.5, 0.5,TCT_NONE);
	m_pListBG->addChild(m_pLastMsgs);
	m_pListBG->setEnabled(false);

	m_pNewMsgSign = Helper::seekWidgetByName(m_pWidget,"NewMsgCome");
	m_pNewMsgSign->setEnabled(false);

	Button *pClose	= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_Exit");
	Button *pSend	= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_Send");
	m_pLatest	= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_LatestMsgs");
	m_pVoice		= (Button*)Helper::seekWidgetByName(m_pWidget, "Button_Voice");
	pClose->addTouchEventListener(this, SEL_TouchEvent(&ChatMainUI::clickExit));
	pSend->addTouchEventListener(this, SEL_TouchEvent(&ChatMainUI::clickSendMsg));
	m_pLatest->addTouchEventListener(this, SEL_TouchEvent(&ChatMainUI::clickLatestMsg));
	m_pVoice->addTouchEventListener(this, SEL_TouchEvent(&ChatMainUI::clickVoice));

	m_pInput = (TextField*)Helper::seekWidgetByName(m_pWidget, "TextField_MsgInput");
	m_pInput->addEventListenerTextField(this, SEL_TextFieldEvent(&ChatMainUI::InputText));
	m_pInput->setVisible(false);
	m_pDisplayedInput = RichText::create();
	m_pDisplayedInput->ignoreContentAdaptWithSize(true);
	m_pDisplayedInput->setPosition(m_pInput->getPosition());

	m_pScrollEditBox = ScrollEditBox::create(m_pDisplayedInput);
	m_pScrollEditBox->setSize(m_pInput->getSize());
	m_pScrollEditBox->setPosition(Point(10, 10));
	m_pInput->getParent()->addChild(m_pScrollEditBox);

	// 光标
	m_pCursor = Text::create();
	m_pCursor->setFontSize(25);
	m_pCursor->setText("I");
	m_pCursor->runAction(RepeatForever::create(Blink::create(1.0f, 1)));
	m_pCursor->retain();

	//表情
	Button* pBtnExpression = (Button*)Helper::seekWidgetByName(m_pWidget,"Button_Expression");
	m_pExpressionUI = Helper::seekWidgetByName(m_pWidget,"Expression");
	pBtnExpression->addTouchEventListener(this,toucheventselector(ChatMainUI::showExpression));
	m_pExpressionUI->setEnabled(false);
	int i=0;
	while (true)
	{
		Button* pExpresstionItem = (Button*)Helper::seekWidgetByName(m_pExpressionUI,CCString::createWithFormat("E_%d",i)->getCString());
		if(!pExpresstionItem) break;
		pExpresstionItem->setTag(i+1);
		pExpresstionItem->addTouchEventListener(this,toucheventselector(ChatMainUI::clickExpressionItem));
		i++;
	}

	m_pMsgWind = CScrollMsgWindow::create();
	m_pMsgWind->SetLineInterval(20);
	m_pMsgWind->setSize(Size(1044, 358));
	m_pMsgWind->setPosition(Point(0, 0));
	m_pMsgWind->SetTouchNameListenner(this, (SEL_TouchNameLinkEvent)&ChatMainUI::clickNameLink);
	m_pMsgWind->SetTouchItemListenner(this, (SEL_TouchItemLinkEvent)&ChatMainUI::clickItemLink);
	pMain->addChild(m_pMsgWind);
	

	Widget* pChanelBg = Helper::seekWidgetByName(m_pWidget,"ChannelList");
	Button* pLeft = (Button*)Helper::seekWidgetByName(m_pWidget,"TurnLeft");
	Button* pRight = (Button*)Helper::seekWidgetByName(m_pWidget,"TurnRight");
	m_pChanelMenu = CScrollMenu::create(pChanelBg->getSize());
	m_pChanelMenu->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
	m_pChanelMenu->setLeftBtn(pLeft);
	m_pChanelMenu->setRightBtn(pRight);
	m_pChanelMenu->setInterval(6.0f);
	m_pChanelMenu->setButtonSize(Size(127,58));
	m_pChanelMenu->SetSelectEvent(this,SEL_SelectIndexEvent(&ChatMainUI::clickTab));
	pChanelBg->addChild(m_pChanelMenu);
	//增加5个固定频道
	CheckBox* pBox = (CheckBox*)gCtrlAllocator->LoadCtrl(CCString::createWithFormat("CheckBox_Ch1")->getCString());
	m_pChanelMenu->addMenu(pBox);
	pBox = (CheckBox*)gCtrlAllocator->LoadCtrl(CCString::createWithFormat("CheckBox_Ch5")->getCString());
	m_pChanelMenu->addMenu(pBox);
	//pBox = (CheckBox*)gCtrlAllocator->LoadCtrl(CCString::createWithFormat("CheckBox_Ch2")->getCString());
	//m_pChanelMenu->addMenu(pBox);
	//pBox = (CheckBox*)gCtrlAllocator->LoadCtrl(CCString::createWithFormat("CheckBox_Ch3")->getCString());
	//m_pChanelMenu->addMenu(pBox);
	pBox = (CheckBox*)gCtrlAllocator->LoadCtrl(CCString::createWithFormat("CheckBox_Ch8")->getCString());
	m_pChanelMenu->addMenu(pBox);

	m_showingChannels.push_back(ChannelType_World);
	m_showingChannels.push_back(ChannelType_System);
	//m_showingChannels[2] = ChannelType_Guild;
	//m_showingChannels[3] = ChannelType_Team;
	m_showingChannels.push_back(ChannelType_Team_Msg);
	m_pChanelMenu->clickButton(0);
	return true;
}

void ChatMainUI::onOpen()
{
	gSysTipsMgr->StopTipsAction(systype_chat);
	pk::C2GS_Request_Friend_State cmd;
	cmd.Send(gNetSocket);
}

void ChatMainUI::onClose()
{

}

void ChatMainUI::clickTab(int index)
{
	m_nChannelMenuIndex = index;
	m_nCurClientChId = m_showingChannels[m_nChannelMenuIndex];

	//客户端私聊频道未玩家ID
	if(m_nCurClientChId >= ChannelType_Count)
	{
		m_nCurSeverChId = ChannelType_Personal;
	}
	else
	{
		m_nCurSeverChId = (ChannelType)m_nCurClientChId;
	}

	UpdateCurChanel();
	updateChannelClose(index);
	showNewMsgSign();
	UpdateInputState();
}

void ChatMainUI::UpdateCurChanel()
{
	m_pMsgWind->Clear();
	Channel* pChannel = gChatDataMgr->GetChannel(m_nCurClientChId);
	if(pChannel)
	{
		for (size_t i = 0; i < pChannel->msg.size(); i++)
		{
			m_pMsgWind->PushMsg(&pChannel->msg[i].content,pChannel->msg[i].bIsMine);
		}
		pChannel->bUnread = false;
		TipsChannelUnread(pChannel);
	}
	m_pMsgWind->Flush(false);
}

void ChatMainUI::clickExit(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		gGameUILayer->close(this);
	}
}


void ChatMainUI::clickSendMsg(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		string tmp = m_pInput->getStringValue();
		if (tmp.empty())
			return;

		//玩家不能发送系统消息
		if(m_nCurSeverChId == ChannelType_System)
		{
			//清空记录
			m_pInput->setText("");
			//m_pDisplayedInput->removeAllElements();
			m_vtrItemsToSent.clear();
			return;
		}

		//私聊频道	目前私聊不支持物品链接
		if(m_nCurSeverChId == ChannelType_Personal)
		{
			Channel* pChannel = gChatDataMgr->GetChannel(m_nCurClientChId);
			if(!pChannel) return;

			pk::C2GS_Private_Chat cmd = {pChannel->channelId, tmp};
			cmd.Send(gNetSocket);

			pk::GS2C_Chat myChatContent = {ChannelType_Personal,0,pChannel->channelId,pChannel->playerName,tmp};
			gChatDataMgr->AddMsg(pChannel->channelId,myChatContent,true);
			m_pMsgWind->PushMsg(&myChatContent,true);
			m_pMsgWind->Flush();
		}
		else
		{
			//固定频道
			vector<pk::ItemLink> items;
			for (int i = (int)m_vtrItemsToSent.size() - 1; i >= 0; i--)
			{
				int nOffset = m_vtrItemsToSent[i].nStrOffset;

				CItem *pItem = gGridsManager->findItemInGrids(m_vtrItemsToSent[i].ePackType, m_vtrItemsToSent[i].nItemID);
				if (pItem == NULL)
					continue;

				if (nOffset == tmp.find(ITEM_LINK_TEXT(m_vtrItemsToSent[i].strName), nOffset))
				{
					// 服务器只有背包1.2.3三个type，装备type == 4 客户端的值为6
					pk::ItemLink link = {static_cast<int8>(m_vtrItemsToSent[i].ePackType == 6 ? 4 : m_vtrItemsToSent[i].ePackType), pItem->getId()};
					tmp.replace(nOffset, ITEM_LINK_TEXT(m_vtrItemsToSent[i].strName).length(), CCString::createWithFormat("%s%lld&@", "&@ItemID=", pItem->getId())->getCString());
					items.insert(items.begin(), link);
				}
			}

			pk::C2GS_Chat cmd = {(int8)m_nCurSeverChId, tmp, items};
			cmd.Send(gNetSocket);
		}

		//记录最近发送消息
		if (find(m_Latest.begin(), m_Latest.end(), MsgRecord(m_pInput->getStringValue(),tmp,m_vtrItemsToSent)) == m_Latest.end())
		{
			m_Latest.push_back(MsgRecord(m_pInput->getStringValue(),tmp,m_vtrItemsToSent));
			if (m_Latest.size() > MAX_LATEST_MSG)
			{
				m_Latest.erase(m_Latest.begin());
			}
		}
		//清空记录
		m_pInput->setText("");
		m_pDisplayedInput->removeAllElements();
		m_vtrItemsToSent.clear();
	}
}

void ChatMainUI::clickLatestMsg(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		m_pLatest->setFlippedY(!m_pLatest->isFlippedY());
		m_pListBG->setEnabled(!m_pListBG->isEnabled());

		if(m_pListBG->isEnabled())
		{
			m_pLastMsgs->Clear();
			for (size_t j = m_Latest.size(); j > 0; j--)
			{
				RichTextEx *pText = RichTextEx::create();
				pText->ignoreContentAdaptWithSize(false);
				pText->setSize(Size(714 - 20, 0));
				MakeChatContent(pText,&m_Latest[j - 1]);
				m_pLastMsgs->AddRow(j-1,pText);
				Size szMsg = pText->getVirtualRendererSize();
				pText->setPositionX(szMsg.width / 2 + 10);
			}
		}		
	}
}

void ChatMainUI::clickVoice(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		//to do 录音
	}
}

void ChatMainUI::showExpression(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		m_pExpressionUI->setEnabled(!m_pExpressionUI->isEnabled());
	}
}

void ChatMainUI::clickExpressionItem(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		//输入框添加表情
		int expressionIndex = ((Widget*)pSender)->getTag();
		string strExpression = CCString::createWithFormat("@E%d@",expressionIndex)->getCString();
		m_pInput->setText(m_pInput->getStringValue()+strExpression);
		UpdateDisplayedText(true);
	}
}

void ChatMainUI::closeExpression(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		m_pExpressionUI->setEnabled(false);
	}
}

void ChatMainUI::clickLatestMenu(int nIndex, long long data)
{
	int nRecentIndex = data;
	m_pInput->setText(m_Latest[nRecentIndex].strMsg);
	m_vtrItemsToSent = m_Latest[nRecentIndex].vtrLinks;
	UpdateDisplayedText(true);
}

void ChatMainUI::clickChanelMenu(int nIndex)
{

}

void ChatMainUI::clickNameLinkOfChanel(int nChanel, Ref* pSender, int64 id)
{
	if (id == gHero->GetId())
		return;

	if(id)// id==0 时是系统提示
	{
		CMenuForPerson::PopupMenu(Point(450, 500), 0, id, NULL, NULL, 
			CMenuForPerson::PO_EQUI, CMenuForPerson::PO_TEAM, 
			CMenuForPerson::PO_FRIEND,CMenuForPerson::PO_MSG,
			CMenuForPerson::PO_BLACKLIST, CMenuForPerson::PO_NAME_COPY, NULL);
		CMenuForPerson::s_nPlayerName = ((Text*)pSender)->getStringValue();
	}
	/*
	for (size_t i = 0; i < m_Msgs[m_nCurSeverChId].size(); i++)
	{
		if (id && m_Msgs[nChanel -1][i].senderId == id)		
		{
			CMenuForPerson::PopupMenu(Point(450, 500), 0, id, NULL, NULL, 
										CMenuForPerson::PO_EQUI, CMenuForPerson::PO_TEAM, 
										CMenuForPerson::PO_FRIEND,CMenuForPerson::PO_MSG,
										CMenuForPerson::PO_MASK, CMenuForPerson::PO_NAME_COPY, NULL);
			CMenuForPerson::s_nPlayerName = ((Text*)pSender)->getStringValue();
			break;
		}
	}
	*/
}

void ChatMainUI::clickItemLinkOfChanel(int nChanel, Ref* pSender, int64 id)
{
	for (size_t i = 0; i < m_Msgs[m_nCurSeverChId].size(); i++)
	{
		for (size_t j = 0; j < m_Msgs[nChanel -1][i].vec.size(); j++)
		if (m_Msgs[nChanel -1][i].vec[j].id == id)
		{
			ItemInfo info;
			info.id = id;
			info.dataId = m_Msgs[nChanel -1][i].vec[j].itemDataId;
			info.count = m_Msgs[nChanel -1][i].vec[j].count;
			info.isBind = (m_Msgs[nChanel -1][i].vec[j].isBind != 0);
			info.refineLevel = m_Msgs[nChanel -1][i].vec[j].refineLevel;
			info.enhanceLevel = m_Msgs[nChanel -1][i].vec[j].enhanceLevel;
			CItem *pItem = CItem::Create(info);
			//CTipsUI::showItemTips(getPositionInUILayer((Widget*)pSender), pItem);
			pItem->release();
			break;
		}
	}
}


void ChatMainUI::clickNameLink(Ref* pSender, int64 id)
{
	m_nCurClickPlayerID = id;
	clickNameLinkOfChanel(m_nCurSeverChId, pSender, id);
}

void ChatMainUI::clickItemLink(Ref* pSender, int64 id)
{
	clickItemLinkOfChanel(m_nCurSeverChId, pSender, id);
}

void ChatMainUI::clickNameLink4MainUI(Ref* pSender, int64 id)
{
	m_nCurClickPlayerID = id;
	clickNameLinkOfChanel(7, pSender, id);			// 7代表综合频道
}

void ChatMainUI::clickItemLink4MainUI(Ref* pSender, int64 id)
{
	clickItemLinkOfChanel(7, pSender, id);			// 7代表综合频道
}

void ChatMainUI::InputText(Ref*, TextFiledEventType type)
{
	switch (type)
	{
	case TEXTFIELD_EVENT_ATTACH_WITH_IME:
		{
			m_pInput->setEnabled(m_nCurClientChId != ChannelType_System);
			break;
		}
	case TEXTFIELD_EVENT_DELETE_BACKWARD:
	case TEXTFIELD_EVENT_INSERT_TEXT:
		{
			if(m_nCurClientChId != ChannelType_System)
			{
				UpdateDisplayedText(true);
			}
		}
		break;
	}
}

void ChatMainUI::UpdateDisplayedText(bool bHasCursor)
{
	string strText = m_pInput->getStringValue();

	m_pDisplayedInput->removeAllElements();

	// 有可能通过手机键盘已经删除了道具链接，也有可能在链接前面插入了文字，这里都需要刷新链接信息
	int nOffset = 0;
	for (vector<ItemLinkData>::iterator it = m_vtrItemsToSent.begin(); it != m_vtrItemsToSent.end();)
	{
		if ((nOffset = strText.find(ITEM_LINK_TEXT(it->strName), nOffset)) == string::npos)
		{
			it = m_vtrItemsToSent.erase(it);
			nOffset = 0;
		}
		else
		{
			it->nStrOffset = nOffset;
			it++;
		}
	}

	size_t nCommTextOffset = 0;
	int nTag = 1;
	for (size_t i = 0; i < m_vtrItemsToSent.size(); i++)
	{
		int nCommTextLen = m_vtrItemsToSent[i].nStrOffset - nCommTextOffset;
		if (nCommTextLen)
		{
			RichElementText* textE = RichElementText::create(nTag++, Color3B::WHITE, 255, strText.substr(nCommTextOffset, nCommTextLen).c_str(), Default_Font_File, 20);
			m_pDisplayedInput->pushBackElement(textE);
		}
		RichElementText* textE = RichElementText::create(nTag++, Color3B::GREEN, 255, ("[" + m_vtrItemsToSent[i].strName + "]").c_str(), Default_Font_File, 20);
		m_pDisplayedInput->pushBackElement(textE);

		nCommTextOffset = m_vtrItemsToSent[i].nStrOffset + m_vtrItemsToSent[i].strName.length() + 2;
	}
	if (nCommTextOffset < strText.length())
	{
		RichElementText* textE = RichElementText::create(nTag++, Color3B::WHITE, 255, strText.substr(nCommTextOffset).c_str(), Default_Font_File, 20);
		m_pDisplayedInput->pushBackElement(textE);
	}
	//光标
	if (bHasCursor)
	{
		RichElementCustomNode* cursor = RichElementCustomNode::create(nTag++, Color3B::WHITE, 255, m_pCursor);
		m_pDisplayedInput->pushBackElement(cursor);
	}

	m_pDisplayedInput->formatText();
	m_pScrollEditBox->update(0);
}

void ChatMainUI::UpdateInputState()
{
	if(m_nCurClientChId == ChannelType_System)
	{
		m_pInput->setTouchAreaEnabled(true);
		m_pDisplayedInput->removeAllElements();	
		RichElementText* textE = RichElementText::create(0, Color3B::RED, 255, STR_Chat_SystemCh_Tips, Default_Font_File, 20);
		m_pDisplayedInput->pushBackElement(textE);
		m_pDisplayedInput->formatText();
		m_pScrollEditBox->update(0);
	}
	else
	{
		m_pInput->setTouchAreaEnabled(false);
		UpdateDisplayedText(true);
	}
}

void ChatMainUI::InputItemLink(emGridsType type, CItem *pItem)
{
	string strTextNow = m_pInput->getStringValue();

	m_vtrItemsToSent.push_back(ItemLinkData(type, pItem->getId(), pItem->getItemData()->name, strTextNow.size()));
	strTextNow += ITEM_LINK_TEXT(pItem->getItemData()->name);
	//strTextNow += "#";		// 占位符，删除它等于删除整个道具链接

	m_pInput->setText(strTextNow);
	UpdateDisplayedText(true);
}

bool ChatMainUI::IsCurChannelMsg(pk::GS2C_Chat *value)
{
	if (value->channelId != ChannelType_Personal)
	{
		return m_nCurClientChId == value->channelId;
	}
	else
	{
		return m_nCurClientChId == value->senderId;
	}
}

void ChatMainUI::MsgArrive(MsgItem* pMsgItem)
{
	//当前正显示该频道，刷新
	if ((m_nCurSeverChId == pMsgItem->content.channelId) && pMsgItem)
	{
		m_pMsgWind->PushMsg(&pMsgItem->content,pMsgItem->bIsMine);
		m_pMsgWind->Flush(true);
	}
}

void ChatMainUI::AddFixChannel(ChannelType type)
{
	if(IsShowingChExist((int64)type))
	{
		return;
	}
	//增加5个固定频道
	CheckBox* pBox = (CheckBox*)gCtrlAllocator->LoadCtrl(CCString::createWithFormat("CheckBox_Ch%d",(int)type)->getCString());
	if(type == ChannelType_Guild)
	{
		m_pChanelMenu->insertMenu(pBox,2);
		m_showingChannels.insert(m_showingChannels.begin()+2,ChannelType_Guild);
	}
	else if(type == ChannelType_Team)
	{
		int nTeamMenuIndex = GetIndexByChannelId(ChannelType_Team_Msg);
		m_pChanelMenu->insertMenu(pBox,nTeamMenuIndex);
		m_showingChannels.insert(m_showingChannels.begin()+nTeamMenuIndex,ChannelType_Team);
	}
}

void ChatMainUI::CloseFixChanel(ChannelType type)
{
	if (!IsShowingChExist((int64)type))
	{
		return;
	}
	int nMenuIndex = GetIndexByChannelId((int64)type);
	m_pChanelMenu->remMenu(nMenuIndex);
	m_showingChannels.erase(m_showingChannels.begin()+nMenuIndex);
}

void ChatMainUI::ShowFixedChannel(ChannelType type)
{
	if(IsShowingChExist(type))
	{
		m_pChanelMenu->clickButton(GetIndexByChannelId(type));
	}
}

void ChatMainUI::PrivateMsgArrive(MsgItem* pMsgItem)
{
	//显示这个私聊频道
	AddPrivateChannel(pMsgItem->content.senderId,pMsgItem->content.senderName);

	//聊天界面未打开,来消息提示
	if (this->getState() != GUIS_OPEN)
	{
		gSysTipsMgr->RunTipsAction(systype_chat);
	}
	//正显示这个私聊频道 刷新
	else if(m_nCurClientChId == pMsgItem->content.senderId)
	{
		m_pMsgWind->PushMsg(&pMsgItem->content,pMsgItem->bIsMine);
		m_pMsgWind->Flush();
		gChatDataMgr->SetChannelReaded(pMsgItem->content.senderId, true);
	}
	TipsChannelUnread(gChatDataMgr->GetChannel(pMsgItem->content.senderId));
	showNewMsgSign();
	gCocosAudio->PlayEffect(64);
}

void ChatMainUI::closePrivateChannel(Ref* pSender, TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		int64 nChannelId = ((Widget*)pSender)->getTag64();
		int nMenuIndex = GetIndexByChannelId(nChannelId);
		//显示前一个频道
		m_pChanelMenu->clickButton(nMenuIndex-1);
		m_pChanelMenu->remMenu(nMenuIndex);
		m_showingChannels.erase(m_showingChannels.begin()+nMenuIndex);
	}
}

void ChatMainUI::AddPrivateChannel(int64 channelId,string playerName)
{
	if(IsShowingChExist(channelId))
	{
		return;
	}

	CheckBox* pBox = (CheckBox*)gCtrlAllocator->LoadCtrl(CCString::createWithFormat("CheckBox_Ch_Private")->getCString());
	if(!pBox) return;
	Text* pPlayerName = (Text*)pBox->getChildByName("Title");
	Button* pClose = (Button*)pBox->getChildByName("Close");
	pPlayerName->setText(WrapLongName(playerName));
	pPlayerName->setFontSize(16);
	pClose->setEnabled(false);
	pClose->setTag64(channelId);
	pClose->addTouchEventListener(this,toucheventselector(ChatMainUI::closePrivateChannel));
	m_pChanelMenu->addMenu(pBox);
	m_showingChannels.push_back(channelId);
	gChatDataMgr->AddChannel(channelId,playerName);
}

bool ChatMainUI::IsShowingChExist(int64 channelId)
{
	for (unsigned int i=0; i<m_showingChannels.size(); ++i)
	{
		if(m_showingChannels[i] == channelId)
			return true;
	}
	return false;
}

int	ChatMainUI::GetIndexByChannelId(int64 channelId)
{
	for (unsigned int i=0; i<m_showingChannels.size(); ++i)
	{
		if(m_showingChannels[i] == channelId)
			return i;
	}
	return -1;
}

void ChatMainUI::ShowPrivateChannel(int64 channelId,string playerName)
{
	AddPrivateChannel(channelId,playerName);
	m_pChanelMenu->clickButton(GetIndexByChannelId(channelId));
}

void ChatMainUI::TipsChannelUnread(Channel* pChannel)
{
	//非私聊不闪烁
	if(pChannel->channelId <= ChannelType_Count) return;

	int nMenuIndex = GetIndexByChannelId(pChannel->channelId);
	vector<CheckBox*>& pBoxs = m_pChanelMenu->GetButtons();
	CheckBox* pBox = pBoxs[nMenuIndex];
	Text* pPlayerName = (Text*)pBox->getChildByName("Title");
	pPlayerName->stopAllActions();
	pPlayerName->setVisible(true);
	pPlayerName->setEnabled(true);
	if(pChannel->bUnread)
	{
		pPlayerName->runAction(RepeatForever::create(Blink::create(1.0f, 1)));
	}
}

void ChatMainUI::updateChannelClose(int menuIndex)
{
	vector<CheckBox*>& pBoxs = m_pChanelMenu->GetButtons();
	CheckBox* pBox = pBoxs[menuIndex];
	Button* pClose = (Button*)pBox->getChildByName("Close");

	if(m_pChannelClose)
		m_pChannelClose->setEnabled(false);

	//固定频道没有关闭按钮
	if(m_showingChannels[menuIndex]<=ChannelType_Count)
	{
		m_pChannelClose = NULL;
	}
	else
	{
		pClose->setEnabled(true);
		m_pChannelClose = (Widget*)(pClose);
	}
}

void ChatMainUI::showNewMsgSign()
{
	if(gChatDataMgr->GetUnreadChannelNum())
		m_pNewMsgSign->setEnabled(true);
	else
		m_pNewMsgSign->setEnabled(false);
}
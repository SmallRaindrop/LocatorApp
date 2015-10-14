#include "ScrollMsgWindow.h"
#include "UnderLinedText.h"
#include "RichTextEX.h"
#include "GameScene/GameDataManager.h"
#include "StringConverter.h"
#include "UI/ResMgr/CtrlAllocator.h"
#include "GameScene/Hero.h"
#include "UI/ChatMainUI.h"

Color3B clr4chs[8] = {Color3B(0xde, 0xd1, 0xa4), Color3B(0xde, 0xd1, 0xa4), Color3B(0xde, 0xd1, 0xa4), 
					  Color3B(0xde, 0xd1, 0xa4), Color3B(0xfe, 0x28, 0x28), Color3B(0xde, 0xd1, 0xa4),
					Color3B(0xde, 0xd1, 0xa4),Color3B(0xde, 0xd1, 0xa4)};

vector<pair<Ref*, int64>> MakeChatSentence(CScrollMsgWindow *pWindow, RichText *pTextIn, const pk::GS2C_Chat *msg, bool bMyWords)
{
	int tag = 1;
	vector<pair<Ref*, int64>> links;
	Color3B clrText = clr4chs[msg->channelId - 1];
	pTextIn->setColor(clrText);

	//频道标题
	/*
	Widget *pCh = gCtrlAllocator->LoadCtrl(CCString::createWithFormat("CheckBox_Ch%d",msg->channelId)->getCString());
	if (pCh)
	{
		pCh->setSize(Size(100,30));
		RichElementCustomNode* textCh = RichElementCustomNode::create(tag++, Color3B::WHITE, 255, pCh);
		pTextIn->pushBackElement(textCh);
	}
	*/
	if (msg->channelId == ChannelType_System)
	{
		// 系统
		RichElement* SysTemTitle = RichElementText::create(tag++, clrText, 255, STR_CHAT_XITONG, Default_Font_File, 16);
		pTextIn->pushBackElement(SysTemTitle);
	}
	else if (msg->channelId == ChannelType_Personal)
	{
		//玩家名字
		UnderlinedText*	pNameLink = UnderlinedText::create((msg->senderName).c_str());
		pNameLink->setColor(Color3B(0xff,0xff,0xff));
		pNameLink->setFontSize(16);
		pNameLink->addTouchEventListener(pWindow, SEL_TouchEvent(&CScrollMsgWindow::ClickName));
		links.push_back(make_pair(pNameLink, msg->senderId));
		if(bMyWords)
		{
			RichElement* pYou2Other1 = RichElementText::create(tag++, clrText, 255, STR_Chat_You2OOther1, Default_Font_File, 16);
			pTextIn->pushBackElement(pYou2Other1);
			RichElementCustomNode* textName = RichElementCustomNode::create(tag++, clrText, 255, pNameLink);
			pTextIn->pushBackElement(textName);
			RichElement* pYou2Other2 = RichElementText::create(tag++, clrText, 255, STR_Chat_You2OOther2, Default_Font_File, 16);
			pTextIn->pushBackElement(pYou2Other2);
		}
		else
		{
			RichElementCustomNode* textName = RichElementCustomNode::create(tag++, clrText, 255, pNameLink);
			pTextIn->pushBackElement(textName);
			RichElement* pOther2You = RichElementText::create(tag++, clrText, 255, STR_Chat_Other2You, Default_Font_File, 16);
			pTextIn->pushBackElement(pOther2You);
		}
		//冒号
		RichElement* colon = RichElementText::create(tag++, clrText, 255, " : ", Default_Font_File, 16);
		pTextIn->pushBackElement(colon);
	}
	else
	{
		//发送者名字
		UnderlinedText*	pNameLink = UnderlinedText::create((msg->senderName).c_str());
		pNameLink->setColor(msg->senderName==gHero->GetRoleName()?Color3B(0x38,0xf1,0x0d):Color3B(0xff,0xff,0xff));
		pNameLink->setFontSize(16);
		pNameLink->addTouchEventListener(pWindow, SEL_TouchEvent(&CScrollMsgWindow::ClickName));
		links.push_back(make_pair(pNameLink, msg->senderId));
		RichElementCustomNode* textName = RichElementCustomNode::create(tag++, clrText, 255, pNameLink);
		pTextIn->pushBackElement(textName);
		//冒号
		RichElement* colon = RichElementText::create(tag++, clrText, 255, " : ", Default_Font_File, 16);
		pTextIn->pushBackElement(colon);
	}

	//显示文本,物品链接,表情
	int nCurpos = 0;
	int nLastPos = 0;
	while(true)
	{
		if(nCurpos >= msg->message.length()) break;

		int itemPos = msg->message.find("&@ItemID=", nCurpos);
		int expressionPos = msg->message.find("@E", nCurpos);
		int txtPos = nCurpos;
		Text *pItemLink = NULL;
		ImageView* pExpressionImg = NULL;
		if(itemPos == string::npos && expressionPos == string::npos) break;
		bool bHasAll = (itemPos!=string::npos&&expressionPos!=string::npos);
		if( expressionPos == string::npos || (bHasAll&&itemPos<expressionPos) )
		{
			txtPos = itemPos;
			int itemPosStart = itemPos+9;
			int itemPosEnd = msg->message.find("&@", itemPosStart);
			nLastPos = itemPosEnd+2;
			bool hasItemLink = false;
			if (itemPosEnd != itemPosStart && itemPosEnd != string::npos)	//to do 判断物品链接长度 太长的是非法
			{
				int64 nItemID = StringConverter::toLongLong(msg->message.substr(itemPosStart, itemPosEnd));
				for(unsigned int i=0; i<msg->vec.size(); ++i)
				{
					if(nItemID == msg->vec[i].id)
					{
						pItemLink = Text::create();
						ItemCfg *pItem = ItemData.get(msg->vec[i].itemDataId);
						pItemLink->setColor(pItem ? GetQualityColor(ItemQualityType(pItem->quality)) : Color3B::GREEN);
						pItemLink->setFontSize(16);
						pItemLink->setText("[" + ItemData.get(msg->vec[i].itemDataId)->name + "]");
						pItemLink->setTouchEnabled(true);
						pItemLink->addTouchEventListener(pWindow, SEL_TouchEvent(&CScrollMsgWindow::ClickItem));
						links.push_back(make_pair(pItemLink, msg->vec[i].id));
						hasItemLink = true;
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
			int expressionPosEnd = msg->message.find("@", expressionPosStart);
			nLastPos = expressionPosEnd+1;
			bool hasExpression = false;
			if (expressionPosEnd != expressionPosStart && expressionPosEnd != string::npos) //to do 判断表情长度 太长的是非法
			{
				int nExpressionId = StringConverter::toInt(msg->message.substr(expressionPosStart, expressionPosEnd));
				string filePath = CCString::createWithFormat("%s#%d.png",ICON_PATH_EXPRESSION,nExpressionId)->getCString();
				if(FileUtils::getInstance()->isFileExist(filePath))
				{
					pExpressionImg = ImageView::create(filePath);
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
			RichElementText* textE = RichElementText::create(tag++, clrText, 255, msg->message.substr(nCurpos, txtPos - nCurpos).c_str(), Default_Font_File, 16);
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

	if (nCurpos < msg->message.length())
	{
		RichElementText* textE = RichElementText::create(tag++, clrText, 255, msg->message.substr(nCurpos).c_str(), Default_Font_File, 16);
		pTextIn->pushBackElement(textE);
	}
	pTextIn->formatText();

	/*
	if (pCh)
		pCh->setPosition(pCh->getPosition() + Point(-10, -8));	// 因为richtext排版默认底部对齐，频道显得太高，这里重新校准
		*/

	return links;
}

CScrollMsgWindow* CScrollMsgWindow::create()
{
    CScrollMsgWindow* pWind = new CScrollMsgWindow();
    if (pWind && pWind->init())
    { 
		pWind->autorelease();
        return pWind;
    }

    CC_SAFE_DELETE(pWind);
    return NULL;
}

void CScrollMsgWindow::PushMsg(const pk::GS2C_Chat *msg,bool bIsMyWords)
{
	RichTextEx *pText = RichTextEx::create();
	pText->ignoreContentAdaptWithSize(false);
	pText->setSize(Size(getSize().width - 10, 0));

	vector<pair<Ref*, int64>> vtrLinks = MakeChatSentence(this, pText, msg, bIsMyWords);
	if (vtrLinks.size() > 0)
	{
		RecordNameLink(vtrLinks[0].first, vtrLinks[0].second);
		for (size_t i = (msg->channelId == 5 ? 0 : 1); i < vtrLinks.size(); i++)
		{
			RecordItemLink(vtrLinks[i].first, vtrLinks[i].second);
		}
	}
	++m_nCurWordsCount;

	Size szMsg = pText->getVirtualRendererSize();
	pText->setPositionX(szMsg.width / 2 + 10);
	addChild(pText);
	if (m_nMaxMsgNum < getChildrenCount())
	{
		removeChild(getChildren().at(0));
	}
}

void CScrollMsgWindow::Flush(bool bAnimation)
{
	m_nCurContentHeight = 0;
	Vector<Node*> children = getChildren();
	for (ssize_t i = 0; i < children.size(); i++)
	{
		Size size = ((RichText*)children.at(i))->getVirtualRendererSize();
		m_nCurContentHeight += (size.height + m_nLineInterval);
	}

	setInnerContainerSize(Size(getSize().width, m_nCurContentHeight));

	float fTopPosY = MAX(m_nCurContentHeight, getSize().height);
	for (ssize_t i = 0; i < children.size(); i++)
	{
		Size size = ((RichText*)children.at(i))->getVirtualRendererSize();
		children.at(i)->setPositionY(fTopPosY -= size.height / 2);
		fTopPosY -= (size.height / 2 + m_nLineInterval);
	}

	scrollToBottom(bAnimation ? 0.5f : 0.001f, bAnimation);
}

void CScrollMsgWindow::ClickName(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (m_pTouchNameListenner && m_pTouchNameHandler)
			(m_pTouchNameListenner->*m_pTouchNameHandler)(pSender, m_mpNameLinks.find(pSender)->second);
	}
}

void CScrollMsgWindow::ClickItem(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (m_pTouchItemListenner && m_pTouchItemHandler)
			(m_pTouchItemListenner->*m_pTouchItemHandler)(pSender, m_mpItemLinks.find(pSender)->second);
	}
}

void CScrollMsgWindow::ClearLetterInMap()
{
	if (m_mpNameLinks.size() > 100)
	{
		map<Ref*, int64>::iterator it = m_mpNameLinks.begin();
		while (it != m_mpNameLinks.end())
		{
			if (it->first->getReferenceCount() == 1)
			{
				it->first->release();
				m_mpNameLinks.erase(it);
			}
		}
	}
	if (m_mpItemLinks.size() > 100)
	{
		map<Ref*, int64>::iterator it = m_mpItemLinks.begin();
		while (it != m_mpItemLinks.end())
		{
			if (it->first->getReferenceCount() == 1)
			{
				it->first->release();
				m_mpItemLinks.erase(it);
			}
		}
	}
}

void CScrollMsgWindow::Clear()
{
	//ClearLetterInMap();
	removeAllChildren();
	m_mpNameLinks.clear();
	m_mpItemLinks.clear();
	m_nCurWordsCount = 0;
	m_nCurContentHeight = 0;
}

CScrollMsgForMainUI* CScrollMsgForMainUI::create()
{
	CScrollMsgForMainUI* pWind = new CScrollMsgForMainUI();
	if (pWind && pWind->init())
	{ 
		pWind->autorelease();
		return pWind;
	}

	CC_SAFE_DELETE(pWind);
	return NULL;
}

void CScrollMsgForMainUI::Update(float dt)
{
	Widget* pChatUI = getWidgetParent();
	if(!pChatUI) return;

	if (gChatDataMgr->GetMsgOfMainUI()->empty())
	{
		m_fShowTime += dt;
		if( m_fShowTime >= 5.0f )
		{
			pChatUI->setVisible(false);
		}
	} 
	else
	{
		if(!pChatUI->isVisible())
		{
			pChatUI->setVisible(true);
			MsgItem* pMsgItem = &gChatDataMgr->GetMsgOfMainUI()->front();
			PushMsg(&pMsgItem->content,pMsgItem->bIsMine);
			Flush(false);
			gChatDataMgr->GetMsgOfMainUI()->pop();
			m_fFlushTime = 0.0f;
			m_fShowTime = 0.0f;
			return;
		}

		pChatUI->setVisible(true);
		m_fFlushTime += dt;
		if ( m_fFlushTime >= 3.0f )
		{
			MsgItem* pMsgItem = &gChatDataMgr->GetMsgOfMainUI()->front();
			PushMsg(&pMsgItem->content,pMsgItem->bIsMine);
			Flush(false);
			gChatDataMgr->GetMsgOfMainUI()->pop();
			m_fFlushTime = 0.0f;
			m_fShowTime = 0.0f;
		}
	}
}

void CScrollMsgForMainUI::Flush(bool bAnimation)
{
	Vector<Node*> children = getChildren();
	if(children.empty()) return;
	children.at(0)->setPositionY(getSize().height / 2);
	scrollToBottom(bAnimation ? 0.5f : 0.001f, bAnimation);
}





















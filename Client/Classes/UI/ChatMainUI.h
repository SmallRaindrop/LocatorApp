#pragma once

#include "GameDef.h"
#include "GameUI.h"
#include "../GameScene/GameUILayer.h"
#include "UIPageView.h"
#include "UI/ResMgr/CtrlAllocator.h"
#include "Net/pk_friend.h"
#include "Net/pk_item.h"
#include "ui/UIRichText.h"

struct ItemLinkData
{
	emGridsType ePackType;
	int64		nItemID;
	string		strName;
	int			nStrOffset;

	ItemLinkData(emGridsType type, int64 id, string str, int offset): ePackType(type), nItemID(id), strName(str), nStrOffset(offset){};
	bool operator == (const ItemLinkData& other)
	{
		return nItemID == other.nItemID && nStrOffset == other.nStrOffset;
	}
};

struct MsgRecord
{
	string					strMsg;		//客户端输入框消息
	string					strMsgServer;	//发送给服务器消息
	vector<ItemLinkData>	vtrLinks;		//物品链接

	MsgRecord(string str, string msgServer, vector<ItemLinkData> vtr): strMsg(str), strMsgServer(msgServer), vtrLinks(vtr){}
	bool operator == (const MsgRecord &other)
	{
		if (vtrLinks.size() != other.vtrLinks.size())
			return false;

		for (size_t i = 0; i < vtrLinks.size(); i++)
		{
			if(!(vtrLinks[i] == other.vtrLinks[i]))
			{
				return false;
			}
		}

		return (strMsg == other.strMsg && strMsgServer == other.strMsgServer);
	}
};

class ChatMainUI : public GameUI
{
public:
	ChatMainUI();
	~ChatMainUI();

	bool			onInit();
	virtual void	onOpen();
	void			onClose();
	void			clickTab(int index);
	//void			clickMenu(int index);
	void			clickExit(Ref*, TouchEventType);
	void			clickSendMsg(Ref*, TouchEventType);
	void			clickLatestMsg(Ref*, TouchEventType);
	void			clickVoice(Ref*, TouchEventType);
	void			clickLatestMenu(int, long long data);
	void			clickChanelMenu(int);
	void			clickNameLink(Ref*, int64);
	void			clickItemLink(Ref*, int64);
	void			clickNameLink4MainUI(Ref*, int64);
	void			clickItemLink4MainUI(Ref*, int64);
	void			clickNameLinkOfChanel(int nChanel, Ref*, int64);
	void			clickItemLinkOfChanel(int nChanel, Ref*, int64);
	void			InputItemLink(emGridsType type, class CItem *pItem);
	//刷新当前频道消息
	void			UpdateCurChanel();
	//是否为当前频道消息
	bool			IsCurChannelMsg(pk::GS2C_Chat *value);
	//五个固定频道来消息
	void			MsgArrive(MsgItem* pMsgItem);
	//增加一个固定频道
	void			AddFixChannel(ChannelType type);
	//关闭一个固定频道
	void			CloseFixChanel(ChannelType type);
	//显示固定频道
	void			ShowFixedChannel(ChannelType type);
	//私聊频道来消息
	void			PrivateMsgArrive(MsgItem* pMsgItem);
	//增加一个私聊频道
	void			AddPrivateChannel(int64 channelId,string playerName);
	//关闭一个私聊频道
	void			closePrivateChannel(Ref*, TouchEventType);
	//是否有这个显示频道
	bool			IsShowingChExist(int64 channelId);
	//根据频道id获取菜单索引
	int				GetIndexByChannelId(int64 channelId);
	//显示私聊频道
	void			ShowPrivateChannel(int64 channelId,string playerName);
	//有未读消息频道标题闪烁提示
	void			TipsChannelUnread(Channel* pChannel);
	//更新频道关闭按钮状态
	void			updateChannelClose(int menuIndex);
	//更新未读新消息的标志状态
	void			showNewMsgSign();
	//表情
	void			showExpression(Ref*, TouchEventType);
	void			clickExpressionItem(Ref*,TouchEventType);
	void			closeExpression(Ref*,TouchEventType);
	//输入框
	void			UpdateDisplayedText(bool bHasCursor);
	void			InputText(Ref*, TextFiledEventType);
	void			UpdateInputState();

private:
	Text*					m_pCursor;
	Text*					m_pTxtMaterialNewCnt;
	Widget*					m_pGridMoved;
	TextField*				m_pInput;
	RichText *				m_pDisplayedInput;		// 显示实际输入的文字，为了显示带颜色的道具链接，故用此拙策
	class ScrollEditBox*	m_pScrollEditBox;
	Button *				m_pLatest;
	class CScrollMsgWindow*	m_pMsgWind;				//频道消息
	class CScrollTable*		m_pLastMsgs;			//最新记录消息
	Widget *				m_pListBG;
	CScrollMenu*			m_pChanelMenu;
	Button *				m_pVoice;
	Widget*					m_pExpressionUI;		//表情界面
	Widget*					m_pChannelClose;		//频道关闭按钮
	Widget*					m_pNewMsgSign;			//新消息标志

	vector<pk::GS2C_Chat>	m_Msgs[8];
	vector<MsgRecord>		m_Latest;
	vector<ItemLinkData>	m_vtrItemsToSent;		// 输入框中道具链接映射的道具，int保存链接在输入框中的起始偏移
	int						m_nCurGroup;
	int64					m_nCurClickPlayerID;
	ChannelType				m_nCurSeverChId;		//当前正在聊的服务器频道ID
	int64					m_nCurClientChId;		//当前正在聊的客户端频道ID
	int						m_nChannelMenuIndex;	//当前聊天菜单索引
	vector<int64>			m_showingChannels;		//正显示的频道 ,<频道ID>
	string					m_sChatingPlayerName;	
};

//显示聊天内容,文本,物品链接,表情
void		MakeChatContent(RichText *pTextIn, MsgRecord* pMyRecord);


class ScrollEditBox : public Layout
{
public:
	ScrollEditBox(){}
	~ScrollEditBox(){}

	CREATE_FUNC(ScrollEditBox);

	static ScrollEditBox* create(Widget* pEdit)
	{
		ScrollEditBox *pSEB = ScrollEditBox::create();
		if ( pSEB )
		{
			pSEB->pEditBox = pEdit;
			pSEB->addChild(pEdit);
			pSEB->setClippingEnabled(true);
			pSEB->scheduleUpdate();
			return pSEB;
		}
		
		return NULL;
	}
	void update(float dt)
	{
		Size szEdit = pEditBox->getSize();
		pEditBox->setPosition(Point(MIN(szEdit.width / 2, _size.width - szEdit.width / 2),  _size.height / 2));
		pEditBox->getSize().width;
	}

private:
	Widget*		pEditBox;
};


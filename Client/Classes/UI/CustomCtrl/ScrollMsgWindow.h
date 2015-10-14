#ifndef _SCROLLMSGWIND_
#define _SCROLLMSGWIND_

#include "UI/CocosUI.h"
#include "Net/pk_item.h"
#include "ui/UIRichText.h"

typedef void (Ref::*SEL_TouchNameLinkEvent)(Ref*, int64);
typedef void (Ref::*SEL_TouchItemLinkEvent)(Ref*, int64);

class CScrollMsgWindow : public ScrollView
{
public:
	CScrollMsgWindow(): m_nCurContentHeight(), m_nCurWordsCount(),
		m_pTouchNameHandler(), m_pTouchNameListenner(), m_nLineInterval(10), 
		m_pTouchItemHandler(), m_pTouchItemListenner(), m_nMaxMsgNum(100)
	{};
	~CScrollMsgWindow()	{};

			void		PushMsg(const pk::GS2C_Chat *msg,bool bIsMyWords = false);
	virtual void		Flush(bool bAnimation = true);
			void		ClickName(Ref*, TouchEventType);
			void		ClickItem(Ref*, TouchEventType);
			void		Clear();
			void		ClearLetterInMap();
			void		SetLineInterval(int nH)	{m_nLineInterval = nH;}

	inline void SetMaxMsgNum(int nMaxNum) { m_nMaxMsgNum = nMaxNum; }
	inline int	GetMaxMsgNum() { return m_nMaxMsgNum; }

	void SetTouchNameListenner(Ref* pSender, SEL_TouchNameLinkEvent handler)
	{
		m_pTouchNameHandler = handler;
		m_pTouchNameListenner = pSender;
	}
	void SetTouchItemListenner(Ref* pSender, SEL_TouchItemLinkEvent handler)
	{
		m_pTouchItemHandler = handler;
		m_pTouchItemListenner = pSender;
	}
	void RecordNameLink(Ref* pSender, int64 id){m_mpNameLinks.insert(make_pair(pSender, id));}
	void RecordItemLink(Ref* pSender, int64 id){m_mpItemLinks.insert(make_pair(pSender, id));}

    static CScrollMsgWindow*	create();

private:
	int						m_nCurContentHeight;
	int						m_nCurWordsCount;
	int						m_nLineInterval;
	int						m_nMaxMsgNum;

	map<Ref*, int64>		m_mpNameLinks;
	map<Ref*, int64>		m_mpItemLinks;

	SEL_TouchNameLinkEvent	m_pTouchNameHandler;
	Ref*					m_pTouchNameListenner;

	SEL_TouchItemLinkEvent	m_pTouchItemHandler;
	Ref*					m_pTouchItemListenner;
};

//显示一条聊天信息
vector<pair<Ref*, int64>> MakeChatSentence(CScrollMsgWindow *pWindow, RichText *pTextIn, const pk::GS2C_Chat *msg, bool bIsMyWords);


class CScrollMsgForMainUI : public CScrollMsgWindow
{
public:
    static CScrollMsgForMainUI*	create();
public:
	CScrollMsgForMainUI()
	:m_fFlushTime(0.0f)
	,m_fShowTime(0.0f)
	{}
	~CScrollMsgForMainUI() {}

			void		Update(float dt);
	virtual void		Flush(bool bAnimation = true);

private:
	float			m_fFlushTime;
	float			m_fShowTime;
};

#endif
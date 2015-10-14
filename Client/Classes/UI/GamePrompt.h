#pragma once

#include "GameDef.h"
#include "GameUI.h"
#include "UIPageView.h"
#include "UI/ResMgr/CtrlAllocator.h"
#include "Net/pk_friend.h"
#include "Net/pk_item.h"
#include "ui/UIRichText.h"

#define Font_Size_Prompt	40
#define Font_Size_Normal	30
#define Font_Size_Notice1	40
#define Font_Size_Notice_Chat	40

typedef void (Ref::*SEL_SCHEDULECLEAR)();
#define scheduleClear_selector(_SELECTOR) SEL_SCHEDULECLEAR(&_SELECTOR)

typedef struct _schedulerTimer
{
	float	accumulativeTime;		//累计时间
	float	alarmTime;				//定时长
	Ref*	listener;
	SEL_SCHEDULECLEAR	selector;	//回调
}SchedulerTimer;

class GamePromptCenter : public Ref,public Singleton<GamePromptCenter>
{
public:
	GamePromptCenter();
	~GamePromptCenter();

	bool initialize();
	void release();

	bool initSystemIcons();
	void updatePositions();

	void updateCompMNMsg(float dt);
	void updateCompMPMsg(float dt);
	void updateSystemMsg(float dt);
	void updateSystemNotice1(float dt);
	void updateSystemNotice2(float dt);
	void updateSystemPrompt(float dt);
	void updateSystemNormal(float dt);
	void updateSystemAlert(float dt);
	void updateSystemIcons(float dt);
	void updateTimer(float dt);
	
	void update(float dt);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	void	stopIconMailFlick();
	void	stopIconChatFlick();
	void	stopIconTeamFlick();
	void	stopIconTradeFlick();

	void	setIconMailMsgNum(int);
	void	setIconChatMsgNum(int);
	void	setIconTeamMsgNum(int);
	void	setIconTradeMsgNum(int);

private:
	void	addPromptText(const string& msg);
	void	popPromptText();
	void	onPromptTextPoped(RichTextEx* pText);

	// 系统提示相关 屏幕中央
	vector<pair<RichTextEx*, float>>	m_promptText;
	queue<RichTextEx*>	m_promptTextCache;	// 文字回收
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	void	addNormalText(const string& msg);
	void	popNormalText();
	void	onNormalTextPoped(Text* pText);

	// 系统信息 左下角
	vector<pair<Text*, float>>	m_normalText;
	queue<Text*>				m_normalTextCache;	// 文字回收
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	void	addNotice1Text(const string& msg);
	void	scrollNotice1Text(float dt);
	Layout*						m_pNotice1Frame;
	Text*						m_pScrollText;

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	void	flickIcon(Button* pBtn);
	void	flickIconMail();
	void	flickIconChat();
	void	flickIconTeam();
	void	flickIconTrade();

	void	onIconMailClicked(Ref *pSender, TouchEventType type);
	void	onIconChatClicked(Ref *pSender, TouchEventType type);
	void	onIconTeamClicked(Ref *pSender, TouchEventType type);
	void	onIconTradeClicked(Ref *pSender, TouchEventType type);

	void	refreshIconsPosition();
public:
	inline Widget* GetWidgetNotice1(){ return m_pNotice1; }	
	inline Widget* GetWidgetNotice2(){ return m_pNotice2; }	
	inline Widget* GetWidgetPrompt(){ return m_pPrompt; }	
	inline Widget* GetWidgetNormal(){ return m_pNormal; }	
	inline Widget* GetWidgetIcons(){ return m_pIconsFrame; }
	inline Button* GetIconMail(){ return m_Icons[0].first; }
	inline Button* GetIconChat(){ return m_Icons[1].first; }
	inline Button* GetIconTeam(){ return m_Icons[2].first; }
	inline Button* GetIconTrade(){ return m_Icons[3].first; }

	inline bool	IsIconMailFlicked(){ return m_Icons[0].second; }
	inline bool	IsIconChatFlicked(){ return m_Icons[1].second; }
	inline bool	IsIconTeamFlicked(){ return m_Icons[2].second; }
	inline bool	IsIconTradeFlicked(){ return m_Icons[3].second; }

	inline void	SetIconMailFlicked(bool val = true){ m_Icons[0].second = val; }
	inline void	SetIconChatFlicked(bool val = true){ m_Icons[1].second = val; }
	inline void	SetIconTeamFlicked(bool val = true){ m_Icons[2].second = val; }
	inline void	SetIconTradeFlicked(bool val = true){ m_Icons[3].second = val; }

	void		AddTimer(float alarmTime,Ref* pListener,SEL_SCHEDULECLEAR selector);

	void		ClearTrade();
	void		Clear();

private:
	Widget*						m_pNotice1;			// 公告1
	Widget*						m_pNotice2;			// 公告2
	Layout*						m_pPrompt;			// 系统提示 中央
	Widget*						m_pNormal;			// 普通提示 左下角
	Layout*						m_pIconsFrame;		// 邮件，消息，组队，交易等提示 
	vector<pair<Button*,bool>>	m_Icons;
	vector<SchedulerTimer>		m_Timers;			//清除定时器
};

#define gPromptCenter	GamePromptCenter::Instance()
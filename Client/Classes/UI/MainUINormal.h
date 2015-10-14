/****************************************************************************
 非战斗主UI
 彭龙华
 2015-07-29
 ****************************************************************************/

#ifndef __MainUINormal_h_
#define __MainUINormal_h_

#include "MainUI.h"

class CMainUINormal : public MainUI
{
public:
	CMainUINormal();
	~CMainUINormal();

	bool					onInit();
	void					onOpen();
	void					onClose();
	void					update(float dt);

    void				    updateLv();
    void				    updateHp();
    void				    updateMp();
	void					updateMapName(const std::string& name);
	ImageView*				getHeadIcon(){ return m_HeadIcon; }
    void				    InitHeadIcon();
	void					updateChatMsg(pk::GS2C_Chat *value);
	void					updateHornMsg(pk::GS2C_Chat *value);
	//副本匹配倒计时UI
	void					ShowMatchStatus();
	void					CloseMatchStatusUI();
	void					OpenMatchStatusUI();

private:
	//点击事件处理
	void					ClickJoyStick(Ref *pSender, TouchEventType type);
	void					ClickQuit(Ref *pSender, TouchEventType type);
	void					ClickQuit0(Ref *pSender, TouchEventType type);
	void					ClickCopyMap(Ref *pSender, TouchEventType type);
	void					ClickTeamCopyMap(Ref *pSender, TouchEventType type);
	void					ClickSwitchB(Ref *pSender, TouchEventType type);
	void					ClickSwitchT(Ref *pSender, TouchEventType type);
	void					clickChat(Ref *pSender, TouchEventType type);
	void					clickChatWind(Ref *pSender, TouchEventType type);
	void					clickHead(Ref *pSender, TouchEventType type);
	void					ClickTeam(Ref *pSender, TouchEventType type);
	void					ClickMap(Ref *pSender, TouchEventType type);
	void					ClickTask(Ref *pSender, TouchEventType type);
	void					ClickMenuRB(Ref *pSender, TouchEventType type);
	void					ClickMail(Ref *pSender, TouchEventType type);
	void					ClickManufacture(Ref *pSender, TouchEventType type);
	void					ClickGoToMatch(Ref *pSender, TouchEventType type);
	void					ClickOpenMatch(Ref *pSender, TouchEventType type);
private:
	Layout*					m_panelLT;	//左上面板
	Layout*					m_panelLB;	//左下面板
	Layout*					m_panelRT;	//右上面板
	Layout*					m_panelRB;	//右下面板

	//玩家头像
	ImageView*				m_HeadIcon;
	Text*					m_HeroLv;
	Text*					m_HeroName;
	bool					m_bIconInit;

	//摇杆
	ImageView*				m_JoyStick;

	Layout*					m_panelMenuB;	//底部菜单Panel
	Button*					m_BtnSwitchB;	//底部菜单开关

	Layout*					m_panelMenuT;	//顶部菜单Panel
	Button*					m_BtnSwitchT;	//顶部菜单开关

	//聊天
	Layout*					m_pChatUI;

	class HornContorller*	m_pHornWind;
	class CScrollMsgForMainUI*	m_pMsgWind;
	Button*					m_pButtonChat;
	float					m_fChatBtnShowTime;
	bool					m_bMsgWindScrolled;

	//副本匹配
	Widget*					m_pMatchStatusUI;
	class Label*			m_pMatchSeconds;
	Widget*					m_pMatchSign;
	RichTextEx*				m_pMatchCopyName;
	Button*					m_pBtnOpenMatchStatus;
	float					m_fMatchUIShowSeconds;

	//地图
	Text*					m_mapName;
};
//主界面和其他界面打开组队
void	openTeamUI(UiOpenType openType);
#endif
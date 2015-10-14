/****************************************************************************
 战斗主UI
 彭龙华
 2015-07-29
 ****************************************************************************/

#pragma once

#include "MainUI.h"

class CMainUIFight : public MainUI
{
public:
	CMainUIFight();
	~CMainUIFight();

	bool					onInit();
	void					onOpen();
	void					onClose();

	void				    InitHeadIcon();
	bool					InitSkillBtns();

	void					update(float dt);
    void				    updateLv();
    void				    updateHp();
    void				    updateMp();
	void					updateSkillBtns();
	void					updateSkillCd();
	void					updateNormalAttack(float dt);	// 长按普通攻击按钮持续攻击处理
	void					updateTeamHead();
	void					updateMapName(const std::string& name);
	void					updateChatMsg(pk::GS2C_Chat *value);
	void				    updateBuff();
	void					ContinueFight(bool yesOrNo);

	ImageView*				getHeadIcon(){ return m_HeadIcon; }
private:
	//点击事件处理
	void					ClickQuit(Ref *pSender, TouchEventType type);
	void					ClickSkill(Ref *pSender, TouchEventType type);
	void					ClickJoyStick(Ref *pSender, TouchEventType type);
	void					clickHead(Ref *pSender, TouchEventType type);
	void					clickChat(Ref *pSender, TouchEventType type);
	void					clickChatWind(Ref *pSender, TouchEventType type);

	//任务
	void					SelTask(int, long long);
	void					UpdateTask();	//
	void					updateTaskTrace();
	void					TraceTask(class Task* pTask);
	void					clickTask(Ref *pSender, TouchEventType type);
	void					clickTaskBtn(Ref *pSender, CheckBoxEventType type);

public:
	int						m_defCountSeconds;
	int						m_DestoryCountSeconds;

private:
	Layout*					m_panelLT;	//左上面板
	Layout*					m_panelLB;	//左下面板
	Layout*					m_panelRT;	//右上面板
	Layout*					m_panelRB;	//右下面板

	//玩家头像
	ImageView*				m_HeadIcon;
	Text*					m_HeroLv;
	Text*					m_HeroHp;
	Text*					m_HeroMp;
	Layout*					m_HeroHpBar;
	Layout*					m_HeroMpBar;
	ImageView*				m_HeroHpSlot;
	ImageView*				m_HeroMpSlot;
	Text*					m_HeroName;
	bool					m_bIconInit;
	//buff列表
	ListView*				m_buffListView;

	//摇杆
	ImageView*				m_JoyStick;

	//技能槽
	SkillBtn				m_SkillBtns[Skill_Max_Num];		// 技能快捷栏按钮
	SkillBtn				m_NormalAtk;					// 普通攻击按钮
	bool					m_bNormalAtkPushed;				// 普通攻击按钮是否被按下，用于做按住按钮持续攻击
	float					m_fNormalAtkTimer;				// 普通攻击被按下时触发攻击的间隔时间

	//队友
	TeamHead				m_TeamHead[Team_Max_Num];

	//聊天
	Layout*					m_pChatUI;

	class HornContorller*	m_pHornWind;
	class CScrollMsgForMainUI*	m_pMsgWind;
	Button*					m_pButtonChat;
	float					m_fChatBtnShowTime;
	bool					m_bMsgWindScrolled;

	//pvp小地图
	Widget*					m_pPvPSmallMap;
};
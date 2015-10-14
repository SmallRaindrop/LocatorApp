#pragma once
#include "GameDef.h"
#include "ComboBox.h"


#define gMenu4PInst ((CMenuForPerson*)gGameUILayer->getChildByTag(Menu4Player_Tag))
#define gMenu4Achievement ((CMenuForAchievement*)gGameUILayer->getChildByTag(Menu4Achievement_Tag))
#define gMenu4MatchMode ((CMenuForMatchMode*)gGameUILayer->getChildByTag(Menu4MatchMode_Tag))

class CMenuForPerson :public CMenu
{
public:
	static const char *PO_MSG;
	static const char *PO_TEAM;
	static const char *PO_MAIL;
	static const char *PO_EQUI;
	static const char *PO_SEARCH;
	static const char *PO_FRIEND;
	static const char *PO_BLACKLIST;
	static const char *PO_ENEMY;
	static const char *PO_DEL;
	static const char *PO_TEAM_KICK;
	static const char *PO_TEAM_HANDOVER;
	static const char *PO_TRADE;
	static const char *PO_TEAM_LEAVE;
	static const char *PO_MASK;
	static const char *PO_NAME_COPY;
public:
	CMenuForPerson(void);
	~CMenuForPerson(void){};

    static CMenuForPerson*	create(string nItemBGID = "Chat_Menu", string nBGID = "Chat_Menu_BG", int nInterval = 0);
	//弹出的菜单，动态显示 动态隐藏
	static  void	PopupMenu(Point pos, int nRadius, int64 nPlayerID, Ref* pListenner, SEL_SelectIndexEvent pHandler, const char* strItem1, ...);
	//非弹出的菜单
	void			AddMenu(int64 nPlayerID,const char* strItem1, ...);

	virtual void	AddItem(const char* strCaption, bool bDisabled = false);
	virtual void	ClickButton(Ref *pSender, TouchEventType type);
	virtual void	Clear();
	void			LayOut();
	void			SetPlayer(int64 nPlayerID);
	void			OneItemFadeOut();

public:
	static int64			s_nPlayerID;
	static string			s_nPlayerName;
	static bool				s_bPlayerOnline;
private:
	map<Ref*, const char*>	m_mpCustomItems;
	int						m_nRadius;
	int						m_nCurFadeOutIndex;
};

class CMenuForAchievement :public CMenu
{
public:
	CMenuForAchievement(void){};
	~CMenuForAchievement(void){};

	static CMenuForAchievement*	create(string nItemBGID = "Button_Menu", string nBGID = "Image_Menu_BG", int nInterval = 10);
	static  void	PopupMenu(Point pos, Ref* pListenner, SEL_SelectIndexEvent pHandler, const char* strItem1, ...);

};

class CMenuForMatchMode :public CMenu
{
public:
	CMenuForMatchMode(void){};
	~CMenuForMatchMode(void){};

	static CMenuForMatchMode*	create(string nItemBGID = "MatchMode_Btn", string nBGID = "MatchMode_BG", int nInterval = 10);
	static  void			PopupMenu(Point pos, Ref* pListenner, SEL_SelectIndexEvent pHandler, const char* strItem1, ...);

};

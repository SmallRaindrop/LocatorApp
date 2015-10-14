/****************************************************************************
 岳良友 主界面整合
 2015-07-29
 ****************************************************************************/
#ifndef __MainUI_h_
#define __MainUI_h_

#include "GameDef.h"
#include "GameUI.h"
#include "GameScene/Hero.h"
#include "GameScene/GameUILayer.h"
#include "Net/pk_map.h"
#include "GameScene/RoleBuff.h"
#include "GameUIWithOutSideTouchEvent.h"

#define Skill_Max_Num		(4)
#define Team_Max_Num		(3)

typedef enum _uiOpenType
{
	UiOpenType_None,
	UiOpenType_FromMainUI,
	UiOpenType_FromWorldMapUI,
	UiOpenType_Count,
}UiOpenType;

typedef struct _skillBtn
{
	SkillCfg*	skill;
	Button*		btn;
	ImageView*	icon;
	ImageView*	lock;
	CdCtrol*	cd;
	Text*		desc;
	bool		enable;

	_skillBtn()
	{
		skill = NULL;
		btn = NULL;
		icon = NULL;
		cd = NULL;
		desc = NULL;
		enable = false;
	}
}SkillBtn;

typedef struct _teamHead
{
	Widget*	ui;
	int64 id;
	ImageView*	icon;
	int			hp;
	int			maxHp;
	ProgressTimer*	progress;
	Text*		Txtleave;

	_teamHead()
	{
		ui = NULL;
		id = 0;
		icon = NULL;
		hp = 0;
		maxHp = 0;
		progress = NULL;
	}
}TeamHead;

class BuffIcon :public Widget
{
public:
	BuffIcon(RoleBuff* buff);
	~BuffIcon();

	/* Name		：BuffIcon::create
	 * Author	：Liyang
	 * Date		: 2015-08-21
	 * Desc		: 创建BUFF图标
	 * Param	: path:图片的路径，TickTime:持续时间,时间单位:毫秒
	 * Return	: BuffIcon
	 */
 	static BuffIcon* create(RoleBuff* _buff);
	bool init(const std::string& path,int tickTime);

	void			update(float dt);
private:
	float			m_tickTime; // 剩余时间 单位毫秒
	ImageView*		m_img;
	RoleBuff*	    m_buffData;
	bool			canStartBlink;
};

class HornContorller : public Ref
{
public:
	HornContorller(Widget *pMainPanel);
	void update(float dt);
	void PushMsg(const pk::GS2C_Chat *value);
	void ScrollText(float dt);
	void MsgOver();
	void SetDelegate(class CScrollMsgWindow *pD){m_pScrollWindDelegate = pD;}
	static HornContorller* Create(Widget *pMainPanel);

private:
	Widget*						m_pMainWind;
	Widget*						m_pClipWind;
	Widget*						m_pHornIcon;
	class CScrollMsgWindow*		m_pScrollWindDelegate;
	class UnderlinedText*		m_pSenderName;
	RichText*					m_pHornText;
	queue<pk::GS2C_Chat>		m_queHornWords;
	float						m_fCurHornLastTime;
	float						m_fTextOrgPosX;
	bool						m_bTextShowing;
	float						m_bTextNeedScrollLen;
};

class MainUI : public GameUIWithOutSideTouchEvent
{
public:
	enum _functionTypeRB
	{
		FunctionTypeRB_None = -1,
		FunctionTypeRB_SkyBook,
		FunctionTypeRB_Friend,
		FunctionTypeRB_GodDevice,
		FunctionTypeRB_Bag,
		FunctionTypeRB_Pet,
		FunctionTypeRB_ArmyGroup,
		FunctionTypeRB_Skill,
		FunctionTypeRB_Produce,
		FunctionTypeRB_Strength,
		FunctionTypeRB_Expand3,
		FunctionTypeRB_Max,
	}FunctionRBType;
public:
	MainUI(int idu,const std::string& strJsonFile) : GameUIWithOutSideTouchEvent(idu,strJsonFile){}
	virtual ~MainUI(){}

	static MainUI* ShowMainUI(GameMapFuncType mapType);
	static void CloseMainUI();

	static MainUI* GetActiveMainUI();
	static MainUI* GetMainUI();

	virtual void updateLv() = 0;
	virtual void updateHp() = 0;
	virtual void updateMp() = 0;
	virtual void updateSkillCd(){}
	virtual void updateSkillBtns(){}
	virtual void updateTeamHead(){}
	virtual void updateBuff(){}
	virtual void updateChatMsg(pk::GS2C_Chat *value){}
	virtual void updateHornMsg(pk::GS2C_Chat *value){}
	virtual void updateMapName(const std::string& name){}

	virtual ImageView* getHeadIcon() = 0;
};

#endif // __MainUI_h_
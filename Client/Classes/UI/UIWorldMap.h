/*
世界地图
彭龙华
2015-8-19
*/

#pragma once
#include "GameDef.h"
#include "GameUI.h"
#include "MainUIFight.h"

class CUIWorldMap :public GameUI
{
public:
	typedef enum _worldMapMode
	{
		WorldMapMode_None = 0,
		WorldMapMode_PlaceList,
		WorldMapMode_CopyList,
		WorldMapMode_Prepare,
		WorldMapMode_Count,
	}WorldMapMode;

	typedef enum _matchBtnStatus
	{
		MatchBtnStatus_None = 0,
		MatchBtnStatus_Cancel,
		MatchBtnStatus_CancelAndStart,
		MatchBtnStatus_Started,
		MatchBtnStatus_Prepare,
		MatchBtnStatus_PrepareOver,
		MatchBtnStatus_Count,
	}MatchBtnStatus;

public:
	CUIWorldMap(void);
	~CUIWorldMap(void);

	//显示即将进入副本的UI
	static	void			ShowGameCopyToEnter(int nMapId)
	{
		GameCopy* pGameCopy = gCopyDataMgr->GetGameCopy(nMapId);
		if(!pGameCopy) return;

		CUIWorldMap* pUI = (CUIWorldMap*)gGameUILayer->open(IDU_WORLDMAPUI);
		if(!pUI) return;
		{
			pUI->ShowLocaleList(pGameCopy->worldMapId);
			pUI->ShowPrepare(pGameCopy);
		}
	}

	virtual bool			onInit();
	virtual void			onOpen();
	virtual void			update(float dt);

	//地图显示模式,地点列表,副本列表,准备UI，匹配UI
	inline WorldMapMode		GetMode() { return m_curMode; } 
	void					SetMode(WorldMapMode mode);
	//匹配按钮模式
	inline MatchBtnStatus	GetMatchBtnStatus() { return m_matchBtnStatus; }
	void					SetMatchBtnStatus(MatchBtnStatus btnStatus);
	//更新解锁状态
	void					UpdateBigPlaceLockUI();
	void					UpdateSmallPlaceLockUI();
	//显示队员ICON
	void					ShowTeamIcon();
	//显示小地点列表(基础副本列表)
	void					ShowLocaleList(int nWorldMapId);
	//展开副本列表
	void					SpreadGameCopyList(unsigned int nIdx,vector<GameCopy*>& gameCopys);
	//收縮当前展开的副本列表
	void					ShrinkGameCopyList();
	//显示副本准备UI
	void					ShowPrepare(GameCopy* gameCopy);
	//显示单个副本信息
	void					ShowGameCopyInfo(Widget* pUI,GameCopy* gameCopy,bool bNeedCopyIcon);
	//设置匹配模式描述
	void					SetMatchModeTxt();
	//显示匹配UI
	void					ShowMatch();
	//显示匹配按钮
	void					UpdateMatchBtn();
	void					ShowBtnCancel();
	void					ShowBtnCancelAndStart();
	void					ShowBtnStarted();
	void					ShowBtnPrepare();
	void					ShowBtnPrepareOver();
	//设置邀请者匹配数据
	void					SetInviterMatchData();
	//设置邀请者随机匹配数据
	void					SetInviterRandomMatchData();

	//点击事件

	//点击返回
	void clickCloseBtn(Ref* pSender,TouchEventType type);
	//点击聊天
	void clickChatBtn(Ref* pSender,TouchEventType type);
	//点击随机副本
	void clickRandomBtn(Ref* pSender,TouchEventType type);
	//点击快捷组队
	void clickTeamBtn(Ref* pSender,TouchEventType type);
	//点击大地点
	void clickWorldPlace( Ref* pSender,TouchEventType type );
	//点击小地点
	void clickLocale(Ref* pSender,TouchEventType type);
	//点击子节点
	void clickChildCopyItem(Ref* pSender,TouchEventType type);
	//点击开始副本
	void clickStartCopy(Ref* pSender,TouchEventType type);
	//点击返回
	void clickBackFromPrepare(Ref* pSender,TouchEventType type);
	//点击匹配模式
	void clickMatch(Ref* pSender,TouchEventType type);
	//点击选择匹配模式
	void clickMatchItem(int nIdx);
	//点击取消匹配
	void clickCancelMatch(Ref* pSender,TouchEventType type);
	//点击立即开始
	void clickStartImmediately(Ref* pSender,TouchEventType type);
	//点击准备
	void clickPrepare(Ref* pSender,TouchEventType type);
private:
	Widget*					m_pPlaceList;						//大地点UI
	Widget*					m_pCopyList;						//副本UI
	Widget*					m_pPrepare;							//准备UI
	Widget*					m_pMatch;							//匹配UI
	ImageView*				m_pTeamIcon[Team_Max_Num];			//队员ICON
	ListView*				m_pCopyListView;					//副本列表
	Slider*					m_pSlider;							//滑动块
	Text*					m_pCopyMode;						//副本模式文本
	Text*					m_pCamp;							//副本敌人文本
	Text*					m_pMatchMode;						//匹配模式文本
	Widget*					m_pMenuMatchBg;
	Widget*					m_pParentCopyItem;					//父节点副本UI模板
	Widget*					m_pChildCopyItem;					//子节点副本UI模板
	vector<Widget*>			m_pWorldPlaceLock;
	RichTextEx*				m_pCountTitle;						//倒计时标题
	class Label*			m_pCountNum;						//倒计时数字
	Button*					m_pBtnCountLeft;					//倒计时左按钮
	Button*					m_pBtnCountRight;					//倒计时右按钮
	Button*					m_pBtnCountCenter;					//倒计时中按钮
	Widget*					m_pMatchingSign;					//正在匹配标记
	Text*					m_pMatchWaitTime;					//匹配等待时间

	WorldMapMode			m_curMode;							//世界地图UI模式
	MatchMode				m_matchMode;						//匹配模式
	MatchStatus				m_matchStatus;						//匹配状态
	MatchBtnStatus			m_matchBtnStatus;					//匹配按钮状态
	int						m_nChildIdxInListView;				//展开子节点在ListView显示的位置
	int						m_nCurLocaleId;						//当前选择的小地点
	GameCopy*				m_curGameCopy;						//当前要进入的副本
	int						m_nMatchModeIdx;					//匹配模式索引
	int						m_nBigPlaceIdx;						//当前显示大地点
};
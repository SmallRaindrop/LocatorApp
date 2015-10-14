#pragma once
#include "GameDef.h"
#include "ui/GameUIDef.h"
#include "GridIcon.h"
#include "GameScene/ItemGrid.h"
#include "UI/CocosUI.h"


#define ICON_TAG 1234

class CGridArrayUI : public Layout
{
public:
	CGridArrayUI();
	~CGridArrayUI();

	static CGridArrayUI* create(emGridsType gridsType,int indexOffset,int capacity,Widget* pBagUI,bool bDynamicShow=false,bool bCanMove=false);

	//以Scrollview创建滑动层
	//param: gridsType 背包类型
	//       totalGrid 总的格子数
	//       _scrollview 引用的滑动层指针
	//add Tangbo
	static CGridArrayUI* create(emGridsType gridsType, int totalGrid,int linegrid, ScrollView * _scrollview);

	bool		init(emGridsType gridsType,int indexOffset,int capacity,Widget* pBagUI,bool bDynamicShow,bool bCanMove);

	//以Scrollview创建滑动层
	//param: gridsType 背包类型
	//       totalGrid 总的格子数
	//       _scrollview 引用的滑动层指针
	//add Tangbo
	bool        init(emGridsType gridsType, int totalGrid,int linegrid, ScrollView * _scrollview);

	void		reset();

	void        resetScroll();

	void		ActiveOneLineUI(int pos);

	void		insertGridUI(int nPos,CItem* pItemGrid,emGridsType gridsType);
	void		removeGridUI(int nIndex);
	void		removeAllGridUIs();

	void		UpdateIconMask();
	void		ShowMaskManual(bool bShow,ItemCfg* pMaskItemCfg);

	inline void setCapacity(int nCapacity) {m_nCapacity = nCapacity;}
	inline int  getCapacity() {return m_nCapacity;}
	inline void setDynamicShow(bool bShow) { m_bDynamicShow=bShow; }
	inline bool IsDynamicShow() { return m_bDynamicShow; }

	CGridIcon*	getIcon(int nIndex) { return m_iconVec[nIndex%m_nCapacity];}
	Widget*		GetIconBk(int nIndex) { return m_iconBGVec[nIndex%m_nCapacity]; }

	void		ShowCd(int cdType, float cdTime);
	void		ShowCd();
	void		RemoveCd();

	void		clickGridActive(Ref *pSender, TouchEventType type);
	void		activeCallFunc(bool yesOrNo);

	void		AddIconClickEvent(Ref* pSender,IconClickEvent event);
private:
	emGridsType			m_gridType;
	int					m_nIndexOffset;
	int					m_nCapacity;
	Widget*				m_pWidget;
	bool				m_bDynamicShow;
	bool				m_bCanMove;
	bool				m_bShowMask;
	vector<CGridIcon*>	m_iconVec;
	vector<Widget*>		m_iconBGVec;
};
#pragma once

#include "GameDef.h"
#include "UI/GameUIDef.h"
#include "GameScene/ItemType.h"
#include "DragCtrol.h"
#include "UI/CocosUI.h"

class CItem;

typedef bool (Ref::*IconClickEvent)(class CGridIcon* pIcon);
#define iconclickeventselector(_SELECTOR) (IconClickEvent)(&_SELECTOR)

class CGridIcon : public ImageView
{
	typedef enum
	{
		part_order_quality = 1,
		part_order_icon,
		part_order_mask,
		part_order_num,
		part_order_lock,
		part_order_cd
	}IconPartOrder;

	typedef enum
	{
		part_num,    //数量
		part_name,   //名字
		part_level,  //等级
		part_precent //进度
	}BookPart;

public:
	CGridIcon();
	~CGridIcon();

	/* pos:物品在格子中的位置 */
    static CGridIcon*	create(CItem* pItem, int pos, emGridsType gridsType,bool bCanMove=false);

public:
	bool				init(CItem* pItem, int pos, emGridsType gridsType,bool bCanMove);

	//初始化天书 Tangbo
	bool				initBook(CItem* pItem, int pos, emGridsType gridsType,bool bCanMove);
	//显示等级   Tangbo
	//_point     父节点的百分位置
	void                ShowLevel(Point _point = Point(0.8f, 0.2f));
	//显示当前精度 Tangbo
	//_point     父节点的百分位置
	void                ShowPrecentBar(Point _point = Point(0.5f, 0.2f));
	//显示当前道具名字 Tangbo
	//_point     父节点的百分位置
	void                ShowName(Point _point = Point(0.2f, 0.8f));
	//显示进度值 Tangbo
	//_point     父节点的百分位置
	void                ShowPrecent(Point _point = Point(0.5f, 0.2f));

	//得到当前品质字体的颜色,只在天书界面使用 Tangbo
	Color3B             getNameColor(BookPart part);

	//得到当前品质字体的描边颜色,只在天书界面使用 Tangbo
	Color4B             getLineColor(BookPart part);

	//设置是否显示数量
	inline void         setShowNum(bool val){ if(m_pItemNum)m_pItemNum->setVisible(val);}

	void				updateByContent();
	inline void			SetItem(CItem* pItem)				{ m_pItem = pItem; }
	inline CItem*		GetItem()							{ return m_pItem; }
	inline void			SetQuickcutIcon(bool isQuickcut)	{ m_bIsQuickcut = isQuickcut; }

	void				ShowQuality();
	void				ShowIcon();
	string              getIconPath();
	void				ShowMask();
	void				ShowNum();
	void				ShowLock();
	void				ShowCd();
	void				RemoveCd();

	bool				CheckUseAble();
	bool				IfShowNum();

	inline void			SetTipsBtnBright(bool bBright)	{ m_bSetTipsBtnBright=bBright; }
	inline bool			GetTipsBtnBright()				{ return m_bSetTipsBtnBright; }
	inline int			GetIndex()						{ return m_GridPos; }

	/*手动显示mask*/
	void				ShowMaskManual(bool bShow);

	void				clickGridIcon(Ref *pSender, TouchEventType type);
	void				AddIconClickEvent(Ref* pSender, IconClickEvent event) { m_clickEventListener=pSender; m_clickEventSelector=event; }

protected:
	CItem*					m_pItem;
	emGridsType				m_GridsType;
	int						m_GridPos;

	ImageView*				m_pQuality;
	ImageView*				m_pIcon;
	ImageView*				m_pMask;
	Text*					m_pItemNum;
	ImageView*				m_pLock;

	//add   Tangbo
	string                  m_sIconPath;
	Text*                   m_pName;
	Text*                   m_pLevel;
	Text*                   m_pPercent;
	LoadingBar*             m_pLoadingBar;


	bool					m_bSetTipsBtnBright;
	bool					m_bIsQuickcut;			//快捷图标 tips不需要操作按钮
	bool					m_bCanMove;

	Ref*					m_clickEventListener;
	IconClickEvent			m_clickEventSelector;
private:

};
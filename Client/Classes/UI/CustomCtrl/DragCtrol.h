#pragma once
#include "GameDef.h"
#include "ui/CocosUI.h"

typedef void (Ref::*SEL_DragEndEvent)(Widget* pDragIcon,int64 id);
#define dragendeventselector(_SELECTOR) (SEL_DragEndEvent)(&_SELECTOR)

typedef enum _dragSlotType
{
	DragSlotType_None = -1,
	DragSlotType_Skill = 0,
	DragSlotType_Item,
	DragSlotType_SkillCancle,	//取消技能配置
	DragSlotType_ItemCancle,	//取消item配置
	DragSlotType_Count
}DragSlotType;

typedef struct _dragSlot
{
	vector<Widget*>		slots;
	Ref*				pListener;
	SEL_DragEndEvent	pSelector;

	_dragSlot()
	{
		slots.clear();
		pListener = NULL;
		pSelector = NULL;
	}
}DragSlot;

class CDragCtrol : public Node
{
public:
	static CDragCtrol*	create();
	static CDragCtrol*	create(Widget* pUICloneSrc,int64 data, DragSlotType slotDes,Ref* pClickEventListener, SEL_TouchEvent clickEventSelector,Widget* pScrollOrPage = NULL);

	CDragCtrol();
	~CDragCtrol();

public:
	bool				init(Widget* pUICloneSrc,int64 data, DragSlotType slotDes,Ref* pClickEventListener, SEL_TouchEvent clickEventSelector,Widget* pScrollOrPage);
	inline void			SetDragId(int nTag) { m_nDragId=nTag; }
	inline void			SetCloneSrc(Widget* pWidget) { m_pCloneSrc=pWidget; }
	void				AddDragEndEvent(Ref* pClickEventListener, SEL_DragEndEvent clickEventSelector);
	void				RemoveDragIcon();
	void				DragTimer(float dt);
	void				StartTimer();
	void				StopTimer();
	inline Widget*		GetDragIcon() { return m_pDragIcon; }
	void				OnDragUp();
	void				DragingIcon(Point pos);
	void				OnDragEnd();
	void				EnableScroll(bool bEnable);
	void				clickSrcUI(Ref* pSender, TouchEventType type);

public:
	static void			SlotScale(DragSlotType type, float fScale, int fOpacity);
	
private:
	DragSlotType		m_slotType;
	int64				m_nDragId;
	Widget*				m_pCloneSrc;
	Widget*				m_pDragIcon;
	Widget*				m_pScrollOrPage;
	float				m_fPressTimeStamp;
	Ref*				_ClickEventListener;
	SEL_TouchEvent		_ClickEventSelector;
	Ref*				_DragEndListener;
	SEL_DragEndEvent	_DragEndSelector;
};
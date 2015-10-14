/****************************************************************************
 副本结束结算UI
 彭龙华
 2015-08-06
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameUI.h"
#include "Net/pk_map.h"

#define TeamSize		(3)

class CCopyEnd : public GameUI
{
public:
	CCopyEnd();
	~CCopyEnd();

	bool			onInit();
	void			onOpen();
	void			onClose();
	void			clickTab(int index);
	void			clickExit(Ref*, TouchEventType);
	void			updateCheckOut(pk::GS2C_CopyMapCheckOut* value);

private:

	Widget*					m_pStaticstPanel;	//统计页面
	Widget*					m_pRewardPanel;		//收益页面

	Text*					m_name[TeamSize];
	Text*					m_harm[TeamSize];
	Text*					m_bear[TeamSize];
	Text*					m_kill[TeamSize];
	Text*					m_dead[TeamSize];
	Text*					m_relive[TeamSize];

	Text*					m_time;
	Text*					m_money;
	Text*					m_exp;

	Widget*					m_pGridsUI;
	ListView*				m_pItemList;
	Slider*					m_pSlider;
};


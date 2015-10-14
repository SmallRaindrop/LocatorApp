/****************************************************************************
 自由战斗结算UI
 彭龙华
 2015-10-37
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameUI.h"
#include "Net/pk_map.h"

class CFreeFightCheckOut : public GameUI
{
public:
	CFreeFightCheckOut();
	~CFreeFightCheckOut();

	bool			onInit();
	void			clickTab(int index);
	void			setCheckOutData(pk::GS2C_FreeFightCopyCheckout* value);
	void			clickExit(Ref*, TouchEventType);

private:
	pk::GS2C_FreeFightCopyCheckout			m_checkOutdata;

	Text*					m_pBlueScore;
	Text*					m_pRedScore;
	Text*					m_pVictory;
	Slider*					m_pSlider;							//滑动块
	ListView*				m_pListView;						//列表
	Widget*					m_pListItem;						//列表item
	RadioButtonSet*			m_pRadioBtn;
};


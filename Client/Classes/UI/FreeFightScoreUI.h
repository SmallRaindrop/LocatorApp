/****************************************************************************
 自由战斗比分UI
 彭龙华
 2015-09-29
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameUI.h"
#include "Net/pk_map.h"

class CFreeFightScoreUI : public GameUI
{
public:
	CFreeFightScoreUI();
	~CFreeFightScoreUI();

	bool			onInit();
	void			clickExit(Ref*, TouchEventType);
	void			UpdateScore(pk::GS2C_FreeFightCopyScoreBoard* value);

private:
	Text*					m_pBlueScore;
	Text*					m_pRedScore;
	Slider*					m_pSlider;							//滑动块
	ListView*				m_pListView;						//列表
	Widget*					m_pListItem;						//列表item
};


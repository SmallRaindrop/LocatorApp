#pragma once
#include "GameDef.h"
#include "../GameScene/GameUILayer.h"

class CReliveUI : public GameUI
{
public:
	CReliveUI();
	~CReliveUI();

	static void		UnscheduleAllTicker()
	{
		CReliveUI* pUI = dynamic_cast<CReliveUI*>(gGameUILayer->getUI(IDU_REVIVEANDBACK));
		if (pUI)
		{
			pUI->unscheduleAllTicker();
		}
	}

	bool			onInit();
	void			onOpen();
	void			onClose();

	void			initialState();
	void			showReliveChoice(RecoverLifeRuleCfg* pRuleCfg);

	void			townTicker(float dt);
	void			nearTicker(float dt);
	void			samePlaceTicker(float dt);

	void			townAutoTicker(float dt);

	void			unscheduleAllTicker();

	void			clickTownBtn(Ref *pSender, TouchEventType type);
	void			clickNearBtn(Ref *pSender, TouchEventType type);
	void			clickSamePlaceBtn(Ref *pSender, TouchEventType type);

private:
	Text*		m_pTownDesc;
	Button*		m_pTownBtn;
	Widget*		m_pTownMask;

	Text*		m_pNearDesc;
	Button*		m_pNearBtn;
	Widget*		m_pNearMask;

	Text*		m_pSamePlaceDesc;
	Button*		m_pSamePlaceBtn;
	Widget*		m_pSamePlaceMask;

	int			m_nTownRuleId;
	int			m_nNearRuleId;
	int			m_nSamePlaceRuleId;

	int			m_nTownCd;
	int			m_nNearCd;
	int			m_nSamePlaceCd;

	int			m_nTownAutoCd;
};
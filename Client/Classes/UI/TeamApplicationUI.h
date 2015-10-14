#pragma once

#include "GameDef.h"
#include "GameUI.h"
#include "Net/pk_team.h"
#include "TeamUI.h"
#include "GameScene/GameUILayer.h"

typedef struct _teamInviterInfo
{
	int64	id;
	string	name;
	int		lv;
	int		career;
}TeamInviterInfo;

class TeamApplicationUI : public GameUI
{
public:
	TeamApplicationUI();
	~TeamApplicationUI();

	bool			onInit();
	virtual void	onOpen();
	virtual void	onClose();

	//void			clickTab(int index);

	void			clickExit(Ref*, TouchEventType);
	void			clickRefuseAll(Ref*, TouchEventType);
	void			clickAgree(Ref*, TouchEventType);
	void			clickRefuse(Ref*, TouchEventType);
	void			clickApproveApp(Ref*, TouchEventType);
	void			clickApproveInvite(Ref*, TouchEventType);
	void			clickApproveInvite2(Ref*, TouchEventType);
	void			Reload();
	void			clickItem(int nIndex, long long);
	void			updateSelState(int nIndex);

public:
	static size_t GetCandidateNum()
	{
		return s_Inviters.size();
	}

	static vector<TeamInviterInfo>	s_Inviters;

private:
	class CScrollTable*			m_pCandidatesList;
	int							m_playerIdx;
	Widget*						m_pSelSign;
};


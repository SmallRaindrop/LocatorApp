/*
*±¶œ‰
*≈Ì¡˙ª™-2015-09-22
*/

#pragma once

#include "RoleFighter.h"
#include "Net/pk_move.h"
#include "RoleModel.h"
#include "ui/UIText.h"

class CChests : public RoleFighter
{
public:
	typedef enum _chestsStatus
	{
		ChestsStatus_None = -1,
		ChestsStatus_Opening,
		ChestsStatus_Idle,
		ChestsStatus_Count
	}ChestsStatus;
public:
	CChests();
	~CChests();

	CREATE_FUNC(CChests);

	virtual bool init();
	virtual bool initRole();
	virtual void update(float delta);
	virtual void onSelect(bool param);
	virtual void RefreshEquip();
	virtual void DeadVirtual(RoleFighter* pKiller);
	virtual void Dead(RoleFighter* pKiller);
	virtual void Disappear();
	virtual void LeaveMap();
	virtual void SetDataID(int dataid);
	int GetDataID(){ return m_pCfgData?m_pCfgData->id:0; }
	inline ChestCfg* GetChestsData(){ return m_pCfgData; }

	inline ChestsStatus	GetChestsStatus() { return m_openStatus; }
	void				SetChestsStatus(ChestsStatus status);
	inline float		GetDestroyLeftTime() { return m_fDestoryLeftTime; }
	void				SetDestroyLeftTime(float fLeftTime);

	void ShowMonsterChat(int strId,int displayMs);
	void removeMonsterChat();
protected:
	ChestCfg*			m_pCfgData;
	ChestsStatus		m_openStatus;
	float				m_fDestoryLeftTime;		//(√Î)
	ui::Text*			m_pChatText;
};
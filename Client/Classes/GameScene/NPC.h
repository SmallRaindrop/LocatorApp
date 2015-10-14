#ifndef __NPC_h_
#define __NPC_h_

#include "RoleFighter.h"
#include "GameScene/TaskMgr.h"
#include "GameScene/GameUILayer.h"
#include "UI/GameUI.h"

class CNpc : public RoleFighter
{
public:
	CNpc();
	~CNpc();

	CREATE_FUNC(CNpc);

	virtual bool init();
	virtual bool initRole();
	virtual void onSelect(bool param);

	virtual void update(float dt);
	virtual void RefreshEquip();
	virtual void SetDataID(int id);
	NPCTaskState GetTaskState();
	vector<int>& GetTaskAcc()	{return m_vtrTaskAcc;};
	vector<int>& GetTaskFin()	{return m_vtrTaskFin;};

	inline int				GetDataID(){ return m_pCfgData?m_pCfgData->id:0; }
	inline NpcCfg*			GetData() { return m_pCfgData; }

	// ²É¼¯
	void CheckForCollect();
	void CollectStart();
	void CollectInterrupt();
	void CollectTimeOut(float fNoUse);
	void CollectFinished();

private:
	NpcCfg*			m_pCfgData;
	vector<int>		m_vtrTaskAcc;		
	vector<int>		m_vtrTaskFin;	
	NPCTaskState	m_eTaskState;
	int				m_nCollectionTaskID;
	class TimerProgressBar*	m_pCollectionProgressBar;

public:
	static CNpc*	s_pCurOptNPC;
	static CNpc*	s_pCurCollecting;
	static map<int, Task*>	s_AddtionalTasks;
};


class NpcUI : public GameUI
{
public:
	NpcUI(int idu, const std::string& strJsonFile): GameUI(idu, strJsonFile)
	{
	}
public:
	virtual void update(float dt);
	virtual bool init()
	{
		if (find(s_vtrExclusiveUID.begin(), s_vtrExclusiveUID.end(), getIDU()) == s_vtrExclusiveUID.end())
			s_vtrExclusiveUID.push_back(getIDU());

		return GameUI::init();
	}
	virtual void onOpen() 
	{
		for (size_t i = 0; i < s_vtrExclusiveUID.size(); i++)
		{
			if (s_vtrExclusiveUID[i] != getIDU())
			{
				gGameUILayer->close(s_vtrExclusiveUID[i]);
			}
		}
	};

private:
	static vector<int>	s_vtrExclusiveUID;
};

#endif //__NPC_h_




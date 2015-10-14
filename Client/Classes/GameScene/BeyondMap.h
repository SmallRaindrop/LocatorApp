#pragma once
#include "GameDef.h"
#include "GameDataManager.h"
#include "Singleton.h"

using std::list;
using std::vector;

#define REACH_OFFSET 2
#define TRANSDOOR_OFFSET 10

class CMapsNetwork :public Singleton_Auto<CMapsNetwork>
{

public:
	CMapsNetwork() : m_pAllNodes(), m_nSize()	{ Init(); }
	~CMapsNetwork()							;
	struct Node
	{
		struct Link
		{
			Node*	pTo;
			int		nCost;
		};
		GatewayCfg*		pTransdoor;
		vector<Link>	vtrNighbors;
		Node*			pPreNode;
		int				nCurCost;
	};

	bool		Init();
	Node*		SeekPath(int dwMapID, int dwCol, int dwRow, int dwDesMapID, int dwDesCol, int dwDesRow);

private:
	Node*					m_pAllNodes;
	int						m_nSize;
};


class GateWaysIterator : public ForeachIterator<GatewayCfg>
{
public:
	GateWaysIterator(vector<GatewayCfg*> *pData):m_vtrTransdoors(pData)	{}
	bool execute(GatewayCfg* pItem)
	{
		m_vtrTransdoors->push_back(pItem);
		return true;
	}

private:
	vector<GatewayCfg*>*	m_vtrTransdoors;
	int						m_nMapID;
}; 


//-----------------------------------------------------move across maps------------------------------------
class CAction
{
public:
	CAction()	{};
	~CAction()	{};
	virtual void	Start()			= 0;
	virtual bool	CheckDone()		= 0;
	virtual bool	CheckFailed()	= 0;
	virtual	void	SetErrorDistance(int nDistance){};
};

class CMove: public CAction
{
public:
	CMove(int nTargetMapID, Point ptDestination, Point DonePos,int nSrcMapID):
		m_nTargetMapID(nTargetMapID), m_Destination(ptDestination), m_nErrorDistance(),
		m_DonePos(DonePos),m_nSrcMapID(nSrcMapID)	{};
	~CMove(){};
	virtual void	Start();
	virtual bool	CheckDone();
	virtual bool	CheckFailed();
	virtual	void	SetErrorDistance(int nDistance)	{m_nErrorDistance = nDistance;};

private:
    int             m_nSrcMapID;
    Point			m_Destination;
    int             m_nErrorDistance;
    //
    int				m_nTargetMapID;
    Point			m_DonePos;
};

//class CTransmit: public CAction
//{
//public:
//	CTransmit(int nTargetMapID):m_nTargetMapID(nTargetMapID){};
//	~CTransmit(){};
//	virtual void	Start()		{}
//	virtual bool	CheckDone()	{return gCurMap->getMapId() == m_nTargetMapID;}
//	virtual void	Update()	{}
//
//private:
//	int				m_nTargetMapID;
//};

class CSuperMove
{
public:
	typedef void (*AfterMoveFinishedFunc)(__int64 pData);
	struct AfterMoveToDo
	{
		AfterMoveFinishedFunc	pFunc;
		__int64					pData;
	};

	CSuperMove();
	~CSuperMove()	{Clear();};
	static CSuperMove*		Instance()	{static CSuperMove inst; return &inst;}
	void					StartMove(CMapsNetwork::Node *pPath, int nDistance = 0);
	bool					HasNextAction();
	bool					NextAction();
	void					Pause();
	void					Resume();
	void					Update();
	void					Clear();
	void					Over();
	bool					IsOver()	{return m_bOver;}
	bool					IsPause()	{return m_bPause;}
	bool					IsHungUp()	{return m_bHungUp;}
	inline void				SetAfterMoveFunc(std::function<void()>& afterMoveFunc) { m_afterMoveFunc=afterMoveFunc; }
	inline void				ClearAfterMoveFunc() { m_afterMoveFunc=nullptr; }
	inline std::function<void()> GetAfterMoveFunc() { return m_afterMoveFunc; }

	/*bGoToDoor 只到最后一个地图的门*/
	static	void Start(int nDesMapID, int nDesCol, int nDesRow, AfterMoveToDo *pWhatToDO = NULL,int distance=0,bool bGoToDoor = false);
	static	void Start(int nDesMapID, int nDesCol, int nDesRow, std::function<void()> afterMoveFunc,int distance=0,bool bGoToDoor = false);
	static AfterMoveToDo s_data;
private:
	std::list<CAction*>				m_lsActions;
	std::list<CAction*>::iterator	m_itCurAction;
	CMapsNetwork::Node *			m_pPath;
	bool							m_bOver;
	bool							m_bPause;
	bool							m_bHungUp;	// 新版本的漫游系统在发出移动指令后主角可能不会立即移动（主角之前如果已经在移动）
    int								m_nErrorDistance;
	AfterMoveFinishedFunc			m_pFunc;
	std::function<void()>			m_afterMoveFunc;
};
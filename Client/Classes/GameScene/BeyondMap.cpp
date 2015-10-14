#include "BeyondMap.h"
#include "GameScene/Hero.h"
#include "GameScene/NPC.h"

int dist(GatewayCfg &A, GatewayCfg &B)
{
	double fDist = 0;
	int w, h;
	double tmp;
	if (A.srcmap == B.srcmap)
	{
		w = A.srcx - B.srcx;
		h = A.srcy - B.srcy;
		tmp = sqrt((double)w * w + h * h);
	}
	else if (A.desmap == B.srcmap)
	{
		w = A.desx - B.srcx;
		h = A.desy - B.srcy;
		tmp = sqrt((double)w * w + h * h);
	}
	else
	{
		CC_ASSERT(1);
	}

 	return (int)tmp;
}

CMapsNetwork::~CMapsNetwork()							
{
	if ( m_pAllNodes )
	{
		delete[] m_pAllNodes;
		m_pAllNodes = NULL;
	}
}

bool CMapsNetwork::Init()
{
	vector<GatewayCfg*>	m_vtrTransdoors;
	GateWaysIterator it(&m_vtrTransdoors);
	GatewayData.foreach(it);
	size_t nTransSize = m_vtrTransdoors.size();

	m_nSize = nTransSize;
	m_pAllNodes = new Node[m_nSize + 2];

	for (size_t i = 0; i < nTransSize; i++)
	{
		m_pAllNodes[i].pTransdoor = m_vtrTransdoors[i];
		m_pAllNodes[i].pPreNode = NULL;
		m_pAllNodes[i].nCurCost = 0;
	}

	for (int i = 0; i < m_nSize; i++)
	{
		for (int j = 0; j < m_nSize; j++)
		{
			if (i == j)	continue;
			if (/*m_pAllNodes[i].pTransdoor->srcmapid == m_pAllNodes[j].pTransdoor->srcmapid ||*/
				m_pAllNodes[i].pTransdoor->desmap == m_pAllNodes[j].pTransdoor->srcmap)
			{
				Node::Link link = {&m_pAllNodes[j], dist(*m_pAllNodes[i].pTransdoor, *m_pAllNodes[j].pTransdoor)};
				m_pAllNodes[i].vtrNighbors.push_back(link);
			}
		}
	}

	return true;
}

CMapsNetwork::Node* CMapsNetwork::SeekPath(int dwMapID, int dwCol, int dwRow, int dwDesMapID, int dwDesCol, int dwDesRow)
{
	static GatewayCfg from = {};
	from.srcmap = from.desmap = dwMapID;
	from.srcx = from.desx = dwCol;
	from.srcy = from.desy = dwRow;
	
	static GatewayCfg to;
	to.srcmap = to.desmap = dwDesMapID;
	to.srcx = to.desx = dwDesCol;
	to.srcy = to.desy = dwDesRow;

	Node node = {&from}, node2 = {&to};
	node.nCurCost = node2.nCurCost = 0;

	if (dwMapID == dwDesMapID)
	{
		m_pAllNodes[m_nSize] = node;
		m_pAllNodes[m_nSize + 1] = node2;
		m_pAllNodes[m_nSize].pPreNode = &m_pAllNodes[m_nSize + 1];
		return &m_pAllNodes[m_nSize];
	}

	for (int i = 0; i < m_nSize; i++)
	{
		for (size_t j = 0; j < m_pAllNodes[i].vtrNighbors.size(); )
		{
			if (m_pAllNodes[i].vtrNighbors[j].pTo == &m_pAllNodes[m_nSize] || m_pAllNodes[i].vtrNighbors[j].pTo == &m_pAllNodes[m_nSize + 1])
			{
				m_pAllNodes[i].vtrNighbors.erase(m_pAllNodes[i].vtrNighbors.begin() + j);
				continue;
			}
			j++;
		}

		m_pAllNodes[i].pPreNode = NULL;

		if (m_pAllNodes[i].pTransdoor->srcmap == node.pTransdoor->srcmap)
		{
			Node::Link link = {&m_pAllNodes[i], dist(from, *m_pAllNodes[i].pTransdoor)};
			node.vtrNighbors.push_back(link);
		}
		if (m_pAllNodes[i].pTransdoor->desmap == node2.pTransdoor->srcmap)
		{
			Node::Link link = {&m_pAllNodes[m_nSize + 1], dist(*m_pAllNodes[i].pTransdoor, to)};
			m_pAllNodes[i].vtrNighbors.push_back(link);
		}

		m_pAllNodes[i].nCurCost = 0;
	}
	m_pAllNodes[m_nSize] = node;
	m_pAllNodes[m_nSize + 1] = node2;

	list<Node*> lstCurPos;
	list<Node*>::iterator it, itRoundOver;
	lstCurPos.push_back(&m_pAllNodes[m_nSize]);
	Node *pLeastCostNode = NULL;
	itRoundOver = lstCurPos.end();
	itRoundOver--;
	for (it = lstCurPos.begin(); it != lstCurPos.end();)
	{
		vector<Node::Link>::iterator itN;
		for (itN = (*it)->vtrNighbors.begin(); itN != (*it)->vtrNighbors.end(); itN++)
		{
			if (itN->pTo->nCurCost > (*it)->nCurCost + itN->nCost || 
				itN->pTo->nCurCost == 0 && itN->pTo != &m_pAllNodes[m_nSize] && itN->pTo->pPreNode == NULL)
			{
				itN->pTo->nCurCost = (*it)->nCurCost + itN->nCost;
				itN->pTo->pPreNode = *it;
				if (pLeastCostNode == NULL || pLeastCostNode->nCurCost > itN->pTo->nCurCost)
				{
					pLeastCostNode = itN->pTo;
				}

				if (itN->pTo == &m_pAllNodes[m_nSize + 1])
				{
					continue;
				}

				list<Node*>::iterator itTemp;
				for (itTemp = lstCurPos.begin(); itTemp != lstCurPos.end(); itTemp++)
				{
					if (*itTemp == itN->pTo)
					{
						break;
					}
				}
				if (itTemp == lstCurPos.end())
				{
					lstCurPos.push_back(itN->pTo);
				}
			}
		}

		if (itRoundOver == it)
		{
			if (m_pAllNodes[m_nSize + 1].pPreNode && pLeastCostNode && pLeastCostNode->nCurCost >= m_pAllNodes[m_nSize + 1].nCurCost)
			{
				break;
			}
			pLeastCostNode = NULL;
			itRoundOver = lstCurPos.end();
			itRoundOver--;
		}

		//it = lstCurPos.erase(it);
		it++;
	}

	if (m_pAllNodes[m_nSize + 1].pPreNode == NULL)
	{
		return NULL;
	}

	Node *pTemp = &m_pAllNodes[m_nSize + 1];
	Node *pTempNext = NULL;
	Node *pPre = m_pAllNodes[m_nSize + 1].pPreNode;
	while (pTemp)
	{
		pTemp->pPreNode = pTempNext;
		pTempNext = pTemp;
		pTemp = pPre;
		if (pPre)
		{
			pPre = pPre->pPreNode;
		}
	}
	CC_ASSERT(pTempNext == &m_pAllNodes[m_nSize]);
	if (pTempNext != &m_pAllNodes[m_nSize])
	{
		return NULL;
	}
	return pTempNext;
}







//---------------------------------------------supermove--------------------------------------------------------------

CSuperMove:: AfterMoveToDo CSuperMove::s_data;

bool CMove::CheckDone()	
{
	if (!gMap)
	{
		return true;
	}

    if (m_nSrcMapID==m_nTargetMapID)
    {
		if (gMap->getMapDataID() == m_nTargetMapID && 
				abs(gHero->GetCellX() - (int)m_DonePos.x) <= m_nErrorDistance && 
				abs(gHero->GetCellY() - (int)m_DonePos.y) <= m_nErrorDistance)
		{
			gHero->Stop();
			return true;
		}
		return false;
    }
    else
    {
        return (gMap && gMap->getMapDataID() == m_nTargetMapID);
    }

}

vector<pk::PosInfo> path;
bool CMove::CheckFailed()	
{
	bool inList = false;

	Point ptDestination = (m_nSrcMapID == m_nTargetMapID ? m_DonePos : m_Destination);
	for (size_t i = 0; i < path.size(); i++)
	{
		if (path[i].x == ptDestination.x && path[i].y == ptDestination.y)
		{
			inList = true;
			break;
		}
	}

	if (!inList)
		return true;

	if (!gHero->IsMoving() && !CheckDone())
	{
		return true;
	}

	return false;
}

void CMove::Start()
{
	if(!gMap) return;

	gHero->MoveTo(m_Destination.x, m_Destination.y);

	path.clear();
	APath &succession_path = gHero->GetMovePath();
	if (succession_path.size() == 0)
	{
		if (gHero->GetMoveMonitor().GetStepX())
		{
			m_DonePos = Point(gHero->GetMoveMonitor().GetStepX(), gHero->GetMoveMonitor().GetStepY());
		}
		else
		{
			m_DonePos = Point(gHero->GetCellX(), gHero->GetCellY());
		}
		pk::PosInfo pos = {static_cast<int16>(m_DonePos.x), static_cast<int16>(m_DonePos.y)};
		path.push_back(pos);
		return;
	}

	CHero::PathToPosInfo(gHero->GetCellX(), gHero->GetCellY(), succession_path, path);
	
	if (gHero->GetCellX() == m_Destination.x && gHero->GetCellY() == m_Destination.y)
	{
        m_DonePos = Point(gHero->GetCellX(), gHero->GetCellY());
	}
	else
	{
		if (path.size()>0)
		{
			m_DonePos = Point(path.back().x, path.back().y);
		}
		//else
		//{
		//	m_DonePos = gHero->getTargetPos();
		//}
	}
}

CSuperMove::CSuperMove()
{
	m_nErrorDistance = 0;
	m_bOver = true;
	m_bPause = false;
	m_bHungUp = false;
	m_pPath = nullptr;
	m_afterMoveFunc = nullptr;
}

void CSuperMove::Start(int nDesMapID, int nDesCol, int nDesRow, AfterMoveToDo *pWhatToDO,int distance,bool bGoToDoor)
{
	CCLOG("SuperMove to %d: %d %d", nDesMapID, nDesCol, nDesRow);

	if (pWhatToDO)
	{
		s_data = *pWhatToDO;
	}

	if (!gMap)
	{
		return;
	}

	if (gMap->getMapDataID() == nDesMapID && gHero->GetCellX() == nDesCol &&  gHero->GetCellY() == nDesRow)
	{
		return CSuperMove::Instance()->Over();
	}

	CMapsNetwork::Node *pPath = CMapsNetwork::Instance()->SeekPath(gMap->getMapDataID(),
		gHero->GetCellX(), gHero->GetCellY(), nDesMapID, nDesCol, nDesRow);

	if (pPath&&bGoToDoor)
	{
		CMapsNetwork::Node *pPathTemp = pPath;
		CMapsNetwork::Node *pPathTempPre = pPath->pPreNode;
		while (pPathTemp)
		{
			if (!pPathTempPre->pPreNode)
			{
				pPathTemp->pPreNode = NULL;
				break;
			}
			else
			{
				pPathTemp = pPathTempPre;
				pPathTempPre = pPathTemp->pPreNode;
			}
		}
	}

	if (pPath)
	{
		CSuperMove::Instance()->StartMove(pPath, distance);
	}
}

void CSuperMove::Start(int nDesMapID, int nDesCol, int nDesRow, std::function<void()> afterMoveFunc,int distance,bool bGoToDoor)
{
	CCLOG("SuperMove to %d: %d %d", nDesMapID, nDesCol, nDesRow);

	CSuperMove::Instance()->SetAfterMoveFunc(afterMoveFunc);

	if (!gMap)
	{
		return;
	}

	if (gMap->getMapDataID() == nDesMapID && gHero->GetCellX() == nDesCol &&  gHero->GetCellY() == nDesRow)
	{
		return CSuperMove::Instance()->Over();
	}

	CMapsNetwork::Node *pPath = CMapsNetwork::Instance()->SeekPath(gMap->getMapDataID(),
		gHero->GetCellX(), gHero->GetCellY(), nDesMapID, nDesCol, nDesRow);

	if (pPath&&bGoToDoor)
	{
		CMapsNetwork::Node *pPathTemp = pPath;
		CMapsNetwork::Node *pPathTempPre = pPath->pPreNode;
		while (pPathTemp)
		{
			if (!pPathTempPre->pPreNode)
			{
				pPathTemp->pPreNode = NULL;
				break;
			}
			else
			{
				pPathTemp = pPathTempPre;
				pPathTempPre = pPathTemp->pPreNode;
			}
		}
	}

	if (pPath)
	{
		CSuperMove::Instance()->StartMove(pPath, distance);
	}
}

void CSuperMove::Pause()
{
	if (m_bOver || m_bPause)
		return;

	m_bPause = true;
}

void CSuperMove::Resume()
{
	if (m_bOver || !m_bPause)
		return;

	(*m_itCurAction)->Start(); 
	m_bPause = false;
}

void CSuperMove::StartMove(CMapsNetwork::Node *pPath, int nDistance)
{
	if (gHero->IsMoving())
	{
		gHero->Stop();
		m_pPath = pPath;
		m_bHungUp = true;
	}
	else
	{
		//Clear();

		pPath = pPath->pPreNode;
		while (pPath)
		{
			m_lsActions.push_back(new CMove(pPath->pTransdoor->desmap, Point(pPath->pTransdoor->srcx, pPath->pTransdoor->srcy), 
				Point(pPath->pTransdoor->desx, pPath->pTransdoor->desy),pPath->pTransdoor->srcmap));
			pPath = pPath->pPreNode;
		}
		m_lsActions.back()->SetErrorDistance(nDistance);

		m_itCurAction = m_lsActions.begin();
		(*m_itCurAction)->Start(); 

		m_bOver = false;
		m_bHungUp = false;
	}

	m_nErrorDistance = nDistance;
}

bool CSuperMove::NextAction()
{
	(*(++m_itCurAction))->Start();
	return true;
}

bool CSuperMove::HasNextAction()
{
	list<CAction*>::iterator it = m_itCurAction;
	if (++it == m_lsActions.end())
	{
		return false;
	}

	return true;
}

static int nFrameCounter = 0;
void CSuperMove::Update()
{
	if (!gMap)
	{
		return /*Clear()*/;
	}

	if (m_bHungUp)
	{
		if (!gHero->IsMoving())
		{
			m_bHungUp = false;
			StartMove(m_pPath, m_nErrorDistance);
		}

		return;
	}

	if (!gHero->IsTransfering() && !m_bOver && !m_bPause)
	{
		if ((*m_itCurAction)->CheckFailed())
		{
			return Clear();
		}

		if ((*m_itCurAction)->CheckDone())
		{
			if (!HasNextAction()) 
			{
				Over();
			}
			else if (nFrameCounter++ == 5)
			{
				NextAction();
				nFrameCounter = 0;
			}
		}
	}
}

void CSuperMove::Clear()
{
	m_itCurAction = m_lsActions.begin();
	while (m_itCurAction != m_lsActions.end())
	{
		delete *m_itCurAction;
		m_itCurAction++;
	}

	m_lsActions.clear();

	nFrameCounter = 0;
	s_data.pFunc = nullptr;
	m_pPath = nullptr;
	m_bOver = true;
	m_bPause = false;
	m_bHungUp = false;
	m_afterMoveFunc = nullptr;
}

void CSuperMove::Over()
{
	if (s_data.pFunc)
	{
		(s_data.pFunc)(s_data.pData);
	}
	if(GetAfterMoveFunc())
	{
		GetAfterMoveFunc()();
	}
	Clear();
}
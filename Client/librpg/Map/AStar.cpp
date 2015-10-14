#include "AStar.h"
#include "TileMap.h"

AStar::AStar(int w,int h,AGenerator* pGenerator)
	:m_nWidth()
	,m_nHeight()
	,m_nNodeVersion()
	,m_bPrune(true)
{
	initialize(w,h,pGenerator);
}

AStar::~AStar()
{

}

void AStar::initialize(int w,int h,AGenerator* pGenerator)
{
	if ( w%2 == 0 )
	{
		m_nWidth = w;
		m_nHeight = h;
	}
	else
	{
		m_nWidth = w-1;
		m_nHeight = h-1;
	}

	int len = m_nWidth*(m_nHeight+1);
	m_NodeList.resize(len);
	for (int i=0;i<len;++i)
	{
		ANode* pNode = &m_NodeList[i];
		int x = i % m_nWidth;
		int y = i / m_nWidth;
		pNode->x = x;
		pNode->y = y;		
		pNode->block = pGenerator->isBlock(x,y);
		pNode->linksLength = 0;
		if ( !pNode->block )
		{
			if ((y % 2) ^ (i & 1))
			{
				if (y > 0 && !m_NodeList[i-m_nWidth].block)
				{
					pNode->links[pNode->linksLength++] = APoint(x,y-1);
				}
				if (y < m_nHeight-1 && !m_NodeList[i+m_nWidth].block)
				{
					pNode->links[pNode->linksLength++] =APoint(x,y+1);
				}
				if (x < m_nHeight-1 && !m_NodeList[i+1].block)
				{
					pNode->links[pNode->linksLength++] =APoint(x+1,y);
				}
				if (x > 0 && !m_NodeList[i-1].block)
				{
					pNode->links[pNode->linksLength++] =APoint(x-1,y);
				}
			}
			else
			{
				if (x < m_nHeight-1 && !m_NodeList[i+1].block)
				{
					pNode->links[pNode->linksLength++] = APoint(x+1,y);
				}
				if (x > 0 && !m_NodeList[i-1].block)
				{
					pNode->links[pNode->linksLength++] = APoint(x-1,y);
				}
				if (y > 0 && !m_NodeList[i-m_nWidth].block)
				{
					pNode->links[pNode->linksLength++] = APoint(x,y-1);
				}
				if (y < m_nHeight-1 && !m_NodeList[i+m_nWidth].block)
				{
					pNode->links[pNode->linksLength++] =APoint(x,y+1);
				}
			}
		}
	}	
}

void AStar::searchForPath(APoint s,APoint e,APath& path)
{
	search(s,e);

	for (int i=(int)m_Result.size()-2;i>=0;--i)
	{
		path.push(APoint(m_Result[i]->x,m_Result[i]->y));
	}
}

bool AStar::isValidPoint(APoint pt)
{
	if ( pt.x > 0 && pt.x <= m_nWidth &&
		 pt.y > 0 && pt.y <= m_nHeight )
	{
		return true;
	}

	return false;
}

ANode* AStar::getNode(APoint pt)
{
	if ( isValidPoint(pt) )
	{
		return &m_NodeList[pt.x+pt.y*m_nWidth];
	}
	return NULL;
}

void AStar::search(APoint s,APoint e)
{
	if ( !isValidPoint(s) || !isValidPoint(e) )
	{
		return ;
	}

	m_Result.clear();

	reviseStartAndEndPos(s,e);

	ANode* pNodeS = getNode(s);
	ANode* pNodeE = getNode(e);

	if ( !pNodeS || pNodeS->block || !pNodeE || pNodeE->block )
	{
		return ;
	}

	int costNow = abs(e.x - s.x) + abs(e.y - s.y);
	vector<ANode*> openList;
	openList.resize(2);
	// 将起点加入开放列表
	openList[0]=pNodeS;
	openList[1]=NULL;
	pNodeS->pre = pNodeS->next = NULL;
	pNodeS->version = ++m_nNodeVersion;
	pNodeS->nowCost = 0;
	while (1)
	{
		// 取开放列表第一个元素
		ANode* pCurrentNode = openList[0];
		openList[0] = pCurrentNode->next;
		if(openList[0]) 
		{
			openList[0]->pre = NULL;
		}

		// 到达终点
		if (pCurrentNode == pNodeE)
		{
			if (m_bPrune) 
				prunePath(pNodeS,pCurrentNode);
			else
				buildPath(pNodeS,pCurrentNode);
			return;			
		}

		int linkLength = pCurrentNode->linksLength;
		for (int i=0;i<linkLength;++i)
		{
			ANode* pTestNode = getNode(APoint(pCurrentNode->links[i].x,pCurrentNode->links[i].y));
			int F = pCurrentNode->nowCost + 1;

			if (pTestNode->version != m_nNodeVersion)
			{
				pTestNode->version = m_nNodeVersion;

 				pTestNode->parent = pCurrentNode;
 				pTestNode->nowCost = F;
 				int dis = abs(e.x - pTestNode->x) + abs(e.y - pTestNode->y);
 				F += dis;
 				pTestNode->mayCost = F;
 				pTestNode->pre = NULL;

				F = (F - costNow) >> 1;
				pTestNode->next = openList[1];
				if (openList[1]) openList[1]->pre = pTestNode;
				openList[1] = pTestNode;
			}
			else if(pTestNode->nowCost > F)
			{
				if (pTestNode->pre)
					pTestNode->pre->next = pTestNode->next;
				if (pTestNode->next) 
					pTestNode->next->pre = pTestNode->pre;
				if(openList[1] == pTestNode)
					openList[1] = pTestNode->next;

 				pTestNode->parent = pCurrentNode;
 				pTestNode->nowCost = F;
 				int dis = abs(e.x - pTestNode->x) + abs(e.y - pTestNode->y);
 				F+=dis;
 				pTestNode->mayCost = F;
 				pTestNode->pre = NULL;

				pTestNode->next = openList[0];
				if(openList[0])
					openList[0]->pre = pTestNode;
				openList[0] = pTestNode;
			}
		}
		if (!openList[0])
		{
			if(!openList[1]) break;
			ANode* pTmp = openList[0];
			openList[0] = openList[1];
			openList[1] = pTmp;
			costNow += 2;
		}
	}
}

void AStar::prunePath(ANode* pNodeS,ANode* pNodeE)
{
	m_Result.push_back(pNodeE);

	if(pNodeE == pNodeS) 
	{
			return;
	}

	ANode* pNode = pNodeE;
	while (true)
	{
		if (pNode == pNodeS)
		{
			return;
		}
		ANode* pNodeParent = pNode->parent;
		if ( pNodeParent == pNodeS )
		{
			m_Result.push_back(pNodeS);
			return;
		}
		ANode* pNodeParentParent = pNodeParent->parent;
		int G1 = abs(pNodeParent->x-pNode->x)+abs(pNodeParent->y-pNode->y);
		int G2 = abs(pNodeParentParent->x-pNodeParent->x)+abs(pNodeParentParent->y-pNodeParent->y);
		int G3_X = abs(pNodeParentParent->x-pNode->x);
		int G3_Y = abs(pNodeParentParent->y-pNode->y);
		if ( G1+G2 < G3_X+G3_Y || G3_X > 1 || G3_Y > 1 )
		{
			m_Result.push_back(pNodeParent);
			pNode = pNodeParent;
		}
		else
		{
			m_Result.push_back(pNodeParentParent);
			pNode = pNodeParentParent;
		}
	}
}

void AStar::buildPath( ANode* pNodeS,ANode* pNodeE )
{
	m_Result.push_back(pNodeE);
	while ( pNodeE != pNodeS)
	{
		pNodeE = pNodeE->parent;
		m_Result.push_back(pNodeE);
	}
}

void AStar::reviseStartAndEndPos(APoint& s,APoint& e)
{
	ANode* pNodeE = getNode(e);
	ANode* pNodeS = getNode(s);


	if (pNodeE->block)
	{
		findNonblockNearBlock(s,e);
	}

	if (pNodeS->block)
	{
		findNonblockNearBlock(e,s);
	}
}

void AStar::findNonblockNearBlock(APoint& s,APoint& e)
{
	int i=0;
	vector<ANode*> vec;
	vec.clear();

	while (true)
	{
		++i;
		bool hasNode = false;
		for (int y=e.y-i;y<=e.y+i;++y)
		{
			for (int x=e.x-i;x<=e.x+i;++x)
			{
				if ( !isValidPoint(APoint(x,y)))
				{
					continue;
				}

				ANode* pNode = getNode(APoint(x,y));
				if (!pNode->block)
				{
					vec.push_back(pNode);
					hasNode = true;
				}
			}
		}

		if (hasNode)
		{
			break;
		}
	}
	ANode* minNode=vec[0];
	int minCost=abs(s.x-minNode->x)+abs(s.y-minNode->y);

	for (i=1;i<(int)vec.size();++i)
	{
		ANode* pNode = vec[i];
		int cost = abs(s.x-pNode->x)+abs(s.y-pNode->y);
		if (cost<minCost)
		{
			minNode = pNode;
		}
	}
	e.x = minNode->x;
	e.y = minNode->y;
}

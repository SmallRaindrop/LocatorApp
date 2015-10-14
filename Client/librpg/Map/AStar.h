/***
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：A星寻路算法相关
 */

#ifndef __AStar_h_
#define __AStar_h_

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <deque>
using namespace std;


/************************************************************************/
/* A星寻路点                                                   */
/************************************************************************/
struct APoint
{
	signed short x;
	signed short y;

	APoint():x(0),y(0){}

	APoint(int _x,int _y):x(_x),y(_y)
	{
	}

	APoint(const APoint& pt):x(pt.x),y(pt.y){}

	APoint operator= (const APoint& pt)
	{
		x = pt.x;
		y = pt.y;
		return *this;
	}
};

/************************************************************************/
/* A星寻路节点                                                   */
/************************************************************************/
class ANode  
{
public:
	ANode(void):block(),version(),linksLength(),parent(),
		nowCost(),mayCost(),x(),y(),next(),pre()
	{
		memset(links,0,sizeof(APoint)*4);

	}

	~ANode()
	{
	}

public:
	bool	block;
	int		version;

	APoint links[4];

	int linksLength;
	int nowCost;
	int mayCost;
	int x;
	int y;
	ANode* parent;
	ANode* next;
	ANode* pre;
};

/************************************************************************/
/* A星寻路点路径                                                  */
/************************************************************************/
class APath
{
public:
	APath(){}
	APath(APath& path){
		while (path.size()>0)
		{
			push(path.pop());
		}
	}
	~APath(){}

	inline void push(APoint pt){
		m_Points.push_back(pt);
	}

	inline APoint pop(){
		APoint pt = m_Points.front();
		m_Points.pop_front();
		return pt;
	}

	inline void clear(){
		m_Points.clear();
	}

	inline int size(){
		return (int)m_Points.size();
	}

	inline deque<APoint>& getPoints(){
		return m_Points;
	}

protected:
	deque<APoint> m_Points;
};

/************************************************************************/
/* A星寻路判断阻挡接口                                                   */
/************************************************************************/
class AGenerator
{
public:
	virtual bool	isBlock(int x,int y) = 0;
};

/************************************************************************/
/* A星寻路算法相关                                                   */
/************************************************************************/
class AStar
{
public:
	AStar(int w,int h,AGenerator* pGenerator);
	~AStar(void);

	void	initialize(int w,int h,AGenerator* pGenerator);
	void	searchForPath(APoint s,APoint e,APath& path);

	bool	isValidPoint(APoint pt);
	ANode*	getNode(APoint pt);

	void	search(APoint s,APoint e);

public:
	int						m_nWidth;
	int						m_nHeight;	
	vector<ANode>			m_NodeList;
	vector<ANode*>			m_Result;
	int						m_nNodeVersion;
	bool					m_bPrune;


protected:
	void reviseStartAndEndPos(int& startX,int& startY,int& endx,int& endy);
	void reviseStartAndEndPos(APoint& s,APoint& e);

	void findNonblockNearBlock(int& startX,int& startY,int& endx,int& endy);
	void findNonblockNearBlock(APoint& s,APoint& e);

	void prunePath(ANode* pNodeS,ANode* pNodeE);
	void buildPath(ANode* pNodeS,ANode* pNodeE);
};

#endif // __AStar_h_
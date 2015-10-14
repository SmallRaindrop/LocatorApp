#ifndef __Terrain_h_
#define __Terrain_h_

#include "GameDef.h"
#include "map_def.h"

#define cellMaskNone	0
#define cellMaskStop	1
#define cellMaskCover	1<<1
#define cellMaskWater	1<<2

struct Cell
{
	//unsigned int uMask;
	unsigned char uMask;

	Cell(){ 
		Zero();
	};

	inline void Zero(){ uMask = cellMaskNone; }

	inline void Mark(int m){
		uMask |= m;
	}

	inline bool isMark(int m){
		return (uMask & m) != 0;
	}

	inline void clMark(int m){
		uMask &= ~m;
	}
};

/* Name		：angleToDir
 * Author	：YueLiangYou
 * Date		: 2015-06-24
 * Desc		: 通过角度获取一个方向
 * Param	: angle 角度
 * Return	: 方向
*/
__Dir angleToDir(float angle);

/* Name		：vectorToDir
 * Author	：YueLiangYou
 * Date		: 2015-06-24
 * Desc		: 通过向量获取一个方向
 * Param	: vec 向量
 * Return	: 方向
*/
__Dir vectorToDir(const Point& vec);

class CTerrain : public Ref
{
public:
	CTerrain();
	~CTerrain();
	CC_SYNTHESIZE_READONLY(int,m_nOriginX,OriginX);
	CC_SYNTHESIZE_READONLY(int,m_nOriginY,OriginY);
	CC_SYNTHESIZE_READONLY(int,m_nCellX,CellX);
	CC_SYNTHESIZE_READONLY(int,m_nCellY,CellY);

public:
	void	initWithMapContext(map_context* context);
	void	initMask(int width,int height);

	inline int		getCellMax(){ return m_nCellX*m_nCellY; }
	inline Cell*	getCellArray(){ return m_arrayCells; }
	inline Cell*	getCell(int idx){ return idx < getCellMax() ? &m_arrayCells[idx] : NULL; }
	inline Cell*	getCell(int cx,int cy){ return getCell(cell2Index(cx,cy)); }

	inline void		index2Cell(int idx,int& cx,int& cy){ cy = idx / m_nCellX; cx = idx % m_nCellX; }
	inline int		cell2Index(int cx,int cy){ return cy*m_nCellX+cx; }

	inline void		world2Cell(int& x,int& y)
	{
		double cx = (double)(x-m_nOriginX)/(double)cellInPixelsX+(double)(m_nOriginY-y)/(double)cellInPixelsY;
		double cy = (double)(m_nOriginY-y)/(double)cellInPixelsY-(double)(x-m_nOriginX)/(double)cellInPixelsX;
		x = (int)(cx>=0?cx:cx-1);
		y = (int)(cy>=0?cy:cy-1);
	}
	inline void		cell2World(int& cx,int& cy)
	{
		double x = m_nOriginX + (double)cx*(double)cellInPixelsX/2.0-(double)cy*(double)cellInPixelsX/2.0;
		double y = m_nOriginY - (double)cy*(double)cellInPixelsY/2.0-(double)cx*(double)cellInPixelsY/2.0 - cellInPixelsY/2.0;
		cx = (int)x;
		cy = (int)y;
	}

	__Dir	getDirBetween2Cells(int cx1,int cy1,int cx2,int cy2);
	__Dir	getDirBetween2Points(const Point& pos1,const Point& pos2);
	
	int		getCellMask(int cx,int cy);
	void	setCellMask(int cx,int cy,int mask);

protected:
	Cell*	m_arrayCells;		// 逻辑坐标
};

#endif
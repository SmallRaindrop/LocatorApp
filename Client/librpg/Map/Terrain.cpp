#include "Terrain.h"

__Dir angleToDir(float angle)
{
	//float degree = CC_RADIANS_TO_DEGREES(angle);

	if ( ( angle >= 0 && angle <= M_PI/8 + 0.001 /* add by 0.001,fixing the 'moon walk' */ ) 
		|| ( angle < 0 && angle >= -M_PI/8 - 0.001 ))
	{
		return DIR_E;
	}
	else if( angle > M_PI/8 && angle <= M_PI/8*3 + 0.001 )
	{
		return DIR_NE;
	}
	else if( angle > M_PI/8*3 && angle <= M_PI/8*5 + 0.001 )
	{
		return DIR_N;
	}
	else if( angle > M_PI/8*5 && angle <= M_PI/8*7 + 0.001 )
	{
		return DIR_NW;
	}
	else if( ( angle > M_PI/8*7 && angle <= M_PI + 0.001 )
		|| ( angle > -M_PI && angle <= -M_PI/8*7 + 0.001 ))
	{
		return DIR_W;
	}
	else if( angle > -M_PI/8*7 && angle <= -M_PI/8*5 + 0.001)
	{
		return DIR_SW;
	}
	else if( angle > -M_PI/8*5 && angle <= -M_PI/8*3 + 0.001  )
	{
		return DIR_S;
	}
	else if( angle > -M_PI/8*3 && angle <= -M_PI/8 + 0.001 )
	{
		return DIR_SE;
	}

	return DIR_SE;
}

__Dir vectorToDir(const Point& vec)
{
	return angleToDir(vec.getAngle());
}

CTerrain::CTerrain() : m_nOriginX(0),m_nOriginY(0),m_nCellX(0),m_nCellY(0),m_arrayCells(NULL)
{

}

CTerrain::~CTerrain()
{
	// 此处不用释放了，由map_context统一释放
	//if ( m_arrayCells )
	//{
	//	delete[] m_arrayCells;
	//}
}

void CTerrain::initMask(int width,int height)
{
	Rect rect(1,1,width-1,height-1);

	for(int j = 0; j < m_nCellY; j ++)
	{
		for(int i = 0; i < m_nCellX; i ++)
		{
			if ( i == 0 || i == m_nCellX-1 || j == 0 || j == m_nCellY-1 )
			{
				setCellMask(i,j,cellMaskStop);
				continue;
			}
			// 判断Cell中心是否不在地图内
			int x = i;
			int y = j;
			cell2World(x,y);

			if ( !rect.containsPoint(Point(x,y)) )
			{
				setCellMask(i,j,cellMaskStop);
			}
			
		}
	}
}

void CTerrain::initWithMapContext(map_context* context)
{
	// 如果是从PSD加载的数据，需要创建CELL数据
	if ( context->type == MAP_CONTEXT_PSD )
	{
		m_nOriginX = context->header.width/2;
		m_nOriginY = context->header.height/2;

		m_nCellX = 0;
		m_nCellY = 0;

		int cx=0;
		int cy=0;

		while( true ){
			++m_nCellX;++m_nCellY;m_nOriginY+=cellInPixelsY/2;
			cx = context->header.width;
			cy = context->header.height;
			world2Cell(cx,cy);

			if ( 0 <= cx && cx <= m_nCellX && 0 <= cy && cy <= m_nCellY )
			{
				break;
			}
		}

		m_arrayCells = new Cell[getCellMax()];
		memset(m_arrayCells,0,getCellMax());

		context->terrain.cell_size_x = m_nCellX;
		context->terrain.cell_size_y = m_nCellY;
		context->terrain.cell_origin_x = m_nOriginX;
		context->terrain.cell_origin_y = m_nOriginY;

		initMask(context->header.width,context->header.height);
		context->terrain.cell_data = (unsigned char*)m_arrayCells;
		context->terrain.cell_data_size = getCellMax()*sizeof(Cell);
	}
	else if( context->type == MAP_CONTEXT_MAP )
	{
		m_nCellX = context->terrain.cell_size_x;
		m_nCellY = context->terrain.cell_size_y;
		m_nOriginX = context->terrain.cell_origin_x;
		m_nOriginY = context->terrain.cell_origin_y;

		m_arrayCells = (Cell*)context->terrain.cell_data;
	}
}

int	CTerrain::getCellMask(int cx,int cy)
{
	Cell* pCell = getCell(cx,cy);
	if ( pCell )
	{
		return pCell->uMask;
	}

	return cellMaskNone;
}

void CTerrain::setCellMask(int cx,int cy,int mask)
{
	Cell* pCell = getCell(cx,cy);
	if ( pCell )
	{
		pCell->Zero();
		pCell->Mark(mask);
	}
}

__Dir CTerrain::getDirBetween2Cells(int cx1,int cy1,int cx2,int cy2)
{
	int x1 = cx1;
	int y1 = cy1;
	int x2 = cx2;
	int y2 = cy2;

	cell2World(x1,y1);
	cell2World(x2,y2);

	return getDirBetween2Points(Point(x1,y1),Point(x2,y2));
}

__Dir CTerrain::getDirBetween2Points(const Point& pos1,const Point& pos2)
{
	Point vec = (pos2-pos1).normalize();
	return vectorToDir(vec);
}
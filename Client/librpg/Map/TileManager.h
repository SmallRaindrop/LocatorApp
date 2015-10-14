#ifndef __TileLayer_h_
#define __TileLayer_h_

#include "GameDef.h"
#include "map_def.h"
#include "ShaderSprite.h"

#define TileFlagNone	0
#define TileFlagLoading	1
#define TileFlagShowing	2

struct TileInfo{
	int			tag;
	int			flag;
	ShaderSprite*		spr;
	TileInfo() : tag(0),flag(TileFlagNone),spr(NULL){}
};

class CTileManager : public Ref
{
public:
	CTileManager();
	~CTileManager();

public:
	void	initWithMapContext(map_context* context);
	void	convertToMapContext(map_context* context);

public:
	inline void index2Tile(int idx,int& tx,int& ty)
	{
		tx = idx%m_nTileX;
		ty = idx/m_nTileX;
	}

	inline int	tile2Index(int tx,int ty)
	{
		return ty*m_nTileX+tx;
	}
	
	inline void tile2World(int& tx,int& ty)
	{
		//int x = tx*tileInPixelsX+tileInPixelsX/2;
		//int y = (m_nTileY-ty)*tileInPixelsY-tileInPixelsY/2;

		int x = tx*tileInPixelsX;
		int y = (m_nTileY-ty)*tileInPixelsY-tileInPixelsY;
		tx = x;
		ty = y;
	}

	inline void world2Tile(int& x,int& y)
	{
		int tx = x/tileInPixelsX;
		int ty = m_nTileY-y/tileInPixelsY-1;
		x = tx;
		y = ty;
	}

	inline void world2TileOffset(int& x,int& y)
	{
		int tx = x;
		int ty = y;
		world2Tile(tx,ty);
		tile2World(tx,ty);
		x -= tx;
		y -= ty;
	}

	inline TileInfo* getTile(int tx,int ty){return getTile(tile2Index(tx,ty)); }
	inline TileInfo* getTile(int tag){ return (size_t)tag < m_vTiles.size() ? &m_vTiles[tag] : NULL; }
	inline void		 getTileRect(int tx,int ty,Rect& rect){ tile2World(tx,ty); rect = Rect((float)tx,(float)ty,tileInPixelsX,tileInPixelsY); }
	
protected:
	CC_SYNTHESIZE_READONLY(int,m_nTileX,TileX);
	CC_SYNTHESIZE_READONLY(int,m_nTileY,TileY);
	vector<TileInfo>	m_vTiles;
	
};

#endif
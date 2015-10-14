#include "TileManager.h"

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
CTileManager::CTileManager() : m_nTileX(0),m_nTileY(0)
{
	
}

CTileManager::~CTileManager()
{

}

void CTileManager::initWithMapContext(map_context* context)
{
	m_nTileX = context->header.width/tileInPixelsX;
	m_nTileY = context->header.height/tileInPixelsY;

	m_vTiles.resize(m_nTileX*m_nTileY);

	for ( size_t i = 0;i<m_vTiles.size(); ++i )
	{
		m_vTiles[i].tag = (int)i;
	}
}
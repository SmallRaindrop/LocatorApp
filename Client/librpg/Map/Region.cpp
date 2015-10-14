#include "Region.h"

CRegion::CRegion() : m_nOriginX(0),m_nOriginY(0),m_nSizeX(0),m_nSizeY(0)
{

}

CRegion::CRegion(int cx,int cy,int sx,int sy) : m_nOriginX(cx),m_nOriginY(cy),m_nSizeX(sx),m_nSizeY(sy)
{

}

CRegion::~CRegion()
{

}

bool CRegion::initWithMapRegion(map_region* region)
{
	m_nOriginX = region->x;
	m_nOriginY = region->y;
	m_nSizeX = region->w;
	m_nSizeY = region->h;

	for ( int i = 0;i<region->property_count;++i )
	{
		
		m_Properties[region->properties[i].name] = region->properties[i].val;
	}

	return true;
}

void CRegion::getMapRegionData(map_region* region)
{
	region->x = m_nOriginX;
	region->y = m_nOriginY;
	region->w = m_nSizeX;
	region->h = m_nSizeY;

	region->property_count = m_Properties.size();
	region->properties = new map_region_property[region->property_count];
	int idx = 0;
	for (RegionProperties::iterator itr = m_Properties.begin(); itr != m_Properties.end();++itr)
	{
		region->properties[idx].name = itr->first;
		region->properties[idx++].val = itr->second;
	}
}

void CRegion::addProperty(string name,int val)
{
	RegionProperties::iterator itr = m_Properties.find(name);
	if ( itr == m_Properties.end() )
	{
		m_Properties[name] = val;
	}
	else
	{
		itr->second = val;
	}
}

int	CRegion::getProperty(string name)
{
	RegionProperties::iterator itr = m_Properties.find(name);
	if ( itr == m_Properties.end() )
	{
		return 0;
	}

	return itr->second;
}

void CRegion::setProperty(string name,int val)
{
	RegionProperties::iterator itr = m_Properties.find(name);
	if ( itr != m_Properties.end() )
	{
		itr->second = val;
	}
}

void CRegion::removeProperty(string name)
{
	RegionProperties::iterator itr = m_Properties.find(name);
	if ( itr != m_Properties.end() )
	{
		m_Properties.erase(itr);
	}
}

void CRegion::removeAllProperty()
{
	m_Properties.clear();
}

bool CRegion::containsCell(int cx,int cy)
{
	return ( m_nOriginX <= cx && cx <= m_nOriginX + m_nSizeX &&
				m_nOriginY <= cy && cy <= m_nOriginY + m_nSizeY ) ;
}

// add by wenzy
bool CRegion::isMonsterRegion()
{
	RegionProperties::iterator itr = m_Properties.find("monster_type_id");
	if ( itr == m_Properties.end() )
	{
		return false;
	}
	else
	{
		return true;
	}
}
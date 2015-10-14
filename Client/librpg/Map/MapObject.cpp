#include "MapObject.h"
#include "TileMap.h"
#include <assert.h>
#include "Log.h"

int MapObject::s_ID_COUNTER = 0;

MapObject::MapObject() : m_pMap(NULL)
{
	m_Info.id = ++s_ID_COUNTER;
}

MapObject::MapObject(MapObjectInfo& info) : m_pMap(NULL)
{
	memcpy(&m_Info,&info,sizeof(MapObjectInfo));
}

MapObject::~MapObject()
{

}

void MapObject::setPosition(float x,float y)
{
	setPosition(Point(x,y));
	//if ( m_pMap )
	//{
	//	setLocalZOrder(zOrderObject+m_pMap->getMapHeight()-y);
	//}
}

void MapObject::setPosition(const Point &position)
{
	Node::setPosition(position);
	//if ( m_pMap )
	//{
	//	setLocalZOrder(zOrderObject+m_pMap->getMapHeight()-position.y);
	//	// add by wenzy, handle mask object
	//	m_pMap->updateMaskObj(position);
	//}
}

int MapObject::compareZ(MapObject* pObj)
{
	int type =  pObj->GetType();
	switch ( type )
	{
	case mapObjectType_Mask:
		{
			return (-1)*pObj->compareZ(this);
		}
	case mapObjectType_Effect:
	case mapObjectType_Item:
	case mapObjectType_Chests:
	case mapObjectType_Npc:
	case mapObjectType_Monster:
	case mapObjectType_Player:
		{
			return (int)(pObj->getPositionY() - getPositionY()); 
		}
		break;
	default:
		break;
	}

	return 0;
}

void MapObject::UpdatePos()
{
	if ( m_pMap )
	{
		int cx = GetCellX();
		int cy = GetCellY();

		m_pMap->getTerrain()->cell2World(cx,cy);
		setPosition(Point(cx+GetOffsetX(),cy+GetOffsetY()));
	}
}

void MapObject::SetCell(int cx,int cy)
{
	m_Info.cx = cx;
	m_Info.cy = cy;

	UpdatePos();

	UpdateBoundingInfo();

	if ( m_pMap )
	{
		Cell* pCell = m_pMap->getTerrain()->getCell(cx,cy);
		if ( !pCell )
		{
			return ;
		}

		if ( pCell->isMark(cellMaskCover))
		{
			onCover(true);
		}
		else
		{
			onCover(false);
		}

		CRegion* pRegionOld = m_pMap->getRegionManager()->getRegionDoor(m_Info.cx,m_Info.cy);
		CRegion* pRegionNew = m_pMap->getRegionManager()->getRegionDoor(cx,cy);
		if ( pRegionNew != pRegionOld )
		{
			if ( pRegionOld )
			{
				onLeaveDoor(pRegionOld);
			}
			if ( pRegionNew )
			{
				onEnterDoor(pRegionNew);
			}
		}

		RegionList listOld;
		RegionList listNew;
		m_pMap->getRegionManager()->getRegionList(m_Info.cx,m_Info.cy,listOld);
		m_pMap->getRegionManager()->getRegionList(cx,cy,listNew);

		for ( RegionList::iterator itr1 = listOld.begin();itr1 != listOld.end(); ++itr1 )
		{
			CRegion* pRegion1 = *itr1;

			bool ignore = false;
			for ( RegionList::iterator itr2 = listNew.begin();itr2 != listNew.end();++itr2 )
			{
				CRegion* pRegion2 = *itr2;
				if ( pRegion2 == pRegion1 )
				{
					listNew.erase(itr2);
					ignore = true;
					break;
				}
			}

			if ( !ignore )
			{
				onLeaveRegion(pRegion1);
			}
		}

		for ( RegionList::iterator itr = listNew.begin();itr != listNew.end();++itr )
		{
			CRegion* pRegion = *itr;
			if ( pRegion )
			{
				onEnterRegion(pRegion);
			}
		}
	}
}

const Rect& MapObject::getBoundingBox()
{
	return m_CollisionRect;
}

Point MapObject::getHungingPoint(int idx)
{
	if ( idx >= 0 && idx < (int)m_HungingPoints.size() )
	{
		return m_HungingPoints[idx];
	}
	return getPosition();
}

 Point MapObject::getHungingPointOffset(int idx)
 {
	 return getHungingPoint(idx)-getPosition();
 }

void MapObject::SetBoundingInfo(int sizeX,int sizeY,int h)
{
	m_Info.sizeX = sizeX;
	m_Info.sizeY = sizeY;
	m_Info.height = h;

	UpdateBoundingInfo();
}

void MapObject::UpdateBoundingInfo()
{
	if ( !GetMap() )
	{
		return ;
	}

	// 计算区域左右顶点
	int x = GetCellX();
	int y = GetCellY();

	int MaxX = x + GetSizeX() / 2 + GetSizeX() % 2;
	int MinX = x - GetSizeX() / 2;
	int MaxY = y + GetSizeY() / 2 + GetSizeY() % 2;
	int MinY = y - GetSizeY() / 2;

	int lx = MinX;
	int ly = MaxY;
	int rx = MaxX;
	int ry = MinY;

	m_RegionCell = Rect(MinX,MinY,GetSizeX(),GetSizeY());

	GetMap()->getTerrain()->cell2World(lx,ly);
	GetMap()->getTerrain()->cell2World(rx,ry);

	lx -= cellInPixelsX / 2;
	rx += cellInPixelsX / 2;

	// 生成碰撞区域
	m_CollisionRect = Rect(lx,ly,rx-lx,GetHeight());

	// 生成挂点信息
	m_HungingPoints.clear();
	m_HungingPoints.push_back(Point(m_CollisionRect.getMidX(),m_CollisionRect.getMaxY()));
	m_HungingPoints.push_back(Point(m_CollisionRect.getMinX()+16,m_CollisionRect.getMinY()+GetHeight()*0.65f));
	m_HungingPoints.push_back(Point(m_CollisionRect.getMidX(),m_CollisionRect.getMinY()+GetHeight()*0.65f));
	m_HungingPoints.push_back(Point(m_CollisionRect.getMaxX()-16,m_CollisionRect.getMinY()+GetHeight()*0.65f));
	m_HungingPoints.push_back(Point(m_CollisionRect.getMidX(),m_CollisionRect.getMinY()));
}

void MapObject::SetOffset(float x,float y)
{ 
	m_Info.offsetX = x;
	m_Info.offsetY = y;
	UpdatePos();
}

bool MapObject::CheckSelected(float x,float y)
{
	if ( m_CollisionRect.containsPoint(Point(x,y)) )
	{
		return true;
	}

	return false;
}

void MapObject::EnterMap(TileMap* pMap,const Point& pos)
{
	if ( !pMap )
	{
		return;
	}

	// 如果此对象已经在地图中
	if ( m_pMap )
	{
		LOGW("map object[%d][%lld] entermap repeate.",GetType(),GetId());
		LeaveMap();
	}

	m_pMap = pMap;

	// 先进地图再进视野
	m_pMap->objectEnterMap(this,pos);

	m_pMap->objectEnterSight(this);
}

void MapObject::EnterMap(TileMap* pMap,int cx,int cy)
{
	if ( !pMap )
	{
		return;
	}

	// 如果此对象已经在地图中
	if ( m_pMap )
	{
		LOGW("map object[%d][%lld] entermap repeate.",GetType(),GetId());
		LeaveMap();
	}

	m_pMap = pMap;

	// 先进地图再进视野
	m_pMap->objectEnterMap(this,cx,cy);

	m_pMap->objectEnterSight(this);
}

void MapObject::LeaveMap()
{
	if(m_pMap)
	{
		TileMap* pMap = m_pMap;
		m_pMap = NULL;
		pMap->objectLeaveMap(this);

		// m_pMap = NULL;	// 问题代码
	}
}

void MapObject::EnterMapWithEffect(TileMap* pMap,int cx,int cy)
{
	EnterMap(pMap,cx,cy);

	onPreEnterSight();
}

void MapObject::LeaveMapWithEffect()
{
	SetLeaved(true);

	onPreLeaveSight();
}

void MapObject::onEnterSight()
{
	SetInsight();
}

void MapObject::onLeaveSight()
{
	SetInsight(false);
}

void MapObject::onPreEnterSight()
{
	stopAllActions();
	setOpacity(0);
	ActionInterval* pAction = FadeIn::create(0.5f);
	runAction(Sequence::create(pAction,CallFunc::create( CC_CALLBACK_0(MapObject::onEnterSightCallBack,this)),NULL));
}

void MapObject::onPreLeaveSight()
{
	stopAllActions();
	ActionInterval* pAction = FadeOut::create(0.5f);
	runAction(Sequence::create(pAction,CallFunc::create( CC_CALLBACK_0(MapObject::onLeaveSightCallBack,this)),NULL));
}

void MapObject::onEnterSightCallBack()
{
	if ( m_pMap )
	{
		Cell* pCell = m_pMap->getTerrain()->getCell(GetCellX(),GetCellY());
		if ( !pCell )
		{
			return ;
		}

		if ( pCell->isMark(cellMaskCover))
		{
			onCover(true);
		}
		else
		{
			onCover(false);
		}
	}
}

void MapObject::onLeaveSightCallBack()
{
	if ( GetLeaved() )
	{
		LeaveMap();
	}
}
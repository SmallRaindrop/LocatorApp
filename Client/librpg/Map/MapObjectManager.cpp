#include "MapObjectManager.h"
#include "TileMap.h"
#include "Role/RoleData.h"
#include "GameDef.h"

CMapObjectManager::CMapObjectManager(TileMap* pMap) : m_pMap(pMap) 
{

}

CMapObjectManager::~CMapObjectManager()
{

}

bool CMapObjectManager::init()
{
	return true;
}

void CMapObjectManager::release()
{
	clear();
	Ref::release();
}

void CMapObjectManager::clear()
{
	for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr )
	{
		MapObject* pObject = *itr;
		if ( pObject )
		{
			pObject->release();
		}
	}

	m_Objects.clear();
}

int	CMapObjectManager::getObjectsInView(MapObjectList& objects)
{
	Rect rect;
	m_pMap->getViewRect(rect);

	float x = 0;
	float y = 0;

	for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr)
	{
		MapObject* pObject = *itr;
		if ( pObject && !pObject->GetDeleted() )
		{
			x = pObject->getPositionX();
			y = pObject->getPositionY();

			if ( rect.containsPoint(Point(x,y)))
			{
				objects.push_back(pObject);
			}
		}
	}

	return (int)objects.size();
}

int	CMapObjectManager::getObjectsInView(MapObjectType type,MapObjectList& objects)
{
	Rect rect;
	m_pMap->getViewRect(rect);

	float x = 0;
	float y = 0;

	for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr)
	{
		MapObject* pObject = *itr;
		if ( pObject && !pObject->GetDeleted() )
		{
			x = pObject->getPositionX();
			y = pObject->getPositionY();

			if ( rect.containsPoint(Point(x,y)) && pObject->GetType() == type )
			{
				objects.push_back(pObject);
			}
		}
	}

	return (int)objects.size();
}

MapObject*	CMapObjectManager::getObjectNearBy(int cx,int cy,MapObjectType type)
{
	Rect rect;
	m_pMap->getViewRect(rect);

	float x = 0;
	float y = 0;

	MapObject* pRet = NULL;
	const int minD = 3;     //最小格子距离
	for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr)
	{
		MapObject* pObject = *itr;
		if ( pObject  && !pObject->GetDeleted() )
		{
			x = pObject->getPositionX();
			y = pObject->getPositionY();
			int distance = Distance(cx,cy,pObject->GetCellX(),pObject->GetCellY());
			if ( rect.containsPoint(Point(x,y)) && pObject->GetType() == type  && distance < minD )
			{
				pRet = pObject;
				//minD = distance;
			}
		}
	}

	return pRet;
}

MapObject*	CMapObjectManager::getObject(MapObjectID id)
{
	for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr)
	{
		MapObject* pObject = *itr;
		if ( pObject && !pObject->GetDeleted() && pObject->GetId() == id )
		{
			return pObject;
		}
	}

	return NULL;
}

MapObject*	CMapObjectManager::getObject(int cx,int cy)
{
	for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr)
	{
		MapObject* pObject = *itr;
		if ( pObject  && !pObject->GetDeleted() && pObject->GetCellX() == cx && pObject->GetCellY() == cy )
		{
			return pObject;
		}
	}

	return NULL;
}

MapObject*	CMapObjectManager::SelectObject(float x,float y,MapObject* pExclude )
{
	MapObjectList objects;
	SelectObjects(x,y,objects);

	MapObject* pRet = NULL; 
	for ( size_t i = 0;i<objects.size();++i )
	{
		MapObject* pObject = objects[i];
		if ( pObject == pExclude || pObject->GetDeleted())
		{
			continue;
		}

		if ( !pRet )
		{
			pRet = pObject;
			continue;
		}

		if ( pRet->getZOrder() < pObject->getZOrder() )
		{
			pRet = pObject;
		}
	}

	return pRet;
}

int CMapObjectManager::SelectObjects(Point pos,MapObjectList& objects)
{
	return SelectObjects(pos.x,pos.y,objects);
}

int	CMapObjectManager::SelectObjects(float x,float y,MapObjectList& objects)
{
	objects.clear();
	for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr)
	{
		MapObject* pObject = *itr;
		if ( pObject  && !pObject->GetDeleted() && pObject->CheckSelected(x,y) )
		{
			objects.push_back(pObject);
		}
	}

	return (int)objects.size();
}

int	CMapObjectManager::getObjects(MapObjectType type,MapObjectList& objects)
{
	objects.clear();
	for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr)
	{
		MapObject* pObject = *itr;
		if ( pObject  && !pObject->GetDeleted() && pObject->GetType() == type )
		{
			objects.push_back(pObject);
		}
	}

	return (int)objects.size();
}

int	CMapObjectManager::getObjects(int cx,int cy,MapObjectList& objects)
{
	objects.clear();
	for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr)
	{
		MapObject* pObject = *itr;
		if ( pObject  && !pObject->GetDeleted() && pObject->GetCellX() == cx && pObject->GetCellY() == cy )
		{
			objects.push_back(pObject);
		}
	}

	return (int)objects.size();
}

void CMapObjectManager::addObject(MapObject* pObject)
{
	if ( pObject )
	{
		m_Objects.push_back(pObject);
		pObject->retain();
	}
}

void CMapObjectManager::removeObject(MapObject* pObject)
{
	if ( pObject )
	{
		for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr )
		{
			if ( pObject == *itr )
			{
				m_Objects.erase(itr);
				pObject->release();
				return ;
			}
		}
	}
}

int CMapObjectManager::getTopObject(MapObject** objs,int len,int idx/* = 0*/)
{
	for ( int i = idx;i<len;++i )
	{
		bool bCover = false;
		for (int j = idx; j < len; j++)
		{
			if ( i == j )
			{
				continue;
			}
			if ( objs[j]->compareZ(objs[i]) > 0 )
			{
				bCover = true;
				break;
			}
		}
		if ( bCover )
		{
			continue;
		}
		else
		{
			return i;
		}
	}

	return idx;
}

void CMapObjectManager::sortZorder(MapObject** objs,int len)
{
	int idx = 0;
	while (idx < len)
	{
		// 找出当前最上层的元素对象（没有任何元素对象遮挡）
		int ret = getTopObject(objs,len,idx);
		assert(ret != -1);
		MapObject* obj = objs[idx];
		objs[idx] = objs[ret];
		objs[ret] = obj;
		idx++;
	}
}

//int compare(MapObject** obj1,MapObject** obj2)
//{
//	return (*obj2)->compareZ(*obj1) ? 1 : -1;
//}

void CMapObjectManager::update(float dt)
{
	MapObject* array[1024] = {0};
	int len = 0;
	assert(m_Objects.size() < 1024);
	for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end(); )
	{
		MapObject* pObject = *itr;

		// 清理掉被标记为删除的，和没有地图的野对象
		if ( !pObject || pObject->GetDeleted() || !pObject->GetMap() )
		{
			CC_SAFE_RELEASE(pObject);
			itr = m_Objects.erase(itr);
			continue;
		}

		// 合法的对象加入新的列表
		array[len++] = pObject;
		pObject->retain();
		++itr;
	}

	// 对新列表按照遮挡关系排序
	//qsort(array,len,sizeof(MapObject*),(int (__cdecl *)(const void *,const void *))compare);
	sortZorder(array,len);
	
	for ( int i = 0;i<len;++i )
	{
		array[i]->setLocalZOrder(len-i);
		array[i]->update(dt);
		array[i]->release();
		array[i] = NULL;
	}
}

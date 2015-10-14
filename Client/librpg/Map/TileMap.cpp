#include "TileMap.h"
#include "MapEffect.h"
#include "map_io.h"

TileMap::TileMap() : m_nWidth(0),m_nHeight(0),m_bTileGrid(false),m_bCellGrid(false),m_bRegionGrid(false),m_bGrey(false),
	m_pTerrain(NULL),
	m_pTileMgrFar(NULL),
	m_pTileMgrNear(NULL),
	m_pObjectManager(NULL),
	m_pRegionManager(NULL),
	m_pContext(NULL),
	m_pAStar(NULL),
	m_mapLoader(this)
{

}

TileMap::~TileMap()
{
	clearMask();
	clearMapPartInfo();
	CC_SAFE_RELEASE(m_pTileMgrFar);
	CC_SAFE_RELEASE(m_pTileMgrNear);
	CC_SAFE_RELEASE(m_pTerrain);
	CC_SAFE_RELEASE(m_pObjectManager);
	CC_SAFE_RELEASE(m_pRegionManager);
	CC_SAFE_DELETE(m_pAStar);
	map_io::map_free(m_pContext);
}

TileMap* TileMap::createWithMapContext(map_context* context)
{
	TileMap* ret = new TileMap;
	if ( ret && ret->init() && ret->initWithMapContext(context))
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return NULL;
}

bool TileMap::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	// 逻辑相关
	m_pTileMgrFar = new CTileManager();
	if ( !m_pTileMgrFar )
	{
		return false;
	}
	m_pTileMgrNear = new CTileManager();
	if ( !m_pTileMgrNear )
	{
		return false;
	}
	m_pTerrain = new CTerrain();
	if ( !m_pTerrain )
	{
		return false;
	}
	m_pObjectManager = new CMapObjectManager(this);
	if ( !m_pObjectManager )
	{
		return false;
	}
	m_pRegionManager = new CRegionManager();
	if ( !m_pRegionManager )
	{
		return false;
	}

	// 地图分层
	m_pFarLayer = Layer::create();
	if ( !m_pFarLayer )
	{
		return false;
	}
	m_pTerrainLayer = Layer::create();
	if ( !m_pTerrainLayer )
	{
		return false;
	}
	m_pObjectLayer = Layer::create();
	if ( !m_pObjectLayer )
	{
		return false;
	}
	m_pMaskLayer = Layer::create();
	if ( !m_pMaskLayer )
	{
		return false;
	}
	m_pSkyLayer = Layer::create();
	if ( !m_pSkyLayer )
	{
		return false;
	}

	addChild(m_pFarLayer,zOrderFar-10,0);
	addChild(m_pTerrainLayer,zOrderTerrain-10,0);
	addChild(m_pObjectLayer,zOrderObject-10,0);
	addChild(m_pMaskLayer,zOrderMask-10,0);
	addChild(m_pSkyLayer,zOrderSky-10,0);

	setAnchorPoint(Point(0,0));

	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	setTouchEnabled(true);

	return true;
}
//
//bool TileMap::initWithPSD(const char* psd)
//{
//	if ( !psd )
//	{
//		return false;
//	}
//
//
//	map_context* context = new map_context;
//	if ( !context )
//	{
//		return false;
//	}
//
//	int ret = map_io::load_from_psd(psd,context);
//	if ( ret != MAP_STATUS_OK )
//	{
//		map_io::map_free(context);
//		return false;
//	}
//
//	if( !initWithMapContext(context) )
//	{
//		map_io::map_free(context);
//		return false;
//	}
//
//	m_sMapName = StringUtil::StringCutFileName(psd);
//
//	map_io::map_save(getMapFileName().c_str(),context);
//
//	return true;
//}
//
//bool TileMap::initWithMAP(const char* map)
//{
//	if ( !map )
//	{
//		return false;
//	}
//
//	map_context* context = new map_context;
//	if ( !context )
//	{
//		return false;
//	}
//
//	int ret = map_io::load_from_map(map,context);
//	if ( ret != MAP_STATUS_OK )
//	{
//		map_io::map_free(context);
//		return false;
//	}
//
//	if( !initWithMapContext(context) )
//	{
//		map_io::map_free(context);
//		return false;
//	}
//
//	m_sMapName = StringUtil::StringCutFileName(map);
//
//	return true;
//}

bool TileMap::initWithMapContext(map_context* context)
{
	m_nWidth = context->header.width;
	m_nHeight = context->header.height;

	// 加入遮挡元素
	for ( int i = 0;i<context->mask_count;++i )
	{
		m_vMasks.push_back(new MapMaskInfo(i,&context->masks[i]));
	}
	
	getTileMgrNear()->initWithMapContext(context);
	getTerrain()->initWithMapContext(context);

	// 加入部件
	for (int i = 0; i < context->part_count; i++)
	{
		MapPartInfo* pPart = new MapPartInfo;
		pPart->info.dataid = context->parts[i].dataid;
		pPart->info.name = context->parts[i].name;
		pPart->info.x = context->parts[i].x;
		pPart->info.y = context->parts[i].y;
		pPart->info.h = context->parts[i].h;
		addMapPartInfo(pPart);
	}

	// 加入区域
	for (int i = 0; i < context->region_count; i++)
	{
		CRegion* pRegion = new CRegion;
		pRegion->initWithMapRegion(&context->regions[i]);

		switch (pRegion->getProperty("region_type"))
		{
		case 0: getRegionManager()->addRegion(pRegion);break;
		case 1: getRegionManager()->addNpcRegion(pRegion);break;
		case 2: getRegionManager()->addMonsterRegion(pRegion);break;
		case 3: getRegionManager()->addDoorRegion(pRegion);break;
		default: delete pRegion;
			break;
		}
	}

	m_pContext = context;

	return initAStar();
}

void TileMap::updateMapContext()
{
	// 部件数据
	// 清空原来的部件数据
	if ( m_pContext->parts )
	{
		delete[] m_pContext->parts;
		m_pContext->parts = NULL;
	}
	m_pContext->part_count = 0;

	if ( m_vParts.size() > 0)
	{
		map_part* parts = new map_part[m_vParts.size()];
		for ( size_t i = 0;i<m_vParts.size(); ++i )
		{
			MapPartInfo* pPart = m_vParts[i];
			parts[i].dataid = pPart->info.dataid;
			parts[i].name = pPart->info.name;
			parts[i].x = pPart->info.x;
			parts[i].y = pPart->info.y;
			parts[i].h = pPart->info.h;
		}

		m_pContext->parts = parts;
		m_pContext->part_count = m_vParts.size();
	}
	
	// 区域数据
	// 清空原来的区域数据
	if ( m_pContext->regions )
	{
		for(int i=0;i<m_pContext->region_count;++i)
		{
			if( m_pContext->regions[i].properties )
			{
				delete[] m_pContext->regions[i].properties;
			}
		}

		delete[] m_pContext->regions;
		m_pContext->regions = NULL;
	}

	m_pContext->region_count = getRegionManager()->getRegionList()->size()
		+getRegionManager()->getNpcList()->size()
		+getRegionManager()->getMonsterList()->size()
		+getRegionManager()->getDoorList()->size();

	if ( m_pContext->region_count > 0 )
	{
		m_pContext->regions = new map_region[m_pContext->region_count];
		int idx = 0;
		for ( size_t i = 0;i<getRegionManager()->getRegionList()->size();++i )
		{
			CRegion* pRegion = getRegionManager()->getRegionList()->at(i);
			if ( pRegion )
			{
				pRegion->getMapRegionData(&(m_pContext->regions[idx++]));
			}
		}
		for ( size_t i = 0;i<getRegionManager()->getNpcList()->size();++i )
		{
			CRegion* pRegion = getRegionManager()->getNpcList()->at(i);
			if ( pRegion )
			{
				pRegion->getMapRegionData(&(m_pContext->regions[idx++]));
			}
		}
		for ( size_t i = 0;i<getRegionManager()->getMonsterList()->size();++i )
		{
			CRegion* pRegion = getRegionManager()->getMonsterList()->at(i);
			if ( pRegion )
			{
				pRegion->getMapRegionData(&(m_pContext->regions[idx++]));
			}
		}
		for ( size_t i = 0;i<getRegionManager()->getDoorList()->size();++i )
		{
			CRegion* pRegion = getRegionManager()->getDoorList()->at(i);
			if ( pRegion )
			{
				pRegion->getMapRegionData(&(m_pContext->regions[idx++]));
			}
		}
	}
}

bool TileMap::initAStar()
{
	if ( m_pAStar )
	{
		CC_SAFE_DELETE(m_pAStar);
	}

	class MapTerrain : public AGenerator
	{
	public:
		MapTerrain(TileMap* pMap) : m_pMap(pMap){}
		~MapTerrain(){}

		bool isBlock(int cx,int cy){ return m_pMap->getTerrain()->getCellMask(cx,cy) == cellMaskStop; }

		TileMap* m_pMap;
	};

	MapTerrain t(this);
	m_pAStar = new AStar(getTerrain()->getCellX(),getTerrain()->getCellY(),&t);

	return m_pAStar != NULL;
}


void TileMap::searchForPath(int cx0,int cy0,int cx1,int cy1,APath& path)
{
	path.clear(); 

	if ( m_pAStar )
	{
		m_pAStar->searchForPath(APoint(cx0,cy0),APoint(cx1,cy1),path);
	}
}

void TileMap::addMapPartInfo(MapPartInfo* pInfo)
{
	if ( pInfo )
	{
		m_vParts.push_back(pInfo);
	}
}

void TileMap::clearMapPartInfo()
{
	for ( MapPartList::iterator itr = m_vParts.begin();itr != m_vParts.end();++itr )
	{
		MapPartInfo* pInfo = *itr;
		if ( pInfo->obj )
		{
			pInfo->obj->LeaveMap();
			pInfo->obj = NULL;
		}

		delete pInfo;
	}

	m_vParts.clear();
}

void TileMap::removeMapPartInfo(MapPartInfo* pInfo)
{
	for ( MapPartList::iterator itr = m_vParts.begin();itr != m_vParts.end(); )
	{
		if ( *itr == pInfo )
		{
			if ( pInfo->obj )
			{
				pInfo->obj->LeaveMap();
			}
			delete pInfo;
			itr = m_vParts.erase(itr);
			return ;
		}
		else
		{
			++itr;
		}
	}
}

MapPartInfo* TileMap::getMapPartInfo(int cx,int cy)
{
	for ( MapPartList::iterator itr = m_vParts.begin();itr != m_vParts.end();++itr)
	{
		MapPartInfo* pPart = *itr;
		int x = pPart->info.x;
		int y = pPart->info.y;
		getTerrain()->world2Cell(x,y);
		if ( x == cx && y == cy )
		{
			return pPart;
		}
	}

	return NULL;
}

void TileMap::touchToNode(Point& pt)
{
	pt = convertToNodeSpace(pt);
}

void TileMap::nodeToView(Point& pt)
{
	kmMat4 mat = _camera.getTransform();
	kmVec3 vec3 = {pt.x, pt.y, 0};
	kmVec3 ret;
	kmVec3Transform(&ret, &vec3, &mat);
	pt = Point(ret.x, ret.y);
}

void TileMap::viewToNode(Point& pt)
{
	kmMat4 mat1, mat;
	mat1 = _camera.getTransform();
	kmMat4Inverse(&mat, &mat1);
	
	kmVec3 vec3 = {pt.x, pt.y, 0};
	kmVec3 ret;
	kmVec3Transform(&ret, &vec3, &mat);
	pt = Point(ret.x, ret.y);
}

float TileMap::GetMaxViewX()
{
	Size viewSize = gDirector->getVisibleSize();
	return m_nWidth-viewSize.width/getScaleX();
}

float TileMap::GetMaxViewY()
{
	Size viewSize = gDirector->getVisibleSize();
	return m_nHeight-viewSize.height/getScaleY();
}

void TileMap::centerMap()
{
	int cx = getTerrain()->getCellX()/2;
	int cy = getTerrain()->getCellY()/2;
	SetView(cx,cy);
}

void TileMap::moveMap(int x,int y)
{
	Point posView = m_viewPoint+Point(x,y);
	
	posView.x = MAX(posView.x, 0);
	posView.x = MIN(posView.x, GetMaxViewX());
	posView.y = MAX(posView.y, 0);
	posView.y = MIN(posView.y, GetMaxViewY());

	Rect rect;

	Size viewSize = gDirector->getVisibleSize();
	Point viewOrigin = gDirector->getVisibleOrigin();

	rect.setRect(viewOrigin.x+m_viewPoint.x,viewOrigin.y+m_viewPoint.y,(viewSize.width)/getScaleX(),(viewSize.height)/getScaleY());

	posView.x=posView.x+(rect.getMaxX()-rect.getMinX())/2;
	posView.y=posView.y+(rect.getMaxY()-rect.getMinY())/2;

	SetView(posView);
}

void TileMap::SetView(int cx,int cy)
{
	getTerrain()->cell2World(cx,cy);
	SetView(Point(cx,cy));
}

/************************************************************************/
/*  处理流程：
	1. 更新视野内所有的tiles
	2. 更新视野内所有的masks
	3. 
 */
/************************************************************************/
// 

void TileMap::SetView(Point pt)
{
	Size visibleSize = gDirector->getVisibleSize()/getScale();
	Point visibleOrigin = gDirector->getVisibleOrigin();

	pt.x=pt.x-(visibleOrigin.x+visibleSize.width/2);
	pt.y=pt.y-(visibleOrigin.y+visibleSize.height/2);

	m_viewPoint = pt;

	//CCLOG("m_viewPoint  (%f,%f)", m_viewPoint.x, m_viewPoint.y);

	_camera.setEye(m_viewPoint.x,m_viewPoint.y);
	_camera.setCenter(m_viewPoint.x,m_viewPoint.y,0);
	kmMat4 mat = _camera.getTransform();
	setAdditionalTransform(&mat);

	//refreshCellsInView();

	refreshTilesInView();
	refreshPartsInView();
}

bool TileMap::isCellInView(int cx,int cy)
{
	Rect rect;
	getViewRect(rect);

	m_pTerrain->cell2World(cx,cy);

	if ( rect.containsPoint(Point(cx+cellInPixelsX/2,cy+cellInPixelsY/2)) || 
		rect.containsPoint(Point(cx-cellInPixelsX/2,cy-cellInPixelsY/2)) || 
		rect.containsPoint(Point(cx-cellInPixelsX/2,cy+cellInPixelsY/2)) || 
		rect.containsPoint(Point(cx+cellInPixelsX/2,cy-cellInPixelsY/2)) )
	{
		return true;
	}

	return false;
}

void TileMap::objectEnterSight(MapObject* pObject)
{
	if ( !pObject )
	{
		return ;
	}

	pObject->onEnterSight();

	//for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr)
	//{
	//	if ( pObject == *itr )
	//	{
	//		return ;
	//	}
	//}
	//m_Objects.push_back(pObject);

	getObjectLayer()->addChild(pObject);
}

void TileMap::objectLeaveSight(MapObject* pObject)
{
	if ( !pObject )
	{
		return ;
	}

	pObject->onLeaveSight();
	/*for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();)
	{
	if ( pObject == *itr )
	{
	getObjectLayer()->removeChild(pObject,true);
	itr = m_Objects.erase(itr);
	return ;
	}
	else
	{
	++itr;
	}
	}*/

	getObjectLayer()->removeChild(pObject,true);
}

void TileMap::allObjectLeaveSight()
{
	for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr)
	{
		objectLeaveSight(*itr);
	}

	m_Objects.clear();
}

void TileMap::allObjectLeaveMap()
{

}

void TileMap::update(float dt)
{
	m_pObjectManager->update(dt);
}

void TileMap::updateTerLayer()
{

}

void TileMap::updateFarLayer()
{

}

void TileMap::objectEnterMap(MapObject* pObject,int cx,int cy)
{
	if ( pObject )
	{
		// 检查是否存在相同ID的对象不处理
		MapObject* pObjectOld = getObjectManager()->getObject(pObject->GetId());
		if( pObjectOld )
		{
			CCLOG("object enter map with the same id!");
			return ;
		}

		// 加入地图元素对象管理器
		getObjectManager()->addObject(pObject);

		pObject->SetCell(cx,cy);
		pObject->SetDeleted(false);
	}
}

void TileMap::objectEnterMap(MapObject* pObject,Point pos)
{
	if ( pObject )
	{
		int x = (int)pos.x;
		int y = (int)pos.y;
		getTerrain()->world2Cell(x,y);
		objectEnterMap(pObject,x,y);
		pObject->setPosition(pos);
	}
}

void TileMap::objectLeaveMap(MapObjectID id)
{
	MapObject* pObject = getObjectManager()->getObject(id);
	if ( pObject )
	{
		objectLeaveMap(pObject);
	}
}

void TileMap::objectLeaveMap(MapObject* pObject)
{
	if ( pObject )
	{
		// 先离开视野再离开地图
		objectLeaveSight(pObject);

		pObject->SetDeleted(true);
		// 移除地图元素对象管理器
		getObjectManager()->removeObject(pObject);
	}
}

bool TileMap::onTouchBegan(Touch *touch, Event *unused_event)
{
	Point pos = convertTouchToNodeSpace(touch);

	int cx = (int)pos.x;
	int cy = (int)pos.y;
	getTerrain()->world2Cell(cx,cy);

	// 部件层暂时不处理
	//m_pPartLayer->onTouch(cx,cy);

	for ( MapObjectList::iterator itr = m_Objects.begin();itr != m_Objects.end();++itr )
	{
		MapObject* pObject = *itr;
		if ( pObject && pObject->CheckSelected(cx,cy))
		{
			pObject->onSelect(true);
		}
	}

	return true;
}

void TileMap::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void TileMap::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void TileMap::onTouchCancelled(Touch *touch, Event *unused_event)
{

}

void TileMap::getViewRect(Rect& rect)
{
	Size viewSize = gDirector->getVisibleSize();
	Point viewOrigin = gDirector->getVisibleOrigin();

	// 可视范围包含预处理区域，所以会比屏幕实际可视范围应该大一些；
	Point offsetLD(-256.0f,-256.0f);
	Point offsetRU(512.0f,512.0f);
	rect.setRect(viewOrigin.x+m_viewPoint.x+offsetLD.x,viewOrigin.y+m_viewPoint.y+offsetLD.y,(viewSize.width+offsetRU.x)/getScaleX(),(viewSize.height+offsetRU.y)/getScaleY());
}

void TileMap::refreshTilesInView()
{
	vector<TileInfo*> tiles;
	getTilesNoneInView(tiles);

	vector<MapMaskInfo*> masks;
	getMasksNoneInView(masks);

	if ( tiles.size() > 0 || masks.size() > 0 )
	{
		TileMapLoader* pLoader = new TileMapLoader(this);
		if ( pLoader )
		{
			pLoader->reset(tiles,masks);
			pLoader->loadAsync();
		}
	}
	
	/*if ( !m_mapLoader.isLoading() )
	{
	m_mapLoader.reset(tiles,masks);
	m_mapLoader.loadAsync();
	}*/
}

void TileMap::refreshCellsInView()
{
	Rect rect;
	getViewRect(rect);

	m_vCellsInView.clear();
	for( int i=0;i<getTerrain()->getCellY();++i)
	{
		for ( int j=0;j<getTerrain()->getCellX();++j)
		{
			int cx = j;
			int cy = i;
			getTerrain()->cell2World(cx,cy);
			if ( rect.containsPoint(Point(cx+cellInPixelsX/2,cy+cellInPixelsY/2)) || 
				rect.containsPoint(Point(cx-cellInPixelsX/2,cy-cellInPixelsY/2)) || 
				rect.containsPoint(Point(cx-cellInPixelsX/2,cy+cellInPixelsY/2)) || 
				rect.containsPoint(Point(cx+cellInPixelsX/2,cy-cellInPixelsY/2)) )
			{
				m_vCellsInView.push_back(i*getTerrain()->getCellX()+j);
			}
		}
	}
}

void TileMap::refreshPartsInView()
{
	// 移除并释放掉视野以外的部件，并且加载新进入视野内的部件。
	Rect rect;
	getViewRect(rect);

	for ( MapPartList::iterator itr = m_vParts.begin();itr != m_vParts.end(); ++itr )
	{
		MapPartInfo* pPart = *itr;
		if ( pPart )
		{
			bool inView = rect.containsPoint(Point(pPart->info.x,pPart->info.y));
			// 之前在显示，现在已经离开视野
			//if ( pPart->obj && !inView )
			//{
			//	pPart->obj->LeaveMap();
			//	pPart->obj = NULL;
			//}

			// 之前未显示，现在出现在视野内
			if ( !pPart->obj && inView )
			{
				MapEffect* pEffect = MapEffect::createWithDataID(pPart->info.dataid);
				if ( pEffect )
				{
					pEffect->setScale(10.0f/7.0f);
					pEffect->getEffect()->setPosition(Point(0,pPart->info.h));
					pEffect->getEffect()->setName(pPart->info.name);
					pEffect->EnterMap(this,Point(pPart->info.x,pPart->info.y));
					pPart->obj = pEffect;
				}
			}
		}
	}
}

void TileMap::clearMask()
{
	for ( size_t i = 0;i<m_vMasks.size();++i )
	{
		MapMaskInfo* pMask = m_vMasks[i];
		if( pMask->obj )
		{
			pMask->obj->LeaveMap();
			pMask->obj = NULL;
		}
		
		if( pMask->mask_relation )
		{
			delete[] pMask->mask_relation;
			pMask->mask_relation = NULL;
		}
		CC_SAFE_DELETE(pMask);
	}
	m_vMasks.clear();
}

bool TileMap::isMaskInRect(const Rect& rect,const map_mask* mask)
{
	return (rect.containsPoint(Point(mask->x,mask->y)) || 
			rect.containsPoint(Point(mask->x+mask->w,mask->y)) || 
			rect.containsPoint(Point(mask->x+mask->w,mask->y+mask->h)) || 
			rect.containsPoint(Point(mask->x,mask->y+mask->h)) );
}

MapMaskInfo* TileMap::getMask(int tag)
{
	if ( tag >= 0 && tag < (int)m_vMasks.size() )
	{
		return m_vMasks[tag];
	}
	return NULL;
}

void TileMap::getMasksInRect(const Rect& rect,vector<MapMaskInfo*>& masks)
{
	masks.clear();
	for ( size_t i = 0;i<m_vMasks.size();++i )
	{
		if ( isMaskInRect(rect,m_vMasks[i]->mask))
		{
			masks.push_back(m_vMasks[i]);
		}
	}
}

void TileMap::getMasksInView(vector<MapMaskInfo*>& masks)
{
	Rect rect;
	getViewRect(rect);
	getMasksInRect(rect,masks);
}

void TileMap::getMasksNoneInRect(const Rect& rect,vector<MapMaskInfo*>& masks)
{
	for ( size_t i = 0;i<m_vMasks.size();++i )
	{
		MapMaskInfo* pMask = m_vMasks[i];
		bool inView = isMaskInRect(rect,pMask->mask);
		// 之前在显示，现在已经离开视野
		if ( pMask->flag == TileFlagShowing && !inView )
		{
			//if ( pMask->spr )
			//{
			//	pMask->spr->removeFromParent();
			//	pMask->spr = NULL;
			//}
			//if(pMask->mask->mask_data)
			//{
			//	CC_SAFE_DELETE_ARRAY(pMask->mask->mask_data);
			//	pMask->mask->mask_data = NULL;
			//}
			//pMask->flag = TileFlagNone;
		}

		// 之前未显示，现在出现在视野内
		if ( pMask->flag == TileFlagNone && inView )
		{
			masks.push_back(pMask);
		}
	}
}

void TileMap::getMasksNoneInView(vector<MapMaskInfo*>& masks)
{
	Rect rect;
	getViewRect(rect);
	getMasksNoneInRect(rect,masks);
}

bool TileMap::isTileInRect(const Rect& rect,const TileInfo* tile)
{
	int x,y;
	getTileMgrNear()->index2Tile(tile->tag,x,y);
	return (rect.containsPoint(Point(x,y)) || 
		rect.containsPoint(Point(x+tileInPixelsX,y)) || 
		rect.containsPoint(Point(x+tileInPixelsX,y+tileInPixelsY)) || 
		rect.containsPoint(Point(x,y+tileInPixelsY)) );
}

void TileMap::getTilesInRect(const Rect& rect,vector<TileInfo*>& tiles)
{
	for ( int i = 0;i<getTileMgrNear()->getTileY(); ++i )
	{
		for ( int j = 0;j<getTileMgrNear()->getTileX();++j )
		{
			TileInfo* pTile = getTileMgrNear()->getTile(j,i);
			if ( rect.containsPoint(Point(j,i)) )
			{
				tiles.push_back(pTile);
			}
		}
	}
}

void TileMap::getTilesInView(vector<TileInfo*>& tiles)
{
	Rect rect;
	getViewRect(rect);

	int tileInViewX = (int)rect.origin.x;
	int tileInViewY = (int)rect.origin.y;
	int tileInViewW = (int)rect.size.width/tileInPixelsX;
	int tileInViewH = (int)rect.size.height/tileInPixelsY;

	getTileMgrNear()->world2Tile(tileInViewX,tileInViewY);

	//tileInViewX -= 1;
	tileInViewY -= tileInViewH;

	rect = Rect(tileInViewX,tileInViewY,tileInViewW,tileInViewH);

	getTilesInRect(rect,tiles);
}

void TileMap::getTilesNoneInRect(const Rect& rect,vector<TileInfo*>& tiles)
{
	for ( int i = 0;i<getTileMgrNear()->getTileY(); ++i )
	{
		for ( int j = 0;j<getTileMgrNear()->getTileX();++j )
		{
			int tx = j;
			int ty = i;
			TileInfo* pTile = getTileMgrNear()->getTile(tx,ty);
			bool inView = rect.containsPoint(Point(tx,ty));
			// 之前在显示，现在已经离开视野
			if ( pTile->flag == TileFlagShowing && !inView )
			{
				if ( pTile->spr )
				{
					pTile->spr->removeFromParent();
					pTile->spr = NULL;
				}

				pTile->flag = TileFlagNone;
			}

			// 之前未显示，现在出现在视野内
			if ( pTile->flag == TileFlagNone && inView )
			{
				tiles.push_back(pTile);
			}
		}
	}
}

void TileMap::getTilesNoneInView(vector<TileInfo*>& tiles)
{
	Rect rect;
	getViewRect(rect);

	int tileInViewX = (int)rect.origin.x;
	int tileInViewY = (int)rect.origin.y;
	int tileInViewW = (int)rect.size.width/tileInPixelsX;
	int tileInViewH = (int)rect.size.height/tileInPixelsY;

	getTileMgrNear()->world2Tile(tileInViewX,tileInViewY);

	//tileInViewX -= 1;
	tileInViewY -= tileInViewH;

	rect = Rect(tileInViewX,tileInViewY,tileInViewW,tileInViewH);

	getTilesNoneInRect(rect,tiles);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void TileMap::draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{	
#ifdef _GameEditor
	Layer::draw(renderer,transform,transformUpdated);

	static CustomCommand _customCommand;
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(TileMap::onDraw, this, renderer,transform, transformUpdated);
	renderer->addCommand(&_customCommand);
#endif
}

void TileMap::onDraw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);

	if ( m_bRegionGrid )
	{
		drawNpcRegions(renderer,transform,transformUpdated);
		drawMonsterRegions(renderer,transform,transformUpdated);
		drawDoorRegions(renderer,transform,transformUpdated);
		drawRegions(renderer,transform,transformUpdated);
		drawSelectedRegions(renderer,transform,transformUpdated);
	}

	//drawPartRect(renderer,transform,transformUpdated);

	if ( m_bTileGrid )
	{
		drawTileGrid(renderer,transform,transformUpdated);
	}

	if ( m_bCellGrid )
	{
		drawCellGrid(renderer,transform,transformUpdated);
		drawCellMask(renderer,transform,transformUpdated);
	}

	drawPartRect(renderer,transform,transformUpdated);

	//end draw
	kmGLPopMatrix();
}

void TileMap::drawTileGrid(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	DrawPrimitives::setDrawColor4B(166, 166, 166, 255);
	glLineWidth (3.0);

	for ( int i = 0;i<=getTileMgrNear()->getTileX();++i )
	{
		DrawPrimitives::drawLine(Point(i*tileInPixelsX,0),Point(i*tileInPixelsX,getTileMgrNear()->getTileY()*tileInPixelsY));
	}

	for ( int j = 0;j<=getTileMgrNear()->getTileY();++j )
	{
		DrawPrimitives::drawLine(Point(0,j*tileInPixelsY),Point(getTileMgrNear()->getTileX()*tileInPixelsX,j*tileInPixelsY));
	}

	CHECK_GL_ERROR_DEBUG();
}

void TileMap::drawCellMask(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	vector<int> stopCells;
	vector<int> coverCells;
	vector<int> waterCells;
	int cx,cy;

	for( size_t i=0;i<m_vCellsInView.size();++i )
	{
		Cell* pCell = getTerrain()->getCell(m_vCellsInView[i]);
		if ( !pCell )
		{
			continue;
		}
		if ( pCell->isMark(cellMaskStop) )
		{
			stopCells.push_back(m_vCellsInView[i]);
		}
		if ( pCell->isMark(cellMaskCover) )
		{
			coverCells.push_back(m_vCellsInView[i]);
		}
		if ( pCell->isMark(cellMaskWater) )
		{
			waterCells.push_back(m_vCellsInView[i]);
		}
	}

	// 画阻挡标识
	DrawPrimitives::setDrawColor4B(255, 0, 0, 255);
	glLineWidth (2.0);
	for ( size_t i = 0; i<stopCells.size(); ++i )
	{
		getTerrain()->index2Cell(stopCells[i],cx,cy);
		getTerrain()->cell2World(cx,cy);
		DrawPrimitives::drawLine(Point(cx,cy + cellInPixelsY/2),Point(cx,cy - cellInPixelsY/2));
		DrawPrimitives::drawLine(Point(cx - cellInPixelsX/2,cy),Point(cx + cellInPixelsX/2,cy));
	}

	// 画遮挡标识
	DrawPrimitives::setDrawColor4B(0, 0, 255, 255);
	glLineWidth (2.0);
	for ( size_t i = 0; i<coverCells.size(); ++i )
	{
		getTerrain()->index2Cell(coverCells[i],cx,cy);
		getTerrain()->cell2World(cx,cy);
		DrawPrimitives::drawLine(Point(cx,cy + cellInPixelsY/2),Point(cx,cy - cellInPixelsY/2));
		DrawPrimitives::drawLine(Point(cx - cellInPixelsX/2,cy),Point(cx + cellInPixelsX/2,cy));
	}

	// 画水标识
	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	glLineWidth (2.0);
	for ( size_t i = 0; i<waterCells.size(); ++i )
	{
		getTerrain()->index2Cell(waterCells[i],cx,cy);
		getTerrain()->cell2World(cx,cy);
		DrawPrimitives::drawLine(Point(cx,cy + cellInPixelsY/2),Point(cx,cy - cellInPixelsY/2));
		DrawPrimitives::drawLine(Point(cx - cellInPixelsX/2,cy),Point(cx + cellInPixelsX/2,cy));
	}

	CHECK_GL_ERROR_DEBUG();
}

void TileMap::drawCellGrid(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	glLineWidth (1.0);

	for ( int i = 0;i<=getTerrain()->getCellX();++i )
	{
		DrawPrimitives::drawLine(Point(getTerrain()->getOriginX()+i*cellInPixelsX/2,getTerrain()->getOriginY()-i*cellInPixelsY/2),
			Point(getTerrain()->getOriginX()-getTerrain()->getCellY()*cellInPixelsX/2+i*cellInPixelsX/2,getTerrain()->getOriginY()-getTerrain()->getCellY()*cellInPixelsY/2-i*cellInPixelsY/2));
	}

	for ( int j=0;j<=getTerrain()->getCellY();++j )
	{
		DrawPrimitives::drawLine(Point(getTerrain()->getOriginX()-j*cellInPixelsX/2,getTerrain()->getOriginY()-j*cellInPixelsY/2),
			Point(getTerrain()->getOriginX()+getTerrain()->getCellX()*cellInPixelsX/2-j*cellInPixelsX/2,getTerrain()->getOriginY()-getTerrain()->getCellX()*cellInPixelsY/2-j*cellInPixelsY/2));
	}

	CHECK_GL_ERROR_DEBUG();
}

void TileMap::drawNpcRegions(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	glLineWidth (1.0);

	int x0,y0,x1,y1,x2,y2,x3,y3;
	for ( size_t i = 0;i<getRegionManager()->getNpcList()->size();++i )
	{
		CRegion* pRegion = getRegionManager()->getNpcList()->at(i);
		if ( pRegion )
		{
			x0 = pRegion->getOriginX();
			y0 = pRegion->getOriginY();
			x1 = pRegion->getEndX();
			y1 = pRegion->getEndY();

			getTerrain()->cell2World(x0,y0);
			getTerrain()->cell2World(x1,y1);

			y0 += cellInPixelsY/2;
			y1 -= cellInPixelsY/2;
			x2 = x0 - pRegion->getSizeY()*cellInPixelsX/2-cellInPixelsX/2;
			y2 = y0 - pRegion->getSizeY()*cellInPixelsY/2-cellInPixelsY/2;
			x3 = x0 + pRegion->getSizeX()*cellInPixelsX/2+cellInPixelsX/2;
			y3 = y0 - pRegion->getSizeX()*cellInPixelsY/2-cellInPixelsY/2;

			Point glVertices[] = {Point(x0,y0),Point(x2,y2),Point(x1,y1),Point(x3,y3)};

			DrawPrimitives::drawSolidPoly(glVertices,4,Color4F(255,255,255,255));
		}
	}

	CHECK_GL_ERROR_DEBUG();
}

void TileMap::drawMonsterRegions(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	glLineWidth (1.0);

	int x0,y0,x1,y1,x2,y2,x3,y3;
	for ( size_t i = 0;i<getRegionManager()->getMonsterList()->size();++i )
	{
		CRegion* pRegion = getRegionManager()->getMonsterList()->at(i);
		if ( pRegion )
		{
			x0 = pRegion->getOriginX();
			y0 = pRegion->getOriginY();
			x1 = pRegion->getEndX();
			y1 = pRegion->getEndY();

			getTerrain()->cell2World(x0,y0);
			getTerrain()->cell2World(x1,y1);

			y0 += cellInPixelsY/2;
			y1 -= cellInPixelsY/2;
			x2 = x0 - pRegion->getSizeY()*cellInPixelsX/2-cellInPixelsX/2;
			y2 = y0 - pRegion->getSizeY()*cellInPixelsY/2-cellInPixelsY/2;
			x3 = x0 + pRegion->getSizeX()*cellInPixelsX/2+cellInPixelsX/2;
			y3 = y0 - pRegion->getSizeX()*cellInPixelsY/2-cellInPixelsY/2;

			Point glVertices[] = {Point(x0,y0),Point(x2,y2),Point(x1,y1),Point(x3,y3)};

			DrawPrimitives::drawSolidPoly(glVertices,4,Color4F(255,0,0,255));
		}
	}

	CHECK_GL_ERROR_DEBUG();
}

void TileMap::drawDoorRegions(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	glLineWidth (1.0);

	int x0,y0,x1,y1,x2,y2,x3,y3;
	for ( size_t i = 0;i<getRegionManager()->getDoorList()->size();++i )
	{
		CRegion* pRegion = getRegionManager()->getDoorList()->at(i);
		if ( pRegion )
		{
			x0 = pRegion->getOriginX();
			y0 = pRegion->getOriginY();
			x1 = pRegion->getEndX();
			y1 = pRegion->getEndY();

			getTerrain()->cell2World(x0,y0);
			getTerrain()->cell2World(x1,y1);

			y0 += cellInPixelsY/2;
			y1 -= cellInPixelsY/2;
			x2 = x0 - pRegion->getSizeY()*cellInPixelsX/2-cellInPixelsX/2;
			y2 = y0 - pRegion->getSizeY()*cellInPixelsY/2-cellInPixelsY/2;
			x3 = x0 + pRegion->getSizeX()*cellInPixelsX/2+cellInPixelsX/2;
			y3 = y0 - pRegion->getSizeX()*cellInPixelsY/2-cellInPixelsY/2;

			Point glVertices[] = {Point(x0,y0),Point(x2,y2),Point(x1,y1),Point(x3,y3)};

			DrawPrimitives::drawSolidPoly(glVertices,4,Color4F(0,255,0,255));
		}
	}

	CHECK_GL_ERROR_DEBUG();
}

void TileMap::drawRegions(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	glLineWidth (1.0);

	int x0,y0,x1,y1,x2,y2,x3,y3;
	for ( size_t i = 0;i<getRegionManager()->getRegionList()->size();++i )
	{
		CRegion* pRegion = getRegionManager()->getRegionList()->at(i);
		if ( pRegion )
		{
			x0 = pRegion->getOriginX();
			y0 = pRegion->getOriginY();
			x1 = pRegion->getEndX();
			y1 = pRegion->getEndY();

			getTerrain()->cell2World(x0,y0);
			getTerrain()->cell2World(x1,y1);

			y0 += cellInPixelsY/2;
			y1 -= cellInPixelsY/2;
			x2 = x0 - pRegion->getSizeY()*cellInPixelsX/2-cellInPixelsX/2;
			y2 = y0 - pRegion->getSizeY()*cellInPixelsY/2-cellInPixelsY/2;
			x3 = x0 + pRegion->getSizeX()*cellInPixelsX/2+cellInPixelsX/2;
			y3 = y0 - pRegion->getSizeX()*cellInPixelsY/2-cellInPixelsY/2;

			Point glVertices[] = {Point(x0,y0),Point(x2,y2),Point(x1,y1),Point(x3,y3)};

			DrawPrimitives::drawSolidPoly(glVertices,4,Color4F(255,255,0,255));
		}
	}

	CHECK_GL_ERROR_DEBUG();
}

void TileMap::drawSelectedRegions(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	glLineWidth (5.0);
	int x0,y0,x1,y1,x2,y2,x3,y3;
	for ( size_t i = 0;i<getRegionManager()->getNpcList()->size();++i )
	{
		CRegion* pRegion = getRegionManager()->getNpcList()->at(i);
		if ( pRegion && pRegion->getSelected() )
		{
			x0 = pRegion->getOriginX();
			y0 = pRegion->getOriginY();
			x1 = pRegion->getEndX();
			y1 = pRegion->getEndY();

			getTerrain()->cell2World(x0,y0);
			getTerrain()->cell2World(x1,y1);

			y0 += cellInPixelsY/2;
			y1 -= cellInPixelsY/2;
			x2 = x0 - pRegion->getSizeY()*cellInPixelsX/2-cellInPixelsX/2;
			y2 = y0 - pRegion->getSizeY()*cellInPixelsY/2-cellInPixelsY/2;
			x3 = x0 + pRegion->getSizeX()*cellInPixelsX/2+cellInPixelsX/2;
			y3 = y0 - pRegion->getSizeX()*cellInPixelsY/2-cellInPixelsY/2;

			DrawPrimitives::drawLine(Point(x0,y0),Point(x2,y2));
			DrawPrimitives::drawLine(Point(x0,y0),Point(x3,y3));
			DrawPrimitives::drawLine(Point(x1,y1),Point(x2,y2));
			DrawPrimitives::drawLine(Point(x1,y1),Point(x3,y3));

		}
	}

	for ( size_t i = 0;i<getRegionManager()->getMonsterList()->size();++i )
	{
		CRegion* pRegion = getRegionManager()->getMonsterList()->at(i);
		if ( pRegion && pRegion->getSelected() )
		{
			x0 = pRegion->getOriginX();
			y0 = pRegion->getOriginY();
			x1 = pRegion->getEndX();
			y1 = pRegion->getEndY();

			getTerrain()->cell2World(x0,y0);
			getTerrain()->cell2World(x1,y1);

			y0 += cellInPixelsY/2;
			y1 -= cellInPixelsY/2;
			x2 = x0 - pRegion->getSizeY()*cellInPixelsX/2-cellInPixelsX/2;
			y2 = y0 - pRegion->getSizeY()*cellInPixelsY/2-cellInPixelsY/2;
			x3 = x0 + pRegion->getSizeX()*cellInPixelsX/2+cellInPixelsX/2;
			y3 = y0 - pRegion->getSizeX()*cellInPixelsY/2-cellInPixelsY/2;

			DrawPrimitives::drawLine(Point(x0,y0),Point(x2,y2));
			DrawPrimitives::drawLine(Point(x0,y0),Point(x3,y3));
			DrawPrimitives::drawLine(Point(x1,y1),Point(x2,y2));
			DrawPrimitives::drawLine(Point(x1,y1),Point(x3,y3));
		}
	}

	for ( size_t i = 0;i<getRegionManager()->getDoorList()->size();++i )
	{
		CRegion* pRegion = getRegionManager()->getDoorList()->at(i);
		if ( pRegion && pRegion->getSelected() )
		{
			x0 = pRegion->getOriginX();
			y0 = pRegion->getOriginY();
			x1 = pRegion->getEndX();
			y1 = pRegion->getEndY();

			getTerrain()->cell2World(x0,y0);
			getTerrain()->cell2World(x1,y1);

			y0 += cellInPixelsY/2;
			y1 -= cellInPixelsY/2;
			x2 = x0 - pRegion->getSizeY()*cellInPixelsX/2-cellInPixelsX/2;
			y2 = y0 - pRegion->getSizeY()*cellInPixelsY/2-cellInPixelsY/2;
			x3 = x0 + pRegion->getSizeX()*cellInPixelsX/2+cellInPixelsX/2;
			y3 = y0 - pRegion->getSizeX()*cellInPixelsY/2-cellInPixelsY/2;

			DrawPrimitives::drawLine(Point(x0,y0),Point(x2,y2));
			DrawPrimitives::drawLine(Point(x0,y0),Point(x3,y3));
			DrawPrimitives::drawLine(Point(x1,y1),Point(x2,y2));
			DrawPrimitives::drawLine(Point(x1,y1),Point(x3,y3));
		}
	}

	for ( size_t i = 0;i<getRegionManager()->getRegionList()->size();++i )
	{
		CRegion* pRegion = getRegionManager()->getRegionList()->at(i);
		if ( pRegion && pRegion->getSelected() )
		{
			x0 = pRegion->getOriginX();
			y0 = pRegion->getOriginY();
			x1 = pRegion->getEndX();
			y1 = pRegion->getEndY();

			getTerrain()->cell2World(x0,y0);
			getTerrain()->cell2World(x1,y1);

			y0 += cellInPixelsY/2;
			y1 -= cellInPixelsY/2;
			x2 = x0 - pRegion->getSizeY()*cellInPixelsX/2-cellInPixelsX/2;
			y2 = y0 - pRegion->getSizeY()*cellInPixelsY/2-cellInPixelsY/2;
			x3 = x0 + pRegion->getSizeX()*cellInPixelsX/2+cellInPixelsX/2;
			y3 = y0 - pRegion->getSizeX()*cellInPixelsY/2-cellInPixelsY/2;

			DrawPrimitives::drawLine(Point(x0,y0),Point(x2,y2));
			DrawPrimitives::drawLine(Point(x0,y0),Point(x3,y3));
			DrawPrimitives::drawLine(Point(x1,y1),Point(x2,y2));
			DrawPrimitives::drawLine(Point(x1,y1),Point(x3,y3));
		}
	}

	CHECK_GL_ERROR_DEBUG();
}

void TileMap::drawPartRect(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	DrawPrimitives::setDrawColor4B(0, 0, 225, 255);
	glLineWidth (2.0);

	int x0,y0,x1,y1,x2,y2,x3,y3;
	for ( size_t i=0;i<m_vParts.size();++i )
	{
		MapPartInfo* pPart = m_vParts[i];
		if ( pPart )
		{
			x0 = pPart->info.x;
			y0 = pPart->info.y;

			getTerrain()->world2Cell(x0,y0);

			x1 = x0;
			y1 = y0;

			getTerrain()->cell2World(x0,y0);
			getTerrain()->cell2World(x1,y1);

			y0 += cellInPixelsY/2;
			y1 -= cellInPixelsY/2;
			x2 = x0 -cellInPixelsX/2;
			y2 = y0 -cellInPixelsY/2;
			x3 = x0 +cellInPixelsX/2;
			y3 = y0 -cellInPixelsY/2;

			DrawPrimitives::drawLine(Point(x0,y0),Point(x2,y2));
			DrawPrimitives::drawLine(Point(x0,y0),Point(x3,y3));
			DrawPrimitives::drawLine(Point(x1,y1),Point(x2,y2));
			DrawPrimitives::drawLine(Point(x1,y1),Point(x3,y3));


			//Point glVertices[] = {Point(x0,y0),Point(x2,y2),Point(x1,y1),Point(x3,y3)};

			//DrawPrimitives::drawSolidPoly(glVertices,4,Color4F(33, 33, 33, 33));
		}
	}

	CHECK_GL_ERROR_DEBUG();
}

void TileMap::setGrey(bool grey /* = true */)
{
	if ( m_bGrey == grey )
	{
		return ;
	}

	m_bGrey = grey;

	vector<TileInfo*> tiles;
	getTilesInView(tiles);

	vector<MapMaskInfo*> masks;
	getMasksInView(masks);

	if ( m_bGrey )
	{
		// 地图背景
		for (size_t i = 0; i < tiles.size(); i++)
		{
			TileInfo* pInfo = tiles[i];
			if ( pInfo && pInfo->spr )
			{
				pInfo->spr->setGrayRate(-1.f);
			}
		}

		// 地图遮挡物件
		for (size_t i = 0; i < masks.size(); i++)
		{
			MapMaskInfo* pMask = masks[i];
			if ( pMask && pMask->obj )
			{
				pMask->obj->getShaderSprite()->setGrayRate(-1.f);
			}
		}

		// 地图元素
		MapObjectList objects = getObjectManager()->GetObjectList();
		for (MapObjectList::iterator iter = objects.begin();iter != objects.end();++iter )
		{
			MapObject* pObj = *iter;
			if ( pObj )
			{
				pObj->SetSkinEffect(SkinEffect_Grey);
			}
		}

	}
	else
	{
		for (size_t i = 0; i < tiles.size(); i++)
		{
			TileInfo* pInfo = tiles[i];
			if ( pInfo && pInfo->spr )
			{
				pInfo->spr->setGrayRate(1.f);
			}
		}

		for (size_t i = 0; i < masks.size(); i++)
		{
			MapMaskInfo* pMask = masks[i];
			if ( pMask && pMask->obj )
			{
				pMask->obj->getShaderSprite()->setGrayRate(1.f);
			}
		}

		// 地图元素
		MapObjectList objects = getObjectManager()->GetObjectList();
		for (MapObjectList::iterator iter = objects.begin();iter != objects.end();++iter )
		{
			MapObject* pObj = *iter;
			if ( pObj )
			{
				pObj->SetSkinEffect(SkinEffect_None);
			}
		}
	}
}
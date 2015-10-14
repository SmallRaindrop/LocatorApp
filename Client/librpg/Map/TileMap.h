/***
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：地图类
 * 地图的加载：通过psd加载，psd-->map_context-->TileMap;适用于编辑器。通过map加载，map-->map_context-->TileMap适用客户端
 * 地图分层架构：
 * 1. 远景层，位于地图最底层
 * 2. 地表层，仅次于地图的远景层，主要是地图背景表现
 * 3. 交互对象层，位于地图的中间层，包括（遮挡物件，地图特效及动画，地图中的物品，地图中的角色（角色，怪物，NPC）他们之间有相互遮挡关系
 * 4. 天气效果层，位于地图最上层

 * 交互对象层相互遮挡关系说明：
 * 遮挡物件随地图导入的时候产生，导入顺序作为zorder，地图特效及动画，物品和角色之间用世界坐标系位置Y坐标来判断，Y值越大zorder越大。遮挡物件和他们之间有色块逻辑判断zorder。
 * 
 */

#ifndef __TileMap_h_
#define __TileMap_h_

#include "Terrain.h"
#include "RegionManager.h"
#include "MapObject.h"
#include "MapObjectManager.h"
#include "Camera.h"
#include "TileMapLoader.h"
#include "MapEffect.h"
#include "AStar.h"

// 地图层级描述
enum zOrderTileMap{
	zOrderBottom,		// 地图最低层
	zOrderFar,			// 远景层
	zOrderTerrain,		// 地表层
	zOrderObject,		// 交互对象层
	zOrderMask,			// 遮挡层
	zOrderSky,			// 天气效果层 预留
	zOrderTop,			// 地图最高层
};

// 地图物件信息结构
struct MapPartInfo
{
	MapPartInfo() : obj(NULL)
	{
		info.x = 0;
		info.y = 0;
		info.h = 0;
		info.dataid = 0;
	}

	map_part info;	// 遮挡物件基本信息
	MapEffect* obj;	// 物件对象指针
};

typedef vector<MapPartInfo*> MapPartList;


enum __maskRelation{
	MASK_RELATION_N=0,    //role不在mask section里面
	MASK_RELATION_FRONT,  //role在遮挡物的前面
	MASK_RELATION_BEHIND  //role在遮挡物的后面
};


class TileMap : public Layer
{
public:
	TileMap();
	virtual ~TileMap();
	
	CREATE_FUNC(TileMap);

	/* Name		：createWithMapContext
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过地图上下文创建地图
	 * Param	: context 地图上下文
	 * Return	: 成功返回地图指针，失败NULL
	 */
	static TileMap* createWithMapContext(map_context* context);

	/* Name		：init
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 地图初始化
	 * Param	: none
	 * Return	: 成功返回true，失败false
	 */
	virtual bool init();

	/* Name		：initWithPSD
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过PSD文件初始化地图对象，map_context中会加载完整数据
	 * Param	: psd 指定.psd格式文件名
	 * Return	: 成功返回true，失败false
	 */
	//virtual bool initWithPSD(const char* psd);

	/* Name		：initWithMAP
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过MAP文件初始化地图对象，map_context中不加载完整数据
	 * Param	: map 指定.map格式文件名
	 * Return	: 成功返回true，失败false
	 */
	//virtual bool initWithMAP(const char* map);

	/* Name		：initWithMapContext
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过map_context初始化地图对象
	 * Param	: map_context指针
	 * Return	: 成功返回true，失败false
	 */
	virtual bool initWithMapContext(map_context* context);

	/* Name		：updateMapContext
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新地图context，地图上下文信息。编辑器修改地图属性后需要修改地图上下文才能保存到文件里面。
	 * Param	: none
	 * Return	: void
	 */
	virtual void updateMapContext();

	// 寻路相关
	/* Name		：initAStar
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: A*寻路算法预处理。
	 * Param	: none
	 * Return	: true 成功，失败 false
	 */
	bool initAStar();

	/* Name		：searchForPath
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 寻找两点间可达路劲。
	 * Param	: none
	 * Return	: void
	 */
	void searchForPath(int cx0,int cy0,int cx1,int cy1,APath& path);

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///////////////////////////地表相关///////////////////////////////////////
public:
	/* Name		：getViewRect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取屏幕视野范围，世界坐标系为单位
	 * Param	: out rect 视野区域
	 * Return	: void
	 */
	virtual void getViewRect(Rect& rect);

	/* Name		：refreshCellsInView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 刷新在视野范围内的逻辑坐标点，地图编辑器内查看逻辑坐标属性使用
	 * Param	: none
	 * Return	: void
	 */
	virtual void refreshCellsInView();

	/* Name		：refreshTilesInView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 刷新在视野范围内的地图tile
	 * Param	: none
	 * Return	: void
	 */
	virtual void refreshTilesInView();

	/* Name		：refreshPartsInView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 刷新在视野范围内的部件
	 * Param	: none
	 * Return	: void
	 */
	virtual void refreshPartsInView();

	/* Name		：draw
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 画编辑器内需要查看的各种格子线
	 * Param	: none
	 * Return	: void
	 */
	void draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated);

	/* Name		：onDraw
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 用这种方式才能够使画的线条不被地图遮挡
	 * Param	: none
	 * Return	: void
	 */
	void onDraw(Renderer *renderer, const kmMat4& transform, bool transformUpdated);

	/* Name		：draw
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 画编辑器内需要查看的各种格子线
	 * Param	: none
	 * Return	: void
	 */
	void drawCellMask(Renderer *renderer, const kmMat4& transform, bool transformUpdated);
	void drawCellGrid(Renderer *renderer, const kmMat4& transform, bool transformUpdated);
	void drawTileGrid(Renderer *renderer, const kmMat4& transform, bool transformUpdated);
	void drawNpcRegions(Renderer *renderer, const kmMat4& transform, bool transformUpdated);
	void drawMonsterRegions(Renderer *renderer, const kmMat4& transform, bool transformUpdated);
	void drawDoorRegions(Renderer *renderer, const kmMat4& transform, bool transformUpdated);
	void drawRegions(Renderer *renderer, const kmMat4& transform, bool transformUpdated);
	void drawSelectedRegions(Renderer *renderer, const kmMat4& transform, bool transformUpdated);
	void drawPartRect(Renderer *renderer, const kmMat4& transform, bool transformUpdated);

	/* Name		：setGrey
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 将地图去色
	 * Param	: grey true 去色，false还原
	 * Return	: void
	 */
	virtual void setGrey(bool grey = true);

protected:
	vector<int>				m_vCellsInView;			// 视野范围内的逻辑坐标点
	CC_SYNTHESIZE(bool,m_bTileGrid,TileGrid);		// 是否画tile格子线
	CC_SYNTHESIZE(bool,m_bCellGrid,CellGrid);		// 是否画逻辑坐标格子
	CC_SYNTHESIZE(bool,m_bRegionGrid,RegionGrid);	// 是否画区域格子
	CC_SYNTHESIZE_READONLY(bool,m_bGrey,Grey);		// 是否去色

public:
///////////////////////////坐标转换///////////////////////////////////////
	/* Name		：touchToNode
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 屏幕坐标到世界坐标的转换
	 * Param	: pt 传入的屏幕坐标，输出为世界坐标
	 * Return	: void
	 */
	void touchToNode(Point& pt);

	/* Name		：nodeToView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 世界坐标到视口坐标的转换
	 * Param	: pt 传入的世界坐标，输出为视口坐标
	 * Return	: void
	 */
	void nodeToView(Point& pt);

	/* Name		：nodeToView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 视口坐标到世界坐标的转换
	 * Param	: pt 传入的视口坐标，输出为世界坐标
	 * Return	: void
	 */
	void viewToNode(Point& pt);
///////////////////////////坐标转换 end///////////////////////////////////////

	/* Name		：update
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 每帧更新地图
	 * Param	: dt 与上一帧的时间差
	 * Return	: void
	 */
	virtual void update(float dt);

	/* Name		：updateTerLayer
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新地表层
	 * Param	: none
	 * Return	: void
	 */
	virtual void updateTerLayer();

	/* Name		：updateFarLayer
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新远景层
	 * Param	: none
	 * Return	: void
	 */
	virtual void updateFarLayer();

	/* Name		：onTouchBegan
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 鼠标事件响应
	 * Param	: none
	 * Return	: void
	 */
	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
	virtual void onTouchMoved(Touch *touch, Event *unused_event); 
	virtual void onTouchEnded(Touch *touch, Event *unused_event); 
	virtual void onTouchCancelled(Touch *touch, Event *unused_event);

	//virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	//virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	//virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
	//virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);

public:
	/* Name		：centerMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 将视点设置为地图的中心
	 * Param	: none
	 * Return	: void
	 */
	void centerMap();

	/* Name		：moveMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移动地图视点
	 * Param	: x,y移动偏移量
	 * Return	: void
	 */
	void moveMap(int x,int y);

	/* Name		：SetView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 用逻辑坐标设置视点
	 * Param	: cx,cy视点逻辑坐标
	 * Return	: void
	 */
	void SetView(int cx,int cy);

	/* Name		：SetView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 用世界坐标设置视点
	 * Param	: Point pt视点世界坐标
	 * Return	: void
	 */
	void SetView(Point pt);

	/* Name		：GetMaxViewX
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 地图X边界，视点不能超过他
	 * Param	: none
	 * Return	: 地图X边界
	 */
	float GetMaxViewX();

	/* Name		：GetMaxViewY
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 地图Y边界，视点不能超过他
	 * Param	: none
	 * Return	: 地图Y边界
	 */
	float GetMaxViewY();

	/* Name		：isCellInView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断指定逻辑坐标是否在视野内
	 * Param	: cx,cy指定逻辑坐标点
	 * Return	: 视野内返回true，视野外返回false
	 */
	bool isCellInView(int cx,int cy);

	/* Name		：AddMapObject
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 将地图元素加入地图的指定逻辑坐标点
	 * Param	: pObject指定地图元素，cx,cy指定逻辑坐标点
	 * Return	: void
	 */
	void objectEnterMap(MapObject* pObject,int cx,int cy);

	/* Name		：AddMapObject
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 将地图元素加入地图的指定逻辑坐标点
	 * Param	: pObject指定地图元素，Point pos指定世界坐标点，转换成逻辑坐标点
	 * Return	: void
	 */
	void objectEnterMap(MapObject* pObject,Point pos);

	/* Name		：RemoveMapObject
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 将地图元素移除地图
	 * Param	: pObject指定地图元素
	 * Return	: void
	 */
	void objectLeaveMap(MapObject* pObject);

	/* Name		：RemoveMapObject
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 将地图元素素移除地图
	 * Param	: id指定地图元素ID
	 * Return	: void
	 */
	void objectLeaveMap(MapObjectID id);

	/* Name		：allObjectLeaveMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 将所有地图元素移除地图，切换地图的时候需要用到
	 * Param	: none
	 * Return	: void
	 */
	void allObjectLeaveMap();

	/* Name		：objectEnterSight
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 指定地图元素进入视野,这个里面要处理遮挡关系
	 * Param	: pObject指定地图元素
	 * Return	: void
	 */
	virtual void objectEnterSight(MapObject* pObject);

	/* Name		：objectLeaveSight
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 将指定地图元素移除视野
	 * Param	: pObject指定地图元素
	 * Return	: void
	 */
	virtual void objectLeaveSight(MapObject* pObject);

	/* Name		：allObjectLeaveSight
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 将所有地图元素移除视野，切换地图的时候需要用到
	 * Param	: none
	 * Return	: void
	 */
	virtual void allObjectLeaveSight();

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///////////////////////////部件相关////////////////////////////////////
public:
	/* Name		：getMapPartInfo
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取位于指定逻辑坐标点的部件信息，只返回找到的第一个。
	 * Param	: cx,cy逻辑坐标点
	 * Return	: 部件信息指针
	 */
	MapPartInfo* getMapPartInfo(int cx,int cy);

	/* Name		：addPart
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 添加一个部件
	 * Param	: MapPartInfo pInfo部件信息
	 * Return	: void
	 */
	void addMapPartInfo(MapPartInfo* pInfo);

	/* Name		：removePart
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移除部件
	 * Param	: MapPartInfo pInfo部件信息
	 * Return	: void
	 */
	void removeMapPartInfo(MapPartInfo* pInfo);

	/* Name		：clearMapPartInfo
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移除所有部件
	 * Param	: none
	 * Return	: void
	 */
	void clearMapPartInfo();

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///////////////////////////遮挡相关////////////////////////////////////
public:
	/* Name		：clearMask
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 清除遮挡信息
	 * Param	: none
	 * Return	: void
	 */
	void clearMask();

	/* Name		：isMaskInRect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断给定的mask是否在指定区域范围内，有交集
	 * Param	: rect 指定区域范围，mask给定遮挡部件基本信息
	 * Return	: 有交集返回true，无交集返回false
	 */
	bool isMaskInRect(const Rect& rect,const map_mask* mask);

	/* Name		：getMask
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取遮挡部件
	 * Param	: tag 部件ID
	 * Return	: void
	 */
	MapMaskInfo* getMask(int tag);

	/* Name		：getMasksInRect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取给定区域范围内所有的遮挡部件
	 * Param	: rect 给定区域范围，masks out 返回的部件信息列表
	 * Return	: void
	 */
	void getMasksInRect(const Rect& rect,vector<MapMaskInfo*>& masks);

	/* Name		：getMasksInView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取所有视野范围内的遮挡部件列表
	 * Param	: masks 部件信息列表
	 * Return	: void
	 */
	void getMasksInView(vector<MapMaskInfo*>& masks);

	/* Name		：getMasksNoneInRect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取给定区域范围内的但是没有创建遮挡对象的所有遮挡部件列表（新进入区域范围的遮挡部件）
	 * Param	: rect 给定区域范围，masks out 返回的部件信息列表
	 * Return	: void
	 */
	void getMasksNoneInRect(const Rect& rect,vector<MapMaskInfo*>& masks);

	/* Name		：getMasksNoneInView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取视野范围内的但是没有创建遮挡对象的所有遮挡部件列表（新进入区域范围的遮挡部件）
	 * Param	: masks out 返回的部件信息列表
	 * Return	: void
	 */
	void getMasksNoneInView(vector<MapMaskInfo*>& masks);

	/* Name		：isTileInRect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 检查给定tile块是否在指定区域范围内
	 * Param	: rect 给定区域范围，tile tile块信息
	 * Return	: 在返回true，不再返回false
	 */
	bool isTileInRect(const Rect& rect,const TileInfo* tile);

	/* Name		：getTilesInRect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取给定区域范围内的tiles
	 * Param	: rect 给定区域范围，tiles out tile列表
	 * Return	: void
	 */
	void getTilesInRect(const Rect& rect,vector<TileInfo*>& tiles);

	/* Name		：getTilesInView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取视野范围内的tiles
	 * Param	: tiles out tile列表
	 * Return	: void
	 */
	void getTilesInView(vector<TileInfo*>& tiles);

	/* Name		：getTilesNoneInRect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取给定区域范围内的但是没有创建显示对象的tiles（新进视野的tiles）
	 * Param	: rect 给定区域范围，tiles out tile列表
	 * Return	: void
	 */
	void getTilesNoneInRect(const Rect& rect,vector<TileInfo*>& tiles);

	/* Name		：getTilesNoneInView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取视野范围内的但是没有创建显示对象的tiles（新进视野的tiles）
	 * Param	: tiles out tile列表
	 * Return	: void
	 */
	void getTilesNoneInView(vector<TileInfo*>& tiles);

	//virtual void setDataID();

	/* Name		：getMapName
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取地图名称，此名称用于索引地图文件
	 * Param	: none
	 * Return	: 地图名称
	 */
	inline string& getMapName(){ return m_pContext->name; }

	/* Name		：getMapFileName
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取地图文件
	 * Param	: none
	 * Return	: 地图名称
	 */
	inline string getMapFileName(){ return "assets/map/"+m_pContext->name+".map"; }

	/* Name		：getMapContext
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取地图上下文map_context
	 * Param	: none
	 * Return	: map_context*
	 */
	inline map_context* getMapContext(){ return m_pContext; }

protected:
	map_context*	m_pContext;	// 地图上下文
	MapPartList				m_vParts;	// 地图内部件，特效
	MapMaskList				m_vMasks;	// 地图内所有遮挡部件信息列表
	CCamera			_camera;		// 地图摄像机管理类
	Point			m_viewPoint;	// 地图视点
	MapObjectList	m_Objects;		// 在视野范围内的地图元素列表
	TileMapLoader	m_mapLoader;	// 地图资源异步加载对象
	AStar*			m_pAStar;		// A* 寻路算法对象

	CC_SYNTHESIZE_READONLY(Layer*,m_pFarLayer,FarLayer);		// 远景层 预留
	CC_SYNTHESIZE_READONLY(Layer*,m_pTerrainLayer,TerrainLayer);// 地表层
	CC_SYNTHESIZE_READONLY(Layer*,m_pObjectLayer,ObjectLayer);	// 交互对象层
	CC_SYNTHESIZE_READONLY(Layer*,m_pMaskLayer,MaskLayer);		// 遮罩层 预留
	CC_SYNTHESIZE_READONLY(Layer*,m_pSkyLayer,SkyLayer);		// 天气效果层

	CC_SYNTHESIZE_READONLY(CTileManager*,m_pTileMgrFar,TileMgrFar);		// 远景层TILE管理
	CC_SYNTHESIZE_READONLY(CTileManager*,m_pTileMgrNear,TileMgrNear);	// 近景层TILE管理
	CC_SYNTHESIZE_READONLY(CTerrain*,m_pTerrain,Terrain);				// 地表管理类
	CC_SYNTHESIZE_READONLY(CRegionManager*,m_pRegionManager,RegionManager);	// 区域管理类
	CC_SYNTHESIZE_READONLY(CMapObjectManager*,m_pObjectManager,ObjectManager);	// 地图元素管理类

	CC_SYNTHESIZE_READONLY(int,m_nWidth,MapWidth);				// 地图大小
	CC_SYNTHESIZE_READONLY(int,m_nHeight,MapHeight);
};

#endif
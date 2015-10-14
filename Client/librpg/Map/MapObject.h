/***
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：地图内所有元素定义基类
 */

#ifndef __MapObject_h_
#define __MapObject_h_

#include "GameDef.h"

// 地图元素类型定义
enum MapObjectType{
	mapObjectType_None = 0,		// 非法的地图类型
	mapObjectType_Mask,			// 地图上的遮挡物件
	mapObjectType_Effect,		// 地图上装饰的特效及动画
	mapObjectType_Item,			// 地图上的物品
	mapObjectType_Chests,		// 地图中的宝箱
	mapObjectType_Npc,			// 地图中的NPC
	mapObjectType_Monster,		// 地图中的怪物
	mapObjectType_Player,		// 地图玩家
	mapObjectType_Pet,			// 地图宠物

	mapObjectType_Max			// 地图类型范围
};


typedef long long MapObjectID;

// 地图元素基本信息
struct MapObjectInfo
{
	MapObjectID		id;			// 唯一标识
	MapObjectType	type;		// 地图元素类型 见 MapObjectType
	int				dataid;		// 数据ID，通常是配置数据索引ID

	int				cx;			// 地图逻辑坐标位置
	int				cy;

	int				sizeX;		// 占用地图格子大小
	int				sizeY;

	int				height;		// 高度

	float			offsetX;	// 逻辑坐标到世界坐标的偏移位置
	float			offsetY;

	bool			selected;	// 是否被选中
	bool			insight;	// 是否在视野内
	bool			leaved;		// 是否标记为离开地图
	bool			deleted;	// 是否指定为删除
	int				skin_effect;// 皮肤效果

	MapObjectInfo()
	{
		memset(this,0,sizeof(MapObjectInfo));
	}
};

class TileMap;
class CRegion;

class MapObject : public Node
{
public:
	MapObject();
	MapObject(MapObjectInfo& info);
	virtual ~MapObject();

	/* Name		：GetMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取地图元素当前所在地图
	 * Param	: 
	 * Return	: TileMap*
	 */
	inline TileMap*	GetMap(){ return m_pMap; }

	/* Name		：GetBaseInfo
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取地图元素基本信息
	 * Param	: 
	 * Return	: MapObjectInfo&
	 */
	inline const MapObjectInfo& GetBaseInfo() const { return m_Info; }
	inline MapObjectID			GetId(){ return m_Info.id; }
	inline int					GetType(){ return m_Info.type; }
	inline int					GetDataID(){ return m_Info.dataid; }
	inline int					GetCellX(){ return m_Info.cx; }
	inline int					GetCellY(){ return m_Info.cy; }
	inline int					GetSizeX(){ return m_Info.sizeX; }
	inline int					GetSizeY(){ return m_Info.sizeY; }
	inline int					GetHeight(){ return m_Info.height; }
	inline float				GetOffsetX(){ return m_Info.offsetX; }
	inline float				GetOffsetY(){ return m_Info.offsetY; }
	inline bool					GetSelected(){ return m_Info.selected; }
	inline bool					GetInsight(){ return m_Info.insight; }
	inline bool					GetDeleted(){ return m_Info.deleted; }
	inline bool					GetLeaved(){ return m_Info.leaved;}
	inline int					GetSkinEffect(){ return m_Info.skin_effect; }

	inline void			SetId(MapObjectID id){ m_Info.id = id; }
	inline void			SetType(MapObjectType type){ m_Info.type = type; }
	inline void			SetInsight(bool val = true){ m_Info.insight = val; }
	inline void			SetLeaved(bool val = true){ m_Info.leaved = val; }
	inline void			SetDeleted(bool val = true){ m_Info.deleted = val; }

	/* Name		：SetSkinEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置皮肤效果 
	 * Param	: type 效果类型
	 * Return	: void
	 */
	virtual void SetSkinEffect(int type){ m_Info.skin_effect = type; }

	/* Name		：EnterMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 进入指定地图世界坐标
	 * Param	: pMap地图指针，pos地图中的世界坐标
	 * Return	: void
	 */
	virtual void EnterMap(TileMap* pMap,const Point& pos);

	/* Name		：EnterMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 进入指定地图
	 * Param	: pMap地图指针，cx，cy地图中的逻辑坐标
	 * Return	: void
	 */
	virtual void EnterMap(TileMap* pMap,int cx,int cy);

	/* Name		：LeaveMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 离开当前地图
	 * Param	: none
	 * Return	: void
	 */
	virtual void LeaveMap();

	/* Name		：EnterMapWithEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 进入指定地图 附带特效
	 * Param	: pMap地图指针，cx，cy地图中的逻辑坐标
	 * Return	: void
	 */
	virtual void EnterMapWithEffect(TileMap* pMap,int cx,int cy);

	/* Name		：LeaveMapWithEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 离开当前地图 附带特效
	 * Param	: none
	 * Return	: void
	 */
	virtual void LeaveMapWithEffect();

	/* Name		：SetDataID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置地图元素地图配置ID
	 * Param	: dataid
	 * Return	: void
	 */
	virtual void SetDataID(int dataid){ m_Info.dataid = dataid; }

	/* Name		：CheckSelected
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 检查地图元素是否被选中
	 * Param	: 需要检查点击的世界坐标位置
	 * Return	: true为选中，false未选中
	 */
	virtual bool CheckSelected(float x,float y);

	/* Name		：SetOffset
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置地图元素的逻辑坐标与世界坐标的偏移位置
	 * Param	: 偏移量x,y
	 * Return	: void
	 */
	virtual void SetOffset(float x,float y);

	/* Name		：SetCell
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置地图元素的逻辑坐标位置
	 * Param	: 逻辑坐标cx,cy
	 * Return	: void
	 */
	virtual void SetCell(int cx,int cy);
	
	/* Name		：getBoundingBox
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取碰撞区域
	 * Param	: none
	 * Return	: Rect 碰撞区域
	 */
	virtual const Rect& getBoundingBox();

	/* Name		：getHungingPoint
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取角色挂点
	 * Param	: idx 挂点索引
	 * Return	: Point 挂点位置
	 */
	virtual Point getHungingPoint(int idx);

	/* Name		：getHungingPointOffset
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取角色挂点偏移
	 * Param	: idx 挂点索引
	 * Return	: Point 挂点位置偏移
	 */
	virtual Point getHungingPointOffset(int idx);

	/* Name		：SetBoundingInfo
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置地图元素碰撞信息
	 * Param	: sizeX,sizeY,h 占用地图逻辑格子大小和高度
	 * Return	: void
	 */
	virtual void SetBoundingInfo(int sizeX,int sizeY,int h);

	/* Name		：UpdateBoundingInfo
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置地图元素碰撞信息
	 * Param	: none
	 * Return	: void
	 */
	virtual void UpdateBoundingInfo();

	/* Name		：UpdatePos
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 将地图元素的逻辑坐标和偏移位置更新到世界坐标位置
	 * Param	: 
	 * Return	: void
	 */
	virtual void UpdatePos();

	//////////////////////////////////////////////////////////////////////////
	// overrided 重载函数列表
	//////////////////////////////////////////////////////////////////////////
	/* Name		：init
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 初始化
	 * Param	: 
	 * Return	: 成功返回true，失败false
	 */
	virtual bool init(){ return true; }

	/* Name		：release
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 释放
	 * Param	: 
	 * Return	: void
	 */
	virtual	void release(){ Node::release();}

	/* Name		：setPosition
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置元素世界坐标系位置
	 * Param	: 世界坐标x,y
	 * Return	: void
	 */
	virtual void setPosition(float x,float y);

	/* Name		：setPosition
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置元素世界坐标系位置
	 * Param	: 世界坐标Point& position
	 * Return	: void
	 */
	virtual void setPosition(const Point &position);

	/* Name		：compareZ
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 与指定元素比较遮挡关系,
	 * Param	: pObj 要比较的地图元素
	 * Return	: 遮挡给定对象返回大于0，无遮挡关系返回 == 0，被指定对象遮挡返回 小于0
	 */
	virtual int compareZ(MapObject* pObj);

	//////////////////////////////////////////////////////////////////////////
	// 事件响应函数列表
	//////////////////////////////////////////////////////////////////////////
	/* Name		：onSelect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素被选中回调函数
	 * Param	: param == true 被选中，否则未被选中
	 * Return	: void
	 */
	virtual void onSelect(bool param){}

	/* Name		：onCover
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素被遮挡回调函数
	 * Param	: param == true 被遮挡，否则未遮挡
	 * Return	: void
	 */
	virtual void onCover(bool param){}

	/* Name		：onEnterSight
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素进入视野回调
	 * Param	: none
	 * Return	: void
	 */
	virtual void onEnterSight();

	/* Name		：onLeaveSight
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素离开视野回调
	 * Param	: none
	 * Return	: void
	 */
	virtual void onLeaveSight();

	/* Name		：onPreEnterSight
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素进入视野回调，处理渐入效果，重载该函数也可以做其他效果
	 * Param	: none
	 * Return	: void
	 */
	virtual void onPreEnterSight();

	/* Name		：onPreLeaveSight
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素离开视野回调，处理渐出效果，重载该函数也可以做其他效果
	 * Param	: none
	 * Return	: void
	 */
	virtual void onPreLeaveSight();

	/* Name		：onEnterSightCallBack
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素进入视野action播放完毕回调，处理渐入效果，重载该函数也可以做其他效果
	 * Param	: none
	 * Return	: void
	 */
	virtual void onEnterSightCallBack();

	/* Name		：onLeaveSightCallBack
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素离开视野action播放完毕回调，处理渐入效果，重载该函数也可以做其他效果
	 * Param	: none
	 * Return	: void
	 */
	virtual void onLeaveSightCallBack();

	/* Name		：onEnterRegion
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素进去某个区域回调函数
	 * Param	: pRegion进入的区域指针
	 * Return	: void
	 */
	virtual void onEnterRegion(CRegion* pRegion){}
	
	/* Name		：onLeaveRegion
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素离开某个区域回调函数
	 * Param	: pRegion离开的区域指针
	 * Return	: void
	 */
	virtual void onLeaveRegion(CRegion* pRegion){}

	/* Name		：onEnterDoor
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素进入传送门回调函数
	 * Param	: pRegion进入的传送门指针
	 * Return	: void
	 */
	virtual void onEnterDoor(CRegion* pRegion){}

	/* Name		：onLeaveDoor
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素离开传送门回调函数
	 * Param	: pRegion离开的传送门指针
	 * Return	: void
	 */
	virtual void onLeaveDoor(CRegion* pRegion){}

protected:
	MapObjectInfo		m_Info;			// 地图元素基本信息
	TileMap*			m_pMap;			// 地图元素所属地图，所有独立于地图存在的地图元素是没有意义的。

	Rect				m_RegionCell;		// 占用格子区域
	Rect				m_CollisionRect;	// 碰撞区域
	vector<Point>		m_HungingPoints;	// 挂点列表

private:
	static int			s_ID_COUNTER;			// 地图元素ID计数器，仅客户端使用，部分元素需要使用服务器ID
};

typedef map<MapObjectID,MapObject*>		MapObjectTable;
typedef	vector<MapObject*>				MapObjectList;

#endif
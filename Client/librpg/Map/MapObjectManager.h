/***
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：地图内所有交互元素管理类，所有在地图内的对象都在里面，遮挡关系计算处理
 */

#ifndef __MapObjectManager_h_
#define __MapObjectManager_h_

#include "GameDef.h"
#include "MapObject.h"

class TileMap;

class CMapObjectManager : public Ref
{
public:
	CMapObjectManager(TileMap* pMap);
	~CMapObjectManager();

	/* Name		：GetMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取当前服务的地图
	 * Param	: 
	 * Return	: TileMap*
	 */
	inline TileMap* GetMap(){ return m_pMap; }

	/* Name		：GetObjectList
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取地图中所有元素
	 * Param	: 
	 * Return	: MapObjectList&
	 */
	inline MapObjectList& GetObjectList(){ return m_Objects; }

	/* Name		：init
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 初始化
	 * Param	: none
	 * Return	: 成功返回true，失败返回false
	 */
	bool init();

	/* Name		：clear
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 清理所有地图元素
	 * Param	: none
	 * Return	: void
	 */
	void clear();

	/* Name		：release
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: override 释放
	 * Param	: none
	 * Return	: void
	 */
	void release();

	/* Name		：update
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 处理所有地图元素更新,清理掉被标记为删除的对象,遮挡关系计算
	 * Param	: none
	 * Return	: void
	 */
	void update(float dt);

	/* Name		：sortZorder
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 计算遮挡关系
	 * Param	: objs 对象数组,len 对象数组长度
	 * Return	: void
	 */
	void sortZorder(MapObject** objs,int len);

	/* Name		：sortZorder
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 计算zoder值
	 * Param	: obj 需要计算的对象元素 objs 对象数组,len 对象数组长度
	 * Return	: zoder值
	 */
	int getTopObject(MapObject** objs,int len,int idx = 0);

public:
	MapObject*		SelectObject(float x,float y,MapObject* pExclude = NULL );
	int				SelectObjects(float x,float y,MapObjectList& objects);
	int				SelectObjects(Point pos,MapObjectList& objects);

	MapObject*		getObject(MapObjectID id);
	MapObject*		getObject(int cx,int cy);
	int				getObjects(MapObjectType type,MapObjectList& objects);
	int				getObjects(int cx,int cy,MapObjectList& objects);
	int				getObjectsInView(MapObjectList& objects);
	int				getObjectsInView(MapObjectType type,MapObjectList& objects);
	MapObject*		getObjectNearBy(int cx,int cy,MapObjectType type);

	/* Name		：addObject
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 将对象加入管理器
	 * Param	: pObject 指定地图元素对象指针
	 * Return	: void
	 */
	void addObject(MapObject* pObject);

	/* Name		：removeObject
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移除对象
	 * Param	: pObject 指定地图元素对象指针
	 * Return	: void
	 */
	void removeObject(MapObject* pObject);

private:
	MapObjectList	m_Objects;			// 地图元素列表
	TileMap*		m_pMap;				// 当前服务的地图
};

#endif
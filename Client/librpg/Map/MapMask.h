/***
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：地图内遮挡物件，map_context中数据创建而来
 */

#ifndef __MapMask_h_
#define __MapMask_h_

#include "MapObject.h"
#include "map_def.h"
#include "ShaderSprite.h"

class MapMask;

// 地图遮挡物件数据信息
struct MapMaskInfo
{
	MapMaskInfo(int idx,map_mask* pMask) : tag(idx),flag(0),mask(pMask),mask_relation(NULL),obj(NULL)
	{
	}

	int tag;		// 索引
	int flag;		// 状态标记
	const map_mask* mask;	// 遮挡物件基本信息
	unsigned char* mask_relation;	// 遮挡关系数据
	MapMask* obj;	// 遮挡物件对象指针
};

typedef vector<MapMaskInfo*> MapMaskList;

class MapMask : public MapObject
{
public: 
	MapMask();
	~MapMask();

	/* Name		：createWithImage
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过image创建MapMask对象
	 * Param	: 已加载好的img图片资源
	 * Return	: void
	 */
	static MapMask* createWithMaskInfo(MapMaskInfo* pInfo,Image* img,bool grey = false);

	/* Name		：initWithImage
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过image初始化MapMask对象
	 * Param	: 已加载好的img图片资源
	 * Return	: void
	 */
	bool initWithMaskInfo(MapMaskInfo* pInfo,Image* img,bool grey = false);

	/* Name		：compareZ
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: override 与指定元素比较遮挡关系
	 * Param	: pObj 要比较的地图元素
	 * Return	: 遮挡给定对象返回大于0，无遮挡关系返回 == 0，被指定对象遮挡返回 小于0
	 */
	int compareZ(MapObject* pObj);

	/* Name		：calMaskRelation
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 计算遮挡关系
	 * Param	: pos物体或者角色的世界坐标
	 * Return	: 遮挡给定对象返回true，非遮挡给定对象返回false
	 */
	bool calMaskRelation(const Point &pos);

	inline ShaderSprite* getShaderSprite(){ return m_pSprite; }

private:
	MapMaskInfo*	m_pInfo;
	ShaderSprite*	m_pSprite;
};

#endif // __MapMask_h_ 
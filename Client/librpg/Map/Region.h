/***
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：地图内所有区域定义
 */

#ifndef __Region_h_
#define __Region_h_

#include "GameDef.h"
#include "map_def.h"

typedef map<string,int> RegionProperties;

class CRegion
{
public:
	CRegion();
	CRegion(int cx,int cy,int sx,int sy);
	~CRegion();

public:
	/* Name		：initWithMapRegion
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过map_region结构初始化对象
	 * Param	: region 
	 * Return	: 成功返回true，失败返回false
	 */
	bool initWithMapRegion(map_region* region);
	
	/* Name		：getMapRegionData
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取map_region结构数据
	 * Param	: region map_region指针
	 * Return	: void 
	 */
	void getMapRegionData(map_region* region);

	/* Name		：addProperty
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 为区域增加一条属性,如果属性已存在，则替换属性值。
	 * Param	: name属性名称，val为属性值
	 * Return	: void
	 */
	void addProperty(string name,int val);

	/* Name		：setProperty
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 修改指定属性对应的值
	 * Param	: name属性名称，val为属性值
	 * Return	: void
	 */
	void setProperty(string name,int val);

	/* Name		：getProperty
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取指定属性对应的值
	 * Param	: name属性名称
	 * Return	: 属性值
	 */
	int	getProperty(string name);

	/* Name		：removeProperty
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移除指定属性
	 * Param	: name属性名称
	 * Return	: void
	 */
	void removeProperty(string name);

	/* Name		：removeAllProperty
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移除所有属性
	 * Param	: none
	 * Return	: void
	 */
	void removeAllProperty();

	/* Name		：containsCell
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 检查指定坐标是否包含在区域内部
	 * Param	: 逻辑坐标cx,cy
	 * Return	: true在内部，false不再内部
	 */
	bool containsCell(int cx,int cy);

	inline int getEndX(){ return m_nOriginX+m_nSizeX; }
	inline int getEndY(){ return m_nOriginY+m_nSizeY; }
	inline RegionProperties& getProperties(){ return m_Properties; }

	/* Name		：isMonsterRegion
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断这个区域是否是怪物区域
	 * Param	: none
	 * Return	: true是，false不是
	 */
	bool isMonsterRegion();

protected:
	// 区域的起点，以逻辑坐标为单位
	CC_SYNTHESIZE(int,m_nOriginX,OriginX);
	CC_SYNTHESIZE(int,m_nOriginY,OriginY);
	// 区域的大小，以逻辑坐标格子为单位
	CC_SYNTHESIZE(int,m_nSizeX,SizeX);
	CC_SYNTHESIZE(int,m_nSizeY,SizeY);
	// 区域属性对应表,属性名---属性值
	RegionProperties m_Properties;
	// 区域是否被选中
	CC_SYNTHESIZE(bool,m_bSelected,Selected);
};

#endif
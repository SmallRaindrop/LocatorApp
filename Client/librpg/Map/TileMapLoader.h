/* Name		：TileMapLoader
 * Author	：YueLiangYou
 * Date		: 2015-06-24
 * Desc		: 地图异步加载对象,负责地图本身相关的资源异步加载。（地表图片加载及地图遮挡物件加载）
 * Param	: none
 * Return	: void
 */

#ifndef __TileMapLoader_h_
#define __TileMapLoader_h_

#include "GameDef.h"
#include "ResBase.h"
#include "TileManager.h"
#include "MapMask.h"

struct TileInfoAsync
{
	int			tag;
	Image*		img;
};

struct MaskInfoAsync
{
	int tag;					// 索引
	int relate_data_size;		// 遮挡关系数据长度
	int mask_data_size;			// 遮挡数据总长度，包括遮挡关系和遮挡数据
	Image* img;					// 图片信息
	unsigned char* mask_relation;	// 遮挡关系数据
};

class TileMap;

class TileMapLoader : public ResBase
{
public:
	TileMapLoader(TileMap* pMap);
	~TileMapLoader();

public:
	/* Name		：reset
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 重置需要加载的元素
	 * Param	: tiles需要加载的tile块信息，masks需要加载的遮挡物件信息
	 * Return	: void
	 */
	void reset(vector<TileInfo*>& tiles,vector<MapMaskInfo*>& masks);

	/* Name		：load
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: override 加载执行体
	 * Param	: none
	 * Return	: true成功，false失败
	 */
	bool load();

	/* Name		：onLoadComplete
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: override 加载完成回调
	 * Param	: pTask 任务对象指针
	 * Return	: 
	 */
	void onLoadComplete(ResTask* pTask);

	/* Name		：loadTileImages
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 加载地图块
	 * Param	: none
	 * Return	: void
	 */
	void loadTileImages();

	/* Name		：loadMaskImages
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 加载遮挡物件
	 * Param	: none
	 * Return	: void
	 */
	void loadMaskImages();

	/* Name		：loadMaskImages
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 加载完成后更新地图块
	 * Param	: none
	 * Return	: void
	 */
	void refreshTiles();

	/* Name		：loadMaskImages
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 加载完成后更新遮挡物件
	 * Param	: none
	 * Return	: void
	 */
	void refreshMasks();

private:
	Image* fillMaskImageByMask(Data &data,MaskInfoAsync* pMask);

protected:
	vector<TileInfoAsync*>	m_vTiles;	// 待加载的地图tile列表
	vector<MaskInfoAsync*>	m_vMasks;	// 待加载的地图遮挡物件列表

	TileMap*			m_pMap;		// 服务的地图指针
};

#endif // __TileMapLoader_h_
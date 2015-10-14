/***
 * 模块：GameMap
 * 作者：岳良友
 * 时间：2015-07-2
 * 说明：游戏地图
 * 对tileMap的功能扩展
 */


#ifndef __GameMap_h_
#define __GameMap_h_

#include "GameDef.h"
#include "Map/TileMap.h"
#include "Map/AStar.h"
#include "db.h"
#include "GameMapTypes.h"

class GameMap : public TileMap
{
public:
	GameMap();
	~GameMap();

	CREATE_FUNC(GameMap);

	/* Name		：loadMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 按照配置数据加载地图，异步调用
	 * Param	: mapid 地图配置数据ID
	 * Return	: true 成功，false 失败
	 */
	bool loadMap(int mapid);

	bool init();
	void update(float dt);

	/* Name		：updateView
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新视点区域
	 * Param	: none
	 * Return	: void
	 */
	void updateView();

	/* Name		：shake
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 屏幕抖动
	 * Param	: float deltaX = 1.0f,float deltaY = 1.0f 震动幅度,float rate,int times 震动的频率与次数
	 * Return	: void
	 */
	void shake(float deltaX = 1.0f,float deltaY = 1.0f,float rate = 0.1f,int times = 5);

	/* Name		：onShakeEnded
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 屏幕抖动结束回调
	 * Param	: none
	 * Return	: void
	 */
	void onShakeEnded();

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
	//void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	//void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	//void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
	//void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);

	/* Name		：getDistance
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断两个逻辑坐标点之间的距离
	 * Param	: pos0 起点，pos1 目标点
	 * Return	: 距离
	 */
	int getDistance(const APoint& pos0,const APoint& pos1);

	/* Name		：checkTargetPos
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断起点到目标点之间是否有阻挡点，如果没有直接返回阻挡的，如果有则返回最后一个非阻挡点
	 * Param	: pos0 起点 ， pos1 目标点
	 * Return	: 最后一个非阻挡点
	 */
	APoint checkTargetPos(const APoint& pos0,const APoint& pos1);

	/* Name		：checkTargetPos
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断起点到目标点之间是否有阻挡点，如果没有直接返回阻挡的，如果有则返回最后一个非阻挡点
	 * Param	: pos0 起点 ， pos1 目标点，最大距离限制
	 * Return	: 最后一个不超过最大距离限制的非阻挡点
	 */
	APoint checkTargetPosWithDistance(const APoint& pos0,const APoint& pos1,int dis);

	/* Name		：ShowEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 在地图上显示一个特效
	 * Param	: int dataid,const string& name,const Point& pos,float duration 播放时间 S,scale 放大系数
	 * Return	: void
	 */
	void ShowEffect(int dataid,const string& name,const Point& pos,float duration = 0.0f,float scale = 1.0f);

	/* Name		：ShowEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 在地图上显示一个特效
	 * Param	: Effect* pEffect,const Point& pos,float duration 播放时间 S,scale 放大系数
	 * Return	: void
	 */
	void ShowEffect(Effect* pEffect,const Point& pos,float duration = 0.0f,float scale = 1.0f);

	/* Name		：ShowEffectCallBack
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示地图特效通用回调
	 * Param	: Layer* pLayer 特效所在层
	 * Return	: void
	 */
	void ShowEffectCallBack(Effect* pEffect);

	/* Name		：getMapId
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取地图唯一标识ID
	 * Param	: none
	 * Return	: __int64 地图ID
	 */
	inline __int64 getMapId(){ return m_nId; }

	/* Name		：setMapId
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置地图唯一标识ID
	 * Param	: __int64 id 地图ID
	 * Return	: void
	 */
	inline void setMapId(__int64 id){ m_nId = id; }

	/* Name		：getMapData
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取地图配置数据
	 * Param	: none
	 * Return	: MapCfg* 地图配置数据指针
	 */
	inline MapCfg* getMapData(){ return m_pData; }

	/* Name		：getMapDataID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取地图配置数据ID
	 * Param	: none
	 * Return	: int 地图配置数据ID
	 */
	inline int getMapDataID(){ return m_pData?m_pData->id:0; }

	/* Name		：isFightMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否是战斗地图
	 * Param	: none
	 * Return	: 
	 */
	inline bool isFightMap(){ return m_pData?m_pData->functiontype == GameMapFuncType_Fight:false; }

	/* Name		：isNormalMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否是常规地图
	 * Param	: none
	 * Return	: 
	 */
	inline bool isNormalMap(){ return m_pData?m_pData->functiontype == GameMapFuncType_Normal:false; }

	/* Name		：getFuncType
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取地图玩法类型
	 * Param	: none
	 * Return	: 
	 */
	inline GameMapFuncType getFuncType(){ return m_pData?GameMapFuncType(m_pData->functiontype):GameMapFuncType_Normal; }

	/* Name		：getPlayType
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取地图玩法类型
	 * Param	: none
	 * Return	: 
	 */
	inline GameMapPlayType getPlayType(){ return m_pData?GameMapPlayType(m_pData->play_type):GameMapPlayType_None; }

	/*副本类型-开放,单人,多人*/
	inline GameMapType	getType(){ return m_pData?GameMapType(m_pData->type):GameMapType_None; }

	/* Name		：getMapBgFileName
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取地图模糊背景文件
	 * Param	: none
	 * Return	: 地图名称
	 */
	inline string getMapBgFileName(){ return "assets/map/"+getMapContext()->name+".jpg"; }

	inline Layer* getEffectLayer(){ return m_pEffectLayer; }
	
	inline vector<int>&	getReliveRules() { return m_reliveRules; }

protected:
	__int64		m_nId;			// 地图ID，由服务器生成的唯一标识
	MapCfg*		m_pData;		// 地图配置数据
	Layer*		m_pEffectLayer;	// 游戏中的特效层，技能特效及其他一些效果特效

	vector<int>	m_reliveRules;
};

#endif //__GameMap_h_
/* Name		：MapEffect
 * Author	：YueLiangYou
 * Date		: 2015-06-24
 * Desc		: 地图上的特效及动画，有的是配置的，有的是动态加入进来的
 * Param	: none
 * Return	: void
 */

#ifndef __MapEffect_h_
#define __MapEffect_h_

#include "MapObject.h"
#include "Role/Effect.h"

class MapEffect : public MapObject
{
public: 
	MapEffect();
	~MapEffect();

	/* Name		：createWithDataID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过配置数据ID创建特效
	 * Param	: dataid
	 * Return	: void
	 */
	static MapEffect* createWithDataID(int dataid);

	/* Name		：initWithDataID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过配置数据ID初始化特效
	 * Param	: dataid
	 * Return	: void
	 */
	bool initWithDataID(int dataid);

	/* Name		：update
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 毎帧更新
	 * Param	: none
	 * Return	: void
	 */
	virtual void update(float dt);

	/* Name		：SetDataID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: override 设置地图元素地图配置ID
	 * Param	: dataid
	 * Return	: void
	 */
	void SetDataID(int dataid);

	/* Name		：getEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取特效对象指针
	 * Param	: none
	 * Return	: 特效对象指针
	 */
	inline Effect* getEffect(){ return m_pEffect; }

	/* Name		：SetSkinEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置皮肤效果 
	 * Param	: type 效果类型
	 * Return	: void
	 */
	virtual void SetSkinEffect(int type);

protected:
	Effect* m_pEffect;		// 特效对象
};

#endif //__MapEffect_h_
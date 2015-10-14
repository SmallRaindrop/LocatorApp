/***
 * 模块：动画及特效
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：游戏内除了角色以外的所有特效及动画
 */

#pragma once

#include "GameDef.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"
#include "NotifyCenter.h"


using namespace cocos2d;
using namespace cocostudio;
class Effect;
typedef vector<Effect*>	EffectList;

class Effect : public Node
{
public:
	/* Name		：SplitDataID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过指定ID规则拆分获取dataID ID规则：最低2位为播放索引，高位为dataid
	 * Param	: none
	 * Return	: int dataid
	 */
	static int SplitDataID(int id){ return id / 100; }

	/* Name		：SplitPlayIndex
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		:  通过指定ID规则拆分获取播放索引
	 * Param	: none
	 * Return	: int index
	 */
	static int SplitPlayIndex(int id){ return id % 100; }

	/* Name		：GetEffectListByConfig
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过配置创建特效
	 * Param	: config 配置参数，list 特效列表
	 * Return	: int count
	 */
	static int GetEffectListByConfig(const string& config,EffectList& list);

public: 
	Effect();
	virtual ~Effect();

	CREATE_FUNC(Effect);

	/* Name		：createWithDataID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过dataID创建一个特效
	 * Param	: id 特效的ID，可以通过它索引到动画json文件。idx 指定JSON文件的第几个动画，loop 是否需要循环播放
	 * Return	: 特效指针
	 */
	static Effect* createWithDataID(int id,bool bLoop = false);

	/* Name		：setDataID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置dataID
	 * Param	: id 特效的ID，可以通过它索引到动画json文件。
	 * Return	: void
	 */
	virtual void setDataID(int dataid);

	/* Name		：onNotifyCenter
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 收到通知中心传来消息
	 * Param	: msg 消息号
	 * Return	: void
	 */
	virtual void onNotifyCenter(int msg);

	/* Name		：onAnimationEvent
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 动作事件响应函数
	 * Param	: armature movementType movementID
	 * Return	: void
	 */
	virtual void onAnimationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);

	/* Name		：onFrameEvent
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 帧事件响应函数
	 * Param	: bone 骨骼，evt 事件自定义参数，
	 * Return	: void
	 */
	virtual void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	/* Name		：loadData
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 加载指定动画
	 * Param	: name 动画名称
	 * Return	: void
	 */
	virtual void loadData(const char* name);

	/* Name		：unloadData
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 卸载加载动画
	 * Param	: none
	 * Return	: void
	 */
	virtual void unloadData();

	/* Name		：playWithName
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 播放指定动画
	 * Param	: name 特效名称（播放的动画）， loop 是否循环播放 -1 循环播放
	 * Return	: void
	 */
	virtual void playWithName(const string& name,int loop = -1);

	/* Name		：setDuration
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置动画播放时间
	 * Param	: duration 时间 S
	 * Return	: void
	 */
	virtual void setDuration(float duration);

	/* Name		：setSkinEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置皮肤效果
	 * Param	: type 效果类型
	 * Return	: void
	 */
	virtual void setSkinEffect(SkinEffectType type);

	/* Name		：play
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 播放动画
	 * Param	: none
	 * Return	: void
	 */
	virtual void play();

	/* Name		：getDataID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取数据文件索引dataID
	 * Param	: none
	 * Return	: int dataId
	 */
	inline int getDataID(){ return m_nDataID; }

	/* Name		：getArmature
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取动画对象指针
	 * Param	: none
	 * Return	: 动画对象指针
	 */
	inline Armature* getArmature(){ return m_pArmature; }

	/* Name		：getPlayIndex
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取播放索引
	 * Param	: none
	 * Return	: int
	 */
	inline string getName(){ return m_sName; }

	/* Name		：getLoop
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取循环次数
	 * Param	: none
	 * Return	: int
	 */
	inline int getLoop(){ return m_nLoop; }

	/* Name		：getDuration
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取播放时间
	 * Param	: none
	 * Return	: int
	 */
	inline float getDuration(){ return m_fDuration; }

	/* Name		：getHungingPoint
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取特效挂点
	 * Param	: none
	 * Return	: int
	 */
	inline int getHungingPoint(){ return m_nHungingPoint; }

	/* Name		：setPlayIndex
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置播放索引
	 * Param	: index 播放索引
	 * Return	: void
	 */
	inline void setName(const string& name){ m_sName = name; play();}

	/* Name		：setLoop
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置循环次数
	 * Param	: loop 循环次数 -1 为循环播放
	 * Return	: void
	 */
	inline void setLoop(int loop = -1){ m_nLoop = loop; play();}

	/* Name		：setHungingPoint
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置特效挂点
	 * Param	: hpt 挂点
	 * Return	: void
	 */
	inline void setHungingPoint(int hpt){ m_nHungingPoint = hpt; }

protected:
	int			m_nDataID;			// dataid JSON文件索引
	string		m_sName;			// 特效名称，播放动画索引
	float 		m_fDuration;		// 播放时间
	int			m_nLoop;			// 循环次数 -1为循环播放
	Armature*	m_pArmature;		// 动画对象
	int			m_nHungingPoint;	// 特效挂点
	SkinEffectType m_nSkinEffectType;	// 皮肤效果
};
/***
 * 模块：子弹
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：子弹数据及子弹管理器，子弹的生命周期：1.爆炸后销毁；2.生命周期耗尽销毁
 */

#ifndef __Bullet_h_
#define __Bullet_h_

#include "GameDef.h"
#include "db.h"
#include "Effect.h"
#include "Singleton.h"
#include "MapObject.h"

enum BulletType
{
	BulletType_None,
	BulletType_SingleFly,		// 单子弹弹道攻击
	BulletType_Multi,			// 多子弹弹道攻击 平行
	BulletType_MultiAngle,		// 多子弹弹道攻击 角度
	BulletType_SingleHitScan,	// 命中扫描，没有碰撞检查，直接命中目标格子，落雷，陨石，光束
};

class RoleFighter;

class Bullet : public Node
{
public:
	Bullet();
	Bullet(__int64 id,BulletCfg* pData);
	~Bullet();

	CREATE_FUNC(Bullet);

	static Bullet* CreateWithDataID(__int64 id,int dataid,const Point& pos,const Point& targetPos,MapObjectID casterid,SkillCfg* pSkill);
	static Bullet* CreateWithData(__int64 id,BulletCfg* pData,const Point& pos,const Point& targetPos,MapObjectID casterid,SkillCfg* pSkill);

	/* Name		：GetId
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取子弹唯一ID
	 * Param	: none
	 * Return	: id
	 */
	inline __int64 GetId(){ return m_llId; }
	inline int GetIndex(){ return m_nIndex; }

	/* Name		：GetData
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取子弹配置数据
	 * Param	: none
	 * Return	: BulletCfg* 子弹配置数据
	 */
	inline BulletCfg* GetData(){ return m_pData; }

	/* Name		：GetDataID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取子弹配置数据ID = 子弹ID
	 * Param	: none
	 * Return	: int 子弹ID
	 */
	inline int GetDataID(){ return GetData()->id; }

	/* Name		：GetType
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取子弹类型
	 * Param	: none
	 * Return	: int 子弹type
	 */
	inline int GetType(){ return GetData()->type; }

	/* Name		：Reload
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 重置子弹相关数据
	 * Param	: bulletid 子弹ID
	 * Return	: void
	 */
	void Reload(int bulletid);

	/* Name		：Reload
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 重置子弹相关数据
	 * Param	: pData 配置数据
	 * Return	: void
	 */
	void Reload(BulletCfg* pData);

	void Clear();

	/* Name		：draw
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 画子弹碰撞区域
	 * Param	: none
	 * Return	: void
	 */
	virtual void draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated);
	virtual void onDraw(Renderer *renderer, const kmMat4& transform, bool transformUpdated);

	/* Name		：Update
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新子弹相关数据
	 * Param	: dt 时间位移
	 * Return	: void
	 */
	virtual void Update(float dt);

	/* Name		：Prepare
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 预处理函数
	 * Param	: none
	 * Return	: void
	 */
	virtual void Prepare();

	/* Name		：ProcessFly
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 处理子弹飞行
	 * Param	: dt 时间位移
	 * Return	: void
	 */
	virtual void ProcessFly(float dt);

	/* Name		：OnHit
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 子弹命中响应函数
	 * Param	: none
	 * Return	: void
	 */
	virtual void OnHit(RoleFighter* pTarget);

	/* Name		：IsHited
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 检查目标是否在碰撞列表中
	 * Param	: none
	 * Return	: void
	 */
	virtual bool IsHited(RoleFighter* pTarget);

	/* Name		：OnBlast
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 爆炸处理事件函数
	 * Param	: none
	 * Return	: void
	 */
	virtual void OnBlast();

	/* Name		：Blast
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 爆炸处理函数
	 * Param	: none
	 * Return	: void
	 */
	virtual void Blast();

	/* Name		：checkCollision
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 碰撞检测，判断子弹是否与指定区域发生碰撞
	 * Param	: Rect 碰撞区域
	 * Return	: 碰撞返回true 否则返回false
	 */
	virtual bool checkCollision(const Rect& rect);

	/* Name		：SetTargetPos
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置目标点
	 * Param	: pos 位置
	 * Return	: void
	 */
	virtual void SetTargetPos(const Point& pos);

	/* Name		：SetTargetVec
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置目标方向
	 * Param	: pos 方向向量
	 * Return	: void
	 */
	inline void SetTargetVec(const Point& pos){ m_TargetVec = pos; }

	/* Name		：SetId
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置ID
	 * Param	: id 
	 * Return	: void
	 */
	inline void SetId(__int64 id){ m_llId = id; }
	inline void SetIndex(int idx){ m_nIndex = idx; }

	/* Name		：SetCasterID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置发射者ID
	 * Param	: id 发射者ID
	 * Return	: void
	 */
	inline void SetCasterID(__int64 id){ m_CasterID = id; }

	/* Name		：SetCasterType
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置发射者类型
	 * Param	: type 发射者类型，人还是怪物
	 * Return	: void
	 */
	inline void SetCasterType(int type){ m_nCasterType = type; }

	/* Name		：SetSkillData
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置技能配置数据
	 * Param	: pSkill 技能配置数据
	 * Return	: void
	 */
	inline void SetSkillData(SkillCfg* pSkill){ m_pSkillData = pSkill; }

	inline SkillCfg* GetSkillData(){ return m_pSkillData; }
	inline __int64 GetCasterID(){ return m_CasterID; }
	inline int GetCasterType(){ return m_nCasterType; }

	/* Name		：IsDie
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断子弹生命是否耗尽,子弹的生命周期：1.穿透力耗尽爆炸后销毁；2.生命周期耗尽爆炸后销毁
	 * Param	: none
	 * Return	: true 消亡，false 没有
	 */
	inline bool IsDie(){ return (m_fLifeTime*1000>GetData()->duration || m_nPenetratePower <= 0 ); }

	/* Name		：IsCollisionNeed
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断子弹是否有碰撞检测的需要
	 * Param	: none
	 * Return	: true 需要，false 没有
	 */
	inline bool IsCollisionNeed(){ return m_bCollision; }

	/* Name		：SetCollisionNeed
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置子弹是否有碰撞检测的需要
	 * Param	: val == true 需要，false 没有
	 * Return	: none
	 */
	inline void SetCollisionNeed(bool val = true){ m_bCollision = val; }

protected:
	__int64			m_llId;			// 子弹唯一标识
	int				m_nIndex;		// 子弹组中的第几颗子弹
	BulletCfg*		m_pData;		// 子弹配置数据
	EffectList		m_effectListAim;		// 子弹表现特效
	EffectList		m_effectListFly;		// 子弹表现特效
	EffectList		m_effectListBlast;		// 子弹表现特效
	Point			m_TargetPos;	// 目标位置
	Point			m_TargetVec;	// 目标方向
	float			m_fLeft;		// 碰撞区域
	float			m_fRight;
	float			m_fTop;
	float			m_fBottom;
	__int64			m_CasterID;		// 发射者ID
	int				m_nCasterType;	// 发射者是人还是怪物
	SkillCfg*		m_pSkillData;	// 产生子弹的技能数据
	int				m_nPenetratePower;	// 子弹当前穿透力
	float			m_fLifeTime;		// 生命周期
	bool			m_bCollision;		// 是否需要做碰撞检测，只有自己发的子弹才需要做碰撞检测，其他人发的不需要。
	vector<__int64> m_vCollisionList;	// 碰撞列表
};

typedef vector<Bullet*>	BulletList;
typedef vector<Bullet*>	BulletGroup;

// 子弹管理器
class BulletManager : public Singleton<BulletManager>
{
public:
	BulletManager();
	~BulletManager();

	/* Name		：CreateBullet
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 创建一个子弹
	 * Param	: id 子弹唯一标识，dataid 子弹ID,pCaster 释放者对象指针，SkillCfg* pSkill 技能配置数据，targetPos 目标点
	 * Return	: void
	 */
	void CreateBullet(__int64 id,int dataid,RoleFighter* pCaster,SkillCfg* pSkill,const Point& pos,int multi = 0);

	/* Name		：AddBullet
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 添加一个子弹
	 * Param	: pBullet 子弹指针
	 * Return	: void
	 */
	void AddBullet(Bullet* pBullet);

	/* Name		：Remove
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移除一个子弹
	 * Param	: pBullet 子弹指针
	 * Return	: void
	 */
	void Remove(Bullet* pBullet);

	/* Name		：Clear
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 清空子弹列表
	 * Param	: none
	 * Return	: void
	 */
	void Clear();

	/* Name		：UpdateBullet
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新所有子弹数据
	 * Param	: dt 时间位移
	 * Return	: void
	 */
	void UpdateBullet(float dt);

	/* Name		：GetBulletList
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取子弹列表
	 * Param	: none
	 * Return	: GetBulletList& 子弹列表引用
	 */
	inline BulletList& GetBulletList() { return m_Bullets; }

private:
	BulletList m_Bullets;
};

#define gBulletMgr BulletManager::Instance()

#endif //__Bullet_h_
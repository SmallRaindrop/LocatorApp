/***
 * 模块：BUFF
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：BUFF数据及BUFF管理
 */

#ifndef __RoleBuff_h_
#define __RoleBuff_h_

#include "GameDef.h"
#include "db.h"
#include "Effect.h"

enum RoleBuffType
{
	RoleBuffType_None,
	RoleBuffType_ChangeProperty,	// 1 修改属性
	RoleBuffType_Damage,			// 2 周期性伤害生命，法力（dot，hot）
	RoleBuffType_SlowDown,			// 3 减速：状态，降低目标移动速度，p1=p1*(1+p2/10000*技能强度/10000)
	RoleBuffType_Skill,				// 4 周期性调用技能，p1 调用技能id
	RoleBuffType_Transfer,			// 5 buff伤害的百分比转化为生命值恢复,p1=p1*(1+p2/10000*技能强度/10000)
};

class RoleBuff
{
public:
	RoleBuff(__int64 id,int buffid,int duration);
	~RoleBuff();

	/* Name		：GetData
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取BUFF配置数据
	 * Param	: none
	 * Return	: BuffCfg* BUFF配置数据
	 */
	inline BuffCfg* GetData(){ return m_pData; }

	inline int64 GetBuffIdentity(){ return m_id; }
	inline int GetBuffDataID(){ return m_pData->id; }
	inline int GetDuration(){ return m_nDuration; }
	inline void SetDuration(int duration){ m_nDuration = duration; }
	inline string& GetIcon(){ return m_pData->icon; }
	inline EffectList& GetEffectList(){ return m_effectList; }

	/* Name		：Reload
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 重置buff相关数据
	 * Param	: buffid BUFF ID
	 * Return	: void
	 */
	void Reload(int buffid);

	void Clear();

public:
	int64		    m_id;			// buff标识ID
	int			    m_nDuration;	// Buff计时
	BuffCfg*	    m_pData;		// BUFF配置数据
	EffectList		m_effectList;		// 特效列表
};

typedef vector<RoleBuff*> RoleBuffList;

class RoleBuffManager
{
public:
	RoleBuffManager();
	~RoleBuffManager();

	/* Name		：Insert
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 添加一个BUFF
	 * Param	: RoleBuff* 新加的BUFF指针
	 * Return	: void
	 */
	void		Insert(RoleBuff* pBuff);

	/* Name		：Remove
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移除一个BUFF
	 * Param	: buffid BUFF配置ID
	 * Return	: void
	 */
	void		Remove(int64 buffid);

	/* Name		：Get
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取一个BUFF
	 * Param	: buffid BUFF配置ID
	 * Return	: RoleBuff* 角色BUFF
	 */
	RoleBuff*	Get(int64 buffid);

	/* Name		：Clear
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 清理BUFF数据
	 * Param	: none
	 * Return	: void
	 */
	void		Clear();

	/* Name		：Count
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 统计BUFF个数
	 * Param	: none
	 * Return	: int BUFF个数
	 */
	inline int Count(){ return (int)m_Buffs.size(); }

	/* Name		：GetBuffList
	 * Author	：Liyang
	 * Date		: 2015-08-21
	 * Desc		: 获取buff列表
	 * Param	: none
	 * Return	: RoleBuffList BUFF列表
	 */
	inline RoleBuffList	GetBuffList(){return m_Buffs;}

private:
	RoleBuffList m_Buffs;
};

#endif //__RoleBuff_h_
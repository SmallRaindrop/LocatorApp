/***
 * 模块：技能
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：技能数据及技能管理
 */

#ifndef __Skill_h_
#define __Skill_h_

#include "GameDef.h"
#include "db.h"
#include "SkillType.h"

class CSkill
{
public:
	typedef enum _cdType
	{
		CdType_None,
		CdType_Skill,	//技能CD
		CdType_Globe,	//公共CD
	}CdType;
public:
	CSkill();
	CSkill(int skillid);
	~CSkill();

	/* Name		：GetData
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取技能配置数据
	 * Param	: none
	 * Return	: SkillCfg* 技能配置数据
	 */
	inline SkillCfg* GetData(){ return m_pData; }

	/* Name		：GetDataID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取技能配置数据ID = 技能ID
	 * Param	: none
	 * Return	: int 技能ID
	 */
	inline int GetDataID(){ return GetData()->id; }

	/* Name		：IsPassive
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断技能是否是被动技能
	 * Param	: none
	 * Return	: bool
	 */
	inline bool	IsPassive(){ return GetData()->passitive != 0; }

	/* Name		：IsNormalAttack
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断技能是否是普通攻击
	 * Param	: none
	 * Return	: bool
	 */
	inline bool	IsNormalAttack(){ return GetData()->normal_attack != 0; }

	/* Name		：GetLevel
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取技能等级
	 * Param	: none
	 * Return	: int 技能等级
	 */
	inline int GetLevel(){ return m_nLevel; }

	/* Name		：SetLevel
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置技能等级
	 * Param	: lv 技能等级
	 * Return	: void
	 */
	inline void	SetLevel(int lv){ m_nLevel = lv; }

	/* Name		：GetType
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取技能类型
	 * Param	: none
	 * Return	: int 技能类型
	 */
	inline int GetType(){ return GetData()->type; }

	/* Name		：GetCDTime
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取技能CD时间 ms
	 * Param	: none
	 * Return	: int 技能CD时间 ms
	 */
	inline int GetCDTime(){ return m_nCDTime; }

	/* Name		：SetCDTime
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置技能CD时间 ms
	 * Param	: cd 技能CD时间 ms
	 * Return	: void
	 */
	inline void	SetCDTime(int cd){ m_nCDTime = cd; }

	//cd类型
	inline CdType	GetCDType(){ return m_cdType; }
	inline void		SetCDType(CdType cdType){ m_cdType = cdType; }

	/* Name		：GetTickTime
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取技能连击计时 ms
	 * Param	: none
	 * Return	: int 技能连击计时 ms
	 */
	inline int GetTickTime(){ return m_nTickTime; }

	/* Name		：SetTickTime
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置技能连击时间 ms
	 * Param	: tick 连击时间 ms
	 * Return	: void
	 */
	inline void	SetTickTime(int tick){ m_nTickTime += tick; }

	/* Name		：m_nTickIndex
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取触发第几个连击技能
	 * Param	: none
	 * Return	: int 触发第几个连击技能
	 */
	inline int GetTickIndex(){ return m_nTickIndex; }

	/* Name		：Reload
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 重置技能相关数据
	 * Param	: skillid 技能ID
	 * Return	: void
	 */
	void Reload(int skillid);

	/* Name		：GetTickSkill
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取连击技能ID
	 * Param	: none
	 * Return	: CSkill* 如果有连击返回连击技能，否则返回本技能
	 */
	SkillCfg* GetTickSkill();

protected:
	int				m_nLevel;		// 技能等级
	int				m_nCDTime;		// 技能冷却时间
	CdType			m_cdType;		// Cd类型
	int				m_nTickTime;	// 技能连击计时
	int				m_nTickIndex;	// 触发第几个连击技能
	vector<int>		m_vTickSkills;	// 连击技能ID
	SkillCfg*		m_pData;		// 技能配置数据
};

typedef vector<CSkill*>	SkillList;

// 技能管理器
class SkillManager
{
public:
	SkillManager();
	~SkillManager();

	/* Name		：Insert
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 添加一个技能
	 * Param	: skillid 技能ID
	 * Return	: CSkill* 新加的技能指针
	 */
	CSkill* Insert(int skillid);

	/* Name		：Insert
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 添加一个技能
	 * Param	: pSkill 技能指针
	 * Return	: CSkill* 新加的技能指针
	 */
	CSkill*	Insert(CSkill* pSkill);

	/* Name		：Remove
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移除一个技能
	 * Param	: skillid 技能ID
	 * Return	: void
	 */
	void Remove(int skillid);

	/* Name		：Clear
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 清除技能列表
	 * Param	: none
	 * Return	: void
	 */
	void Clear();

	/* Name		：Get
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取技能指针
	 * Param	: skillid 技能ID
	 * Return	: CSkill*
	 */
	CSkill* Get(int skillid);

	/* Name		：IndexBy
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更加下标索引获取技能指针
	 * Param	: idx 下标
	 * Return	: CSkill*
	 */
	CSkill* IndexBy(int idx);

	/* Name		：Last
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取最后一个技能指针
	 * Param	: none
	 * Return	: CSkill*
	 */
	CSkill* Last();

	/* Name		：LastActive
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取最后一个主动攻击技能指针
	 * Param	: none
	 * Return	: CSkill*
	 */
	CSkill* LastActive();

	/* Name		：Count
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 统计技能个数
	 * Param	: none
	 * Return	: int 技能个数
	 */
	int	Count();

	/* Name		：CountActive
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 统计主动型技能个数
	 * Param	: none
	 * Return	: int 技能个数
	 */
	int		CountActive();

	/* Name		：isStudyed
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否学会了某类型技能
	 * Param	: type 技能类型
	 * Return	: true 学会，false未学会
	 */
	bool IsStudyed(int skillid);

	/* Name		：GetSkillLevel
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取技能等级
	 * Param	: skillid 技能id
	 * Return	: int 技能等级
	 */
	int GetSkillLevel(int skillid);

	/* Name		：StartCd
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 重置技能CD时间
	 * Param	: skillid 技能id
	 * Return	: void
	 */
	void StartCd(int skillId);

	/* Name		：UpdateSkill
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新所有技能的CD时间
	 * Param	: dt 时间位移
	 * Return	: void
	 */
	void UpdateSkill(float dt);

	/* Name		：GetSkillList
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取技能列表
	 * Param	: none
	 * Return	: SkillList& 技能列表引用
	 */
	inline SkillList& GetSkillList() { return m_Skills; }

	/* Name		：GetSkillList
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取技能列表
	 * Param	: val -1 帮会技能列表，其他返回非帮会技能
	 * Return	: SkillList& 技能列表引用
	 */
	void GetSkillListByFlag(int val,SkillList& lists);

private:
	SkillList m_Skills;
};



#endif //__Skill_h_
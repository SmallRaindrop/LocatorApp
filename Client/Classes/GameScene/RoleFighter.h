/***
 * 模块：RoleFighter
 * 作者：岳良友
 * 时间：2015-07-2
 * 说明：可战斗角色相关
 * 可以参与战斗，使用技能，具有战斗属性
 */

#ifndef __RoleFighter_h_
#define __RoleFighter_h_

#include "GameDef.h"
#include "role.h"
#include "RoleState.h"
#include "Map/AStar.h"
#include "GameMap.h"
#include "db.h"
#include "RoleEffect.h"
#include "StateMachine.h"
#include "Skill.h"
#include "Net/pk_role.h"
#include "Bullet.h"
#include "RoleBuff.h"

// 状态机共享数据
struct RoleFighterStateMachineData
{
	union 
	{
		struct 
		{

		}Idle;

		struct 
		{
			
		}Move;

		struct 
		{
			
		}Fight;

		struct 
		{
			
		}Ready;

		struct 
		{
			
		}Injured;

		struct 
		{
			
		}Forbiden;

		struct
		{
			float   deadRestTime;	//濒死状态剩余复活时间
			int		restPoint;		//剩余点数
			int		helpNum;		//拯救角色数目
			float	restTime;		//剩余毫秒
			int		percent;		//复活进度速度
		}Dead;
	};
};

class RoleFighter : public Role
{
public:
	RoleFighter();
	virtual ~RoleFighter();

	static inline EquipmentID	getNakedArmorID(int prof,int sex){ return 0; }
	static inline EquipmentID	getNakedWeaponID(int prof,int sex){ return 0; }
	static inline EquipmentID	getNakedWingID(int prof,int sex){ return 0; }

	static inline EquipmentID	getEquipedArmorID(int prof,int sex,int artid){ return artid; }
	static inline EquipmentID	getEquipedWeaponID(int prof,int sex,int artid){ return artid; }
	static inline EquipmentID	getEquipedWingID(int prof,int sex,int artid){ return artid; }

	virtual void update(float dt);

	virtual bool initRole();

	virtual bool isSelect(float x,float y);

	/* Name		：onSelect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素被选中回调函数
	 * Param	: param == true 被选中，否则未被选中
	 * Return	: void
	 */
	virtual void onSelect(bool param);

	inline bool IsChests(){ return GetType() == mapObjectType_Chests; }
	inline bool IsMonster(){ return GetType() == mapObjectType_Monster; }
	inline bool IsPlayer(){ return GetType() == mapObjectType_Player; }
	inline bool IsNpc(){ return GetType() == mapObjectType_Npc; }

	/* Name		：setPosition
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置元素世界坐标系位置
	 * Param	: 世界坐标x,y
	 * Return	: void
	 */
	void setPosition(float x,float y);

	/* Name		：setPosition
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置元素世界坐标系位置
	 * Param	: 世界坐标Point& position
	 * Return	: void
	 */
	void setPosition(const Point &position);

	/* Name		：isDynamicBlock
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断一个逻辑坐标点相对于自己是否是动态阻挡点
	 * Param	: cx,cy 逻辑坐标点
	 * Return	: void
	 */
	bool isDynamicBlock(int cx,int cy);

	/* Name		：EnterMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 进入指定地图
	 * Param	: pMap地图指针，cx，cy地图中的逻辑坐标
	 * Return	: void
	 */
	virtual void EnterMap(TileMap* pMap,int cx,int cy);

	/* Name		：LeaveMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 离开当前地图
	 * Param	: none
	 * Return	: void
	 */
	virtual void LeaveMap();

	/* Name		：onEnterSight
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素进入视野回调
	 * Param	: none
	 * Return	: void
	 */
	virtual void onEnterSight();

	/* Name		：onLeaveSight
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素离开视野回调
	 * Param	: none
	 * Return	: void
	 */
	virtual void onLeaveSight();

	//////////////////////////////////////////////////////////////////////////
	// 属性相关
	//////////////////////////////////////////////////////////////////////////
public:
	virtual void		SetProperty(RoleProperty idx,int val);
	virtual void		SetProperty(RoleProperty idx,__int64 val);
	virtual void		SetProperty(RoleProperty idx,const string& val);

	inline int			GetCareer(){ return GetPropertyInt(RoleProperty_Career); }
	inline int			GetSex(){ return GetPropertyInt(RoleProperty_Sex); }
	inline int			GetLevel(){ return GetPropertyInt(RoleProperty_Level); }
	inline int			GetCamp(){ return GetPropertyInt(RoleProperty_Camp); }
	inline __int64		GetHP(){ return GetPropertyInt64(RoleProperty_HP); }
	inline int			GetMP(){ return GetPropertyInt(RoleProperty_MP); }
	inline __int64		GetHPMax() { return GetPropertyInt64(RoleProperty_hp_max); }
	inline int			GetMPMax() { return GetPropertyInt(RoleProperty_mp_max); }

	virtual void		SetRoleName(const string& val);
	virtual void		SetCareer(int val);
	virtual void		SetSex(int val){ GetData()->SetProperty(RoleProperty_Sex,val); }
	virtual void		SetLevel(int val){ GetData()->SetProperty(RoleProperty_Level,val); }
	virtual void		SetCamp(int val);
	virtual void		SetHP(__int64 val);
	virtual void		SetMP(int val);
	virtual void		SetHPMax(__int64 val);
	virtual void		SetMPMax(int val);
	virtual void		SetCloth(int val){ GetData()->SetProperty(RoleProperty_Cloth,val); RefreshEquip(); }
	virtual void		SetWeapon(int val){ GetData()->SetProperty(RoleProperty_Weapon,val); RefreshEquip(); }
	virtual void		SetWing(int val){ GetData()->SetProperty(RoleProperty_Wing,val); RefreshEquip(); }

	/* Name		：SetStateFlag
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置角色状态标志位
	 * Param	: val 状态值
	 * Return	: void
	 */
	virtual void SetStateFlag(int val);

	/* Name		：AddStateFlag
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 增加指定角色状态标志位
	 * Param	: val 状态值
	 * Return	: void
	 */
	virtual void AddStateFlag(int val);

	/* Name		：ClrStateFlag
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 清除指定角色状态标志位
	 * Param	: val 状态值
	 * Return	: void
	 */
	virtual void ClrStateFlag(int val);

	/* Name		：RefreshEquip
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新角色装备外观
	 * Param	: none
	 * Return	: void
	 */
	virtual void RefreshEquip();

	/* Name		：RefreshRoleTitle
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新角色附加信息展示
	 * Param	: none
	 * Return	: void
	 */
	virtual void RefreshRoleTitle();

protected:
	class RoleTitle* m_pRoleTitle;			// 角色附加信息展示，名字，血条，称谓，成就，VIP等级等等

	//////////////////////////////////////////////////////////////////////////
	// 属性相关
	//////////////////////////////////////////////////////////////////////////

public:
	/* Name		：ShowRoleEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过效果类型来表现效果
	 * Param	: type 效果类型，val 参数数值
	 * Return	: void
	 */
	virtual void ShowRoleEffect(pk::RoleEffectInfo* pInfo);

	/* Name		：ShowDamageEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示伤害特效及音效
	 * Param	: pos 受伤位置，damage 伤害数值
	 * Return	: void
	 */
	virtual void ShowDamageEffect(Point pos,int damage);

	/* Name		：ShowCritEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示暴击特效及音效
	 * Param	: pos 受伤位置，damage 伤害数值
	 * Return	: void
	 */
	virtual void ShowCritEffect(Point pos,int damage);

	/* Name		：ShowMissEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示闪避特效及音效
	 * Param	: none
	 * Return	: void
	 */
	virtual void ShowMissEffect();

	/* Name		：ShowRecoverHP
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示回复血量效果
	 * Param	: none
	 * Return	: void
	 */
	virtual void ShowRecoverHP(int value);

	/* Name		：ShowRecoverMP
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示回复魔法效果
	 * Param	: none
	 * Return	: void
	 */
	virtual void ShowRecoverMP(int value);

	/* Name		：ShowRecoverHPByItem
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示吃血球效果
	 * Param	: none
	 * Return	: void
	 */
	virtual void ShowRecoverHPByItem(int value);

	/* Name		：ShowRecoverMPByItem
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示吃法球效果
	 * Param	: none
	 * Return	: void
	 */
	virtual void ShowRecoverMPByItem(int value);

	/* Name		：ShowMissEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示升级特效及音效
	 * Param	: none
	 * Return	: void
	 */
	virtual void ShowLevelUPEffect();

	/* Name		：ShowStageEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示角色出场特效及音效
	 * Param	: none
	 * Return	: void
	 */
	virtual void ShowStageEffect();

	/* Name		：ShowHitFly
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 击飞效果，用于角色死亡
	 * Param	: pos 打击力位置
	 * Return	: void
	 */
	virtual void ShowHitFly(const Point& pos);

// 战斗相关
public:
	/* Name		：IsForbiddenMove
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否受限制移动
	 * Param	: none
	 * Return	: true 受限制，false 不受限制
	 */
	virtual bool IsForbiddenMove();

	/* Name		：IsForbiddenAttack
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否受限制攻击
	 * Param	: none
	 * Return	: true 受限制，false 不受限制
	 */
	virtual bool IsForbiddenAttack();

	/* Name		：IsForbiddenSkill
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否受限制使用技能
	 * Param	: none
	 * Return	: true 受限制，false 不受限制
	 */
	virtual bool IsForbiddenSkill();

	/* Name		：IsEnemyTo
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否与目标敌对
	 * Param	: pFighter 目标对象
	 * Return	: true 敌对的，false 非敌对的（中立或者友好）
	 */
	virtual bool IsEnemyTo(RoleFighter* pFighter);

	/* Name		：Forward
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 冲锋
	 * Param	: cx,cy 冲锋的目标位置
	 * Return	: void
	 */
	virtual void Forward(int cx,int cy);

	/* Name		：Evade
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 逃避躲闪
	 * Param	: cx,cy 逃避的目标位置
	 * Return	: void
	 */
	virtual void Evade(int cx,int cy);

	virtual bool	IsAttacking();
	virtual bool	IsInjured();

	/* Name		：IsDead
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否真正死亡
	 * Param	: none
	 * Return	: 是返回true ，否则false
	 */
	virtual bool	IsDead();

	/* Name		：IsDeadVirtual
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否濒死状态
	 * Param	: none
	 * Return	: 是返回true ，否则false
	 */
	virtual bool	IsDeadVirtual();
	
	/* Name		：Injured
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 角色受伤处理 僵直处理
	 * Param	: none
	 * Return	: void
	 */
	virtual void Injured();

	/* Name		：Dead
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 角色死亡处理
	 * Param	: pKiller 杀人犯
	 * Return	: void
	 */
	virtual void Dead(RoleFighter* pKiller);

	/* Name		：DeadVirtual
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 角色濒死处理
	 * Param	: pKiller 杀人犯
	 * Return	: void
	 */
	virtual void DeadVirtual(RoleFighter* pKiller);

	/* Name		：Relive
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 角色复活处理
	 * Param	: pFighter 复活者，自动复活为NULL
	 * Return	: void
	 */
	virtual void Relive(RoleFighter* pFighter = nullptr);

	//////////////////////////////////////////////////////////////////////////
	// buff数据
	//////////////////////////////////////////////////////////////////////////
public:
	/* Name		：GetBuffManager
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取BUFF管理器
	 * Param	: none
	 * Return	: RoleBuffManager&
	 */
	inline RoleBuffManager&	GetBuffManager(){ return m_BuffMgr; }

	/* Name		：GetBuff
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取指定BUFF对象
	 * Param	: buffid
	 * Return	: RoleBuff*
	 */
	inline RoleBuff* GetBuff(int64 buffid){ return GetBuffManager().Get(buffid); }

	/* Name		：AddBuff
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 添加BUFF对象
	 * Param	: RoleBuff* BUFF对象
	 * Return	: void
	 */
	virtual void AddBuff(RoleBuff* pBuff);

	/* Name		：AddBuff
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 添加指定BUFF对象
	 * Param	: buffid
	 * Return	: RoleBuff*
	 */
	virtual RoleBuff* AddBuff(__int64 id,int buffid,int duration);

	/* Name		：RemoveBuff
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移除指定BUFF对象
	 * Param	: buffid
	 * Return	: void
	 */
	virtual void RemoveBuff(int64 buffid);

protected:
	RoleBuffManager m_BuffMgr;	// buff管理器

	//////////////////////////////////////////////////////////////////////////
	// ----buff数据 end----
	//////////////////////////////////////////////////////////////////////////
public:
	/* Name		：ConvertToTargetID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过逻辑坐标点获取目标ID
	 * Param	: cx,cy 目标逻辑点
	 * Return	: __int64 targetid
	 */
	inline __int64 ConvertToTargetID(int cx,int cy){__int64 ret = cx;ret = ret << 32;ret += cy;return ret;}

	/* Name		：ConvertToCell
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通过逻辑坐标点获取目标ID
	 * Param	: cx,cy 目标逻辑点
	 * Return	: __int64 targetid
	 */
	inline void ConvertToCell(__int64 targetId,int& cx,int& cy){ cy = targetId; cx = targetId >> 32; }

	/* Name		：GetCellByDir
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取面前指定距离的坐标
	 * Param	: cx,cy 目标逻辑点
	 * Return	: void
	 */
	virtual void GetCellByDir(int distance,int& cx,int& cy);

	/* Name		：FaceToTarget
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 使自己面向目标点
	 * Param	: pos 目标逻辑点 世界坐标系
	 * Return	: void
	 */
	virtual void FaceToTarget(const Point& pos);

	/* Name		：FaceToTarget
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 使自己面向目标
	 * Param	: cx,cy 目标逻辑点
	 * Return	: void
	 */
	virtual void FaceToTarget(int cx,int cy);

	/* Name		：FaceToTarget
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 使自己面向目标
	 * Param	: pTarget 目标对象
	 * Return	: void
	 */
	virtual void FaceToTarget(RoleFighter* pTarget);

	/* Name		：MagicAttack
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 使用技能，战斗技能表现
	 * Param	: pSkill 技能配置数据信息 targetid 目标对象id，int offsetX,int offsetY 目标位置偏移
	 * Return	: void
	 */
	virtual void MagicAttack(SkillCfg* pSkill,__int64 targetid,int offsetX,int offsetY);

	/* Name		：GetActiveSkill
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取当前使用的技能
	 * Param	: none
	 * Return	: pSkill 技能对象指针
	 */
	inline SkillCfg* GetActiveSkill(){ return m_pActiveSkill; }

	/* Name		：GetTargetID
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取当前目标ID
	 * Param	: none
	 * Return	: 
	 */
	inline __int64 GetTargetID(){ return m_nTargetID; }

	/* Name		：GetTargetOffsetX
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取当前目标偏移
	 * Param	: none
	 * Return	: 
	 */
	inline int GetTargetOffsetX(){ return m_nTargetOffsetX; }
	inline int GetTargetOffsetY(){ return m_nTargetOffsetY; }

	inline RoleFighterStateMachineData& GetStateMachineData(){ return m_StateMachineData; }

	virtual float	GetDeadVirtualDeadRestTime();
	virtual int		GetDeadVirtualRestPoint();
	virtual int		GetDeadVirtualHelpNum();
	virtual float	GetDeadVirtualRestTime();
	virtual int		GetDeadVirtualPercent();

	virtual void SetDeadVirtualPercent();
	virtual void SetDeadVirtualDeadRestTime(float timer);
	virtual void SetDeadVirtualRestPoint(int restPoint);
	virtual void SetDeadVirtualHelpNum(int helpnum);
	virtual void SetDeadVirtualRestTime(float restTime);

protected:
	SkillCfg*		m_pActiveSkill;		// 目前正在使用的技能		
	__int64			m_nTargetID;		// 技能目标ID
	int				m_nTargetOffsetX;	// 目标偏移
	int				m_nTargetOffsetY;	// 目标偏移		
	RoleFighterStateMachineData m_StateMachineData;
};

#endif //__IRole_h_
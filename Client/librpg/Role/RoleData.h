#ifndef __RoleData_h_
#define __RoleData_h_

#include "RoleStatus.h"

// 角色职业定义
enum RoleCareer
{
	RoleCareer_None = 0,        //无职业
	RoleCareer_DunWei = 1,      //盾卫
	RoleCareer_QiangShen,       //枪神
	RoleCareer_JianXian,        //剑仙
	RoleCareer_JiGuanShi,       //机关师
	RoleCareer_Max,				//最大限制
};

// 角色阵营关系
enum RoleCamp
{
	RoleCamp_None,
	RoleCamp_Player,
	RoleCamp_Red,
	RoleCamp_Blue,
};

enum RoleProperty
{
	//////////////////////////////////////////////////////////////////////////
	// 以下是战斗属性
	//////////////////////////////////////////////////////////////////////////
	RoleProperty_None,
	RoleProperty_phy_dam,    //物理伤害
	RoleProperty_fire_dam,    //火伤害
	RoleProperty_cold_dam,    //冰伤害
	RoleProperty_elec_dam,    //电伤害
	RoleProperty_toxin_dam,    //毒伤害
	RoleProperty_base_dam_increase,    //基础伤害增强
	RoleProperty_all_dam_increase,    //造成伤害系数
	RoleProperty_all_dam_reduce,    //受到伤害系数
	RoleProperty_atk_power,    //攻击强度
	RoleProperty_hp_max,    //最大生命值
	RoleProperty_hp_r,    //生命秒回值
	RoleProperty_hp_rp,    //生命秒回比
	RoleProperty_by_cure_factor,    //受到治疗系数
	RoleProperty_mp_max,    //最大法力值
	RoleProperty_mp_r,    //法力秒回值
	RoleProperty_speed,    //移动速度
	RoleProperty_armor,    //护甲
	RoleProperty_phy_res,    //物理抗性
	RoleProperty_fire_res,    //火抗性
	RoleProperty_cold_res,    //冰抗性
	RoleProperty_elec_res,    //电抗性
	RoleProperty_toxin_res,    //毒抗性
	RoleProperty_tough,    //坚韧
	RoleProperty_penetrate,    //穿深
	RoleProperty_thickness,    //厚度
	RoleProperty_crit,    //暴击率
	RoleProperty_crit_dam_factor,    //暴击伤害系数
	RoleProperty_accurate,    //精准率
	RoleProperty_dodge,    //躲闪率
	RoleProperty_trigger,    //触发率
	RoleProperty_atk_speed_increase,    //攻击加速
	RoleProperty_mp_efficiency,    //节约法力
	RoleProperty_skill_duration,    //技能持久
	RoleProperty_skill_power,    //技能强度
	RoleProperty_skill_range,    //技能范围
	RoleProperty_hp_ball,    //血球回血量
	RoleProperty_mp_ball,    //法球回法力量
	RoleProperty_armor_reduce,    //护甲削弱
	RoleProperty_Fight_Max,						// 战斗属性最大值
	//////////////////////////////////////////////////////////////////////////
	// 以下是基本属性
	//////////////////////////////////////////////////////////////////////////
	RoleProperty_Name = 1000,	// 角色名字
	RoleProperty_Career,		// 职业
	RoleProperty_Sex,			// 性别
	RoleProperty_Level,			//
	RoleProperty_Lucky,			// 幸运值
	RoleProperty_Camp,			// 阵营
	RoleProperty_Weapon,               //%外观 武器装备
	RoleProperty_Cloth,                //%外观 衣服 
	RoleProperty_Wing,                 //%外观 翅膀
	RoleProperty_HP,                   //%当前血量
	RoleProperty_MP,                   //%当前魔法值
	RoleProperty_Exp,                  //%经验
	RoleProperty_Coin,                //%金币
	RoleProperty_Coin_b,              //%金币绑定
	RoleProperty_Treasure,            //%元宝
	RoleProperty_Treasure_b,          //%元宝绑定
	RoleProperty_GuildID,			   //%公会ID
	RoleProperty_StateFlag,			   //%状态值
	RoleProperty_Reputation,			// 声望	
	RoleProperty_VipLevel,				// VIP等级
	RoleProperty_FightValue,			// 战斗力
	RoleProperty_Achievement,			// 成就
	RoleProperty_ManufactureSize,       // 玩家生产线大小
	RoleProperty_RecoverCount,			// 已经免费复活次数 0 1 2
	/************************************************/

	RoleProperty_Max// 加在这个前面！！！
};

class RoleData
{
public:
	RoleData();
	virtual ~RoleData(){}

	inline string&	GetName(){ return name; }
	inline int		GetSpeed(){ return speed; }
	inline int		GetStateFlag(){ return stateFlag; }
	inline int		GetRecoverCount(){return m_recoverCount;}
	inline void		SetName(const string& val){ name = val; }
	inline void		SetSpeed(int val){ speed = val; }
	inline void		SetStateFlag(RoleStatus val){ stateFlag = val; }
	inline bool		HasStateFlag(RoleStatus val){ return (stateFlag & (1<<val)) != 0; }
	inline void		AddStateFlag(RoleStatus val){ stateFlag |= (1<<val); }
	inline void		ClrStateFlag(RoleStatus val){ stateFlag &= ~(1<<val); }

	virtual void SetProperty(RoleProperty idx,__int64 val);
	virtual void SetProperty(RoleProperty idx,int val);
	virtual void SetProperty(RoleProperty idx,const string& val);

	virtual void GetProperty(RoleProperty idx,__int64& val);
	virtual void GetProperty(RoleProperty idx,int& val);
	virtual void GetProperty(RoleProperty idx,string& val);

protected:
	string	name;			// 名字
	int		speed;			// 移动速度
	int		stateFlag;		// 状态标志
	int		career;			// 职业
	int		sex;			// 性别
	int		level;			// 等级
	int		weapon;			// 武器外观
	int		cloth;			// 衣服外观
	int		wing;			// 翅膀外观
	int		m_recoverCount;			// 已经免费复活次数 0 1 2
	int		m_lastRecoverTime;		// 上次复活时间
};

class RoleFighterData : public RoleData
{
public:
	RoleFighterData();
	virtual ~RoleFighterData();

	virtual void SetProperty(RoleProperty idx,__int64 val);
	virtual void SetProperty(RoleProperty idx,int val);
	virtual void SetProperty(RoleProperty idx,const string& val);

	virtual void GetProperty(RoleProperty idx,__int64& val);
	virtual void GetProperty(RoleProperty idx,int& val);
	virtual void GetProperty(RoleProperty idx,string& val);

protected:
	__int64		hp;			// 当前血量
	int			mp;			// 当前魔法量
	int			camp;		// 阵营
	int			fightValue;		// 战斗力
	__int64		fight_array[RoleProperty_Fight_Max];	// 战斗属性列表
};

class NpcData : public RoleData
{
public:
	void SetProperty(RoleProperty idx,__int64 val);
	void SetProperty(RoleProperty idx,int val);
	void SetProperty(RoleProperty idx,const string& val);

	void GetProperty(RoleProperty idx,__int64& val);
	void GetProperty(RoleProperty idx,int& val);
	void GetProperty(RoleProperty idx,string& val);
};

class MonsterData : public RoleFighterData
{
public:
	MonsterData(){}
	~MonsterData(){}

	virtual void SetProperty(RoleProperty idx,__int64 val);
	virtual void SetProperty(RoleProperty idx,int val);
	virtual void SetProperty(RoleProperty idx,const string& val);

	virtual void GetProperty(RoleProperty idx,__int64& val);
	virtual void GetProperty(RoleProperty idx,int& val);
	virtual void GetProperty(RoleProperty idx,string& val);
};

class PetData : public RoleFighterData
{
public:
	PetData(){}
	~PetData(){}

	virtual void SetProperty(RoleProperty idx,__int64 val);
	virtual void SetProperty(RoleProperty idx,int val);
	virtual void SetProperty(RoleProperty idx,const string& val);

	virtual void GetProperty(RoleProperty idx,__int64& val);
	virtual void GetProperty(RoleProperty idx,int& val);
	virtual void GetProperty(RoleProperty idx,string& val);
};

class PlayerData : public RoleFighterData
{
public:
	PlayerData() : vipLevel(0),guildID(0){}
	virtual ~PlayerData(){}

	void SetProperty(RoleProperty idx,__int64 val);
	void SetProperty(RoleProperty idx,int val);
	void SetProperty(RoleProperty idx,const string& val);

	void GetProperty(RoleProperty idx,__int64& val);
	void GetProperty(RoleProperty idx,int& val);
	void GetProperty(RoleProperty idx,string& val);

protected:
	int			vipLevel;			// VIP等级
	int			achievement;		// 成就
	__int64		guildID;			// 公会ID
};

class HeroData : public PlayerData
{
public:
	HeroData() : lucky(0),exp(0),money(0),money_b(0),gold(0),gold_b(0),reputation(0){}
	~HeroData(){}

 	void SetProperty(RoleProperty idx,__int64 val);
 	void SetProperty(RoleProperty idx,int val);
 	void SetProperty(RoleProperty idx,const string& val);
 
 	void GetProperty(RoleProperty idx,__int64& val);
 	void GetProperty(RoleProperty idx,int& val);
 	void GetProperty(RoleProperty idx,string& val);

private:
	int			lucky;			// 幸运
	__int64		exp;			// 经验
	__int64	    money;			// 金币
	__int64		money_b;		// 绑定金币
	int			gold;			// 元宝 
	int			gold_b;			// 绑定元宝
	int			reputation;		// 声望
	int16       manufactureSize;// 生产线上限
};

#endif //__RoleData_h_
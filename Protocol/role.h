// -> client to server
// <- server to client
// <-> client & serverGS2C_PlayerProperty


// 玩家单个属性改变消息
struct GS2C_PlayerSingleProperty  <-
{
	int16	type;		//属性对应的是哪个属性
	int64	value;		//对应属性的值
};


// 玩家单个属性改变消息
struct GS2C_PlayerSinglePropertyStr  <-
{
	int16	type;		//属性对应的是哪个属性
	string	value;		//对应属性的值
};

// 玩家单个属性改变广播消息 value is number
struct GS2C_PlayerSinglePropertySync  <-
{
	int64	playerID;	//玩家ID
	int16	type;		//属性对应的是哪个属性
	int64	value;		//对应属性的值
};



// 玩家单个属性改变广播消息 value is string, eg:玩家帮会名字
struct GS2C_PlayerSinglePropertyStrSync  <-
{
	int64	playerID;	//玩家ID
	int16	type;
	string	value;		//对应属性的值
};

struct PlayerProperty
{
	int16 type;
	int64	value;		//对应属性的值
};
// 玩家多个属性改变广播消息 value is number
struct GS2C_PlayerMultiplePropertySync  <-
{
	int64	playerID;	//玩家ID
	vector<PlayerProperty> playerProperties;		// 玩家多个属性
};


// 道具使用的cd时间
struct GS2C_CdUseItem <-
{
	int32	id; //物品种类
	int64	remainTime; //cd剩余时间
};

// BUFF信息
struct PlayerBuffInfo
{
	int64   id;      //唯一id
	int32	buffDataId;  //配置id
	int32	duration; //单位：毫秒

	//int8    acc;  //叠加重数
	//int32   power; //
	//int32   powerpercent;//千分数
};


// 技能信息
struct PlayerSkillInfo
{
	int16	skillId; //技能ID
	int16   level;   //技能等级
	int16	cdtime; //cd时间 此次cd还有多久，用于保存玩家下线后的cd时间
};

//请求进入游戏，返回玩家角色的属性信息
struct GS2C_PlayerProperty  <-
{
	// 基本属性
	int64	playerID;
	string	name;
	int32	level;
	int8	career;
	int64	exp;
	int64	bindCoin;		//绑定金币,金币默认不可以
	int32	treasure;		//元宝
	int32	bindTreasure;	//绑定元宝
	int32	fight;			//战斗力
	vector<GS2C_CdUseItem> cdTimeUseItem; //使用物品的cd时间列表
	int8	bagGridNum;		//背包容量
	int8    vipLevel; 		//vip等级
	int32   totalTreasure; 	// 累计充值金额
	int16   titleId; 		//玩家的称号ID
	int64   hp;             //当前血量
	int32   mp;             //当前魔法值
	int8    recoverCount;//免费复活次数
	int16   manufactureSize; //玩家生产线上限
	// 战斗属性
	vector<PlayerBuffInfo> buff_list;
	vector<PlayerSkillInfo> skill_list;
	int32	state;					//状态值
	int32	pk;						//pk值
	int8	pkState;				//pk模式
	
	int32 phy_dam;               //物理伤害 
    int32 fire_dam;              //火伤害 
	int32 code_dam;              //冰伤害
    int32 elec_dam;              //电伤	
	int32 toxin_dam;             //毒伤害
	int16 base_dam_increase;     //基础伤害增强
	int32 all_dam_increase;      //造成伤害
	int32 all_dam_reduce;        //受到伤害系数
	int32 atk_power;             //攻击强度 
	int64 hp_max;				 //最大血量
	int32 hp_r;                  //生命秒回值 
	int32 hp_rp;                 //每秒回复最大生命
	int32 by_cure_factor;        //受到治疗系数
	int32 mp_max;				 //最大法力值
	int32 mp_r;                  //法力秒回值
	int16 speed;                 //移动速度
	int32 armor;                 //护甲
	int16 phy_res;               //物理抗性
	int16 fire_res;              //火抗性
	int16 cold_res;              //冰抗性
	int16 elec_res;              //电抗性
	int16 toxin_res;             //毒抗性
	int16 tough;                 //坚韧
	int16 penetrate;             //穿深
	int16 thickness;             //厚度
	int32 crit_p;                //爆击率
	int32 crit_hurt;             //爆击伤害
	int32 accurate_p;            //精准率
	int32 dodge_p;               //躲闪率 
	int32 trigger_p;             //触发率
	int16 atk_speed_increase;    //攻击加速
	int16 mp_efficiency;         //节约法力
	int16 skill_duration;        //技能持久
	int32 skill_power;           //技能强度
	int16 skill_rang;            //技能范围
	int32 hp_ball;               //生命之球
	int32 mp_ball;               //法力之球恢复
	int16 armor_reduce;          //护甲削弱
};

//角色战斗属性
struct GS2C_PlayerFightProperty  <-
{
	int32	state;				 //状态值
	int64   hp;                  //当前血量
	int32   mp;                  //当前魔法值

	int32 phy_dam;               //物理伤害 
    int32 fire_dam;              //火伤害 
	int32 code_dam;              //冰伤害
    int32 elec_dam;              //电伤	
	int32 toxin_dam;             //毒伤害
	int16 base_dam_increase;     //基础伤害增强
	int32 all_dam_increase;      //造成伤害
	int32 all_dam_reduce;        //受到伤害系数
	int32 atk_power;             //攻击强度 
	int64 hp_max;				 //最大血量
	int32 hp_r;                  //生命秒回值 
	int32 hp_rp;                 //每秒回复最大生命
	int32 by_cure_factor;        //受到治疗系数
	int32 mp_max;				 //最大法力值
	int32 mp_r;                  //法力秒回值
	int16 speed;                 //移动速度
	int32 armor;                 //护甲
	int16 phy_res;               //物理抗性
	int16 fire_res;              //火抗性
	int16 cold_res;              //冰抗性
	int16 elec_res;              //电抗性
	int16 toxin_res;             //毒抗性
	int16 tough;                 //坚韧
	int16 penetrate;             //穿深
	int16 thickness;             //厚度
	int32 crit_p;                //爆击率
	int32 crit_hurt;             //爆击伤害
	int32 accurate_p;            //精准率
	int32 dodge_p;               //躲闪率 
	int32 trigger_p;             //触发率
	int16 atk_speed_increase;    //攻击加速
	int16 mp_efficiency;         //节约法力
	int16 skill_duration;        //技能持久
	int32 skill_power;           //技能强度
	int16 skill_rang;            //技能范围
	int32 hp_ball;               //生命之球
	int32 mp_ball;               //法力之球恢复
	int16 armor_reduce;          //护甲削弱
};


// 增加技能
struct GS2U_AddSkillList <-
{
	vector<PlayerSkillInfo> skill_list;//客户端据技能配置表来区分是主动技能，还是被动技能
};
//删除技能
struct GS2U_RemoveSkillList <-
{
	vector<int16> skill_id_list;//技能ID 客户端据技能配置表来区分是主动技能，还是被动技能
};
//等级改变的技能列表
struct GS2U_LevelChangeSkillList <-
{
	vector<PlayerSkillInfo> skill_list;//客户端据技能配置表来区分是主动技能，还是被动技能
};

// 玩家使用技能
struct C2GS_UseSkill ->
{
	int16	skillId;		// 技能ID
	int16   selfPosX;       // 自己的x坐标
	int16   selfPosY;		// 自己的y坐标
	int16   offsetX;		// 偏移的x坐标 客户端表现用
	int16   offsetY;		// 偏移的y坐标 客户端表现用
	int64	targetId;		// 目标ID，可以是逻辑点，也可以是角色ID
};

// 玩家使用技能广播
struct GS2U_UseSkill <-
{
	int64	casterId;			// 施法者
	int16   offsetX;			// 偏移的x坐标 客户端表现用
	int16   offsetY;			// 偏移的y坐标 客户端表现用
	int64	targetId;			// 目标ID，可以是逻辑点，也可以是角色ID
	int16	skillId;			// 技能ID 
};
// 玩家使用带瞬移的技能广播
struct GS2U_UseTransferSkill <-
{
	int64	casterId;			// 施法者
	int64	targetId;			// 目标
	int16	skillId;			// 技能ID 
	int16   transferDesX;       // 瞬移的目标点的x坐标,
	int16   transferDesY;       // 瞬移的目标点的y坐标, 
};

	





//通知client，战士下一次攻击为攻杀
struct  GS2C_NextAttack_Is_GongSha <-
{
	int8 reserve;//不使用
}

struct RoleEffectInfo
{
	int64   castId;             //施放者id
	int64	targetId;           //目标id
	int32   skillDataId;        //技能配置id 如果造成些效果的是buff,则填写0
	int32	effectType;			// 效果 
	int64	data;				// 击退效果中要保存目标的位置，改为64位
};



// 角色效果
struct GS2U_RoleEffect <-
{
	vector<RoleEffectInfo>		effects;
};


// 复活
struct C2GS_RecoverLife_Req ->
{
	int16 recoverRuleId; 
};

struct GS2C_RecoverLife_Ret <-
{
	int16 retCode;
	int8 recoverCount;
};

// 队友拯救复活
struct C2GS_HelpRecover_Req ->
{
	int64 playerID;
	int8 state;//0：开始，1：停止
};

struct GS2C_HelpRecover_Ret <-
{
	int8 state;//为-1时表示打断,0为成功,1进行中
	int64 playerID;
	int16 restTime;//剩余毫秒
	int16 restPoint;//剩余点数（最大10000点）
	int8 helpNum;//拯救角色数目
};


// 玩家增加BUFF,或替换BUFF
struct GS2U_BufferAttach <-
{
	int64   id;      //唯一id
	int32	buffDataId;  //配置id
	int32	duration; //单位：毫秒
	//int8    acc;  //叠加重数
	//int32   power; //
	//int32   powerpercent;//千分数
};

struct GS2U_BufferRemove <-
{
	int64   id;      //buff唯一id
};

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// 踢玩家下线
struct GS2C_KickOut <-
{
	int32	type;
	string	desc;
};





//玩家切换模式
//模式对应的ID：0：和平模式；2：全体模式；1：帮会模式
struct C2GS_ChangePkState ->
{
	int64	playerID;			// 玩家ID
	int8	pkState;			// 切换成的pk模式
};

// 小退，返回选择角色界面
struct C2GS_ReturnToSelectRoleDlg_Req ->
{
}




//广播使用野蛮突斩的效果
//struct  GS2C_Use_SavageSuddenCut_Effect <-
//{
//}
// pet使用技能
struct C2GS_PetUseSkill ->
{
	int64	petID;
	int16	skillId;		// 技能ID
	int16   selfPosX;       // 自己的x坐标
	int16   selfPosY;		// 自己的y坐标
	int16   offsetX;		// 偏移的x坐标 客户端表现用
	int16   offsetY;		// 偏移的y坐标 客户端表现用
	int64	targetId;		// 目标ID，可以是逻辑点，也可以是角色ID
};




struct skill_shortcut_config
{
	int8 type; //0:itemId,1:skillId
	int8 index;
	int64 id;
};

struct C2GS_SkillShortCutConfig ->
{
	vector<skill_shortcut_config> vec;
};

struct GS2C_SkillShortCutConfig <-
{
	vector<skill_shortcut_config> vec;
};



// wing
struct GS2C_WingInfo<-
{
	vector<int32> wingIdVec;
	int32 equipWingId;
};

// 招唤wing
struct C2GS_SummonWing ->
{
	int32	wingId;
};
// 招唤成功时，通知client添加swing
// 如失败会通过配置的文本通知client
struct GS2C_AddWing <-
{
	int32	wingId;
};

struct C2GS_EquipWing ->
{
	int32	wingId;
};
struct C2GS_UnEquipWing ->
{
	int32	wingId;
};

// upgrade wing
struct C2GS_UpgradeWing ->
{
	int32 wingId;
};
//用新的wing替换老的wing
struct GS2C_ReplaceWing <-
{
	int32 oldWingId;
	int32 newWingId;
};

// 玩家战斗力属性改变消息
struct GS2C_PlayerFightingCapacityChange  <-
{
	int8	eventId;	//属性对应的是哪个属性
	int32	value;		//对应属性的值
};

//-----------------------战舰系统——begin---------------------------
struct hallTech
{
	int16 id;
	int8 lv;
	int32 nextLvTime;//升到下级的时间戳，0表示不是升级状态
};

struct GS2C_HallTechOpenList <-
{
	vector<hallTech> openList;
};

struct C2GS_HallTechLvUp_Req ->
{
	int16 id;
};

struct GS2C_HallTechLvUp_Ret <-
{
	int8 retCode;//-1:升级中，-2，已经最大等级，-3，条件不足，-4金钱不足，-5材料不足，0: 成功  
	int16 id;
	int32 nextLvTime;
};

struct GS2C_HallTechLvUp <-
{
	int16 id;
	int8 lv;
};
//-----------------------战舰系统——over---------------------------





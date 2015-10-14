

struct EquipTianshuDetail
{
	int8	solt;			// 天书部位（0-8,0为特殊位置）
	int32	tianShuDataId;	// 天书data_id
	int32	tianShuLv;		// 天书等级
}
//天书信息
struct EquipTianshu
{
	int8 index;//配置号（1-3）
	vector<EquipTianshuDetail> tianShuList;	// 天书
}

struct TianshuSoltStreng
{
	int8	solt;
	int8	strengLv;
}

//装备的基本数据
struct EquipItem
{
	int8	part;			// 装备部位 
	int64	id;				// 
	int8	isBind;			//
	int32	equipDataId;	// 装备的配置id
	int8  refineLevel;         // 精炼等级
	int8  enhanceLevel;        //进阶等级
	int32   score;  //装备评分
	vector<EquipTianshu> tianShuList;	// 天书
	int8 content_lv;//容量等级
	vector<TianshuSoltStreng> soltStrengList;	// 天书位置强化信息
	int8 tian_shu_use_index;//天书使用配置套
};

//获取玩家的装备信息
struct GS2C_EquipGetItem_Ret<-
{
	vector<EquipItem> equipItems;
}

//装备 穿上装备
struct C2GS_EquipItem->
{
	int16 index;	//道具在背包中的index
	int8 part;		//装备到的部位
}

//脱下
struct C2GS_UnequipItem->
{
	int8 part;//装备到的部位
}

//穿上 or 脱下的事件，本玩家收到后修改装备和背包里的数据
struct GS2C_EquipExchangeRet<-
{
	int8	isEquip;	//1:穿上装备 0:脱下;
	int8	part;		//装备到的部位 or 脱下的部位
	int16	index;		//要装备在背包中的index，or 脱下装备后，放到背包的哪一格里
}

struct C2GS_BagGetItems->
{
	int8 bagType;//1:装备背包  2:杂物背包 3: 材料背包 4:图纸背包
};

struct TianShuSet
{
	int64 id;				//道具的唯一id
	int64 type;//装备类型，0神器，1装备,其他为宠物id
	int8 index;//配置号（1-3）
}

struct BagItem
{
	int16 index;			//背包中的格子位置，从0开始
	int64 id;				//道具的唯一id
	int32 itemDataId;		//道具的配置id
	int16 count;			//对应格子里的道具数量改变为此值
	int8 isBind;			//0表示不绑定，1表示绑定
	int8 strengthenLevel;	//强化等级
	int8  refineLevel;      // 精炼等级
	int8  enhanceLevel;     //进阶等级
	int32   score;  //装备评分
	vector<EquipTianshu> tianShuList;	// 天书
	int8 content_lv;//容量等级
	vector<TianshuSoltStreng> soltStrengList;	// 天书位置强化信息
	int16 tian_shu_exp;
	vector<TianShuSet> tian_shu_set_list;
};

//获取背包中道具的信息
struct GS2C_BagGetItems_Ret<-
{
	int8	bagType;		//1:装备背包  2:杂物背包 3: 材料背包 4:图纸背包
	int16	bagGridNum;		//背包激活数量
	vector<BagItem> getBagItems;
};

//背包中,增加道具
struct GS2C_BagAddItem<-
{
	int8 bagType;//1:装备背包  2:杂物背包 3: 材料背包 4:图纸背包
	int8 reason;
	BagItem addItem;
};
//背包中,某个格子里的道具数量发生变化
struct GS2C_ItemCntChange<-
{
	int8  bagType;//1:装备背包  2:杂物背包 3: 材料背包
	int16 index;//背包中的格子位置，从0开始
	int16  newCount;
	int16  oldCount;
};

//背包中,删除道具
struct GSWithC_BagDeleteItems<->
{
	int8 bagType;//1:装备背包  2:杂物背包 3: 材料背包 4:图纸背包
	vector<int16> indexs;//背包中的格子位置，从0开始
};


struct GSWithC_ExchangeBagItem <->
{
	int8 bagType;//1:装备背包  2:杂物背包 3: 材料背包 4:图纸背包
	int8 index1;
	int8 index2;
}

//整理背包
struct C2GS_BagSort ->
{
	int8 bagType;//1:装备背包  2:杂物背包 3: 材料背包 4:图纸背包
};

struct GS2C_SignalItemInfo <-
{
	int64 id;				//道具的唯一id
	int32 itemDataId;		//道具的配置id
	int16 count;			//对应格子里的道具数量改变为此值
	int8 isBind;			//0表示不绑定，1表示绑定
	int8  refineLevel;         // 精炼等级
	int8  enhanceLevel;        //进阶等级
	int32 score; //装备评分
};

struct Mail_Info
{
	int64 mailId;
	int32 mailSendTime;
	int32 mailReadState; //0未读 1已读 2已领取
	int8  mailType;
	string mailSendName;
	string mailTitle;
	string mailContent;
	int32 money;
	vector<GS2C_SignalItemInfo> vec;
};

struct GS2C_All_Mail_Info <-
{
	vector<Mail_Info> vec;
};

struct GS2C_Send_Mail <-
{
	Mail_Info st;
};

// GS通知客户端聊天消息
struct GS2C_Chat <-
{
	int8	channelId;  //频道, (如：ChannelType_World)
	int8    isVip;      //发送者是否是vip, 1:是vip用户, 0:不是vip用户
	int64	senderId;   //发送者id
	string	senderName; //发送者名字
	string	message;    //消息
	vector<GS2C_SignalItemInfo> vec; //物品链接信息
};

struct C2GS_LookOverPlayerEquip ->
{
	int64 playerId;
};

struct GS2C_LookOverPlayerEquip_Result <-
{
	int8 retCode;
	int64	playerId;
	string	playerName;
	string	leagueName;
	int16	level;
	int8	career;
	int8	sex;
	int32 	weapon;
	int32	armor;
	int32	wing;
	vector<EquipItem> equipItems;
};

struct EquipId
{
	int64 equipId;
	int32 cnt;
};







// 选择第几张卡牌(翻卡牌)
struct C2GS_SelectEquipCompose ->
{
	int8 equipComposeOrder; //获取第几次融合的结果
};

struct GS2C_SelectEquipCompose <-
{
	int8 retCode; //1:成功, -1:钻石不够，失败
};

// 确认第几张卡牌(选择第几次融合的结果)
struct C2GS_ConfirmEquipComposeOrder ->
{
	int8 equipComposeOrder;
};




struct C2GS_UseItem ->
{
	int8 bagType;
	int32 index;
	int64 itemId;
};

struct GS2C_UseItem_Result <-
{
	int8 retCode; //1:成功，-1失败
};

struct C2GS_StartEquipStrengthen ->
{
	int64 equipId;
	int8  isUseLuckyStone; //是否使用幸运符
	int8  isAutoBuyLuckyStone; //是否自动购买幸运符
	int8  isAutoBuyStrengthenStone; //是否自动购买强化石
	int8  isTenStrengthen; // 是否一键10次强化（1为是，0为否）
};

struct GS2C_StartEquipStrengthen <-
{
	int8 retCode; //1:成功
};

struct GS2C_EquipLevelChange <-
{
	int64 id;
	int32 level;
	int32 score;
};

struct GS2C_DesPlayer_LockTrade_Result <-
{
	int32 coin;
	vector<GS2C_SignalItemInfo> vec;
};

struct GS2C_InputItem_Result <-
{
	int32 coin;
	vector<GS2C_SignalItemInfo> vec;
};

struct C2GS_SetBagGrid ->
{
	int8 bagType;
};

struct GS2C_SetBagGrid <-
{
	int8 bagType;
	int32 newNum;
	int8 retCode; //-1: 格子已经达到最大值, -2:配制错误, -3:金钱不足, 1:成功
};

struct C2GS_SplitItem ->
{
	int8 bagType;  //背包类型
	int32 itemCnt; //待拆分物品的数量
	int64 itemId;  //待拆分物品
	int32 splitItemCnt; //拆分成新物品的数量
};

struct GS2C_SplitItem <-
{
	int8 retCode; //-1: 物品不存在, -2:数量大于2才能拆分, -3:拆分数量必须小于物品当前数量, -4:背包已满, 1:成功
};

// -define(TipType_Personal, 1). %%个人
// -define(TipType_World, 2). %%世界
// -define(TipType_Guild, 3). %%公会
// -define(TipType_Team, 4). %%队伍
// -define(TipType_Map, 5). %%同一张地图
// GS通知客户端系统消息
struct GS2C_Tip_Msg <-
{
	int32   tipId; //
	string	args;//以逗号为分隔符分离出多个string
	vector<GS2C_SignalItemInfo> vec;
};

struct C2GS_DropItem ->
{
	int8 bagType;
	int32 index;
	int64 itemId;
};

struct GS2C_Sale_PutOnItem_Result <-
{
	int8 retCode; //1:成功, -1: 物品错误, -2:未找到寄售的npc, -3:npc距离太远, -4:寄售已经达到上限, -5:自已寄售物品已经达到上限
	int64 saleId;
	GS2C_SignalItemInfo saleItem;
};

struct sale_filter_item
{
	int32 price;
	int64 saleId;
	GS2C_SignalItemInfo saleItem;
};

struct GS2C_Sale_Filter_Item_Result <-
{
	int8 isNextPage;
	int32 totalPage;
	vector<sale_filter_item> saleVec;
};

struct GS2C_Sale_Find_Item_Result <-
{
	int8 isNextPage;
	int32 totalPage;
	vector<sale_filter_item> saleVec;
};

struct my_sale_item
{
	int32 price;
	int32 remainTime;
	int64 saleId;
	GS2C_SignalItemInfo saleItem;
};

struct my_sale_gold
{
	int32 price;
	int32 remainTime;
	int64 saleId;
	int32 goldType;
};

//我的寄售
struct GS2C_Sale_My_Sale_Item <-
{
	vector<my_sale_item> mySaleVec;
};

struct GS2C_Sale_My_Sale_Gold <-
{
	vector<my_sale_gold> mySaleVec;
};

struct GS2C_SubmitTaskChain <-
{
	//1:成功, -1:npc不存在, -2:此任务未接取, -3:玩家等级不足, -4:与npc距离太远, -5:背包已满
	int8  retCode;
	int16 taskChainCnt; //链数(第几链, 从1开始)
	int16 loopCnt; //环数(一任务链包括200环任务, 从1开始)
	int32 startNpcDataId;
	int32 endNpcDataId;
	int32 taskId;
	int32 exp;
	int32 coin;
	int32 bindCoin;
	int32 honor;
	vector<GS2C_SignalItemInfo> awardItem; //固定奖励
	vector<GS2C_SignalItemInfo> awardRandItem; //随机奖励
};

struct taskChainProgress
{
	int8 targetType; //目标类型
	int32 targetCnt; //配制文件中需要完成的数量
	int32 curCnt; //当前完成的数量
};

//上线时下发的已经接取的任务(任务链)
struct GS2C_AcceptedTaskChain <-
{
	int32 taskId; //任务id
	int32 startNpcDataId;
	int32 endNpcDataId;	
	int16 taskChainCnt; //链数(第几链, 从1开始)
	int16 loopCnt; //环数(一任务链包括200环任务, 从1开始)	
	vector<taskChainProgress> progress;
	int32 exp;
	int32 coin;
	int32 bindCoin;
	int32 honor;
	vector<GS2C_SignalItemInfo> awardItem; //固定奖励
	vector<GS2C_SignalItemInfo> awardRandItem; //随机奖励	
};

//天书镶嵌
struct C2GS_TianShuSet_Req ->
{
	int8 index;//配置号（1-3）
	int64 type;//装备类型，0神器，1装备,其他为宠物id
	int8 solt;//天书镶嵌位置（0-8,0为特殊位置）
	int16 bag_index;//天书背包位置
};

struct GS2C_TianShuSet_Ret <-
{
	int8 retCode; //-1: 系统错误, 1:成功
	int64 type;//装备类型，0神器，1装备,其他为宠物id
	vector<EquipTianshu> tianShuList;	// 天书
	BagItem newTianShu;
};

//天书更新
struct GS2C_TianShuUpate <-
{
	BagItem newTianShu;
};

//装备天书信息变化更新
struct GS2C_EquipTianShuUpate <-
{
	EquipItem newEquip;
};

//取下天书
struct C2GS_TianShuTakeOff_Req ->
{
	int8 index;//配置号（1-3）
	int64 type;//装备类型，0神器，1装备,其他为宠物id
	int8 solt;//天书位置
};

struct GS2C_TianShuTakeOff_Ret <-
{
	int8 retCode; //-1: 超重不能取下, 1:成功
	int64 type;//装备类型，0神器，1装备,其他为宠物id
	vector<EquipTianshu> tianShuList;	// 天书
};

struct tian_shu_material
{
	int16 index;//天书背包位置
	int16 count;//天书数量
};

//天书升级
struct C2GS_TianShuLvUp_Req ->
{
	int16 index;//升级天书背包位置
	vector<tian_shu_material> materialList;//材料天书背包位置
};

struct GS2C_TianShuLvUp_Ret <-
{
	int8 retCode; //-1: 材料数量不足,-2:已经是最大等级,-3:金钱不足 1:成功
	int8 newLv;
	int16 newExp;
};

//天书合成
struct C2GS_TianShuCompose_Req ->
{
	vector<tian_shu_material> materialList;//材料天书背包位置
};

struct GS2C_TianShuCompose_Ret <-
{
	int8 retCode; //-1: 金钱不足, 1:成功
	int16 itemDataId;
};

//装备天书容量强化
struct C2GS_TianShuEquipContentLvUp_Req ->
{
	int64 type;//装备类型，0神器，1装备,其他为宠物id
};

struct GS2C_TianShuEquipContentLvUp_Ret <-
{
	int8 retCode; //-2: 金钱不足，-1材料不足，1:成功
	int64 type;//装备类型，0神器，1装备,其他为宠物id
};

//装备天书孔位强化
struct C2GS_TianShuEquipSoltLvUp_Req ->
{
	int64 type;//装备类型，0神器，1装备,其他为宠物id
	int8 solt;//天书位置（0-8,0为特殊位置）
};

struct GS2C_TianShuEquipSoltLvUp_Ret <-
{
	int8 retCode; //-2: 金钱不足，-1材料不足，1:成功
	int64 type;//装备类型，0神器，1装备,其他为宠物id
	int8 solt;//天书位置（0-8,0为特殊位置）
};

//天书切换页面
struct GS2C_TianShuChangeIndex_Req ->
{
	int64 type;//装备类型，0神器，1装备,其他为宠物id
	int8 index;
};

struct C2GS_TianShuChangeIndex_Ret <-
{
	int8 retCode; //1:成功
	int64 type;//装备类型，0神器，1装备,其他为宠物id
	int8 index;
};

//天书切换位置
struct GS2C_TianShuChangeSolt_Req ->
{
	int64 type;//装备类型，0神器，1装备,其他为宠物id
	int8 index;
	int8 solt;//天书位置（1-8）
	int8 newsolt;//新天书位置（1-8）
};

struct C2GS_TianShuChangeSolt_Ret <-
{
	int8 retCode; //1:成功
	int64 type;//装备类型，0神器，1装备,其他为宠物id
	int8 index;
	int8 solt;//天书位置（1-8）
	int8 newsolt;//新天书位置（1-8）
};

struct PlayerGodDevice
{
	int8 isDress;   //1:当前穿戴的神器,0则不是
	int32 godDeviceCfgId; //神器配置id
	int8  refineLevel;         // 精炼等级
	int8  enhanceLevel;        //进阶等级
	int64 equipId; //神器绑定的装备id
	vector<EquipTianshu> tianShuList;	// 天书
	int8 content_lv;//容量等级
	vector<TianshuSoltStreng> soltStrengList;	// 天书位置强化信息
	int8 tian_shu_use_index;//天书使用配置套
};

struct GS2C_PlayerGodDeviceList<-
{
	vector<PlayerGodDevice>  playerGodDeviceList;
};


//请求获得一个神器
struct C2GS_GainGodDevice->
{
	int16 godDeviceCfgId;
};

struct GS2C_GainGodDevice_Ret <-
{   
	int8 errorCode;  //0 成功,错误码
	vector<PlayerGodDevice> playerGainGodDevice;
};

//请求切换神器
struct C2GS_ChangeGodDevice->
{
	int8 index;         //神器在列表中的下标
};

struct GS2C_ChangeGodDevice_Ret <-
{
	int8 errorCode;     //0 成功，其他失败
	int8 oldIndex;      //被替换下的神器下标
	int8 newIndex;      //新换上的神器下标
};

//更新一个神器,因镶嵌
struct GS2C_UpdateGodDevice_Ret<-
{
	PlayerGodDevice playerGodDevice;
};


//装备和神器进阶
struct C2GS_Enhance ->
{
	int8 type;      //1 神器,  2 装备
	int64 equipId;       //如果是装备则为装备id,神器就给各0做默认值
};

struct GS2C_Enhance_Ret <-
{
	int8 type;     //1 神器,  2 装备
	int64 equipId;
	int8 inWhere; //1 背包, 2 角色身上
	int8 enhanceLevel;  //当前进阶等级
};


//装备精炼
struct C2GS_Refine ->
{
	int8 type;      //1 神器,  2 装备
	int64 equipId;       //如果是装备则为装备id,神器就给各0做默认值
	int8 isRefineMaxLevel;//是否精炼到最大等级 1:精炼到最大等级, 0 只精炼一级
};

struct C2GS_Refine_All ->
{
	
};

struct PlayerRefine
{
	int8 type; //1 神器,  2 装备
	int64 equipId;
	int8 inWhere; //1 背包, 2 角色身上
	int8 refineLevel;
}

struct GS2C_Refine_Ret <-
{
	int16 errorCode;
	vector<PlayerRefine> playerRefineList;
};

//制造系统
struct Manufacture_Element
{
	int32 itemDataId;     //制作书配置id
	int8 eliminateCdFlag; //是否消除过cd, 0 没有, 1 使用过
	int32 remainSeconds; //剩余时间, 秒为单位
	int8 isDone;          // 1 完成, 0 未完成 
};

//制造列表
struct GS2C_ManufactureList_Ret <-
{
	vector<Manufacture_Element> manufactureList;
};

//请求新的制造单元
struct C2GS_New_Manufacture_Element ->
{
	int32 itemDataId;     //制作书配置id
};

//回复制造结果
struct GS2C_New_Manufacture_Element_Ret <-
{
	int16 errorCode;      // 0 正确,>0 需显示错误
	Manufacture_Element manufactureElement;
}

//请求消除cd
struct C2GS_Eliminate_Cd ->
{
	int32 itemDataId;
};
//回复消除cd
struct GS2C_Eliminate_Cd_Ret <-
{
	int16 errorCode;
	Manufacture_Element manufactureElement;
}
//请求获取已经完成的制造道具
struct C2GS_Gain_Item ->
{
	int32 itemDataId;
};

struct GS2C_Gain_Item_Ret <-
{
	int32 itemDataId;
	int16 errorCode;
};

//宠物信息更新转移（配合天书协议所以定义这边）
struct FightProperty  <-
{
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

struct PetInfo
{
	int64 id;
	int32 dataId;
	int16 level;
	int32 exp;
	int16 strengLv;
	int8 isActive;//1出战，0喂出战
	FightProperty prop;
	vector<EquipTianshu> tianShuList;	// 天书
	int8 content_lv;//容量等级
	vector<TianshuSoltStreng> soltStrengList;	// 天书位置强化信息
	int8 tian_shu_use_index;//天书使用配置套
};

//上线或者喂养时候下发
struct GS2C_AllPets  <-
{
	vector<PetInfo> pets;
};

//宠物信息更新，升级、强化或者获得新宠物时候下发
struct GS2C_UpdatePetInfo  <-
{
	int64 id;
	int32 dataId;
	int16 level;
	int32 exp;
	int16 strengLv;
	int8 isActive;//1出战，0喂出战
	FightProperty prop;
	vector<EquipTianshu> tianShuList;	// 天书
	int8 content_lv;//容量等级
	vector<TianshuSoltStreng> soltStrengList;	// 天书位置强化信息
	int8 tian_shu_use_index;//天书使用配置套
};






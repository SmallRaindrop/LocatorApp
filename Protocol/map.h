//拾取物品
//拾取附加技能道具时，必须指定id, 其它情况id请填写0
struct C2GS_PickUpItem ->
{
	int64 id;
};

struct GS2C_ChangeMap <-
{
	int32 mapDataID;
	int64 mapId;
	int16 x;
	int16 y;
};

//查看玩家位置
struct C2GS_LookupPlayerPos ->
{
	int64 playerId;
};


//查看玩家位置
struct GS2C_LookupPlayerPosRet <-
{
	int64 playerId;
	int64 mapId;
	int32 mapDataID;
	int16 x;
	int16 y;
};


//查看boss位置
struct C2GS_LookupCurMapBossPos ->
{
	int32 bossDataId;
};


//查看boss位置
struct GS2C_LookupCurMapBossPosRet <-
{
	int8  retCode; //0: 成功 
	int32 mapDataID;
	int16 x;
	int16 y;
};


struct playerPos
{
	int64 playerId;
	int64 mapId;
	int32 mapDataID;
	int16 x;
	int16 y;
};

struct C2GS_LookupTeamPos ->
{
	int64 playerId;
};

struct GS2C_LookupTeamPos <-
{
	vector<playerPos> vec;
}

//查看位置模块里，的传送功能，此传送将消耗道具
struct C2GS_TransferMapInLookupPos ->
{
	int64 mapId;
	int32 mapDataID;
	int16 x;
	int16 y;
	int8  isTransferWithTeam;//整个队伍一起传送：1   单个人传送：0
};


//在传送点时，客户端请求传送
struct C2GS_ReqChangeMapInTransport ->
{
	int32 curMapDataID;
};

//在动态传送点时，客户端请求传送
struct C2GS_ReqChangeMapInDynamicTransport ->
{
	int32 curMapDataID;
	int64 doorId;
};

//在世界地图上，客户端请求传送
//传送到目标地图的出生点
struct C2GS_ReqChangeMapInWorldMap ->
{
	int32 desMapDataID;
};

//通过npc，客户端请求传送
struct C2GS_ReqChangeMapByNpc ->
{
	int64 id; //npc的唯一id
	int32 npcDataID;//npc在配置文件里的id 
	int16 npcTransferId;//npc_transfer配置表中的id
};

//发起者请求进入副本
struct C2GS_ReqEnterCopyMap ->
{
	int64  npcId; //npc的唯一id
	int32  npcDataID;//npc在配置文件里的id 
	int32  enterMapDataId;//进入随机副本时，填写0
	int8   enterType; //1:单人进入 2:邀请  3:匹配
};

struct GS2C_ReqEnterCopyMap_Ret <-
{
	int8 retCode;  //检查不通过的原因
	//int64 playerId;//哪个玩家检查不通过, 只要发起者符合就ok,其它队员直接拉进去
};

//给队伍成员发送邀请进入团队副本消息
struct GS2C_BeginePrepareEnterCopy <-
{
	int64 npcId;
	int32 npcDataId;
	int32 copyMapDataId; //副本data ID
	int8   enterType; //1:单人进入 2:邀请  3:匹配
	int64 sponsorId;
};

//客户端回复准备完毕
struct C2GS_PrepareCompleteEnterCopy ->
{
	int64 sponsorId;
};
//服务器收到一个C2GS_PrepareCompleteEnterCopy不需要转发，当所有人都准备完毕时，就广播下面的消息
struct GS2C_AllPrepareEnterCopy <-
{
	int64 sponsorId;
};

//发起人取消进入副本
struct C2GS_SponsorCancelEnterCopyMap ->
{
	int32 curMapDataId;
};

//取消进入副本时，就广播下面的消息
struct GS2C_CancelEnterCopyMap <-
{
	int32  cancelReason;
};

//点击立即开始，客户端发送下面消息，则会5秒倒计时进入副本
struct C2GS_SponsorExitMatchEnterCopyMapNow ->
{
	int32 curMapDataId;
	int32  enterMapDataId;//进入随机副本时，填写0
};

//点击取消匹配，不再进入副本
struct C2GS_SponsorCancelMatchEnter ->
{
	int32 curMapDataId;
	int32  enterMapDataId;//进入随机副本时，填写0
};

//立即进入副本时，就广播下面的消息
struct GS2C_ExitMatchEnterCopyMapNow <-
{
	int64 sponsorId;
};

struct GS2C_CancelMatchEnter <-
{
	int64 sponsorId;
};

//匹配成功时，广播下面的消息
struct GS2C_MatchEnterCopySuccess <-
{
	int32  enterMapDataId; //进入具体哪个副本
};

//玩家离开副本
struct C2GS_PlayerLeaveCopyMap ->
{
};


struct FightStatsInfo
{
	int64 playerId;     //玩家的id
	string playerName;  //玩家的名字
	int8 damagePercent;//伤害输出    百分数
	int8 bearDamagePercent; //伤害承受     百分数
	int16 killCnt;//击杀数
	int16 deadCnt;//死亡次数 
	int16 reliveCnt;//复活队友次数
}
//
struct ItemDataIdAndCnt
{
	int32 itemDataID;
	int32 cnt;
};

//通关副本或失败，发送通关消息给此副本里的所以玩家，如果isContinue为0，客户端收到后，可能倒计时离开副本
//阶段性胜利，选择框倒计时结束，也会发关此消息，如果isContinue为0，客户端离开副本
//如果isContinue为1,客户端继续留在副本
struct GS2C_CopyMapCompleted <-
{
	int8  successNum;   //  0：挑战副本失败  1:阶段性成功  2:通关副本，
	int8  isContinue;   //继续：1    结束副本：0
};

//离开副本后，发送通关结算信息给玩家，客户端收到后，屏幕出现结算对话框
struct GS2C_CopyMapCheckOut <-
{
	int8  successNum;   //  0：挑战副本失败  1:阶段性成功  2:通关副本，
	//1) 战斗统计
	vector<FightStatsInfo> fightStats;
	//2)收益
	int32  seconds;//玩了多少秒
	int16  steps; //完成副本的步骤数,
	int32  coin;  //金币
	int32  exp;   //经验
	vector<ItemDataIdAndCnt> itemInfos;//道具
};


struct PlayerCopyCDInfo   
{
	int32 map_data_id;
	int8 enter_cnt; //已进入的次数
	int8 remain_cnt; //剩余的次数
};
//玩家上线或cd重置时，发送给客户端的副本cd 信息及激活的精英副本列表
struct GS2C_AllCopyCDInfo    <-
{
	vector<PlayerCopyCDInfo> copyCdInfos;//副本的CD信息
};


//通知客户端，更新某副本的cd信息
struct GS2C_UpdatPlayerCopyCDInfo <-  
{
	int32 map_data_id;
	int8 enter_cnt; //已进入的次数
	int8 remain_cnt; //剩余的次数
};

//副本关闭倒计时,时间到时，客户端应该发送离开副本消息到服务器
struct GS2C_CopyMapClose_Countdown <-
{
	int8  second;     //倒计时时间，单位：second
};

// 玩家进入副本时，发送初始信息
struct GS2C_CopyInitInfo<-
{
	int16   copyStepId;      //完成副本的步骤Id 对应copy_step.xls里的id
	int16  totalCnt;    //需要完成的总数量
	int16  curCnt;     //当前已完成的目标数量
	int16  remainSec;   //副本的剩余时间， 单位：秒
	int16  mapDataID;
};

struct GS2C_UpdateCopyProgress<-
{
	int16   copyStepId;      //完成副本的步骤Id 对应copy_step.xls里的id
	int16  curCnt;     //当前已完成的目标数量
};

struct GS2C_MonsterSpawnRemind<-
{
	int16   waveIndex;      //第几波怪物
	int16   delaySec;       //怪物将在多少秒后到来
	int16   isActive;       // 1:被玩家激活，怪物提前到来
};

struct GS2C_GiveSelectionToContinueCopy<-
{
	int16  steps;      //完成副本的步骤数,
	vector<ItemDataIdAndCnt> itemInfos;//道具
};

//是否继续的选择框
//有15秒的倒计时， 玩家在这个倒计时里可以重新选择 客户端要显示各个玩家的选择结果
struct C2GS_ReplySelectionToContinueCopy ->
{
	int8 isContinue;//继续：1    结束副本：0
};
//收到C2GS_ReplySelectionToContinueCopy后，服务器广播此消息给地图内的所有玩家
struct GS2C_ReplySelectionToContinueCopy <-
{
	int64 playerId; 
	int8 isContinue;//继续：1    结束副本：0
};

//发射子弹的技能，发出子弹时向同屏玩家广播些消息
struct GS2C_Missile <-
{
	int64 id;
	int64 ownerId;
	int32 skillId;
	int32 dataId;
	int16 targetX;
	int16 targetY;
	int16 offsetX;			// 偏移的x坐标 客户端表现用
	int16 offsetY;			// 偏移的y坐标 客户端表现用
	int8 multiNum;//多重个数
};

// 子弹碰到目标后，或爆炸后会产生伤害
struct C2GS_MissileDamage ->
{
	int64 id;
	int64 targetId;   //碰撞时，为撞到的对象   爆炸时为爆炸的坐标（类似打点的技能的拼接方式)
	int8  index;
	int16 targetX;
	int16 targetY;
	int8 isExplosion;//是否爆炸0: 碰撞   1：爆炸
};

struct GS2C_MissileDamage <-
{
	int64 id;
	int64 targetId;   //碰撞时，为撞到的对象   爆炸时为爆炸的坐标（类似打点的技能的拼接方式)
	int8  isExplosion;//0: 碰撞   1：爆炸
	int8  index;
};




struct BlockSectionInfo   
{
	int16 x; //区域的起始点的x坐标
	int16 y; //区域的起始点的y坐标
	int8 dx; //区域的x方向的长度
	int8 dy; //区域的y方向的长度
};
//玩家进副本时 服务器发送需要设置阻档的区域列表
struct GS2C_SetBlockSections    <-
{
	vector<BlockSectionInfo> blockSectionInfo;//阻档的区域列表
};

//打掉门时 服务器发送需要清除阻档的区域
struct GS2C_ClearBlockSections    <-
{
	vector<BlockSectionInfo> blockSectionInfo;//阻档的区域列表
};

struct C2GS_OpenDoor_Req ->
{
	int64 id;//门的id
};
struct GS2C_OpenDoor_Ret <-
{
	int8  retCode;//0: 成功  
	int64 id;     //门的id
};

//禁地 单人副本
struct GS2C_ForbiddenArea_Exp <-
{
	int32 exp;//玩家在此副本里获取的经验
};


//副本成功时间
struct GS2C_COPY_SUCC_TIME <-
{
	int32 time;     //时间戳，为0时表示取消
};

struct OpenMap
{
	int32 id;
	int8 state;//0未解锁，1解锁
};

//地点解锁列表
struct GS2C_OPEN_MAP_LIST <-
{
	vector<OpenMap> bigMapList;//大地图
	vector<OpenMap> smallMapList;//小地图
};

//地点解锁或者更新
struct GS2C_OPEN_MAP_UPDATE_OR_ADD <-
{
	int8 type;//0大地图，1小地图
	OpenMap map;
};

//宝箱解锁
struct C2GS_OPEN_TREAS_Req ->
{
	int64 id;
	int64 open_state;//0开启，1停止开启
};

struct GS2C_OPEN_TREAS_Ret <-
{
	int8  retCode;//0: 成功 
	int64 id;
	int64 open_state;//0开启，1停止开启
};

//宝箱状态更新
struct GS2C_TREAS_STATE <-
{
	int64	id;
	int8	status;		// 0开启中，1闲置中
	int32	disTime;	// 毁灭时间
};

//宝箱开启成功
struct C2GS_OPEN_TREAS_Succ_Req ->
{
	int64 id;
};

struct GUIDE_INFO
{
	int16 x;
	int16 y;
};

struct GS2C_GUIDE_LIST <-
{
	vector<GUIDE_INFO> guides;
};


//-define(FreeFightCopyPhase_Wait,1).      %%等待开启自由战斗
//-define(FreeFightCopyPhase_Countdown,2). %%倒计时开启自由战斗
//-define(FreeFightCopyPhase_Started,3).   %%已开启自由战斗
struct GS2C_FreeFightCopyPhaseInfo <-
{
	int8 phase;         //自由战斗处于哪个阶段
	int16 countDownSecs;//在倒计时阶段，秒数，其它阶段填写0
};

//请求获取积分板
struct C2GS_FreeFightCopyScoreBoard_Req ->
{
};

struct scoreBoardItem
{
	string	name;
	int32	level;
	int16 killCnt;//击杀数
	int16 deadCnt;//死亡次数 
};
struct GS2C_FreeFightCopyScoreBoard <-
{
	int32 redCampScore;//红方的积分
	int32 blueCampScore;//蓝方的积分
	vector<scoreBoardItem> redVec;//
	vector<scoreBoardItem> blueVec;//
};

//如果副本玩法已经开启且总人数少于4人则在30秒内关闭副本，并将玩家传出副本
struct GS2C_FreeFightCopyCloseTimerStart<-
{
	int16 countDownSecs;//在倒计秒数
};
//如果启动了关闭副本的倒计时，后面人数又增加到了4个人，会取消这个关闭副本的倒计时
struct GS2C_FreeFightCopyCloseTimerCancel<-
{
	int8 reserve;//预留，没有使用
};



struct freeFightCheckoutItem
{
	int64 id;
	string	name;
	int32	level;
	int16 killCnt;//击杀数
	int16 deadCnt;//死亡次数 
	int32 bindCoin;//奖励的绑金币
	int32 exp;     //奖励的经验
	int32 honor;   //荣誉
};
struct GS2C_FreeFightCopyCheckout<-
{
	int8  winCamp;  //获胜的一方，平局时，获胜的一方填0
	int32 redCampScore;//红方的积分
	int32 blueCampScore;//蓝方的积分
	vector<freeFightCheckoutItem> redVec;//
	vector<freeFightCheckoutItem> blueVec;//
};


struct GS2C_LivePoint<-
{
	int16 livePoint;//注意度（-1为清除）
};

struct ContentionPoint
{
	int8 id;
	int16 x;
	int16 y;
	int8 r;//半径
	int8 processOwner;//进度归属0玩家，1怪物
	int8 processType;//进度是否走0停止，1走, 2反走
	int16 process;//进度
};
struct GS2C_ContentionInfo<-
{
	int16 monsterPoint;
	int16 playerPoint;
	vector<ContentionPoint> contentionPoints;
};

//快捷键
struct ShortcutInfo   
{
	int8 index;
	int8 type;
	int64 id;
};

struct GSWithC_Shortcuts <->
{
	vector<ShortcutInfo> shortcutInfos;
};

//发送一个玩家个性化设置信息到client
struct GS2C_Preference_Set_Info <-
{
	int8 teamSet;//组队设置
};

struct VariantData
{
	int8 index;
	int32 value;
};
struct GS2C_VariantDataSet <-
{
	int8 variant_type;//变量类型，  0:未初始化;    1:玩家变量； 2：世界变量
	vector<VariantData> info_list;
};




//竞技场玩家信息

// 竞技场玩家信息
struct ArenaPlayerEquipinfo
{
	int32 equipDataId;    //装备的配置id
	int8 part;            //装备到的部位 or 脱下的部位	
	int8 stars;           //装备的星级,强化后星级会增加
	int8 luck;            //装备的幸运值
};

struct ArenaPlayerInfo   
{
	int64 	playerId;
	string	name;
	int8	sex;
	int8 	career;
	int32	level;
	int32	fight;	//战斗力
	int32	rank;   // 玩家排名
	vector<ArenaPlayerEquipinfo>  equipList;
};

struct ArenaMsgInfo   
{
	string 	name;
	int8	flag;
	int32 	rank;
	int32	time;
};

// 进入竞技场
struct C2GS_EnterArena_Req  ->
{
};

struct GS2C_EnterArena_Ret <-
{
	int32 	ret;	
};
// 竞技场信息
struct GS2C_ArenaInfo <-
{
	int32	curRank;  // 玩家当前排名
	int32	fight;  // 战斗力
	int32	awardId;  // 昨日奖励	
	vector<ArenaPlayerInfo>  arenaPlayerList;
	vector<ArenaMsgInfo> arenaMsgList;
};

// 开始挑战
struct C2GS_StartChallenge_Req  ->
{
	int64 	playerId;   // 被挑战玩家Id	
};

struct GS2C_StartChallenge_Ret  <-
{
	int32 	ret;
};

// 开始5秒倒计时
struct C2GS_Start_Count_down_Req  ->
{	
};

// 领取竞技场昨日奖励
struct C2GS_Arena_Award_Req  ->
{
};

struct GS2C_Arena_Award_Ret  <-
{
	int32 	ret;
};


//塔防副本
struct DefenseMonsterInfo   
{
	int64 id;
	int32 dataId;
	int8 isDead;
};

// defense monster info update
struct GS2C_Update_TowerDefenseMonster  <-
{
	vector<DefenseMonsterInfo> defenseMonsterInfos;
};

// refresh monster
struct GS2C_MonsterRefresh_Time  <-
{
	int8 waveIndex; //第几波怪
	int32 delayMs; //延迟多少毫秒后到来
};


// 升级塔防副本里面的守护怪物
struct C2GS_Upgrade_TowerDefenseMonster  ->
{
	int64 id;
	int32 dataId;
};

struct C2GS_RecoverLife_TowerDefenseMonster  ->
{
	int64 id;
	int32 dataId;
};

//更新玩家的award info
struct GS2C_TowerDefense_Update_AwardInfo <-
{
	int32 spiritNum;
	int32 awardExp;
	int32 awardCoin;
};


struct GS2C_TowerDefenseCopy_Result <-
{
	int8 isSuccess; //1:成功 0：失败
};


struct GS2C_ArenaCopy_Result <-
{
	int8 isSuccess; //1:成功 0：失败
};

//公告
struct Login_Notice 
{
	string	title;
	string	content;
	string	date;
	string	signature;
};

struct GS2C_Login_Notice <-
{
	vector<Login_Notice>	login_Notice_lists;
};


struct C2GS_HeartBeat  ->
{
};

struct Pay_Info 
{
	int8	id;
	int32	gameMoney;
	int32	ucMoney;
	int8	state;
};

struct GS2C_Pay_Info <-
{
	vector<Pay_Info>	pay_Info_lists;
};

struct C2GS_Player_Get_Sign_In_Info ->
{
};

struct GS2C_Player_Sign_In_Info <-
{
	int8  isAlready;   //是否已签到
};

struct C2GS_Player_Sign_In ->
{
};

struct GS2C_Player_Sign_In_Result <-
{
	int32 days;
	int8 retCode;
};

//补签
struct C2GS_Player_Again_Sign_In ->
{
	int32 days;
};

struct GS2C_Player_Again_Sign_In_Result <-
{
	int32 days;
	int8 retCode;
};

struct C2GS_Player_Get_Award ->
{
	int8 id;
};

struct GS2C_Player_Get_Award_Result <-
{
	int8 retCode;
};

struct C2GS_Sign_In_One_Key_Get_Award ->
{
};

struct C2GS_System_Set_Request ->
{
	int32 type; //类型(如设置交易,组队等等)
	int32 flag;
};

struct GS2C_System_Set_Request_Result <-
{
	int8 retCode;
};

struct C2GS_MakeQuestion ->
{
	int64 playerId;
};

struct GS2C_MakeQuestion <-
{
	vector<int32> questionVec;
};

struct C2GS_Question ->
{
	int32 id;
	int8 type;
	int8 answer;
};

struct GS2C_Question <-
{
	int8 errCnt;
	int8 rightCnt;
	int32 useTime;
	int32 remainTime;
	int8 retCode; //-1,id不存在, -2,已答过, -3,错误次数太多, -4,不在活动期内, 0:答案错误, 1:答案正确
};

//购买红心
struct C2GS_ResetQuestErr ->
{
	int32 cnt;
};

struct GS2C_ResetQuestErr <-
{
	int16 newErrCnt;
	int8 retCode; //1:成功，0:失败,元宝不足
};

struct GS2C_Question_OnLine <-
{
	int8 errCnt;
	int8 rightCnt;
	int32 useTime;
	int32 remainTime;
	int32 lastScore;
	int32 weekScore;
	vector<int32> questionVec;
	vector<int32> finishQuestionVec;
};

struct C2GS_FinishQuestion ->
{
	int64 playerId;
};

struct GS2C_FinishQuestion <-
{
	int32 exp;
	int32 coin;
	int32 bindCoin;
	int32 score;
	int32 weekScore;
};


//	请求排行榜
struct C2GS_RankList_Req ->
{
	int8				rankType;   //1:智慧达人榜
};
// 排行信息
struct RankInfo
{
	int8                rank;      //排名
	string				name;      //牛逼榜和等级榜时为玩家name，帮会榜时为帮会name
	int8                sex;       //性别
	int8                career;    // 职业
	int32               count;     // 智慧达人榜为上周得分
};
//	排行榜返回
struct GS2C_RankList_Ret <-
{
	int32				retCode;    //0成功
	int8				rankType;   //1:智慧达人榜
	vector<RankInfo>    rank_list;  //排行的玩家信息
};


//	boss挑战里，获取boss刷新信息
struct C2GS_BossRefreshList_Req ->
{
};
struct BossRefreshInfo
{
	int8                isDead;      //1：死了  0:活的
	int32               monsterDataId;//怪物的配置id
	int32               nextRefreshDownCountSec; //怪物下次刷新还要多少秒
};
//	boss挑战里  返回boss刷新信息
struct GS2C_BossRefreshList_Ret <-
{
	vector<BossRefreshInfo>    refresh_list;  //boss刷新信息
};


//保存新手引导进度到server,server将把它保存到玩家变量，玩家上线时，应把此玩家变量发给client
struct C2GS_SaveNewHandGuildProgress ->
{
	int32 index;
};

//-define(EnterBattleMap_Err_Of_Cfg, -1).  %%配制表错误
//-define(EnterBattleMap_Err_Of_Cnt, -2).  %%进入次数错误
//-define(EnterBattleMap_Err_Of_Item, -3). %%物品不足
//-define(EnterBattleMap_Err_Of_Level, -4). %%人物等级不足
//-define(EnterBattleMap_Err_Of_PlayerCnt, -5). %%人数已经达到上限
//-define(EnterBattleMap_Err_Of_IsNotLeader, -6). %%不是队长
//-define(EnterBattleMap_Err_Of_Time, -7). %%活动未开始或者已经结束
//-define(EnterBattleMap_Err_Of_Refuse, -8). %%拒绝进入
//-define(EnterBattleMap_Err_Of_IsNotHaveTeam, -9). %%没有队伍
//-define(EnterBattleMap_Err_Of_InTeamList, -10). %%你已经同意进入战场
//-define(EnterBattleMap_Err_Of_IsNotEnterSignalMap, -11). %%组队模式下不能进入单人战场
//-define(EnterBattleMap_Err_Of_PlayerIsMax, -12). %%人数达到上限
//-define(EnterBattleMap_Err_Of_EnterBattlMap, -13). %%你已经进入过战场
//-define(EnterBattleMap_Err_Of_NpcDis, -14). %%npc距离太远
//-define(EnterBattleMap_Err_Of_InBattlMap, -15). %%你已经在战场中
//-define(EnterBattleMap_Err_Of_MemberLevel, -16). %%队员等级不足
//-define(EnterBattleMap_Succ, 1). %%成功进入战场
//-define(RequestBattleMap_Succ, 2). %%队长请求进入战场
//-define(AgreeEnterBattle, 3). %%同意进入战场

//单人进战场
struct C2GS_SignalEnterBattleMap ->
{
	int64 npcId;
	int32 npcDataId;
};

struct GS2C_SignalEnterBattleMap <-
{
	int8 retCode;
};

//组队进战场(队长操作)
struct C2GS_TeamRequestEnterMap ->
{
	int64 npcId;
	int32 npcDataId;
};

struct GS2C_TeamRequestEnterMap <-
{
	int8 retCode;
};

//队伍成员接收到的消息
struct GS2C_InviteEnterBattleMap <-
{
	int64 npcId;
	int32 npcDataId;
	int64 inviteId;
	string inviteName;
};

struct C2GS_InviteEnterBattleMap ->
{
	int8 isAgree; //0:拒绝, 1:同意
	int64 inviterId;
	int64 npcId;
	int32 npcDataId;	
};

struct GS2C_InviteerEnterBattleMap <-
{
	int8 retCode;
};

struct GS2C_InviteEnterBattleMap_Result <-
{
	int8 retCode; //0:拒绝, 1:同意
	string playerName;
};

struct GS2C_UpdateBattlePlayerCnt <-
{
	int32 redPlayerCnt;
	int32 bluePlayerCnt;
	int32 remainTime;
};

struct battleBaseInfo
{
	int32 myScore;          //自已的积分
	int32 redScore;          //
	int32 redKillPlayerCnt;  //击杀玩家
	int32 redKillBaseCnt;    //摧毁建筑
	int32 redGatherCnt;      //夺取圣物
	int32 redKillMonster;    //击杀酋长
	int32 blueScore;          
	int32 blueKillPlayerCnt;  
	int32 blueKillBaseCnt;    
	int32 blueGatherCnt;      
	int32 blueKillMonster; 
};

struct GS2C_EndBattle <-
{
	int32 exp;
	int32 money;
	int32 honor;
	battleBaseInfo st;
};

struct GS2C_UpdateBattleInfo <-
{
	int32 myScore;          //自已的积分
	int32 redScore;         //红方积分
	int32 blueScore;        //蓝方积分
	int32 killPlayerCnt;    //击杀玩家
	int32 deadCnt;          //死亡次数	
};

struct C2GS_BuyBuff ->
{
	int32 buffId;
};

struct GS2C_BuyBuff <-
{
	int8 retCode; //-1,buff不存在,-2,金钱不足,-3,不在战场中,1,成功
};

struct GS2C_TeamTimeOut <-
{
};

struct GS2C_Open_Battle_Door <-
{
	int64 id;
};





//offline pvp protocol
//发送离线经验给客户端
struct GS2C_OfflineExp <-
{
	int32 normalProtOfflineExp;//普通玩家受保护的经验
	int32 vipExtraProtOfflineExp;//vip玩家额外受保护的经验
	int32 notProtOfflineExp;//玩家获取的不受保护的离线经验
	int32 robbedOfflineExp;//被抢走的经验
};

//领取离线经验
struct C2GS_PickupOfflineExp ->
{
};

struct RobbedRecord
{
	int32   robExp;
	int32   robTime;  //格林威治时间
	int64   id;
	string	name;
	int8	career,
	int32	level;
	int32	fight;			//战斗力
	int32   guildId;
};

//抢夺离线经验的详细信息
struct GS2C_RobbedOfflineExpDetailInfo <-
{ 
	vector<RobbedRecord> robbedRecordList;
}


	
struct taskProgress
{
	int8 targetType; //目标类型
	int32 targetCnt; //配制文件中需要完成的数量
	int32 curCnt; //当前完成的数量
};

//接取任务
struct C2GS_AccpetTask ->
{
	int32 taskId;
	int32 npcDataId;
	int64 npcId;
};

struct GS2C_AccpetTask_Result <-
{
	int32 taskId;
	//1:成功, -1:npc不存在, -2:玩家等级不足, -3:玩家职业不符, -4:可接取任务达到上限, 
	//-5:已经接取过, -6:此任务已经完成了, -7:前继任务未完成, -8:与npc距离太远
	int8 retCode;
};

//取消任务
struct C2GS_CannelTask ->
{
	int32 taskId;
	int32 npcDataId;
	int64 npcId;
};

struct GS2C_CannelTask_Result <-
{
	int32 taskId;
	//1:成功, -1:npc不存在, -2:与npc距离太远, -3:此任务未接取
	int8 retCode;
};

//提交任务
struct C2GS_SubmitTask ->
{
	int32 taskId;
	int32 npcDataId;
	int64 npcId;
	int8  index;
};

struct GS2C_SubmitTask_Result <-
{
	int32 taskId;
	//1:成功, -1:npc不存在, -2:此任务未接取, -3:玩家等级不足, -4:与npc距离太远,
	//-5:金币超过上限, -6:背包空间不足, -7:进度未完成, -8:任务过期
	int8 retCode;
};

struct acceptTask
{
	int32 taskId;
	vector<taskProgress> progress;
};

//已接取任务列表
struct GS2C_AcceptTaskList <-
{
	vector<acceptTask> vec;
};

struct completeTask
{
	int32 taskId;
	int32 completeCnt;
};

//已完成任务列表
struct GS2C_CompleteTaskList <-
{
	vector<completeTask> vec;
};

//任务进度变化
struct GS2C_TaskProgressChange <-
{
	int32 taskId;
	vector<taskProgress> progress;
};



struct C2GS_CompleteGather ->
{
	int64 gatherId;
};

struct GS2C_CompleteGather_Result <-
{
	int64 gatherId;
	int8 retCode; //-1:时间未到, 1:成功
};




///////////////////////////////////////////////////////////////////////////////////////////////////////任务链///////////////////////////////////////////////////////////////////////////////////////////////////////

struct C2GS_AccpetTaskChain ->
{
	int32 taskId;
	int32 npcDataId;
	int64 npcId;	
};

struct GS2C_AccpetTaskChain <-
{
	int32 retCode; //1:成功,0:失败
};

//提交任务链
struct C2GS_SubmitTaskChain ->
{
	int32 taskId;
	int32 npcDataId;
	int64 npcId;	
};

//取消任务链
struct C2GS_CannelTaskChain ->
{
	int64 playerId;
};

struct GS2C_CannelTaskChain <-
{
	int8  retCode;
	int16 loopCnt;
};
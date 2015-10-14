struct playTime
{
	int32 startTime;
	int32 endTime;
};

struct buttonBase
{
	int32 type;
	int32 id;
};

struct activeCenterBaseInfo
{
	int32 id;	
	int32 remainTime;
};

struct GS2C_ActiveCenterBaseInfo <-
{
	vector<activeCenterBaseInfo> vec;
};

struct activeBaseInfo
{
	int32 id;
	int32 cnt; //时间段完成的次数
	int32 completeCnt; //完成总次数
};

//正在进行
struct GS2C_InActive <-
{
	vector<activeBaseInfo> vec;
};

//即将开始
struct GS2C_Guture <-
{
	vector<activeBaseInfo> vec;
};

//已完成
struct GS2C_Completed <-
{
	vector<activeBaseInfo> vec;
};

struct GS2C_UpdateActive <-
{
	int32 id;
	int32 cnt;
	int32 totalCnt;
};

struct C2GS_RequestEnterActive ->
{
	int32 id;
};

struct GS2C_RequestEnterActive <-
{
	int8 retCode; //1:成功
};

struct C2GS_OpenActiveUI ->
{
	int64 playerId;
};


//成长礼包
struct C2GS_LevelAward_Req ->
{
	int32 level;
};

//登录礼包
struct C2GS_LoginAward_Req ->
{
	int32 cfgId;//登录礼包的配置id
};

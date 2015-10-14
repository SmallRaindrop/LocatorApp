
//经验增加下发
struct GS2C_PET_EXP_UPDATE <-
{
	int32 exp;
};

//宠物出战
struct C2GS_CALL_PET_Req ->
{
	int64 id;
};

struct GS2C_CALL_PET_Ret <-
{
	int64 call_id;
	int64 call_back_id;
};

//宠物招回
struct C2GS_CALL_BACK_PET_Req ->
{
	int64 id;
};

struct GS2C_CALL_BACK_PET_Ret <-
{
	int64 id;
};

//地图宠物更新广播信息
struct GS2C_PET_MAP_UPDATE <-
{
	int64 id;
	int16 level;
	int32 hp;
	int32 mp;
	int32 hp_max;
	int32 mp_max;
};

//宠物强化
struct C2GS_PET_STRENG_Req ->
{
	int64 id;
};

struct GS2C_PET_STRENG_Ret <-
{
	int8 retCode;//0:成功，-1已经最大等级，-2金钱不足，-3材料不足
};

struct C2GS_PET_FEED_Req ->
{
	
};

struct GS2C_PET_FEED_Ret <-
{
	int8 retCode;//0:成功，-1已经最大喂养值，-2材料不足
};
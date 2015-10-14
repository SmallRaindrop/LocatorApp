struct mallInfo
{
	int32 id;
	int32 itemId;
	int32 item_type; //物品分类 1:杂物, 2:药品, 3:宝石, 4:时装
	int32 sale_type; //0 普通商城 1 特惠商城 2 VIP商城
	int32 number; //道具数量
	int32 discount; //是否折扣, 1:折扣, 0:不折扣
	int32 price; //原价
	int32 price_discount; //折扣价
	int32 price_lucky; //特惠价
	vector<int32> price_vip_vec;
};

struct GS2C_MallInfo <-
{
	vector<mallInfo> mallVec;
};

struct GS2C_MallHot9 <-
{
	vector<int32> vec;
};

struct GS2C_MallLuckyPrice <-
{
	vector<int32> vec;
};

struct C2GS_Common_Buy ->
{
	int32 id;
	int32 cnt;
};

struct GS2C_Common_Buy_Result <-
{
	int8 retCode; //1:成功, -1:此物品不在商城中, -2:元宝不足, -3:背包已满
};

struct C2GS_Lucky_Buy ->
{
	int32 id;
};

struct GS2C_Lucky_Buy_Result <-
{
	int8 retCode; //1:成功, -1:此物品不在商城中, -2:元宝不足, -3:背包已满
	int32 id;
};

struct C2GS_Mall_Refresh ->
{
	int64 playerId;
};

struct GS2C_Mall_Refresh_Result <-
{
	int8 retCode;
};

struct C2GS_vip_Buy ->
{
	int32 id;
	int32 cnt;
};

struct GS2C_vip_Buy_Result <-
{
	int8 retCode; //1:成功, -1:此物品不在商城中, -2:元宝不足, -3:背包已满
};
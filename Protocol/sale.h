struct saleItem
{
	int8 bagType;
	int32 index;
	int64 itemId;
	int32 itemCnt;
};

//上架物品
struct C2GS_PutOnItem ->
{
	saleItem item;
	int64 npcId;
	int32 npcDataId;
	int32 price;
};

//上架元宝
//goldType;
//-define(Sale_Gold_Type_200, 1).
//-define(Sale_Gold_Type_500, 2).
//-define(Sale_Gold_Type_1000, 3).
//-define(Sale_Gold_Type_2000, 4).
//-define(Sale_Gold_Type_5000, 5).
//-define(Sale_Gold_Type_10000, 6).
struct C2GS_PutOnGold ->
{
	int64 npcId;
	int32 npcDataId;
	int32 price;
	int8 goldType;
};

struct GS2C_PutOnGold_Result <-
{
	int8 retCode; //1:成功, -1: 元宝类型错误, -2:元宝不足, -3:未找到寄售的npc, -4:npc距离太远, -5:寄售已经达到上限, -6:自已寄售元宝已经达到上限
	int64 saleId;
	int32 goldType;
};

//下架
struct C2GS_TakeDown ->
{
	int64 saleId;
};

struct GS2C_TakeDown_Result <-
{
	int8 retCode; //1:成功, -1:此寄售不存在, -2:背包已满, -3:元宝达到最大值
	int64 saleId;
};

//购买
struct C2GS_Buy ->
{
	int64 saleId;
};

struct GS2C_Buy <-
{
	int64 saleId;
	int64 buyPlayerId;
	string buyPlayerName;
};

struct GS2C_Buy_Result <-
{
	int8 retCode;//-1;金币不足, -2:背包已满, -3:元宝超过上限或者手续不足, -4:已经被别人买走了
};

//sub_type应由策划指定, 如:武器类, 1000--1999之间
struct C2GS_Filter_Item ->
{
	int32 sub_type;   //物品sub_type结束值
	int32 carrer; //职业
	int32 grade; //品阶
	int32 quality; //品质
};

struct C2GS_Filter_Item_Next_Page ->
{
	int32 page; //显示第几页(从下标2开始)
};

struct C2GS_Filter_Gold ->
{
	int32 goldType;
};

struct C2GS_Filter_Gold_Next_Page ->
{
	int32 page; //显示第几页(从下标2开始)
};

struct sale_filter_gold
{
	int32 price;
	int32 goldType;
	int64 saleId;
};

struct GS2C_Filter_Gold_Result <-
{
	int8 isNextPage;
	int32 totalPage;
	vector<sale_filter_gold> saleVec;
};

struct C2GS_Find_Item ->
{
	string itemName;
};

struct C2GS_Find_Item_Next_Page ->
{
	int32 page; //显示第几页(从下标2开始)
};

struct GS2C_Delete_Sale <-
{
	int64 saleId;
};
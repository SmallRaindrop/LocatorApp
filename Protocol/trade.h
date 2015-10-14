//请求交易
struct C2GS_RequestTrade ->
{
	int64 desPlayerId; //目标玩家
};

struct GS2C_RequestTrade <-
{
	int64 tradeId; //交易id
	string requestName;
};

//响应交易
struct C2GS_ReponseTrade ->
{
	int64 tradeId; //交易id
	int8 reponse; //1:同意, 0:拒绝
};

struct GS2C_ReponseTrade_Result <-
{
	int8 retCode; //-1:对方已经下线, -2:交易不存在, -3:距离太远, -4:对方或者自已正在交易, 1:同意, 0:拒绝
	string name;
	int64 tradeId;
};

struct GS2C_RequestTrade_Result <-
{
	int8 retCode; //-1:对方不在线, -2:距离太远, -3:自己交易未打开, -4：对方交易未打开  1:成功
	int64 tradeId;
}

//取消交易
struct C2GS_CannelTrade ->
{
	int64 tradeId;
};

struct GS2C_CannelTrade <-
{
	int64 playerId;
	int64 tradeId;
};

struct tradeItem
{
	int8 bagType;
	int32 index;
	int64 itemId;
	int32 itemCnt;
};

struct C2GS_InputItem ->
{
	int64 tradeId;
	int32 coin;
	vector<tradeItem> vec;
};

struct GS2C_InputItem <-
{
	int8 retCode; //-1:失败, 0:成功
}

//锁定交易
struct C2GS_LockTrade ->
{
	int32 coin;
	vector<tradeItem> vec;
	int64 tradeId;
};

struct GS2C_LockTrade_Result <-
{
	int8 retCode; //1:成功, -1:元宝不足, -2:金币不足, -3:物品错误, -4:交易不存在, -5:交易状态错误, -6:对方已经下线
	int64 tradeId;
};

struct C2GS_StartTrade ->
{
	int64 tradeId;
};

struct GS2C_StartTrade <-
{
	int8 retCode; //1:成功, 2,对方确定交易, -1:交易不存在, -2:交易状态不对, -3:对方已经下线, -4交易失败
	int64 tradeId;
};

struct C2GS_NpcShopBuy ->
{
	int64 npcId;
	int32 npcDataId;
	int32 itemDataId;
	int32 itemCnt;
};

struct GS2C_NpcShopBuy_Result <-
{
	int8 retCode; //0:成功, 1:背包空间不足 2: 金币不足 3：绑定金币不足 4: 元宝不足 5：绑定元宝不足 
};

struct C2GS_NpcShopSell ->
{
	int64 itemId;
	int32 itemDataId;
	int8  bagType;
	int32 itemCnt;
};

struct GS2C_NpcShopSell_Result <-
{
	int8 retCode; //0:失败, 1:成功
};

struct C2GS_PortableShopBuy ->
{
	int32 itemDataId;
	int32 itemCnt;
};

struct GS2C_PortableShopBuy_Result <-
{
	int8 retCode; //0:成功, 1:背包空间不足 2: 金币不足 3：绑定金币不足 4: 元宝不足 5：绑定元宝不足 
};
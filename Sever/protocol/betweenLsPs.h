// LS向充值服务器(PS)请求注册自己
struct LS2PS_Register_Request <->
{
	int32		serverID;
	string  	sign;
};

// LS注册返回
struct PS2LS_Register_Ret <->
{
	int8		retCode;
};

// 充值信息
struct PS2LS_PayInfo_Request <->
{
	string		orderId;
	string		gameId;
	string		serverId;
	int32       platformId;
	string      accountId;
	string 		payWay;
	string		amount;
};

// 充值信息返回
struct LS2PS_PayInfo_Ret <->
{
	string		orderId;
	int8		retCode;
};

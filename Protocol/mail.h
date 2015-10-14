

//-define(Send_Mail_Failed_Title_Long, -1).  标题太长
//-define(Send_Mail_Failed_Content_Long, -2).  内容太长
//-define(Send_Mail_Failed_Name_Is_Not_Exit, -3).  玩家不存在
//-define(Send_Mail_Failed_Item, -4).  物品不够
//-define(Send_Mail_Failed_Mail_Is_Full, -5).  邮箱已满
//-define(Send_Mail_Failed_Item_Cnt, -6).  附件太多
//-define(Send_Mail_Money_Too_Much, -7).  金钱超过上限
//-define(Send_Mail_Money_Is_Not_Enough, -8).  金钱不够
//-define(Send_Mail_Succ, 1).  成功

//-define(Read_Mail_Is_Not_Exit, -1). 邮件不存在
//-define(Delete_Mail_Is_Have_Attach, -2).有附件不能删除
//-define(Read_Mail_Succ, 1).

//-define(Delete_Mail_Is_Not_Exit, -1). 邮件不存在
//-define(Delete_Mail_Succ, 1).

//-define(Get_Attach_Mail_Is_Not_Exit, -1). 邮件不存在
//-define(Get_Attach_Mail_Bag_Is_Full, -2). 背包已满
//-define(Get_Attach_Mail_Money_Too_Much, -3).金钱超过上线
//-define(Get_Attach_Mail_HaveGet, -4).已经领取过了
//-define(Get_Attach_Mail_Succ, 1).

//-define(System_Mail, 1).  普通邮件
//-define(Common_Mail, 2).  系统邮件

struct Mail_Item
{
	int8 bagType;  //背包类型, 1:装备, 2:杂物, 3:材料
	int64 itemId; //物品id
	int32 index;
	int32 itemCnt;     //物品个数
};

struct C2GS_Send_Mail ->
{
	int64 receivePlayerId;
	string mailTitle;
	string mailContent;
	int32 money;
	vector<Mail_Item> vec;
};

struct GS2C_Send_Mail_Result <-
{
	int8 retCode;
};

struct C2GS_Read_Mail ->
{
	int64 mailId;
};

struct GS2C_Read_Mail_Result <-
{
	int8 retCode;
	int64 mailId;
};

//删除邮件
struct C2GS_Delete_Mail ->
{
	int64 mailId;
};

struct GS2C_Delete_Mail_Result <-
{
	int8 retCode;
	int64 mailId;
};

//批量删除
struct C2GS_Delete_Mail_List ->
{
	vector<int64> mailIdList;
};

struct GS2C_Delete_Mail_List_Result <-
{
	int8 retCode;
	vector<int64> mailIdList;//删除成功的id列表
};

//获取附件
struct C2GS_Get_Attach ->
{
	int64 mailId;
};

struct GS2C_Get_Attach_Result <-
{
	int8 retCode;
	int64 mailId;
};

//批量获取附件
struct C2GS_Get_Attach_List ->
{
	vector<int64> mailIdList;
};

struct GS2C_Get_Attach_List_Result <-
{
	int8 retCode;
	vector<int64> mailIdList;//获取附件成功的id列表
};
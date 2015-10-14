
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct saleItem
{
	int8 bagType;
	int32 index;
	int64 itemId;
	int32 itemCnt;
};
void WritesaleItem(stNetMsg& msg,saleItem& value);
void ReadsaleItem(stNetMsg& msg,saleItem& value);

struct C2GS_PutOnItem
{
	saleItem item;
	int64 npcId;
	int32 npcDataId;
	int32 price;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PutOnItem(stNetMsg& msg,C2GS_PutOnItem& value);
void ReadC2GS_PutOnItem(stNetMsg& msg,C2GS_PutOnItem& value);

struct C2GS_PutOnGold
{
	int64 npcId;
	int32 npcDataId;
	int32 price;
	int8 goldType;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PutOnGold(stNetMsg& msg,C2GS_PutOnGold& value);
void ReadC2GS_PutOnGold(stNetMsg& msg,C2GS_PutOnGold& value);

struct GS2C_PutOnGold_Result
{
	int8 retCode;
	int64 saleId;
	int32 goldType;
};
void WriteGS2C_PutOnGold_Result(stNetMsg& msg,GS2C_PutOnGold_Result& value);
bool OnGS2C_PutOnGold_Result(GS2C_PutOnGold_Result* value);
void ReadGS2C_PutOnGold_Result(stNetMsg& msg,GS2C_PutOnGold_Result& value);

struct C2GS_TakeDown
{
	int64 saleId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_TakeDown(stNetMsg& msg,C2GS_TakeDown& value);
void ReadC2GS_TakeDown(stNetMsg& msg,C2GS_TakeDown& value);

struct GS2C_TakeDown_Result
{
	int8 retCode;
	int64 saleId;
};
void WriteGS2C_TakeDown_Result(stNetMsg& msg,GS2C_TakeDown_Result& value);
bool OnGS2C_TakeDown_Result(GS2C_TakeDown_Result* value);
void ReadGS2C_TakeDown_Result(stNetMsg& msg,GS2C_TakeDown_Result& value);

struct C2GS_Buy
{
	int64 saleId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Buy(stNetMsg& msg,C2GS_Buy& value);
void ReadC2GS_Buy(stNetMsg& msg,C2GS_Buy& value);

struct GS2C_Buy
{
	int64 saleId;
	int64 buyPlayerId;
	string buyPlayerName;
};
void WriteGS2C_Buy(stNetMsg& msg,GS2C_Buy& value);
bool OnGS2C_Buy(GS2C_Buy* value);
void ReadGS2C_Buy(stNetMsg& msg,GS2C_Buy& value);

struct GS2C_Buy_Result
{
	int8 retCode;
};
void WriteGS2C_Buy_Result(stNetMsg& msg,GS2C_Buy_Result& value);
bool OnGS2C_Buy_Result(GS2C_Buy_Result* value);
void ReadGS2C_Buy_Result(stNetMsg& msg,GS2C_Buy_Result& value);

struct C2GS_Filter_Item
{
	int32 sub_type;
	int32 carrer;
	int32 grade;
	int32 quality;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Filter_Item(stNetMsg& msg,C2GS_Filter_Item& value);
void ReadC2GS_Filter_Item(stNetMsg& msg,C2GS_Filter_Item& value);

struct C2GS_Filter_Item_Next_Page
{
	int32 page;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Filter_Item_Next_Page(stNetMsg& msg,C2GS_Filter_Item_Next_Page& value);
void ReadC2GS_Filter_Item_Next_Page(stNetMsg& msg,C2GS_Filter_Item_Next_Page& value);

struct C2GS_Filter_Gold
{
	int32 goldType;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Filter_Gold(stNetMsg& msg,C2GS_Filter_Gold& value);
void ReadC2GS_Filter_Gold(stNetMsg& msg,C2GS_Filter_Gold& value);

struct C2GS_Filter_Gold_Next_Page
{
	int32 page;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Filter_Gold_Next_Page(stNetMsg& msg,C2GS_Filter_Gold_Next_Page& value);
void ReadC2GS_Filter_Gold_Next_Page(stNetMsg& msg,C2GS_Filter_Gold_Next_Page& value);

struct sale_filter_gold
{
	int32 price;
	int32 goldType;
	int64 saleId;
};
void Writesale_filter_gold(stNetMsg& msg,sale_filter_gold& value);
void Readsale_filter_gold(stNetMsg& msg,sale_filter_gold& value);

struct GS2C_Filter_Gold_Result
{
	int8 isNextPage;
	int32 totalPage;
	vector<sale_filter_gold> saleVec;
};
void WriteGS2C_Filter_Gold_Result(stNetMsg& msg,GS2C_Filter_Gold_Result& value);
bool OnGS2C_Filter_Gold_Result(GS2C_Filter_Gold_Result* value);
void ReadGS2C_Filter_Gold_Result(stNetMsg& msg,GS2C_Filter_Gold_Result& value);

struct C2GS_Find_Item
{
	string itemName;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Find_Item(stNetMsg& msg,C2GS_Find_Item& value);
void ReadC2GS_Find_Item(stNetMsg& msg,C2GS_Find_Item& value);

struct C2GS_Find_Item_Next_Page
{
	int32 page;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Find_Item_Next_Page(stNetMsg& msg,C2GS_Find_Item_Next_Page& value);
void ReadC2GS_Find_Item_Next_Page(stNetMsg& msg,C2GS_Find_Item_Next_Page& value);

struct GS2C_Delete_Sale
{
	int64 saleId;
};
void WriteGS2C_Delete_Sale(stNetMsg& msg,GS2C_Delete_Sale& value);
bool OnGS2C_Delete_Sale(GS2C_Delete_Sale* value);
void ReadGS2C_Delete_Sale(stNetMsg& msg,GS2C_Delete_Sale& value);


};


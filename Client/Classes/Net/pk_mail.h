
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct Mail_Item
{
	int8 bagType;
	int64 itemId;
	int32 index;
	int32 itemCnt;
};
void WriteMail_Item(stNetMsg& msg,Mail_Item& value);
void ReadMail_Item(stNetMsg& msg,Mail_Item& value);

struct C2GS_Send_Mail
{
	int64 receivePlayerId;
	string mailTitle;
	string mailContent;
	int32 money;
	vector<Mail_Item> vec;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Send_Mail(stNetMsg& msg,C2GS_Send_Mail& value);
void ReadC2GS_Send_Mail(stNetMsg& msg,C2GS_Send_Mail& value);

struct GS2C_Send_Mail_Result
{
	int8 retCode;
};
void WriteGS2C_Send_Mail_Result(stNetMsg& msg,GS2C_Send_Mail_Result& value);
bool OnGS2C_Send_Mail_Result(GS2C_Send_Mail_Result* value);
void ReadGS2C_Send_Mail_Result(stNetMsg& msg,GS2C_Send_Mail_Result& value);

struct C2GS_Read_Mail
{
	int64 mailId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Read_Mail(stNetMsg& msg,C2GS_Read_Mail& value);
void ReadC2GS_Read_Mail(stNetMsg& msg,C2GS_Read_Mail& value);

struct GS2C_Read_Mail_Result
{
	int8 retCode;
	int64 mailId;
};
void WriteGS2C_Read_Mail_Result(stNetMsg& msg,GS2C_Read_Mail_Result& value);
bool OnGS2C_Read_Mail_Result(GS2C_Read_Mail_Result* value);
void ReadGS2C_Read_Mail_Result(stNetMsg& msg,GS2C_Read_Mail_Result& value);

struct C2GS_Delete_Mail
{
	int64 mailId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Delete_Mail(stNetMsg& msg,C2GS_Delete_Mail& value);
void ReadC2GS_Delete_Mail(stNetMsg& msg,C2GS_Delete_Mail& value);

struct GS2C_Delete_Mail_Result
{
	int8 retCode;
	int64 mailId;
};
void WriteGS2C_Delete_Mail_Result(stNetMsg& msg,GS2C_Delete_Mail_Result& value);
bool OnGS2C_Delete_Mail_Result(GS2C_Delete_Mail_Result* value);
void ReadGS2C_Delete_Mail_Result(stNetMsg& msg,GS2C_Delete_Mail_Result& value);

struct C2GS_Delete_Mail_List
{
	vector<int64> mailIdList;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Delete_Mail_List(stNetMsg& msg,C2GS_Delete_Mail_List& value);
void ReadC2GS_Delete_Mail_List(stNetMsg& msg,C2GS_Delete_Mail_List& value);

struct GS2C_Delete_Mail_List_Result
{
	int8 retCode;
	vector<int64> mailIdList;
};
void WriteGS2C_Delete_Mail_List_Result(stNetMsg& msg,GS2C_Delete_Mail_List_Result& value);
bool OnGS2C_Delete_Mail_List_Result(GS2C_Delete_Mail_List_Result* value);
void ReadGS2C_Delete_Mail_List_Result(stNetMsg& msg,GS2C_Delete_Mail_List_Result& value);

struct C2GS_Get_Attach
{
	int64 mailId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Get_Attach(stNetMsg& msg,C2GS_Get_Attach& value);
void ReadC2GS_Get_Attach(stNetMsg& msg,C2GS_Get_Attach& value);

struct GS2C_Get_Attach_Result
{
	int8 retCode;
	int64 mailId;
};
void WriteGS2C_Get_Attach_Result(stNetMsg& msg,GS2C_Get_Attach_Result& value);
bool OnGS2C_Get_Attach_Result(GS2C_Get_Attach_Result* value);
void ReadGS2C_Get_Attach_Result(stNetMsg& msg,GS2C_Get_Attach_Result& value);

struct C2GS_Get_Attach_List
{
	vector<int64> mailIdList;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_Get_Attach_List(stNetMsg& msg,C2GS_Get_Attach_List& value);
void ReadC2GS_Get_Attach_List(stNetMsg& msg,C2GS_Get_Attach_List& value);

struct GS2C_Get_Attach_List_Result
{
	int8 retCode;
	vector<int64> mailIdList;
};
void WriteGS2C_Get_Attach_List_Result(stNetMsg& msg,GS2C_Get_Attach_List_Result& value);
bool OnGS2C_Get_Attach_List_Result(GS2C_Get_Attach_List_Result* value);
void ReadGS2C_Get_Attach_List_Result(stNetMsg& msg,GS2C_Get_Attach_List_Result& value);


};


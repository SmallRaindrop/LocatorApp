
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct taskProgress
{
	int8 targetType;
	int32 targetCnt;
	int32 curCnt;
};
void WritetaskProgress(stNetMsg& msg,taskProgress& value);
void ReadtaskProgress(stNetMsg& msg,taskProgress& value);

struct C2GS_AccpetTask
{
	int32 taskId;
	int32 npcDataId;
	int64 npcId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_AccpetTask(stNetMsg& msg,C2GS_AccpetTask& value);
void ReadC2GS_AccpetTask(stNetMsg& msg,C2GS_AccpetTask& value);

struct GS2C_AccpetTask_Result
{
	int32 taskId;
	int8 retCode;
};
void WriteGS2C_AccpetTask_Result(stNetMsg& msg,GS2C_AccpetTask_Result& value);
bool OnGS2C_AccpetTask_Result(GS2C_AccpetTask_Result* value);
void ReadGS2C_AccpetTask_Result(stNetMsg& msg,GS2C_AccpetTask_Result& value);

struct C2GS_CannelTask
{
	int32 taskId;
	int32 npcDataId;
	int64 npcId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_CannelTask(stNetMsg& msg,C2GS_CannelTask& value);
void ReadC2GS_CannelTask(stNetMsg& msg,C2GS_CannelTask& value);

struct GS2C_CannelTask_Result
{
	int32 taskId;
	int8 retCode;
};
void WriteGS2C_CannelTask_Result(stNetMsg& msg,GS2C_CannelTask_Result& value);
bool OnGS2C_CannelTask_Result(GS2C_CannelTask_Result* value);
void ReadGS2C_CannelTask_Result(stNetMsg& msg,GS2C_CannelTask_Result& value);

struct C2GS_SubmitTask
{
	int32 taskId;
	int32 npcDataId;
	int64 npcId;
	int8 index;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SubmitTask(stNetMsg& msg,C2GS_SubmitTask& value);
void ReadC2GS_SubmitTask(stNetMsg& msg,C2GS_SubmitTask& value);

struct GS2C_SubmitTask_Result
{
	int32 taskId;
	int8 retCode;
};
void WriteGS2C_SubmitTask_Result(stNetMsg& msg,GS2C_SubmitTask_Result& value);
bool OnGS2C_SubmitTask_Result(GS2C_SubmitTask_Result* value);
void ReadGS2C_SubmitTask_Result(stNetMsg& msg,GS2C_SubmitTask_Result& value);

struct acceptTask
{
	int32 taskId;
	vector<taskProgress> progress;
};
void WriteacceptTask(stNetMsg& msg,acceptTask& value);
void ReadacceptTask(stNetMsg& msg,acceptTask& value);

struct GS2C_AcceptTaskList
{
	vector<acceptTask> vec;
};
void WriteGS2C_AcceptTaskList(stNetMsg& msg,GS2C_AcceptTaskList& value);
bool OnGS2C_AcceptTaskList(GS2C_AcceptTaskList* value);
void ReadGS2C_AcceptTaskList(stNetMsg& msg,GS2C_AcceptTaskList& value);

struct completeTask
{
	int32 taskId;
	int32 completeCnt;
};
void WritecompleteTask(stNetMsg& msg,completeTask& value);
void ReadcompleteTask(stNetMsg& msg,completeTask& value);

struct GS2C_CompleteTaskList
{
	vector<completeTask> vec;
};
void WriteGS2C_CompleteTaskList(stNetMsg& msg,GS2C_CompleteTaskList& value);
bool OnGS2C_CompleteTaskList(GS2C_CompleteTaskList* value);
void ReadGS2C_CompleteTaskList(stNetMsg& msg,GS2C_CompleteTaskList& value);

struct GS2C_TaskProgressChange
{
	int32 taskId;
	vector<taskProgress> progress;
};
void WriteGS2C_TaskProgressChange(stNetMsg& msg,GS2C_TaskProgressChange& value);
bool OnGS2C_TaskProgressChange(GS2C_TaskProgressChange* value);
void ReadGS2C_TaskProgressChange(stNetMsg& msg,GS2C_TaskProgressChange& value);

struct C2GS_CompleteGather
{
	int64 gatherId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_CompleteGather(stNetMsg& msg,C2GS_CompleteGather& value);
void ReadC2GS_CompleteGather(stNetMsg& msg,C2GS_CompleteGather& value);

struct GS2C_CompleteGather_Result
{
	int64 gatherId;
	int8 retCode;
};
void WriteGS2C_CompleteGather_Result(stNetMsg& msg,GS2C_CompleteGather_Result& value);
bool OnGS2C_CompleteGather_Result(GS2C_CompleteGather_Result* value);
void ReadGS2C_CompleteGather_Result(stNetMsg& msg,GS2C_CompleteGather_Result& value);

struct C2GS_AccpetTaskChain
{
	int32 taskId;
	int32 npcDataId;
	int64 npcId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_AccpetTaskChain(stNetMsg& msg,C2GS_AccpetTaskChain& value);
void ReadC2GS_AccpetTaskChain(stNetMsg& msg,C2GS_AccpetTaskChain& value);

struct GS2C_AccpetTaskChain
{
	int32 retCode;
};
void WriteGS2C_AccpetTaskChain(stNetMsg& msg,GS2C_AccpetTaskChain& value);
bool OnGS2C_AccpetTaskChain(GS2C_AccpetTaskChain* value);
void ReadGS2C_AccpetTaskChain(stNetMsg& msg,GS2C_AccpetTaskChain& value);

struct C2GS_SubmitTaskChain
{
	int32 taskId;
	int32 npcDataId;
	int64 npcId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SubmitTaskChain(stNetMsg& msg,C2GS_SubmitTaskChain& value);
void ReadC2GS_SubmitTaskChain(stNetMsg& msg,C2GS_SubmitTaskChain& value);

struct C2GS_CannelTaskChain
{
	int64 playerId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_CannelTaskChain(stNetMsg& msg,C2GS_CannelTaskChain& value);
void ReadC2GS_CannelTaskChain(stNetMsg& msg,C2GS_CannelTaskChain& value);

struct GS2C_CannelTaskChain
{
	int8 retCode;
	int16 loopCnt;
};
void WriteGS2C_CannelTaskChain(stNetMsg& msg,GS2C_CannelTaskChain& value);
bool OnGS2C_CannelTaskChain(GS2C_CannelTaskChain* value);
void ReadGS2C_CannelTaskChain(stNetMsg& msg,GS2C_CannelTaskChain& value);


};


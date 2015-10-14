#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WritetaskProgress(stNetMsg& msg,taskProgress& value)
{
	msg << value.targetType;
	msg << value.targetCnt;
	msg << value.curCnt;
}
void ReadtaskProgress(stNetMsg& msg,taskProgress& value)
{
	msg >> value.targetType;
	msg >> value.targetCnt;
	msg >> value.curCnt;
}
void WriteC2GS_AccpetTask(stNetMsg& msg,C2GS_AccpetTask& value)
{
	msg << value.taskId;
	msg << value.npcDataId;
	msg << value.npcId;
	msg.command(MSG_C2GS_AccpetTask);
}
void C2GS_AccpetTask::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_AccpetTask(msg_s,*this);
	EndSend();
}
void ReadC2GS_AccpetTask(stNetMsg& msg,C2GS_AccpetTask& value)
{
	msg >> value.taskId;
	msg >> value.npcDataId;
	msg >> value.npcId;
}
void WriteGS2C_AccpetTask_Result(stNetMsg& msg,GS2C_AccpetTask_Result& value)
{
	msg << value.taskId;
	msg << value.retCode;
	msg.command(MSG_GS2C_AccpetTask_Result);
}
void ReadGS2C_AccpetTask_Result(stNetMsg& msg,GS2C_AccpetTask_Result& value)
{
	msg >> value.taskId;
	msg >> value.retCode;
}
void WriteC2GS_CannelTask(stNetMsg& msg,C2GS_CannelTask& value)
{
	msg << value.taskId;
	msg << value.npcDataId;
	msg << value.npcId;
	msg.command(MSG_C2GS_CannelTask);
}
void C2GS_CannelTask::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_CannelTask(msg_s,*this);
	EndSend();
}
void ReadC2GS_CannelTask(stNetMsg& msg,C2GS_CannelTask& value)
{
	msg >> value.taskId;
	msg >> value.npcDataId;
	msg >> value.npcId;
}
void WriteGS2C_CannelTask_Result(stNetMsg& msg,GS2C_CannelTask_Result& value)
{
	msg << value.taskId;
	msg << value.retCode;
	msg.command(MSG_GS2C_CannelTask_Result);
}
void ReadGS2C_CannelTask_Result(stNetMsg& msg,GS2C_CannelTask_Result& value)
{
	msg >> value.taskId;
	msg >> value.retCode;
}
void WriteC2GS_SubmitTask(stNetMsg& msg,C2GS_SubmitTask& value)
{
	msg << value.taskId;
	msg << value.npcDataId;
	msg << value.npcId;
	msg << value.index;
	msg.command(MSG_C2GS_SubmitTask);
}
void C2GS_SubmitTask::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SubmitTask(msg_s,*this);
	EndSend();
}
void ReadC2GS_SubmitTask(stNetMsg& msg,C2GS_SubmitTask& value)
{
	msg >> value.taskId;
	msg >> value.npcDataId;
	msg >> value.npcId;
	msg >> value.index;
}
void WriteGS2C_SubmitTask_Result(stNetMsg& msg,GS2C_SubmitTask_Result& value)
{
	msg << value.taskId;
	msg << value.retCode;
	msg.command(MSG_GS2C_SubmitTask_Result);
}
void ReadGS2C_SubmitTask_Result(stNetMsg& msg,GS2C_SubmitTask_Result& value)
{
	msg >> value.taskId;
	msg >> value.retCode;
}
void WriteacceptTask(stNetMsg& msg,acceptTask& value)
{
	msg << value.taskId;
	WriteArray(msg,taskProgress,value.progress);
}
void ReadacceptTask(stNetMsg& msg,acceptTask& value)
{
	msg >> value.taskId;
	ReadArray(msg,taskProgress,value.progress);
}
void WriteGS2C_AcceptTaskList(stNetMsg& msg,GS2C_AcceptTaskList& value)
{
	WriteArray(msg,acceptTask,value.vec);
	msg.command(MSG_GS2C_AcceptTaskList);
}
void ReadGS2C_AcceptTaskList(stNetMsg& msg,GS2C_AcceptTaskList& value)
{
	ReadArray(msg,acceptTask,value.vec);
}
void WritecompleteTask(stNetMsg& msg,completeTask& value)
{
	msg << value.taskId;
	msg << value.completeCnt;
}
void ReadcompleteTask(stNetMsg& msg,completeTask& value)
{
	msg >> value.taskId;
	msg >> value.completeCnt;
}
void WriteGS2C_CompleteTaskList(stNetMsg& msg,GS2C_CompleteTaskList& value)
{
	WriteArray(msg,completeTask,value.vec);
	msg.command(MSG_GS2C_CompleteTaskList);
}
void ReadGS2C_CompleteTaskList(stNetMsg& msg,GS2C_CompleteTaskList& value)
{
	ReadArray(msg,completeTask,value.vec);
}
void WriteGS2C_TaskProgressChange(stNetMsg& msg,GS2C_TaskProgressChange& value)
{
	msg << value.taskId;
	WriteArray(msg,taskProgress,value.progress);
	msg.command(MSG_GS2C_TaskProgressChange);
}
void ReadGS2C_TaskProgressChange(stNetMsg& msg,GS2C_TaskProgressChange& value)
{
	msg >> value.taskId;
	ReadArray(msg,taskProgress,value.progress);
}
void WriteC2GS_CompleteGather(stNetMsg& msg,C2GS_CompleteGather& value)
{
	msg << value.gatherId;
	msg.command(MSG_C2GS_CompleteGather);
}
void C2GS_CompleteGather::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_CompleteGather(msg_s,*this);
	EndSend();
}
void ReadC2GS_CompleteGather(stNetMsg& msg,C2GS_CompleteGather& value)
{
	msg >> value.gatherId;
}
void WriteGS2C_CompleteGather_Result(stNetMsg& msg,GS2C_CompleteGather_Result& value)
{
	msg << value.gatherId;
	msg << value.retCode;
	msg.command(MSG_GS2C_CompleteGather_Result);
}
void ReadGS2C_CompleteGather_Result(stNetMsg& msg,GS2C_CompleteGather_Result& value)
{
	msg >> value.gatherId;
	msg >> value.retCode;
}
void WriteC2GS_AccpetTaskChain(stNetMsg& msg,C2GS_AccpetTaskChain& value)
{
	msg << value.taskId;
	msg << value.npcDataId;
	msg << value.npcId;
	msg.command(MSG_C2GS_AccpetTaskChain);
}
void C2GS_AccpetTaskChain::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_AccpetTaskChain(msg_s,*this);
	EndSend();
}
void ReadC2GS_AccpetTaskChain(stNetMsg& msg,C2GS_AccpetTaskChain& value)
{
	msg >> value.taskId;
	msg >> value.npcDataId;
	msg >> value.npcId;
}
void WriteGS2C_AccpetTaskChain(stNetMsg& msg,GS2C_AccpetTaskChain& value)
{
	msg << value.retCode;
	msg.command(MSG_GS2C_AccpetTaskChain);
}
void ReadGS2C_AccpetTaskChain(stNetMsg& msg,GS2C_AccpetTaskChain& value)
{
	msg >> value.retCode;
}
void WriteC2GS_SubmitTaskChain(stNetMsg& msg,C2GS_SubmitTaskChain& value)
{
	msg << value.taskId;
	msg << value.npcDataId;
	msg << value.npcId;
	msg.command(MSG_C2GS_SubmitTaskChain);
}
void C2GS_SubmitTaskChain::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SubmitTaskChain(msg_s,*this);
	EndSend();
}
void ReadC2GS_SubmitTaskChain(stNetMsg& msg,C2GS_SubmitTaskChain& value)
{
	msg >> value.taskId;
	msg >> value.npcDataId;
	msg >> value.npcId;
}
void WriteC2GS_CannelTaskChain(stNetMsg& msg,C2GS_CannelTaskChain& value)
{
	msg << value.playerId;
	msg.command(MSG_C2GS_CannelTaskChain);
}
void C2GS_CannelTaskChain::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_CannelTaskChain(msg_s,*this);
	EndSend();
}
void ReadC2GS_CannelTaskChain(stNetMsg& msg,C2GS_CannelTaskChain& value)
{
	msg >> value.playerId;
}
void WriteGS2C_CannelTaskChain(stNetMsg& msg,GS2C_CannelTaskChain& value)
{
	msg << value.retCode;
	msg << value.loopCnt;
	msg.command(MSG_GS2C_CannelTaskChain);
}
void ReadGS2C_CannelTaskChain(stNetMsg& msg,GS2C_CannelTaskChain& value)
{
	msg >> value.retCode;
	msg >> value.loopCnt;
}

};


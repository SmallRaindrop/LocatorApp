#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteachievementBase(stNetMsg& msg,achievementBase& value)
{
	msg << value.achievementId;
	msg << value.sort;
}
void ReadachievementBase(stNetMsg& msg,achievementBase& value)
{
	msg >> value.achievementId;
	msg >> value.sort;
}
void WriteachievementProgress(stNetMsg& msg,achievementProgress& value)
{
	msg << value.achievementType;
	msg << value.cnt;
}
void ReadachievementProgress(stNetMsg& msg,achievementProgress& value)
{
	msg >> value.achievementType;
	msg >> value.cnt;
}
void WriteGS2C_FinishAndUnFinishAchievementList(stNetMsg& msg,GS2C_FinishAndUnFinishAchievementList& value)
{
	WriteArray(msg,achievementBase,value.finishVec);
	WriteArray(msg,achievementBase,value.unFinishVec);
	WriteArray(msg,achievementProgress,value.progressVec);
	msg.command(MSG_GS2C_FinishAndUnFinishAchievementList);
}
void ReadGS2C_FinishAndUnFinishAchievementList(stNetMsg& msg,GS2C_FinishAndUnFinishAchievementList& value)
{
	ReadArray(msg,achievementBase,value.finishVec);
	ReadArray(msg,achievementBase,value.unFinishVec);
	ReadArray(msg,achievementProgress,value.progressVec);
}
void WriteGS2C_AchieveProgressChange(stNetMsg& msg,GS2C_AchieveProgressChange& value)
{
	msg << value.achievementType;
	msg << value.cnt;
	msg.command(MSG_GS2C_AchieveProgressChange);
}
void ReadGS2C_AchieveProgressChange(stNetMsg& msg,GS2C_AchieveProgressChange& value)
{
	msg >> value.achievementType;
	msg >> value.cnt;
}
void WriteGS2C_AddAchievement(stNetMsg& msg,GS2C_AddAchievement& value)
{
	WriteachievementBase(msg, value.st);
	msg.command(MSG_GS2C_AddAchievement);
}
void ReadGS2C_AddAchievement(stNetMsg& msg,GS2C_AddAchievement& value)
{
	ReadachievementBase(msg, value.st);
}
void WriteC2GS_UseAchievement(stNetMsg& msg,C2GS_UseAchievement& value)
{
	msg << value.achievementId;
	msg.command(MSG_C2GS_UseAchievement);
}
void C2GS_UseAchievement::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_UseAchievement(msg_s,*this);
	EndSend();
}
void ReadC2GS_UseAchievement(stNetMsg& msg,C2GS_UseAchievement& value)
{
	msg >> value.achievementId;
}
void WriteGS2C_UseAchievement(stNetMsg& msg,GS2C_UseAchievement& value)
{
	msg << value.retCode;
	msg << value.achievementId;
	msg.command(MSG_GS2C_UseAchievement);
}
void ReadGS2C_UseAchievement(stNetMsg& msg,GS2C_UseAchievement& value)
{
	msg >> value.retCode;
	msg >> value.achievementId;
}
void WriteGS2C_UpdateAchievementFinishCnt(stNetMsg& msg,GS2C_UpdateAchievementFinishCnt& value)
{
	msg << value.achievementId;
	msg << value.cnt;
	msg.command(MSG_GS2C_UpdateAchievementFinishCnt);
}
void ReadGS2C_UpdateAchievementFinishCnt(stNetMsg& msg,GS2C_UpdateAchievementFinishCnt& value)
{
	msg >> value.achievementId;
	msg >> value.cnt;
}

};


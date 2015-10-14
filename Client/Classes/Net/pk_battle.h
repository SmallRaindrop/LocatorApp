
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct C2GS_SignalEnterBattleMap
{
	int64 npcId;
	int32 npcDataId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SignalEnterBattleMap(stNetMsg& msg,C2GS_SignalEnterBattleMap& value);
void ReadC2GS_SignalEnterBattleMap(stNetMsg& msg,C2GS_SignalEnterBattleMap& value);

struct GS2C_SignalEnterBattleMap
{
	int8 retCode;
};
void WriteGS2C_SignalEnterBattleMap(stNetMsg& msg,GS2C_SignalEnterBattleMap& value);
bool OnGS2C_SignalEnterBattleMap(GS2C_SignalEnterBattleMap* value);
void ReadGS2C_SignalEnterBattleMap(stNetMsg& msg,GS2C_SignalEnterBattleMap& value);

struct C2GS_TeamRequestEnterMap
{
	int64 npcId;
	int32 npcDataId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_TeamRequestEnterMap(stNetMsg& msg,C2GS_TeamRequestEnterMap& value);
void ReadC2GS_TeamRequestEnterMap(stNetMsg& msg,C2GS_TeamRequestEnterMap& value);

struct GS2C_TeamRequestEnterMap
{
	int8 retCode;
};
void WriteGS2C_TeamRequestEnterMap(stNetMsg& msg,GS2C_TeamRequestEnterMap& value);
bool OnGS2C_TeamRequestEnterMap(GS2C_TeamRequestEnterMap* value);
void ReadGS2C_TeamRequestEnterMap(stNetMsg& msg,GS2C_TeamRequestEnterMap& value);

struct GS2C_InviteEnterBattleMap
{
	int64 npcId;
	int32 npcDataId;
	int64 inviteId;
	string inviteName;
};
void WriteGS2C_InviteEnterBattleMap(stNetMsg& msg,GS2C_InviteEnterBattleMap& value);
bool OnGS2C_InviteEnterBattleMap(GS2C_InviteEnterBattleMap* value);
void ReadGS2C_InviteEnterBattleMap(stNetMsg& msg,GS2C_InviteEnterBattleMap& value);

struct C2GS_InviteEnterBattleMap
{
	int8 isAgree;
	int64 inviterId;
	int64 npcId;
	int32 npcDataId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_InviteEnterBattleMap(stNetMsg& msg,C2GS_InviteEnterBattleMap& value);
void ReadC2GS_InviteEnterBattleMap(stNetMsg& msg,C2GS_InviteEnterBattleMap& value);

struct GS2C_InviteerEnterBattleMap
{
	int8 retCode;
};
void WriteGS2C_InviteerEnterBattleMap(stNetMsg& msg,GS2C_InviteerEnterBattleMap& value);
bool OnGS2C_InviteerEnterBattleMap(GS2C_InviteerEnterBattleMap* value);
void ReadGS2C_InviteerEnterBattleMap(stNetMsg& msg,GS2C_InviteerEnterBattleMap& value);

struct GS2C_InviteEnterBattleMap_Result
{
	int8 retCode;
	string playerName;
};
void WriteGS2C_InviteEnterBattleMap_Result(stNetMsg& msg,GS2C_InviteEnterBattleMap_Result& value);
bool OnGS2C_InviteEnterBattleMap_Result(GS2C_InviteEnterBattleMap_Result* value);
void ReadGS2C_InviteEnterBattleMap_Result(stNetMsg& msg,GS2C_InviteEnterBattleMap_Result& value);

struct GS2C_UpdateBattlePlayerCnt
{
	int32 redPlayerCnt;
	int32 bluePlayerCnt;
	int32 remainTime;
};
void WriteGS2C_UpdateBattlePlayerCnt(stNetMsg& msg,GS2C_UpdateBattlePlayerCnt& value);
bool OnGS2C_UpdateBattlePlayerCnt(GS2C_UpdateBattlePlayerCnt* value);
void ReadGS2C_UpdateBattlePlayerCnt(stNetMsg& msg,GS2C_UpdateBattlePlayerCnt& value);

struct battleBaseInfo
{
	int32 myScore;
	int32 redScore;
	int32 redKillPlayerCnt;
	int32 redKillBaseCnt;
	int32 redGatherCnt;
	int32 redKillMonster;
	int32 blueScore;
	int32 blueKillPlayerCnt;
	int32 blueKillBaseCnt;
	int32 blueGatherCnt;
	int32 blueKillMonster;
};
void WritebattleBaseInfo(stNetMsg& msg,battleBaseInfo& value);
void ReadbattleBaseInfo(stNetMsg& msg,battleBaseInfo& value);

struct GS2C_EndBattle
{
	int32 exp;
	int32 money;
	int32 honor;
	battleBaseInfo st;
};
void WriteGS2C_EndBattle(stNetMsg& msg,GS2C_EndBattle& value);
bool OnGS2C_EndBattle(GS2C_EndBattle* value);
void ReadGS2C_EndBattle(stNetMsg& msg,GS2C_EndBattle& value);

struct GS2C_UpdateBattleInfo
{
	int32 myScore;
	int32 redScore;
	int32 blueScore;
	int32 killPlayerCnt;
	int32 deadCnt;
};
void WriteGS2C_UpdateBattleInfo(stNetMsg& msg,GS2C_UpdateBattleInfo& value);
bool OnGS2C_UpdateBattleInfo(GS2C_UpdateBattleInfo* value);
void ReadGS2C_UpdateBattleInfo(stNetMsg& msg,GS2C_UpdateBattleInfo& value);

struct C2GS_BuyBuff
{
	int32 buffId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_BuyBuff(stNetMsg& msg,C2GS_BuyBuff& value);
void ReadC2GS_BuyBuff(stNetMsg& msg,C2GS_BuyBuff& value);

struct GS2C_BuyBuff
{
	int8 retCode;
};
void WriteGS2C_BuyBuff(stNetMsg& msg,GS2C_BuyBuff& value);
bool OnGS2C_BuyBuff(GS2C_BuyBuff* value);
void ReadGS2C_BuyBuff(stNetMsg& msg,GS2C_BuyBuff& value);

struct GS2C_TeamTimeOut
{
};
void WriteGS2C_TeamTimeOut(stNetMsg& msg,GS2C_TeamTimeOut& value);
bool OnGS2C_TeamTimeOut(GS2C_TeamTimeOut* value);
void ReadGS2C_TeamTimeOut(stNetMsg& msg,GS2C_TeamTimeOut& value);

struct GS2C_Open_Battle_Door
{
	int64 id;
};
void WriteGS2C_Open_Battle_Door(stNetMsg& msg,GS2C_Open_Battle_Door& value);
bool OnGS2C_Open_Battle_Door(GS2C_Open_Battle_Door* value);
void ReadGS2C_Open_Battle_Door(stNetMsg& msg,GS2C_Open_Battle_Door& value);

struct GS2C_OfflineExp
{
	int32 normalProtOfflineExp;
	int32 vipExtraProtOfflineExp;
	int32 notProtOfflineExp;
	int32 robbedOfflineExp;
};
void WriteGS2C_OfflineExp(stNetMsg& msg,GS2C_OfflineExp& value);
bool OnGS2C_OfflineExp(GS2C_OfflineExp* value);
void ReadGS2C_OfflineExp(stNetMsg& msg,GS2C_OfflineExp& value);

struct C2GS_PickupOfflineExp
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PickupOfflineExp(stNetMsg& msg,C2GS_PickupOfflineExp& value);
void ReadC2GS_PickupOfflineExp(stNetMsg& msg,C2GS_PickupOfflineExp& value);

struct RobbedRecord
{
	int32 robExp;
	int32 robTime;
	int64 id;
	string name;
	int8 career;
	int32 level;
	int32 fight;
	int32 guildId;
};
void WriteRobbedRecord(stNetMsg& msg,RobbedRecord& value);
void ReadRobbedRecord(stNetMsg& msg,RobbedRecord& value);

struct GS2C_RobbedOfflineExpDetailInfo
{
	vector<RobbedRecord> robbedRecordList;
};
void WriteGS2C_RobbedOfflineExpDetailInfo(stNetMsg& msg,GS2C_RobbedOfflineExpDetailInfo& value);
bool OnGS2C_RobbedOfflineExpDetailInfo(GS2C_RobbedOfflineExpDetailInfo* value);
void ReadGS2C_RobbedOfflineExpDetailInfo(stNetMsg& msg,GS2C_RobbedOfflineExpDetailInfo& value);


};


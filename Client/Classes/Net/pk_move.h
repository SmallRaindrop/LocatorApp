
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct PosInfo
{
	int16 x;
	int16 y;
};
void WritePosInfo(stNetMsg& msg,PosInfo& value);
void ReadPosInfo(stNetMsg& msg,PosInfo& value);

struct C2GS_PlayerMoveTo
{
	int32 curMapDataId;
	int16 posX;
	int16 posY;
	vector<PosInfo> posInfos;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PlayerMoveTo(stNetMsg& msg,C2GS_PlayerMoveTo& value);
void ReadC2GS_PlayerMoveTo(stNetMsg& msg,C2GS_PlayerMoveTo& value);

struct GS2C_PlayerStopMove
{
	int64 id;
	int16 posX;
	int16 posY;
};
void WriteGS2C_PlayerStopMove(stNetMsg& msg,GS2C_PlayerStopMove& value);
bool OnGS2C_PlayerStopMove(GS2C_PlayerStopMove* value);
void ReadGS2C_PlayerStopMove(stNetMsg& msg,GS2C_PlayerStopMove& value);

struct C2GS_PlayerStopMove
{
	int32 curMapDataId;
	int16 posX;
	int16 posY;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PlayerStopMove(stNetMsg& msg,C2GS_PlayerStopMove& value);
void ReadC2GS_PlayerStopMove(stNetMsg& msg,C2GS_PlayerStopMove& value);

struct GS2C_PlayerMoveInfo
{
	int64 id;
	int16 posX;
	int16 posY;
	vector<PosInfo> posInfos;
};
void WriteGS2C_PlayerMoveInfo(stNetMsg& msg,GS2C_PlayerMoveInfo& value);
bool OnGS2C_PlayerMoveInfo(GS2C_PlayerMoveInfo* value);
void ReadGS2C_PlayerMoveInfo(stNetMsg& msg,GS2C_PlayerMoveInfo& value);

struct GS2C_LookInfoPlayer
{
	int64 id;
	string name;
	int64 guildId;
	int16 level;
	int8 career;
	int8 sex;
	int32 weapon;
	int32 armor;
	int32 wing;
	int64 hp;
	int64 hpMax;
	int32 mp;
	int32 mpMax;
	int16 x;
	int16 y;
	int16 moveSpeed;
	int16 movedMs;
	int32 status;
	int8 vipLevel;
	vector<PosInfo> posInfos;
	int32 pkValue;
	int8 camp;
	int32 battleScore;
	int32 achievementId;
	int8 deadRestTime;
	int16 restPoint;
	int8 helpNum;
	int16 restTime;
};
void WriteGS2C_LookInfoPlayer(stNetMsg& msg,GS2C_LookInfoPlayer& value);
bool OnGS2C_LookInfoPlayer(GS2C_LookInfoPlayer* value);
void ReadGS2C_LookInfoPlayer(stNetMsg& msg,GS2C_LookInfoPlayer& value);

struct GS2C_LookInfoTreas
{
	int64 id;
	int32 dataId;
	int16 x;
	int16 y;
	int8 status;
	int32 disTime;
};
void WriteGS2C_LookInfoTreas(stNetMsg& msg,GS2C_LookInfoTreas& value);
bool OnGS2C_LookInfoTreas(GS2C_LookInfoTreas* value);
void ReadGS2C_LookInfoTreas(stNetMsg& msg,GS2C_LookInfoTreas& value);

struct GS2C_LookInfoVirtualPlayer
{
	int64 id;
	string name;
	int64 guildId;
	int16 level;
	int8 career;
	int8 sex;
	int32 weapon;
	int32 armor;
	int32 wing;
	int64 hp;
	int64 hpMax;
	int32 mp;
	int32 mpMax;
	int16 x;
	int16 y;
	int16 moveSpeed;
	int16 movedMs;
	int32 status;
	int8 vipLevel;
	vector<PosInfo> posInfos;
	int32 pkValue;
	int8 camp;
	int8 profession;
	int32 battleScore;
	int32 achievementId;
};
void WriteGS2C_LookInfoVirtualPlayer(stNetMsg& msg,GS2C_LookInfoVirtualPlayer& value);
bool OnGS2C_LookInfoVirtualPlayer(GS2C_LookInfoVirtualPlayer* value);
void ReadGS2C_LookInfoVirtualPlayer(stNetMsg& msg,GS2C_LookInfoVirtualPlayer& value);

struct GS2C_LookInfoMonster
{
	int64 id;
	int16 monster_data_id;
	int64 hp;
	int64 hpMax;
	int32 mp;
	int32 mpMax;
	int16 x;
	int16 y;
	int16 moveSpeed;
	int16 movedMs;
	int32 status;
	vector<PosInfo> posInfos;
	int8 camp;
};
void WriteGS2C_LookInfoMonster(stNetMsg& msg,GS2C_LookInfoMonster& value);
bool OnGS2C_LookInfoMonster(GS2C_LookInfoMonster* value);
void ReadGS2C_LookInfoMonster(stNetMsg& msg,GS2C_LookInfoMonster& value);

struct GS2C_LookInfoNpc
{
	int64 id;
	int32 npc_data_id;
	int16 x;
	int16 y;
};
void WriteGS2C_LookInfoNpc(stNetMsg& msg,GS2C_LookInfoNpc& value);
bool OnGS2C_LookInfoNpc(GS2C_LookInfoNpc* value);
void ReadGS2C_LookInfoNpc(stNetMsg& msg,GS2C_LookInfoNpc& value);

struct GS2C_LookInfoItem
{
	int64 id;
	int32 item_data_id;
	int64 ownerId;
	int16 x;
	int16 y;
};
void WriteGS2C_LookInfoItem(stNetMsg& msg,GS2C_LookInfoItem& value);
bool OnGS2C_LookInfoItem(GS2C_LookInfoItem* value);
void ReadGS2C_LookInfoItem(stNetMsg& msg,GS2C_LookInfoItem& value);

struct GS2C_LookInfoTrap
{
	int64 id;
	int32 trapDataId;
	int16 x;
	int16 y;
	int16 dx;
	int16 dy;
};
void WriteGS2C_LookInfoTrap(stNetMsg& msg,GS2C_LookInfoTrap& value);
bool OnGS2C_LookInfoTrap(GS2C_LookInfoTrap* value);
void ReadGS2C_LookInfoTrap(stNetMsg& msg,GS2C_LookInfoTrap& value);

struct GS2C_LookInfoPet
{
	int64 id;
	int64 masterId;
	int16 dataId;
	string name;
	int16 level;
	int64 hp;
	int64 hpMax;
	int32 mp;
	int32 mpMax;
	int16 x;
	int16 y;
	int16 moveSpeed;
	int16 movedMs;
	int32 status;
	vector<PosInfo> posInfos;
};
void WriteGS2C_LookInfoPet(stNetMsg& msg,GS2C_LookInfoPet& value);
bool OnGS2C_LookInfoPet(GS2C_LookInfoPet* value);
void ReadGS2C_LookInfoPet(stNetMsg& msg,GS2C_LookInfoPet& value);

struct GS2C_LookInfoDynamicTransferDoor
{
	int64 id;
	int32 door_data_id;
	int16 x;
	int16 y;
	int8 cx;
	int8 cy;
};
void WriteGS2C_LookInfoDynamicTransferDoor(stNetMsg& msg,GS2C_LookInfoDynamicTransferDoor& value);
bool OnGS2C_LookInfoDynamicTransferDoor(GS2C_LookInfoDynamicTransferDoor* value);
void ReadGS2C_LookInfoDynamicTransferDoor(stNetMsg& msg,GS2C_LookInfoDynamicTransferDoor& value);

struct GS2C_ActorDisapearList
{
	vector<int64> info_list;
};
void WriteGS2C_ActorDisapearList(stNetMsg& msg,GS2C_ActorDisapearList& value);
bool OnGS2C_ActorDisapearList(GS2C_ActorDisapearList* value);
void ReadGS2C_ActorDisapearList(stNetMsg& msg,GS2C_ActorDisapearList& value);

struct GS2C_MonsterStopMove
{
	int64 id;
	int16 posX;
	int16 posY;
};
void WriteGS2C_MonsterStopMove(stNetMsg& msg,GS2C_MonsterStopMove& value);
bool OnGS2C_MonsterStopMove(GS2C_MonsterStopMove* value);
void ReadGS2C_MonsterStopMove(stNetMsg& msg,GS2C_MonsterStopMove& value);

struct GS2C_MonsterMoveInfo
{
	int64 id;
	int16 posX;
	int16 posY;
	vector<PosInfo> posInfos;
};
void WriteGS2C_MonsterMoveInfo(stNetMsg& msg,GS2C_MonsterMoveInfo& value);
bool OnGS2C_MonsterMoveInfo(GS2C_MonsterMoveInfo* value);
void ReadGS2C_MonsterMoveInfo(stNetMsg& msg,GS2C_MonsterMoveInfo& value);

struct C2GS_PetMoveTo
{
	int32 curMapDataId;
	int16 posX;
	int16 posY;
	vector<PosInfo> posInfos;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PetMoveTo(stNetMsg& msg,C2GS_PetMoveTo& value);
void ReadC2GS_PetMoveTo(stNetMsg& msg,C2GS_PetMoveTo& value);

struct C2GS_PetStopMove
{
	int32 curMapDataId;
	int16 posX;
	int16 posY;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PetStopMove(stNetMsg& msg,C2GS_PetStopMove& value);
void ReadC2GS_PetStopMove(stNetMsg& msg,C2GS_PetStopMove& value);

struct GS2C_PetStopMove
{
	int64 id;
	int16 posX;
	int16 posY;
};
void WriteGS2C_PetStopMove(stNetMsg& msg,GS2C_PetStopMove& value);
bool OnGS2C_PetStopMove(GS2C_PetStopMove* value);
void ReadGS2C_PetStopMove(stNetMsg& msg,GS2C_PetStopMove& value);

struct GS2C_PetMoveInfo
{
	int64 id;
	int16 posX;
	int16 posY;
	vector<PosInfo> posInfos;
};
void WriteGS2C_PetMoveInfo(stNetMsg& msg,GS2C_PetMoveInfo& value);
bool OnGS2C_PetMoveInfo(GS2C_PetMoveInfo* value);
void ReadGS2C_PetMoveInfo(stNetMsg& msg,GS2C_PetMoveInfo& value);

struct GS2C_RoleTeleport
{
	int64 id;
	int16 posX;
	int16 posY;
};
void WriteGS2C_RoleTeleport(stNetMsg& msg,GS2C_RoleTeleport& value);
bool OnGS2C_RoleTeleport(GS2C_RoleTeleport* value);
void ReadGS2C_RoleTeleport(stNetMsg& msg,GS2C_RoleTeleport& value);

struct C2GS_PetTeleport_OutOfView
{
	int32 curMapDataId;
	int64 id;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PetTeleport_OutOfView(stNetMsg& msg,C2GS_PetTeleport_OutOfView& value);
void ReadC2GS_PetTeleport_OutOfView(stNetMsg& msg,C2GS_PetTeleport_OutOfView& value);

struct PushRoleInfo
{
	int64 id;
	int16 curX;
	int16 curY;
	int16 targetX;
	int16 targetY;
};
void WritePushRoleInfo(stNetMsg& msg,PushRoleInfo& value);
void ReadPushRoleInfo(stNetMsg& msg,PushRoleInfo& value);

struct GS2C_SkillPushRoleList
{
	int64 castId;
	int32 skillId;
	vector<PushRoleInfo> affectRoles;
};
void WriteGS2C_SkillPushRoleList(stNetMsg& msg,GS2C_SkillPushRoleList& value);
bool OnGS2C_SkillPushRoleList(GS2C_SkillPushRoleList* value);
void ReadGS2C_SkillPushRoleList(stNetMsg& msg,GS2C_SkillPushRoleList& value);

struct C2GS_PlayerEvade
{
	int32 curMapDataId;
	int16 desPosX;
	int16 desPosY;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PlayerEvade(stNetMsg& msg,C2GS_PlayerEvade& value);
void ReadC2GS_PlayerEvade(stNetMsg& msg,C2GS_PlayerEvade& value);

struct GS2C_PlayerEvade
{
	int64 id;
	int16 desPosX;
	int16 desPosY;
};
void WriteGS2C_PlayerEvade(stNetMsg& msg,GS2C_PlayerEvade& value);
bool OnGS2C_PlayerEvade(GS2C_PlayerEvade* value);
void ReadGS2C_PlayerEvade(stNetMsg& msg,GS2C_PlayerEvade& value);


};


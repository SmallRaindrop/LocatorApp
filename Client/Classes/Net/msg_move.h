
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_move(stNetMsg& msg);
const int MSG_C2GS_PlayerMoveTo			= 14002;
const int MSG_GS2C_PlayerStopMove			= 14003;
const int MSG_C2GS_PlayerStopMove			= 14004;
const int MSG_GS2C_PlayerMoveInfo			= 14005;
const int MSG_GS2C_LookInfoPlayer			= 14006;
const int MSG_GS2C_LookInfoTreas			= 14007;
const int MSG_GS2C_LookInfoVirtualPlayer			= 14008;
const int MSG_GS2C_LookInfoMonster			= 14009;
const int MSG_GS2C_LookInfoNpc			= 14010;
const int MSG_GS2C_LookInfoItem			= 14011;
const int MSG_GS2C_LookInfoTrap			= 14012;
const int MSG_GS2C_LookInfoPet			= 14013;
const int MSG_GS2C_LookInfoDynamicTransferDoor			= 14014;
const int MSG_GS2C_ActorDisapearList			= 14015;
const int MSG_GS2C_MonsterStopMove			= 14016;
const int MSG_GS2C_MonsterMoveInfo			= 14017;
const int MSG_C2GS_PetMoveTo			= 14018;
const int MSG_C2GS_PetStopMove			= 14019;
const int MSG_GS2C_PetStopMove			= 14020;
const int MSG_GS2C_PetMoveInfo			= 14021;
const int MSG_GS2C_RoleTeleport			= 14022;
const int MSG_C2GS_PetTeleport_OutOfView			= 14023;
const int MSG_GS2C_SkillPushRoleList			= 14025;
const int MSG_C2GS_PlayerEvade			= 14026;
const int MSG_GS2C_PlayerEvade			= 14027;

#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WritePosInfo(stNetMsg& msg,PosInfo& value)
{
	msg << value.x;
	msg << value.y;
}
void ReadPosInfo(stNetMsg& msg,PosInfo& value)
{
	msg >> value.x;
	msg >> value.y;
}
void WriteC2GS_PlayerMoveTo(stNetMsg& msg,C2GS_PlayerMoveTo& value)
{
	msg << value.curMapDataId;
	msg << value.posX;
	msg << value.posY;
	WriteArray(msg,PosInfo,value.posInfos);
	msg.command(MSG_C2GS_PlayerMoveTo);
}
void C2GS_PlayerMoveTo::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PlayerMoveTo(msg_s,*this);
	EndSend();
}
void ReadC2GS_PlayerMoveTo(stNetMsg& msg,C2GS_PlayerMoveTo& value)
{
	msg >> value.curMapDataId;
	msg >> value.posX;
	msg >> value.posY;
	ReadArray(msg,PosInfo,value.posInfos);
}
void WriteGS2C_PlayerStopMove(stNetMsg& msg,GS2C_PlayerStopMove& value)
{
	msg << value.id;
	msg << value.posX;
	msg << value.posY;
	msg.command(MSG_GS2C_PlayerStopMove);
}
void ReadGS2C_PlayerStopMove(stNetMsg& msg,GS2C_PlayerStopMove& value)
{
	msg >> value.id;
	msg >> value.posX;
	msg >> value.posY;
}
void WriteC2GS_PlayerStopMove(stNetMsg& msg,C2GS_PlayerStopMove& value)
{
	msg << value.curMapDataId;
	msg << value.posX;
	msg << value.posY;
	msg.command(MSG_C2GS_PlayerStopMove);
}
void C2GS_PlayerStopMove::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PlayerStopMove(msg_s,*this);
	EndSend();
}
void ReadC2GS_PlayerStopMove(stNetMsg& msg,C2GS_PlayerStopMove& value)
{
	msg >> value.curMapDataId;
	msg >> value.posX;
	msg >> value.posY;
}
void WriteGS2C_PlayerMoveInfo(stNetMsg& msg,GS2C_PlayerMoveInfo& value)
{
	msg << value.id;
	msg << value.posX;
	msg << value.posY;
	WriteArray(msg,PosInfo,value.posInfos);
	msg.command(MSG_GS2C_PlayerMoveInfo);
}
void ReadGS2C_PlayerMoveInfo(stNetMsg& msg,GS2C_PlayerMoveInfo& value)
{
	msg >> value.id;
	msg >> value.posX;
	msg >> value.posY;
	ReadArray(msg,PosInfo,value.posInfos);
}
void WriteGS2C_LookInfoPlayer(stNetMsg& msg,GS2C_LookInfoPlayer& value)
{
	msg << value.id;
	msg << value.name;
	msg << value.guildId;
	msg << value.level;
	msg << value.career;
	msg << value.sex;
	msg << value.weapon;
	msg << value.armor;
	msg << value.wing;
	msg << value.hp;
	msg << value.hpMax;
	msg << value.mp;
	msg << value.mpMax;
	msg << value.x;
	msg << value.y;
	msg << value.moveSpeed;
	msg << value.movedMs;
	msg << value.status;
	msg << value.vipLevel;
	WriteArray(msg,PosInfo,value.posInfos);
	msg << value.pkValue;
	msg << value.camp;
	msg << value.battleScore;
	msg << value.achievementId;
	msg << value.deadRestTime;
	msg << value.restPoint;
	msg << value.helpNum;
	msg << value.restTime;
	msg.command(MSG_GS2C_LookInfoPlayer);
}
void ReadGS2C_LookInfoPlayer(stNetMsg& msg,GS2C_LookInfoPlayer& value)
{
	msg >> value.id;
	msg >> value.name;
	msg >> value.guildId;
	msg >> value.level;
	msg >> value.career;
	msg >> value.sex;
	msg >> value.weapon;
	msg >> value.armor;
	msg >> value.wing;
	msg >> value.hp;
	msg >> value.hpMax;
	msg >> value.mp;
	msg >> value.mpMax;
	msg >> value.x;
	msg >> value.y;
	msg >> value.moveSpeed;
	msg >> value.movedMs;
	msg >> value.status;
	msg >> value.vipLevel;
	ReadArray(msg,PosInfo,value.posInfos);
	msg >> value.pkValue;
	msg >> value.camp;
	msg >> value.battleScore;
	msg >> value.achievementId;
	msg >> value.deadRestTime;
	msg >> value.restPoint;
	msg >> value.helpNum;
	msg >> value.restTime;
}
void WriteGS2C_LookInfoTreas(stNetMsg& msg,GS2C_LookInfoTreas& value)
{
	msg << value.id;
	msg << value.dataId;
	msg << value.x;
	msg << value.y;
	msg << value.status;
	msg << value.disTime;
	msg.command(MSG_GS2C_LookInfoTreas);
}
void ReadGS2C_LookInfoTreas(stNetMsg& msg,GS2C_LookInfoTreas& value)
{
	msg >> value.id;
	msg >> value.dataId;
	msg >> value.x;
	msg >> value.y;
	msg >> value.status;
	msg >> value.disTime;
}
void WriteGS2C_LookInfoVirtualPlayer(stNetMsg& msg,GS2C_LookInfoVirtualPlayer& value)
{
	msg << value.id;
	msg << value.name;
	msg << value.guildId;
	msg << value.level;
	msg << value.career;
	msg << value.sex;
	msg << value.weapon;
	msg << value.armor;
	msg << value.wing;
	msg << value.hp;
	msg << value.hpMax;
	msg << value.mp;
	msg << value.mpMax;
	msg << value.x;
	msg << value.y;
	msg << value.moveSpeed;
	msg << value.movedMs;
	msg << value.status;
	msg << value.vipLevel;
	WriteArray(msg,PosInfo,value.posInfos);
	msg << value.pkValue;
	msg << value.camp;
	msg << value.profession;
	msg << value.battleScore;
	msg << value.achievementId;
	msg.command(MSG_GS2C_LookInfoVirtualPlayer);
}
void ReadGS2C_LookInfoVirtualPlayer(stNetMsg& msg,GS2C_LookInfoVirtualPlayer& value)
{
	msg >> value.id;
	msg >> value.name;
	msg >> value.guildId;
	msg >> value.level;
	msg >> value.career;
	msg >> value.sex;
	msg >> value.weapon;
	msg >> value.armor;
	msg >> value.wing;
	msg >> value.hp;
	msg >> value.hpMax;
	msg >> value.mp;
	msg >> value.mpMax;
	msg >> value.x;
	msg >> value.y;
	msg >> value.moveSpeed;
	msg >> value.movedMs;
	msg >> value.status;
	msg >> value.vipLevel;
	ReadArray(msg,PosInfo,value.posInfos);
	msg >> value.pkValue;
	msg >> value.camp;
	msg >> value.profession;
	msg >> value.battleScore;
	msg >> value.achievementId;
}
void WriteGS2C_LookInfoMonster(stNetMsg& msg,GS2C_LookInfoMonster& value)
{
	msg << value.id;
	msg << value.monster_data_id;
	msg << value.hp;
	msg << value.hpMax;
	msg << value.mp;
	msg << value.mpMax;
	msg << value.x;
	msg << value.y;
	msg << value.moveSpeed;
	msg << value.movedMs;
	msg << value.status;
	WriteArray(msg,PosInfo,value.posInfos);
	msg << value.camp;
	msg.command(MSG_GS2C_LookInfoMonster);
}
void ReadGS2C_LookInfoMonster(stNetMsg& msg,GS2C_LookInfoMonster& value)
{
	msg >> value.id;
	msg >> value.monster_data_id;
	msg >> value.hp;
	msg >> value.hpMax;
	msg >> value.mp;
	msg >> value.mpMax;
	msg >> value.x;
	msg >> value.y;
	msg >> value.moveSpeed;
	msg >> value.movedMs;
	msg >> value.status;
	ReadArray(msg,PosInfo,value.posInfos);
	msg >> value.camp;
}
void WriteGS2C_LookInfoNpc(stNetMsg& msg,GS2C_LookInfoNpc& value)
{
	msg << value.id;
	msg << value.npc_data_id;
	msg << value.x;
	msg << value.y;
	msg.command(MSG_GS2C_LookInfoNpc);
}
void ReadGS2C_LookInfoNpc(stNetMsg& msg,GS2C_LookInfoNpc& value)
{
	msg >> value.id;
	msg >> value.npc_data_id;
	msg >> value.x;
	msg >> value.y;
}
void WriteGS2C_LookInfoItem(stNetMsg& msg,GS2C_LookInfoItem& value)
{
	msg << value.id;
	msg << value.item_data_id;
	msg << value.ownerId;
	msg << value.x;
	msg << value.y;
	msg.command(MSG_GS2C_LookInfoItem);
}
void ReadGS2C_LookInfoItem(stNetMsg& msg,GS2C_LookInfoItem& value)
{
	msg >> value.id;
	msg >> value.item_data_id;
	msg >> value.ownerId;
	msg >> value.x;
	msg >> value.y;
}
void WriteGS2C_LookInfoTrap(stNetMsg& msg,GS2C_LookInfoTrap& value)
{
	msg << value.id;
	msg << value.trapDataId;
	msg << value.x;
	msg << value.y;
	msg << value.dx;
	msg << value.dy;
	msg.command(MSG_GS2C_LookInfoTrap);
}
void ReadGS2C_LookInfoTrap(stNetMsg& msg,GS2C_LookInfoTrap& value)
{
	msg >> value.id;
	msg >> value.trapDataId;
	msg >> value.x;
	msg >> value.y;
	msg >> value.dx;
	msg >> value.dy;
}
void WriteGS2C_LookInfoPet(stNetMsg& msg,GS2C_LookInfoPet& value)
{
	msg << value.id;
	msg << value.masterId;
	msg << value.dataId;
	msg << value.name;
	msg << value.level;
	msg << value.hp;
	msg << value.hpMax;
	msg << value.mp;
	msg << value.mpMax;
	msg << value.x;
	msg << value.y;
	msg << value.moveSpeed;
	msg << value.movedMs;
	msg << value.status;
	WriteArray(msg,PosInfo,value.posInfos);
	msg.command(MSG_GS2C_LookInfoPet);
}
void ReadGS2C_LookInfoPet(stNetMsg& msg,GS2C_LookInfoPet& value)
{
	msg >> value.id;
	msg >> value.masterId;
	msg >> value.dataId;
	msg >> value.name;
	msg >> value.level;
	msg >> value.hp;
	msg >> value.hpMax;
	msg >> value.mp;
	msg >> value.mpMax;
	msg >> value.x;
	msg >> value.y;
	msg >> value.moveSpeed;
	msg >> value.movedMs;
	msg >> value.status;
	ReadArray(msg,PosInfo,value.posInfos);
}
void WriteGS2C_LookInfoDynamicTransferDoor(stNetMsg& msg,GS2C_LookInfoDynamicTransferDoor& value)
{
	msg << value.id;
	msg << value.door_data_id;
	msg << value.x;
	msg << value.y;
	msg << value.cx;
	msg << value.cy;
	msg.command(MSG_GS2C_LookInfoDynamicTransferDoor);
}
void ReadGS2C_LookInfoDynamicTransferDoor(stNetMsg& msg,GS2C_LookInfoDynamicTransferDoor& value)
{
	msg >> value.id;
	msg >> value.door_data_id;
	msg >> value.x;
	msg >> value.y;
	msg >> value.cx;
	msg >> value.cy;
}
void WriteGS2C_ActorDisapearList(stNetMsg& msg,GS2C_ActorDisapearList& value)
{
	msg << value.info_list;
	msg.command(MSG_GS2C_ActorDisapearList);
}
void ReadGS2C_ActorDisapearList(stNetMsg& msg,GS2C_ActorDisapearList& value)
{
	msg >> value.info_list;
}
void WriteGS2C_MonsterStopMove(stNetMsg& msg,GS2C_MonsterStopMove& value)
{
	msg << value.id;
	msg << value.posX;
	msg << value.posY;
	msg.command(MSG_GS2C_MonsterStopMove);
}
void ReadGS2C_MonsterStopMove(stNetMsg& msg,GS2C_MonsterStopMove& value)
{
	msg >> value.id;
	msg >> value.posX;
	msg >> value.posY;
}
void WriteGS2C_MonsterMoveInfo(stNetMsg& msg,GS2C_MonsterMoveInfo& value)
{
	msg << value.id;
	msg << value.posX;
	msg << value.posY;
	WriteArray(msg,PosInfo,value.posInfos);
	msg.command(MSG_GS2C_MonsterMoveInfo);
}
void ReadGS2C_MonsterMoveInfo(stNetMsg& msg,GS2C_MonsterMoveInfo& value)
{
	msg >> value.id;
	msg >> value.posX;
	msg >> value.posY;
	ReadArray(msg,PosInfo,value.posInfos);
}
void WriteC2GS_PetMoveTo(stNetMsg& msg,C2GS_PetMoveTo& value)
{
	msg << value.curMapDataId;
	msg << value.posX;
	msg << value.posY;
	WriteArray(msg,PosInfo,value.posInfos);
	msg.command(MSG_C2GS_PetMoveTo);
}
void C2GS_PetMoveTo::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PetMoveTo(msg_s,*this);
	EndSend();
}
void ReadC2GS_PetMoveTo(stNetMsg& msg,C2GS_PetMoveTo& value)
{
	msg >> value.curMapDataId;
	msg >> value.posX;
	msg >> value.posY;
	ReadArray(msg,PosInfo,value.posInfos);
}
void WriteC2GS_PetStopMove(stNetMsg& msg,C2GS_PetStopMove& value)
{
	msg << value.curMapDataId;
	msg << value.posX;
	msg << value.posY;
	msg.command(MSG_C2GS_PetStopMove);
}
void C2GS_PetStopMove::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PetStopMove(msg_s,*this);
	EndSend();
}
void ReadC2GS_PetStopMove(stNetMsg& msg,C2GS_PetStopMove& value)
{
	msg >> value.curMapDataId;
	msg >> value.posX;
	msg >> value.posY;
}
void WriteGS2C_PetStopMove(stNetMsg& msg,GS2C_PetStopMove& value)
{
	msg << value.id;
	msg << value.posX;
	msg << value.posY;
	msg.command(MSG_GS2C_PetStopMove);
}
void ReadGS2C_PetStopMove(stNetMsg& msg,GS2C_PetStopMove& value)
{
	msg >> value.id;
	msg >> value.posX;
	msg >> value.posY;
}
void WriteGS2C_PetMoveInfo(stNetMsg& msg,GS2C_PetMoveInfo& value)
{
	msg << value.id;
	msg << value.posX;
	msg << value.posY;
	WriteArray(msg,PosInfo,value.posInfos);
	msg.command(MSG_GS2C_PetMoveInfo);
}
void ReadGS2C_PetMoveInfo(stNetMsg& msg,GS2C_PetMoveInfo& value)
{
	msg >> value.id;
	msg >> value.posX;
	msg >> value.posY;
	ReadArray(msg,PosInfo,value.posInfos);
}
void WriteGS2C_RoleTeleport(stNetMsg& msg,GS2C_RoleTeleport& value)
{
	msg << value.id;
	msg << value.posX;
	msg << value.posY;
	msg.command(MSG_GS2C_RoleTeleport);
}
void ReadGS2C_RoleTeleport(stNetMsg& msg,GS2C_RoleTeleport& value)
{
	msg >> value.id;
	msg >> value.posX;
	msg >> value.posY;
}
void WriteC2GS_PetTeleport_OutOfView(stNetMsg& msg,C2GS_PetTeleport_OutOfView& value)
{
	msg << value.curMapDataId;
	msg << value.id;
	msg.command(MSG_C2GS_PetTeleport_OutOfView);
}
void C2GS_PetTeleport_OutOfView::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PetTeleport_OutOfView(msg_s,*this);
	EndSend();
}
void ReadC2GS_PetTeleport_OutOfView(stNetMsg& msg,C2GS_PetTeleport_OutOfView& value)
{
	msg >> value.curMapDataId;
	msg >> value.id;
}
void WritePushRoleInfo(stNetMsg& msg,PushRoleInfo& value)
{
	msg << value.id;
	msg << value.curX;
	msg << value.curY;
	msg << value.targetX;
	msg << value.targetY;
}
void ReadPushRoleInfo(stNetMsg& msg,PushRoleInfo& value)
{
	msg >> value.id;
	msg >> value.curX;
	msg >> value.curY;
	msg >> value.targetX;
	msg >> value.targetY;
}
void WriteGS2C_SkillPushRoleList(stNetMsg& msg,GS2C_SkillPushRoleList& value)
{
	msg << value.castId;
	msg << value.skillId;
	WriteArray(msg,PushRoleInfo,value.affectRoles);
	msg.command(MSG_GS2C_SkillPushRoleList);
}
void ReadGS2C_SkillPushRoleList(stNetMsg& msg,GS2C_SkillPushRoleList& value)
{
	msg >> value.castId;
	msg >> value.skillId;
	ReadArray(msg,PushRoleInfo,value.affectRoles);
}
void WriteC2GS_PlayerEvade(stNetMsg& msg,C2GS_PlayerEvade& value)
{
	msg << value.curMapDataId;
	msg << value.desPosX;
	msg << value.desPosY;
	msg.command(MSG_C2GS_PlayerEvade);
}
void C2GS_PlayerEvade::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PlayerEvade(msg_s,*this);
	EndSend();
}
void ReadC2GS_PlayerEvade(stNetMsg& msg,C2GS_PlayerEvade& value)
{
	msg >> value.curMapDataId;
	msg >> value.desPosX;
	msg >> value.desPosY;
}
void WriteGS2C_PlayerEvade(stNetMsg& msg,GS2C_PlayerEvade& value)
{
	msg << value.id;
	msg << value.desPosX;
	msg << value.desPosY;
	msg.command(MSG_GS2C_PlayerEvade);
}
void ReadGS2C_PlayerEvade(stNetMsg& msg,GS2C_PlayerEvade& value)
{
	msg >> value.id;
	msg >> value.desPosX;
	msg >> value.desPosY;
}

};


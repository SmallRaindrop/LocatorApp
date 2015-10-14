#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_move(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_PlayerStopMove);
 		CMD_DEAL(GS2C_PlayerMoveInfo);
 		CMD_DEAL(GS2C_LookInfoPlayer);
 		CMD_DEAL(GS2C_LookInfoTreas);
 		CMD_DEAL(GS2C_LookInfoVirtualPlayer);
 		CMD_DEAL(GS2C_LookInfoMonster);
 		CMD_DEAL(GS2C_LookInfoNpc);
 		CMD_DEAL(GS2C_LookInfoItem);
 		CMD_DEAL(GS2C_LookInfoTrap);
 		CMD_DEAL(GS2C_LookInfoPet);
 		CMD_DEAL(GS2C_LookInfoDynamicTransferDoor);
 		CMD_DEAL(GS2C_ActorDisapearList);
 		CMD_DEAL(GS2C_MonsterStopMove);
 		CMD_DEAL(GS2C_MonsterMoveInfo);
 		CMD_DEAL(GS2C_PetStopMove);
 		CMD_DEAL(GS2C_PetMoveInfo);
 		CMD_DEAL(GS2C_RoleTeleport);
 		CMD_DEAL(GS2C_SkillPushRoleList);
 		CMD_DEAL(GS2C_PlayerEvade);
 	END_DEAL();
	return false;
}

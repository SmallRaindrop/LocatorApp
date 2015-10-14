#include "NetMsg.h" 
#include "IOSocket.h" 
#include "message.h" 
#include "package.h" 
bool DoMessage_role(stNetMsg& msg)
{
	BEING_DEAL();
		CMD_DEAL(GS2C_PlayerSingleProperty);
 		CMD_DEAL(GS2C_PlayerSinglePropertyStr);
 		CMD_DEAL(GS2C_PlayerSinglePropertySync);
 		CMD_DEAL(GS2C_PlayerSinglePropertyStrSync);
 		CMD_DEAL(GS2C_PlayerMultiplePropertySync);
 		CMD_DEAL(GS2C_CdUseItem);
 		CMD_DEAL(GS2C_PlayerProperty);
 		CMD_DEAL(GS2C_PlayerFightProperty);
 		CMD_DEAL(GS2U_AddSkillList);
 		CMD_DEAL(GS2U_RemoveSkillList);
 		CMD_DEAL(GS2U_LevelChangeSkillList);
 		CMD_DEAL(GS2U_UseSkill);
 		CMD_DEAL(GS2U_UseTransferSkill);
 		CMD_DEAL(GS2C_NextAttack_Is_GongSha);
 		CMD_DEAL(GS2U_RoleEffect);
 		CMD_DEAL(GS2C_RecoverLife_Ret);
 		CMD_DEAL(GS2C_HelpRecover_Ret);
 		CMD_DEAL(GS2U_BufferAttach);
 		CMD_DEAL(GS2U_BufferRemove);
 		CMD_DEAL(GS2C_KickOut);
 		CMD_DEAL(GS2C_SkillShortCutConfig);
 		CMD_DEAL(GS2C_WingInfo);
 		CMD_DEAL(GS2C_AddWing);
 		CMD_DEAL(GS2C_ReplaceWing);
 		CMD_DEAL(GS2C_PlayerFightingCapacityChange);
 		CMD_DEAL(GS2C_HallTechOpenList);
 		CMD_DEAL(GS2C_HallTechLvUp_Ret);
 		CMD_DEAL(GS2C_HallTechLvUp);
 	END_DEAL();
	return false;
}

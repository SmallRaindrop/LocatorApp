
#pragma  once 

#include <vector> 

using namespace std;

extern bool DoMessage_role(stNetMsg& msg);
const int MSG_GS2C_PlayerSingleProperty			= 12001;
const int MSG_GS2C_PlayerSinglePropertyStr			= 12002;
const int MSG_GS2C_PlayerSinglePropertySync			= 12003;
const int MSG_GS2C_PlayerSinglePropertyStrSync			= 12004;
const int MSG_GS2C_PlayerMultiplePropertySync			= 12006;
const int MSG_GS2C_CdUseItem			= 12007;
const int MSG_GS2C_PlayerProperty			= 12010;
const int MSG_GS2C_PlayerFightProperty			= 12011;
const int MSG_GS2U_AddSkillList			= 12012;
const int MSG_GS2U_RemoveSkillList			= 12013;
const int MSG_GS2U_LevelChangeSkillList			= 12014;
const int MSG_C2GS_UseSkill			= 12015;
const int MSG_GS2U_UseSkill			= 12016;
const int MSG_GS2U_UseTransferSkill			= 12017;
const int MSG_GS2C_NextAttack_Is_GongSha			= 12018;
const int MSG_GS2U_RoleEffect			= 12020;
const int MSG_C2GS_RecoverLife_Req			= 12021;
const int MSG_GS2C_RecoverLife_Ret			= 12022;
const int MSG_C2GS_HelpRecover_Req			= 12023;
const int MSG_GS2C_HelpRecover_Ret			= 12024;
const int MSG_GS2U_BufferAttach			= 12025;
const int MSG_GS2U_BufferRemove			= 12026;
const int MSG_GS2C_KickOut			= 12027;
const int MSG_C2GS_ChangePkState			= 12028;
const int MSG_C2GS_ReturnToSelectRoleDlg_Req			= 12029;
const int MSG_C2GS_PetUseSkill			= 12030;
const int MSG_C2GS_SkillShortCutConfig			= 12032;
const int MSG_GS2C_SkillShortCutConfig			= 12033;
const int MSG_GS2C_WingInfo			= 12034;
const int MSG_C2GS_SummonWing			= 12035;
const int MSG_GS2C_AddWing			= 12036;
const int MSG_C2GS_EquipWing			= 12037;
const int MSG_C2GS_UnEquipWing			= 12038;
const int MSG_C2GS_UpgradeWing			= 12039;
const int MSG_GS2C_ReplaceWing			= 12040;
const int MSG_GS2C_PlayerFightingCapacityChange			= 12041;
const int MSG_GS2C_HallTechOpenList			= 12043;
const int MSG_C2GS_HallTechLvUp_Req			= 12044;
const int MSG_GS2C_HallTechLvUp_Ret			= 12045;
const int MSG_GS2C_HallTechLvUp			= 12046;

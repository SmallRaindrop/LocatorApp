#include "NetMsg.h" 
#include "IOSocket.h" 
#include "package.h" 
#include "message.h" 

namespace pk{

void WriteGS2C_PlayerSingleProperty(stNetMsg& msg,GS2C_PlayerSingleProperty& value)
{
	msg << value.type;
	msg << value.value;
	msg.command(MSG_GS2C_PlayerSingleProperty);
}
void ReadGS2C_PlayerSingleProperty(stNetMsg& msg,GS2C_PlayerSingleProperty& value)
{
	msg >> value.type;
	msg >> value.value;
}
void WriteGS2C_PlayerSinglePropertyStr(stNetMsg& msg,GS2C_PlayerSinglePropertyStr& value)
{
	msg << value.type;
	msg << value.value;
	msg.command(MSG_GS2C_PlayerSinglePropertyStr);
}
void ReadGS2C_PlayerSinglePropertyStr(stNetMsg& msg,GS2C_PlayerSinglePropertyStr& value)
{
	msg >> value.type;
	msg >> value.value;
}
void WriteGS2C_PlayerSinglePropertySync(stNetMsg& msg,GS2C_PlayerSinglePropertySync& value)
{
	msg << value.playerID;
	msg << value.type;
	msg << value.value;
	msg.command(MSG_GS2C_PlayerSinglePropertySync);
}
void ReadGS2C_PlayerSinglePropertySync(stNetMsg& msg,GS2C_PlayerSinglePropertySync& value)
{
	msg >> value.playerID;
	msg >> value.type;
	msg >> value.value;
}
void WriteGS2C_PlayerSinglePropertyStrSync(stNetMsg& msg,GS2C_PlayerSinglePropertyStrSync& value)
{
	msg << value.playerID;
	msg << value.type;
	msg << value.value;
	msg.command(MSG_GS2C_PlayerSinglePropertyStrSync);
}
void ReadGS2C_PlayerSinglePropertyStrSync(stNetMsg& msg,GS2C_PlayerSinglePropertyStrSync& value)
{
	msg >> value.playerID;
	msg >> value.type;
	msg >> value.value;
}
void WritePlayerProperty(stNetMsg& msg,PlayerProperty& value)
{
	msg << value.type;
	msg << value.value;
}
void ReadPlayerProperty(stNetMsg& msg,PlayerProperty& value)
{
	msg >> value.type;
	msg >> value.value;
}
void WriteGS2C_PlayerMultiplePropertySync(stNetMsg& msg,GS2C_PlayerMultiplePropertySync& value)
{
	msg << value.playerID;
	WriteArray(msg,PlayerProperty,value.playerProperties);
	msg.command(MSG_GS2C_PlayerMultiplePropertySync);
}
void ReadGS2C_PlayerMultiplePropertySync(stNetMsg& msg,GS2C_PlayerMultiplePropertySync& value)
{
	msg >> value.playerID;
	ReadArray(msg,PlayerProperty,value.playerProperties);
}
void WriteGS2C_CdUseItem(stNetMsg& msg,GS2C_CdUseItem& value)
{
	msg << value.id;
	msg << value.remainTime;
	msg.command(MSG_GS2C_CdUseItem);
}
void ReadGS2C_CdUseItem(stNetMsg& msg,GS2C_CdUseItem& value)
{
	msg >> value.id;
	msg >> value.remainTime;
}
void WritePlayerBuffInfo(stNetMsg& msg,PlayerBuffInfo& value)
{
	msg << value.id;
	msg << value.buffDataId;
	msg << value.duration;
}
void ReadPlayerBuffInfo(stNetMsg& msg,PlayerBuffInfo& value)
{
	msg >> value.id;
	msg >> value.buffDataId;
	msg >> value.duration;
}
void WritePlayerSkillInfo(stNetMsg& msg,PlayerSkillInfo& value)
{
	msg << value.skillId;
	msg << value.level;
	msg << value.cdtime;
}
void ReadPlayerSkillInfo(stNetMsg& msg,PlayerSkillInfo& value)
{
	msg >> value.skillId;
	msg >> value.level;
	msg >> value.cdtime;
}
void WriteGS2C_PlayerProperty(stNetMsg& msg,GS2C_PlayerProperty& value)
{
	msg << value.playerID;
	msg << value.name;
	msg << value.level;
	msg << value.career;
	msg << value.exp;
	msg << value.bindCoin;
	msg << value.treasure;
	msg << value.bindTreasure;
	msg << value.fight;
	WriteArray(msg,GS2C_CdUseItem,value.cdTimeUseItem);
	msg << value.bagGridNum;
	msg << value.vipLevel;
	msg << value.totalTreasure;
	msg << value.titleId;
	msg << value.hp;
	msg << value.mp;
	msg << value.recoverCount;
	msg << value.manufactureSize;
	WriteArray(msg,PlayerBuffInfo,value.buff_list);
	WriteArray(msg,PlayerSkillInfo,value.skill_list);
	msg << value.state;
	msg << value.pk;
	msg << value.pkState;
	msg << value.phy_dam;
	msg << value.fire_dam;
	msg << value.code_dam;
	msg << value.elec_dam;
	msg << value.toxin_dam;
	msg << value.base_dam_increase;
	msg << value.all_dam_increase;
	msg << value.all_dam_reduce;
	msg << value.atk_power;
	msg << value.hp_max;
	msg << value.hp_r;
	msg << value.hp_rp;
	msg << value.by_cure_factor;
	msg << value.mp_max;
	msg << value.mp_r;
	msg << value.speed;
	msg << value.armor;
	msg << value.phy_res;
	msg << value.fire_res;
	msg << value.cold_res;
	msg << value.elec_res;
	msg << value.toxin_res;
	msg << value.tough;
	msg << value.penetrate;
	msg << value.thickness;
	msg << value.crit_p;
	msg << value.crit_hurt;
	msg << value.accurate_p;
	msg << value.dodge_p;
	msg << value.trigger_p;
	msg << value.atk_speed_increase;
	msg << value.mp_efficiency;
	msg << value.skill_duration;
	msg << value.skill_power;
	msg << value.skill_rang;
	msg << value.hp_ball;
	msg << value.mp_ball;
	msg << value.armor_reduce;
	msg.command(MSG_GS2C_PlayerProperty);
}
void ReadGS2C_PlayerProperty(stNetMsg& msg,GS2C_PlayerProperty& value)
{
	msg >> value.playerID;
	msg >> value.name;
	msg >> value.level;
	msg >> value.career;
	msg >> value.exp;
	msg >> value.bindCoin;
	msg >> value.treasure;
	msg >> value.bindTreasure;
	msg >> value.fight;
	ReadArray(msg,GS2C_CdUseItem,value.cdTimeUseItem);
	msg >> value.bagGridNum;
	msg >> value.vipLevel;
	msg >> value.totalTreasure;
	msg >> value.titleId;
	msg >> value.hp;
	msg >> value.mp;
	msg >> value.recoverCount;
	msg >> value.manufactureSize;
	ReadArray(msg,PlayerBuffInfo,value.buff_list);
	ReadArray(msg,PlayerSkillInfo,value.skill_list);
	msg >> value.state;
	msg >> value.pk;
	msg >> value.pkState;
	msg >> value.phy_dam;
	msg >> value.fire_dam;
	msg >> value.code_dam;
	msg >> value.elec_dam;
	msg >> value.toxin_dam;
	msg >> value.base_dam_increase;
	msg >> value.all_dam_increase;
	msg >> value.all_dam_reduce;
	msg >> value.atk_power;
	msg >> value.hp_max;
	msg >> value.hp_r;
	msg >> value.hp_rp;
	msg >> value.by_cure_factor;
	msg >> value.mp_max;
	msg >> value.mp_r;
	msg >> value.speed;
	msg >> value.armor;
	msg >> value.phy_res;
	msg >> value.fire_res;
	msg >> value.cold_res;
	msg >> value.elec_res;
	msg >> value.toxin_res;
	msg >> value.tough;
	msg >> value.penetrate;
	msg >> value.thickness;
	msg >> value.crit_p;
	msg >> value.crit_hurt;
	msg >> value.accurate_p;
	msg >> value.dodge_p;
	msg >> value.trigger_p;
	msg >> value.atk_speed_increase;
	msg >> value.mp_efficiency;
	msg >> value.skill_duration;
	msg >> value.skill_power;
	msg >> value.skill_rang;
	msg >> value.hp_ball;
	msg >> value.mp_ball;
	msg >> value.armor_reduce;
}
void WriteGS2C_PlayerFightProperty(stNetMsg& msg,GS2C_PlayerFightProperty& value)
{
	msg << value.state;
	msg << value.hp;
	msg << value.mp;
	msg << value.phy_dam;
	msg << value.fire_dam;
	msg << value.code_dam;
	msg << value.elec_dam;
	msg << value.toxin_dam;
	msg << value.base_dam_increase;
	msg << value.all_dam_increase;
	msg << value.all_dam_reduce;
	msg << value.atk_power;
	msg << value.hp_max;
	msg << value.hp_r;
	msg << value.hp_rp;
	msg << value.by_cure_factor;
	msg << value.mp_max;
	msg << value.mp_r;
	msg << value.speed;
	msg << value.armor;
	msg << value.phy_res;
	msg << value.fire_res;
	msg << value.cold_res;
	msg << value.elec_res;
	msg << value.toxin_res;
	msg << value.tough;
	msg << value.penetrate;
	msg << value.thickness;
	msg << value.crit_p;
	msg << value.crit_hurt;
	msg << value.accurate_p;
	msg << value.dodge_p;
	msg << value.trigger_p;
	msg << value.atk_speed_increase;
	msg << value.mp_efficiency;
	msg << value.skill_duration;
	msg << value.skill_power;
	msg << value.skill_rang;
	msg << value.hp_ball;
	msg << value.mp_ball;
	msg << value.armor_reduce;
	msg.command(MSG_GS2C_PlayerFightProperty);
}
void ReadGS2C_PlayerFightProperty(stNetMsg& msg,GS2C_PlayerFightProperty& value)
{
	msg >> value.state;
	msg >> value.hp;
	msg >> value.mp;
	msg >> value.phy_dam;
	msg >> value.fire_dam;
	msg >> value.code_dam;
	msg >> value.elec_dam;
	msg >> value.toxin_dam;
	msg >> value.base_dam_increase;
	msg >> value.all_dam_increase;
	msg >> value.all_dam_reduce;
	msg >> value.atk_power;
	msg >> value.hp_max;
	msg >> value.hp_r;
	msg >> value.hp_rp;
	msg >> value.by_cure_factor;
	msg >> value.mp_max;
	msg >> value.mp_r;
	msg >> value.speed;
	msg >> value.armor;
	msg >> value.phy_res;
	msg >> value.fire_res;
	msg >> value.cold_res;
	msg >> value.elec_res;
	msg >> value.toxin_res;
	msg >> value.tough;
	msg >> value.penetrate;
	msg >> value.thickness;
	msg >> value.crit_p;
	msg >> value.crit_hurt;
	msg >> value.accurate_p;
	msg >> value.dodge_p;
	msg >> value.trigger_p;
	msg >> value.atk_speed_increase;
	msg >> value.mp_efficiency;
	msg >> value.skill_duration;
	msg >> value.skill_power;
	msg >> value.skill_rang;
	msg >> value.hp_ball;
	msg >> value.mp_ball;
	msg >> value.armor_reduce;
}
void WriteGS2U_AddSkillList(stNetMsg& msg,GS2U_AddSkillList& value)
{
	WriteArray(msg,PlayerSkillInfo,value.skill_list);
	msg.command(MSG_GS2U_AddSkillList);
}
void ReadGS2U_AddSkillList(stNetMsg& msg,GS2U_AddSkillList& value)
{
	ReadArray(msg,PlayerSkillInfo,value.skill_list);
}
void WriteGS2U_RemoveSkillList(stNetMsg& msg,GS2U_RemoveSkillList& value)
{
	msg << value.skill_id_list;
	msg.command(MSG_GS2U_RemoveSkillList);
}
void ReadGS2U_RemoveSkillList(stNetMsg& msg,GS2U_RemoveSkillList& value)
{
	msg >> value.skill_id_list;
}
void WriteGS2U_LevelChangeSkillList(stNetMsg& msg,GS2U_LevelChangeSkillList& value)
{
	WriteArray(msg,PlayerSkillInfo,value.skill_list);
	msg.command(MSG_GS2U_LevelChangeSkillList);
}
void ReadGS2U_LevelChangeSkillList(stNetMsg& msg,GS2U_LevelChangeSkillList& value)
{
	ReadArray(msg,PlayerSkillInfo,value.skill_list);
}
void WriteC2GS_UseSkill(stNetMsg& msg,C2GS_UseSkill& value)
{
	msg << value.skillId;
	msg << value.selfPosX;
	msg << value.selfPosY;
	msg << value.offsetX;
	msg << value.offsetY;
	msg << value.targetId;
	msg.command(MSG_C2GS_UseSkill);
}
void C2GS_UseSkill::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_UseSkill(msg_s,*this);
	EndSend();
}
void ReadC2GS_UseSkill(stNetMsg& msg,C2GS_UseSkill& value)
{
	msg >> value.skillId;
	msg >> value.selfPosX;
	msg >> value.selfPosY;
	msg >> value.offsetX;
	msg >> value.offsetY;
	msg >> value.targetId;
}
void WriteGS2U_UseSkill(stNetMsg& msg,GS2U_UseSkill& value)
{
	msg << value.casterId;
	msg << value.offsetX;
	msg << value.offsetY;
	msg << value.targetId;
	msg << value.skillId;
	msg.command(MSG_GS2U_UseSkill);
}
void ReadGS2U_UseSkill(stNetMsg& msg,GS2U_UseSkill& value)
{
	msg >> value.casterId;
	msg >> value.offsetX;
	msg >> value.offsetY;
	msg >> value.targetId;
	msg >> value.skillId;
}
void WriteGS2U_UseTransferSkill(stNetMsg& msg,GS2U_UseTransferSkill& value)
{
	msg << value.casterId;
	msg << value.targetId;
	msg << value.skillId;
	msg << value.transferDesX;
	msg << value.transferDesY;
	msg.command(MSG_GS2U_UseTransferSkill);
}
void ReadGS2U_UseTransferSkill(stNetMsg& msg,GS2U_UseTransferSkill& value)
{
	msg >> value.casterId;
	msg >> value.targetId;
	msg >> value.skillId;
	msg >> value.transferDesX;
	msg >> value.transferDesY;
}
void WriteGS2C_NextAttack_Is_GongSha(stNetMsg& msg,GS2C_NextAttack_Is_GongSha& value)
{
	msg << value.reserve;
	msg.command(MSG_GS2C_NextAttack_Is_GongSha);
}
void ReadGS2C_NextAttack_Is_GongSha(stNetMsg& msg,GS2C_NextAttack_Is_GongSha& value)
{
	msg >> value.reserve;
}
void WriteRoleEffectInfo(stNetMsg& msg,RoleEffectInfo& value)
{
	msg << value.castId;
	msg << value.targetId;
	msg << value.skillDataId;
	msg << value.effectType;
	msg << value.data;
}
void ReadRoleEffectInfo(stNetMsg& msg,RoleEffectInfo& value)
{
	msg >> value.castId;
	msg >> value.targetId;
	msg >> value.skillDataId;
	msg >> value.effectType;
	msg >> value.data;
}
void WriteGS2U_RoleEffect(stNetMsg& msg,GS2U_RoleEffect& value)
{
	WriteArray(msg,RoleEffectInfo,value.effects);
	msg.command(MSG_GS2U_RoleEffect);
}
void ReadGS2U_RoleEffect(stNetMsg& msg,GS2U_RoleEffect& value)
{
	ReadArray(msg,RoleEffectInfo,value.effects);
}
void WriteC2GS_RecoverLife_Req(stNetMsg& msg,C2GS_RecoverLife_Req& value)
{
	msg << value.recoverRuleId;
	msg.command(MSG_C2GS_RecoverLife_Req);
}
void C2GS_RecoverLife_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_RecoverLife_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_RecoverLife_Req(stNetMsg& msg,C2GS_RecoverLife_Req& value)
{
	msg >> value.recoverRuleId;
}
void WriteGS2C_RecoverLife_Ret(stNetMsg& msg,GS2C_RecoverLife_Ret& value)
{
	msg << value.retCode;
	msg << value.recoverCount;
	msg.command(MSG_GS2C_RecoverLife_Ret);
}
void ReadGS2C_RecoverLife_Ret(stNetMsg& msg,GS2C_RecoverLife_Ret& value)
{
	msg >> value.retCode;
	msg >> value.recoverCount;
}
void WriteC2GS_HelpRecover_Req(stNetMsg& msg,C2GS_HelpRecover_Req& value)
{
	msg << value.playerID;
	msg << value.state;
	msg.command(MSG_C2GS_HelpRecover_Req);
}
void C2GS_HelpRecover_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_HelpRecover_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_HelpRecover_Req(stNetMsg& msg,C2GS_HelpRecover_Req& value)
{
	msg >> value.playerID;
	msg >> value.state;
}
void WriteGS2C_HelpRecover_Ret(stNetMsg& msg,GS2C_HelpRecover_Ret& value)
{
	msg << value.state;
	msg << value.playerID;
	msg << value.restTime;
	msg << value.restPoint;
	msg << value.helpNum;
	msg.command(MSG_GS2C_HelpRecover_Ret);
}
void ReadGS2C_HelpRecover_Ret(stNetMsg& msg,GS2C_HelpRecover_Ret& value)
{
	msg >> value.state;
	msg >> value.playerID;
	msg >> value.restTime;
	msg >> value.restPoint;
	msg >> value.helpNum;
}
void WriteGS2U_BufferAttach(stNetMsg& msg,GS2U_BufferAttach& value)
{
	msg << value.id;
	msg << value.buffDataId;
	msg << value.duration;
	msg.command(MSG_GS2U_BufferAttach);
}
void ReadGS2U_BufferAttach(stNetMsg& msg,GS2U_BufferAttach& value)
{
	msg >> value.id;
	msg >> value.buffDataId;
	msg >> value.duration;
}
void WriteGS2U_BufferRemove(stNetMsg& msg,GS2U_BufferRemove& value)
{
	msg << value.id;
	msg.command(MSG_GS2U_BufferRemove);
}
void ReadGS2U_BufferRemove(stNetMsg& msg,GS2U_BufferRemove& value)
{
	msg >> value.id;
}
void WriteGS2C_KickOut(stNetMsg& msg,GS2C_KickOut& value)
{
	msg << value.type;
	msg << value.desc;
	msg.command(MSG_GS2C_KickOut);
}
void ReadGS2C_KickOut(stNetMsg& msg,GS2C_KickOut& value)
{
	msg >> value.type;
	msg >> value.desc;
}
void WriteC2GS_ChangePkState(stNetMsg& msg,C2GS_ChangePkState& value)
{
	msg << value.playerID;
	msg << value.pkState;
	msg.command(MSG_C2GS_ChangePkState);
}
void C2GS_ChangePkState::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ChangePkState(msg_s,*this);
	EndSend();
}
void ReadC2GS_ChangePkState(stNetMsg& msg,C2GS_ChangePkState& value)
{
	msg >> value.playerID;
	msg >> value.pkState;
}
void WriteC2GS_ReturnToSelectRoleDlg_Req(stNetMsg& msg,C2GS_ReturnToSelectRoleDlg_Req& value)
{
	msg.command(MSG_C2GS_ReturnToSelectRoleDlg_Req);
}
void C2GS_ReturnToSelectRoleDlg_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_ReturnToSelectRoleDlg_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_ReturnToSelectRoleDlg_Req(stNetMsg& msg,C2GS_ReturnToSelectRoleDlg_Req& value)
{
}
void WriteC2GS_PetUseSkill(stNetMsg& msg,C2GS_PetUseSkill& value)
{
	msg << value.petID;
	msg << value.skillId;
	msg << value.selfPosX;
	msg << value.selfPosY;
	msg << value.offsetX;
	msg << value.offsetY;
	msg << value.targetId;
	msg.command(MSG_C2GS_PetUseSkill);
}
void C2GS_PetUseSkill::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_PetUseSkill(msg_s,*this);
	EndSend();
}
void ReadC2GS_PetUseSkill(stNetMsg& msg,C2GS_PetUseSkill& value)
{
	msg >> value.petID;
	msg >> value.skillId;
	msg >> value.selfPosX;
	msg >> value.selfPosY;
	msg >> value.offsetX;
	msg >> value.offsetY;
	msg >> value.targetId;
}
void Writeskill_shortcut_config(stNetMsg& msg,skill_shortcut_config& value)
{
	msg << value.type;
	msg << value.index;
	msg << value.id;
}
void Readskill_shortcut_config(stNetMsg& msg,skill_shortcut_config& value)
{
	msg >> value.type;
	msg >> value.index;
	msg >> value.id;
}
void WriteC2GS_SkillShortCutConfig(stNetMsg& msg,C2GS_SkillShortCutConfig& value)
{
	WriteArray(msg,skill_shortcut_config,value.vec);
	msg.command(MSG_C2GS_SkillShortCutConfig);
}
void C2GS_SkillShortCutConfig::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SkillShortCutConfig(msg_s,*this);
	EndSend();
}
void ReadC2GS_SkillShortCutConfig(stNetMsg& msg,C2GS_SkillShortCutConfig& value)
{
	ReadArray(msg,skill_shortcut_config,value.vec);
}
void WriteGS2C_SkillShortCutConfig(stNetMsg& msg,GS2C_SkillShortCutConfig& value)
{
	WriteArray(msg,skill_shortcut_config,value.vec);
	msg.command(MSG_GS2C_SkillShortCutConfig);
}
void ReadGS2C_SkillShortCutConfig(stNetMsg& msg,GS2C_SkillShortCutConfig& value)
{
	ReadArray(msg,skill_shortcut_config,value.vec);
}
void WriteGS2C_WingInfo(stNetMsg& msg,GS2C_WingInfo& value)
{
	msg << value.wingIdVec;
	msg << value.equipWingId;
	msg.command(MSG_GS2C_WingInfo);
}
void ReadGS2C_WingInfo(stNetMsg& msg,GS2C_WingInfo& value)
{
	msg >> value.wingIdVec;
	msg >> value.equipWingId;
}
void WriteC2GS_SummonWing(stNetMsg& msg,C2GS_SummonWing& value)
{
	msg << value.wingId;
	msg.command(MSG_C2GS_SummonWing);
}
void C2GS_SummonWing::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_SummonWing(msg_s,*this);
	EndSend();
}
void ReadC2GS_SummonWing(stNetMsg& msg,C2GS_SummonWing& value)
{
	msg >> value.wingId;
}
void WriteGS2C_AddWing(stNetMsg& msg,GS2C_AddWing& value)
{
	msg << value.wingId;
	msg.command(MSG_GS2C_AddWing);
}
void ReadGS2C_AddWing(stNetMsg& msg,GS2C_AddWing& value)
{
	msg >> value.wingId;
}
void WriteC2GS_EquipWing(stNetMsg& msg,C2GS_EquipWing& value)
{
	msg << value.wingId;
	msg.command(MSG_C2GS_EquipWing);
}
void C2GS_EquipWing::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_EquipWing(msg_s,*this);
	EndSend();
}
void ReadC2GS_EquipWing(stNetMsg& msg,C2GS_EquipWing& value)
{
	msg >> value.wingId;
}
void WriteC2GS_UnEquipWing(stNetMsg& msg,C2GS_UnEquipWing& value)
{
	msg << value.wingId;
	msg.command(MSG_C2GS_UnEquipWing);
}
void C2GS_UnEquipWing::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_UnEquipWing(msg_s,*this);
	EndSend();
}
void ReadC2GS_UnEquipWing(stNetMsg& msg,C2GS_UnEquipWing& value)
{
	msg >> value.wingId;
}
void WriteC2GS_UpgradeWing(stNetMsg& msg,C2GS_UpgradeWing& value)
{
	msg << value.wingId;
	msg.command(MSG_C2GS_UpgradeWing);
}
void C2GS_UpgradeWing::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_UpgradeWing(msg_s,*this);
	EndSend();
}
void ReadC2GS_UpgradeWing(stNetMsg& msg,C2GS_UpgradeWing& value)
{
	msg >> value.wingId;
}
void WriteGS2C_ReplaceWing(stNetMsg& msg,GS2C_ReplaceWing& value)
{
	msg << value.oldWingId;
	msg << value.newWingId;
	msg.command(MSG_GS2C_ReplaceWing);
}
void ReadGS2C_ReplaceWing(stNetMsg& msg,GS2C_ReplaceWing& value)
{
	msg >> value.oldWingId;
	msg >> value.newWingId;
}
void WriteGS2C_PlayerFightingCapacityChange(stNetMsg& msg,GS2C_PlayerFightingCapacityChange& value)
{
	msg << value.eventId;
	msg << value.value;
	msg.command(MSG_GS2C_PlayerFightingCapacityChange);
}
void ReadGS2C_PlayerFightingCapacityChange(stNetMsg& msg,GS2C_PlayerFightingCapacityChange& value)
{
	msg >> value.eventId;
	msg >> value.value;
}
void WritehallTech(stNetMsg& msg,hallTech& value)
{
	msg << value.id;
	msg << value.lv;
	msg << value.nextLvTime;
}
void ReadhallTech(stNetMsg& msg,hallTech& value)
{
	msg >> value.id;
	msg >> value.lv;
	msg >> value.nextLvTime;
}
void WriteGS2C_HallTechOpenList(stNetMsg& msg,GS2C_HallTechOpenList& value)
{
	WriteArray(msg,hallTech,value.openList);
	msg.command(MSG_GS2C_HallTechOpenList);
}
void ReadGS2C_HallTechOpenList(stNetMsg& msg,GS2C_HallTechOpenList& value)
{
	ReadArray(msg,hallTech,value.openList);
}
void WriteC2GS_HallTechLvUp_Req(stNetMsg& msg,C2GS_HallTechLvUp_Req& value)
{
	msg << value.id;
	msg.command(MSG_C2GS_HallTechLvUp_Req);
}
void C2GS_HallTechLvUp_Req::Send(IOSocket* pIOSock){
	BeginSend();
	WriteC2GS_HallTechLvUp_Req(msg_s,*this);
	EndSend();
}
void ReadC2GS_HallTechLvUp_Req(stNetMsg& msg,C2GS_HallTechLvUp_Req& value)
{
	msg >> value.id;
}
void WriteGS2C_HallTechLvUp_Ret(stNetMsg& msg,GS2C_HallTechLvUp_Ret& value)
{
	msg << value.retCode;
	msg << value.id;
	msg << value.nextLvTime;
	msg.command(MSG_GS2C_HallTechLvUp_Ret);
}
void ReadGS2C_HallTechLvUp_Ret(stNetMsg& msg,GS2C_HallTechLvUp_Ret& value)
{
	msg >> value.retCode;
	msg >> value.id;
	msg >> value.nextLvTime;
}
void WriteGS2C_HallTechLvUp(stNetMsg& msg,GS2C_HallTechLvUp& value)
{
	msg << value.id;
	msg << value.lv;
	msg.command(MSG_GS2C_HallTechLvUp);
}
void ReadGS2C_HallTechLvUp(stNetMsg& msg,GS2C_HallTechLvUp& value)
{
	msg >> value.id;
	msg >> value.lv;
}

};


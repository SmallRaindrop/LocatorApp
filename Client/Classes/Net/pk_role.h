
#pragma  once 

#include <vector> 

#include "NetMsg.h" 

class IOSocket;

using namespace std;

namespace pk{

struct GS2C_PlayerSingleProperty
{
	int16 type;
	int64 value;
};
void WriteGS2C_PlayerSingleProperty(stNetMsg& msg,GS2C_PlayerSingleProperty& value);
bool OnGS2C_PlayerSingleProperty(GS2C_PlayerSingleProperty* value);
void ReadGS2C_PlayerSingleProperty(stNetMsg& msg,GS2C_PlayerSingleProperty& value);

struct GS2C_PlayerSinglePropertyStr
{
	int16 type;
	string value;
};
void WriteGS2C_PlayerSinglePropertyStr(stNetMsg& msg,GS2C_PlayerSinglePropertyStr& value);
bool OnGS2C_PlayerSinglePropertyStr(GS2C_PlayerSinglePropertyStr* value);
void ReadGS2C_PlayerSinglePropertyStr(stNetMsg& msg,GS2C_PlayerSinglePropertyStr& value);

struct GS2C_PlayerSinglePropertySync
{
	int64 playerID;
	int16 type;
	int64 value;
};
void WriteGS2C_PlayerSinglePropertySync(stNetMsg& msg,GS2C_PlayerSinglePropertySync& value);
bool OnGS2C_PlayerSinglePropertySync(GS2C_PlayerSinglePropertySync* value);
void ReadGS2C_PlayerSinglePropertySync(stNetMsg& msg,GS2C_PlayerSinglePropertySync& value);

struct GS2C_PlayerSinglePropertyStrSync
{
	int64 playerID;
	int16 type;
	string value;
};
void WriteGS2C_PlayerSinglePropertyStrSync(stNetMsg& msg,GS2C_PlayerSinglePropertyStrSync& value);
bool OnGS2C_PlayerSinglePropertyStrSync(GS2C_PlayerSinglePropertyStrSync* value);
void ReadGS2C_PlayerSinglePropertyStrSync(stNetMsg& msg,GS2C_PlayerSinglePropertyStrSync& value);

struct PlayerProperty
{
	int16 type;
	int64 value;
};
void WritePlayerProperty(stNetMsg& msg,PlayerProperty& value);
void ReadPlayerProperty(stNetMsg& msg,PlayerProperty& value);

struct GS2C_PlayerMultiplePropertySync
{
	int64 playerID;
	vector<PlayerProperty> playerProperties;
};
void WriteGS2C_PlayerMultiplePropertySync(stNetMsg& msg,GS2C_PlayerMultiplePropertySync& value);
bool OnGS2C_PlayerMultiplePropertySync(GS2C_PlayerMultiplePropertySync* value);
void ReadGS2C_PlayerMultiplePropertySync(stNetMsg& msg,GS2C_PlayerMultiplePropertySync& value);

struct GS2C_CdUseItem
{
	int32 id;
	int64 remainTime;
};
void WriteGS2C_CdUseItem(stNetMsg& msg,GS2C_CdUseItem& value);
bool OnGS2C_CdUseItem(GS2C_CdUseItem* value);
void ReadGS2C_CdUseItem(stNetMsg& msg,GS2C_CdUseItem& value);

struct PlayerBuffInfo
{
	int64 id;
	int32 buffDataId;
	int32 duration;
};
void WritePlayerBuffInfo(stNetMsg& msg,PlayerBuffInfo& value);
void ReadPlayerBuffInfo(stNetMsg& msg,PlayerBuffInfo& value);

struct PlayerSkillInfo
{
	int16 skillId;
	int16 level;
	int16 cdtime;
};
void WritePlayerSkillInfo(stNetMsg& msg,PlayerSkillInfo& value);
void ReadPlayerSkillInfo(stNetMsg& msg,PlayerSkillInfo& value);

struct GS2C_PlayerProperty
{
	int64 playerID;
	string name;
	int32 level;
	int8 career;
	int64 exp;
	int64 bindCoin;
	int32 treasure;
	int32 bindTreasure;
	int32 fight;
	vector<GS2C_CdUseItem> cdTimeUseItem;
	int8 bagGridNum;
	int8 vipLevel;
	int32 totalTreasure;
	int16 titleId;
	int64 hp;
	int32 mp;
	int8 recoverCount;
	int16 manufactureSize;
	vector<PlayerBuffInfo> buff_list;
	vector<PlayerSkillInfo> skill_list;
	int32 state;
	int32 pk;
	int8 pkState;
	int32 phy_dam;
	int32 fire_dam;
	int32 code_dam;
	int32 elec_dam;
	int32 toxin_dam;
	int16 base_dam_increase;
	int32 all_dam_increase;
	int32 all_dam_reduce;
	int32 atk_power;
	int64 hp_max;
	int32 hp_r;
	int32 hp_rp;
	int32 by_cure_factor;
	int32 mp_max;
	int32 mp_r;
	int16 speed;
	int32 armor;
	int16 phy_res;
	int16 fire_res;
	int16 cold_res;
	int16 elec_res;
	int16 toxin_res;
	int16 tough;
	int16 penetrate;
	int16 thickness;
	int32 crit_p;
	int32 crit_hurt;
	int32 accurate_p;
	int32 dodge_p;
	int32 trigger_p;
	int16 atk_speed_increase;
	int16 mp_efficiency;
	int16 skill_duration;
	int32 skill_power;
	int16 skill_rang;
	int32 hp_ball;
	int32 mp_ball;
	int16 armor_reduce;
};
void WriteGS2C_PlayerProperty(stNetMsg& msg,GS2C_PlayerProperty& value);
bool OnGS2C_PlayerProperty(GS2C_PlayerProperty* value);
void ReadGS2C_PlayerProperty(stNetMsg& msg,GS2C_PlayerProperty& value);

struct GS2C_PlayerFightProperty
{
	int32 state;
	int64 hp;
	int32 mp;
	int32 phy_dam;
	int32 fire_dam;
	int32 code_dam;
	int32 elec_dam;
	int32 toxin_dam;
	int16 base_dam_increase;
	int32 all_dam_increase;
	int32 all_dam_reduce;
	int32 atk_power;
	int64 hp_max;
	int32 hp_r;
	int32 hp_rp;
	int32 by_cure_factor;
	int32 mp_max;
	int32 mp_r;
	int16 speed;
	int32 armor;
	int16 phy_res;
	int16 fire_res;
	int16 cold_res;
	int16 elec_res;
	int16 toxin_res;
	int16 tough;
	int16 penetrate;
	int16 thickness;
	int32 crit_p;
	int32 crit_hurt;
	int32 accurate_p;
	int32 dodge_p;
	int32 trigger_p;
	int16 atk_speed_increase;
	int16 mp_efficiency;
	int16 skill_duration;
	int32 skill_power;
	int16 skill_rang;
	int32 hp_ball;
	int32 mp_ball;
	int16 armor_reduce;
};
void WriteGS2C_PlayerFightProperty(stNetMsg& msg,GS2C_PlayerFightProperty& value);
bool OnGS2C_PlayerFightProperty(GS2C_PlayerFightProperty* value);
void ReadGS2C_PlayerFightProperty(stNetMsg& msg,GS2C_PlayerFightProperty& value);

struct GS2U_AddSkillList
{
	vector<PlayerSkillInfo> skill_list;
};
void WriteGS2U_AddSkillList(stNetMsg& msg,GS2U_AddSkillList& value);
bool OnGS2U_AddSkillList(GS2U_AddSkillList* value);
void ReadGS2U_AddSkillList(stNetMsg& msg,GS2U_AddSkillList& value);

struct GS2U_RemoveSkillList
{
	vector<int16> skill_id_list;
};
void WriteGS2U_RemoveSkillList(stNetMsg& msg,GS2U_RemoveSkillList& value);
bool OnGS2U_RemoveSkillList(GS2U_RemoveSkillList* value);
void ReadGS2U_RemoveSkillList(stNetMsg& msg,GS2U_RemoveSkillList& value);

struct GS2U_LevelChangeSkillList
{
	vector<PlayerSkillInfo> skill_list;
};
void WriteGS2U_LevelChangeSkillList(stNetMsg& msg,GS2U_LevelChangeSkillList& value);
bool OnGS2U_LevelChangeSkillList(GS2U_LevelChangeSkillList* value);
void ReadGS2U_LevelChangeSkillList(stNetMsg& msg,GS2U_LevelChangeSkillList& value);

struct C2GS_UseSkill
{
	int16 skillId;
	int16 selfPosX;
	int16 selfPosY;
	int16 offsetX;
	int16 offsetY;
	int64 targetId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_UseSkill(stNetMsg& msg,C2GS_UseSkill& value);
void ReadC2GS_UseSkill(stNetMsg& msg,C2GS_UseSkill& value);

struct GS2U_UseSkill
{
	int64 casterId;
	int16 offsetX;
	int16 offsetY;
	int64 targetId;
	int16 skillId;
};
void WriteGS2U_UseSkill(stNetMsg& msg,GS2U_UseSkill& value);
bool OnGS2U_UseSkill(GS2U_UseSkill* value);
void ReadGS2U_UseSkill(stNetMsg& msg,GS2U_UseSkill& value);

struct GS2U_UseTransferSkill
{
	int64 casterId;
	int64 targetId;
	int16 skillId;
	int16 transferDesX;
	int16 transferDesY;
};
void WriteGS2U_UseTransferSkill(stNetMsg& msg,GS2U_UseTransferSkill& value);
bool OnGS2U_UseTransferSkill(GS2U_UseTransferSkill* value);
void ReadGS2U_UseTransferSkill(stNetMsg& msg,GS2U_UseTransferSkill& value);

struct GS2C_NextAttack_Is_GongSha
{
	int8 reserve;
};
void WriteGS2C_NextAttack_Is_GongSha(stNetMsg& msg,GS2C_NextAttack_Is_GongSha& value);
bool OnGS2C_NextAttack_Is_GongSha(GS2C_NextAttack_Is_GongSha* value);
void ReadGS2C_NextAttack_Is_GongSha(stNetMsg& msg,GS2C_NextAttack_Is_GongSha& value);

struct RoleEffectInfo
{
	int64 castId;
	int64 targetId;
	int32 skillDataId;
	int32 effectType;
	int64 data;
};
void WriteRoleEffectInfo(stNetMsg& msg,RoleEffectInfo& value);
void ReadRoleEffectInfo(stNetMsg& msg,RoleEffectInfo& value);

struct GS2U_RoleEffect
{
	vector<RoleEffectInfo> effects;
};
void WriteGS2U_RoleEffect(stNetMsg& msg,GS2U_RoleEffect& value);
bool OnGS2U_RoleEffect(GS2U_RoleEffect* value);
void ReadGS2U_RoleEffect(stNetMsg& msg,GS2U_RoleEffect& value);

struct C2GS_RecoverLife_Req
{
	int16 recoverRuleId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_RecoverLife_Req(stNetMsg& msg,C2GS_RecoverLife_Req& value);
void ReadC2GS_RecoverLife_Req(stNetMsg& msg,C2GS_RecoverLife_Req& value);

struct GS2C_RecoverLife_Ret
{
	int16 retCode;
	int8 recoverCount;
};
void WriteGS2C_RecoverLife_Ret(stNetMsg& msg,GS2C_RecoverLife_Ret& value);
bool OnGS2C_RecoverLife_Ret(GS2C_RecoverLife_Ret* value);
void ReadGS2C_RecoverLife_Ret(stNetMsg& msg,GS2C_RecoverLife_Ret& value);

struct C2GS_HelpRecover_Req
{
	int64 playerID;
	int8 state;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_HelpRecover_Req(stNetMsg& msg,C2GS_HelpRecover_Req& value);
void ReadC2GS_HelpRecover_Req(stNetMsg& msg,C2GS_HelpRecover_Req& value);

struct GS2C_HelpRecover_Ret
{
	int8 state;
	int64 playerID;
	int16 restTime;
	int16 restPoint;
	int8 helpNum;
};
void WriteGS2C_HelpRecover_Ret(stNetMsg& msg,GS2C_HelpRecover_Ret& value);
bool OnGS2C_HelpRecover_Ret(GS2C_HelpRecover_Ret* value);
void ReadGS2C_HelpRecover_Ret(stNetMsg& msg,GS2C_HelpRecover_Ret& value);

struct GS2U_BufferAttach
{
	int64 id;
	int32 buffDataId;
	int32 duration;
};
void WriteGS2U_BufferAttach(stNetMsg& msg,GS2U_BufferAttach& value);
bool OnGS2U_BufferAttach(GS2U_BufferAttach* value);
void ReadGS2U_BufferAttach(stNetMsg& msg,GS2U_BufferAttach& value);

struct GS2U_BufferRemove
{
	int64 id;
};
void WriteGS2U_BufferRemove(stNetMsg& msg,GS2U_BufferRemove& value);
bool OnGS2U_BufferRemove(GS2U_BufferRemove* value);
void ReadGS2U_BufferRemove(stNetMsg& msg,GS2U_BufferRemove& value);

struct GS2C_KickOut
{
	int32 type;
	string desc;
};
void WriteGS2C_KickOut(stNetMsg& msg,GS2C_KickOut& value);
bool OnGS2C_KickOut(GS2C_KickOut* value);
void ReadGS2C_KickOut(stNetMsg& msg,GS2C_KickOut& value);

struct C2GS_ChangePkState
{
	int64 playerID;
	int8 pkState;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ChangePkState(stNetMsg& msg,C2GS_ChangePkState& value);
void ReadC2GS_ChangePkState(stNetMsg& msg,C2GS_ChangePkState& value);

struct C2GS_ReturnToSelectRoleDlg_Req
{
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_ReturnToSelectRoleDlg_Req(stNetMsg& msg,C2GS_ReturnToSelectRoleDlg_Req& value);
void ReadC2GS_ReturnToSelectRoleDlg_Req(stNetMsg& msg,C2GS_ReturnToSelectRoleDlg_Req& value);

struct C2GS_PetUseSkill
{
	int64 petID;
	int16 skillId;
	int16 selfPosX;
	int16 selfPosY;
	int16 offsetX;
	int16 offsetY;
	int64 targetId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_PetUseSkill(stNetMsg& msg,C2GS_PetUseSkill& value);
void ReadC2GS_PetUseSkill(stNetMsg& msg,C2GS_PetUseSkill& value);

struct skill_shortcut_config
{
	int8 type;
	int8 index;
	int64 id;
};
void Writeskill_shortcut_config(stNetMsg& msg,skill_shortcut_config& value);
void Readskill_shortcut_config(stNetMsg& msg,skill_shortcut_config& value);

struct C2GS_SkillShortCutConfig
{
	vector<skill_shortcut_config> vec;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SkillShortCutConfig(stNetMsg& msg,C2GS_SkillShortCutConfig& value);
void ReadC2GS_SkillShortCutConfig(stNetMsg& msg,C2GS_SkillShortCutConfig& value);

struct GS2C_SkillShortCutConfig
{
	vector<skill_shortcut_config> vec;
};
void WriteGS2C_SkillShortCutConfig(stNetMsg& msg,GS2C_SkillShortCutConfig& value);
bool OnGS2C_SkillShortCutConfig(GS2C_SkillShortCutConfig* value);
void ReadGS2C_SkillShortCutConfig(stNetMsg& msg,GS2C_SkillShortCutConfig& value);

struct GS2C_WingInfo
{
	vector<int32> wingIdVec;
	int32 equipWingId;
};
void WriteGS2C_WingInfo(stNetMsg& msg,GS2C_WingInfo& value);
bool OnGS2C_WingInfo(GS2C_WingInfo* value);
void ReadGS2C_WingInfo(stNetMsg& msg,GS2C_WingInfo& value);

struct C2GS_SummonWing
{
	int32 wingId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_SummonWing(stNetMsg& msg,C2GS_SummonWing& value);
void ReadC2GS_SummonWing(stNetMsg& msg,C2GS_SummonWing& value);

struct GS2C_AddWing
{
	int32 wingId;
};
void WriteGS2C_AddWing(stNetMsg& msg,GS2C_AddWing& value);
bool OnGS2C_AddWing(GS2C_AddWing* value);
void ReadGS2C_AddWing(stNetMsg& msg,GS2C_AddWing& value);

struct C2GS_EquipWing
{
	int32 wingId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_EquipWing(stNetMsg& msg,C2GS_EquipWing& value);
void ReadC2GS_EquipWing(stNetMsg& msg,C2GS_EquipWing& value);

struct C2GS_UnEquipWing
{
	int32 wingId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_UnEquipWing(stNetMsg& msg,C2GS_UnEquipWing& value);
void ReadC2GS_UnEquipWing(stNetMsg& msg,C2GS_UnEquipWing& value);

struct C2GS_UpgradeWing
{
	int32 wingId;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_UpgradeWing(stNetMsg& msg,C2GS_UpgradeWing& value);
void ReadC2GS_UpgradeWing(stNetMsg& msg,C2GS_UpgradeWing& value);

struct GS2C_ReplaceWing
{
	int32 oldWingId;
	int32 newWingId;
};
void WriteGS2C_ReplaceWing(stNetMsg& msg,GS2C_ReplaceWing& value);
bool OnGS2C_ReplaceWing(GS2C_ReplaceWing* value);
void ReadGS2C_ReplaceWing(stNetMsg& msg,GS2C_ReplaceWing& value);

struct GS2C_PlayerFightingCapacityChange
{
	int8 eventId;
	int32 value;
};
void WriteGS2C_PlayerFightingCapacityChange(stNetMsg& msg,GS2C_PlayerFightingCapacityChange& value);
bool OnGS2C_PlayerFightingCapacityChange(GS2C_PlayerFightingCapacityChange* value);
void ReadGS2C_PlayerFightingCapacityChange(stNetMsg& msg,GS2C_PlayerFightingCapacityChange& value);

struct hallTech
{
	int16 id;
	int8 lv;
	int32 nextLvTime;
};
void WritehallTech(stNetMsg& msg,hallTech& value);
void ReadhallTech(stNetMsg& msg,hallTech& value);

struct GS2C_HallTechOpenList
{
	vector<hallTech> openList;
};
void WriteGS2C_HallTechOpenList(stNetMsg& msg,GS2C_HallTechOpenList& value);
bool OnGS2C_HallTechOpenList(GS2C_HallTechOpenList* value);
void ReadGS2C_HallTechOpenList(stNetMsg& msg,GS2C_HallTechOpenList& value);

struct C2GS_HallTechLvUp_Req
{
	int16 id;
	void Send(IOSocket* pIOSock);
};
void WriteC2GS_HallTechLvUp_Req(stNetMsg& msg,C2GS_HallTechLvUp_Req& value);
void ReadC2GS_HallTechLvUp_Req(stNetMsg& msg,C2GS_HallTechLvUp_Req& value);

struct GS2C_HallTechLvUp_Ret
{
	int8 retCode;
	int16 id;
	int32 nextLvTime;
};
void WriteGS2C_HallTechLvUp_Ret(stNetMsg& msg,GS2C_HallTechLvUp_Ret& value);
bool OnGS2C_HallTechLvUp_Ret(GS2C_HallTechLvUp_Ret* value);
void ReadGS2C_HallTechLvUp_Ret(stNetMsg& msg,GS2C_HallTechLvUp_Ret& value);

struct GS2C_HallTechLvUp
{
	int16 id;
	int8 lv;
};
void WriteGS2C_HallTechLvUp(stNetMsg& msg,GS2C_HallTechLvUp& value);
bool OnGS2C_HallTechLvUp(GS2C_HallTechLvUp* value);
void ReadGS2C_HallTechLvUp(stNetMsg& msg,GS2C_HallTechLvUp& value);


};


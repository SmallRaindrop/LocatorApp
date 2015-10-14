#ifndef __GameDataManager_h_
#define __GameDataManager_h_

#include "GameDef.h"
#include "db.h"
#include "cfgTable.h"
#include "Singleton.h"

class GameDataManager : public Singleton_Auto<GameDataManager>
{
public:
	GameDataManager();
	~GameDataManager();

	bool LoadConfigs();

public:
	CCfgTable<GameProcCfg>			GameProcTable;
	CCfgTable<PlayerBaseCfg>		PlayerBaseTable;
	CCfgTable<PlayerExpCfg>			PlayerExpTable;
	CCfgTable<NpcCfg>				NpcCfgTable;
	CCfgTable<Npc_functionCfg>		NpcFuncsTable;
	CCfgTable<MapCfg>				MapCfgTable;
	CCfgTable<ItemCfg>				ItemCfgTable;
	CCfgTable<EquipBaseCfg>			EquipBaseTable;
	CCfgTable<EquipmenthardCfg>		EquipmenthardTable;
	CCfgTable<EquipmenthiddenCfg>	EquipmenthiddenTable;
	CCfgTable<EquipRandomCfg>		EquipRandomTable;
	CCfgTable<EquipComposeCfg>		EquipComposeTable;
	CCfgTable<EquipUpgradeCfg>		EquipUpgradeTable;
	CCfgTable<SkillCfg>				SkillCfgTable;
	CCfgTable<BulletCfg>			BulletCfgTable;
	CCfgTable<ChatCfg>				ChatCfgTable;
	CCfgTable<GameStringCfg>		GameStringCfgTable;
	CCfgTable<BagGridCfg>			BagGridCfgTable;
	CCfgTable<CommonCfg>			CommonTable;
	CCfgTable<MonsterBaseCfg>		MonsterBaseTable;
	CCfgTable<TaskCfg>				TaskTable;
	CCfgTable<RecoverLifeRuleCfg>	RecoverLifeRuleTable;
	CCfgTable<SalebankCfg>			SalebankTable;
	CCfgTable<GatewayCfg>			GatewayTable;
	CCfgTable<AudioCfg>				AudioTable;
	CCfgTable<AutofightCfg>			AutoFightTable;
	CCfgTable<RandomNameCfg>		RandomNameTable;
	CCfgTable<Active_wuziCfg>		Chess5Table;
	CCfgTable<Copy_stepCfg>			CopyStepTable;
	CCfgTable<Active_battleCfg>		BattleTable;
	CCfgTable<BuffCfg>				BuffTable;
	CCfgTable<AchievementCfg>		AchievementTable;
	CCfgTable<QuestionCfg>			QuestionTable;
	CCfgTable<GuideCfg>				GuideTable;
	CCfgTable<MonsterGenerateCfg>	MonsterGenerateTable;
	CCfgTable<ActiveCenterCfg>		ActivityCenterTable;
	CCfgTable<LevelawardCfg>		LevelawardTable;
	CCfgTable<LoginawardCfg>		LoginawardTable;
	CCfgTable<WingCfg>				WingTable;
	CCfgTable<PortableShopCfg>		PortableShopTable;
	CCfgTable<DramaCfg>             DramaTable;
	CCfgTable<WorldmapCfg>          WorldmapTable;
	CCfgTable<LocaleCfg>            LocaleTable;
	CCfgTable<AttributeInfoCfg>     AttributeInfoTable;	
	CCfgTable<EquipRefineBonusCfg>  EquipRefineBonusTable;  // liyang 2015/9/7	装备精炼属性配置表
	CCfgTable<EquipRefineCostCfg>	EquipRefineCostTable;   // liyang 2015/9/8	装备精炼消耗配置表
	CCfgTable<One_strokeCfg>		OneStrokeTable;
	CCfgTable<Open_lockCfg>			OpenLockTable;
	CCfgTable<BluePrintCfg>         BluePrintTable;
	CCfgTable<ChestCfg>				ChestsTable;				//宝箱
	CCfgTable<HallTechCfg>			HallTechTable;				//战舰
	CCfgTable<PetBaseCfg>			PetBaseTable;			// liyang 2015/9/28	宠物配置表
};

#define gGameData			GameDataManager::Instance()
#define GameProcData		gGameData->GameProcTable
#define PlayerBaseData		gGameData->PlayerBaseTable
#define PlayerExpData		gGameData->PlayerExpTable
#define NpcCfgData			gGameData->NpcCfgTable
#define NpcFuncsData		gGameData->NpcFuncsTable
#define MapData				gGameData->MapCfgTable
#define ItemData			gGameData->ItemCfgTable
#define EquipBaseData		gGameData->EquipBaseTable
#define EquipmenthardData	gGameData->EquipmenthardTable
#define EquipmenthiddenData	gGameData->EquipmenthiddenTable
#define EquipRandomData		gGameData->EquipRandomTable
#define EquipComposeData	gGameData->EquipComposeTable
#define SkillData			gGameData->SkillCfgTable
#define BulletData			gGameData->BulletCfgTable
#define ChatData			gGameData->ChatCfgTable
#define GameString			gGameData->GameStringCfgTable
#define MonsterBaseData		gGameData->MonsterBaseTable
#define BagGridData			gGameData->BagGridCfgTable
#define EquipUpgradeData	gGameData->EquipUpgradeTable
#define CommoneData			gGameData->CommonTable
#define TaskData			gGameData->TaskTable
#define RecoverLifeRuleData	gGameData->RecoverLifeRuleTable
#define SalebankData		gGameData->SalebankTable
#define GatewayData			gGameData->GatewayTable
#define AudioData			gGameData->AudioTable
#define AutoFightData		gGameData->AutoFightTable
#define RandomNameData		gGameData->RandomNameTable
#define Chess5Data			gGameData->Chess5Table
#define CopyStepData		gGameData->CopyStepTable
#define BattleData			gGameData->BattleTable
#define BuffData			gGameData->BuffTable
#define AchievementData		gGameData->AchievementTable
#define QuestionData		gGameData->QuestionTable
#define GuideData			gGameData->GuideTable
#define MonsterGenerateData	gGameData->MonsterGenerateTable
#define ActivityCenterData	gGameData->ActivityCenterTable
#define LevelAwardData		gGameData->LevelawardTable
#define LoginAwardData		gGameData->LoginawardTable
#define WingData			gGameData->WingTable
#define PortableShopData	gGameData->PortableShopTable
#define DramaTableData      gGameData->DramaTable
#define WorldmapTableData   gGameData->WorldmapTable
#define LocaleTableData     gGameData->LocaleTable
#define AttributeTableData  gGameData->AttributeInfoTable
#define EquipRefineBonusData  gGameData->EquipRefineBonusTable	 // liyang 2015/9/7  装备精炼属性配置表
#define EquipRefineCostData  gGameData->EquipRefineCostTable	 // liyang 2015/9/8  装备精炼消耗配置表
#define OneStrokeData		gGameData->OneStrokeTable
#define OpenLockData		gGameData->OpenLockTable
#define BluePrintData       gGameData->BluePrintTable
#define ChestsData			gGameData->ChestsTable
#define HallTechData		gGameData->HallTechTable			//liyang 2015/9/24  战舰配置表
#define PetBaseData			gGameData->PetBaseTable				//liyang 2015/9/28  宠物配置表

#endif // !__GameDataManager_h_

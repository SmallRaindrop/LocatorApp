#include "GameDataManager.h"
#include "Log.h"

GameDataManager::GameDataManager()
{

}

GameDataManager::~GameDataManager()
{

}

bool GameDataManager::LoadConfigs()
{
	LOGI(" loading game config data start ... ");
	Data ret;
	ret = gFileUtils->getDataFromFile("assets/data/gameProc.bin");
	if ( ret.isNull() || !GameProcTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/gameProc.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/gameProc.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/playerBase.bin");
	if ( ret.isNull() || !PlayerBaseTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/playerBase.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/playerBase.bin ok.");
	
	ret = gFileUtils->getDataFromFile("assets/data/playerExp.bin");
	if ( ret.isNull() || !PlayerExpTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/playerExp.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/playerExp.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/npc.bin");
	if ( ret.isNull() || !NpcCfgTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/npc.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/npc.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/npc_function.bin");
	if ( ret.isNull() || !NpcFuncsTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/npc_function.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/npc_function.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/map.bin");
	if ( ret.isNull() || !MapCfgTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/map.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/map.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/equipBase.bin");
	if ( ret.isNull() || !EquipBaseTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/equipBase.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/equipBase.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/item.bin");
	if ( ret.isNull() || !ItemCfgTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/item.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/item.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/skill.bin");
	if ( ret.isNull() || !SkillCfgTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/skill.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/skill.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/bullet.bin");
	if ( ret.isNull() || !BulletCfgTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/bullet.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/bullet.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/buff.bin");
	if ( ret.isNull() || !BuffTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/buff.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/buff.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/drama.bin");
	if ( ret.isNull() || !DramaTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/drama.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/drama.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/attributeInfo.bin");
	if ( ret.isNull() || !AttributeInfoTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/attributeInfo.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/attributeInfo.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/monsterBase.bin");
	if ( ret.isNull() || !MonsterBaseTable.load(ret.getBytes(),ret.getSize()))
	{
		LOGE("loading assets/data/monsterBase.bin failed.");
	}
	ret.clear();
	LOGI(" loading assets/data/monsterBase.bin ok.");

	ret = gFileUtils->getDataFromFile("assets/data/equipmenthard.bin");
	if ( ret.isNull() || !EquipmenthardTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/equipmenthard.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/equipmenthidden.bin");
	if ( ret.isNull() || !EquipmenthiddenTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/equipmenthidden.bin failed.");
	}
	ret.clear();
	CCLOG("GameDataManager::initialize -------------5 ");
	ret = gFileUtils->getDataFromFile("assets/data/equipRandom.bin");
	if ( ret.isNull() || !EquipRandomTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/equipRandom.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/equipCompose.bin");
	if ( ret.isNull() || !EquipComposeTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/equipCompose.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/equipUpgrade.bin");
	if ( ret.isNull() || !EquipUpgradeTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/equipUpgrade.bin failed.");
	}
	ret.clear();

	ret = gFileUtils->getDataFromFile("assets/data/chat.bin");
	if ( ret.isNull() || !ChatCfgTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/chat.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/gameString.bin");
	if ( ret.isNull() || !GameStringCfgTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/gameString.bin failed.");
	}
	ret.clear();

	ret = gFileUtils->getDataFromFile("assets/data/bagGrid.bin");
	if ( ret.isNull() || !BagGridCfgTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/bagGrid.bin failed.");
	}
	ret.clear();
	CCLOG("GameDataManager::initialize -------------9 ");
	ret = gFileUtils->getDataFromFile("assets/data/common.bin");
	if ( ret.isNull() || !CommonTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/common.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/task.bin");
	if ( ret.isNull() || !TaskTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/task.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/recoverLifeRule.bin");
	if ( ret.isNull() || !RecoverLifeRuleTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/recoverLifeRule.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/salebank.bin");
	if ( ret.isNull() || !SalebankTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/salebank.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/gateway.bin");
	if ( ret.isNull() || !GatewayTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/gateway.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/audio.bin");
	if ( ret.isNull() || !AudioTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/audio.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/autofight.bin");
	if ( ret.isNull() || !AutoFightTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/aotofight.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/randomName.bin");
	if ( ret.isNull() || !RandomNameTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/randomName.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/active_wuzi.bin");
	if ( ret.isNull() || !Chess5Table.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/active_wuzi.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/copy_step.bin");
	if ( ret.isNull() || !CopyStepTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/copy_step.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/active_battle.bin");
	if ( ret.isNull() || !BattleTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/active_battle.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/achievement.bin");
	if ( ret.isNull() || !AchievementTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/achievement.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/question.bin");
	if ( ret.isNull() || !QuestionTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/question.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/guide.bin");
	if ( ret.isNull() || !GuideTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/guide.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/monsterGenerate.bin");
	if ( ret.isNull() || !MonsterGenerateTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/monsterGenerate.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/activeCenter.bin");
	if ( ret.isNull() || !ActivityCenterTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/activeCenter.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/levelaward.bin");
	if ( ret.isNull() || !LevelawardTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/levelaward.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/loginaward.bin");
	if ( ret.isNull() || !LoginawardTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/loginaward.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/wing.bin");
	if ( ret.isNull() || !WingTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/wing.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/portableShop.bin");
	if ( ret.isNull() || !PortableShopTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/portableShop.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/worldmap.bin");
	if ( ret.isNull() || !WorldmapTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/worldmap.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/locale.bin");
	if ( ret.isNull() || !LocaleTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/locale.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/equipRefineBonus.bin");
	if ( ret.isNull() || !EquipRefineBonusTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/equipRefineBonus.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/equipRefineCost.bin");
	if ( ret.isNull() || !EquipRefineCostTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/equipRefineCost.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/one_stroke.bin");
	if ( ret.isNull() || !OneStrokeTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/one_stroke.bin failed.");
	}
	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/open_lock.bin");
	if ( ret.isNull() || !OpenLockTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/open_lock.bin failed.");
	}

	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/bluePrint.bin");
	if ( ret.isNull() || !BluePrintTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/bluePrint.bin failed.");
	}

	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/chest.bin");
	if ( ret.isNull() || !ChestsTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/chest.bin failed.");
	}

	ret.clear();
	ret = gFileUtils->getDataFromFile("assets/data/hallTech.bin");
	if ( ret.isNull() || !HallTechTable.load(ret.getBytes(),ret.getSize()))
	{
		CCLOG("load assets/data/hallTech.bin failed.");
	}
	LOGI(" loading game config data complete. ");

	return true;
}


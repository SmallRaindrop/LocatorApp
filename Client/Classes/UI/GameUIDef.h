#ifndef __GameUIDef_h_
#define __GameUIDef_h_

/* 5 3 2 2 1 1*/
#define BAG_SIZE_EQUIP		(64)		//背包装备格子数
#define BAG_SIZE_ZAWU		(64)		//背包杂物格子数
#define BAG_SIZE_MATERIAL	(64)		//背包材料格子数
#define BAG_SIZE_TUZHI	    (64)		//背包图纸格子数
#define BAG_SIZE_TIANSHU	(64)		//背包天书格子数
#define GRIDS_SIZE_MAILSEND (4)			//邮件格子数
#define GRIDS_SIZE_FURNACECOMPOUND (3)	//装备合成格子数
#define GRIDS_SIZE_ROLE		(11)		//角色装备格子数
#define GRIDS_SIZE_TASK		(5)			//任务格子数
#define GRIDS_SIZE_TRADE	(5)			//交易格子数
#define GRIDS_SIZE_SALEBANK_PROP	(5) //寄售道具
#define GRIDS_SIZE_SALEBANK_MINE	(5) //寄售道具
#define GRIDS_SIZE_SALEBANK_GOLD	(10)//寄售元宝

#define BAG_SIZE_EQUIPACTIVE	(32)
#define BAG_SIZE_ZAWUACTIVE		(16)
#define BAG_SIZE_MATERIALACTIVE	(16)

#define	BAG_PAGE_SIZE				(16)
#define MAX_PAGE_SIZE				(5)
#define Page_Size_CopyCheckOut		(10)

enum emGridsType
{
	emGrids_None,
	emGrids_BagEquip,
	emGrids_BagZaWu,
	emGrids_BagMaterial,
	emGrids_BagTuZi,
	emGrids_BagBook,
	emGrids_Role,
	emGrids_StrengthMaterial,
	emGrids_TaskAward,
	emGrids_BagEquipRole, //add Tangbo  主要存在人物装备界面
	emGrids_CopyCheckout, //副本结算
	emGrids_Count	// 加在此项前面！！！
};

enum emGUIS{
	GUIS_NONE,
	GUIS_SHOW,
	GUIS_OPEN,
	GUIS_CLOSED,
};

//格子标记
#define GRIDICON_TAG	(1)

//ui设计分辨率
#define GAME_UI_ORIG_SIZE Size(1920, 1080)	//old
#define UI_ORIG_SIZE Size(1334, 750)	//new

/************************************************************************/
/* ui json 文件路径                                                     */
/************************************************************************/
#define JSONFILE_LOGIN				"assets/ui/LoginUI.json"
#define JSONFILE_MESSAGEBOXUI		"assets/ui/MessageBoxUI.json"
#define JSONFILE_CHATMAINUI			"assets/ui/ChatMainUI.json"
#define JSONFILE_CTeamUI				"assets/ui/CTeamUI.json"
#define JSONFILE_TEAMAPPLICATION	"assets/ui/TeamApplicationList.json"
#define JSONFILE_NPCDIALOG			"assets/ui/NpcDialog.json"
#define JSONFILE_TASKUI				"assets/ui/TaskUI.json"
#define JSONFILE_TASKDIALOG			"assets/ui/TaskDialog.json"
#define JSONFILE_RELIVE				"assets/ui/Revive.json"
#define JSONFILE_SERVERLIST			"assets/ui/SelectServerUI.json"
#define JSONFILE_CREATEPLAYER		"assets/ui/CreateHeroUI.json"
#define JSONFILE_SELECTPLAYER		"assets/ui/SelectHeroUI.json"
#define JsonFile_MainUINormal		"assets/ui/MainUINormal.json"
#define JsonFile_MainUIFight		"assets/ui/MainUIFight.json"
#define JsonFile_FightPause			"assets/ui/FightPause.json"
#define JsonFile_HeroInfo			"assets/ui/HeroInfo.json"
#define JsonFile_Social				"assets/ui/SocialUI.json"
#define JsonFile_WaveEnd			"assets/ui/CopyWaveEnd.json"
#define JsonFile_CopyEnd			"assets/ui/CopyEnd.json"
#define JsonFile_MailUI				"assets/ui/MailUI.json"
#define JSONFILE_WORLDMAPUI			"assets/ui/WorldMap.json"
#define JSONFILE_LOADUI             "assets/ui/LoadingUI.json"
#define JSONFILE_DRAMAUI            "assets/ui/DramaUI.json"
#define JSONFILE_FRIENDUI			"assets/ui/FriendsUI.json"
#define JSONFILE_FRICHILD			"assets/ui/ChildNode.json"
#define JSONFILE_ROLEATTRI          "assets/ui/RoleAttriUI.json"
#define JSONFILE_ROLEPACKAGE        "assets/ui/RolePackageUI.json"
#define JSONFILE_ROLEEATTRICHILD    "assets/ui/DetailChild.json"
#define JsonFile_MissionUI			"assets/ui/MissionUI.json"
#define JsonFile_SkyBookUI          "assets/ui/SkyBookUI.json"
#define JsonFile_SkyBookCalcUI      "assets/ui/SkyBookCalcUI.json"
#define JsonFile_GodDeviceUI		"assets/ui/GodDeviceUI.json"
#define JsonFile_StrengthenUI		"assets/ui/StrengthenUI.json"
#define JsonFile_ManufactureUI      "assets/ui/ManufactureUI.json"
#define JsonFile_ManufactureJiDuUI  "assets/ui/ManufactureJuDuTipsUI.json"
#define JsonFile_ManufactureMaterial "assets/ui/ManufactureMaterialTipsUI.json"
#define JsonFile_OneStrokeUI		"assets/ui/OneStroke.json"
#define JsonFile_OpenLockUI			"assets/ui/OpenLock.json"
#define JsonFile_ReviveUI			"assets/ui/ReviveUI.json"
#define JsonFile_ItemTipsUI         "assets/ui/ItemTipsUI.json"
#define JsonFile_HallTechUI			"assets/ui/HallTechUI.json"
#define JsonFile_HallTechTreeUI		"assets/ui/HallTechTreeUI.json"
#define JsonFile_AddLegionUI        "assets/ui/AddLegionUI.json"
#define JsonFile_LegionUI           "assets/ui/LegionUI.json"
#define JsonFile_FreeFightScoreUI	"assets/ui/FreeFightScore.json"
#define JsonFile_FreeFightCheckOut	"assets/ui/FreeFightCheckOut.json"

//副本界面Start
#define JsonFile_CopyCommon				"assets/ui/CopyCommon.json"				//通用副本
#define JsonFile_CopyDefUI				"assets/ui/CopyDef.json"				//守护副本
#define JsonFile_CopySurvive			"assets/ui/CopySurvive.json"			//生存副本
#define JsonFile_CopyContendFor			"assets/ui/CopyContendFor.json"			//争夺副本
#define JsonFile_CopyFreeFight			"assets/ui/CopyFreeFight.json"			//自由战斗
//副本界面End

#define JsonFile_PetUI				"assets/ui/PetUI.json"						//宠物界面UI

enum emIDU{
	IDU_NONE = 0,
	IDU_LOGIN = 60001,			//登陆界面;
	IDU_CopyUIStart,
	//副本界面Start
	IDU_CopyCommon,				//通用副本
	IDU_CopyUIDef,				//守护副本
	IDU_CopyUISurvive,			//生存副本
	IDU_CopyUIContendFor,		//争夺副本
	IDU_CopyFreeFight,			//自由战斗
	//副本界面End
	IDU_MESSAGEBOX,				//消息提示框
	IDU_REVIVEANDBACK,			//复活和回城;
	IDU_CHATMAINUI,				//聊天主界面
	IDU_TEAMAPPLICATION,		//入队申请列表
	IDU_NPCDIALOG,				//NPC对话;
	IDU_TASKUI,					//任务管理;
	IDU_TASKDIALOG,	            //任务对话
	IDU_SERVERLIST,				//服务器列表;
	IDU_CREATEPLAYER,			//创建角色;
	IDU_SELECTPLAYER,			//选择角色;
	IDU_MainUINormal,			//非战斗主界面
	IDU_MainUIFight,			//战斗主界面
	IDU_FightPause,				//战斗暂停
	IDU_HeroInfo,				//英雄信息
	IDU_Social,					//社交
	IDU_WaveEnd,				//副本5波结算
	IDU_CopyEnd,				//副本结束结算
	IDU_MailUI,					//邮件界面  2015/8/17 李阳
	IDU_WORLDMAPUI,				//地图;
	IDU_Loading,				//加载界面
	IDU_Drama,					//剧情界面
	IDU_Friend,					//好友界面
	IDU_RoleAttri,				//角色属性界面
	IDU_RolePackage,            //角色背包界面
	IDU_MissionlUI,				//任务系统界面  2015/8/24 李阳
	IDU_SkyBookUI,				//天书系统界面  2015/9/2  Tangbo
	IDU_SkyBookCalcUI,          //天书计算界面  
	IDU_GodDeviceUI,			//神器系统界面  2015/9/2 李阳
	IDU_StrengthenUI,			//强化系统界面  2015/9/9 李阳
	IDU_ManufactureUI,          //制造系统界面  
	IDU_OneStrokeUI,			//一笔画
	IDU_OpenLock,				//开锁
	IDU_ReviveUI,				//复活
	IDU_ITEMTIPSUI,             //道具提示界面
	IDU_HallTechUI,				//战舰
	IDU_HallTechTreeUI,			//战舰科技树
	IDU_AddLegionUI,            //还未加入军团
	IDU_LegionUI,               //已经加入军团
	IDU_FreeFightScore,			//自由战斗比分
	IDU_FreeFightCheckOut,		//自由战斗结算
	IDU_PetUI,					//宠物界面
};

#endif
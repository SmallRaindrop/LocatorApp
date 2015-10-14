#ifndef __StringDef_h_
#define __StringDef_h_

#include "../GameScene/GameDataManager.h"


/************************聊天面板字符串*********************/

#define STR_CHAT_SHIJIE			GameString.get(1)->value.c_str()
#define STR_CHAT_GONGHUI		GameString.get(2)->value.c_str()
#define STR_CHAT_ZUDUI			GameString.get(3)->value.c_str()
#define STR_CHAT_DITU			GameString.get(4)->value.c_str()
#define STR_CHAT_XITONG			GameString.get(5)->value.c_str()
#define STR_CHAT_LABA			GameString.get(6)->value.c_str()
/************************角色面板字符串*********************/
#define STR_ROLE_ATKMAGIC		GameString.get(7)->value
#define STR_ROLE_ATK			GameString.get(8)->value
/************************邮件面板字符串*********************/
#define STR_MAIL_SYS			GameString.get(9)->value
#define STR_MAIL_PLAYER			GameString.get(10)->value
#define STR_MAIL_DEL			GameString.get(11)->value
#define STR_MAIL_GET			GameString.get(12)->value
#define STR_MAIL_FRIEND			GameString.get(13)->value
#define STR_MAIL_ENEMY			GameString.get(14)->value
#define STR_MAIL_BLACKLIST		GameString.get(15)->value
#define STR_MAIL_TODAY			GameString.get(156)->value
#define STR_MAIL_MoneyOwn		GameString.get(158)->value
#define STR_MAIL_SendSuc		GameString.get(159)->value
#define STR_MAIL_BagNotEnough	GameString.get(160)->value
#define STR_MAIL_LenNotEnough	GameString.get(162)->value
/************************技能面板字符串*********************/
#define STR_SKILL_LV			GameString.get(16)->value
#define STR_SKILL_STUDY			GameString.get(17)->value
#define STR_SKILL_STUDY1		GameString.get(18)->value
#define STR_SKILL_TOMAXLV		GameString.get(19)->value
#define STR_SKILL_CURLV			GameString.get(20)->value
#define STR_SKILL_CD			GameString.get(21)->value
#define STR_SKILL_POINT			GameString.get(22)->value
#define STR_SKILL_MP			GameString.get(23)->value
#define STR_SKILL_UP			GameString.get(24)->value
#define STR_SKILL_BOOK			GameString.get(25)->value
#define STR_SKILL_TOSTUDY		GameString.get(26)->value
#define STR_SKILL_STUDY0		GameString.get(27)->value
#define STR_SKILL_SingleAtk		GameString.get(169)->value
#define STR_SKILL_GroupAtk		GameString.get(170)->value
#define STR_SKILL_Assist		GameString.get(171)->value
#define STR_SKILL_Passive		GameString.get(172)->value
#define STR_SKILL_LvDesc		GameString.get(245)->value
#define STR_SKILL_UnStudy		GameString.get(246)->value
#define STR_SKILL_Study			GameString.get(247)->value
#define STR_SKILL_Upgrade		GameString.get(248)->value
#define STR_SKILL_LvNeed		GameString.get(317)->value
#define STR_SKILL_UnLockLv		GameString.get(318)->value
#define STR_SKILL_ConditionTitle1		GameString.get(319)->value
#define STR_SKILL_ConditionTitle2		GameString.get(320)->value
/************************TIPS按钮字符串*********************/
#define STR_TIPS_EQUIP			GameString.get(28)->value
#define STR_TIPS_SHOW			GameString.get(29)->value
#define STR_TIPS_DESTROY		GameString.get(30)->value
#define STR_TIPS_SELL			GameString.get(31)->value
#define STR_TIPS_USE			GameString.get(32)->value
#define STR_TIPS_UNEQUIP		GameString.get(33)->value
#define STR_TIPS_PUTIN			GameString.get(34)->value
#define STR_TIPS_PUTOUT			GameString.get(35)->value
#define STR_TIPS_SPLIT			GameString.get(141)->value
#define STR_TIPS_DROP			GameString.get(183)->value
#define STR_TIPS_BUY			GameString.get(267)->value
#define STR_TIPS_UPFRAME		GameString.get(262)->value
#define STR_TIPS_DOWNFRAME		GameString.get(265)->value

#define STR_Lv_NotEnough		GameString.get(166)->value
/************************装备类型描述*********************/
#define STR_EQUIP_HEAD			GameString.get(36)->value
#define STR_EQUIP_NECKLACE		GameString.get(37)->value
#define STR_EQUIP_WEAPON		GameString.get(38)->value
#define STR_EQUIP_ARMOR			GameString.get(39)->value
#define STR_EQUIP_BANGLE		GameString.get(40)->value
#define STR_EQUIP_RING			GameString.get(41)->value
#define STR_EQUIP_BELT			GameString.get(42)->value
#define STR_EQUIP_SHOE			GameString.get(43)->value
#define STR_EQUIP_WING			GameString.get(44)->value
#define STR_GRADE_ZERO			GameString.get(157)->value
#define STR_GRADE_ONE			GameString.get(45)->value
#define STR_GRADE_TWO			GameString.get(46)->value
#define STR_GRADE_THREE			GameString.get(47)->value
#define STR_GRADE_FOUR			GameString.get(48)->value
#define STR_GRADE_FIVE			GameString.get(49)->value
#define STR_GRADE_SIX			GameString.get(50)->value
#define STR_EQUIP_BIND			GameString.get(51)->value
#define STR_EQUIP_UNBIND		GameString.get(52)->value
#define STR_EQUIP_LVNEED		GameString.get(53)->value
#define STR_EQUIP_CAREER		GameString.get(54)->value
/************************职业类型描述*********************/
#define STR_CAREER_ZS			GameString.get(55)->value
#define STR_CAREER_FS			GameString.get(56)->value
#define STR_CAREER_GJ			GameString.get(57)->value
#define STR_CAREER_TY			GameString.get(58)->value
/************************装备基础属性*********************/
#define STR_EQUIPBASE_HPMAX			GameString.get(59)->value
#define STR_EQUIPBASE_MPMAX			GameString.get(60)->value
#define STR_EQUIPBASE_ATK_L			GameString.get(61)->value
#define STR_EQUIPBASE_ATK_H			GameString.get(62)->value
#define STR_EQUIPBASE_ATK_MAGIC_L	GameString.get(63)->value
#define STR_EQUIPBASE_ATK_MAGIC_H	GameString.get(64)->value
#define STR_EQUIPBASE_DEF			GameString.get(65)->value
#define STR_EQUIPBASE_DEF_MAGIC		GameString.get(66)->value
#define STR_EQUIPBASE_HIT			GameString.get(67)->value
#define STR_EQUIPBASE_DODGE			GameString.get(68)->value
#define STR_EQUIPBASE_CRIT			GameString.get(69)->value
#define STR_EQUIPBASE_SPEED			GameString.get(70)->value

#define STR_EQUIPBASE_ATK			GameString.get(71)->value
#define STR_EQUIPBASE_ATK_MAGIC		GameString.get(72)->value
/************************装备隐藏属性*********************/
#define STR_EQUIPHIDDEN_DAMAGE_ADD			GameString.get(73)->value
#define STR_EQUIPHIDDEN_DAMAGE_REDUCE		GameString.get(74)->value
#define STR_EQUIPHIDDEN_DAMAGE_MAGIC_ADD	GameString.get(75)->value
#define STR_EQUIPHIDDEN_DAMAGE_MAGIC_REDUCE	GameString.get(76)->value
#define STR_EQUIPHIDDEN_HIT_RATE			GameString.get(77)->value
#define STR_EQUIPHIDDEN_DODGE_RATE			GameString.get(78)->value
#define STR_EQUIPHIDDEN_CRIT_RATE			GameString.get(79)->value
#define STR_EQUIPHIDDEN_CRIT_TIMES_RATE		GameString.get(80)->value

#define STR_MENU_MSG						GameString.get(81)->value.c_str()
#define STR_MENU_TEAM						GameString.get(82)->value.c_str()
#define STR_MENU_SENDMAIL					GameString.get(83)->value.c_str()
#define STR_MENU_CHECKOUTEQI				GameString.get(84)->value.c_str()
#define STR_MENU_SEARCH						GameString.get(85)->value.c_str()
#define STR_MENU_ADDFRIEND					GameString.get(86)->value.c_str()
#define STR_MENU_ADDBLACKLIST				GameString.get(87)->value.c_str()
#define STR_MENU_ADDENEMY					GameString.get(88)->value.c_str()
#define STR_MENU_DELETE						GameString.get(89)->value.c_str()
#define STR_MENU_TEAMKICK					GameString.get(90)->value.c_str()
#define STR_MENU_TEAMHANDOVER				GameString.get(91)->value.c_str()
#define STR_MENU_FRIEND						GameString.get(92)->value.c_str()
#define STR_MENU_ENEMY						GameString.get(93)->value.c_str()
#define STR_MENU_BLACKLIST					GameString.get(94)->value.c_str()
#define STR_MENU_STRANGER					GameString.get(95)->value.c_str()
#define STR_MENU_TRADE						GameString.get(167)->value.c_str()

#define STR_EQUIPHIDDEN_STRENGTH			GameString.get(96)->value
#define STR_EQUIPHIDDEN_ATTACH				GameString.get(235)->value
#define STR_FIGHT_CAPACITY					GameString.get(236)->value
#define STR_HOLE_NOTACTIVE					GameString.get(237)->value
#define STR_EQUIP_SELL						GameString.get(97)->value
#define STR_EQUIP_CANNOTSELL				GameString.get(98)->value

/************************装备随机属性*********************/
#define STR_RANDOM_ATK_L				GameString.get(99)->value	
#define STR_RANDOM_ATK_H				GameString.get(100)->value	
#define STR_RANDOM_ATK_MAGIC_L			GameString.get(101)->value	
#define STR_RANDOM_ATK_MAGIC_H			GameString.get(102)->value	
#define STR_RANDOM_DEF					GameString.get(103)->value	
#define STR_RANDOM_DEF_MAGIC			GameString.get(104)->value	
#define STR_RANDOM_HIT					GameString.get(105)->value	
#define STR_RANDOM_DODGE				GameString.get(106)->value
#define STR_RANDOM_CRIT					GameString.get(107)->value	
#define STR_RANDOM_STRENGTH				GameString.get(146)->value	
#define STR_RANDOM_AGILITY				GameString.get(108)->value	
#define STR_RANDOM_SPEED				GameString.get(109)->value
#define STR_RANDOM_POSION				GameString.get(110)->value
#define STR_RANDOM_LUCKY				GameString.get(111)->value
#define STR_RANDOM_HP_R					GameString.get(112)->value
#define STR_RANDOM_HP_RP				GameString.get(113)->value	
#define STR_RANDOM_MP_R					GameString.get(114)->value	
#define STR_RANDOM_MP_RP				GameString.get(115)->value	
#define STR_RANDOM_HPMAX				GameString.get(116)->value
#define STR_RANDOM_MPMAX				GameString.get(117)->value
#define STR_RANDOM_INT					GameString.get(118)->value
#define STR_RANDOM_DAMAGE_ADD			GameString.get(119)->value	
#define STR_RANDOM_DAMAGE_MAGIC_ADD		GameString.get(120)->value	
#define STR_RANDOM_DAMAGE_REDUCE		GameString.get(121)->value
#define STR_RANDOM_DAMAGE_MAGIC_REDUCE	GameString.get(122)->value
#define STR_RANDOM_DAMAGE_ALL_REDUCE	GameString.get(123)->value
#define STR_RANDOM_HP_P					GameString.get(124)->value	
#define STR_RANDOM_ATK_P				GameString.get(125)->value	
//#define STR_RANDOM_ATK_H_P				GameString.get(126)->value
#define STR_RANDOM_ATK_MAGIC_P		GameString.get(127)->value
//#define STR_RANDOM_ATK_MAGIC_H_P		GameString.get(128)->value
#define STR_RANDOM_DEF_P				GameString.get(129)->value
#define STR_RANDOM_DEF_MAGIC_P			GameString.get(130)->value
#define STR_RANDOM_ALL					GameString.get(131)->value
#define STR_RANDOM_MP_P					GameString.get(132)->value
#define STR_RANDOM_HITRATE				GameString.get(147)->value
#define STR_RANDOM_DODGERATE			GameString.get(148)->value
#define STR_RANDOM_CRITRATE				GameString.get(149)->value

#define STR_RANDOM_MAX					GameString.get(133)->value
#define STR_ISEQUIPING					GameString.get(136)->value

// 下面定义长字符串，通常是对话框上面的问句或陈述
#define STR_TEAM_APPLICATION	GameString.get(134)->value.c_str()
#define STR_TEAM_INVITATION		GameString.get(135)->value.c_str()
#define STR_TEAM_INVITATION2	GameString.get(168)->value.c_str()

//message box 提示语
#define STR_MESSAGEBOX_COMFIRM		GameString.get(137)->value
#define STR_MESSAGEBOX_CANCEL		GameString.get(138)->value
#define STR_MESSAGEBOX_COST			GameString.get(139)->value
#define STR_MESSAGEBOX_ACTTIVEGRID	GameString.get(140)->value
#define STR_Sell_Tips1				GameString.get(189)->value
#define STR_Sell_Tips2				GameString.get(190)->value
//数量选择UI
#define STR_ItemSel_Title			GameString.get(191)->value
#define STR_ItemSel_Btn1			GameString.get(192)->value
#define STR_ItemSel_Btn2			GameString.get(193)->value
//激活格子
#define STR_MONEY_NOTENOUGH			GameString.get(142)->value
#define STR_Active_OneLine_Suc		GameString.get(164)->value
//物品主类型描述
#define STR_ITEMTYPE_EQUIP			GameString.get(143)->value
#define STR_ITEMTYPE_ZAWU			GameString.get(144)->value
#define STR_ITEMTYPE_MATERIAL		GameString.get(145)->value
//格子拆分提示
#define STR_SPLIT_NUMNOTENOUGH		GameString.get(150)->value
#define STR_SPLIT_GRIDNOTENOUGH		GameString.get(151)->value
#define STR_SPLIT_NUM_NOTRIGHT		GameString.get(152)->value
#define STR_SPLIT_ITEM_NOTEXIST		GameString.get(153)->value
#define STR_SPLIT_EQUIP_NOTRIGHT	GameString.get(154)->value
#define STR_Split_Suc				GameString.get(163)->value
//背包
#define STR_Bag_OrderCd				GameString.get(165)->value
//熔炉
#define STR_Compose_UseStone		GameString.get(180)->value
#define STR_Compose_NotUseStone		GameString.get(181)->value
#define STR_Strength_Fail			GameString.get(184)->value
#define STR_Compose_MainEquipTip	GameString.get(199)->value
#define STR_Compose_SubEquipTip		GameString.get(200)->value
#define STR_Strength_Tips			GameString.get(222)->value
#define STR_Strenght_PreView		GameString.get(257)->value
//消息盒子
#define STR_Confirm					GameString.get(182)->value
//物品品质颜色
#define STR_QualityColor_White		GameString.get(185)->value
#define STR_QualityColor_Green		GameString.get(186)->value
#define STR_QualityColor_Blue		GameString.get(187)->value
#define STR_QualityColor_Orange		GameString.get(188)->value

#define STR_Bag_Equip				GameString.get(194)->value
#define STR_Bag_ZaWu				GameString.get(195)->value
#define STR_Bag_Material			GameString.get(196)->value

//NPC
#define STR_NpcDialog_Leave			GameString.get(201)->value

//交易
#define STR_Trade_Message1			GameString.get(209)->value
#define STR_Trade_Message2			GameString.get(215)->value
#define STR_Trade_Message3			GameString.get(216)->value
#define STR_Trade_UnLock			GameString.get(250)->value
#define STR_Trade_Lock				GameString.get(251)->value

//复活
#define STR_Relive_Free				GameString.get(225)->value
#define STR_Relive_Money			GameString.get(226)->value
#define STR_Relive_BindMoney		GameString.get(227)->value
#define STR_Relive_Gold				GameString.get(228)->value
#define STR_Relive_CostDesc			GameString.get(229)->value

//寄售行
#define STR_Sale_FilterCareer		GameString.get(238)->value
#define STR_Sale_FilterGrade		GameString.get(239)->value
#define STR_Sale_FilterQuality		GameString.get(240)->value
#define STR_Sale_LastPage			GameString.get(241)->value
#define STR_Sale_NextPage			GameString.get(242)->value
#define STR_Sale_Message1			GameString.get(255)->value
#define STR_Sale_Message2			GameString.get(256)->value
#define STR_Sale_UpFrameTips		GameString.get(260)->value
#define STR_Sale_DownFrameTips		GameString.get(261)->value
#define STR_Sale_RemainTime1		GameString.get(288)->value
#define STR_Sale_RemainTime2		GameString.get(263)->value
#define STR_Sale_RemainTime3		GameString.get(264)->value

//活动中心
#define STR_Activity_Coming			GameString.get(268)->value
#define STR_Activity_BeComing		GameString.get(269)->value
#define STR_Activity_Completed		GameString.get(270)->value
#define STR_Activity_CannotDo		GameString.get(271)->value

//副本
#define STR_CopyMap_TitlePre		GameString.get(273)->value
#define STR_CopyMap_LeaveCommon		GameString.get(312)->value
#define STR_CopyMap_Leave1			GameString.get(275)->value
#define STR_CopyMap_Leave2			GameString.get(276)->value

#define STR_CareerDesc_ZS			GameString.get(280)->value
#define STR_CareerDesc_FS			GameString.get(281)->value
#define STR_CareerDesc_GJ			GameString.get(282)->value

//答题
#define STR_ActivityTimeLeft		GameString.get(284)->value
#define STR_TimeUsed				GameString.get(287)->value
#define STR_Question_Continue1		GameString.get(289)->value
#define STR_Question_Continue2		GameString.get(290)->value
#define STR_No_Heart				GameString.get(291)->value
#define STR_Question_Result			GameString.get(292)->value
#define STR_Question_Leave			GameString.get(296)->value
#define STR_Question_DaRen			GameString.get(302)->value

#define STR_Player_Del				GameString.get(293)->value

//成就
#define STR_Achievement_use			GameString.get(297)->value
#define STR_Achievement_CancleUse	GameString.get(316)->value

#define STR_AchievementRank_Legend	GameString.get(298)->value
#define STR_AchievementRank_Top10	GameString.get(299)->value
#define STR_AchievementRank_Others	GameString.get(300)->value
#define STR_AchievementRank_GetNum	GameString.get(301)->value
#define STR_AchievementRank_NoPerson	GameString.get(303)->value
#define STR_AchievementRank_Everyone	GameString.get(304)->value

//世界BOSS
#define STR_WorldBoss				GameString.get(309)->value
#define STR_WorldBoss_Reflesh		GameString.get(310)->value
#define STR_WorldBoss_Dead			GameString.get(311)->value

//等级礼包
#define STR_LevelGift_Got			GameString.get(313)->value
#define STR_LevelGift_CanGet		GameString.get(314)->value
#define STR_LevelGift_CanotGet		GameString.get(315)->value

//翅膀
#define STR_Wing_SubTitle1			GameString.get(900)->value
#define STR_Wing_SubTitle2			GameString.get(901)->value
#define STR_Wing_SubTitle3			GameString.get(902)->value
#define STR_Wing_SubTitle4			GameString.get(903)->value
#define STR_Wing_SubTitle5			GameString.get(910)->value
#define STR_Wing_Adorn				GameString.get(904)->value
#define STR_Wing_AdornCancle		GameString.get(905)->value
#define STR_Wing_CostItem			GameString.get(906)->value
#define STR_Wing_NeedCharge			GameString.get(907)->value
#define STR_Wing_NeedLv				GameString.get(908)->value
#define STR_Wing_CostMoney			GameString.get(909)->value

//xiaohao
#define STR_Cost_Honor				GameString.get(911)->value
#define STR_Cost_Reputation			GameString.get(912)->value

//设置UI
#define STR_Set_GeZi				GameString.get(321)->value
#define STR_Set_Recommond			GameString.get(322)->value

#define STR_Map_Back				GameString.get(323)->value

#define STR_Guild_Apply1			GameString.get(324)->value
#define STR_Guild_Apply2			GameString.get(325)->value

//加载界面
#define STR_LOADING_ADDRES          GameString.get(913)->value
#define STR_LOADING_UPDATE          GameString.get(914)->value

//组队
#define STR_Team_Apply1				 GameString.get(1004)->value
#define STR_Team_Apply2				 GameString.get(1005)->value

//社交
#define STR_Check_Player			 GameString.get(1100)->value.c_str()
#define STR_Add_Friend				 GameString.get(1101)->value.c_str()
#define STR_Team_Kickout			 GameString.get(1102)->value.c_str()
#define STR_Team_Leave				 GameString.get(1103)->value.c_str()
#define STR_Team_Invite				 GameString.get(1104)->value.c_str()
#define STR_Private_Msg				 GameString.get(1106)->value.c_str()
#define STR_Mask_Msg				 GameString.get(1107)->value.c_str()
#define STR_CopyName				 GameString.get(1108)->value.c_str()
#define STR_DelFriend_Fail           GameString.get(1109)->value.c_str()
#define STR_IsDelFriend              GameString.get(1110)->value.c_str() 
#define STR_IsAddFriend              GameString.get(1111)->value.c_str() 
#define STR_DelBlackPlayer           GameString.get(1112)->value.c_str()
#define STR_IsAddBlackP              GameString.get(1113)->value.c_str() 

//聊天
#define STR_Chat_Other2You			GameString.get(1300)->value.c_str()
#define STR_Chat_You2OOther1		GameString.get(1301)->value.c_str()
#define STR_Chat_You2OOther2		GameString.get(1302)->value.c_str()
#define STR_Chat_SystemCh_Tips		GameString.get(1303)->value.c_str()

//个人属性
#define STR_ROLEBAG_TOOMORE         GameString.get(1400)->value.c_str()
#define STR_ROLEBAG_ONLYONE         GameString.get(1401)->value.c_str()
#define STR_ROLEBAG_NOMATCH         GameString.get(1402)->value.c_str()
#define STR_ROLEBAG_DISRULE         GameString.get(1403)->value.c_str()
#define STR_ROLEBAG_CHANGEQUIP      GameString.get(1404)->value.c_str()
#define STR_ROLEBAG_HAVENOTSELL     GameString.get(1405)->value.c_str()
#define STR_ROLEBAG_ADMINSELL       GameString.get(1406)->value.c_str()
#define STR_ROLEBAG_NOSELL          GameString.get(1407)->value.c_str()
#define STR_ROLEBAG_NOGIVEUP        GameString.get(1408)->value.c_str()
#define STR_ROLEBAG_ADMINUNLOADING  GameString.get(1409)->value.c_str()
#define STR_ROLEBAG_NOPICK          GameString.get(1410)->value.c_str()

//副本匹配
#define STR_Match_Cancle1			GameString.get(1600)->value.c_str()		//取消
#define STR_Match_Cancle2			GameString.get(1601)->value.c_str()		//取消匹配
#define STR_Match_Start				GameString.get(1602)->value.c_str()		//立即开始
#define STR_Match_prepare			GameString.get(1603)->value.c_str()		//准备
#define STR_Match_prepare_over		GameString.get(1604)->value.c_str()		//准备完毕
#define STR_Match_prepare_Start		GameString.get(1605)->value.c_str()		//准备开始
#define STR_Match_Matching			GameString.get(1606)->value.c_str()		//正在匹配...
#define STR_Match_prepareing		GameString.get(1607)->value.c_str()		//准备中
#define STR_Match_randomCopy		GameString.get(1608)->value.c_str()		//随机副本

//副本类型
#define STR_Copy_Type_PT			GameString.get(1700)->value.c_str()		//普通
#define STR_Copy_Type_XS			GameString.get(1701)->value.c_str()		//悬赏
#define STR_Copy_Type_CT			GameString.get(1702)->value.c_str()		//冲突
#define STR_Copy_Type_EM			GameString.get(1703)->value.c_str()		//噩梦

//副本敌人
#define STR_Copy_Enemy_YG			GameString.get(1800)->value.c_str()		//妖鬼
#define STR_Copy_Enemy_SZ			GameString.get(1801)->value.c_str()		//水族
#define STR_Copy_Enemy_YG_SZ		GameString.get(1802)->value.c_str()		//妖鬼VS水族

//副本玩法
#define STR_Copy_Play_FS			GameString.get(1500)->value.c_str()		//防守
#define STR_Copy_Play_JM			GameString.get(1501)->value.c_str()		//歼灭
#define STR_Copy_Play_BH			GameString.get(1502)->value.c_str()		//捕获

//副本UI标题
#define STR_Copy_CountTitle				GameString.get(2000)->value.c_str()		//离开倒计时
#define STR_Copy_Title_GoalKill			GameString.get(2001)->value.c_str()		//目标击杀数
#define STR_Copy_Title_CurKill			GameString.get(2002)->value.c_str()		//当前击杀数
#define STR_Copy_Title_GoalDestroy		GameString.get(2003)->value.c_str()		//目标破坏数
#define STR_Copy_Title_CurDestroy		GameString.get(2004)->value.c_str()		//当前破坏数
#define STR_Copy_Title_GoalChests		GameString.get(2005)->value.c_str()		//目标宝箱数
#define STR_Copy_Title_CurChests		GameString.get(2006)->value.c_str()		//当前解开宝箱数
#define STR_Copy_Title_GoalCatch		GameString.get(2007)->value.c_str()		//目标捕获数
#define STR_Copy_Title_CurCatch			GameString.get(2008)->value.c_str()		//当前捕获数
#define STR_Copy_Title_CountFight		GameString.get(2009)->value.c_str()		//战斗倒计时
#define STR_Copy_Title_GoalSave			GameString.get(2010)->value.c_str()		//目标营救数
#define STR_Copy_Title_CurSave			GameString.get(2011)->value.c_str()		//当前营救数
#define STR_Copy_Title_FightSec			GameString.get(2012)->value.c_str()		//战斗时间

#define STR_Copy_Title_ContendFor_Wave	GameString.get(2013)->value.c_str()		//第%d轮
#define STR_Copy_Title_ContendFor_Dot	GameString.get(2014)->value.c_str()		//点
#define STR_Copy_Title_ContendFor_ZL	GameString.get(2015)->value.c_str()		//占领
#define STR_Copy_Title_ContendFor_BZL	GameString.get(2016)->value.c_str()		//被敌人占领
#define STR_Copy_Title_ContendFor_ZD	GameString.get(2017)->value.c_str()		//争夺中

//任务按钮文本
#define STR_Btn_Text_Get			GameString.get(10000)->value.c_str()	//领取
#define STR_Btn_Text_Go				GameString.get(10001)->value.c_str()	//前往

//神器切换按钮文本
#define STR_Btn_Text_Dress			GameString.get(10002)->value.c_str()	//装备
#define STR_Btn_Text_Dressed		GameString.get(10003)->value.c_str()	//已装备
#define STR_ChangeGodDevice_Text	GameString.get(10004)->value.c_str()	//切换神器提示文本

//天书界面
#define STR_Btn_Text_Inlay          GameString.get(11000)->value.c_str()    //镶嵌
#define STR_Btn_Text_Push           GameString.get(11001)->value.c_str()    //放入
#define STR_Text_UnPush             GameString.get(11002)->value.c_str()    //xx天书不可放入
#define STR_Text_Star               GameString.get(11003)->value.c_str()    //%d星
#define STR_Text_RefinedBook        GameString.get(11004)->value.c_str()    //请放入要祭炼的天书
#define STR_Text_Refinedgoods       GameString.get(11005)->value.c_str()    //请选择祭炼材料天书
#define STR_Text_Syntheticgoods     GameString.get(11006)->value.c_str()    //请选择合成材料天书
#define STR_TS_BTN_INLAYED          GameString.get(11007)->value.c_str()    //已镶嵌
#define STR_TS_BTN_ALL              GameString.get(11008)->value.c_str()    //全部
#define STR_TS_BTN_RELIC            GameString.get(11009)->value.c_str()    //神器
#define STR_TS_BTN_WEAPON           GameString.get(11010)->value.c_str()    //武器
#define STR_TS_BTN_PET              GameString.get(11011)->value.c_str()    //宠物
#define STR_TS_BTN_MATERIAL         GameString.get(11012)->value.c_str()    //材料

//强化界面
#define STR_Text_Gold				GameString.get(10009)->value.c_str()    //金币
#define STR_Text_Jinglian_Stone		GameString.get(10005)->value.c_str()    //精炼石
#define STR_Text_Jinjie_Stone		GameString.get(10006)->value.c_str()    //精炼石
#define STR_Text_Jinglian_Consume	GameString.get(10007)->value.c_str()    //精炼消耗
#define STR_Text_Jinjie_Consume		GameString.get(10008)->value.c_str()    //进阶消耗
#define STR_Text_Tip_Jinglian		GameString.get(10010)->value.c_str()    //是否进行精炼
#define STR_Text_Tip_Jinglian_Max	GameString.get(10011)->value.c_str()    //是否进行最大精炼
#define STR_Text_Tip_Jinjie			GameString.get(10012)->value.c_str()    //是否进行进阶
#define STR_Text_Tip_Jinjie_need    ChatData.get(1300)->content.c_str()    //精炼等级达到15级才能进阶
#define STR_Text_Tip_item_not_enough    ChatData.get(1301)->content.c_str()    //材料不足
#define STR_Text_Tip_gold_not_enough    ChatData.get(1302)->content.c_str()    //金币不足
#define STR_Text_Tip_level_not_enough   ChatData.get(1303)->content.c_str()   //精炼等级不能超过人物等级的一半
#define STR_Text_Tip_jinglian_max		ChatData.get(1304)->content.c_str()   //已达到最高精炼等级
#define STR_Text_Tip_jinjie_max			ChatData.get(1305)->content.c_str()   //已达到最高进阶等级
#define STR_Text_Tip_free_revive_tip	ChatData.get(1307)->content.c_str()   //免费复活提示
#define STR_Text_Tip_gold_revive_tip	ChatData.get(1306)->content.c_str()   //金币复活提示

//制造界面显示文本
#define STR_MANUF_HAVETARGET        GameString.get(12000)->value.c_str()       //%s已有目标个数%d  
#define STR_MANUF_NEEDTIME          GameString.get(12001)->value.c_str()       //所需时间%d  
#define STR_MANUF_NEEDGOLD          GameString.get(12002)->value.c_str()       //所需金币%d  
#define STR_MANUF_FASTTEXT          GameString.get(12003)->value.c_str()       //花费%d元宝加速制造    

//复活
#define STR_REVIVE_DEADVIRTUAL      GameString.get(13000)->value.c_str()       //您已濒临死亡 
#define STR_REVIVE_DEAD			    GameString.get(13001)->value.c_str()       //您已死亡    

#endif	// __StringDef_h_

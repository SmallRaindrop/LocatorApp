#ifndef __ItemType_h_
#define __ItemType_h_

#include "GameDef.h"

// 金币类型定义
enum MoneyType
{
	MoneyType_Coin,		// 金币
	MoneyType_BindCoin,	// 绑定金币
	MoneyType_Gold,			// 元宝
	MoneyType_BindGold,		// 绑定元宝
};

// 物品类型定义
enum ItemType
{
	ItemType_None = 0,
	ItemType_Equip,				// 装备
	ItemType_Others,			// 杂物
	ItemType_Material,			// 材料
	ItemType_DrawingSheet,		// 图纸
	ItemType_SkyBook,			// 天书
	ItemType_GodDevice,			// 神器（衣服）
};

enum EquipType
{
	EquipType_Weapon = 1,		// 武器
	EquipType_MagicCimelia,		// 防具
};

// 物品子类型定义
enum ItemSubType
{
	//物品子类型：
	//装备子类型：
	//0 无

	//图纸子类型
	SubType_TUZHI_WEAPON = 1, //1 武器
	SubType_TUZHI_RELIC,      //2 神器
	SubType_TUZHI_AROMR,      //3 防具
	SubType_TUZHI_PET,        //4 宠物
	SubType_TUZHI_MATERIAL,   //5 材料
	SubType_TUZHI_OTHER,      //6 其它


	//材料子类型
	//0 无

	//天书子类型
	//可镶嵌位置先填写A，再填写B
	SubType_TIANSHU_WUJI = 1, //1 武技天书，镶嵌在武器特殊槽位
	SubType_TIANSHU_WEAPON,   //2 武器普通天书，镶嵌在武器一般槽位
	SubType_TIANSHU_HALO,     //3 光环天书，镶嵌在神器特殊槽位
	SubType_TIANSHU_RELIC,    //4 神器普通天书，镶嵌在神武一般槽位
	SubType_TIANSHU_MATERIAL, //5 材料天书，不可镶嵌，只能作为升级用材料
	SubType_TIANSHU_PET,      //6 宠物天书，镶嵌在宠物一般槽位

	//杂项子类型
	SubType_ZAWU_REWARD = 1,  //1 礼包
	SubType_ZAWU_XUQIU,       //2 血球
	SubType_ZAWU_FAQIU,       //3 法球
	SubType_ZAWU_COIN,        //4 掉落在地面的金币，可直接拾取
};

// 装备栏定义 6个
enum EquipColumnType
{
	EquipColumn_GodDevice,			// 神器（衣服）
	EquipColumn_Weapon,				// 武器
	EquipColumn_MagicCimelia0,		// 法宝1
	EquipColumn_MagicCimelia1,		// 法宝2
	EquipColumn_MagicCimelia2,		// 法宝3
	EquipColumn_MagicCimelia3,		// 法宝4
	EquipColumn_MagicCimeliaMax,	// 
	EquipColumn_Max
};

//物品品质
enum ItemQualityType
{
	ItemQuality_None,
	ItemQuality_Green,
	ItemQuality_Blue,
	ItemQuality_Orange
};

#endif //__ItemType_h_
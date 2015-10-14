#pragma once
#include "GameDef.h"
#include "GameScene/db.h"
#include "UI/GameUIDef.h"
#include "GameScene/ItemType.h"
#include "UI/CocosUI.h"

//获取职业icon路径
string GetCareerIcon(int nCareer);
//获取世界地图职业icon路径
string GetWorldMapCareerIcon(int nCareer);
//获取队员死亡icon路径
string GetTeamIconDead(int nCareer);
//获取队员活着的icon路径
string GetTeamIconAlive(int nCareer);

/*获取品质color*/
Color3B GetQualityColor(ItemQualityType quality);
string GetQualityImgPath(ItemQualityType type);
string GetQualityDesc(ItemQualityType type);

string GetBagTypeDes(int type);

/****************************装备通用 start ************************************/
/*获取职业描述*/
string GetCareerDes(int career);

/****************************装备通用 end ************************************/

/*获取默认激活格子数*/
int GetDefaultActiveGrids(emGridsType type);

string GetAtkTypeDes(int type);

int getPageNum(int itemCount,int numsOfPage=BAG_PAGE_SIZE);

class CCommonUI
{
public:
	CCommonUI();
	~CCommonUI();

	static Point getWorldPosition(Widget* pWidget);

	/*生成左标签*/
	static void changeToLeftLabel(Widget* pWidget);

private:

};
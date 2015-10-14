#include "CommonUI.h"
#include "GameScene/GameUILayer.h"
#include "UI/MainUI.h"

#define path_qulity_green		("assets/ui/common/quality_green.png")
#define path_qulity_blue		("assets/ui/common/quality_blue.png")
#define path_qulity_orange		("assets/ui/common/quality_orange.png")

string GetCareerIcon(int nCareer)
{
	return CCString::createWithFormat("%sCareer%d.png",ICON_PATH_HEAD,nCareer)->getCString();
}
string GetWorldMapCareerIcon(int nCareer)
{
	return CCString::createWithFormat("%sWorldMapCareer%d.png",ICON_PATH_HEAD,nCareer)->getCString();
}
string GetTeamIconDead(int nCareer)
{
	return CCString::createWithFormat("%sTeamDead%d.png",ICON_PATH_HEAD,nCareer)->getCString();
}
string GetTeamIconAlive(int nCareer)
{
	return CCString::createWithFormat("%sTeamAlive%d.png",ICON_PATH_HEAD,nCareer)->getCString();
}

Color3B GetQualityColor(ItemQualityType quality)
{
	switch (quality)
	{
	case ItemQuality_None:
		return Color3B::WHITE;				/*°×*/
	case ItemQuality_Green:
		return Color3B(0,255,0);			/*ÂÌ*/
	case ItemQuality_Blue:
		return Color3B(0,0,255);			/*À¶*/
	case ItemQuality_Orange:
		return Color3B(230,165,25);			/*³È*/
	default:
		return Color3B::WHITE;				/*°×*/
	}
}

string GetQualityImgPath(ItemQualityType type)
{
	string path_quality = "";
	switch (type)
	{
	case ItemQuality_None:
		break;
	case ItemQuality_Green:
		path_quality = path_qulity_green;
		break;
	case ItemQuality_Blue:
		path_quality = path_qulity_blue;
		break;
	case ItemQuality_Orange:
		path_quality = path_qulity_orange;
		break;
	default:
		break;
	}
	return path_quality;
}

string GetQualityDesc(ItemQualityType type)
{
	switch (type)
	{
	case ItemQuality_None:
		return STR_QualityColor_White;
	case ItemQuality_Green:
		return STR_QualityColor_Green;
	case ItemQuality_Blue:
		return STR_QualityColor_Blue;
	case ItemQuality_Orange:
		return STR_QualityColor_Orange;
	}
	return "";
}

string GetBagTypeDes(int type)
{
	switch (type)
	{
	case 1:return STR_Bag_Equip;
	case 2:return STR_Bag_ZaWu;
	case 3:return STR_Bag_Material;
	}
	return "";
}

string GetCareerDes(int career)
{
	RoleCareer i = RoleCareer(career);
	switch (i)
	{
	case RoleCareer_None:
		break;
	case RoleCareer_DunWei:
		break;
	case RoleCareer_QiangShen:
		break;
	case RoleCareer_JianXian:
		break;
	case RoleCareer_JiGuanShi:
		break;
	case RoleCareer_Max:
		break;
	default:
		break;
	}
	return "";
}

int GetDefaultActiveGrids(emGridsType type)
{
	switch (type)
	{
	case emGrids_BagEquip: return BAG_SIZE_EQUIPACTIVE;
	case emGrids_BagZaWu: return BAG_SIZE_ZAWUACTIVE;
	case emGrids_BagMaterial: return BAG_SIZE_MATERIALACTIVE;
	default:return 0;
	}
}

string GetAtkTypeDes(int type)
{
	switch (type)
	{
	case 1: return STR_SKILL_SingleAtk;
	case 2: return STR_SKILL_GroupAtk;
	case 3: return STR_SKILL_Assist;
	case 4:	return STR_SKILL_Passive;
	}
	return "";
}

int getPageNum(int itemCount,int numsOfPage)
{
	int nPages;
	if (itemCount%numsOfPage != 0)
	{
		nPages=itemCount/numsOfPage + 1;
	}
	else if(itemCount == 0)
	{
		nPages = 1;
	}
	else
	{
		nPages = itemCount/numsOfPage;
	}
	return nPages;
}

CCommonUI::CCommonUI()
{

}

CCommonUI::~CCommonUI()
{

}

Point CCommonUI::getWorldPosition(Widget* pWidget)
{
	Point pos = pWidget->getWorldPosition();
	if( MainUI::GetActiveMainUI())
	{
		return MainUI::GetActiveMainUI()->getWidget()->convertToNodeSpace(pos);
	}
	
	return pos;
}

void CCommonUI::changeToLeftLabel(Widget* pWidget)
{
	pWidget->setScaleX(-1.0f);

    for(const auto& child: pWidget->getChildren())
		child->setScaleX(-1.0f);
}
#include "RoleModel.h"

RoleModel::RoleModel()
{

}

RoleModel::~RoleModel()
{

}

bool RoleModel::init()
{
	changeDir(DIR_S);
	setScale(2.5f);
	return true;
}

void RoleModel::setAppearance(EquipmentID armorID,EquipmentID weaponID,EquipmentID wingID)
{
	equipWeapon(weaponID);
	equipArmor(armorID);
	equipWing(wingID);
}
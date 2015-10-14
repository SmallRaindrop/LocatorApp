#ifndef __RoleModel_h_
#define __RoleModel_h_

#include "GameDef.h"
#include "role.h"

class RoleModel : public Role
{
public:
	RoleModel();
	~RoleModel();

	CREATE_FUNC(RoleModel);

	bool init();

	void setAppearance(EquipmentID armorID,EquipmentID weaponID,EquipmentID wingID);
};

#endif //__RoleModel_h_
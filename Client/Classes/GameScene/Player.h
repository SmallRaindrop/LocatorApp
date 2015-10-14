#ifndef __Player_h_
#define __Player_h_

#include "RoleFighter.h"
#include "Net/pk_move.h"
#include "RoleModel.h"

class CPlayer : public RoleFighter
{
public:
	CPlayer();
	virtual ~CPlayer();

	CREATE_FUNC(CPlayer);

	virtual bool init();
	virtual bool initRole();

	virtual void update(float dt);
	virtual void onSelect(bool param);

	inline int	 GetVipLevel(){ return GetPropertyInt(RoleProperty_VipLevel); }
	inline int64 GetGuildID() { return GetPropertyInt64(RoleProperty_GuildID); }

	virtual void SetProperty(RoleProperty idx,int val);
	virtual void SetProperty(RoleProperty idx,__int64 val);
	virtual void SetProperty(RoleProperty idx,const string& val);

	virtual void SetCloth(int val);
	virtual void SetWeapon(int val);
	virtual void SetWing(int val);
	virtual void SetVipLevel(int val);
	virtual void SetGuildID(__int64 val);

	virtual void RefreshEquip();
	virtual void RefreshRoleTitle();
};

#endif //__Player_h_




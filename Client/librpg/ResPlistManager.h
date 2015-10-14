#ifndef __ResPlistManager_h_
#define __ResPlistManager_h_

#include "GameDef.h"
#include "Singleton.h"
#include "ResPlist.h"

class ResPlistManager : public Ref, public Singleton<ResPlistManager>
{
public:
	ResPlistManager();
	~ResPlistManager();

public:
	ResPlist*	getPlist(const string& path);
	ResPlist*	getPlistEx(const string& path);
	void		clearUnusedPlists();
	void		clear();
	void		update(float dt);

protected:
	typedef map<string,ResPlist*>	PlistTable;
	PlistTable m_Plists;
};

#define gPlistManager ResPlistManager::Instance()

#endif
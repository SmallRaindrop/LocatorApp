#include "ResPlistManager.h"
#include "MemoryMonitor.h"

#define SCHEDULE gDirector->getScheduler()
ResPlistManager::ResPlistManager()
{
	m_Plists.clear();
	//Æô¶¯¶¨Ê±Æ÷
	SCHEDULE->schedule(schedule_selector(ResPlistManager::update),this,0.1f,false);
}

ResPlistManager::~ResPlistManager()
{
	SCHEDULE->unscheduleAllForTarget(this);

	clear();
}

ResPlist* ResPlistManager::getPlist(const string& path)
{
	PlistTable::iterator itr = m_Plists.find(path);
	if ( itr != m_Plists.end() )
	{
		return itr->second;
	}

	return NULL;
}

ResPlist* ResPlistManager::getPlistEx(const string& path)
{
	PlistTable::iterator itr = m_Plists.find(path);
	if ( itr != m_Plists.end() )
	{
		return itr->second;
	}

	ResPlist* pPlist = new ResPlist(path);
	if ( pPlist )
	{
		pPlist->loadAsync();
		m_Plists[path] = pPlist;
	}

	return pPlist;
}

void ResPlistManager::update(float dt)
{
	for ( PlistTable::iterator itr = m_Plists.begin();itr != m_Plists.end();)
	{
		ResPlist* pPlist = itr->second;
		if ( pPlist->isFree() )
		{
			if ( gMemoryMonitor->isMemoryWarnning() )
			{
				pPlist->release();
				itr = m_Plists.erase(itr);
				continue;
			}
		}

		if ( pPlist->isUsing() )
		{
			pPlist->update(dt);
		}

		++itr;
	}
}

void ResPlistManager::clear()
{
	for ( PlistTable::iterator itr = m_Plists.begin();itr != m_Plists.end();++itr )
	{
		CC_SAFE_RELEASE(itr->second);
	}

	m_Plists.clear();
}

void ResPlistManager::clearUnusedPlists()
{
	for ( PlistTable::iterator itr = m_Plists.begin();itr != m_Plists.end(); )
	{
		ResPlist* pPlist = itr->second;
		if ( pPlist->isFree() )
		{
			//CCLog("clear unused plist : %s",pPlist->getPathKey().c_str());
			pPlist->release();
			itr = m_Plists.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}
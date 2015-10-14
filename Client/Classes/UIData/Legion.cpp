#include "Legion.h"

LegionMember_cl::LegionMember_cl()
{
	m_vMemberList.clear();
}

LegionMember_cl::~LegionMember_cl()
{
	m_vMemberList.clear();
}

void LegionMember_cl::addMember( pk::memberList* member )
{
	bool isexist = false;
	for(auto iter :m_vMemberList)
	{
		if(iter.playerId == member->playerId)
		{
			isexist = true;
			break;
		}
	}
	if(!isexist)
	{
		m_vMemberList.push_back(*member);
	}
}

void LegionMember_cl::removeMemberByPlayerId( int playerid )
{
	for (auto iter = m_vMemberList.begin(); iter != m_vMemberList.end(); iter++)
	{
		if(iter->playerId == playerid)
		{
			iter = m_vMemberList.erase(iter);
			break;
		}
	}
}

void LegionMember_cl::removeMember( pk::memberList* member )
{
	if(!member) return;
	removeMemberByPlayerId(member->playerId);
}


Legion_cl::Legion_cl()
{
	m_pMember = nullptr;
	m_pGuild.clear();
}

Legion_cl::~Legion_cl()
{
	if(m_pMember)
	{
		delete m_pMember;

	}
	m_pGuild.clear();
}

void Legion_cl::initLegion( Legion_V _list )
{
	m_pGuild = _list;
}

void Legion_cl::initMemberList( Member_V _list )
{
	m_pMember = new LegionMember_cl();
	for (size_t i = 0; i < _list.size(); i++)
	{
		m_pMember->addMember(&_list[i]);
	}
}

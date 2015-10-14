#include "GameVariable.h"
#include <memory.h>

CGameVariable::CGameVariable()
{
	Reset();
}

CGameVariable::~CGameVariable()
{
	
}

void CGameVariable::Reset()
{
	memset(m_arrPlayerVariable, 0x00, sizeof(m_arrPlayerVariable));
}

int CGameVariable::GetWorldVariable(int index)
{
	if (index < 1000 && index > -1)
	{
		return m_arrWorldVariable[index];
	}
	return 0;
}

int CGameVariable::GetPlayerVariable(int index)
{
	if (index < 1000 && index > -1)
	{
		return m_arrPlayerVariable[index];
	}
	return 0;
}

void CGameVariable::SetWorldVariable(int index, int value)
{
	if (index < 1000 && index > -1)
	{
		m_arrWorldVariable[index] = value;
	}
}

void CGameVariable::SetPlayerVariable(int index, int value)
{
	if (index < 1000 && index > -1)
	{
		m_arrPlayerVariable[index] = value;
	}
}

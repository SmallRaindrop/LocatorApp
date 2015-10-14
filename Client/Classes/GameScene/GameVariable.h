#ifndef __GAME_VARIABLE_h_
#define __GAME_VARIABLE_h_

#include "Singleton.h"

class CGameVariable : public Singleton_Auto<CGameVariable>
{
public:
	CGameVariable();
	~CGameVariable();

	void	Reset();
	int		GetWorldVariable(int index);
	int		GetPlayerVariable(int index);
	void	SetWorldVariable(int index, int value);
	void	SetPlayerVariable(int index, int value);

private:
	int	m_arrWorldVariable[1000];
	int	m_arrPlayerVariable[1000];
};

#define gGameVariable CGameVariable::Instance()

inline int GetWorldVariable(int index)
{
	return gGameVariable->GetWorldVariable(index);
}

inline int GetPlayerVariable(int index)
{
	return gGameVariable->GetPlayerVariable(index);
}

inline void SetPlayerVariable(int index,int value)
{
	gGameVariable->SetPlayerVariable(index,value);
}

inline void SetWorldVariable(int index,int value)
{
	gGameVariable->SetWorldVariable(index,value);
}

#endif //__GAME_VARIABLE_h_



////////////////////////////////// 下面定义变量索引/////////////////////////////////////
#define PlayerVariant_Index_GuildDonation	7
#define PlayerVariant_Index_TitleUsing		9	// 使用中的成就称号
#define PlayerVariant_Index_NewHandGuild_ProgressIndex_P	51
#define PlayerVariant_Index_LevelGift						10
#define PlayerVariant_Index_LoginDays						12
#define PlayerVariant_Index_LoginGift						13
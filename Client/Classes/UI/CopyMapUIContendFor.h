/* 
	争夺副本UI
	彭龙华
	2015-10-13
*/
#pragma once
#include "cocos2d.h"
#include "GameUI.h"
#include "CopyMapUI.h"

#define Max_ContendFor_Num	(5)
//争夺副本
class CCopyMapContendFor:public CCopyMapUI
{
	//争夺点状态
	typedef enum _placeStatus
	{
		PlaceStatus_Zl,	//占领
		PlaceStatus_BZL, //被占领
		PlaceStatus_ZDZ, //争夺中
	}PlaceStatus;

	//进度归属0玩家，1怪物
	typedef enum _processOwner
	{
		ProcessOwner_Player,
		ProcessOwner_Monster,
	}ProcessOwner;
	//进度是否走0停止，1走, 2反走
	typedef enum _processType
	{
		ProcessType_Stop,
		ProcessType_Player,
		ProcessType_Monster,
	}ProcessType;
	typedef struct _process
	{
		int			id;
		int			x;
		int			y;
		ProcessOwner owner;
		ProcessType type;
		int			processValue;
		_process(pk::ContentionPoint& value)
		{
			id = value.id;
			x = value.x;
			y = value.y;
			owner = (ProcessOwner)value.processOwner;
			type = (ProcessType)value.processType;
			processValue = value.process;
		}
		PlaceStatus GetStatus()
		{
			if( owner==ProcessOwner_Player && processValue==100 )
			{
				return PlaceStatus_Zl;
			}
			else if (owner==ProcessOwner_Monster && processValue==100)
			{
				return PlaceStatus_BZL;
			}
			else
			{
				return PlaceStatus_ZDZ;
			}
		}
		Color3B GetValueColor()
		{
			switch (owner)
			{
			case ProcessOwner_Player:
				return Color3B(0x41,0x69,0xe1);
			default:
				return Color3B::RED;
			}
		}
		Color3B GetStatusColor()
		{
			switch (GetStatus())
			{
			case PlaceStatus_Zl:
				return Color3B(0x41,0x69,0xe1);
			case PlaceStatus_BZL:
				return Color3B::RED;
			default:
				return Color3B::WHITE;
			}
		}
		std::string GetStatusText()
		{
			switch (GetStatus())
			{
			case PlaceStatus_Zl:
				return STR_Copy_Title_ContendFor_ZL;
			case PlaceStatus_BZL:
				return STR_Copy_Title_ContendFor_BZL;
			default:
				return STR_Copy_Title_ContendFor_ZD;
			}
		}
	}Process;
public:
	CCopyMapContendFor();
	~CCopyMapContendFor();

	virtual bool			onInit();
	void					UpdateContendForInfo(pk::GS2C_ContentionInfo* value);
	virtual void			BeforeActive();
	virtual void			OnActive();
	virtual void			SetWaveIdx(int nWaveIdx);
private:
	Text*	m_pPlayerScore;
	Text*	m_pMonsterScore;
	Text*	m_pPlaceTitle[Max_ContendFor_Num];
	Text*	m_pPlaceStatus[Max_ContendFor_Num];
};
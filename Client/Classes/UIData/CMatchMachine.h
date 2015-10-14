/****************************************************************************
 副本匹配状态机
 彭龙华
 2015-09-08
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameScene/Hero.h"

typedef enum _matchMode
{
	MatchMode_None,
	MatchMode_Single,
	MatchMode_Invite,
	MatchMode_Match,
	MachMode_End,
	MatchMode_Count,
}MatchMode;

//MatchMode<<2 | TeamStatus
typedef enum _matchStatus
{
	MatchStatus_None = -1,
	MatchStatus_NoTeam_Single = 4,					//未组队,单人模式
	MatchStatus_NoTeam_Invite = 8,					//未组队,邀请模式
	MatchStatus_NoTeam_Match = 12,					//未组队,匹配模式
	MatchStatus_TeamNoFull_Single = 5,				//组队未满,单人模式
	MatchStatus_TeamNoFull_Invite = 9,				//组队未满,邀请模式
	MatchStatus_TeamNoFull_Match = 13,				//组队未满,匹配模式
	MatchStatus_TeamFull_Single = 6,				//组队满,单人模式
	MatchStatus_TeamFull_Invite = 10,				//组队满,邀请模式
	MatchStatus_TeamFull_Match = 14,				//组队满,匹配模式
	MatchStatus_Count,									//最大个数
}MatchStatus;

class CMatchMachine
{
public:
	CMatchMachine();
	~CMatchMachine();

	void					Init();
	void					Clear();

	void					Update(float dt);

	//匹配是否启动
	inline bool				IsMatchStarted() { return m_bMatchStarted; }
	inline void				SetMatchStarted(bool bStarted) { m_bMatchStarted=bStarted; }
	inline void				MatchStart() { SetMatchStarted(true); }
	void					MatchEnd();
	//匹配发起者ID
	inline int64			GetMatchInvitedPlayerId() { return m_nMatchInvitedPlayerId; }
	inline void				SetMatchInvitedPlayerId(int64 nPlayerId) { m_nMatchInvitedPlayerId = nPlayerId; }
	inline bool				AmIInviter() { return m_nMatchInvitedPlayerId == gHero->GetId(); }
	//匹配倒计时
	inline float			GetMatchCountSeconds()	{ return m_fMatchCountSeconds; }
	inline void				SetMatchCountSeconds(float nSeconds) { m_fMatchCountSeconds = nSeconds; m_fMatchCountSecondSum = nSeconds; time(&m_nMatchStartTimeStamp); }
	//匹配准备进入的地图ID
	inline int				GetMatchCopyMapIdToEnter()	{ return m_nMatchCopyMapIdToEnter; }
	inline void				SetMatchCopyMapIdToEnter(int nMapId) { m_nMatchCopyMapIdToEnter = nMapId; }
	//匹配模式
	inline MatchMode		GetMatchMode() { return m_nMatchMode; }
	inline void				SetMatchMode(MatchMode matchMode) { m_nMatchMode = matchMode; }
	//匹配是否准备好
	inline bool				GetMatchPrepared() { return m_bMatchPrepared; }
	inline void				SetMatchPrepared(bool bMatchPrepared) { m_bMatchPrepared = bMatchPrepared; }
	//匹配状态
	inline MatchStatus		GetMatchStatus() { return m_matchStatus; }
	inline void				SetMatchStatus(MatchStatus matchStatus) { m_matchStatus = matchStatus; }
	void					UpdateMatchStatus();
	//匹配等待时间
	inline float			GetMatchWaitTime() { return m_fMatchWaitTime; }
	void					SetMatchWaitTime(float fWaitTime) { m_fMatchWaitTime = fWaitTime; }


private:
	bool					m_bMatchStarted;					  //匹配是否启动了
	int64					m_nMatchInvitedPlayerId;			  //匹配发起者ID
	float					m_fMatchCountSeconds;				  //匹配倒计时秒
	int						m_nMatchCopyMapIdToEnter;			  //匹配准备进入的地图ID
	MatchMode				m_nMatchMode;						  //匹配模式,匹配模式手动结束，其他模式自动结束
	bool					m_bMatchPrepared;					  //匹配是否准备好
	MatchStatus				m_matchStatus;						  //匹配状态
	float					m_fMatchWaitTime;					  //匹配等待时间
	time_t					m_nMatchStartTimeStamp;				  //匹配启动时间戳
	float					m_fMatchCountSecondSum;				  //倒计时总时间
};

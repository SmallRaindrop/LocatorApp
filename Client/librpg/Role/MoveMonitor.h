#ifndef __MoveMonitor_h_
#define __MoveMonitor_h_

/************************************************************************/
/* 移动速度定义：10S 移动的格子数                 
/************************************************************************/

#include "GameDef.h"
#include "Map/AStar.h"
#include "RoleData.h"
#include "Map/map_def.h"

__Dir DirectionBy(int cx0,int cy0,int cx1,int cy1);

Point DistanceByWorld(int cx0,int cy0,int cx1,int cy1);


enum MoveType
{
	MoveType_Normal,
	MoveType_Flash,
};

class MoveMonitor
{
public:
	MoveMonitor();
	~MoveMonitor();

public:
	/* Name		：Move
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移动开始
	 * Param	: start 起点 path 移动路径 speed 移动速度 timeoffset 时间偏移
	 * Return	: void
	 */
	void Move(APoint start,APath& path,int speed,int timeOffset);

	/* Name		：Flash
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 闪现至某点
	 * Param	: start 起点 end 终点 speed 移动速度 timeoffset 时间偏移
	 * Return	: void
	 */
	void Flash(const APoint& start,const APoint& end,int speed,int timeOffset);

	/* Name		：MoveEnd
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 停止当前移动
	 * Param	: point停止的目标点
	 * Return	: void
	 */
	void MoveEnd(APoint point = APoint());

	/* Name		：Terminate
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移动终止
	 * Param	: none
	 * Return	: void
	 */
	void Terminate();

	/* Name		：Update
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新
	 * Param	: dt
	 * Return	: void
	 */
	void Update(float dt);

	/* Name		：UpdateMove
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新
	 * Param	: dt
	 * Return	: void
	 */
	void UpdateMove(float dt);

	/* Name		：UpdateFlash
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新
	 * Param	: dt
	 * Return	: void
	 */
	void UpdateFlash(float dt);

	
	//
	inline APath&	GetPath(){ return m_Path; }
	inline __Dir	GetDir(){ return m_nDir; }

	inline long		GetMoveTimeCost(){ return m_lMoveTimeCost; }
	inline void		SetMoveTimeCost(long s){ m_lMoveTimeCost = s; }
	inline void		AddMoveTimeCost(long s){ m_lMoveTimeCost += s; }
	inline long		GetMoveTimeCorrect(){ return m_lMoveTimeCorrect; }
	inline void		SetMoveTimeCorrect(long ms){ m_lMoveTimeCorrect = ms; }
	inline void		AddMoveTimeCorrect(long ms){ m_lMoveTimeCorrect += ms; }
	inline void		SubMoveTimeCorrect(long ms){ m_lMoveTimeCorrect -= ms; }

	inline int		GetStepX(){ return m_StepPoint.x; }
	inline int		GetStepY(){ return m_StepPoint.y; }
	inline APoint	GetCurrPoint(){ return m_CurrPoint; }
	inline APoint	GetStepPoint(){ return m_StepPoint; }
	inline Point	GetCurrPointOffset(){ return m_CurrPointOffset; }
	
	inline void		Step(int x,int y){ m_StepPoint.x = x; m_StepPoint.y = y; }
	inline void		Step(APoint point){ m_StepPoint = point; }

	inline bool		IsStepOver(){ return (m_StepPoint.x == 0 && m_StepPoint.y == 0) ;}

	inline MoveType GetMoveType(){ return m_nType; }

	/* Name		：GetMoveSpeed
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取移动速度，返回移动一个格子所需要的时间MS
	 * Param	: none
	 * Return	: 移动速度 long
	 */
	float GetMoveSpeed();

	/* Name		：GetMoveSpeedRecover
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 返回错误修复速度
	 * Param	: none
	 * Return	: 移动速度 float
	 */
	float GetMoveSpeedRecover();

	/* Name		：GetMoveSpeed
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 移动一个格子时间 = 本身移动速度+误差速度。
	 * Param	: none
	 * Return	: 移动一个格子时间 
	 */
	float GetMoveTimeOneCell();

	/* Name		：GetFlashTime
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取闪烁的时间
	 * Param	: none
	 * Return	: 闪烁总时间
	 */
	long GetFlashTime();

protected:
	MoveType		m_nType;				// 移动类型，是普通移动还是闪烁
	APath			m_Path;					// 移动路径
	APoint			m_CurrPoint;			// 起点
	APoint			m_StepPoint;			// 下一个位置
	Point			m_CurrPointOffset;		// 移动位移
	
	__Dir			m_nDir;					// 当前方向,8方向之一
	int				m_nSpeed;				// 移动速度
	long			m_lMoveTimeCost;		// 当前格子移动消耗时间
	long			m_lMoveTimeCorrect;		// 当前格子移动矫正时间
	long			m_lLastTime;			// 上一次时间
};

#endif
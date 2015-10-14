#pragma once
#include "GameScene/GameDataManager.h"
#include "TileMap.h"
#include "GameScene/GridsManager.h"
#include "Net/NetDispatcher.h"
#include "GameScene/Hero.h"
#include "GameScene/MapItem.h"
#include "Singleton.h"


USING_NS_CC;
extern float fNow;

typedef void (Ref::*Monitor_Trigger)(void *);

//-----------------------------------------Monitors----------------------------------------------
class CMonitor
{
public:
	enum eConditionMet
	{
		CM_CONFIG_CHANGED = 1,
		CM_Approach,
		CM_Attack,
		CM_HP,
		CM_MP,
		CM_Pick,
	};

	struct Condition
	{
		int nMoveRange;		// 活动范围(格)
		int nAttackMode;	// 1:均衡 2:单体 3:群体
		int nHPRedLine;		// 30, 50, 70%
		int nMPRedLine;		// 30, 50, 70%
		int nPickMode;		// 1:all  2:白品 3:不拾取
	};

	struct ActionData
	{
		eConditionMet	action;
		__int64			target;
		int				skill;
	};
public:
	CMonitor():m_bRunning()	{};
	~CMonitor()				{};
	virtual bool update(float dt)	{return (m_pActionCondition && m_bRunning && m_pActionFunc && m_pActionExecutor); };
	void		 InitWithConditions(Condition *pCondition){	m_pActionCondition = pCondition;}
	void		 SetRunning(bool bRunning)	{m_bRunning = bRunning;};
	void		 SetCenter(Point pos)	{m_ptCenter = pos;};
	virtual void SaveConfigToFile()	{};
	void		 SetActionHandler(Ref* pObj, Monitor_Trigger pActionFunc)	
				{
					m_pActionFunc = pActionFunc;	
					m_pActionExecutor = pObj;
				}

protected:
	bool			m_bRunning;
	Monitor_Trigger	m_pActionFunc;
	Ref*		m_pActionExecutor;
	Condition*		m_pActionCondition;
	Point			m_ptCenter;
};

class CPropMonitor : public CMonitor
{
public:
	CPropMonitor():m_bPickAnyway()	{};
	~CPropMonitor()					{};
    virtual bool update(float dt);
	virtual void SaveConfigToFile();
	void		 PickAnyway(bool p)	{m_bPickAnyway = p;}

private:
	bool	m_bPickAnyway;		// 不管是否是自己的都去捡
};

class CHMPMonitor : public CMonitor
{
public:
	CHMPMonitor() {};
	~CHMPMonitor(){};
    virtual bool update(float dt);
	virtual void SaveConfigToFile();

private:
};

class CFightMonitor : public CMonitor
{
	friend class Robot;
public:
	CFightMonitor():m_nTargetID(){};
	~CFightMonitor()	{};
	virtual bool update(float dt);
	virtual bool updateEx(float dt)	{return false;};
	void BeAttackedBy(MapObjectID nEnemyID);
	bool NeedFightBack();
	void Reset()	{}

	struct FightBackInfo
	{
		double		fBeAttackedTime;
		int			fHPMoment;
	};
protected:
	MapObjectID		m_nTargetID;
};

//-----------------------------------------Actions----------------------------------------------
typedef void (Ref::*ActionException)(int reason);
class RobotAction
{
public:
	RobotAction(Ref* pExe = NULL, ActionException func = NULL): m_bException()
	{
		m_nMaxDuration = 5; 
		m_tStartingTime = fNow; 
		m_pExceptionFunc = func; 
		m_pExceptionExe = pExe;
	}
	~RobotAction()	{};
	virtual void update(float dt){};
	virtual bool Exception()
	{
		if (m_pExceptionFunc && m_pExceptionExe)
			(m_pExceptionExe->*m_pExceptionFunc)(0);
		return true;
	}
	virtual bool IsDone()
	{
		if (m_bException)
		{
			return Exception();
		}

		if (m_tStartingTime + m_nMaxDuration < fNow)
		{
			return Exception();
		}
		return false;
	};

protected:
	double			m_tStartingTime;
	int				m_nMaxDuration;
	bool			m_bException;

	ActionException	m_pExceptionFunc;
	Ref*		m_pExceptionExe;
};

class StandStill : public RobotAction
{
public:
	StandStill(): m_Duration(rand() % 6){m_tBegainning = fNow; CCLOG("StandStill---------------------->");};
	~StandStill()					{};
	virtual bool IsDone()			
	{
		return (m_tBegainning + m_Duration < fNow);
	};
private:
	double		m_tBegainning;
	int			m_Duration;
};

class RandWalk : public RobotAction
{
public:
	RandWalk(Point ptCenter, Point ptRadius)
	{
		do
		{
			m_ptTarget = Point(gHero->GetCellX(), gHero->GetCellY()) + Point(rand() % 20 - 10, rand() % 20 - 10);
		}
		while (m_ptTarget.x == gHero->GetCellX() && m_ptTarget.y == gHero->GetCellY());

		if (ptRadius.x > 0)
		{
			m_ptTarget.x = clampf(m_ptTarget.x, ptCenter.x - ptRadius.x, ptCenter.x + ptRadius.x);
			m_ptTarget.y = clampf(m_ptTarget.y, ptCenter.y - ptRadius.y, ptCenter.y + ptRadius.y);
		}
		else if (ptRadius.x == 0)
		{
			if (s_AutoMovePorts.size())
			{
				if (++s_itCurPort == s_AutoMovePorts.end())
					s_itCurPort = s_AutoMovePorts.begin();
				m_ptTarget = *s_itCurPort;
			}
		}
		else
		{
			m_ptTarget = ptCenter;
		}

		CCLOG("RandWalk---------------------->");
		gHero->MoveTo(m_ptTarget.x, m_ptTarget.y);
		//gNotificationCenter->postNotification(geHeroEvent,GameEvent::create(mapEvent_MapClicked,(void*)&m_ptTarget,NULL));
	}
	~RandWalk()	{};
	virtual bool IsDone()
	{
		return (!gHero->IsMoving() || gHero->GetCellX() == m_ptTarget.x && gHero->GetCellY() == m_ptTarget.y);
	};
private:
	Point		m_ptTarget;
public:
	static vector<Point>				s_AutoMovePorts;
	static vector<Point>::iterator	s_itCurPort;
};

class ExceptionAction : public RobotAction
{
public:
	ExceptionAction(Point ptCenter, Point ptRadius):m_handler(ptCenter, ptRadius){m_ptBeforeMoved = Point(gHero->GetCellX(), gHero->GetCellY());
			CCLOG("ExceptionAction---------------------->");}
	virtual bool IsDone()
	{
		bool m_bMoved = false;
		if (m_ptBeforeMoved.x != gHero->GetCellX() || m_ptBeforeMoved.x != gHero->GetCellY())
		{
			m_bMoved = true;
			CCLOG("ExceptionAction start move---------------------->");
		}
		return (gHero->IsStandStill() || m_bMoved && m_handler.IsDone());
	}
private:
	RandWalk	m_handler;
	Point		m_ptBeforeMoved;
};

class Pick : public RobotAction
{
public:
	Pick(CMapItem *pProp, Ref* pExe, ActionException func): RobotAction(pExe, func), m_nTarget(pProp->GetId())	
	{
		gHero->MoveTo(pProp->GetCellX(), pProp->GetCellY());
		gHero->SelectTargetByPos(pProp->getPosition()); m_tStartingTime = 0; m_nMaxDuration = 1;
	};
	~Pick()	{};
	CMapItem*	Get(){return (CMapItem*)(gMap->getObjectManager()->getObject(m_nTarget));};

	virtual bool Exception()
	{
		if (s_PropsInException.find(m_nTarget) != s_PropsInException.end())
		{
			s_PropsInException.find(m_nTarget)->second = fNow + 10;
		}
		else
		{
			s_PropsInException.insert(make_pair(m_nTarget, fNow + 10));
		}
		return true;
	}
	virtual bool IsDone()	
	{
		MapObject *pProp = gMap->getObjectManager()->getObject(m_nTarget);
		if (!pProp) return true;
		Point ptProp = Point(pProp->GetCellX(), pProp->GetCellY());
		Point ptMe = Point(gHero->GetCellX(), gHero->GetCellY());
		if (m_tStartingTime == 0 && !gHero->IsRunningForPicking()/*ptProp.x == ptMe.x && ptProp.y == ptMe.y*/)
		{
			m_tStartingTime = fNow;
		}

		return (m_tStartingTime && RobotAction::IsDone());
	}
	static void UpdatePropInProtection()
	{
		map<MapObjectID, double>::iterator it = s_PropsInException.begin();
		while (it != s_PropsInException.end())
		{
			MapObject *pProp = gMap->getObjectManager()->getObject(it->first);
			if (pProp == NULL)
			{
				it = s_PropsInException.erase(it);
				continue;
			}
			if (it->second < fNow)
			{
				it->second = 0;
			}
			it++;
		}
	}
	static bool CheckPropInException(MapObjectID id)
	{
		map<MapObjectID, double>::iterator it = Pick::s_PropsInException.find(id);
		if (it != Pick::s_PropsInException.end() && it->second != 0)
		{
			return true;
		}
		return false;
	}
public:
	static map<MapObjectID, double>	s_PropsInException;
protected:
	MapObjectID		m_nTarget;
};

class Use : public RobotAction
{
public:
	Use(int nIndex)
	{
		CItem *pProp = gGridsManager->getGirdItem(emGrids_BagZaWu, nIndex);
		if (pProp && !pProp->IsCding() )
		{
			m_nIndex = nIndex;
			m_nOrgNum = gGridsManager->getGirdItem(emGrids_BagZaWu, nIndex)->getCount();

			gHero->UseItem(pProp);
		}
		else
		{
			m_nIndex = 0;
			m_nOrgNum = -1;
		}
	}
	~Use();
	virtual bool IsDone()	{return (RobotAction::IsDone() || gGridsManager->getGirdItem(emGrids_BagZaWu, m_nIndex) == NULL ||
							m_nOrgNum != gGridsManager->getGirdItem(emGrids_BagZaWu, m_nIndex)->getCount());};
private:
	int			m_nIndex;
	int			m_nOrgNum;
};

class Approach : public RobotAction
{
public:
	Approach(__int64 nID, Ref* pExe, ActionException func):
	RobotAction(pExe, func)
	{
		MapObject *pObj = gMap->getObjectManager()->getObject(nID);
		if (pObj)
		{
			m_ptTargetOrg = Point(pObj->GetCellX(), pObj->GetCellY());
			m_nTarget = nID;

			if (m_ptTargetOrg.x == s_Target.x && m_ptTargetOrg.y == s_Target.y)
			{
				m_bException = true;
				s_Target = Point(0, 0);
			}
			else
			{
				s_Target = m_ptTargetOrg;
				gHero->MoveTo(m_ptTargetOrg.x, m_ptTargetOrg.y); 
			}

			CCLOG("Approach: %d, %d", pObj->GetCellX(), pObj->GetCellY());
			CCLOG("Me: %d, %d", gHero->GetCellX(), gHero->GetCellY());
		}
	}
	~Approach();
	virtual bool IsDone()
	{
		MapObject *pObj = gMap->getObjectManager()->getObject(m_nTarget);
		if (!pObj)
			return true;

		vector<pk::PosInfo> path;
		APath &succession_path = gHero->GetMovePath();
		CHero::PathToPosInfo(gHero->GetCellX(), gHero->GetCellY(), succession_path, path);

		if (path.back().x != m_ptTargetOrg.x || path.back().y != m_ptTargetOrg.y)
		{
			s_Target = Point(0, 0);
			return true;
		}

		if (m_ptTargetOrg.x != pObj->GetCellX() || m_ptTargetOrg.y != pObj->GetCellY())
		{
			m_ptTargetOrg = Point(pObj->GetCellX(), pObj->GetCellY());
			s_Target = m_ptTargetOrg;
			m_tStartingTime = fNow; 
			gHero->MoveTo(m_ptTargetOrg.x, m_ptTargetOrg.y); 
		}
		if (abs(gHero->GetCellX() - pObj->GetCellX()) <= 1 && abs(gHero->GetCellY() - pObj->GetCellY()) <= 1)
		{
			gHero->Stop(); 
			return true;
		}
		if (gHero->IsStandStill())
		{
			return true;
		}

		return RobotAction::IsDone();
	}
private:
	MapObjectID		m_nTarget;
	Point			m_ptTargetOrg;
	static Point	s_Target;
};

extern bool SKillCanRelease(int skill, MapObjectID nTargetID = 0);
class Attack : public RobotAction
{
public:
	Attack(__int64 nTargetID, int skill, Ref* pExe, ActionException func): 
		RobotAction(pExe, func)
	{
		CCLOG("Attack---------------------->: %d, %f", skill, fNow);
		MapObject *pObj = gMap->getObjectManager()->getObject(nTargetID);
		m_bTargetIsMe = (pObj == gHero);
		if (pObj)
		{
			if (!SKillCanRelease(skill, nTargetID))
			{
				if (m_bTargetIsMe)
					return;

				//skill = 100;
				//for (int i = m_vtrDefaultSkills.size() - 1; i >= 0; i--)
				//{
				//	if (SKillCanRelease(m_vtrDefaultSkills[i].first, nTargetID))
				//	{
				//		skill = m_vtrDefaultSkills[i].first;
				//		break;
				//	}
				//}

				//if (gHero->getISGSJF() && skill == 100)
				//{
				//	skill = 401;
				//	gHero->setISGSJF(false);
				//}

			}

			gHero->SelectTarget(dynamic_cast<RoleFighter*>(pObj));

			if (gHero->IsPursueing())
			{
				return;
			}

			gHero->Attack(skill);
			if (m_bTargetIsMe)
			{
				m_nTargetInitHP = 0;
				m_nTarget = 0;
				m_nTargetStartAttack = fNow;
				return;
			}

			if (m_nTarget != nTargetID)
			{
				m_nTargetInitHP = ((RoleFighter*)pObj)->GetHP();
				m_nTargetStartAttack = fNow;
				m_nTarget = nTargetID;
			}
			else
			{
				if (m_nTargetInitHP == ((RoleFighter*)pObj)->GetHP()) 
				{
					if (pObj->GetType() != mapObjectType_Player && m_nTargetStartAttack + 5 < fNow)
					{
						m_nTarget = 0;
						m_bException = true;
					}
				}
				else
				{
					m_nTargetInitHP = ((RoleFighter*)pObj)->GetHP();
					m_nTargetStartAttack = fNow;
				}
			}
		}
	}
	~Attack()
	{
		m_nTargetInitHP = 0;
	}
	virtual bool Exception()
	{
		if (m_bTargetIsMe)
			return true;
		return RobotAction::Exception();
	}
	virtual bool IsDone()	
	{
		//CCLOG("this= %d, m_tStartingTime = %f m_nMaxDuration = %d m_tStarting = %f, fNow = %f",
			//(int)this, m_tStartingTime, m_nMaxDuration, m_tStarting, fNow);
		if (gHero->IsPursueing())
		{
			m_tStartingTime = fNow;
		}
		return (RobotAction::IsDone() || m_tStartingTime + 1.1f < fNow && !gHero->IsAttacking() && !gHero->IsPursueing());
	}

public:
	static void ClearStatics()
	{
		//m_tStarting = 0;
		m_nTarget = 0;
		m_nTargetInitHP = 0;
		m_nTargetStartAttack = 0;
	}
	static vector<pair<int, bool>>		m_vtrDefaultSkills;
private:
	bool					m_bTargetIsMe;
	static MapObjectID		m_nTarget;
	static __int64			m_nTargetInitHP;
	static double			m_nTargetStartAttack;		// �Դ�Ŀ��ĵ�һ�ι���ʱ�̣���Ŀ�����
	//static double			m_tStarting;
};

//-----------------------------------------Robot----------------------------------------------
class PickEx : public Pick
{
public:
	PickEx(CMapItem *pProp, Ref* pExe, ActionException func): Pick(pProp, pExe, func)	{m_ptProp = Point(pProp->GetCellX(), pProp->GetCellY());};
	~PickEx()	{};
	virtual bool Exception()
	{
		// 后续要求一键拾取在道具在保护期时也尝试去捡，失败则原地停止捡取过程。
		if (Get()->GetOwnerID())
		{
			Pick::Exception();
			return RobotAction::Exception();
		}
		return true;
	}
	Point GetTargetPos()	{return m_ptProp;}

private:
	Point	m_ptProp;
};

class Picker : public Ref
{
public:
	Picker();
	~Picker();
	void Start();
    void update(float dt);
	void PropConditionMet(void *);
	void PickNeedAbortion(int);
private:
	CPropMonitor	m_Monitor;
	PickEx*			m_pAction;
	bool			m_bRuning;
};

class Robot : public Node,public Singleton<Robot>
{
public:
	enum Robot_Move_Range
	{
		RMR_STAND,
		RMR_SCREEN,
		RMR_GLOBAL
	};
public:
	Robot();
	~Robot()				{ReplaceAction(NULL); ConcurrentAction(NULL);};

    virtual void update(float dt);
	void EventHandler(Ref* sender);
	bool IsRunning()	{return m_bRunning;}
	void SetRunning(bool bRunning);
	void ConditionMet(void *);
	void ActionNeedAbortion(int);
	void SetRobotActionRule(CPropMonitor::Condition *pCond1, CHMPMonitor::Condition *pCond2, CFightMonitor::Condition *pCond3, Robot_Move_Range move);
	void ReplaceAction(RobotAction *pAction)	{delete m_pCurAction; m_pCurAction = pAction;}
	void ConcurrentAction(RobotAction *pAction)	{delete m_pConAction; m_pConAction = pAction;}
	void PickThese(){m_pPicker.Start();};
	CMonitor::Condition* GetConditions()	{return &m_Condition;}
	void Save();
	void Idle();

private:
	bool				m_bRunning;
	bool				m_bActionException;
	//Robot_Move_Range	m_eMoveRange;
	Point				m_ptCenter;
	CMonitor::Condition	m_Condition;

	CPropMonitor		m_PropMonitor;
	CHMPMonitor			m_HMPMonitor;
	CFightMonitor		m_FightMonitor;
	Picker				m_pPicker;				// ��Ϊ������һ������һ��ʰȡ���ܣ��ǹһ�

	RobotAction*		m_pCurAction;			// ֫����Ϊ�������г���ʱ������
	RobotAction*		m_pConAction;			// ��֫����Ϊ�����޳���ʱ�����ԣ�����֫����Ϊ������
};

#define gRobot Robot::Instance()

#include "GameScene/Monster.h"
#include "GameScene/Skill.h"
//#include "GameModules/buffList/BuffManager.h"
#include "GameScene/BeyondMap.h"
#include "StringUtil.h"
#include "Robot.h"
#include "GameDef.h"
#include "Common/CommonDef.h"
#include "GameScene/TaskMgr.h"
#include "StringConverter.h"
#include "GameScene/PKMode.h"


//double						Attack::m_tStarting;
vector<pair<int, bool>>		Attack::m_vtrDefaultSkills;
MapObjectID					Attack::m_nTarget;
__int64							Attack::m_nTargetInitHP;
double						Attack::m_nTargetStartAttack;
map<MapObjectID, double>	Pick::s_PropsInException;
Point						Approach::s_Target;

vector<Point>				RandWalk::s_AutoMovePorts;
vector<Point>::iterator	RandWalk::s_itCurPort = RandWalk::s_AutoMovePorts.end();

void CPropMonitor::SaveConfigToFile()
{
	char strHeroID[20] = {};
	sprintf(strHeroID, "_%lld", gHero->GetId());
	string strSuffix = strHeroID;

	CCUserDefault::getInstance()->setBoolForKey(strSuffix.c_str(), true);
	CCUserDefault::getInstance()->setIntegerForKey(("PickMode" + strSuffix).c_str(),((Condition*)m_pActionCondition)->nPickMode);
}

int GetPropNotInProtection(MapObjectList *pContainer)
{
    MapObjectList objList;
    gMap->getObjectManager()->getObjects(mapObjectType_Item, objList);
	MapObjectList::iterator it;
	int nCounter = 0;
	for (it = objList.begin(); it != objList.end(); it++)
	{
		if (((CMapItem*)(*it))->GetOwnerID() == 0 || gHero->GetId() == ((CMapItem*)(*it))->GetOwnerID())
		{
			if (pContainer)
				pContainer->push_back(*it);
			nCounter++;
		}
	}

	return nCounter;
}

bool CPropMonitor::update(float dt)
{
	Condition *pActionCondition = (Condition*)m_pActionCondition;
	if (!m_bRunning || m_pActionFunc && m_pActionExecutor == NULL || pActionCondition->nPickMode == 3)
	{
		return false;
	}

	ActionData data = {CM_Pick};
    MapObjectList objList;
	MapObjectList::iterator it;
	int	nNearestIndex = -1, i = 0;
	float nNearestDistance = 100000;

	if (m_bPickAnyway)
	    gMap->getObjectManager()->getObjects(mapObjectType_Item, objList);
	else
		GetPropNotInProtection(&objList);

	for (it = objList.begin(); it != objList.end(); )
	{
		CMapItem *pProp = (CMapItem*)(*it);

		// 排除拾取异常道具
		if (Pick::CheckPropInException(pProp->GetId()))
		{
			it = objList.erase(it);
			continue;
		}

		if (pActionCondition->nPickMode == 2)
		{
			if (pProp->GetItemData()->quality == 0)
			{
				it = objList.erase(it);
				continue;
			}
		}

		if (!gGridsManager->countEmpty((emGridsType)(pProp->GetItemData()->type - emGrids_BagEquip + 1)))	// 可叠加物品最多掉落5个，这里用最大限度
		{
			it = objList.erase(it);
			continue;
		}

		Point ptMe	= Point(gHero->GetCellX(), gHero->GetCellY());
		Point ptProp	= Point(pProp->GetCellX(), pProp->GetCellY());
		float nThisDistance = (ptProp.x - ptMe.x) * (ptProp.x - ptMe.x) + (ptProp.y - ptMe.y) * (ptProp.y - ptMe.y);
		if (nThisDistance < nNearestDistance)
		{
			nNearestDistance = nThisDistance;
			nNearestIndex = i;
		}

		it++;
		i++;
	}
	Pick::UpdatePropInProtection();

	if (nNearestIndex != -1)
	{
		data.target = *(int*)objList[nNearestIndex];
		(m_pActionExecutor->*m_pActionFunc)(&data);
			
		return true;
	}

	return false;
}




int GetTheSmallestMedicineByDType(int dtype)
{
	static vector<int> vtrIndices[2];
	string hmp[2] = {AutoFightData.get(1)->hp, AutoFightData.get(1)->mp};
	if (vtrIndices[dtype].size() == 0)
	{
		vector<string> des;
		StringSplit(hmp[dtype], ";", des);
		for (size_t i = 0; i < des.size(); i++)
		{
			vtrIndices[dtype].push_back(StringConverter::toInt(des[i]));
		}
	}

	for (size_t i = 0; i < vtrIndices[dtype].size(); i++)
	{
		CItem *pItem = gGridsManager->findItemByDataID(emGrids_BagZaWu, vtrIndices[dtype][i]);
		if (pItem && !pItem->IsCding())
		{
			return pItem->getIndex();
		}				
	}

	return -1;
}

int GetRightSkill(int nSkillMode)
{
	static vector<int> vtrIndices[3][3];
	string hmp[9] = {	AutoFightData.get(1)->skill10, AutoFightData.get(1)->skill11, AutoFightData.get(1)->skill12,
						AutoFightData.get(1)->skill20, AutoFightData.get(1)->skill21, AutoFightData.get(1)->skill22,
						AutoFightData.get(1)->skill30, AutoFightData.get(1)->skill31, AutoFightData.get(1)->skill32	};

	nSkillMode = nSkillMode - 1;

	if (vtrIndices[gHero->GetCareer() - 1][nSkillMode].size() == 0)
	{
		vector<string> des;
		StringSplit(hmp[(gHero->GetCareer() - 1) * 3 + nSkillMode], ";", des);
		for (size_t i = 0; i < des.size(); i++)
		{
			vtrIndices[gHero->GetCareer() - 1][nSkillMode].push_back(StringConverter::toInt(des[i]));
		}
	}

	for (size_t i = 0; i < vtrIndices[gHero->GetCareer() - 1][nSkillMode].size(); i++)
	{
		CSkill *pSkill = gHero->GetSkill(vtrIndices[gHero->GetCareer() - 1][nSkillMode][i]);
		if (pSkill && pSkill->GetCDTime() <= 0)
		{
			return pSkill->GetDataID();
		}				
	}

	return 0;
}

void CHMPMonitor::SaveConfigToFile()
{
	char strHeroID[20] = {};
	sprintf(strHeroID, "_%lld", gHero->GetId());
	string strSuffix = strHeroID;

	CCUserDefault::getInstance()->setIntegerForKey(("HPRedLine" + strSuffix).c_str(),((Condition*)m_pActionCondition)->nHPRedLine);
	CCUserDefault::getInstance()->setIntegerForKey(("MPRedLine" + strSuffix).c_str(),((Condition*)m_pActionCondition)->nMPRedLine);
}

bool CHMPMonitor::update(float dt)
{
	if (!CMonitor::update(dt))
	{
		return false;
	}

	Condition *pActionCondition = (Condition*)m_pActionCondition;
	ActionData data = {};

	//if (pActionCondition->bHPRedLine)
	{
		if (gHero->GetHPMax()!= 0 && gHero->GetHP() * 100 / gHero->GetHPMax() < pActionCondition->nHPRedLine)
		{
			int index = GetTheSmallestMedicineByDType(0);
			if (index != -1)
			{
				CItem *pProp = gGridsManager->getGirdItem(emGrids_BagZaWu, index);
				static double fLastEatingTime = 0.0;
				
				if(fLastEatingTime + 0.5 < fNow && !pProp->IsCding())
				{
					data.action = CM_HP;
					data.target = index;
					fLastEatingTime = fNow;
					goto End;
				}
			}
		}
	}
	//if (pActionCondition->bMPRedLine)
	{
		if (gHero->GetMPMax() != 0 && gHero->GetMP() * 100 / gHero->GetMPMax() < pActionCondition->nMPRedLine)
		{
			int index = GetTheSmallestMedicineByDType(1);
			if (index != -1)
			{
				CItem *pProp = gGridsManager->getGirdItem(emGrids_BagZaWu, index);
				static double fLastEatingTime = 0.0;
				if (fLastEatingTime + 0.5 < fNow && !pProp->IsCding() )
				{
					data.action = CM_MP;
					data.target = index;
					fLastEatingTime = fNow;
					goto End;
				}
			}
		}
	}

End:

	if (data.action)
	{
		(m_pActionExecutor->*m_pActionFunc)(&data);
		return true;
	}

	return false;
}

MapObject* GetNearestEntityByType(MapObjectType type, Point ptCenter, int nRaidus)
{
	MapObjectList objList;
	gMap->getObjectManager()->getObjectsInView(objList);
	MapObjectList::iterator it;
	float nNearestDistance = 100000;

	MapObject *pObj = NULL;
	for (it = objList.begin(); it != objList.end(); it++)
	{
		if (*it != gHero && (*it)->GetType() == type && dynamic_cast<RoleFighter*> (*it) && !((RoleFighter*)(*it))->IsDead())
		{
			// 塔防NPC用怪物实现，不攻击
			//if ((*it)->GetType() == mapObjectType_Monster && (((MonsterData*)((CMonster*)(*it))->getData())->isTowerDefencer
			//	|| (((MonsterData*)((CMonster*)(*it))->getData())->data_id == DefensePet_Data_Id_InTowerDefenseCopy 
			//	|| ((MonsterData*)((CMonster*)(*it))->getData())->data_id == Tower_Data_Id_InTowerDefenseCopy)))
			//{
			//	continue;
			//}
			if (abs((*it)->GetCellX() - ptCenter.x) > nRaidus
				|| abs((*it)->GetCellY() - ptCenter.y) > nRaidus)
			{
				continue;
			}

			Point ptMe	= Point(gHero->GetCellX(), gHero->GetCellY());
			Point ptProp	= Point((*it)->GetCellX(), (*it)->GetCellY());
			float nThisDistance = (ptProp.x - ptMe.x) * (ptProp.x - ptMe.x) + (ptProp.y - ptMe.y) * (ptProp.y - ptMe.y);
			if (nNearestDistance > nThisDistance)
			{
				nNearestDistance = nThisDistance;
				pObj = *it;
			}
		}
	}

	return pObj;
}

int GetEntityAroundByType(MapObject *pCenter, MapObjectType type, MapObjectList& objects)
{
	Point ptMe = Point(pCenter->GetCellX(), pCenter->GetCellY());

	MapObjectList objList;
	gMap->getObjectManager()->getObjectsInView(objList);
	MapObjectList::iterator it;

	for (it = objList.begin(); it != objList.end(); it++)
	{
		if (*it != pCenter && (*it)->GetType() == type && dynamic_cast<RoleFighter*> (*it) && !((RoleFighter*)(*it))->IsDead())
		{
			Point ptProp	= Point((*it)->GetCellX(), (*it)->GetCellY());
			float nThisDistance = (ptProp.x - ptMe.x) * (ptProp.x - ptMe.x) + (ptProp.y - ptMe.y) * (ptProp.y - ptMe.y);
			if (nThisDistance <= 2)
			{
				objects.push_back(*it);
			}
		}
	}

	return objects.size();
}

bool SKillCanRelease(int skilltype, MapObjectID nTargetID)
{
	return true;
}


bool CFightMonitor::update(float dt)
{
	if (!CMonitor::update(dt))
	{
		return false;
	}

	SetCenter(Point(gHero->GetCellX(), gHero->GetCellY()));

	Condition *pActionCondition = (Condition*)m_pActionCondition;
	m_nTargetID = 0;

	MapObject *pPlayer = GetNearestEntityByType(mapObjectType_Player, m_ptCenter, pActionCondition->nMoveRange);
	if (pPlayer && gPKMode->CanIFightHim((CPlayer*)pPlayer))
	{
		m_nTargetID = pPlayer->GetId();
	}

	if (m_nTargetID == 0)
	{
		MapObject *pMonster = GetNearestEntityByType(mapObjectType_Monster, m_ptCenter, pActionCondition->nMoveRange);
		if (pMonster)
		{
			m_nTargetID = pMonster->GetId();
		}
		else
		{
			return false;
		}
	}

	ActionData data = {(eConditionMet)0, m_nTargetID, 0};

	//CRole* pTarget = dynamic_cast<CRole*> (gMap->getObjectManager()->getObject(m_nTargetID));
	//if (abs(pTarget->GetCellX() - gHero->GetCellX()) > 1 || abs(pTarget->GetCellY() - gHero->GetCellY()) > 1)
	//{
	//	// 逼近
	//	data.action = CM_Approach;
	//}
	//else
	{
		data.action = CM_Attack;
		data.skill = GetRightSkill(pActionCondition->nAttackMode);
	}

	if (data.action && data.target && data.skill)
	{
		(m_pActionExecutor->*m_pActionFunc)(&data);
		return true;
	}

	return false;
}

void LoadAutoMovePortsOfThisMap()
{
	MapCfg *pMap = gMap->getMapData();
	if (!pMap)
		return;

    vector<string> des;
    //StringUtil::StringSplit(pMap->automoveports,";",des);	// 后续可能需要
	RandWalk::s_AutoMovePorts.clear();
	RandWalk::s_itCurPort = RandWalk::s_AutoMovePorts.end();
	float nNearestDistance = 99999999.9f;
	int nNearestIndex = 0;
	for (size_t i = 0; i < des.size(); i++)
	{
		vector<string> des2;
		StringSplit(des[i],",",des2);
		if (des2.size() != 2)
		{
			continue;
		}

		Point ptMe	= Point(gHero->GetCellX(), gHero->GetCellY());
		Point ptProp	= Point(StringConverter::toInt(des2[0]), StringConverter::toInt(des2[1]));
		RandWalk::s_AutoMovePorts.push_back(ptProp);

		// locate me to the nearest port.
		
		float nThisDistance = ptProp.getDistance(ptMe);
		if (nNearestDistance > nThisDistance)
		{
			nNearestDistance = nThisDistance;
			nNearestIndex = i;
		}
	}
	RandWalk::s_itCurPort = RandWalk::s_AutoMovePorts.begin() + nNearestIndex;
}




Robot::Robot(): m_pCurAction()	
{
	m_Condition.nAttackMode = 1;
	m_Condition.nHPRedLine = 50;
	m_Condition.nMPRedLine = 50;
	m_Condition.nMoveRange = 15;
	m_Condition.nPickMode = 1;

	m_bRunning = false; m_pConAction = NULL;
	m_PropMonitor.SetActionHandler(this, (Monitor_Trigger)&Robot::ConditionMet);
	m_HMPMonitor.SetActionHandler(this, (Monitor_Trigger)&Robot::ConditionMet); 
	m_FightMonitor.SetActionHandler(this, (Monitor_Trigger)&Robot::ConditionMet);
	m_FightMonitor.InitWithConditions(&m_Condition);
	m_PropMonitor.InitWithConditions(&m_Condition);
	m_HMPMonitor.InitWithConditions(&m_Condition);
	//m_eMoveRange = RMR_GLOBAL; 
	m_bActionException = false;
}

void Robot::SetRunning(bool bRunning)	
{
	m_bRunning = bRunning; ReplaceAction(NULL);
	ConcurrentAction(NULL);
	m_ptCenter = Point(gHero->GetCellX(), gHero->GetCellY());

	if (bRunning)
	{
		LoadAutoMovePortsOfThisMap();
	}
	else
	{
		Attack::ClearStatics();
		Pick::s_PropsInException.clear();
		m_FightMonitor.Reset();
	}

	m_PropMonitor.SetRunning(bRunning);
	m_PropMonitor.SetCenter(m_ptCenter);
	m_FightMonitor.SetRunning(bRunning);
	m_FightMonitor.SetCenter(m_ptCenter);
}

void Robot::update(float dt)
{
	if(!gMap) return;

	if (gHero->IsDead())
	{
		SetRunning(false);
		return;
	}

	// 一键拾取
	//m_pPicker.update(dt);

	// 后续的需求要求一些功能在非挂机状态下依然生效（相当于非挂机人物自动行为功能）
	if (!m_pConAction || m_pConAction->IsDone())
	{
		m_HMPMonitor.SetRunning(true);
		m_HMPMonitor.update(dt);
	}

	if (m_bActionException)
	{
		// 换目标攻击
		if (dynamic_cast<Attack*>(m_pCurAction))
		{
			m_FightMonitor.Reset();
		}

		ReplaceAction(new ExceptionAction(Point(gHero->GetCellX(), gHero->GetCellY()), Point(5.0f, 5.0f)));
		m_bActionException = false;
		return;
	}

	bool bActionDone = (!m_pCurAction || m_pCurAction->IsDone());
	if (bActionDone)
	{
		if (CSuperMove::Instance()->IsPause())
			CSuperMove::Instance()->Resume();

		if (m_FightMonitor.updateEx(dt))
			return;

		ReplaceAction(NULL);
		if (gHero->IsMoving())	// 玩家手动控制移动优先
		{
			return;
		}
	}

	// 下面是挂机部分
	if (!m_bRunning)	return;

	if (bActionDone || dynamic_cast<RandWalk*>(m_pCurAction) || dynamic_cast<StandStill*>(m_pCurAction))
	{
		if (!m_PropMonitor.update(dt) && !m_FightMonitor.update(dt) && bActionDone)
		{
			Idle();
		}
	}
}

void Robot::Idle()
{
	RobotAction *pAction = NULL;
	ReplaceAction((rand() % 2) ? pAction = new RandWalk(m_ptCenter, Point(m_Condition.nMoveRange, m_Condition.nMoveRange)) : pAction = new StandStill);
}

void Robot::ConditionMet(void *pData)
{
	CMonitor::ActionData* pD = ((CMonitor::ActionData*)pData);
	//m_PropMonitor.SetRunning(false);
	
	switch (pD->action)
	{
	case CFightMonitor::CM_Approach:
		{
			// 因底层移动问题，将动作临时解决方案
			static double sNow = fNow - 1;
			if (sNow + 0.2 < fNow)
			{
				ReplaceAction(new Approach(pD->target, this, (ActionException)&Robot::ActionNeedAbortion));
				sNow = fNow;
			}
		}
		break;
	case CFightMonitor::CM_Attack:
		ReplaceAction(new Attack(pD->target, pD->skill, this, (ActionException)&Robot::ActionNeedAbortion));
		break;
	case CPropMonitor::CM_Pick:
		{	
			// 因底层移动问题，将动作临时解决方案
			static double sNow = fNow - 1;
			if (sNow + 0.55 < fNow)
			{
				ReplaceAction(new Pick((CMapItem*)pD->target, this, (ActionException)&Robot::ActionNeedAbortion));
				sNow = fNow;
			}

		}
		break;
	case CHMPMonitor::CM_HP:
	case CHMPMonitor::CM_MP:
		ConcurrentAction(new Use(pD->target));
		SetRunning(false);
		break;
	case CMonitor::CM_CONFIG_CHANGED:
		Save();
		break;
	}
}

void Robot::ActionNeedAbortion(int)
{
	m_bActionException = true;
}

void Robot::Save()
{
	m_FightMonitor.SaveConfigToFile();
	m_PropMonitor.SaveConfigToFile();
	m_HMPMonitor.SaveConfigToFile();
}





Picker::Picker(): m_bRuning(), m_pAction()
{
	static CPropMonitor::Condition cond;
	//cond.bPickEquipment = true;
	//cond.bPickMoney = true;
	//cond.bPickMedicine = true;
	//cond.bPickOther = true;

	m_Monitor.InitWithConditions(&cond);
	m_Monitor.SetActionHandler(this, (Monitor_Trigger)&Picker::PropConditionMet);
}

Picker::~Picker()
{
}

void Picker::Start()
{
	m_bRuning = true;
	if (gRobot->IsRunning())
		gRobot->SetRunning(false);
	m_Monitor.SetRunning(true);
	m_Monitor.PickAnyway(GetPropNotInProtection(NULL) == 0);
}

void Picker::PropConditionMet(void *pData)
{
	delete m_pAction;
	CPropMonitor::ActionData* pD = ((CPropMonitor::ActionData*)pData);
	m_pAction = new PickEx((CMapItem*)pD->target, this, (ActionException)&Picker::PickNeedAbortion);
	m_Monitor.SetRunning(false);
}

void Picker::PickNeedAbortion(int)
{
	m_Monitor.SetRunning(false);
	delete m_pAction; m_pAction = NULL;
	m_bRuning = false;
}

void Picker::update(float dt)
{
	//if (!m_bRuning)	return;

	//if (m_pAction)
	//{
	//	if (m_pAction->IsDone() && m_bRuning)	// 有可能已经发生异常而关闭捡取过程
	//	{
	//		m_Monitor.PickAnyway(GetPropNotInProtection(NULL) == 0);
	//		m_Monitor.SetRunning(true);	
	//	}
	//	else
	//		return;
	//}

	//Point ptTarget = gHero->m_path.size() ? gHero->m_path.back() : gHero->getTargetPos();

	//if (m_pAction /*&& dynamic_cast<RoleMove*>(gHero->getFSM()->getCurrentState())*/ && !m_pAction->GetTargetPos().equals(ptTarget)  // 第一行手动终止条件
	//	|| !m_Monitor.update(dt))
	//{
	//	CCLog("m_pAction = %d RoleMove ? %d", m_pAction, gHero->IsMoving()));
	//	m_Monitor.SetRunning(false);
	//	delete m_pAction; m_pAction = NULL;
	//	m_bRuning = false;
	//}
}

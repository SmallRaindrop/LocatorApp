#include "Hero.h"
#include "TileMap.h"
#include "GameMap.h"
#include "GameLayer.h"
#include "GameManager.h"
#include "db.h"
#include "GameDataManager.h"
#include "Net/pk_item.h"
#include "Net/NetDispatcher.h"
#include "GameUILayer.h"
#include "GridsManager.h"
#include "MessageCenter.h"
#include "MapItem.h"
#include "Net/pk_map.h"
#include "RoleTitle.h"
#include "Robot.h"
#include "Monster.h"
#include "BeginnerGuide.h"
#include "Net/pk_others.h"
#include "GameVariable.h"
#include "Net/pk_move.h"
#include "UI/MainUIFight.h"
#include "cocostudio/CCSkin.h"
#include "RoleTitleLayer.h"
#include "UI/MainUINormal.h"
#include "assert.h"
#include "GameProcess.h"
#include "IndicatorLayer.h"
#include "UI/ReviveUI.h"

void CHero::PathToPosInfo(int cx,int cy,APath& path,vector<pk::PosInfo>& posInfos)
{
	deque<APoint> points = path.getPoints();
	APoint pt = points.front();
	int cx0 = cx;
	int cy0 = cy;
	int dir =  DirectionBy(cx0,cy0,pt.x,pt.y);
	pk::PosInfo pos = { pt.x,pt.y };
	for ( deque<APoint>::iterator itr = points.begin();itr != points.end(); ++itr )
	{
		int dir1 = DirectionBy(cx0,cy0,itr->x,itr->y);
		if ( dir == dir1 )
		{
			pos.x = itr->x;
			pos.y = itr->y;
		}
		else
		{
			posInfos.push_back(pos);
			pos.x = itr->x;
			pos.y = itr->y;
		}
		cx0 = itr->x;
		cy0 = itr->y;
		dir = dir1;
	}

	posInfos.push_back(pos);
}

void CHero::PosInfoToPath(int cx,int cy,vector<pk::PosInfo>& posInfos,APath& path)
{
	path.clear();

	if ( posInfos.empty() )
	{
		return ;
	}

	int cx0 = cx;
	int cy0 = cy;

	for ( size_t i = 0;i<posInfos.size();++i )
	{
		pk::PosInfo pt = posInfos[i];

		int dir = DirectionBy(cx0,cy0,pt.x,pt.y);
		int dis = Distance(pt.x,pt.y,cx0,cy0);
		if ( dis == 0 )
		{
			continue;
		}

		int x = cx0 + _DELTA_CX[dir];
		int y = cy0 + _DELTA_CY[dir];

		int cnt = 0;

		while (x != pt.x || y != pt.y )
		{
			path.push(APoint(x,y));
			cx0 = x;
			cy0 = y;
			x = cx0 + _DELTA_CX[dir];
			y = cy0 + _DELTA_CY[dir];

			// wrong path
			if ( ++cnt > dis )
			{
				path.clear();
				return ;
			}
		}

		path.push(APoint(x,y));
		cx0 = pt.x;
		cy0 = pt.y;
	}
}

void CHero::GetMoveCmd(int mapDataID,int cx,int cy,APath& path,pk::C2GS_PlayerMoveTo& cmd)
{
	PathToPosInfo(cx,cy,path,cmd.posInfos);

	cmd.posX = cx;
	cmd.posY = cy;
	cmd.curMapDataId = mapDataID;
}

CHero::CHero() : m_pSelectTarget(NULL),m_pPickupAction(NULL),
	m_pGuide(NULL),m_bTransDoorFlag(false),m_pIndicatorLayer(nullptr),m_bCanUseSkill(true)
{
	initRole();
}

CHero::~CHero()
{
	LeaveMap();
	m_SkillMgr.Clear();
	m_BuffMgr.Clear();
	CC_SAFE_DELETE(m_pPickupAction);
	CC_SAFE_DELETE(m_pGuide);
	CC_SAFE_RELEASE(m_pRoleModel);
	if(m_pIndicatorLayer)
	{
		m_pIndicatorLayer->removeFromParentAndCleanup(true);
		m_pIndicatorLayer = nullptr;
	}
}

bool CHero::initRole()
{
	m_pData = new HeroData;
	if ( !m_pData )
	{
		return false;
	}

	if ( !CPlayer::initRole() )
	{
		return false;
	}

	m_pRoleModel = RoleModel::create();
	if ( m_pRoleModel )
	{
		m_pRoleModel->retain();
	}
	
	SetType(mapObjectType_Player);

	m_pGuide = new BeginnerGuide;
	if ( !m_pGuide )
	{
		return false;
	}

	AddIndicatorLayer();

	return true;
}

void CHero::update(float dt)
{
	UpdateSkillCd(dt);

	gRobot->update(dt);

	// 新手引导
	if ( m_pGuide )
	{
		m_pGuide->Update(dt);
	}

	// 游戏历程管理
	//gGameProcess->PushEvent(GameProcEvent_Timer);
	gGameProcess->Update(dt);

	GetHallTechManager().Update(dt);
	CPlayer::update(dt);
}

bool CHero::updateMove(float dt)
{
	// 动态阻挡判断
	if ( isDynamicBlock(m_MoveMonitor.GetStepPoint().x,m_MoveMonitor.GetStepPoint().y) )
	{
		SetCell(m_MoveMonitor.GetCurrPoint().x,m_MoveMonitor.GetCurrPoint().y);
		NotifyServerStopMove();
		m_MoveMonitor.Terminate();
		return false;
	}

	// 检测周围死亡的队友
	//MapObjectList playerObjects;
	//GetMap()->getObjectManager()->getObjectsInView(MapObjectType::mapObjectType_Player,playerObjects);
	//for ( size_t i = 0;i<playerObjects.size();++i )
	//{ 
	//	RoleFighter* role = dynamic_cast<RoleFighter*>(playerObjects[i]);
	//	if ( role && role->IsDeadVirtual() && this->GetDistanceTo(role) < 3 )
	//	{
	//		MainUI::GetMainUI()->updateHelpReviveUI(role);
	//	}
	//}

	bool ret = Role::updateMove(dt);

	if ( gMap )
	{
		gMap->updateView();
	}

	// 移动结束需要通知服务器
	if ( !ret )
	{
		NotifyServerStopMove();
		return false;
	}

	searchItemByCell(GetCellX(),GetCellY());

	return ret;
}

bool CHero::updateFlash(float dt)
{
	bool ret = Role::updateFlash(dt);
	if ( gMap )
	{
		gMap->updateView();
	}

	return ret;
}

void CHero::SetLevel(int val)
{
	CPlayer::SetLevel(val);
	//升级刷新背包红色底板
	gGridsManager->UpdateIconMask(emGrids_BagEquip);
	gGridsManager->UpdateIconMask(emGrids_BagMaterial);
	gGridsManager->UpdateIconMask(emGrids_BagZaWu);

	// 抛出历程事件
	gGameProcess->PushEvent(GameProcEvent_LevelUp);

	if ( MainUI::GetActiveMainUI() )
	{
		MainUI::GetActiveMainUI()->updateLv();
	}
}

void CHero::SetExp(__int64 val,bool tips /* = true */)
{
	//系统提示:增加多少经验
	__int64 oldValue = gHero->GetPropertyInt64(RoleProperty_Exp);
	__int64 deltaValue = val - oldValue;
	/* 先不在系统频道显示经验变化
	if ( tips )
	{
		if(deltaValue > 0 )
		{		
			// 经验增加
			gMessageCenter->SystemMessage(165, CCString::createWithFormat("%d",deltaValue)->getCString());			
		}
		else
		{
			// 经验减少
			gMessageCenter->SystemMessage(165, CCString::createWithFormat("%d",deltaValue)->getCString());
		}
	}*/
	
	GetData()->SetProperty(RoleProperty_Exp,val);
}

void CHero::SetMoney(__int64 val,bool tips /* = true */)
{
	//系统提示:增加多少金钱
	__int64 oldValue = gHero->GetPropertyInt(RoleProperty_Coin_b);
	__int64 deltaValue = val - oldValue;
	if ( tips )
	{
		if(deltaValue > 0 )
		{		
			// 金币增加
			gMessageCenter->SystemMessage(164, CCString::createWithFormat("%d",deltaValue)->getCString());			
		}
		else
		{
			// 金币减少
			gMessageCenter->SystemMessage(164, CCString::createWithFormat("%d",deltaValue)->getCString());
		}
	}

	GetData()->SetProperty(RoleProperty_Coin_b,val);
}

void CHero::SetMoneyBind(__int64 val,bool tips /* = true */)
{
	//系统提示:增加多少绑定金钱
	__int64 oldValue = gHero->GetPropertyInt(RoleProperty_Coin_b);
	__int64 deltaValue = val - oldValue;
	if ( tips )
	{
		if(deltaValue > 0 )
		{		
			// 金币增加
			gMessageCenter->SystemMessage(164, CCString::createWithFormat("%d",deltaValue)->getCString());			
		}
		else
		{
			// 金币减少
			gMessageCenter->SystemMessage(164, CCString::createWithFormat("%d",deltaValue)->getCString());
		}
	}

	GetData()->SetProperty(RoleProperty_Coin_b,val);
}

void CHero::SetGold(int val,bool tips /* = true */)
{
	//系统提示:增加多少元宝
	int oldValue = gHero->GetPropertyInt(RoleProperty_Treasure);
	int deltaValue = val - oldValue;
	if ( tips )
	{
		if(deltaValue > 0 )
		{		
			// 元宝增加
			gMessageCenter->SystemMessage(164, CCString::createWithFormat("%d",deltaValue)->getCString());			
		}
		else
		{
			// 元宝减少
			gMessageCenter->SystemMessage(164, CCString::createWithFormat("%d",deltaValue)->getCString());
		}
	}

	GetData()->SetProperty(RoleProperty_Treasure,val);
}

void CHero::SetGoldBind(int val,bool tips /* = true */)
{
	//系统提示:增加多少元宝
	int oldValue = gHero->GetPropertyInt(RoleProperty_Treasure_b);
	int deltaValue = val - oldValue;
	if ( tips )
	{
		if(deltaValue > 0 )
		{		
			// 元宝增加
			gMessageCenter->SystemMessage(164, CCString::createWithFormat("%d",deltaValue)->getCString());			
		}
		else
		{
			// 元宝减少
			gMessageCenter->SystemMessage(164, CCString::createWithFormat("%d",deltaValue)->getCString());
		}
	}

	GetData()->SetProperty(RoleProperty_Treasure_b,val);
}

void CHero::SetHP(__int64 val)
{
	GetData()->SetProperty(RoleProperty_HP,val);

	if ( MainUI::GetActiveMainUI() )
	{
		MainUI::GetActiveMainUI()->updateHp();
	}
}

void CHero::SetHPMax(__int64 val)
{
	GetData()->SetProperty(RoleProperty_hp_max,val);
}

void CHero::SetMP(int val)
{
	GetData()->SetProperty(RoleProperty_MP,val);

	if ( MainUI::GetActiveMainUI() )
	{
		MainUI::GetActiveMainUI()->updateMp();
	}
}

void CHero::SetMPMax(int val)
{
	GetData()->SetProperty(RoleProperty_mp_max,val);
}


void CHero::SetProperty(RoleProperty idx,int val)
{
	switch (idx)
	{
	case RoleProperty_Level: 
		SetLevel(val);
		return;
	case RoleProperty_Exp:
		SetExp(val);
		return;
	case RoleProperty_HP:
		SetHP(val);
		return;
	case RoleProperty_MP:
		SetMP(val);
		return;
	case RoleProperty_Coin:
		SetMoney(val);
		return;
	case RoleProperty_Coin_b:
		SetMoneyBind(val);
		return;
	case RoleProperty_Treasure:
		SetGold(val);
		return;
	default:
		break;
	}
	CPlayer::SetProperty(idx,val);
}

void CHero::SetProperty(RoleProperty idx,__int64 val)
{
	CPlayer::SetProperty(idx,val);
}

void CHero::SetProperty(RoleProperty idx,const string& val)
{
	CPlayer::SetProperty(idx,val);
}

void CHero::setProperty(pk::GS2C_PlayerProperty* value)
{
	SetRoleName(value->name);  // 角色名字
	SetCareer(value->career);  // 职业
	SetStateFlag(value->state);
	SetMoveSpeed(value->speed);
	SetMoney(value->bindCoin,false);
	SetMoneyBind(value->bindCoin,false);
	SetGold(value->treasure,false);
	SetGoldBind(value->bindTreasure,false);
	SetProperty(RoleProperty_Level,value->level);
	SetProperty(RoleProperty_HP,value->hp);
	SetProperty(RoleProperty_MP,value->mp);
	SetProperty(RoleProperty_hp_max,value->hp_max);
	SetProperty(RoleProperty_mp_max,value->mp_max);
	SetProperty(RoleProperty_Exp,value->exp);
	SetProperty(RoleProperty_speed,value->speed);
	SetProperty(RoleProperty_FightValue,value->fight);
	SetProperty(RoleProperty_StateFlag, value->state);
	SetProperty(RoleProperty_VipLevel, value->vipLevel);

	SetProperty(RoleProperty_phy_dam, value->phy_dam);       //物理伤害
	SetProperty(RoleProperty_fire_dam, value->fire_dam);     //火伤害
	SetProperty(RoleProperty_cold_dam, value->code_dam);     //冰伤害  
	SetProperty(RoleProperty_elec_dam, value->elec_dam);     //电伤害  
	SetProperty(RoleProperty_toxin_dam, value->toxin_dam);   //毒伤害  
	SetProperty(RoleProperty_base_dam_increase, value->base_dam_increase);     //基础伤害增强  
	SetProperty(RoleProperty_all_dam_increase, value->all_dam_increase);       //造成伤害系数  
	SetProperty(RoleProperty_all_dam_reduce, value->all_dam_reduce);           //受到伤害系数  
	SetProperty(RoleProperty_atk_power, value->atk_power);     //攻击强度  
	SetProperty(RoleProperty_hp_max,value->hp_max);          //最大生命值
	SetProperty(RoleProperty_hp_r,value->hp_r);              //生命秒回值
	SetProperty(RoleProperty_hp_rp,value->hp_rp);	         //生命秒回比
	SetProperty(RoleProperty_hp_ball,value->hp_ball);	     //血球回血量
	SetProperty(RoleProperty_by_cure_factor,value->by_cure_factor);	 //受到治疗系数
	SetProperty(RoleProperty_mp_max,value->mp_max);	         //最大法力值
	SetProperty(RoleProperty_mp_r,value->mp_r);		         //法力秒回值    
	SetProperty(RoleProperty_mp_ball,value->mp_r);		     //法球回法力量  
	SetProperty(RoleProperty_speed,value->speed);	         //移动速度
	SetProperty(RoleProperty_armor,value->armor);	         //护甲
	SetProperty(RoleProperty_armor_reduce,value->armor_reduce);	        //护甲削弱
	SetProperty(RoleProperty_phy_res,value->phy_res);	                //物理抗性
	SetProperty(RoleProperty_fire_res,value->fire_res);	                //火抗性
	SetProperty(RoleProperty_cold_res,value->cold_res);	                //冰抗性
	SetProperty(RoleProperty_elec_res,value->elec_res);	                //电抗性
	SetProperty(RoleProperty_toxin_res,value->toxin_res);	            //毒抗性
	SetProperty(RoleProperty_tough,value->tough);	                    //坚韧
	SetProperty(RoleProperty_penetrate,value->penetrate);	            //穿深
	SetProperty(RoleProperty_thickness,value->thickness);	            //厚度
	SetProperty(RoleProperty_crit,value->crit_p);	                    //暴击率
	SetProperty(RoleProperty_crit_dam_factor,value->crit_hurt);	        //暴击伤害系数
	SetProperty(RoleProperty_accurate,value->accurate_p);	            //精准率
	SetProperty(RoleProperty_dodge,value->dodge_p);	                    //躲闪率
	SetProperty(RoleProperty_trigger,value->trigger_p);	                //触发率
	SetProperty(RoleProperty_atk_speed_increase,value->atk_speed_increase);	    //攻击加速
	SetProperty(RoleProperty_mp_efficiency,value->mp_efficiency);	            //节约法力
	SetProperty(RoleProperty_skill_duration,value->skill_duration);	            //技能持久
	SetProperty(RoleProperty_skill_power,value->skill_power);	                //技能强度
	SetProperty(RoleProperty_skill_range,value->skill_rang);	                //技能范围
	SetProperty(RoleProperty_RecoverCount,value->recoverCount);	                //免费复活次数
}

void CHero::setFightProperty(pk::GS2C_PlayerFightProperty* value)
{
	SetProperty(RoleProperty_StateFlag, value->state);
	SetProperty(RoleProperty_HP,value->hp);
	SetProperty(RoleProperty_MP,value->mp);

	SetProperty(RoleProperty_phy_dam, value->phy_dam);       //物理伤害
	SetProperty(RoleProperty_fire_dam, value->fire_dam);     //火伤害
	SetProperty(RoleProperty_cold_dam, value->code_dam);     //冰伤害  
	SetProperty(RoleProperty_elec_dam, value->elec_dam);     //电伤害  
	SetProperty(RoleProperty_toxin_dam, value->toxin_dam);   //毒伤害  
	SetProperty(RoleProperty_base_dam_increase, value->base_dam_increase);     //基础伤害增强  
	SetProperty(RoleProperty_all_dam_increase, value->all_dam_increase);       //造成伤害系数  
	SetProperty(RoleProperty_all_dam_reduce, value->all_dam_reduce);           //受到伤害系数  
	SetProperty(RoleProperty_atk_power, value->atk_power);     //攻击强度  
	SetProperty(RoleProperty_hp_max,value->hp_max);          //最大生命值
	SetProperty(RoleProperty_hp_r,value->hp_r);              //生命秒回值
	SetProperty(RoleProperty_hp_rp,value->hp_rp);	         //生命秒回比
	SetProperty(RoleProperty_hp_ball,value->hp_ball);	     //血球回血量
	SetProperty(RoleProperty_by_cure_factor,value->by_cure_factor);	 //受到治疗系数
	SetProperty(RoleProperty_mp_max,value->mp_max);	         //最大法力值
	SetProperty(RoleProperty_mp_r,value->mp_r);		         //法力秒回值    
	SetProperty(RoleProperty_mp_ball,value->mp_r);		     //法球回法力量  
	SetProperty(RoleProperty_speed,value->speed);	         //移动速度
	SetProperty(RoleProperty_armor,value->armor);	         //护甲
	SetProperty(RoleProperty_armor_reduce,value->armor_reduce);	        //护甲削弱
	SetProperty(RoleProperty_phy_res,value->phy_res);	                //物理抗性
	SetProperty(RoleProperty_fire_res,value->fire_res);	                //火抗性
	SetProperty(RoleProperty_cold_res,value->cold_res);	                //冰抗性
	SetProperty(RoleProperty_elec_res,value->elec_res);	                //电抗性
	SetProperty(RoleProperty_toxin_res,value->toxin_res);	            //毒抗性
	SetProperty(RoleProperty_tough,value->tough);	                    //坚韧
	SetProperty(RoleProperty_penetrate,value->penetrate);	            //穿深
	SetProperty(RoleProperty_thickness,value->thickness);	            //厚度
	SetProperty(RoleProperty_crit,value->crit_p);	                    //暴击率
	SetProperty(RoleProperty_crit_dam_factor,value->crit_hurt);	        //暴击伤害系数
	SetProperty(RoleProperty_accurate,value->accurate_p);	            //精准率
	SetProperty(RoleProperty_dodge,value->dodge_p);	                    //躲闪率
	SetProperty(RoleProperty_trigger,value->trigger_p);	                //触发率
	SetProperty(RoleProperty_atk_speed_increase,value->atk_speed_increase);	    //攻击加速
	SetProperty(RoleProperty_mp_efficiency,value->mp_efficiency);	            //节约法力
	SetProperty(RoleProperty_skill_duration,value->skill_duration);	            //技能持久
	SetProperty(RoleProperty_skill_power,value->skill_power);	                //技能强度
	SetProperty(RoleProperty_skill_range,value->skill_rang);	                //技能范围
}

void CHero::setSingleProperty(RoleProperty idx, __int64 value)
{
	SetProperty(idx,value);
	SetProperty(idx,(int)value);
}

void CHero::ChangeMap(ResID mapID,int cx,int cy)
{
	gHero->LeaveMap();

	if ( gMap && gMap->getMapDataID() == mapID )
	{
		gHero->SetCell(cx,cy);
		return ;
	}
	
	gGameLayer->switchMap(mapID,cx,cy);

	// 重新创建标题头
	if ( !m_pRoleTitle )
	{
		m_pRoleTitle = RoleTitle::createWithRole(this);
		if ( m_pRoleTitle )
		{
			gRoleTitleLayer->addChild(m_pRoleTitle);
		}
	}

	AddIndicatorLayer();

	SetRoleName(GetRoleName());
}

bool CHero::PursueCheck()
{
	RoleFighter *pEnemy = GetMapRole(m_nPursueTargetID);
	if ( !pEnemy )
	{
		return false;
	}

	if( !IsInjured() && !IsDead() )
	{
		return true;
	}

	return false;
}

bool CHero::PursueOk()
{
	return Role::PursueOk();
}

void CHero::onEnterDoor(CRegion* pRegion)
{
	//Stop();
	m_bTransDoorFlag = true;

	int low = pRegion->getProperty("door_id_low");
	int high = pRegion->getProperty("door_id_high");
	if(low == 0 && high == 0)
	{
		pk::C2GS_ReqChangeMapInTransport cmd;
		cmd.curMapDataID = gMap->getMapDataID();
		cmd.Send(gNetSocket);
	}
	else
	{
		pk::C2GS_ReqChangeMapInDynamicTransport cmd;
		cmd.curMapDataID = gMap->getMapDataID();
		int64 doorId = high;
		doorId = ((doorId << 32) |  low );
		cmd.doorId = doorId;
		cmd.Send(gNetSocket);
	}
}

void CHero::EnterMap(TileMap* pMap,int cx,int cy)
{
	RoleFighter::EnterMap(pMap,cx,cy);
	gMap->setGrey(false);
	gMap->updateView();

	m_bTransDoorFlag = false;

	// 抛出历程事件
	gGameProcess->PushEvent(GameProcEvent_EnterMap);

	// 显示主界面
	MainUI::ShowMainUI(gMap->getFuncType());
}

void CHero::LeaveMap()
{
	SelectTargetCancel();
	RoleFighter::LeaveMap();
}

void CHero::setPosition(float x,float y)
{	
	setPosition(Point(x,y));
}

void CHero::setPosition(const Point &position)
{
	RoleFighter::setPosition(position);
	gIndicatorLayer->UpdateIndicators();
}

void CHero::SetCell(int cx,int cy)
{
	RoleFighter::SetCell(cx,cy);
}

void CHero::MoveTo(int cx,int cy)
{
	if ( !gMap )
	{
		return ;
	}

	if ( IsForbiddenMove() )
	{
		return ;
	}

	if ( m_MoveMonitor.IsStepOver() )
	{
		APath path;
		GetMap()->searchForPath(GetCellX(),GetCellY(),cx,cy,path);
		if ( path.size() > 0 )
		{
			APoint pt = path.getPoints().front();
			// 动态阻挡判断 判断第一个点是否为动态阻挡点
			if ( isDynamicBlock(pt.x,pt.y))
			{
				path.clear();
			}
			else
			{
				pk::C2GS_PlayerMoveTo cmd;
				GetMoveCmd(gMap->getMapDataID(),GetCellX(),GetCellY(),path,cmd);
				cmd.Send(gNetSocket);
			}
		}
		Move(path);
	}
	else
	{
		RoleCommand cmd;
		cmd.type = RoleCommand_Move;
		cmd.param.pos.x = cx;
		cmd.param.pos.y = cy;
		pushCommand(cmd);

		Stop();
	}
	
}

void CHero::MoveBy(__Dir dir)
{
	if ( !GetMap() )
	{
		return ;
	}

	// 如果正在做移动处理，先停止移动
	if ( !GetMoveMonitor().IsStepOver() && GetMoveMonitor().GetPath().size() > 0 && getDir() != dir )
	{
		Stop();
		return ;
	}

	// 如果单步移动未完成，直接返回等待
	if ( !GetMoveMonitor().IsStepOver() )
	{
		return ;
	}

	changeDir(dir);

	static const int _MAX_STEP_ = 5;

	APoint start,end;

	start.x = GetCellX();
	start.y = GetCellY();

	for ( int i = 0;i<_MAX_STEP_;++i )
	{
		int cx0 = start.x+_DELTA_CX[dir]*i;
		int cy0 = start.y+_DELTA_CY[dir]*i;

		if( GetMap()->getTerrain()->getCell(cx0,cy0)->isMark(cellMaskStop) )
		{
			break;
		}

		end.x = cx0;
		end.y = cy0;
	}

	RoleCommand cmd;
	cmd.type = RoleCommand_Move;
	cmd.param.pos.x = end.x;
	cmd.param.pos.y = end.y;
	pushCommand(cmd);
}

void CHero::NotifyServerStopMove()
{
	pk::C2GS_PlayerStopMove cmd;
	cmd.curMapDataId = gMap->getMapDataID();

	if ( GetMoveMonitor().IsStepOver() )
	{
		cmd.posX = GetCellX();
		cmd.posY = GetCellY();
	}
	else
	{
		cmd.posX = GetMoveMonitor().GetStepX();
		cmd.posY = GetMoveMonitor().GetStepY();
	}

	cmd.Send(gNetSocket);
}

void CHero::processCommand(const RoleCommand& cmd)
{
	Role::processCommand(cmd);

	if ( cmd.type == RoleCommand_Attack )
	{
		Attack(cmd.param.skill.skillid);
	}

	if ( cmd.type == RoleCommand_Skill )
	{
		SkillCfg* pSkill = SkillData.get(cmd.param.skill.skillid);
		if ( !pSkill )
		{
			gMessageCenter->SystemMessage(93);
			return ;
		}

		switch( pSkill->targettype)
		{
		case SkillTarget_Target: 
			{
				RoleFighter* pTarget = GetMapRole(cmd.param.skill.targetid);
				if ( pTarget )
				{
					UseSkill(pSkill,pTarget);
				}
			}
			break;
		case SkillTarget_Point:
			{
				RoleFighter* pTarget = GetMapRole(cmd.param.skill.targetid);
				// 未找到目标，获取面前指定点为目标
				if ( !pTarget )
				{
					int cx = 0;
					int cy = 0;
					GetCellByDir(pSkill->distance,cx,cy);
					UseSkill(pSkill,cx,cy,0,0);
					return ;
				}
				// 找到目标判断目标的距离是否在攻击距离之内，追击目标
				else
				{
					Point offset = pTarget->getHungingPointOffset(2);
					UseSkill(pSkill,pTarget->GetCellX(),pTarget->GetCellY(),offset.x,offset.y);
				}
			}
			break;
		default: break;
		}
	}
}

void CHero::SelectTargetNearBy()
{
	RoleFighter* pTarget = NULL;
	if ( m_pSelectTarget )
	{
		RoleFighter* pTarget = dynamic_cast<RoleFighter*>(m_pSelectTarget);
		if( pTarget && !pTarget->IsDead() && IsEnemyTo(pTarget) )
		{
			return ;
		}
		else
		{
			SelectTargetCancel();
		}
	}
	
	MapObjectList monsterList;
	gMap->getObjectManager()->getObjectsInView(mapObjectType_Monster,monsterList);
	int minD = 9999;
	for ( size_t i = 0;i<monsterList.size();++i )
	{
		RoleFighter* role = dynamic_cast<RoleFighter*>(monsterList[i]);
		if ( role && !role->IsDead() && IsEnemyTo(role) )
		{
			int distance = Distance(GetCellX(),GetCellY(),role->GetCellX(),role->GetCellY());
			if ( distance < minD )
			{
				pTarget = role;
				minD = distance;
			}
		}
	}

	SelectTarget(pTarget);
}

bool CHero::TryPickupItem()
{
	if(m_pPickupAction && m_pPickupAction->pickUp() )
	{
		delete m_pPickupAction;
		m_pPickupAction = NULL;
		return true;
	}
	return false;
}

bool CHero::SelectTargetByPos(Point pos)
{
	if ( gMap )
	{
		MapObject* pObject = gMap->getObjectManager()->SelectObject(pos.x,pos.y,this);
		if ( pObject )
		{
			if( dynamic_cast<RoleFighter*> (pObject) )
			{
				//select a role
				SelectTarget(pObject);
				return true;
			}
			else if( dynamic_cast<CMapItem*> (pObject) )
			{
				//select a map item
				// replace m_pPickupAction
				CMapItem* pMapItem = dynamic_cast<CMapItem*> (pObject);			
				if(m_pPickupAction && m_pPickupAction->GetId() == pObject->GetId() )
				{
				
				}
				else
				{
					if(m_pPickupAction)
					{
						delete m_pPickupAction;
					}
					CPickupItemAction *pAction = new CPickupItemAction();
					pAction->initWithMapItem(pMapItem);
					m_pPickupAction = pAction;
				}
				//try to pick up
				TryPickupItem();

				//仍然要让调用者继续往下执行，return false
				return false;
			}
			else 
			{
				return false;
			}		
		}
	}

	return false;
}

bool CHero::searchItemByCell(int cx, int cy)
{
	if(gMap)
	{
		MapObject * pMapObject = gMap->getObjectManager()->getObjectNearBy(cx, cy, mapObjectType_Item);
		if(pMapObject && dynamic_cast<CMapItem*>(pMapObject))
		{
			CMapItem * pObject = dynamic_cast<CMapItem*>(pMapObject);	
			if(m_pPickupAction && m_pPickupAction->GetId() == pObject->GetId() )
			{

			}
			else
			{
				if(m_pPickupAction)
				{
					delete m_pPickupAction;
				}
				CPickupItemAction *pAction = new CPickupItemAction();
				pAction->initWithMapItem(pObject);
				m_pPickupAction = pAction;
			}
			//try to pick up
			if(TryPickupItem())
				return true;
		}
	}
	return false;
}


bool CHero::searchItemByCell(Point cell)
{
	return searchItemByCell(cell.x, cell.y);
}


void CHero::SelectTargetCancel()
{
	if ( m_pSelectTarget )
	{
		m_pSelectTarget->onSelect(false);
		m_pSelectTarget = NULL;
	}
}

void CHero::SelectTarget(MapObject* pTarget)
{
	if (pTarget)
	{
		SelectTargetCancel();
		m_pSelectTarget = pTarget;
		m_pSelectTarget->onSelect(true);
	}
}

void CHero::Equip(int pos)
{
	CItem* pItem = gGridsManager->getGirdItem(emGrids_BagEquip,pos);
	if ( !pItem )
	{
		return ;
	}
	// 等级检查
	if ( pItem->getUseLevel() > GetLevel() )
	{
		gMessageCenter->SystemMessage(84);
		return;
	}
	// 职业检查
	if ( pItem->getUseCareer() != GetCareer() )
	{
		gMessageCenter->SystemMessage(84);
		return;
	}
	EquipColumnType part = pItem->getEquipColumnType();
	if ( part == EquipColumn_Max )
	{
		return;
	}
	pk::C2GS_EquipItem cmd;
	cmd.index = pos;
	cmd.part = part;
	cmd.Send(gNetSocket);
}

void CHero::UnEquip(EquipColumnType type)
{
	CItem* pItem = gGridsManager->getGirdItem(emGrids_Role,type);
	if ( pItem )
	{
		pk::C2GS_UnequipItem cmd;
		cmd.part = type;
		cmd.Send(gNetSocket);
	}
}

void CHero::OnEquiped(int pos,EquipColumnType type)
{
	CItem* pItem = gGridsManager->removeGrid(emGrids_BagEquip,pos);
	if ( pItem )
	{
		CItem* pItemEquip = gGridsManager->removeGrid(emGrids_Role,type);
		if ( pItemEquip )
		{
			gGridsManager->insertGrid(emGrids_BagEquip,pos,pItemEquip,true);
		}

		gGridsManager->insertGrid(emGrids_Role,type,pItem,true);

		if ( type == EquipColumn_Weapon )
		{
			SetWeapon(pItem->getArtID());
		}
	}
}

void CHero::OnUnEquiped(int pos,EquipColumnType type)
{
	CItem* pItem = gGridsManager->removeGrid(emGrids_Role,type);
	if ( pItem )
	{
		gGridsManager->insertGrid(emGrids_BagEquip,pos,pItem,true);
	}

	if ( type == EquipColumn_Weapon )
	{
		SetWeapon(0);
	}
}

void CHero::RefreshEquip()
{
	CPlayer::RefreshEquip();

	if ( m_pRoleModel )
	{
		m_pRoleModel->setAppearance(10101010,0,0);
	}	
}

void CHero::UseItem(int pos)
{
	CItem* pItem = gGridsManager->getGirdItem(emGrids_BagEquip,pos);
	if ( !pItem )
	{
		return ;
	}
	UseItem(pItem);
}

void CHero::UseItem(CItem* pItem)
{
	// 等级检查
	if ( pItem->getUseLevel() > GetLevel() )
	{
		gMessageCenter->SystemMessage(84);
		return;
	}
	// 职业检查
	if ( pItem->getUseCareer())
	{
	}

	pk::C2GS_UseItem cmd;
	cmd.bagType = pItem->getType();
	cmd.itemId = pItem->getId();
	cmd.index = pItem->getIndex();
	cmd.Send(gNetSocket);
}

//
//bool CHero::IsMagicReady()
//{
//	if ( m_pSkillDataLocked && m_pTargetLocked )
//	{
//		int dis = Distance(GetCellX(),GetCellY(),m_pTargetLocked->GetCellX(),m_pTargetLocked->GetCellY());
//		if ( dis > m_pSkillDataLocked->distance )
//		{
//			return false;
//		}
//		else
//		{
//			Stop();
//			return true;
//		}
//	}
//
//	return false;
//}
//
//void CHero::AttackCheck(SkillCfg* pSkillData,RoleFighter* pTarget)
//{
//	if ( !pSkillData )
//	{
//		return ;
//	}
//
//	// 判断攻击距离
//	switch( pSkillData->targettype)
//	{
//	case SkillTarget_None:	
//		{
//			MagicAttack(pSkillData,GetId());
//		}
//		break;
//	case SkillTarget_Target:
//		{
//			if ( !pTarget )
//			{
//				return ;
//			}
//			int dis = Distance(GetCellX(),GetCellY(),pTarget->GetCellX(),pTarget->GetCellY());
//			if ( dis > pSkillData->distance )
//			{
//				TraceTarget(pTarget,true);
//				LockTarget(pSkillData,pTarget);
//			}
//			else
//			{
//				TraceNull();
//				ReleaseTarget();
//				MagicAttack(pSkillData,GetTargetID(pTarget));
//			}
//			break;
//		}
//	case SkillTarget_Point:
//		{
//			if ( !pTarget )
//			{
//				return ;
//			}
//			int dis = Distance(GetCellX(),GetCellY(),pTarget->GetCellX(),pTarget->GetCellY());
//			if ( dis > pSkillData->distance )
//			{
//				TraceTarget(pTarget,true);
//				LockTarget(pSkillData,pTarget);
//			}
//			else
//			{
//				TraceNull();
//				ReleaseTarget();
//				MagicAttack(pSkillData,GetTargetID(pTarget->GetCellX(),pTarget->GetCellY()));
//			}
//			break;
//		}
//	case SkillTarget_Self: 
//		{
//			MagicAttack(pSkillData,GetId());
//		}
//		break;
//	default: break;
//	}
//}
//
//void CHero::Attack(int skillId, RoleFighter* pTarget)
//{
//	if ((GetPropertyInt(RoleProperty_Camp) == 0 || pTarget->GetPropertyInt(RoleProperty_Camp) != GetPropertyInt(RoleProperty_Camp)))
//	{
//		CSkill*	pSkill = GetSkillManager().Get(skillId);
//		AttackCheck(pSkill->GetData(),pTarget);
//	}
//}

void CHero::Evade(int cx,int cy)
{
	// 检查最大最小距离
	if( GetDistanceTo(cx,cy) < 5 )
	{
		return ;
	}

	// 检查当前位置到目标位置中间是否存在阻挡点
	APoint targetPos = gMap->checkTargetPosWithDistance(APoint(GetCellX(),GetCellY()),APoint(cx,cy),10);

	RoleFighter::Evade(targetPos.x,targetPos.y);

	pk::C2GS_PlayerEvade cmd;
	cmd.curMapDataId = gMap->getMapDataID();
	cmd.desPosX = targetPos.x;
	cmd.desPosY = targetPos.y;
	cmd.Send(gNetSocket);
}

void CHero::Forward(int cx,int cy)
{
	// 逆向取方向
	__Dir dir = DirectionBy(cx,cy,GetCellX(),GetCellY());

	APoint targetPos;

	targetPos.x = cx + _DELTA_CX[dir];
	targetPos.y = cy + _DELTA_CY[dir];

	// 检查当前位置到目标位置中间是否存在阻挡点
	targetPos = gMap->checkTargetPosWithDistance(APoint(GetCellX(),GetCellY()),targetPos,15);

	RoleFighter::Forward(targetPos.x,targetPos.y);
}

void CHero::Attack(int skillid)
{
	if ( IsMoving() )
	{
		RoleCommand cmd;
		cmd.type = RoleCommand_Attack;
		cmd.param.skill.skillid = skillid;
		pushCommand(cmd);
		Stop();
		return ;
	}

	if ( IsForbiddenAttack() )
	{
		return ;
	}

	CSkill* pSkill = GetSkillManager().Get(skillid);
	if ( !pSkill )
	{
		gMessageCenter->SystemMessage(93);
		return ;
	}

	if ( pSkill->GetCDTime() > 0 )
	{
		gMessageCenter->SystemMessage(39);
		return ;
	}

	SkillCfg* pData = pSkill->GetTickSkill();

	switch( pData->targettype)
	{
	case SkillTarget_None:
		{
			UseSkill(pData,this);
		}
		break;
	case SkillTarget_Target: 
		{
			SelectTargetNearBy();
			RoleFighter* pTarget = dynamic_cast<RoleFighter*>(GetSelectTarget());
			// 未找到目标，返回
			if ( !pTarget )
			{
				return ;
			}
			// 找到目标判断目标的距离是否在攻击距离之内，追击目标
			else
			{
				if ( GetDistanceTo(pTarget) > pData->distance )
				{
					RoleCommand cmd;
					cmd.type = RoleCommand_Skill;
					cmd.param.skill.skillid = pData->id;
					cmd.param.skill.targetid = pTarget->GetId();
					Pursue(pTarget->GetId(),pData->distance,cmd);
				}
				else
				{
					UseSkill(pData,pTarget);
				}
			}
		}
		break;
	case SkillTarget_Point:
		{
			SelectTargetNearBy();

			RoleFighter* pTarget = dynamic_cast<RoleFighter*>(GetSelectTarget());
			// 未找到目标，获取面前指定点为目标
			if ( !pTarget )
			{
				int cx = 0;
				int cy = 0;
				GetCellByDir(pData->distance,cx,cy);
				UseSkill(pData,cx,cy,0,0);
				return ;
			}
			// 找到目标判断目标的距离是否在攻击距离之内，追击目标
			else
			{
				if ( GetDistanceTo(pTarget) > pData->distance )
				{
					RoleCommand cmd;
					cmd.type = RoleCommand_Skill;
					cmd.param.skill.skillid = pData->id;
					cmd.param.skill.targetid = ConvertToTargetID(pTarget->GetCellX(),pTarget->GetCellY());
					Pursue(pTarget->GetId(),pData->distance,cmd);
				}
				else
				{
					Point offset = pTarget->getHungingPointOffset(2);
					UseSkill(pData,pTarget->GetCellX(),pTarget->GetCellY(),offset.x,offset.y);
				}
			}
		}
		break;
	case SkillTarget_Self: 
		{
			UseSkill(pData,this);
		}
		break;
	default: break;
	}
}

void CHero::UseSkill(SkillCfg* pSkill,RoleFighter* pTarget)
{
	if ( !pSkill || !pTarget )
	{
		return ;
	}

	if ( IsDead() )
	{
		gMessageCenter->SystemMessage(96);
		return ;
	}

	if ( GetCurrStateID() == RoleState_Fight )
	{
		return ;
	}

	// 检查通过，可以使用技能

	
	//
	RoleFighter::MagicAttack(pSkill,pTarget->GetId(),0,0);

	// 通知服务器使用技能
	pk::C2GS_UseSkill cmd;
	cmd.selfPosX = GetCellX();
	cmd.selfPosY = GetCellY();
	cmd.offsetX = 0;
	cmd.offsetY = 0;
	cmd.skillId = pSkill->id;
	cmd.targetId = pTarget->GetId();
	cmd.Send(gNetSocket);

	GetSkillManager().StartCd(pSkill->id);

	MainUI::GetActiveMainUI()->updateSkillCd();
}

void CHero::UseSkill(SkillCfg* pSkill,int cx,int cy,int offsetX,int offsetY)
{
	if ( !pSkill )
	{
		return ;
	}

	if ( IsDead() )
	{
		gMessageCenter->SystemMessage(96);
		return ;
	}

	if ( GetCurrStateID() == RoleState_Fight )
	{
		return ;
	}

	// 检查通过，可以使用技能

	// just for test
	/*
	static struct timeval tv={0,0};
	if(tv.tv_sec == 0 && tv.tv_usec == 0)
	{
		gettimeofday(&tv, NULL);
	}
	else
	{
		struct timeval tv_now={0,0};
		gettimeofday(&tv_now, NULL);

		int delta = (tv_now.tv_sec - tv.tv_sec) * 1000 + (tv_now.tv_usec - tv.tv_usec) / 1000;
		tv = tv_now;
		assert(delta >= 600);
	}*/

	__int64 targetId = ConvertToTargetID(cx,cy);
	// 执行
	RoleFighter::MagicAttack(pSkill,targetId,offsetX,offsetY);

	// 通知服务器使用技能
	pk::C2GS_UseSkill cmd;
	cmd.selfPosX = GetCellX();
	cmd.selfPosY = GetCellY();
	cmd.offsetX = offsetX;
	cmd.offsetY = offsetY;
	cmd.skillId = pSkill->id;
	cmd.targetId = targetId;
	cmd.Send(gNetSocket);

	GetSkillManager().StartCd(pSkill->id);

	if ( MainUI::GetActiveMainUI() )
	{
		MainUI::GetActiveMainUI()->updateSkillCd();
	}
}

void CHero::Dead(RoleFighter* pKiller)
{
	RoleFighter::Dead(pKiller);
	gMap->setGrey(true);
	CReviveUI* pUI = dynamic_cast<CReviveUI*>(gGameUILayer->getActiveUI(IDU_ReviveUI));
	if (pUI)
	{
		pUI->deadTimeOut();
	}
}

void CHero::DeadVirtual(RoleFighter* pKiller)
{
	gCocosAudio->PlayEffect(8);
	RoleFighter::DeadVirtual(pKiller);
	gGameUILayer->closeOtherUIs();
	gGameUILayer->open(IDU_ReviveUI);
}

void CHero::Relive(RoleFighter* pFighter /* = nullptr */)
{
	RoleFighter::Relive(pFighter);
	gMap->setGrey(false);
	ShowEffect(151613,"Animation1");
}

void CHero::ShowDamageEffect(Point pos,int damage)
{
	ImageView* pHeadIcon = NULL;
	if ( MainUI::GetActiveMainUI() )
	{
		pHeadIcon = MainUI::GetActiveMainUI()->getHeadIcon();
	}

	if ( !pHeadIcon )
	{
		return ;
	}

	Layer* pLayer = Layer::create();
	if ( !pLayer )
	{
		return ;
	}

	__String str;
	str.initWithFormat("-%d",damage);

	LabelTTF* pFont = LabelTTF::create(str.getCString(),Default_Font_File, 20);
	if ( !pFont )
	{
		return ;
	}

	Point damagePos = Point(pHeadIcon->getSize().width/2,pHeadIcon->getSize().height/3);

	pFont->setPosition(damagePos);
	pFont->setColor(Color3B::WHITE);
	pFont->runAction(FadeOut::create(0.5f));
	pLayer->addChild(pFont);
	pLayer->runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create( CC_CALLBACK_0(Role::ShowEffectCallBack,this,pLayer)),NULL));

	pHeadIcon->addChild(pLayer,999);

	PushShowEffectLayer(pLayer);
}

void CHero::ShowCritEffect(Point pos,int damage)
{
	ImageView* pHeadIcon = NULL;
	if ( MainUI::GetActiveMainUI() )
	{
		pHeadIcon = MainUI::GetActiveMainUI()->getHeadIcon();
	}

	if ( !pHeadIcon )
	{
		return ;
	}

	Layer* pLayer = Layer::create();
	if ( !pLayer )
	{
		return ;
	}

	__String str;
	str.initWithFormat("-%d",damage);

	LabelTTF* pFont = LabelTTF::create(str.getCString(),Default_Font_File, 20);
	if ( !pFont )
	{
		return ;
	}

	Point damagePos = Point(pHeadIcon->getSize().width/2,pHeadIcon->getSize().height/3);

	pFont->setPosition(damagePos);
	pFont->setColor(Color3B::WHITE);
	pFont->runAction(FadeOut::create(0.5f));
	pLayer->addChild(pFont);
	pLayer->runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create( CC_CALLBACK_0(Role::ShowEffectCallBack,this,pLayer)),NULL));

	pHeadIcon->addChild(pLayer,999);

	PushShowEffectLayer(pLayer);
}

void CHero::ShowMissEffect()
{
	Layer* pLayer = Layer::create();
	if ( !pLayer )
	{
		return ;
	}

	Sprite* pSprite = Sprite::create("assets/common/img_duoshanzi2.png");
	if ( !pSprite )
	{
		return ;
	}

	Point damagePos = getHungingPoint(2)+Point(rand()%60-rand()%60,rand()%50);
	Point offsetPos = Point(0,60);

	pSprite->setPosition(damagePos);
	//pSprite->setScale(0.9f);
	pLayer->addChild(pSprite);

	pSprite->runAction(Sequence::create(
		DelayTime::create(0.25f),
		MoveBy::create(1.0f,offsetPos),NULL));
	pSprite->runAction(Sequence::create(
		DelayTime::create(0.25f),
		FadeOut::create(1.0f),NULL));

	pLayer->runAction(Sequence::create(DelayTime::create(1.5f),CallFunc::create( CC_CALLBACK_0(Role::ShowEffectCallBack,this,pLayer)),NULL));

	gRoleTitleLayer->addChild(pLayer,999);

	PushShowEffectLayer(pLayer);
}

void CHero::ShowRecoverHPByItem(int value)
{
	RoleFighter::ShowRecoverHPByItem(value);
	ImageView* pHeadIcon = NULL;
	if ( MainUI::GetActiveMainUI() )
	{
		pHeadIcon = MainUI::GetActiveMainUI()->getHeadIcon();
	}

	if ( !pHeadIcon )
	{
		return ;
	}

	Layer* pLayer = Layer::create();
	if ( !pLayer )
	{
		return ;
	}

	__String str;
	str.initWithFormat("+%d",value);

	LabelTTF* pFont = LabelTTF::create(str.getCString(),Default_Font_File, 20);
	if ( !pFont )
	{
		return ;
	}

	Point damagePos = Point(pHeadIcon->getSize().width/2,pHeadIcon->getSize().height/3);

	pFont->setPosition(damagePos);
	pFont->setColor(Color3B(0,163,0));
	pFont->runAction(FadeOut::create(0.5f));
	pLayer->addChild(pFont);
	pLayer->runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create( CC_CALLBACK_0(Role::ShowEffectCallBack,this,pLayer)),NULL));

	pHeadIcon->addChild(pLayer,999);

	PushShowEffectLayer(pLayer);
}

void CHero::ShowRecoverMPByItem(int value)
{
	ImageView* pHeadIcon = NULL;
	if ( MainUI::GetActiveMainUI() )
	{
		pHeadIcon = MainUI::GetActiveMainUI()->getHeadIcon();
	}

	if ( !pHeadIcon )
	{
		return ;
	}

	Layer* pLayer = Layer::create();
	if ( !pLayer )
	{
		return ;
	}

	__String str;
	str.initWithFormat("+%d",value);

	LabelTTF* pFont = LabelTTF::create(str.getCString(),Default_Font_File, 20);
	if ( !pFont )
	{
		return ;
	}

	Point damagePos = Point(pHeadIcon->getSize().width/2,pHeadIcon->getSize().height/3);

	pFont->setPosition(damagePos);
	pFont->setColor(Color3B(33,33,188));
	pFont->runAction(FadeOut::create(0.5f));
	pLayer->addChild(pFont);
	pLayer->runAction(Sequence::create(DelayTime::create(0.5f),CallFunc::create( CC_CALLBACK_0(Role::ShowEffectCallBack,this,pLayer)),NULL));

	pHeadIcon->addChild(pLayer,999);

	PushShowEffectLayer(pLayer);
}

void CHero::OnGuideStep(GuideCfg* pData)
{
	if ( !pData )
	{
		return ;
	}
	
	SetPlayerVariable(PlayerVariant_Index_NewHandGuild_ProgressIndex_P,pData->id);
	// 通知服务器改变进度
	pk::C2GS_SaveNewHandGuildProgress cmd;
	cmd.index = pData->id;
	cmd.Send(gNetSocket);
}

void CHero::OnGuideInitialize()
{
	if ( m_pGuide )
	{
		int step = GetPlayerVariable(PlayerVariant_Index_NewHandGuild_ProgressIndex_P);
		SetPlayerVariable(PlayerVariant_Index_NewHandGuild_ProgressIndex_P,step);
		// 通知服务器改变进度
		pk::C2GS_SaveNewHandGuildProgress cmd;
		cmd.index = step;
		cmd.Send(gNetSocket);
	}
}

void CHero::AddIndicatorLayer()
{
	if (m_pIndicatorLayer)
	{
		return;
	}

	m_pIndicatorLayer = CIndicatorLayer::createWithRole(this);
	if (m_pIndicatorLayer)
	{
		gRoleTitleLayer->addChild(m_pIndicatorLayer,998);
	}
}

void CHero::ShowCopyEnterEffect()
{
	if(!gMap->isFightMap() || gMap->getMapDataID() == 101)
		return;

	Vector<FiniteTimeAction*> arrayOfActions;
	FiniteTimeAction* action1 = CallFunc::create(this,SEL_CallFunc(&CHero::CopyEnterActionStart));
	FiniteTimeAction* action2 = DelayTime::create(2.0f);
	FiniteTimeAction* action3 = CallFunc::create(this,SEL_CallFunc(&CHero::CopyEnterActionProcess1));
	FiniteTimeAction* action4 = DelayTime::create(2.0f);
	FiniteTimeAction* action5 = CallFunc::create(this,SEL_CallFunc(&CHero::CopyEnterActionEnd));
	arrayOfActions.pushBack(action1);
	arrayOfActions.pushBack(action2);
	arrayOfActions.pushBack(action3);
	arrayOfActions.pushBack(action4);
	arrayOfActions.pushBack(action5);

	runAction(Sequence::create(arrayOfActions));
}

void CHero::LeaveCopyWithEffect()
{
	if(!gMap->isFightMap() || gMap->getMapDataID() == 101)
	{
		LeaveCopy();
		return;
	}
	Vector<FiniteTimeAction*> arrayOfActions;
	FiniteTimeAction* action1 = CallFunc::create(this,SEL_CallFunc(&CHero::CopyLeaveActionStart));
	FiniteTimeAction* action2 = DelayTime::create(2.0f);
	FiniteTimeAction* action3 = CallFunc::create(this,SEL_CallFunc(&CHero::CopyLeaveActionProcess1));
	FiniteTimeAction* action4 = DelayTime::create(2.0f);
	std::function<void()> fun1 = [this]()
	{
		this->setVisible(false);
	};
	FiniteTimeAction* action5 = CallFunc::create(fun1);
	FiniteTimeAction* action6 = CallFunc::create(this,SEL_CallFunc(&CHero::CopyLeaveActionEnd));
	FiniteTimeAction* action7 = CallFunc::create(this,SEL_CallFunc(&CHero::LeaveCopy));
	arrayOfActions.pushBack(action1);
	arrayOfActions.pushBack(action2);
	arrayOfActions.pushBack(action3);
	arrayOfActions.pushBack(action4);
	arrayOfActions.pushBack(action5);
	arrayOfActions.pushBack(action6);
	arrayOfActions.pushBack(action7);

	runAction(Sequence::create(arrayOfActions));
}

void CHero::LeaveCopy()
{
	pk::C2GS_PlayerLeaveCopyMap cmd;
	cmd.Send(gNetSocket);
	setVisible(true);
	SetCanUseSkill(true);
}
void CHero::CopyEnterActionStart()
{
	gJoyStick->setTouchEnabled(false);
	setVisible(false);
	SetCanUseSkill(false);
	gMap->setTouchEnabled(false);
	Effect* pEffect = Effect::createWithDataID(704,true);
	if ( !pEffect )
	{
		return ;
	}
	pEffect->setName("fubenchuansong1_shang");
	//pEffect->setDuration(2.0f);
	pEffect->setPosition(getPosition());
	pEffect->setScale(0.7f);
	pEffect->setTag(704);
	gMap->addChild(pEffect);
}
void CHero::CopyEnterActionProcess1()
{
	setVisible(true);
	Effect* pEffect = Effect::createWithDataID(705,true);
	if ( !pEffect )
	{
		return ;
	}
	pEffect->setName("fubenchuansong2_shang");
	//pEffect->setDuration(2.0f);
	pEffect->setPosition(getPosition());
	pEffect->setScale(0.7f);
	pEffect->setTag(705);
	gMap->addChild(pEffect);
}
void CHero::CopyEnterActionEnd()
{
	gMap->setTouchEnabled(true);
	gMap->removeChildByTag(704);
	gMap->removeChildByTag(705);
	gJoyStick->setTouchEnabled(true);
	SetCanUseSkill(true);
}

void CHero::CopyLeaveActionStart()
{
	SetCanUseSkill(false);
	gJoyStick->setTouchEnabled(false);
	gMap->setTouchEnabled(false);
	Effect* pEffect = Effect::createWithDataID(704,true);
	if ( !pEffect )
	{
		return ;
	}
	pEffect->setName("fubenchuansong1_shang");
	//pEffect->setDuration(2.0f);
	pEffect->setPosition(getPosition());
	pEffect->setScale(0.7f);
	pEffect->setTag(704);
	gMap->addChild(pEffect);
}
void CHero::CopyLeaveActionProcess1()
{
	Effect* pEffect = Effect::createWithDataID(705,true);
	if ( !pEffect )
	{
		return ;
	}
	pEffect->setName("fubenchuansong2_shang");
	//pEffect->setDuration(2.0f);
	pEffect->setPosition(getPosition());
	pEffect->setScale(0.7f);
	pEffect->setTag(705);
	gMap->addChild(pEffect);
}

void CHero::CopyLeaveActionEnd()
{
	SetCanUseSkill(true);
	gMap->setTouchEnabled(true);
	gMap->removeChildByTag(704);
	gMap->removeChildByTag(705);
	setVisible(true);
	gJoyStick->setTouchEnabled(true);
}
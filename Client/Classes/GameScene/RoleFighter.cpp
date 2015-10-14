#include "RoleFighter.h"
#include "GameMap.h"
#include "Hero.h"
#include "Net/NetDispatcher.h"
#include "GameDataManager.h"
#include "Net/pk_role.h"
#include "GameUILayer.h"
#include "MessageCenter.h"
#include "RoleTitleLayer.h"
#include "RoleTitle.h"
#include "RoleState_Fight.h"
#include "RoleState_Injured.h"
#include "RoleState_Dead.h"
#include "UI/ReviveUI.h"
#include "UI/MainUI.h"
RoleFighter::RoleFighter() : m_pRoleTitle(NULL)
{
	InsertState(new FightState);
	InsertState(new InjuredState);
	InsertState(new DeadState);
}

RoleFighter::~RoleFighter()
{
	if ( m_pRoleTitle )
	{
		m_pRoleTitle->removeFromParentAndCleanup(true);
		m_pRoleTitle = NULL;
	}

	//CC_SAFE_RELEASE(m_pRoleTitle);
	CC_SAFE_DELETE(m_pData);
}

void RoleFighter::update(float dt)
{
	RefreshRoleTitle();

	Role::update(dt);
}

bool RoleFighter::initRole()
{
	m_pRoleTitle = RoleTitle::createWithRole(this);
	if ( m_pRoleTitle )
	{
		gRoleTitleLayer->addChild(m_pRoleTitle);
	}

	enableLightShadow(true);

	return true;
}

bool RoleFighter::isSelect(float x,float y)
{
	Point pos(x,y);
	pos = pos-getPosition();
	
	//return isTouched(pos) && !IsDead();
	return true;
}

void RoleFighter::onSelect(bool param)
{
	if ( param )
	{
		this->attach(151610,"Animation1")->setLocalZOrder(-10);
	}
	else
	{
		this->detach(151610,"Animation1");
	}
	
}

void RoleFighter::setPosition(float x,float y)
{	
	setPosition(Point(x,y));
}

void RoleFighter::setPosition(const Point &position)
{
	MapObject::setPosition(position);

	if ( m_pRoleTitle )
	{
		Point pos = position;
		pos.y += GetHeight();
		m_pRoleTitle->setPosition(pos);
	}
}

bool RoleFighter::isDynamicBlock(int cx,int cy)
{
	// 动态阻挡判断
	MapObjectList objs;
	if( GetMap()->getObjectManager()->getObjects(cx,cy,objs) > 0 )
	{
		for ( MapObjectList::iterator itr = objs.begin(); itr != objs.end(); ++itr )
		{
			RoleFighter* pFighter = dynamic_cast<RoleFighter*>(*itr);
			if ( pFighter && IsEnemyTo(pFighter) && !pFighter->IsDead() )
			{
				return true;
			}
		}
	}

	return false;
}

void RoleFighter::EnterMap(TileMap* pMap,int cx,int cy)
{
	SetBoundingInfo(0,0,120);
	Role::EnterMap(pMap,cx,cy);
	RefreshRoleTitle();
	EnterState(RoleState_Idle);
}

void RoleFighter::LeaveMap()
{
	LeaveState();

	if ( m_pRoleTitle )
	{
		m_pRoleTitle->removeFromParentAndCleanup(true);
		m_pRoleTitle = NULL;
	}

	ClearShowEffectLayer();

	MapObject::LeaveMap();
}

void RoleFighter::onEnterSight()
{
	MapObject::onEnterSight();
}

void RoleFighter::onLeaveSight()
{
	if ( this == gHero->GetSelectTarget() )
	{
		gHero->SelectTargetCancel();
	}

	MapObject::onLeaveSight();
}

void RoleFighter::RefreshEquip()
{
	int armorID = GetPropertyInt(RoleProperty_Cloth);
	int weaponID = GetPropertyInt(RoleProperty_Weapon);
	int wingID = GetPropertyInt(RoleProperty_Wing);

	unequipAll();
	equipArmor(armorID);
	equipWeapon(weaponID);
	equipWing(wingID);
}

void RoleFighter::GetCellByDir(int distance,int& cx,int& cy)
{
	cx = GetCellX()+_DELTA_CX[getDir()]*distance;
	cy = GetCellY()+_DELTA_CY[getDir()]*distance;
}

bool RoleFighter::IsAttacking()
{
	return GetCurrStateID() == RoleState_Fight;
}

bool RoleFighter::IsInjured()
{
	return GetCurrStateID() == RoleState_Injured;
}

bool RoleFighter::IsDead()
{
	return GetCurrStateID() == RoleState_Dead;
}

bool RoleFighter::IsDeadVirtual()
{
	return GetCurrStateID() == RoleState_Dead && HasStateFlag(RoleStateFlag_DeadVirtual);
}

void RoleFighter::FaceToTarget(RoleFighter* pTarget)
{
	FaceToTarget(pTarget->GetCellX(),pTarget->GetCellY());
}

void RoleFighter::FaceToTarget(int cx,int cy)
{
	if ( cx == GetCellX() && cy == GetCellY() )
	{
		return ;
	}
	__Dir dir = GetMap()->getTerrain()->getDirBetween2Cells(GetCellX(),GetCellY(),cx,cy);
	changeDir(dir);
}

void RoleFighter::FaceToTarget(const Point& pos)
{
	if ( getPosition() == pos )
	{
		return ;
	}
	__Dir dir = GetMap()->getTerrain()->getDirBetween2Points(getPosition(),pos);
	changeDir(dir);
}

void RoleFighter::MagicAttack(SkillCfg* pSkill,__int64 targetid,int offsetX,int offsetY)
{
	m_pActiveSkill = pSkill;
	m_nTargetID = targetid;
	m_nTargetOffsetX = offsetX;
	m_nTargetOffsetY = offsetY;

	EnterState(RoleState_Fight);		// 进入战斗状态
}

bool RoleFighter::IsForbiddenMove()
{
	if ( GetCurrStateID() == RoleState_Fight || 
		 GetCurrStateID() == RoleState_Injured )
	{
		return true;
	}

	return false;
}

bool RoleFighter::IsForbiddenAttack()
{
	if ( GetCurrStateID() == RoleState_Injured )
	{
		return true;
	}

	return false;
}

bool RoleFighter::IsForbiddenSkill()
{
	return false;
}

bool RoleFighter::IsEnemyTo(RoleFighter* pFighter)
{
	if( GetPropertyInt(RoleProperty_Camp) == pFighter->GetPropertyInt(RoleProperty_Camp) )
	{
		return false;
	}

	return true;
}

void RoleFighter::Forward(int cx,int cy)
{
	enableGhostShadow(true);
	m_MoveMonitor.Flash(APoint(GetCellX(),GetCellY()),APoint(cx,cy),GetDistanceTo(cx,cy)*30,0);

	playAction(RoleAction_Skill1,0,0);
}

void RoleFighter::Evade(int cx,int cy)
{
	enableGhostShadow(true);

	m_MoveMonitor.Flash(APoint(GetCellX(),GetCellY()),APoint(cx,cy),GetDistanceTo(cx,cy)*30,0);

	EnterState(RoleState_Move);
}

void RoleFighter::Injured()
{
	if ( IsMoving() )
	{
		Stop();

		GetMoveMonitor().Terminate();

		SetCell(GetMoveMonitor().GetCurrPoint().x,GetMoveMonitor().GetCurrPoint().y);
	}
	
	EnterState(RoleState_Injured);
}

void RoleFighter::Dead(RoleFighter* pKiller)
{
	// 添加死亡标志位
	ClrStateFlag(RoleStateFlag_DeadVirtual);
	AddStateFlag(RoleStateFlag_Dead);
	if ( GetCurrStateID() != RoleState_Dead )
	{
		EnterState(RoleState_Dead);
	}

	if ( this == gHero->GetSelectTarget() )
	{
		gHero->SelectTargetCancel();
	}
}

void RoleFighter::DeadVirtual(RoleFighter* pKiller)
{
	// 添加死亡标志位
	AddStateFlag(RoleStateFlag_DeadVirtual);
	if ( GetCurrStateID() != RoleState_Dead )
	{
		EnterState(RoleState_Dead);
	}

	if ( this == gHero->GetSelectTarget() )
	{
		gHero->SelectTargetCancel();
	}

	LOGE("RoleFighter::Dead called");

	this->SetDeadVirtualDeadRestTime((float)20.0f);
	this->SetDeadVirtualHelpNum((int)0);
	this->SetDeadVirtualRestPoint((int)10000);
}

void RoleFighter::Relive(RoleFighter* pFighter /* = nullptr */)
{
	// 清除死亡标志位
	ClrStateFlag(RoleStateFlag_Dead);
	ClrStateFlag(RoleStateFlag_DeadVirtual);
	ClearShowEffectLayer();
	EnterState(RoleState_Idle);
	MainUI::ShowMainUI(gMap->getFuncType());
}

void RoleFighter::AddBuff(RoleBuff* pBuff)
{ 
	if ( !pBuff )
	{
		return ;
	}
	// 增加buff特效
	EffectList effects = pBuff->GetEffectList();
	for (size_t i = 0; i < effects.size(); i++)
	{
		attach(effects[i]);
	}
	
	GetBuffManager().Insert(pBuff);
}

RoleBuff* RoleFighter::AddBuff(__int64 id,int buffid,int duration)
{ 
	RoleBuff* pBuff = new RoleBuff(id,buffid,duration);
	if ( pBuff )
	{
		AddBuff(pBuff);
		return pBuff;
	}
	else
	{
		LOGE("RoleFighter::AddBuff new RoleBuff(%lld,%d,%d) failed.",id,buffid,duration);
	}

	return NULL;
}

void RoleFighter::RemoveBuff(int64 buffid)
{ 
	// 移除buff特效
	RoleBuff* pBuff = GetBuff(buffid);
	if ( pBuff )
	{
		EffectList effects = pBuff->GetEffectList();
		for (size_t i = 0; i < effects.size(); i++)
		{
			detach(effects[i]);
		}
		
		GetBuffManager().Remove(buffid);
	}
}

void RoleFighter::ShowDamageEffect(Point pos,int damage)
{
	if ( !m_pRoleTitle )
	{
		return ;
	}

	Layer* pLayer = Layer::create();
	if ( !pLayer )
	{
		return ;
	}

	__String str;
	str.initWithFormat("%d",damage);

	Label* pFont = Label::createWithBMFont("assets/common/font/damage.fnt",str.getCString());
	if ( !pFont )
	{
		return ;
	}

	Point damagePos = getHungingPoint(2)+Point(rand()%60-rand()%60,rand()%50);
	Point offsetPos = Point(0,60);

	pFont->setPosition(damagePos);
	pFont->setScale(0.9f);
	pLayer->addChild(pFont);

	pFont->runAction(Sequence::create(
		DelayTime::create(0.25f),
		MoveBy::create(1.0f,offsetPos),NULL));
	pFont->runAction(Sequence::create(
		DelayTime::create(0.25f),
		FadeOut::create(1.0f),NULL));

	pLayer->runAction(Sequence::create(DelayTime::create(1.5f),CallFunc::create( CC_CALLBACK_0(Role::ShowEffectCallBack,this,pLayer)),NULL));

	gRoleTitleLayer->addChild(pLayer,999);

	PushShowEffectLayer(pLayer);
}

void RoleFighter::ShowCritEffect(Point pos,int damage)
{
	Layer* pLayer = Layer::create();
	if ( !pLayer )
	{
		return ;
	}

	__String str;
	str.initWithFormat("%d",damage);

	Label* pFont = Label::createWithBMFont("assets/common/font/damage_crit.fnt",str.getCString());
	if ( !pFont )
	{
		return ;
	}

	Label* pFontLight = Label::createWithTTF(str.getCString(), "assets/fonts/Abberancy.ttf", 20);
	if ( !pFontLight )
	{
		return ;
	}
	pFontLight->setColor(Color3B::WHITE);
	pFontLight->enableOutline(Color4B::WHITE,5);

	Point damagePos = getHungingPoint(2);
	Point targetPos = Point(rand()%60-rand()%60,rand()%30+50);
	Point offsetPos = Point(0,60);

	pFont->setPosition(damagePos);
	pFont->setScale(0.5f);
	pFont->setOpacity(0);
	pFontLight->setPosition(damagePos);
	pFontLight->setScale(0.2f);
	pLayer->addChild(pFont);
	pLayer->addChild(pFontLight);

	pFont->runAction(Sequence::create(
		ScaleTo::create(0.15f,2.2f,2.2f,2.2f),
		ScaleTo::create(0.15f,1.2f,1.2f,1.2f),
		DelayTime::create(0.15f),
		MoveBy::create(0.5f,offsetPos),NULL));
	pFont->runAction(Sequence::create(
		MoveBy::create(0.15f,targetPos),
		FadeIn::create(0.15f),
		DelayTime::create(0.15f),
		FadeOut::create(0.5f),NULL));

	pFontLight->runAction(Sequence::create(
		ScaleTo::create(0.15f,2.5f,2.4f,2.4f),
		ScaleTo::create(0.15f,1.4f,1.4f,1.4f),NULL));
	pFontLight->runAction(Sequence::create(
		MoveBy::create(0.15f,targetPos),
		FadeOut::create(0.15f),NULL));

	pLayer->runAction(Sequence::create(DelayTime::create(1.8f),CallFunc::create( CC_CALLBACK_0(Role::ShowEffectCallBack,this,pLayer)),NULL));

	gRoleTitleLayer->addChild(pLayer,999);

	PushShowEffectLayer(pLayer);
}

void RoleFighter::ShowMissEffect()
{
	Layer* pLayer = Layer::create();
	if ( !pLayer )
	{
		return ;
	}

	Sprite* pSprite = Sprite::create("assets/common/img_duoshanzi1.png");
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

void RoleFighter::ShowRecoverHP(int value)
{
	if ( !m_pRoleTitle )
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

	Label* pFont = Label::createWithBMFont("assets/common/font/recoverHP.fnt",str.getCString());
	if ( !pFont )
	{
		return ;
	}

	Point damagePos = getHungingPoint(0);
	Point offsetPos = Point(0,60);

	pFont->setPosition(damagePos);
	pLayer->addChild(pFont);

	pFont->runAction(Sequence::create(
		DelayTime::create(0.25f),
		MoveBy::create(1.0f,offsetPos),NULL));
	pFont->runAction(Sequence::create(
		DelayTime::create(0.25f),
		FadeOut::create(1.0f),NULL));

	pLayer->runAction(Sequence::create(DelayTime::create(1.5f),CallFunc::create( CC_CALLBACK_0(Role::ShowEffectCallBack,this,pLayer)),NULL));

	gRoleTitleLayer->addChild(pLayer,999);

	PushShowEffectLayer(pLayer);
}

void RoleFighter::ShowRecoverMP(int value)
{
	if ( !m_pRoleTitle )
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

	Label* pFont = Label::createWithBMFont("assets/common/font/recoverMP.fnt",str.getCString());
	if ( !pFont )
	{
		return ;
	}

	Point damagePos = getHungingPoint(0);
	Point offsetPos = Point(0,60);

	pFont->setPosition(damagePos);
	pLayer->addChild(pFont);

	pFont->runAction(Sequence::create(
		DelayTime::create(0.25f),
		MoveBy::create(1.0f,offsetPos),NULL));
	pFont->runAction(Sequence::create(
		DelayTime::create(0.25f),
		FadeOut::create(1.0f),NULL));

	pLayer->runAction(Sequence::create(DelayTime::create(1.5f),CallFunc::create( CC_CALLBACK_0(Role::ShowEffectCallBack,this,pLayer)),NULL));

	gRoleTitleLayer->addChild(pLayer,999);

	PushShowEffectLayer(pLayer);
}

void RoleFighter::ShowRecoverHPByItem(int value)
{
	ShowEffect(702,"fuhuo_zhiliao");
}

void RoleFighter::ShowRecoverMPByItem(int value)
{

}

void RoleFighter::ShowLevelUPEffect()
{
	// 升级特效
	ShowEffect(703,"shengji",0,10.0f/7.0f);
}

void RoleFighter::ShowStageEffect()
{

}

void RoleFighter::ShowHitFly(const Point& pos)
{
	Point p1 = getPosition();
	Point p2 = p1-pos;
	p2 = p2.normalize()*300;
	p2 += p1;
	this->runAction(Sequence::create(MoveTo::create(0.3f,p2),NULL));
}

void RoleFighter::ShowRoleEffect(pk::RoleEffectInfo* pInfo)
{
	if ( !pInfo )
	{
		return ;
	}

	switch( pInfo->effectType )
	{
	case RoleEffect_Miss:
		{
			ShowMissEffect();
		}
		break;	
	case RoleEffect_Injured:
		{
			Injured();
		}
		break;		
	case RoleEffect_Dead:
		{
			RoleFighter* pRole = GetMapRole(pInfo->castId);
			DeadVirtual(pRole);
		}
		break;	
	case RoleEffect_Damage:
		{
			ShowDamageEffect(Point::ZERO,pInfo->data);
		}
		break;
	case RoleEffect_Crit:
		{
			ShowCritEffect(Point::ZERO,pInfo->data);
		}
		break;
	case RoleEffect_Revive:
		{
			gCocosAudio->PlayEffect(9);

			CReviveUI* pUI = dynamic_cast<CReviveUI*>(gGameUILayer->getActiveUI(IDU_ReviveUI));
			if (pUI)
			{
				gGameUILayer->close(IDU_ReviveUI);
			}

			RoleFighter* pRole = GetMapRole(pInfo->targetId);
			pRole->Relive();

		}
		break;
	case RoleEffect_LevelUP:
		{
			ShowLevelUPEffect();
		}
		break;
	case RoleEffect_RecoverHP:
		{
			ShowRecoverHP(pInfo->data);
		}
		break;
	case RoleEffect_RecoverMP:
		{
			ShowRecoverMP(pInfo->data);
		}
		break;
	case RoleEffect_RecoverHP_Ball:
		{
			ShowRecoverHPByItem(pInfo->data);
		}
		break;
	case RoleEffect_RecoverMP_Ball:
		{
			ShowRecoverMPByItem(pInfo->data);
		}
		break;
	case RoleEffect_HitBack:
		{
			
		}
		break;
	default:
		break;
	}
}

void RoleFighter::SetProperty(RoleProperty idx,int val)
{
	switch (idx)
	{
	case RoleProperty_Career:
		SetCareer(val);
		break;
	case RoleProperty_StateFlag:
		SetStateFlag(val);
		break;
	case RoleProperty_Level:
		SetLevel(val);
		break;
	case RoleProperty_Cloth:
		SetCloth(val);
		break;
	case RoleProperty_Weapon:
		SetWeapon(val);
		break;
	case RoleProperty_Wing:
		SetWing(val);
		break;
	default:
		break;
	}
	Role::SetProperty(idx,val);
}

void RoleFighter::SetProperty(RoleProperty idx,__int64 val)
{
	switch (idx)
	{
	case RoleProperty_HP:
		SetHP(val);
		break;
	case RoleProperty_hp_max:
		SetHPMax(val);
		break;
	default:
		break;
	}
	Role::SetProperty(idx,val);
}

void RoleFighter::SetProperty(RoleProperty idx,const string& val)
{
	Role::SetProperty(idx,val);
}

void RoleFighter::SetRoleName(const string& val)
{ 
	GetData()->SetName(val); 
	if(m_pRoleTitle)
	{
		m_pRoleTitle->SetRoleName(val); 
	}
}

void RoleFighter::SetCamp(int val)
{
	GetData()->SetProperty(RoleProperty_Camp,val);

	if(m_pRoleTitle)
		m_pRoleTitle->UpdateRoleNameCampColor();
}

void RoleFighter::SetCareer(int val)
{
	GetData()->SetProperty(RoleProperty_Career,val);
}

void RoleFighter::SetHP(__int64 val)
{
	GetData()->SetProperty(RoleProperty_HP,val);

	if (m_pRoleTitle && GetHPMax() > 0 )
	{
		m_pRoleTitle->SetHPPercent(((float)GetHP()) / GetHPMax() * 100);
	}
}

void RoleFighter::SetHPMax(__int64 val)
{
	GetData()->SetProperty(RoleProperty_hp_max,val);

	if (m_pRoleTitle && GetHPMax() > 0 )
	{
		m_pRoleTitle->SetHPPercent(((float)GetHP()) / GetHPMax() * 100);
	}
}

void RoleFighter::SetMP(int val)
{
	GetData()->SetProperty(RoleProperty_MP,val);

	if (m_pRoleTitle && GetMPMax() > 0 )
	{
		m_pRoleTitle->SetHPPercent(((float)GetMP()) / GetMPMax() * 100);
	}
}

void RoleFighter::SetMPMax(int val)
{
	GetData()->SetProperty(RoleProperty_mp_max,val);

	if (m_pRoleTitle && GetMPMax() > 0 )
	{
		m_pRoleTitle->SetHPPercent(((float)GetMP()) / GetMPMax() * 100);
	}
}

void RoleFighter::SetStateFlag(int val)
{
	// 获取老的状态
	int state = GetStateFlag();

	Role::SetStateFlag(val);

	if ( HasStateFlag(RoleStateFlag_Dead) )
	{
		Dead(nullptr);
	}

	if ( HasStateFlag(RoleStateFlag_DeadVirtual) && GetCurrStateID() != RoleState_Dead )
	{
		DeadVirtual(nullptr);
	}
}

void RoleFighter::AddStateFlag(int val)
{
	Role::AddStateFlag(val);
}

void RoleFighter::ClrStateFlag(int val)
{
	Role::ClrStateFlag(val);
}

void RoleFighter::RefreshRoleTitle()
{
	if ( m_pRoleTitle )
	{
		m_pRoleTitle->setLocalZOrder(getLocalZOrder());
		m_pRoleTitle->updateRevivePanel();
	}
}

float RoleFighter::GetDeadVirtualDeadRestTime()
{
	if ( GetCurrStateID() == RoleState_Dead )
	{
		return GetStateMachineData().Dead.deadRestTime;
	}

	return 0;
}

int	RoleFighter::GetDeadVirtualRestPoint()
{
	if ( GetCurrStateID() == RoleState_Dead )
	{
		return GetStateMachineData().Dead.restPoint;
	}

	return 0;
}

int	RoleFighter::GetDeadVirtualHelpNum()
{
	if ( GetCurrStateID() == RoleState_Dead )
	{
		return GetStateMachineData().Dead.helpNum;
	}

	return 0;
}

float RoleFighter::GetDeadVirtualRestTime()
{
	if ( GetCurrStateID() == RoleState_Dead )
	{
		return (float)GetStateMachineData().Dead.restTime / 1000.0f;
	}

	return 0;
}

int RoleFighter::GetDeadVirtualPercent()
{
	if ( GetCurrStateID() == RoleState_Dead )
	{
		return GetStateMachineData().Dead.percent;
	}

	return 0;
}

void RoleFighter::SetDeadVirtualPercent()
{
	if ( GetCurrStateID() == RoleState_Dead )
	{
		GetStateMachineData().Dead.percent = (int)(GetDeadVirtualRestPoint() / GetDeadVirtualRestTime());
	}
}

void RoleFighter::SetDeadVirtualDeadRestTime(float timer)
{
	if ( GetCurrStateID() == RoleState_Dead )
	{
		GetStateMachineData().Dead.deadRestTime = timer;
	}
}

void RoleFighter::SetDeadVirtualRestPoint(int restPoint)
{
	if ( GetCurrStateID() == RoleState_Dead )
	{
		GetStateMachineData().Dead.restPoint = restPoint;
	}
}

void RoleFighter::SetDeadVirtualHelpNum(int helpnum)
{
	if ( GetCurrStateID() == RoleState_Dead )
	{
		GetStateMachineData().Dead.helpNum = helpnum;
	}
}

void RoleFighter::SetDeadVirtualRestTime(float restTime)
{
	if ( GetCurrStateID() == RoleState_Dead )
	{
		GetStateMachineData().Dead.restTime = restTime;
	}
}
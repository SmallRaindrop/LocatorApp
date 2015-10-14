#include "Role.h"
#include "SimpleAudioEngine.h"
#include "RoleEvent.h"
#include "commonRef.h"
#include "Map/TileMap.h"
#include "../StringUtil.h"
#include "cocostudio/CCSkin.h"
#include "Map/map_def.h"
#include "ArmatureManager.h"
#include "RoleEffect.h"

using namespace CocosDenshion;

Role::Role() : StateMachine(this),m_pData(NULL),
	m_nArmorID(0),m_nWeaponID(0),m_nWingID(0),
	m_pArmor(NULL),m_pWeapon(NULL),m_pWing(NULL),m_bLightShadow(false),
	m_pArmorShadow(NULL),m_pWeaponShadow(NULL),m_pWingShadow(NULL),
	m_nArmorShadowFrame(-1),m_nWeaponShadowFrame(-1),m_nWingShadowFrame(-1),
	m_sActionName(RoleAction_Stand),m_nDir(DIR_S),m_nLoop(4),m_nDurationTo(-1),m_nActionSpeed(0),
	m_nPursueTargetID(0),m_nPursueDistance(0),m_bGhostShadow(false),m_pGhostShadowLayer(NULL)
{
	InsertState(new IdleState);
	InsertState(new MoveState);
	InsertState(new ReadyState);
}

Role::~Role()
{
	unequipAll();

	enableGhostShadow(false);

	enableLightShadow(false);

	ClearShowEffectLayer();
	//gArmatureManager->getNotifyCenterRole().eraseElement(this);
}

void Role::update(float dt)
{
	Update(dt);

	PursueUpdate();

	if ( m_bLightShadow )
	{
		updateLightShadow(dt);
	}

	if ( !m_dequeCommands.empty() )
	{
		RoleCommand cmd = m_dequeCommands.front();
		m_dequeCommands.pop_front();

		processCommand(cmd);
	}
}

void Role::equipWeapon(int dataid)
{
	if ( dataid == 0 )
	{
		return ;
	}

	m_nWeaponID = dataid;

	gArmatureManager->loadArmatureFileForRole(dataid,this);

	/*__String str;
	str.initWithFormat("%d.ExportJson",dataid);

	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(str.getCString(), this, schedule_selector(Role::onWeaponLoaded));*/
}

void Role::equipArmor(int dataid)
{
	if ( dataid == 0 )
	{
		return ;
	}

	m_nArmorID = dataid;

	gArmatureManager->loadArmatureFileForRole(dataid,this);

	/*__String str;
	str.initWithFormat("assets/role/%d.ExportJson",dataid);

	TIME_COST_BEGIN;
	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(str.getCString(), this, schedule_selector(Role::onArmorLoaded));
	TIME_COST_LOG_IF("addArmatureFileInfoAsync",3);*/
}

void Role::equipWing(int dataid)
{
	if ( dataid == 0 )
	{
		return ;
	}

	m_nWingID = dataid;

	gArmatureManager->loadArmatureFileForRole(dataid,this);

	/*__String str;
	str.initWithFormat("%d.ExportJson",dataid);

	ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(str.getCString(), this, schedule_selector(Role::onWingLoaded));*/
}

void Role::onNotifyCenter(int msg)
{
	if ( msg == m_nArmorID )
	{
		__String str;
		str.initWithFormat("%d",msg);
		equipArmor(str.getCString());
	}

	if ( msg == m_nWeaponID )
	{
		__String str;
		str.initWithFormat("%d",msg);
		equipWeapon(str.getCString());
	}

	if ( msg == m_nWingID )
	{
		__String str;
		str.initWithFormat("%d",msg);
		equipWing(str.getCString());
	}

	// 收到通知，释放自己一次
	this->release();
}

void Role::equipArmor(const char* armor)
{
	unequipArmor();
	//armor = "3Animation";
	TIME_COST_BEGIN;
 	m_pArmor = gArmatureManager->getArmature(armor);
 	TIME_COST_LOG_IF("equipArmor Armature::create",3);
 	if ( m_pArmor )
 	{
 		m_pArmor->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Role::onAnimationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
 		m_pArmor->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Role::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
 		m_pArmor->setSkinEffect(SkinEffectType(GetSkinEffect()));
		this->addChild(m_pArmor);
 
 		TIME_COST_LOG_IF("equipArmor mid",3);
 		refreshAction(true);
 		TIME_COST_LOG_IF("equipArmor refreshAction",3);
 	}
}

void Role::equipWeapon(const char* weapon)
{
	unequipWeapon();

	m_pWeapon = gArmatureManager->getArmature(weapon);
	if ( m_pWeapon )
	{
		m_pWeapon->setSkinEffect(SkinEffectType(GetSkinEffect()));
		addChild(m_pWeapon);
		refreshAction(true);
	}
}

void Role::equipWing(const char* wing)
{
	unequipWing();

	m_pWing = gArmatureManager->getArmature(wing);
	if ( m_pWing )
	{
		m_pWing->setSkinEffect(SkinEffectType(GetSkinEffect()));
		this->addChild(m_pWing);
		refreshAction(true);
	}
}

void Role::unequipArmor()
{
	if ( m_pArmor )
	{
		m_pArmor->stopAllActions();
		m_pArmor->getAnimation()->stop();
		m_pArmor->removeFromParent();
		m_pArmor = NULL;
	}
}

void Role::unequipWeapon()
{
	if ( m_pWeapon )
	{
		m_pWeapon->stopAllActions();
		m_pWeapon->getAnimation()->stop();
		m_pWeapon->removeFromParent();
		m_pWeapon = NULL;
	}
}

void Role::unequipWing()
{
	if ( m_pWing )
	{
		m_pWing->stopAllActions();
		m_pWing->getAnimation()->stop();
		m_pWing->removeFromParent();
		m_pWing = NULL;
	}
}

void Role::unequipAll()
{
	unequipArmor();
	unequipWeapon();
	unequipWing();
}

void Role::ShowEffectAsync(const string& config)
{
	RoleEffectList effects;
	RoleEffect::createRoleEffectListByConfig(this,config,effects);
	for(size_t i = 0 ;i<effects.size();++i )
	{
		ShowEffectAsync(effects[i]);
	}
}

void Role::ShowEffectAsync(int effectid,const string& name,int zorder /* = 0 */)
{
	RoleEffect* pEffect = RoleEffect::createWithDataID(this,effectid,name);
	if ( !pEffect )
	{
		return ;
	}
	pEffect->setLocalZOrder(zorder);

	ShowEffectAsync(pEffect);
}

void Role::ShowEffectAsync(RoleEffect* pEffect)
{
	if ( pEffect )
	{
		Layer* pLayer = Layer::create();
		if ( !pLayer )
		{
			return ;
		}

		Point pos = getHungingPointOffset(pEffect->getHungingPoint()-1);
		pEffect->setPosition(pos);
		pLayer->addChild(pEffect);

		// 固定5秒清理一次
		pLayer->runAction(Sequence::create(DelayTime::create(5.0f),CallFunc::create( CC_CALLBACK_0(Role::ShowEffectCallBack,this,pLayer)),NULL));

		this->addChild(pLayer,pEffect->getLocalZOrder());

		PushShowEffectLayer(pLayer);
	}
}

void Role::ShowEffect(const string& config)
{
	EffectList effects;
	Effect::GetEffectListByConfig(config,effects);
	for(size_t i = 0 ;i<effects.size();++i )
	{
		ShowEffect(effects[i]);
	}
}

void Role::ShowEffect(int effectid,const string& name,int hpt /* = 0 */,float scale /* = 1.0f */,int zorder /* = 0 */)
{
	Effect* pEffect = Effect::createWithDataID(effectid,false);
	if ( !pEffect )
	{
		return ;
	}

	pEffect->setName(name);
	pEffect->setHungingPoint(hpt);
	pEffect->setScale(scale);
	pEffect->setLocalZOrder(zorder);

	ShowEffect(pEffect);
}

void Role::ShowEffect(Effect* pEffect)
{
	if ( pEffect )
	{
		Layer* pLayer = Layer::create();
		if ( !pLayer )
		{
			return ;
		}
		Point pos = getHungingPointOffset(pEffect->getHungingPoint()-1);
		pEffect->setPosition(pos);
		pLayer->addChild(pEffect);

		// 固定5秒清理一次
		pLayer->runAction(Sequence::create(DelayTime::create(5.0f),CallFunc::create( CC_CALLBACK_0(Role::ShowEffectCallBack,this,pLayer)),NULL));

		this->addChild(pLayer,pEffect->getLocalZOrder());

		PushShowEffectLayer(pLayer);
	}
}

void Role::ShowEffectCallBack(Layer* pLayer)
{
	ClearShowEffectLayer(pLayer);
}

void Role::PushShowEffectLayer(Layer* pLayer)
{
	if ( pLayer )
	{
		m_vShowEffectLayers.push_back(pLayer);
		pLayer->retain();
	}
}

void Role::ClearShowEffectLayer(Layer* pLayer)
{
	for (vector<Layer*>::iterator itr = m_vShowEffectLayers.begin();itr != m_vShowEffectLayers.end();++itr )
	{
		if ( pLayer == *itr )
		{
			m_vShowEffectLayers.erase(itr);
			pLayer->removeFromParent();
			pLayer->release();
			return;
		}
	}
}

void Role::ClearShowEffectLayer()
{
	for (vector<Layer*>::iterator itr = m_vShowEffectLayers.begin();itr != m_vShowEffectLayers.end();++itr )
	{
		Layer* pLayer = *itr;
		if ( pLayer )
		{
			pLayer->removeFromParent();
			pLayer->release();
		}
	}

	m_vShowEffectLayers.clear();
}

void Role::attach(const string& config)
{
	EffectList effects;
	Effect::GetEffectListByConfig(config,effects);
	for(size_t i = 0;i<effects.size();++i )
	{
		attach(effects[i]);
	}
	
}

Effect* Role::attach(int dataid,const string& name,int zorder /* = 0 */)
{
	Effect* pEffect = Effect::createWithDataID(dataid,true);
	if ( pEffect )
	{
		pEffect->setLocalZOrder(zorder);
		pEffect->setName(name);
		attach(pEffect);
		return pEffect;
	}

	return NULL;
}

void Role::attach(Effect* pEffect)
{
	if ( pEffect && !isAttached(pEffect->getDataID(),pEffect->getName()))
	{
		Point pos = getHungingPointOffset(pEffect->getHungingPoint()-1);
		pEffect->setPosition(pos);
		pEffect->setLoop();
		addChild(pEffect);
		pEffect->retain();
		m_vEffects.push_back(pEffect);
	}
}

bool Role::isAttached(int dataid,const string& name)
{
	if ( dataid == 0 || name.empty() )
	{
		return false;
	}
	for (EffectList::iterator itr = m_vEffects.begin();itr != m_vEffects.end();++itr)
	{
		Effect* pEffect = *itr;
		if( pEffect->getDataID() == dataid && name == pEffect->getName() )
		{
			return true;
		}
	}
	return false;
}

void Role::detach(int dataid,const string& name)
{
	if ( dataid == 0 || name.empty() )
	{
		return ;
	}
	for (EffectList::iterator itr = m_vEffects.begin();itr != m_vEffects.end();++itr)
	{
		Effect* pEffect = *itr;
		if( pEffect->getDataID() == dataid && name == pEffect->getName() )
		{
			pEffect->removeFromParent();
			CC_SAFE_RELEASE(pEffect);
			m_vEffects.erase(itr);
			return ;
		}
	}
}

void Role::detach()
{
	for (EffectList::iterator itr = m_vEffects.begin();itr != m_vEffects.end();++itr)
	{
		Effect* pEffect = *itr;
		pEffect->removeFromParent();
		CC_SAFE_RELEASE(pEffect);
	}
	m_vEffects.clear();
}

void Role::detach(Effect* pEffect)
{
	for (EffectList::iterator itr = m_vEffects.begin();itr != m_vEffects.end();++itr)
	{
		if ( pEffect == *itr )
		{
		}
		pEffect->removeFromParent();
		CC_SAFE_RELEASE(pEffect);
		m_vEffects.erase(itr);
		return;
	}
}

void Role::flip(bool val /* = true */)
{
	float scale = val ? -1.0f : 1.0f;
	if ( m_pArmor )
	{
		m_pArmor->setScaleX(scale);
	}

	if ( m_pWeapon )
	{
		m_pWeapon->setScaleX(scale);
	}

	if ( m_pWing )
	{
		m_pWing->setScaleX(scale);
	}
}

void Role::changeDir(__Dir dir)
{
	if ( dir == m_nDir )
	{
		return ;
	}

	m_nDir = dir;

	refreshAction(true);
}

void Role::SetActionSpeed(int speed)
{ 
	if ( m_nActionSpeed == speed || m_pArmor == NULL )
	{
		return ;
	}

	m_nActionSpeed = speed; 

	float scale = m_nActionSpeed > 0 ? ((float)m_pArmor->getAnimation()->getRawDuration()*1000.0f/60.0f/(float)m_nActionSpeed) : 1.0f;

	// 更新动画速度
	if ( m_pArmor )
	{
		m_pArmor->getAnimation()->setSpeedScale(scale);
	}

	if ( m_pWeapon )
	{
		m_pArmor->getAnimation()->setSpeedScale(scale);
	}

	if ( m_pWing )
	{
		m_pArmor->getAnimation()->setSpeedScale(scale);
	}
}

void Role::EnterMap(TileMap* pMap,int cx,int cy)
{
	m_MoveMonitor.Terminate();
	//getArmor()->setSkinEffect(SkinEffect_Grey);
	MapObject::EnterMap(pMap,cx,cy);
}

void Role::EnterMap(TileMap* pMap,const Point& pos)
{
	m_MoveMonitor.Terminate();
	//getArmor()->setSkinEffect(SkinEffect_Grey);
	MapObject::EnterMap(pMap,pos);
}

void Role::LeaveMap()
{
	m_MoveMonitor.Terminate();

	MapObject::LeaveMap();
}

void Role::MoveTo(int cx,int cy)
{
	if ( !GetMap() )
	{
		return ;
	}

	if ( m_MoveMonitor.IsStepOver() )
	{
		APath path;
		GetMap()->searchForPath(GetCellX(),GetCellY(),cx,cy,path);
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

void Role::MoveBy(__Dir dir)
{
	if ( !GetMap() )
	{
		return ;
	}

	static const int _MAX_STEP_ = 5;

	if ( !m_MoveMonitor.IsStepOver() && getDir() != dir )
	{
		Stop();
		return ;
	}

	if ( !m_MoveMonitor.IsStepOver() )
	{
		return ;
	}

	int cx = GetCellX();
	int cy = GetCellY();
	for ( int i = 0;i<_MAX_STEP_;++i )
	{
		int cx0 = GetCellX()+_DELTA_CX[dir]*i;
		int cy0 = GetCellY()+_DELTA_CY[dir]*i;

		if( GetMap()->getTerrain()->getCell(cx0,cy0)->isMark(cellMaskStop) )
		{
			break;
		}

		cx = cx0;
		cy = cy0;
	}

	MoveTo(cx,cy);
}

void Role::onAnimationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID)
{
	if ( MovementEventType::COMPLETE == movementType )
	{
		if ( m_sActionName == RoleAction_Death || m_sActionName == RoleAction_Injured )
		{
			getArmor()->getAnimation()->pause();

			if ( getWeapon() )
			{
				getWeapon()->getAnimation()->pause();
			}

			if ( getWing() )
			{
				getWing()->getAnimation()->pause();
			}
		}
	}

	if ( MovementEventType::LOOP_COMPLETE == movementType )
	{
		
	}
}

void Role::onFrameEvent(Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
	CCLOG("(%s) emit a frame event (%s) at frame index (%d).", bone->getName().c_str(), evt.c_str(), currentFrameIndex);

	vector<string> events;
	StringUtil::StringSplit(evt,";",events);

	for ( size_t i = 0;i<events.size(); ++i )
	{
		string event = events[i];
		if ( event == "sound" )
		{
			SimpleAudioEngine::getInstance()->playEffect("skill_ban_yue_zhan.mp3");
		}
		if ( event == "damage" )
		{
			//m_pTraceTarget->beattack("");
			//m_pTraceTarget->PushEvent(new InjuredEvent(this,50,100));
			//Rect rect = m_pTarget->getBoundingBox();

			//// This code is just telling how to get the vertex.
			//// For a more accurate collider detection, you need to implemente yourself.
			//const Map<std::string, Bone*>& map = armature2->getBoneDic();
			//for(const auto& element : map)
			//{
			//	Bone *bone = element.second;
			//	ColliderDetector *detector = bone->getColliderDetector();

			//	if (!detector)
			//		continue;

			//	const cocos2d::Vector<ColliderBody*>& bodyList = detector->getColliderBodyList();

			//	for (const auto& object : bodyList)
			//	{
			//		ColliderBody *body = static_cast<ColliderBody*>(object);
			//		const std::vector<Point> &vertexList = body->getCalculatedVertexList();

			//		float minx = 0, miny = 0, maxx = 0, maxy = 0;
			//		size_t length = vertexList.size();
			//		for (size_t i = 0; i<length; i++)
			//		{
			//			Point vertex = vertexList.at(i);
			//			if (i == 0)
			//			{
			//				minx = maxx = vertex.x;
			//				miny = maxy = vertex.y;
			//			}
			//			else
			//			{
			//				minx = vertex.x < minx ? vertex.x : minx;
			//				miny = vertex.y < miny ? vertex.y : miny;
			//				maxx = vertex.x > maxx ? vertex.x : maxx;
			//				maxy = vertex.y > maxy ? vertex.y : maxy;
			//			}
			//		}
			//		Rect temp = Rect(minx, miny, maxx - minx, maxy - miny);

			//		if (temp.intersectsRect(rect))
			//		{
			//			armature2->setVisible(false);
			//		}
			//	}
			//}
		}
	}
	
}

void Role::refreshAction(bool go /* = false */)
{
	__String actionName;
	if ( getDir() < FACES )
	{
		actionName.initWithFormat("%s_%d",getActionName().c_str(),getDir());
		flip(false);
	}
	else
	{
		actionName.initWithFormat("%s_%d",getActionName().c_str(),DIR_MAX-getDir());
		flip();
	}

	int frameIndex = 0;

	if ( m_pArmor )
	{
		frameIndex = m_pArmor->getAnimation()->getCurrentFrameIndex();
		m_pArmor->getAnimation()->play(actionName.getCString(),m_nDurationTo,m_nLoop);
		if ( go )
		{
			m_pArmor->getAnimation()->gotoAndPlay(frameIndex);
		}
	}

	if ( m_pWeapon )
	{
		m_pWeapon->getAnimation()->play(actionName.getCString(),m_nDurationTo,m_nLoop);

		if ( go )
		{
			m_pWeapon->getAnimation()->gotoAndPlay(frameIndex);
		}
	}

	if ( m_pWing )
	{
		m_pWing->getAnimation()->play(actionName.getCString(),m_nDurationTo,m_nLoop);

		if ( go )
		{
			m_pWing->getAnimation()->gotoAndPlay(frameIndex);
		}
	}
}

void Role::playAction(RoleAction action,int duration/* = 0*/, int loop/* = -1*/)
{
	if ( action == m_sActionName )
	{
		return ;
	}

	stopAction();

	m_sActionName = action;
	m_nLoop = loop;

	refreshAction();

	SetActionSpeed(duration);
}

void Role::stopAction()
{
	if ( m_pArmor )
	{
		m_pArmor->getAnimation()->stop();
	}

	if ( m_pWeapon )
	{
		m_pWeapon->getAnimation()->stop();
	}

	if ( m_pWing )
	{
		m_pWing->getAnimation()->stop();
	}

	m_sActionName = RoleAction_Stand;
}

void Role::enableLightShadow(bool flag)
{
	m_bLightShadow = flag;

	if ( !m_bLightShadow )
	{
		if ( m_pArmorShadow )
		{
			m_pArmorShadow->removeFromParent();
			m_pArmorShadow = NULL ;
		}

		if ( m_pWeaponShadow )
		{
			m_pWeaponShadow->removeFromParent();
			m_pWeaponShadow = NULL ;
		}

		if ( m_pWingShadow )
		{
			m_pWingShadow->removeFromParent();
			m_pWingShadow = NULL ;
		}

		m_nArmorShadowFrame = -1;
		m_nWeaponShadowFrame = -1;
		m_nWingShadowFrame = -1;
	}
}

void Role::enableGhostShadow(bool flag)
{
	m_bGhostShadow = flag;

	if ( !m_bGhostShadow )
	{
		if ( m_pGhostShadowLayer )
		{
			m_pGhostShadowLayer->removeFromParent();
			m_pGhostShadowLayer = NULL;
		}
	}
}

void Role::draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	Node::draw(renderer,transform,transformUpdated);

	static CustomCommand _customCommand;
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(Role::onDraw, this, renderer,transform, transformUpdated);
	renderer->addCommand(&_customCommand);

	//onDraw(renderer,transform,transformUpdated);
}

void Role::onDraw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	if ( !GetMap() )
	{
		return ;
	}

	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);

	//drawCollisionRect(renderer,transform,transformUpdated);
	//drawRoleCell(renderer,transform,transformUpdated);
	//drawHungingPoints(renderer,transform,transformUpdated);

	//end draw
	kmGLPopMatrix();
}

void Role::drawCollisionRect(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	DrawPrimitives::setDrawColor4B(0, 255, 0, 66);
	glLineWidth (1.0);

	Point point0(m_CollisionRect.getMinX(),m_CollisionRect.getMinY());
	Point point1(m_CollisionRect.getMinX(),m_CollisionRect.getMaxY());
	Point point2(m_CollisionRect.getMaxX(),m_CollisionRect.getMaxY());
	Point point3(m_CollisionRect.getMaxX(),m_CollisionRect.getMinY());

	point0 -= getPosition();
	point1 -= getPosition();
	point2 -= getPosition();
	point3 -= getPosition();

	Point glVertices[] = {point0,point1,point2,point3};

	DrawPrimitives::drawSolidPoly(glVertices,4,Color4F(0,255,0,66));

	CHECK_GL_ERROR_DEBUG();
}

void Role::drawRoleCell(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	DrawPrimitives::setDrawColor4B(0, 255, 0, 55);
	glLineWidth (1.0);

	int x0,y0,x1,y1,x2,y2,x3,y3;

	x0 = m_RegionCell.getMinX();
	y0 = m_RegionCell.getMinY();
	x1 = m_RegionCell.getMaxX();
	y1 = m_RegionCell.getMaxY();

	GetMap()->getTerrain()->cell2World(x0,y0);
	GetMap()->getTerrain()->cell2World(x1,y1);

	x0 -= getPositionX();
	x1 -= getPositionX();
	y0 -= getPositionY();
	y1 -= getPositionY();

	y0 += cellInPixelsY/2;
	y1 -= cellInPixelsY/2;

	x2 = x0 - m_RegionCell.size.height*cellInPixelsX/2-cellInPixelsX/2;
	y2 = y0 - m_RegionCell.size.height*cellInPixelsY/2-cellInPixelsY/2;
	x3 = x0 + m_RegionCell.size.width*cellInPixelsX/2+cellInPixelsX/2;
	y3 = y0 - m_RegionCell.size.width*cellInPixelsY/2-cellInPixelsY/2;

	Point glVertices[] = {Point(x0,y0),Point(x2,y2),Point(x1,y1),Point(x3,y3)};

	DrawPrimitives::drawSolidPoly(glVertices,4,Color4F(255,0,0,55));

	CHECK_GL_ERROR_DEBUG();
}

void Role::drawHungingPoints(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	DrawPrimitives::setDrawColor4B(0, 0, 255, 55);
	glLineWidth (1.0);

	int x0,y0,x1,y1,x2,y2,x3,y3;
	int r = 5;

	for ( size_t i = 0;i<m_HungingPoints.size();++i )
	{
		Point pt = m_HungingPoints[i];
		pt -= getPosition();

		x0 = pt.x - r;
		y0 = pt.y - r;

		x1 = pt.x - r;
		y1 = pt.y + r;

		x2 = pt.x + r;
		y2 = pt.y + r;

		x3 = pt.x + r;
		y3 = pt.y - r;

		Point glVertices[] = {Point(x0,y0),Point(x1,y1),Point(x2,y2),Point(x3,y3)};

		DrawPrimitives::drawSolidPoly(glVertices,4,Color4F(0,0,255,55));
	}

	CHECK_GL_ERROR_DEBUG();
}

bool Role::updateMove(float dt)
{
	m_MoveMonitor.Update(dt);

	if (m_MoveMonitor.IsStepOver())
	{
		enableGhostShadow(false);
		SetCell(m_MoveMonitor.GetCurrPoint().x,m_MoveMonitor.GetCurrPoint().y);
		return false;
	}

	changeDir(m_MoveMonitor.GetDir());

	int x = m_MoveMonitor.GetCurrPoint().x;
	int y = m_MoveMonitor.GetCurrPoint().y;

	if ( x != GetCellX() || y != GetCellY() )
	{
		SetCell(x,y);
	}

	GetMap()->getTerrain()->cell2World(x,y);

	Point newPos(0,0);

	newPos.x = x + m_MoveMonitor.GetCurrPointOffset().x;
	newPos.y = y + m_MoveMonitor.GetCurrPointOffset().y;

	//CCLog("cellPos:(%d,%d),newPos:(%f,%f),offset:(%f,%f)",
	//	GetCellX(), GetCellY(),newPos.x,newPos.y,
	//	m_MoveMonitor.GetCurrPointOffset().x,m_MoveMonitor.GetCurrPointOffset().y);

	// 残影效果
	if ( m_bGhostShadow && getArmor() )
	{
		if ( !m_pGhostShadowLayer )
		{
			m_pGhostShadowLayer = Layer::create();
			GetMap()->addChild(m_pGhostShadowLayer);
		}

		const Map<std::string, Bone*>& map = getArmor()->getBoneDic();
		for(const auto& element : map)
		{
			Node *node = element.second->getDisplayRenderNode();
			if ( !node )
			{
				continue;
			}
			SpriteFrame* frame = static_cast<Skin*>(node)->getSpriteFrame()->clone();
			Sprite* sprite = Sprite::createWithSpriteFrame(frame);
			
			static const int ONE_ACTION_FACES = 5;
			if ( getDir() < ONE_ACTION_FACES )
			{
				sprite->setScaleX(1.0f);
			}
			else
			{
				sprite->setScaleX(-1.0f);
			}

			sprite->setPosition(getPosition());

			sprite->runAction(Sequence::create(FadeOut::create(0.15f),CallFunc::create( CC_CALLBACK_0(Role::GhostShadowCallBack,this,sprite)),NULL));

			m_pGhostShadowLayer->addChild(sprite);
		}
	}

	setPosition(newPos);

	return true;
}

bool Role::updateFlash(float dt)
{
	if (m_MoveMonitor.IsStepOver())
	{
		enableGhostShadow(false);
		return false;
	}

	m_MoveMonitor.Update(dt);

	if (m_MoveMonitor.IsStepOver())
	{
		enableGhostShadow(false);
		SetCell(m_MoveMonitor.GetCurrPoint().x,m_MoveMonitor.GetCurrPoint().y);
		return false;
	}

	changeDir(m_MoveMonitor.GetDir());

	int x = m_MoveMonitor.GetCurrPoint().x;
	int y = m_MoveMonitor.GetCurrPoint().y;

	if ( x != GetCellX() || y != GetCellY() )
	{
		SetCell(x,y);
	}

	GetMap()->getTerrain()->cell2World(x,y);

	Point newPos(0,0);

	newPos.x = x + m_MoveMonitor.GetCurrPointOffset().x;
	newPos.y = y + m_MoveMonitor.GetCurrPointOffset().y;

	//CCLog("cellPos:(%d,%d),newPos:(%f,%f),offset:(%f,%f)",
	//	GetCellX(), GetCellY(),newPos.x,newPos.y,
	//	m_MoveMonitor.GetCurrPointOffset().x,m_MoveMonitor.GetCurrPointOffset().y);

	// 残影效果
	if ( m_bGhostShadow )
	{
		if ( !m_pGhostShadowLayer )
		{
			m_pGhostShadowLayer = Layer::create();
			GetMap()->addChild(m_pGhostShadowLayer);
		}

		const Map<std::string, Bone*>& map = getArmor()->getBoneDic();
		for(const auto& element : map)
		{
			Node *node = element.second->getDisplayRenderNode();
			if ( !node )
			{
				continue;
			}
			SpriteFrame* frame = static_cast<Skin*>(node)->getSpriteFrame()->clone();
			Sprite* sprite = Sprite::createWithSpriteFrame(frame);

			static const int ONE_ACTION_FACES = 5;
			if ( getDir() < ONE_ACTION_FACES )
			{
				sprite->setScaleX(1.0f);
			}
			else
			{
				sprite->setScaleX(-1.0f);
			}

			sprite->setPosition(getPosition());

			sprite->runAction(Sequence::create(FadeOut::create(0.15f),CallFunc::create( CC_CALLBACK_0(Role::GhostShadowCallBack,this,sprite)),NULL));

			m_pGhostShadowLayer->addChild(sprite);
		}
	}

	setPosition(newPos);

	return true;
}

void Role::GhostShadowCallBack(Sprite* pSprite)
{
	if ( pSprite )
	{
		pSprite->removeFromParent();
	}
}

void Role::SetSkinEffect(int type)
{
	MapObject::SetSkinEffect(type);

	if ( getArmor() )
	{
		getArmor()->setSkinEffect(SkinEffectType(type));
	}

	if ( getWeapon() )
	{
		getWeapon()->setSkinEffect(SkinEffectType(type));
	}

	if ( getWing() )
	{
		getWing()->setSkinEffect(SkinEffectType(type));
	}
}

void Role::updateLightShadow(float dt)
{
	// 衣服光影
	if( getArmor() && getArmor()->getBone("body") )
	{
		int idx = getArmor()->getBone("body")->getDisplayManager()->getCurrentDisplayIndex();
		if ( m_nArmorShadowFrame != idx )
		{
			m_nArmorShadowFrame = idx;

			Node *armor  = getArmor()->getBone("body")->getDisplayRenderNode();
			SpriteFrame* frame = static_cast<Skin*>(armor)->getSpriteFrame();

			// 克隆一帧，制作新光影
			frame = static_cast<Skin*>(armor)->getSpriteFrame()->clone();

			Sprite* sprite = Sprite::createWithSpriteFrame(frame);

			static const int ONE_ACTION_FACES = 5;
			if ( getDir() < ONE_ACTION_FACES )
			{
				sprite->setScaleX(1.2f);
			}
			else
			{
				sprite->setScaleX(-1.2f);
			}

			sprite->setScaleY(0.6f);
			sprite->setRotationSkewX(45);
			sprite->setRotationSkewY(15);
			sprite->setColor(Color3B::BLACK);
			sprite->setOpacity(0x6E);

			if ( m_pArmorShadow )
			{
				m_pArmorShadow->removeFromParent();
				m_pArmorShadow = NULL;
			}

			m_pArmorShadow = sprite;
			addChild(m_pArmorShadow,-1);

		}
	}
	else
	{
		if ( m_pArmorShadow )
		{
			m_pArmorShadow->removeFromParent();
			m_pArmorShadow = NULL;
		}
	}
	
	if( getWeapon() && getWeapon()->getBone("body") )
	{
		int idx = getWeapon()->getBone("body")->getDisplayManager()->getCurrentDisplayIndex();
		if ( m_nWeaponShadowFrame != idx )
		{
			m_nWeaponShadowFrame = idx;

			Node *weapon  = getWeapon()->getBone("body")->getDisplayRenderNode();
			SpriteFrame* frame = static_cast<Skin*>(weapon)->getSpriteFrame();

			// 克隆一帧，制作新光影
			frame = static_cast<Skin*>(weapon)->getSpriteFrame()->clone();

			Sprite* sprite = Sprite::createWithSpriteFrame(frame);

			static const int ONE_ACTION_FACES = 5;
			if ( getDir() < ONE_ACTION_FACES )
			{
				sprite->setScaleX(1.2f);
			}
			else
			{
				sprite->setScaleX(-1.2f);
			}

			sprite->setScaleY(0.6f);
			sprite->setRotationSkewX(45);
			sprite->setRotationSkewY(15);
			sprite->setColor(Color3B::BLACK);
			sprite->setOpacity(0x6E);

			if ( m_pWeaponShadow )
			{
				m_pWeaponShadow->removeFromParent();
				m_pWeaponShadow = NULL;
			}

			m_pWeaponShadow = sprite;
			addChild(m_pWeaponShadow,-1);
		}
	}
	else
	{
		if ( m_pWeaponShadow )
		{
			m_pWeaponShadow->removeFromParent();
			m_pWeaponShadow = NULL;
		}
	}

	if( getWing() && getWing()->getBone("body"))
	{
		int idx = getWeapon()->getBone("body")->getDisplayManager()->getCurrentDisplayIndex();
		if ( m_nWingShadowFrame != idx )
		{
			m_nWingShadowFrame = idx;

			Node *wing  = getWing()->getBone("body")->getDisplayRenderNode();
			SpriteFrame* frame = static_cast<Skin*>(wing)->getSpriteFrame();

			// 克隆一帧，制作新光影
			frame = static_cast<Skin*>(wing)->getSpriteFrame()->clone();

			Sprite* sprite = Sprite::createWithSpriteFrame(frame);

			static const int ONE_ACTION_FACES = 5;
			if ( getDir() < ONE_ACTION_FACES )
			{
				sprite->setScaleX(1.2f);
			}
			else
			{
				sprite->setScaleX(-1.2f);
			}

			sprite->setScaleY(0.6f);
			sprite->setRotationSkewX(45);
			sprite->setRotationSkewY(15);
			sprite->setColor(Color3B::BLACK);
			sprite->setOpacity(0x6E);

			if ( m_pWingShadow )
			{
				m_pWingShadow->removeFromParent();
				m_pWingShadow = NULL;
			}

			m_pWingShadow = sprite;
			addChild(m_pWingShadow,-1);
		}
	}
	else
	{
		if ( m_pWingShadow )
		{
			m_pWingShadow->removeFromParent();
			m_pWingShadow = NULL;
		}
	}
}

void Role::Move(APath& path,long offset/* =0 */)
{
	m_MoveMonitor.Move(APoint(GetCellX(),GetCellY()),path,GetMoveSpeed(),offset);

	EnterState(RoleState_Move);
}

void Role::Stop()
{
	m_MoveMonitor.MoveEnd();
}

void Role::StopTo(int x,int y)
{
	// 如果坐标不同步
	if ( IsMoving() )
	{
		GetMoveMonitor().Terminate();
		EnterState(RoleState_Idle);
	}

	SetCell(x,y);
}

void Role::processCommand(const RoleCommand& cmd)
{
	if ( cmd.type == RoleCommand_Move )
	{
		MoveTo(cmd.param.pos.x,cmd.param.pos.y);
	}
}

void Role::pushCommand(const RoleCommand& cmd)
{
	if ( cmd.type == RoleCommand_Move )
	{
		m_dequeCommands.clear();
	}

	if ( cmd.type == RoleCommand_Attack )
	{
		m_dequeCommands.clear();
	}

	m_dequeCommands.push_back(cmd);
}

void Role::Pursue(__int64 targetid,int distance,const RoleCommand& cmd)
{
	m_pursueTargetPos = APoint(0,0);
	m_nPursueTargetID = targetid;
	m_nPursueDistance = distance;
	m_pursueCommand = cmd;
}

void Role::PursueCancel()
{
	m_nPursueTargetID = 0;
	m_nPursueDistance = 0;
	m_pursueCommand.type = RoleCommand_None;
}

bool Role::PursueCheck()
{
	return true;
}

bool Role::PursueOk()
{
	if ( GetDistanceTo(m_pursueTargetPos.x,m_pursueTargetPos.y) <= m_nPursueDistance+1 )
	{
		return true;
	}
	return false;
}

void Role::PursueUpdate()
{
	if ( m_nPursueTargetID == 0 )
	{
		return ;
	}
	
	Role *pTarget = (Role*)GetMap()->getObjectManager()->getObject(m_nPursueTargetID);
	if ( !pTarget || !PursueCheck() )
	{
		Stop();
		PursueCancel();
		return ;
	}

	if ( PursueOk() )
	{
		if ( IsMoving() )
		{
			Stop();
		}
		else
		{
			processCommand(m_pursueCommand);
			PursueCancel();
		}
		return ;
	}

	if ( (m_pursueTargetPos.x != pTarget->GetCellX() || 
		 m_pursueTargetPos.y != pTarget->GetCellY()) )
	{
		m_pursueTargetPos.x = pTarget->GetCellX();
		m_pursueTargetPos.y = pTarget->GetCellY();

		//RoleCommand cmd;
		//cmd.type = RoleCommand_Move;
		//cmd.param.pos.x = m_pursueTargetPos.x;
		//cmd.param.pos.y = m_pursueTargetPos.y;
		//gHero->pushCommand(cmd);
		MoveTo(m_pursueTargetPos.x,m_pursueTargetPos.y);
	}
}
#include "GameMap.h"
#include "Hero.h"
#include "UI/CustomCtrl/JoyStick.h"
#include "GameDataManager.h"
#include "RoleTitleLayer.h"
#include "Net/NetDispatcher.h"
#include "GameManager.h"
#include "../Common/CommonDef.h"
#include "Robot.h"
#include "map_io.h"
#include "GameHelper.h"

GameMap::GameMap() : m_pData(NULL)
{

}

GameMap::~GameMap()
{
	m_reliveRules.clear();
}

bool GameMap::init()
{
	if ( !TileMap::init() )
	{
		return false;
	}

	// 增加特效层
	m_pEffectLayer = Layer::create();
	if ( !m_pEffectLayer )
	{
		return false;
	}
	addChild(m_pEffectLayer);

	// 增加角色名称显示
	addChild(gRoleTitleLayer);

	return true;
}

void GameMap::update(float dt)
{
	TileMap::update(dt);

	// 子弹管理器
	gBulletMgr->UpdateBullet(dt);
}

void GameMap::updateView()
{
	Point posView = gHero->getPosition()+Point(0,85.f);

	Rect rect;

	Size viewSize = gDirector->getVisibleSize();
	Point viewOrigin = gDirector->getVisibleOrigin();
	Point offsetLD;
	Point offsetRU;
	rect.setRect(viewOrigin.x+m_viewPoint.x+offsetLD.x,viewOrigin.y+m_viewPoint.y+offsetLD.y,(viewSize.width+offsetRU.x)/getScaleX(),(viewSize.height+offsetRU.y)/getScaleY());

	Point posMin = Point(rect.getMaxX()-rect.getMidX(),rect.getMaxY()-rect.getMidY());
	Point posMax = Point(GetMaxViewX()+rect.getMaxX()-rect.getMidX(),GetMaxViewY()+rect.getMaxY()-rect.getMidY());
	// 限制地图出屏
	if( posView.x<posMin.x ) posView.x = posMin.x;
	if( posView.x>posMax.x ) posView.x = posMax.x;
	if( posView.y<posMin.y ) posView.y = posMin.y;
	if( posView.y>posMax.y ) posView.y = posMax.y;

	SetView(posView);
}

void GameMap::shake(float deltaX /* = 1.0f */,float deltaY /* = 1.0f */,float rate /* = 0.1f */,int times /* = 5 */)
{
	Vector<FiniteTimeAction*> arrayOfActions;

	Point pos = this->getPosition();

	// 衰减因子
	float dec = 1.0f;

	for (int i = 0; i < times; i++)
	{
		ActionInterval* action1 = MoveTo::create(rate/4.0f*dec,pos+Point(deltaX,deltaY)*dec);
		ActionInterval* action2 = MoveTo::create(rate/4.0f*dec,pos);
		ActionInterval* action3 = MoveTo::create(rate/4.0f*dec,pos+Point(-deltaX,-deltaY)*dec);
		ActionInterval* action4 = MoveTo::create(rate/4.0f*dec,pos);
		arrayOfActions.pushBack(action1);
		arrayOfActions.pushBack(action2);
		arrayOfActions.pushBack(action3);
		arrayOfActions.pushBack(action4);
		dec -= dec / (float)times;
	}
	arrayOfActions.pushBack(CallFunc::create( CC_CALLBACK_0(GameMap::onShakeEnded,this)));
	
	runAction(Sequence::create(arrayOfActions));
}

void GameMap::onShakeEnded()
{
	//setPosition(Point::ZERO);
}

bool GameMap::onTouchBegan(Touch *touch, Event *unused_event)
{
	Point pos = convertTouchToNodeSpace(touch);

	gRobot->SetRunning(false);

	return true;
}

void GameMap::onTouchMoved(Touch *touch, Event *unused_event)
{
	Point pos = convertTouchToNodeSpace(touch);
}

void GameMap::onTouchEnded(Touch *touch, Event *unused_event)
{
	Point pos = convertTouchToNodeSpace(touch);

	Point logicPoint = convertToNodeSpace(touch->getLocation());
	int cx = (int)logicPoint.x;
	int cy = (int)logicPoint.y;
	getTerrain()->world2Cell(cx,cy);

	// 选中目标
	if ( gHero->SelectTargetByPos(pos) )
	{
		return ;
	}

	if ( gGameHelper->IsDoubleClicked() )
	{
		gHero->Evade(cx,cy);
	}
	else
	{
		gHero->MoveTo(cx,cy);
	}

	// 点击地图特效
	gMap->ShowEffect(151611,"Animation1",logicPoint,0.5f);

	/*float scale = 1.0f;
	float scaleX = scale;
	int zorder = 0;
	__String str;
	if ( gHero->getDir() < Role::FACES )
	{
		str.initWithFormat("dir_skill3_%d",gHero->getDir());
		scaleX *= 1.0f;
	}
	else
	{
		scaleX *= -1.0f;
		str.initWithFormat("dir_skill3_%d",DIR_MAX-gHero->getDir());
	}

	if ( gHero->getDir() == DIR_N || 
		 gHero->getDir() == DIR_NE ||
		 gHero->getDir() == DIR_NW )
	{
		zorder = -10;
	}
	else
	{
		zorder = 10;
	}

	Effect* pEffect = Effect::createWithDataID(151013);
	if ( pEffect )
	{
		pEffect->setScale(scale);
		pEffect->setScaleX(scaleX);
		pEffect->setName(str.getCString());
		gMap->ShowEffect(pEffect,pos,1.5f);
	}*/
}

void GameMap::onTouchCancelled(Touch *touch, Event *unused_event)
{
	Point pos = convertTouchToNodeSpace(touch);
}

int GameMap::getDistance(const APoint& pos0,const APoint& pos1)
{
	return Distance(pos0.x,pos0.y,pos1.x,pos1.y);
}

APoint GameMap::checkTargetPos(const APoint& pos0,const APoint& pos1)
{
	int dx = pos1.x-pos0.x;
	int dy = pos1.y-pos0.y;
	int di = MAX(abs(dx),abs(dy));

	float factor_x = dx >= dy ? 1.0f : float(dx) / float(dy);
	float factor_y = dy >= dx ? 1.0f : float(dy) / float(dx);

	APoint pos = pos0;

	float next_x = pos.x + factor_x;
	float next_y = pos.y + factor_y;



	while (pos.x != pos1.x || pos.y != pos1.y)
	{
		if( getTerrain()->getCell(FLOAT_TO_INT_5(next_x),FLOAT_TO_INT_5(next_y))->isMark(cellMaskStop) )
		{
			break;
		}

		pos.x = FLOAT_TO_INT_5(next_x);
		pos.y = FLOAT_TO_INT_5(next_y);
		next_x += factor_x;
		next_y += factor_y;
	}

	return pos;
}

APoint GameMap::checkTargetPosWithDistance(const APoint& pos0,const APoint& pos1,int dis)
{
	int dx = pos1.x-pos0.x;
	int dy = pos1.y-pos0.y;
	int di = MAX(abs(dx),abs(dy));

	float factor_x = abs(dx) > abs(dy) ? 1.0f : fabs(float(dx) / float(dy));
	float factor_y = abs(dy) > abs(dx) ? 1.0f : fabs(float(dy) / float(dx));

	APoint pos = pos0;

	float next_x = dx > 0 ? pos.x + factor_x : pos.x - factor_x;
	float next_y = dy > 0 ? pos.y + factor_y : pos.y - factor_y;



	while (pos.x != pos1.x || pos.y != pos1.y)
	{
		if( getTerrain()->getCell(FLOAT_TO_INT_5(next_x),FLOAT_TO_INT_5(next_y))->isMark(cellMaskStop) )
		{
			break;
		}

		if ( getDistance(pos,pos0) > dis )
		{
			break;
		}

		pos.x = FLOAT_TO_INT_5(next_x);
		pos.y = FLOAT_TO_INT_5(next_y);

		next_x = dx > 0 ? next_x + factor_x : next_x - factor_x;
		next_y = dy > 0 ? next_y + factor_y : next_y - factor_y;
	}

	return pos;
}

void GameMap::ShowEffect(int dataid,const string& name,const Point& pos,float duration /* = 0.0f */,float scale /* = 1.0f */)
{
	Effect* pEffect = Effect::createWithDataID(dataid);
	if ( pEffect )
	{
		pEffect->setName(name);
		ShowEffect(pEffect,pos,duration,scale);
	}
}

void GameMap::ShowEffect(Effect* pEffect,const Point& pos,float duration /* = 0.0f */,float scale /* = 1.0f */)
{
	if ( pEffect )
	{
		pEffect->setPosition(pos);
		pEffect->setDuration(duration);
		pEffect->setScale(scale);
		m_pEffectLayer->addChild(pEffect);

		pEffect->runAction(Sequence::create(DelayTime::create(duration),CallFunc::create( CC_CALLBACK_0(GameMap::ShowEffectCallBack,this,pEffect)),NULL));
	}
}

void GameMap::ShowEffectCallBack(Effect* pEffect)
{
	if ( pEffect )
	{
		pEffect->removeFromParent();
	}
}

bool GameMap::loadMap(int mapid)
{
	MapCfg* pData = MapData.get(mapid);
	if ( !pData )
	{
		LOGE("========GameMap::setMapDataID [%d]  Not Found!============",mapid);
		return false;
	}

	m_pData = pData;

	m_reliveRules.clear();
	StringSplitToInt(m_pData->recover_life_ids,";",m_reliveRules);
	
	string map = "assets/map/"+m_pData->map;

	LOGD("========CGameMap::loadMap[%s]  start============",map.c_str());

	map_context* context = new map_context;
	if ( !context )
	{
		return false;
	}

	int ret = map_io::load_from_map(map.c_str(),context);
	if ( ret != MAP_STATUS_OK )
	{
		map_io::map_free(context);
		LOGE("========CGameMap::loadMap[%s]  load_from_map failed============",map.c_str());
		return false;
	}

	if ( initWithMapContext(context) )	
	{
		gCocosAudio->PlayMusic(pData->sound,true);
		LOGE("========CGameMap::loadMap[%s] success============",map.c_str());

		return true;
	}

	LOGE("========CGameMap::loadMap[%s]  initWithMapContext failed============",map.c_str());
	return false;
}
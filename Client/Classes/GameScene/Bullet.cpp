#include "Bullet.h"
#include "GameDataManager.h"
#include "CommonDef.h"
#include "RoleFighter.h"
#include "Hero.h"
#include "Log.h"
#include "GameDef.h"
#include "Net/pk_map.h"
#include "Net/NetDispatcher.h"

Bullet* Bullet::CreateWithDataID(__int64 id,int dataid,const Point& pos,const Point& targetPos,MapObjectID casterid,SkillCfg* pSkill)
{
	BulletCfg* pData = BulletData.get(dataid);
	if ( !pData )
	{
		LOGE("Bullet [%d] not found!",dataid);
		return NULL;
	}
	
	return Bullet::CreateWithData(id,pData,pos,targetPos,casterid,pSkill);
}

Bullet* Bullet::CreateWithData(__int64 id,BulletCfg* pData,const Point& pos,const Point& targetPos,MapObjectID casterid,SkillCfg* pSkill)
{
	Bullet* pRet = Bullet::create();
	if ( pRet )
	{
		pRet->SetId(id);
		pRet->Reload(pData);
		pRet->setPosition(pos);
		pRet->SetCasterID(casterid);
		pRet->SetSkillData(pSkill);
		pRet->SetTargetPos(targetPos);
		pRet->SetTargetVec((targetPos-pos).normalize());
		if ( gHero->GetId() == casterid )
		{
			pRet->SetCollisionNeed(true);
		}
		return pRet;
	}

	return NULL;
}

Bullet::Bullet() : m_llId(0),m_pData(NULL),m_fLeft(0.0f),
	m_fRight(0.0f),m_fTop(0.0f),m_fBottom(0.0f),m_CasterID(0),
	m_pSkillData(NULL),m_nPenetratePower(0),m_fLifeTime(0.0f),
	m_bCollision(false)
{

}

Bullet::Bullet(__int64 id,BulletCfg* pData) : m_llId(id),m_pData(NULL),m_fLeft(0.0f),
	m_fRight(0.0f),m_fTop(0.0f),m_fBottom(0.0f),m_CasterID(0),
	m_pSkillData(NULL),m_nPenetratePower(0),m_fLifeTime(0.0f),
	m_bCollision(false)
{
	Reload(pData);
}

Bullet::~Bullet()
{
	Clear();
}

void Bullet::Reload(int bulletid)
{
	BulletCfg* pData = BulletData.get(bulletid);
	if ( !pData )
	{
		LOGE("Bullet [%d] not found!",bulletid);
		return ;
	}

	Reload(pData);
}

void Bullet::Reload(BulletCfg* pData)
{
	if ( !pData )
	{
		return ;
	}

	m_pData = pData;

	Clear();
	
	Effect::GetEffectListByConfig(m_pData->aim_art,m_effectListAim);
	Effect::GetEffectListByConfig(m_pData->flyart,m_effectListFly);
	Effect::GetEffectListByConfig(m_pData->blastart,m_effectListBlast);

	// 创建特效
	for(size_t i = 0 ;i<m_effectListAim.size();++i )
	{
		CC_SAFE_RETAIN(m_effectListAim[i]);
	}

	for(size_t i = 0 ;i<m_effectListFly.size();++i )
	{
		CC_SAFE_RETAIN(m_effectListFly[i]);
	}

	for(size_t i = 0 ;i<m_effectListBlast.size();++i )
	{
		CC_SAFE_RETAIN(m_effectListBlast[i]);
	}

	Prepare();
}

void Bullet::Clear()
{
	removeAllChildren();
	for(size_t i = 0 ;i<m_effectListAim.size();++i )
	{
		CC_SAFE_RELEASE(m_effectListAim[i]);
	}

	for(size_t i = 0 ;i<m_effectListFly.size();++i )
	{
		CC_SAFE_RELEASE(m_effectListFly[i]);
	}

	for(size_t i = 0 ;i<m_effectListBlast.size();++i )
	{
		CC_SAFE_RELEASE(m_effectListBlast[i]);
	}
}

void Bullet::Prepare()
{
	m_nPenetratePower = m_pData->penetrate+1;

	// 创建飞行特效
	for(size_t i = 0 ;i<m_effectListFly.size();++i )
	{
		addChild(m_effectListFly[i]);
	}

}

bool Bullet::checkCollision(const Rect& rect)
{
	// 圆心
	Point circleCenter = getPosition();
	// 矩形中心
	Point rectCenter = Point(rect.getMidX(),rect.getMidY());
	// 差异向量
	Point diffVec = circleCenter-rectCenter;
	// 两中心间距
	float dist = diffVec.getLength();
	// 参考距离
	float distRef = GetData()->radius + rect.size.width*0.125f;

	return dist < distRef;
}

void Bullet::SetTargetPos(const Point& pos)
{
	m_TargetPos = pos;

	// 取飞行方向
	if ( GetData()->type == 1 )
	{
		m_TargetVec = (m_TargetPos-getPosition()).normalize();
	}
}

void Bullet::ProcessFly(float dt)
{
	// 速度为0，直接命中目标点
	if ( GetData()->speed == 0 )
	{
		setPosition(m_TargetPos);
	}
	else
	{
		// 计算新的位置
		Point pos = getPosition()+m_TargetVec*GetData()->speed*dt;
		setPosition(pos);
		setRotation(-CC_RADIANS_TO_DEGREES(m_TargetVec.getAngle()));
	}
}

void Bullet::Update(float dt)
{
	if ( IsDie() )
	{
		return ;
	}

	// 增加生命期
	m_fLifeTime += dt;

	// 生命周期耗尽
	if ( m_fLifeTime*1000>GetData()->duration )
	{
		OnBlast();
		return ;
	}

	// 碰撞
	RoleFighter* pCaster = GetMapRole(m_CasterID);
	if ( pCaster )
	{
		MapObjectList objs = gMap->getObjectManager()->GetObjectList();
		for ( MapObjectList::iterator itr = objs.begin();itr != objs.end();++itr )
		{
			RoleFighter* pFighter = dynamic_cast<RoleFighter*>(*itr);
			if ( pFighter && pCaster->IsEnemyTo(pFighter) && 
				!pFighter->IsDead() && 
				checkCollision(pFighter->getBoundingBox()) && 
				!IsHited(pFighter) )
			{

				// 发生碰撞了，通知服务器 穿透 -1
				OnHit(pFighter);

				// 穿透力耗尽
				if ( m_nPenetratePower <= 0 )
				{
					OnBlast();
					return ;
				}
			}
		}
	}
	// 位移
	ProcessFly(dt);
}

bool Bullet::IsHited(RoleFighter* pTarget)
{
	for ( size_t i = 0;i<m_vCollisionList.size();++i )
	{
		if ( m_vCollisionList[i] == pTarget->GetId() )
		{
			return true;
		}
	}

	return false;
}

void Bullet::OnHit(RoleFighter* pTarget)
{
	CCLOG("==========Bullet::OnHit Called. [%d]========",m_nPenetratePower);
	--m_nPenetratePower;

	// 在角色身上显示命中特效
	if ( !m_pData->hitart.empty() && pTarget )
	{
		// 将目标ID加入碰撞列表中
		m_vCollisionList.push_back(pTarget->GetId());

		// 命中特效
		pTarget->ShowEffect(m_pData->hitart);
	}

	if ( IsCollisionNeed() || (GetCasterType() == mapObjectType_Monster && gHero == pTarget) )
	{
		pk::C2GS_MissileDamage cmd;
		cmd.id = GetId();
		cmd.index = GetIndex();
		cmd.targetId = pTarget->GetId();
		cmd.targetX = pTarget->GetCellX();
		cmd.targetY = pTarget->GetCellY();
		cmd.isExplosion = 0;
		cmd.Send(gNetSocket);
	}
}

void Bullet::OnBlast()
{
	// 通知服务器
	if ( IsCollisionNeed() || (GetCasterType() == mapObjectType_Monster) )
	{
		int cx = getPositionX();
		int cy = getPositionY();
		if (gMap )
		{
			gMap->getTerrain()->world2Cell(cx,cy);
		}
		
		pk::C2GS_MissileDamage cmd;
		cmd.id = GetId();
		cmd.index = GetIndex();
		cmd.targetId = 0;
		cmd.targetX = cx;
		cmd.targetY = cy;
		cmd.isExplosion = 1;
		cmd.Send(gNetSocket);
	}
	Blast();
}

void Bullet::Blast()
{
	// 将自己从地图中移除
	this->removeFromParent();

	// 在地图上显示爆炸特效
	// 命中特效
	for ( size_t i = 0;i<m_effectListBlast.size();++i )
	{
		gMap->ShowEffect(m_effectListBlast[i],getPosition());
	}
}

void Bullet::draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	Node::draw(renderer,transform,transformUpdated);

	//static CustomCommand _customCommand;
	//_customCommand.init(_globalZOrder);
	//_customCommand.func = CC_CALLBACK_0(Bullet::onDraw, this, renderer,transform, transformUpdated);
	//renderer->addCommand(&_customCommand);

	//onDraw(renderer,transform,transformUpdated);
}

void Bullet::onDraw(Renderer *renderer, const kmMat4& transform, bool transformUpdated)
{
	kmGLPushMatrix();
	kmGLLoadMatrix(&transform);

	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	glLineWidth (1.0);

	Point point0(-GetData()->radius,-GetData()->radius);
	Point point1(-GetData()->radius,GetData()->radius);
	Point point2(GetData()->radius,GetData()->radius);
	Point point3(GetData()->radius,-GetData()->radius);

	Point glVertices[] = {point0,point1,point2,point3};

	DrawPrimitives::drawSolidPoly(glVertices,4,Color4F(0,255,0,255));

	CHECK_GL_ERROR_DEBUG();

	//end draw
	kmGLPopMatrix();
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	Clear();
}

void BulletManager::CreateBullet(__int64 id,int dataid,RoleFighter* pCaster,SkillCfg* pSkill,const Point& pos,int multi /* = 0 */)
{
	BulletCfg* pData = BulletData.get(dataid);
	if ( !pData )
	{
		LOGE("Bullet [%d] not found!",dataid);
		return;
	}

	// 子弹发出位置
	Point posS = (pData->castpoint <= 0) ? pCaster->getPosition() : pCaster->getHungingPoint(pData->castpoint-1);
	Point posE = pos;

	// 子弹组处理
	switch ( pData->type )
	{
	case BulletType_SingleFly:
		{
			int multi_cnt = multi + 1;
			Point multi_vec = (posE-posS).normalize();
			float multi_delta = pData->radius + 10;
			Point multi_start = posS;
			Point multi_end = posE;
			for ( int i = 0;i<multi_cnt;++i )
			{
				
				Bullet* pBullet = Bullet::CreateWithData(id,pData,multi_start,multi_end,pCaster->GetId(),pSkill);
				if ( pBullet )
				{
					pBullet->SetCasterType(pCaster->GetType());
					pBullet->SetIndex(i);
					AddBullet(pBullet);
					gMap->getEffectLayer()->addChild(pBullet);
				}
				multi_start = multi_start - multi_vec*multi_delta;
				multi_end = multi_end - multi_vec*multi_delta;
			}
		}
		break;
	case BulletType_SingleHitScan:
		{
			int multi_cnt = multi + 1;
			Point multi_start = posS;
			Point multi_end = posE;
			for ( int i = 0;i<multi_cnt;++i )
			{
				Bullet* pBullet = Bullet::CreateWithData(id,pData,multi_start,multi_end,pCaster->GetId(),pSkill);
				if ( pBullet )
				{
					pBullet->SetCasterType(pCaster->GetType());
					pBullet->SetIndex(i);
					AddBullet(pBullet);
					gMap->getEffectLayer()->addChild(pBullet);
				}
			}
		}
		break;
	case BulletType_Multi:
		{
			vector<string> params;
			StringSplit(pData->multi_track,",",params);
			if ( params.size() == 2 )
			{
				int dis = atoi(params[0].c_str());
				int cnt = atoi(params[1].c_str());

				if ( cnt <= 1 )
				{
					LOGE("bulletdata multi_track warnning cnt <= 1. param[%s]",pData->multi_track.c_str());
					return;
				}

				// 旋转90度取向量
				Point vec = (posE - posS).rotate(Point(0,1)).normalize();
				float middis = (float)dis / 2.0f;
				float delta = (float)dis/(cnt-1);
				Point start = posS - (vec*middis);
				Point end = posE - (vec*middis);
				for ( int i = 0;i<cnt;++i )
				{
					int multi_cnt = multi + 1;
					Point multi_vec = (end-start).normalize();
					float multi_delta = pData->radius + 10;
					Point multi_start = start;
					Point multi_end = end;						
					for (int j = 0; j < multi_cnt; j++)
					{
						Bullet* pBullet = Bullet::CreateWithData(id,pData,multi_start,multi_end,pCaster->GetId(),pSkill);
						if ( pBullet )
						{
							pBullet->SetCasterType(pCaster->GetType());
							pBullet->SetIndex(i*multi_cnt+j);
							AddBullet(pBullet);
							gMap->getEffectLayer()->addChild(pBullet);
						}
						multi_start = multi_start + multi_vec*multi_delta;
						multi_end = multi_end + multi_vec*multi_delta;
					}
					
					start += (vec*delta);
					end += (vec*delta);
				}
			}
			else
			{
				LOGE("bulletdata multi_track error. param[%s]",pData->multi_track.c_str());
			}
		}
		break;
	case BulletType_MultiAngle:
		{
			vector<string> params;
			StringSplit(pData->multi_track,",",params);
			if ( params.size() == 2 )
			{
				int degree = atoi(params[0].c_str());
				int cnt = atoi(params[1].c_str());

				if ( cnt <= 1 )
				{
					LOGE("bulletdata multi_track warnning cnt <= 1. param[%s]",pData->multi_track.c_str());
					return;
				}

				// 角度转浮点
				float angle = CC_DEGREES_TO_RADIANS(degree);
				Point vec = (posE - posS).normalize();
				float len = (posE-posS).getLength();
				float midangle = (float)angle / 2.0f;
				float delta = degree == 360 ? (float)angle/(cnt) : (float)angle/(cnt-1);
				Point vec_s = vec.rotate(Point::forAngle(midangle));
				Point end = posS+vec_s*len;
				for ( int i = 0;i<cnt;++i )
				{
					int multi_cnt = multi + 1;
					Point multi_vec = (end-posS).normalize();
					float multi_delta = pData->radius + 10;
					Point multi_start = posS;
					Point multi_end = end;
					for ( int j = 0;j<multi_cnt;++j )
					{

						Bullet* pBullet = Bullet::CreateWithData(id,pData,multi_start,multi_end,pCaster->GetId(),pSkill);
						if ( pBullet )
						{
							pBullet->SetCasterType(pCaster->GetType());
							pBullet->SetIndex(i*multi_cnt+j);
							AddBullet(pBullet);
							gMap->getEffectLayer()->addChild(pBullet);
						}
						multi_start = multi_start + multi_vec*multi_delta;
						multi_end = multi_end + multi_vec*multi_delta;
					}
					
					vec_s = vec_s.rotate(Point::forAngle(-delta));
					end = posS+vec_s*len;
				}
			}
			else
			{
				LOGE("bulletdata multi_track error. param[%s]",pData->multi_track.c_str());
			}
		}
		break;
	default:
		break;
	}
}

void BulletManager::AddBullet(Bullet* pBullet)
{
	if ( pBullet )
	{
		pBullet->retain();
		m_Bullets.push_back(pBullet);
	}
}

void BulletManager::Remove(Bullet* pBullet)
{
	for ( BulletList::iterator itr = m_Bullets.begin();itr != m_Bullets.end(); ++itr )
	{
		if ( pBullet == *itr )
		{
			m_Bullets.erase(itr);
			return ;
		}
	}
}

void BulletManager::Clear()
{
	for ( BulletList::iterator itr = m_Bullets.begin();itr != m_Bullets.end(); ++itr )
	{
		CC_SAFE_RELEASE(*itr);
	}

	m_Bullets.clear();
}

void BulletManager::UpdateBullet(float dt)
{
	for ( BulletList::iterator itr = m_Bullets.begin();itr != m_Bullets.end(); )
	{
		Bullet* pBullet = *itr;
		if ( pBullet && !pBullet->IsDie() )
		{
			pBullet->Update(dt);
			++itr;
		}
		else
		{
			CC_SAFE_RELEASE(pBullet);
			itr = m_Bullets.erase(itr);
		}
	}
}

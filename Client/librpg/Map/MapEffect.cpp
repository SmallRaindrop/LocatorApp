#include "MapEffect.h"

MapEffect::MapEffect()
{
	SetType(mapObjectType_Effect);
}

MapEffect::~MapEffect()
{

}

MapEffect* MapEffect::createWithDataID(int dataid)
{
	MapEffect* pEffect = new MapEffect;
	if( pEffect && pEffect->initWithDataID(dataid) )
	{
		pEffect->autorelease();
		return pEffect;
	}

	CC_SAFE_DELETE(pEffect);

	return NULL;
}

bool MapEffect::initWithDataID(int dataid)
{
	SetDataID(dataid);

	m_pEffect = Effect::createWithDataID(dataid,true);
	if ( !m_pEffect )
	{
		return false;
	}

	addChild(m_pEffect);

	return true;
}

void MapEffect::update(float dt)
{
	
}

void MapEffect::SetDataID(int dataid)
{
	MapObject::SetDataID(dataid);
}

void MapEffect::SetSkinEffect(int type)
{
	MapObject::SetSkinEffect(type);

	if ( m_pEffect )
	{
		m_pEffect->setSkinEffect(SkinEffectType(type));
	}
}
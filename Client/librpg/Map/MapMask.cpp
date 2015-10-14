#include "MapMask.h"

MapMask::MapMask() : m_pInfo(NULL),m_pSprite(NULL)
{
	SetType(mapObjectType_Mask);
}

MapMask::~MapMask()
{
	CC_SAFE_RELEASE(m_pSprite);
}

MapMask* MapMask::createWithMaskInfo(MapMaskInfo* pInfo,Image* img,bool grey /* = false */)
{
	MapMask* pMask = new MapMask;
	if ( pMask && pMask->initWithMaskInfo(pInfo,img,grey) )
	{
		pMask->autorelease();
		return pMask;
	}

	CC_SAFE_DELETE(pMask);
	return NULL;
}

bool MapMask::initWithMaskInfo(MapMaskInfo* pInfo,Image* img,bool grey /* = false */)
{
	if ( !pInfo || !img )
	{
		return false;
	}

	Texture2D* pTexture = new Texture2D();
	if( pTexture && pTexture->initWithImage(img) )
	{
		pTexture->autorelease();
		if ( grey )
		{
			m_pSprite = ShaderSprite::createWithTexture(pTexture,-1.0f);
		}
		else
		{
			m_pSprite = ShaderSprite::createWithTexture(pTexture,1.0f);
		}
		if ( m_pSprite )
		{
			m_pSprite->retain();
			m_pSprite->setAnchorPoint(Point(0,0));
			m_pSprite->setOpacity(0xCE);
			//mask2World(pMask->mask,x,y);
			m_pSprite->setPosition(Point(0,0));
			//pSprite->setPosition(Point(pInfo->mask->x,pInfo->mask->y));
			addChild(m_pSprite);	
			
			setZOrder(pInfo->tag);

			m_pInfo = pInfo;

			return true;
		}
	}

	CC_SAFE_RELEASE(pTexture);

	return false;
}

bool MapMask::calMaskRelation(const Point &pos)
{
	if ( !m_pInfo )
	{
		return false;
	}

	int x = pos.x;
	int y = pos.y;

	if (x >= m_pInfo->mask->x && x <= m_pInfo->mask->x+m_pInfo->mask->w
		&& y >= m_pInfo->mask->y && y <= m_pInfo->mask->y+m_pInfo->mask->h)
	{
		//point is in mask section
		int dx = x - m_pInfo->mask->x;
		int dy = m_pInfo->mask->h - (y - m_pInfo->mask->y);
		int totalBitIndex = dy * m_pInfo->mask->w + dx;

		int byteIndex = totalBitIndex / 8;

		int bitIndex = totalBitIndex % 8;

		unsigned char byteValue =  *(m_pInfo->mask_relation + byteIndex);
		int colorValue = (byteValue >> bitIndex) & 0x01;
		if(colorValue == 1) //SHADOW_LAYER_COLOR_GREEN
		{
			return true;
		}
		else
		{
			return false;
		}		
	}
	
	return false;
}

int MapMask::compareZ(MapObject* pObj)
{
	int type =  pObj->GetType();
	switch ( type )
	{
	case mapObjectType_Mask: return 0;
	case mapObjectType_Effect:
	case mapObjectType_Item:
	case mapObjectType_Chests:
	case mapObjectType_Npc:
	case mapObjectType_Monster:
	case mapObjectType_Player:
		{
			if( pObj->getPositionY() < getPositionY()  ) // 角色在遮挡无下方，角色遮挡遮挡物
			{
				return -1;
			}
			else
			{
				Rect rect(m_pInfo->mask->x,m_pInfo->mask->y,m_pInfo->mask->w,m_pInfo->mask->h);
				// 角色与遮挡无是否有交集
				if ( rect.containsPoint(pObj->getPosition()) )
				{
					if ( calMaskRelation(pObj->getPosition()) )
					{
						return -1;
					}
					else
					{
						return 1;
					}
				}
				else
				{
					return 0;
				}
			}
			return 0;
		}
	default:
		break;
	}

	return 0;
}
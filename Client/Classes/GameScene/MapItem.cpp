#include "MapItem.h"
#include "TileMap.h"
#include "ui/UIImageView.h"
#include "Common/CommonDef.h"
#include "Hero.h"
#include "Net/pk_map.h"
#include "Net/NetDispatcher.h"
#include "MapObject.h"


#define ICON_ITEM_SCALE		0.5

using namespace ui;

extern float fNow;
CMapItem::CMapItem() : 
	m_pDropIcon(NULL)
	,m_pLabelName(NULL)
	,m_nDropArtID(0)
	,m_nDispArtID(0)
	,m_sDropArtName("")
	,m_sDispArtName("")
{
	m_fBornTime = fNow;
}

bool CMapItem::init()
{
	// maybe should manage label according to IRole
	/*
	m_pLabelName = Label::create();
	if ( m_pLabelName )
	{
		m_pLabelName->setSystemFontSize(20);
		m_pLabelName->setPosition(Point(0,40));
		addChild(m_pLabelName);
	}
	*/

	return true;
}

CMapItem::~CMapItem()
{
}

void CMapItem::SetDataID(int dataid)
{
	SetType(mapObjectType_Item);

	m_pItemData = ItemData.get(dataid);
	if ( m_pItemData )
	{
		//0000144: 道具掉落在地上时，绿色道具不显示其名字，蓝色、橙色道具名字字色与其品质一样
		switch (m_pItemData->quality) {
            case ItemQuality_Green:
                m_pLabelName = Label::create();
				if ( m_pLabelName )
				{
					m_pLabelName->setColor(Color3B::GREEN);
					m_pLabelName->setSystemFontSize(20);
					m_pLabelName->setPosition(Point(0,40));
					m_pLabelName->setString(m_pItemData->name);
					addChild(m_pLabelName);
				}
				break;
			case ItemQuality_Blue:
				m_pLabelName = Label::create();
				if ( m_pLabelName )
				{
					m_pLabelName->setColor(Color3B::BLUE);
					m_pLabelName->setSystemFontSize(20);
					m_pLabelName->setPosition(Point(0,40));
					m_pLabelName->setString(m_pItemData->name);
					addChild(m_pLabelName);
				}
				break;
			case ItemQuality_Orange:
				m_pLabelName = Label::create();
				if ( m_pLabelName )
				{
					m_pLabelName->setColor(Color3B::ORANGE);				
					m_pLabelName->setSystemFontSize(20);
					m_pLabelName->setPosition(Point(0,40));
					m_pLabelName->setString(m_pItemData->name);
					addChild(m_pLabelName);
				}
				break;
            default:

                break;
        }
		
		// maybe should manage icon by manager
		if(m_pItemData->drop_art != "")
		{
			vector<string> subStr;
			StringSplit(m_pItemData->drop_art, ";",subStr);
			if ( subStr.size() == 2 )
			{
				vector<string> params;
				StringSplit(subStr[0],",",params);
				if ( params.size() == 2 )
				{
					m_nDropArtID = atoi(params[0].c_str());
					m_sDropArtName = params[1];
				}
				params.clear();
				StringSplit(subStr[1],",",params);
				if ( params.size() == 2 )
				{
					m_nDispArtID = atoi(params[0].c_str());
					m_sDispArtName = params[1];
				}
				
			}
			else
			{
				LOGE("item drop art config error.");
			}

			Effect* pEffect = Effect::createWithDataID(m_nDropArtID,true);
			if ( pEffect )
			{
				pEffect->setName(m_sDropArtName);
				addChild(pEffect);
			}
		}
		else
		{
			string iconPath = ICON_PATH_DROP+m_pItemData->dropicon;
			m_pDropIcon  = ImageView::create(iconPath);
			if (m_pDropIcon)
			{
				m_pDropIcon->setScale(ICON_ITEM_SCALE);
				addChild(m_pDropIcon);
			}
		}


		// 加入闪亮的星
		//m_pStarEffect = CEffect::create();
		//if ( m_pStarEffect )
		//{
		//	m_pStarEffect->setEffectID(1002001);
		//	//m_pStarEffect->setPosition(Point(-10,10));
		//	addChild(m_pStarEffect);

		//	ActionInterval* pAction1 = DelayTime::create(1.6f);
		//	ActionInterval* pAction2 = DelayTime::create(3.0f);
		//	
		//	m_pStarEffect->runAction(RepeatForever::create( Sequence::create(	CallFunc::create(CC_CALLBACK_0(CMapItem::beginBlink,this)),pAction1,
		//												CallFunc::create(CC_CALLBACK_0(CMapItem::stopBlink,this)),pAction2,NULL)));

		//	ActionInterval* pActionS1 = ScaleTo::create(0.6f,2.5f);
		//	ActionInterval* pActionS2 = DelayTime::create(0.4f);
		//	ActionInterval* pActionS3 = ScaleTo::create(0.6f,1.0f);
		//	ActionInterval* pActionS4 = DelayTime::create(3.0f);

		//	m_pStarEffect->runAction(RepeatForever::create( Sequence::create(pActionS1,pActionS2,pActionS3,pActionS4,NULL)));
		//}
	}
}

void CMapItem::beginBlink()
{
	//m_pStarEffect->setCover(false); 
	//m_pStarEffect->pause(false);
}

void CMapItem::stopBlink()
{
	//m_pStarEffect->setCover();
	//m_pStarEffect->pause();
}

void CMapItem::onCover(bool covered)
{
	if ( covered )
	{
		if ( m_pLabelName )
		{
			m_pLabelName->setOpacity(120);
		}
		
		if ( m_pDropIcon )
		{
			m_pDropIcon->setOpacity(120);
		}
	}
	else
	{
		if ( m_pLabelName )
		{
			m_pLabelName->setOpacity(255);
		}

		if ( m_pDropIcon )
		{
			m_pDropIcon->setOpacity(255);
		}
	}
}

void CMapItem::update(float dt)
{
	MapObject::update(dt); 

	if (m_fBornTime + 60 < fNow)
	{
		m_nOwner = 0;
	}
}

bool CMapItem::isSelect(float x,float y)
{
	AffineTransform t = getParentToNodeAffineTransform();
	Point pt = PointApplyAffineTransform(Point(x,y),t);
	Size size_orig = m_pDropIcon->getContentSize();
	Size size = size_orig * ICON_ITEM_SCALE;
	return (Rect(-size.width / 2, -size.height / 2, size.width, size.height).containsPoint(pt));
}

void CPickupItemAction::initWithMapItem(CMapItem* pMapItem)
{
	if(pMapItem)
	{
		m_id = pMapItem->GetId();
		m_cellX = pMapItem->GetCellX();
		m_cellY = pMapItem->GetCellY();
	}
	else
	{
		m_id = 0;
		m_cellX = 0;
		m_cellY = 0;
	}
	m_getTime = getMilliSecond();
}

bool CPickupItemAction::pickUp()
{
	auto dis = Distance(m_cellX, m_cellY, gHero->GetCellX(), gHero->GetCellY());
	const int    range   = 3;     //拾取的视野范围
	const double wait_T  = 300.f; //发送拾取消息的时间间隔
	double  pMilli = getMilliSecond();
	double val = pMilli - m_getTime;
	if(dis <= range)
	{
		if(val != 0 && val < wait_T)
			return false;
		m_getTime = pMilli;
		//CMapItem pMapItem = GetMapItem(m_id);
		pk::C2GS_PickUpItem cmd;
		cmd.id = 0;
		cmd.Send(gNetSocket);
		//gCocosAudio->PlayEffect(13);
		return true;
	}
	return false;
}
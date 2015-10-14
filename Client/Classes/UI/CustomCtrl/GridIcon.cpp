#include "GridIcon.h"
#include "GameScene/GameUILayer.h"
#include "Common/CommonDef.h"
#include "UI/MessageBoxUI.h"
#include "Net/NetDispatcher.h"
#include "CdCtrol.h"

#define path_mask				("assets/ui/common/UnUseAbleMask.png")
#define path_lock				("assets/ui/bag/subscript1.png")

//字体颜色
#define COLOR__NAME               Color3B(0xff, 0xff, 0xff)          //名字颜色
#define COLOR__CNT                Color3B(0x0a, 0xf2, 0x0a)          //数量颜色
#define COLOR__PRECENT            Color3B(0xff, 0xff, 0xff)          //进度颜色


//顺序 铜 银 金 玉 等级值颜色
static Color3B gLevelColor[4] = {Color3B(0xe0, 0xb2, 0x80),Color3B(0xff, 0xff, 0xff),Color3B(0xed, 0xb6, 0x4b),Color3B(0x13, 0xed, 0xb4)};
//描边颜色
#define COLOR__NAME_LINE          Color4B(0x27, 0x13, 0x03, 0xff)    //名字描边
#define COLOR__CNT_LINE           Color4B(0x00, 0x17, 0x01, 0xff)    //数量描边
//顺序 铜 银 金 玉  进度值描边
static Color4B gLinePrecentColor[4] = { Color4B(0x28, 0x12, 0x01, 0xff) ,Color4B(0x00, 0x00, 0x00, 0xff) , Color4B(0x28, 0x12, 0x01, 0xff), Color4B(0x00, 0x17, 0x01, 0xff)};

//顺序 铜 银 金 玉  进度值图片
static const char* gBookBarIcon[4] = {
	"assets/ui/SkyBook/img_tongserongliangtiao.png",
	"assets/ui/SkyBook/img_yinserongliangtiao.png",
	"assets/ui/SkyBook/img_jinserongliangtiao.png",
	"assets/ui/SkyBook/img_yuserongliangtiao.png",
};

enum BookQuality_en
{
	BOOK_TONG_Q = 5,              //铜色
	BOOK_YIN_Q,                   //银色
	BOOK_JIN_Q,                   //金色
	BOOK_YU_Q,                    //玉色
};

CGridIcon::CGridIcon() 
	:m_pItem(NULL)
	,m_GridPos(-1)
	,m_pItemNum(NULL)
	,m_pIcon(NULL)
	,m_pQuality(NULL)
	,m_pLock(NULL)
	,m_pMask(NULL)
	,m_bSetTipsBtnBright(false)
	,m_bCanMove(false)
	,m_clickEventListener(NULL)
	,m_clickEventSelector(NULL)
	,m_bIsQuickcut(false)
	,m_sIconPath("")
	,m_pLevel(nullptr)
	,m_pName(nullptr)
	,m_pLoadingBar(nullptr)
	,m_pPercent(nullptr)
{

}

CGridIcon::~CGridIcon()
{
}

CGridIcon* CGridIcon::create(CItem* pItem, int pos, emGridsType gridsType,bool bCanMove)
{
	CGridIcon* widget = new CGridIcon();
	if(gridsType == emGrids_BagBook)
	{
		if (widget && widget->initBook(pItem,pos,gridsType,bCanMove))
		{
			widget->autorelease();
			return widget;
		}
	}
	else
	{
		if (widget && widget->init(pItem,pos,gridsType,bCanMove))
		{
			widget->autorelease();
			return widget;
		}
	}

	CC_SAFE_DELETE(widget);
	return nullptr;
}

bool CGridIcon::init(CItem* pItem, int pos, emGridsType gridsType,bool bCanMove)
{
	if ( !ImageView::init() )
	{
		return false;
	}

	if(!pItem) return false;

	ignoreContentAdaptWithSize(false);
	setSize(Size(132,132));
	
	m_pItem = pItem;
	m_GridPos = pos;
	m_GridsType = gridsType;
	m_bCanMove = bCanMove;

	updateByContent();

	return true;
}


bool CGridIcon::initBook(CItem* pItem, int pos, emGridsType gridsType,bool bCanMove)
{
	if(!ImageView::init())
		return false;
	if(!pItem) return false;

	ignoreContentAdaptWithSize(false);
	setSize(Size(132,132));

	m_pItem = pItem;
	m_GridPos = pos;
	m_GridsType = gridsType;
	m_bCanMove = bCanMove;

	updateByContent();

	return true;
}

void CGridIcon::updateByContent()
{
	if(m_GridsType == emGrids_BagBook)
	{
		ShowQuality();
		ShowIcon();
		ShowMask();
		ShowNum();
		ShowPrecent();
		ShowPrecentBar();
		ShowLevel();
	}
	else
	{
		ShowQuality();
		ShowIcon();
		ShowMask();
		ShowNum();
		ShowCd();
	}
	setTouchEnabled(true);
	if (m_bCanMove&&m_pItem)
	{
		CDragCtrol* pDrag = CDragCtrol::create(this,m_pItem->getId(),DragSlotType_Item,this,toucheventselector(CGridIcon::clickGridIcon),NULL);
		addChild(pDrag);
	}
	else
	{
		addTouchEventListener(this,toucheventselector(CGridIcon::clickGridIcon));
	}
}

void CGridIcon::ShowLevel(Point _point)
{
	if(!m_pLevel && m_pItem)
	{
		m_pLevel = Text::create();
		m_pLevel->setFontSize(18);

		m_pLevel->setColor(getNameColor(part_level));
		m_pLevel->setPosition(Point(_customSize.width * _point.x, _customSize.height * _point.y));
		addChild(m_pLevel);
	}
	if(m_pLevel && m_pItem)
	m_pLevel->setText(INT_TO_STRING(m_pItem->getScore()));
}

void CGridIcon::ShowName(Point _point)
{
	if(!m_pName && m_pItem)
	{
		m_pName = Text::create();
		m_pName->setFontSize(24);
		m_pName->setColor(getNameColor(part_name));
		m_pName->enableOutline(getLineColor(part_name));
		m_pName->setPosition(Point(_customSize.width * _point.x, _customSize.height * _point.y));
		addChild(m_pName);
	}
	if(m_pLevel && m_pItem)
	m_pLevel->setText(m_pItem->getItemData()->name);
}

void CGridIcon::ShowPrecentBar(Point _point)
{
	if(!m_pLoadingBar && m_pItem)
	{
		m_pLoadingBar = LoadingBar::create(gBookBarIcon[m_pItem->getItemData()->quality - BOOK_TONG_Q]);
		m_pLoadingBar->setPosition(Point(_customSize.width * _point.x, _customSize.height * _point.y));
		addChild(m_pLoadingBar);
	}
	if(m_pLoadingBar && m_pItem)
	m_pLoadingBar->setPercent(m_pItem->getBookPercent());
}

void CGridIcon::ShowPrecent(Point _point)
{
	if(!m_pPercent && m_pItem)
	{
		m_pPercent = Text::create();
		m_pPercent->setFontSize(16);
		m_pPercent->setColor(getNameColor(part_precent));
		m_pPercent->enableOutline(getLineColor(part_precent));
		m_pPercent->setPosition(Point(_customSize.width * _point.x, _customSize.height * _point.y));
		addChild(m_pPercent);
	}
	if(m_pPercent && m_pItem)
	m_pPercent->setText(INT_TO_STRING(m_pItem->getBookPercent()));
}

Color3B CGridIcon::getNameColor(BookPart part)
{
	Color3B color = Color3B::BLACK;
	switch (part)
	{
	case part_num:    //数量
		color = COLOR__CNT;
		break;
	case part_name:   //名字
		color = COLOR__NAME;
		break;
	case part_level:  //等级
		color = gLevelColor[m_pItem->getItemData()->quality - BOOK_TONG_Q];
		break;
	case part_precent: //进度
		color = COLOR__PRECENT;
		break;
	default:
		break;
	}
	return color;
};

Color4B CGridIcon::getLineColor(BookPart part)
{
	Color4B color = Color4B::BLACK;
	switch (part)
	{
	case part_num:    //数量
		color = COLOR__CNT_LINE;
		break;
	case part_name:   //名字
		color = COLOR__NAME_LINE;
		break;
	case part_level:  //等级
		//不存在描边
		break;
	case part_precent: //进度
		color = gLinePrecentColor[m_pItem->getItemData()->quality - BOOK_TONG_Q];
		break;
	default:
		break;
	}
	return color;
}

void CGridIcon::ShowQuality()
{
	string path_img = GetQualityImgPath(ItemQualityType(m_pItem->getItemData()->quality));

	if ( !path_img.empty() )
	{
		if (!m_pQuality)
		{
			m_pQuality = ImageView::create(path_img);
			m_pQuality->setPosition(Point(_customSize.width/2,_customSize.height/2));
			addChild(m_pQuality,part_order_quality);
		}
		else
		{
			m_pQuality->loadTexture(path_img);
		}
	}
	else
	{
		if (m_pQuality)
		{
			m_pQuality->removeFromParentAndCleanup(true);
			m_pQuality = NULL;
		}
	}
}

void CGridIcon::ShowIcon()
{
	m_sIconPath = ICON_PATH_ITEM+m_pItem->getItemData()->icon;
	if ( !m_pIcon )
	{
		m_pIcon = ImageView::create(m_sIconPath);
		m_pIcon->setPosition(Point(_customSize.width/2,_customSize.height/2));
		addChild(m_pIcon,part_order_icon);
	}
	else
	{
		m_pIcon->loadTexture(m_sIconPath);
	}
}

string CGridIcon::getIconPath()
{
	return m_sIconPath;
}

void CGridIcon::ShowMask()
{
	if ( !CheckUseAble() )
	{
		if ( !m_pMask )
		{
			m_pMask = ImageView::create(path_mask);
			m_pMask->setPosition(Point(_customSize.width/2,_customSize.height/2));
			m_pMask->setOpacity(225);
			addChild(m_pMask,part_order_mask);
		}
	}
	else
	{
		if ( m_pMask )
		{
			m_pMask->removeFromParentAndCleanup(true);
			m_pMask=NULL;
		}
	}
}

bool CGridIcon::IfShowNum()
{
	if (m_pItem->getItemData()->overlaycnt > 1 && m_pItem->getCount() > 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CGridIcon::ShowNum()
{
	if (IfShowNum())
	{
		if(!m_pItemNum)
		{
			m_pItemNum = Text::create();
			m_pItemNum->setAnchorPoint(Point(1.0f,0.0f));
			m_pItemNum->setPosition(Point(_customSize.width-5,5.0f));
			addChild(m_pItemNum,part_order_num);
		}
		m_pItemNum->setText(CCString::createWithFormat("%d",m_pItem->getCount())->getCString());
	}
	else
	{
		if (m_pItemNum)
		{
			m_pItemNum->removeFromParentAndCleanup(true);
			m_pItemNum=NULL;
		}
	}
}

void CGridIcon::ShowLock()
{
	if (m_pItem->isBind())
	{
		m_pLock = ImageView::create(path_lock);
		m_pLock->setAnchorPoint(Point(0,0));
		m_pLock->setPosition(Point(5.0f,5.0f));
		m_pLock->setScale(0.75f);
		addChild(m_pLock,part_order_lock);
	}
	else
	{
		if ( m_pLock )
		{
			m_pLock->removeFromParentAndCleanup(true);
			m_pLock = NULL;
		}
	}
}

void CGridIcon::ShowCd()
{
	RemoveCd();
	if (m_pItem->GetCdTime()>0)
	{
		CdCtrol* pCd = CdCtrol::create(m_pItem->GetCdTime()*1000,m_pItem->GetCdTimeTotal()*1000);
		if(pCd)
		{
			addChild(pCd,part_order_cd);
		}
	}
}

void CGridIcon::RemoveCd()
{
	removeChildByTag(Child_Cd_Tag,true);
}

bool CGridIcon::CheckUseAble()
{
	ItemCfg* pCfg = m_pItem->getItemData();

	return true;
	//if( isCareerRight(pCfg->career) && isUseLvRight(pCfg->uselevel) )
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}

void CGridIcon::ShowMaskManual(bool bShow)
{
	if (!m_pMask)
	{
		m_pMask = ImageView::create(path_mask);
		m_pMask->setPosition(Point(_customSize.width/2,_customSize.height/2));
		m_pMask->setOpacity(225);
		addChild(m_pMask,part_order_mask);
	}
	m_pMask->setVisible(bShow);
	SetTipsBtnBright(true);
}

void CGridIcon::clickGridIcon(Ref *pSender, TouchEventType type)
{
	if ( TOUCH_EVENT_ENDED == type )
	{
		if (m_clickEventListener&&m_clickEventSelector)
		{
			if ((m_clickEventListener->*m_clickEventSelector)(this))
			{
				return;
			}
		} 
	}
}
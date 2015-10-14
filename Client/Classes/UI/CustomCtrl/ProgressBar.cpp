#include "ProgressBar.h"
#include "GUI/CCControlExtension/CCScale9Sprite.h"
USING_NS_CC_EXT;

//////////////////////////////////////////////////////////////////////////
ProgerssBar::ProgerssBar() : m_fSpeed(1.0f),
	m_fCursor(0.0f),m_fPercent(0),m_Size(800,30),
	m_pLayerBackGround(nullptr),m_pLayerProgress(nullptr),m_pLoadginBg(nullptr),
	m_pLoadingBar(nullptr),m_pImageCursor(nullptr),m_pText(nullptr)
{

}

ProgerssBar::~ProgerssBar()
{

}

bool ProgerssBar::init()
{
	m_pLayerBackGround = LayerColor::create(Color4B::WHITE);
	m_pLayerProgress = LayerColor::create(Color4B::GREEN);

	m_pLayerBackGround->setPosition(Point::ZERO);
	m_pLayerProgress->setPosition(Point(0,1));

	m_pLayerBackGround->setContentSize(m_Size);
	m_pLayerProgress->setContentSize(Size(0,m_Size.height-2));

	addChild(m_pLayerBackGround);
	addChild(m_pLayerProgress);

	m_pLoadginBg = Scale9Sprite::create();
	if ( m_pLoadginBg )
	{
		m_pLoadginBg->setAnchorPoint(Point::ZERO);
		m_pLoadginBg->setContentSize(m_Size);
		m_pLayerBackGround->addChild(m_pLoadginBg);
	}

	m_pLoadingBar = LoadingBar::create();
	if ( m_pLoadingBar )
	{
		m_pLoadingBar->setAnchorPoint(Point::ZERO);
		m_pLoadingBar->setSize(m_Size-Size(0,2));
		m_pLoadingBar->setScale9Enabled(true);
		m_pLayerProgress->addChild(m_pLoadingBar);
	}

	m_pImageCursor = Sprite::create();
	if ( m_pImageCursor )
	{
		m_pLayerProgress->addChild(m_pImageCursor);
	}

	m_pText = Label::createWithSystemFont("","Arial",22);
	if ( m_pText )
	{
		m_pText->setPosition(Point(m_Size/2));
		m_pLayerProgress->addChild(m_pText);
	}

	scheduleUpdate();

	return true;
}

void ProgerssBar::setTexture(const string& background,const string& progress,const string& cursor /* = "" */)
{
	if ( !background.empty() && m_pLoadginBg )
	{
		dynamic_cast<Scale9Sprite*>(m_pLoadginBg)->initWithFile(background);
		dynamic_cast<Scale9Sprite*>(m_pLoadginBg)->setContentSize(m_Size);
		dynamic_cast<Scale9Sprite*>(m_pLoadginBg)->setAnchorPoint(Point::ZERO);
		dynamic_cast<Scale9Sprite*>(m_pLoadginBg)->setCapInsets(Rect::ZERO);
	}

	if ( !progress.empty() && m_pLoadingBar )
	{
		m_pLoadingBar->loadTexture(progress);
	}

	if ( !cursor.empty() && m_pImageCursor )
	{
		m_pImageCursor->setTexture(cursor);
	}
}

void ProgerssBar::update(float dt)
{
	if ( IsComplete() )
	{
		return ;
	}

	if ( m_fCursor < m_fPercent )
	{
		m_fCursor = MIN(m_fCursor+m_fSpeed,m_fPercent);
		if(m_fCursor >= PRECENT_MAX)
		{
			m_fCursor = PRECENT_MAX;
		}
	}
	float posX = m_fCursor / PRECENT_MAX * m_Size.width;
	m_pLayerProgress->setContentSize(Size(posX,m_Size.height-2));
	m_pLoadingBar->setPercent(m_fCursor);
	if( m_pImageCursor )
	{
		m_pImageCursor->setPositionX(posX);
	}
}

void ProgerssBar::SetSize(Size size)
{
	m_Size = size;
	m_pLayerBackGround->setContentSize(m_Size);
	float posX = m_fCursor / PRECENT_MAX * m_Size.width;
	m_pLayerProgress->setContentSize(Size(posX,m_Size.height-2));
}

void ProgerssBar::SetText(const string& str)
{
	if ( m_pText )
	{
		m_pText->setString(str);
	}
}

void ProgerssBar::Reset()
{
	m_fCursor = 0.0f;
	m_fPercent = 0.0f;
	SetText("");
	m_pLayerBackGround->setContentSize(m_Size);
	m_pLayerProgress->setContentSize(Size(0,m_Size.height-2));
}

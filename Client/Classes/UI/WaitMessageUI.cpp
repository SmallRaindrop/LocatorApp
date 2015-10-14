#include "WaitMessageUI.h"

USING_NS_CC;

#define  TIME_OUT   30               //超时时间(单位秒)
#define  OPACITY_VAR 50              //透明度（0~255）

WaitMessageUI * WaitMessageUI::m_waitMsgPtr = nullptr;

WaitMessageUI::WaitMessageUI()
{
	m_show = false;
	m_timeout = TIME_OUT;
	init();
}

WaitMessageUI::~WaitMessageUI()
{
	releaseFunc();
}

bool WaitMessageUI::init()
{
	if(!Layer::init())
		return false;
	return true;
}

void WaitMessageUI::onEnter()
{
	Layer::onEnter();

	auto size = CCDirector::getInstance()->getVisibleSize();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch * touch, Event * event){
		return true;
	};
	
	listener->onTouchEnded = [&](Touch * touch, Event * event){

	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto layercolor = LayerColor::create(Color4B(0,0,0,OPACITY_VAR));
	addChild(layercolor);

	auto  sprite = Sprite::create("common/wait.png");
	sprite->setScaleY(-1.0f);
	sprite->setPosition(Point(size.width * 0.5f, size.height * 0.5f));
	this->addChild(sprite);
	sprite->runAction(cocos2d::RepeatForever::create(cocos2d::RotateBy::create(0.15f, 180)));
}


void WaitMessageUI::onExit()
{
	Layer::onExit();
}




void WaitMessageUI::setShow( bool _isshow )
{
	this->unscheduleAllSelectors();
	if(_isshow)
	{
		//先检测是否显示
		if(m_show)
		{
			reSetTimeout();
		}
		auto scene = CCDirector::getInstance()->getRunningScene();
		if(scene)
		{
			scene->addChild(this);
			this->schedule(schedule_selector(WaitMessageUI::update), 1);
		}
		m_show = true;
	}
	else
	{
		if(!m_show)
		{
			return ;
		}
		m_show = false;
		this->removeFromParentAndCleanup(true);
	}
}


void  WaitMessageUI::update(float fd)
{
	if(m_timeout)
	{
		m_timeout -= 1;
	}
	else
	{
		this->unscheduleAllSelectors();
		m_show = false;
		this->removeFromParentAndCleanup(false);
	}
}

void WaitMessageUI::reSetTimeout()
{
	m_timeout = TIME_OUT;
}






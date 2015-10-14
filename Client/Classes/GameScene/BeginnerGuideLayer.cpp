#include "BeginnerGuideLayer.h"
#include "Common/CommonDef.h"
#include "GameUILayer.h"
#include "UI/CustomCtrl/TuoYuanAction.h"
#include "Hero.h"
#include "GameScene/BeginnerGuide.h"
#include "UI/CustomCtrl/RichTextEX.h"
#include "UI/CustomCtrl/JoyStick.h"

GuideControlMapping g_GCM[] = {
	{GControlID_TaskMain, IDU_MainUINormal,0, "" },
	{GControlID_TaskMain, IDU_MainUINormal,0, "BtnCopyMap" },
	{GControlID_None, IDU_NONE, 0,"" }
};

BeginnerGuideLayer::BeginnerGuideLayer() : m_pGuideData(NULL)
{

}

BeginnerGuideLayer::~BeginnerGuideLayer()
{

}

bool BeginnerGuideLayer::initWithGuideData(GuideCfg* pData)
{
	if ( !pData || !init() )
	{
		return false;
	}

	m_pGuideData = pData;

	return true;
}

bool BeginnerGuideLayer::getGuideControlRect(GuideControlID controlid,Rect& rect)
{
	if (controlid != 0 && controlid < GControlID_Max )
	{
		if ( g_GCM[controlid].type == 0 )
		{
			return getWidgetRect(g_GCM[controlid].idu,g_GCM[controlid].name,rect);
		}

		if ( g_GCM[controlid].type == 1 )
		{
			return getWidgetRect(g_GCM[controlid].idu,g_GCM[controlid].name,rect);
		}

		if ( g_GCM[controlid].type == 2 )
		{
			return getWidgetRect(g_GCM[controlid].idu,g_GCM[controlid].name,rect);
		}
	}

	return false;
}

bool BeginnerGuideLayer::getWidgetRect(int idu,const string& name,Rect& rect)
{
	GameUI* pUI = gGameUILayer->getActiveUI(idu);
	if ( pUI )
	{
		Widget* pWidget = Helper::seekWidgetByName(pUI->getWidget(),name.c_str());
		if ( pWidget )
		{
			Point pos = pWidget->getWorldPosition();
			if ( pUI->getWidget() )
			{
				pos = pUI->getWidget()->convertToNodeSpace(pos);
			}
			else
			{
				pos = pUI->convertToNodeSpace(pos);
			}
			Size size = pWidget->getContentSize();
			rect.origin = pos;
			rect.size = size;

			return true;
		}
	}

	return false;
}

bool BeginnerGuideLayer::getEquipRect(int dataid,Rect& rect)
{
	CGridIcon* pIcon = gGridsManager->getIconByDataId(emGrids_BagEquip,dataid);
	if ( pIcon )
	{
		Point pos = pIcon->getWorldPosition();
		Size size = pIcon->getContentSize();
		pos = convertToNodeSpace(pos);
		rect.origin = pos;
		rect.size = size;
		return true;
	}

	return false;
}

bool BeginnerGuideLayer::getItemRect(int dataid,Rect& rect)
{
	CGridIcon* pIcon = gGridsManager->getIconByDataId(emGrids_BagEquip,dataid);
	if ( pIcon )
	{
		Point pos = pIcon->getWorldPosition();
		Size size = pIcon->getContentSize();
		pos = convertToNodeSpace(pos);
		rect.origin = pos;
		rect.size = size;
		return true;
	}

	return false;
}

void BeginnerGuideLayer::onComplete()
{
	gHero->GetGuidePtr()->CloseGuide(getGuideData()->id);
}

void BeginnerGuideLayer::onClose()
{

}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

BeginnerGuideMove::BeginnerGuideMove() : m_bFlag(false)
{

}

BeginnerGuideMove::~BeginnerGuideMove()
{
	_eventDispatcher->removeEventListener(_touchListener);
	_touchListener = nullptr;
}

BeginnerGuideMove* BeginnerGuideMove::create(GuideCfg* pData)
{
	BeginnerGuideMove* pRet = new BeginnerGuideMove;
	if ( pRet && pRet->initWithGuideData(pData) )
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);

	return NULL;
}

bool BeginnerGuideMove::initWithGuideData(GuideCfg* pData)
{
	if ( !BeginnerGuideLayer::initWithGuideData(pData) )
	{
		return false;
	}

	// Register Touch Event
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(Layer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Layer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Layer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(Layer::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithFixedPriority(listener,-128);
	_touchListener = listener;

	//创建一个遮罩层
	LayerColor * layer = LayerColor::create(Color4B(0,0,0,150));
	layer->setContentSize(GAME_UI_ORIG_SIZE*5);
	addChild(layer,0,10);

	//创建一个手型精灵用来指导用户点击
	Sprite* hand = Sprite::create("assets/ui/common/guide_hand_move.png");
	hand->setAnchorPoint(Point(1,1));
	hand->setPosition(GAME_UI_ORIG_SIZE.width/2,GAME_UI_ORIG_SIZE.height/2+200);
	addChild(hand,0,11);

	Text* pText = Text::create();
	pText->setFontSize(50);
	pText->setColor(Color3B::WHITE);
	pText->setText(GameString.get(1000)->value);
	pText->setPosition(Point(GAME_UI_ORIG_SIZE.width/2,GAME_UI_ORIG_SIZE.height/2-120));
	addChild(pText,0,12);

	MoveBy* pAction = MoveBy::create(0.6f,Point(300,50));
	FadeOut* pAction1 = FadeOut::create(0.01f);
	FadeIn* pAction2 = FadeIn::create(0.01f);
	DelayTime* pAction3 = DelayTime::create(0.5f);
	hand->runAction(RepeatForever::create(Sequence::create(pAction,pAction3,pAction1,pAction->reverse(),pAction2,NULL)));

	return true;
}

bool BeginnerGuideMove::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	m_OriginPoint = pTouch->getLocation();
	pEvent->stopPropagation();
	return true;
}

void BeginnerGuideMove::onTouchMoved(Touch *pTouch, Event *pEvent)
{
	Point pos = pTouch->getLocation();
	if( m_OriginPoint.getDistance(pos) > 60 )
	{
		getChildByTag(10)->setVisible(false);
		getChildByTag(11)->setVisible(false);
		getChildByTag(12)->setVisible(false);
		m_bFlag = true;
	}

	pEvent->stopPropagation();
}

void BeginnerGuideMove::onTouchEnded(Touch *touch, Event *unused_event)
{
	if ( m_bFlag )
	{
		m_bFlag = false;
		onComplete();
	}
}

void BeginnerGuideMove::onTouchCancelled(Touch *touch, Event *unused_event)
{

}

//当新手引导退出的时候在onExit()中处理一些事情
void BeginnerGuideMove::onExit()
{
	Layer::onExit();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

BeginnerGuideForce* BeginnerGuideForce::create(GuideCfg* pData)
{
	BeginnerGuideForce* pRet = new BeginnerGuideForce;
	if ( pRet && pRet->initWithGuideData(pData) )
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);

	return NULL;
}

BeginnerGuideForce::BeginnerGuideForce()
{

}

BeginnerGuideForce::~BeginnerGuideForce()
{
	_eventDispatcher->removeEventListener(_touchListener);
	_touchListener = nullptr;
}

bool BeginnerGuideForce::initWithGuideData(GuideCfg* pData)
{
	if ( !BeginnerGuideLayer::initWithGuideData(pData) )
	{
		return false;
	}

	Rect rect;
	if( !getGuideControlRect(GuideControlID(pData->controlid),rect) )
	{
		return false;
	}

	// Register Touch Event
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(Layer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Layer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Layer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(Layer::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithFixedPriority(listener,-128);
	_touchListener = listener;

	//创建一个裁剪节点
	m_pClippingNode = ClippingNode::create();
	addChild(m_pClippingNode);
	//创建一个遮罩层
	LayerColor * layer = LayerColor::create(Color4B(0,0,0,150));
	layer->setContentSize(GAME_UI_ORIG_SIZE*5);
	//设置一些属性
	m_pClippingNode->addChild(layer);
	m_pClippingNode->setInverted(true);
	m_pClippingNode->setAlphaThreshold(0);

	//
	ImageView* pImage = ImageView::create("assets/ui/common/null.png");
	pImage->setScale9Enabled(true);
	Rect rc(30,30,40,40);
	pImage->setCapInsets(rc);
	pImage->setSize(rect.size+Size(30,30));
	pImage->setPosition(rect.origin);
	addChild(pImage,0,10);

	ImageView* stencil = ImageView::create("assets/ui/common/button4_0.png");
	stencil->setScale9Enabled(true);
	stencil->setSize(rect.size);
	stencil->setPosition(rect.origin);
	stencil->setParent(m_pClippingNode);
	m_pClippingNode->setStencil(stencil);

	Point pos = stencil->getPosition();
	float ra = MIN(pImage->getSize().width/2,pImage->getSize().height/2)*pImage->getScale();

	//创建一个手型精灵用来指导用户点击
	Sprite* hand = Sprite::create("assets/ui/common/closeSel_2nd.png");
	hand->setPosition(pos+Point(ra,0));
	hand->setAnchorPoint(Point(0.5f,0.5f));
	addChild(hand,0,11);

	CircleBy* pAction = CircleBy::create(1.4f,ra,ra,pos,(float)(2*PI),0.0f);
	hand->runAction(RepeatForever::create(Sequence::create(pAction,DelayTime::create(0.5f),NULL)));

	return true;
}

void BeginnerGuideForce::update(float delta)
{

}

bool BeginnerGuideForce::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	Point point = pTouch->getLocation();
	//获取当前的模板
	Node * stencil = m_pClippingNode->getStencil();
	Rect rect = stencil->getBoundingBox();
	//判断手指点击的位置是否为模板的位置
	if(rect.containsPoint(m_pClippingNode->convertToNodeSpace(point)))
	{
		onComplete();
	}
	else
	{
		pEvent->stopPropagation();
	}

	return true;
}

void BeginnerGuideForce::onExit()
{
	Layer::onExit();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

BeginnerGuideCommon::BeginnerGuideCommon() : m_pImage(NULL)
{

}

BeginnerGuideCommon::~BeginnerGuideCommon()
{
	_eventDispatcher->removeEventListener(_touchListener);
	_touchListener = nullptr;
}

BeginnerGuideCommon* BeginnerGuideCommon::create(GuideCfg* pData)
{
	BeginnerGuideCommon* pRet = new BeginnerGuideCommon;
	if ( pRet && pRet->initWithGuideData(pData) )
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);

	return NULL;
}

bool BeginnerGuideCommon::initWithGuideData(GuideCfg* pData)
{
	if ( !BeginnerGuideLayer::initWithGuideData(pData) )
	{
		return false;
	}

	Rect rect;
	if( !getGuideControlRect(GuideControlID(pData->controlid),rect) )
	{
		return false;
	}

	// Register Touch Event
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(Layer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Layer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Layer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(Layer::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithFixedPriority(listener,-128);
	_touchListener = listener;

	//
	m_pImage = ImageView::create("assets/ui/common/guide_frame.png");
	m_pImage->setScale9Enabled(true);
	Rect rc(30,30,40,40);
	m_pImage->setCapInsets(rc);
	m_pImage->setSize(rect.size+Size(30,30));
	m_pImage->setPosition(rect.origin);
	addChild(m_pImage);

	Point pos = m_pImage->getPosition();
	float ra = MIN(m_pImage->getSize().width/2,m_pImage->getSize().height/2)*m_pImage->getScale();
	//创建一个手型精灵用来指导用户点击
	Sprite* hand = Sprite::create("assets/ui/common/guide_hand.png");
	hand->setPosition(pos+Point(ra,0));
	hand->setAnchorPoint(Point(0.1f,0.9f));
	addChild(hand);

	CircleBy* pAction = CircleBy::create(1.4f,ra,ra,pos,(float)(2*PI),0.0f);
	hand->runAction(RepeatForever::create(Sequence::create(pAction,DelayTime::create(0.5f),NULL)));

	return true;
}

bool BeginnerGuideCommon::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	Point point = pTouch->getLocation();
	Rect rect = m_pImage->getBoundingBox();
	//判断手指点击的位置是否为模板的位置
	if(rect.containsPoint(convertToNodeSpace(point)))
	{
		onComplete();
	}
	
	return true;
}

void BeginnerGuideCommon::onExit()
{
	Layer::onExit();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
BeginnerGuideSkill::BeginnerGuideSkill()
{

}

BeginnerGuideSkill::~BeginnerGuideSkill()
{
	_eventDispatcher->removeEventListener(_touchListener);
	_touchListener = nullptr;
}

BeginnerGuideSkill* BeginnerGuideSkill::create(GuideCfg* pData)
{
	BeginnerGuideSkill* pRet = new BeginnerGuideSkill;
	if ( pRet && pRet->initWithGuideData(pData) )
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);

	return NULL;
}

bool BeginnerGuideSkill::initWithGuideData(GuideCfg* pData)
{
	CSkill* pSkill = gHero->GetLastestSkill();
	if ( !pSkill )
	{
		return false;
	}

	m_pSkillData = pSkill->GetData();

	if ( !BeginnerGuideLayer::initWithGuideData(pData) )
	{
		return false;
	}

	// Register Touch Event
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(Layer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Layer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Layer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(Layer::onTouchCancelled, this);

	_eventDispatcher->addEventListenerWithFixedPriority(listener,-128);
	_touchListener = listener;

	//创建一个遮罩层
	LayerColor * layer = LayerColor::create(Color4B(0,0,0,220));
	layer->setContentSize(GAME_UI_ORIG_SIZE*5);
	addChild(layer);

	m_pSkillIcon = ImageView::create(pSkill->GetData()->icon);
	//pSkillIconBg->setScale9Enabled(true);
	//Rect rc(30,30,40,40);
	//pSkillIconBg->setCapInsets(rc);
	//pSkillIconBg->setSize(rect.size);
	m_pSkillIcon->setPosition(Point(GAME_UI_ORIG_SIZE.width/2,GAME_UI_ORIG_SIZE.height/2+150));
	addChild(m_pSkillIcon);

	ImageView* pSkillIconBg = ImageView::create("assets/ui/mainui/skill_frame.png");
	//pSkillIconBg->setScale9Enabled(true);
	//Rect rc(30,30,40,40);
	//pSkillIconBg->setCapInsets(rc);
	//pSkillIconBg->setSize(rect.size);
	pSkillIconBg->setPosition(Point(GAME_UI_ORIG_SIZE.width/2,GAME_UI_ORIG_SIZE.height/2+150));
	addChild(pSkillIconBg,0,11);

	//
	ImageView* pImage = ImageView::create("assets/ui/common/guide_frame.png");
	pImage->setScale9Enabled(true);
	Rect rc(30,30,40,40);
	pImage->setCapInsets(rc);
	pImage->setSize(Size(pSkillIconBg->getSize().width+50,pSkillIconBg->getSize().height+50));
	pImage->setPosition(pSkillIconBg->getPosition());
	addChild(pImage,1,13);

	Point pos = pImage->getPosition();
	float ra = MIN(pImage->getSize().width/2,pImage->getSize().height/2)*pImage->getScale();
	//创建一个手型精灵用来指导用户点击
	Sprite* hand = Sprite::create("assets/ui/common/guide_hand.png");
	hand->setPosition(pos+Point(ra,0));
	hand->setAnchorPoint(Point(0.1f,0.9f));
	addChild(hand,1,14);


	CircleBy* pAction = CircleBy::create(1.4f,ra,ra,pos,(float)(2*PI),0.0f);
	hand->runAction(RepeatForever::create(Sequence::create(pAction,DelayTime::create(0.5f),NULL)));

	// 获得新技能
	Text* pText = Text::create();
	pText->setFontSize(40);
	pText->setColor(Color3B::WHITE);
	pText->setText(GameString.get(307)->value);
	pText->setPosition(Point(GAME_UI_ORIG_SIZE.width/2,560));
	addChild(pText,0,12);
	// 技能名称
	Text* pText1 = Text::create();
	pText1->setFontSize(80);
	pText1->setColor(Color3B::WHITE);
	pText1->setText(pSkill->GetData()->name);
	pText1->setPosition(Point(GAME_UI_ORIG_SIZE.width/2,400));
	addChild(pText1);

	// 技能描述
	Text* pText2 = Text::create();
	RichTextEx* pRichEx = RichTextEx::create();
	pRichEx->ignoreContentAdaptWithSize(false);
	pRichEx->setSize(Size(800,0));
	pRichEx->SetFontSize(40);
	pRichEx->setColor(Color3B::WHITE);
	pRichEx->ParseAndLayout(pSkill->GetData()->desc);
	pRichEx->formatText();
	pText2->setSize(Size(800,pRichEx->getVirtualRendererSize().height));
	pText2->setPosition(Point(GAME_UI_ORIG_SIZE.width/2,320));
	pRichEx->setPosition(Point(0, pText2->getSize().height-pRichEx->getVirtualRendererSize().height / 2));
	pText2->addChild(pRichEx);
	addChild(pText2);

	return true;
}

bool BeginnerGuideSkill::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	Point point = pTouch->getLocation();
	//获取当前的模板
	Rect rect = m_pSkillIcon->getBoundingBox();
	//判断手指点击的位置是否为模板的位置
	if(rect.containsPoint(convertToNodeSpace(point)))
	{
		getChildByTag(11)->setVisible(false);
		getChildByTag(12)->setVisible(false);
		getChildByTag(13)->setVisible(false);
		getChildByTag(14)->setVisible(false);

		if ( m_pSkillData->passitive != 0 )
		{
			onComplete();
			return true;
		}
	}
	else
	{
		pEvent->stopPropagation();
	}

	return true;
}

void BeginnerGuideSkill::onTouchMoved(Touch *pTouch, Event *pEvent)
{

}

void BeginnerGuideSkill::onComplete()
{
	BeginnerGuideLayer::onComplete();
}

void BeginnerGuideSkill::onExit()
{
	Layer::onExit();
} 
#include "LoadingUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/RootScene.h"

USING_NS_CC;

#define     PRECENT_MAX    100.f

LoadingUI::LoadingUI()
	:m_fCursor(0.f),m_pWidget(NULL)
	,m_showtips("")
	,m_lable(nullptr)
	,m_tipslable(nullptr)
	,m_loadingbar(nullptr)
	,m_bActive(false)
	,m_fPercent(0.0f)
	,m_fd(4.f)
	,_loadEndEventListener(nullptr)
	,_loadEndEventCallBack(nullptr)
{

}

LoadingUI::~LoadingUI()
{
	ClearLoadEndEvent();
	removeFromParent();
}

void LoadingUI::initWidget()
{
	assert(m_pWidget==NULL);
	m_pWidget = GUIReader::getInstance()->widgetFromJsonFile(JSONFILE_LOADUI);
	m_loadingbar = dynamic_cast<ui::LoadingBar*>(m_pWidget->getChildByName("ProgressBar"));
	m_loadingbar->setPercent(m_fCursor);

	m_lable = dynamic_cast<ui::Text*>(m_pWidget->getChildByName("Label_precent"));
	char str[10];
	memset(str,'0',sizeof(str));
	sprintf(str, "%d%%", (int)m_fCursor);
	m_lable->setText(str);
	m_lable->setFontSize(20);
	m_lable->enableOutline(Color4B(0x4b,0x05,0x9a,0xff),2);

	m_tipslable = dynamic_cast<ui::Text*>(m_pWidget->getChildByName("Label_curstr"));
	m_tipslable->setText(m_showtips);
	m_tipslable->enableOutline(Color4B::BLACK,2);

	//²Ã¼ô²ã
	auto cpLayout = dynamic_cast<Layout*>(m_pWidget->getChildByName("Panel_light"));
	cpLayout->setClippingEnabled(true);

	m_light = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWidget,"Image_light"));

	addChild(m_pWidget);

	gRootScene->getCurrScene()->addChild(this,9999);
	scheduleUpdate();
}


void LoadingUI::Show(LoadType _type)
{
	if ( IsActive() )
	{
		return ;
	}

	initWidget();

	switch (_type)
	{
	case UPDATE_TYPE:
		m_fCursor = 0.f;
		m_showtips = STR_LOADING_UPDATE;
		break;
	case LOADRES_TYPE:
		m_fCursor = 0.f;
		m_showtips = STR_LOADING_ADDRES;
		break;
	default:
		break;
	}
	m_loadingbar->setPercent(m_fCursor);
	m_lable->setText(FORMAT_TO_STRING("%d%%", (int)m_fCursor));
	m_tipslable->setText(m_showtips);
	m_bActive = true;
}


//void LoadingUI::Show(LoadType _type, int idu, ...)
//{
//	if(idu > 0)
//	{
//		va_list l;
//		va_start(l, idu);
//		for (int i = 0; i < idu; i++)
//		{
//			auto pIDU = va_arg(l, int);
//			m_iduV.push_back(pIDU);
//		}
//		va_end(l);
//	}
//	Show(_type);
//}

void LoadingUI::update(float dt)
{
	if ( !IsActive() )
	{
		return ;
	}
	
	if ( m_fCursor < m_fPercent )
	{
		m_fCursor = MIN(m_fCursor+m_fd,m_fPercent);
		if(m_fCursor >= PRECENT_MAX)
		{
			m_fCursor = PRECENT_MAX;
			this->runAction(cocos2d::Sequence::createWithTwoActions(
				DelayTime::create(0.1f),
				CallFunc::create([=](){
					Close();
			})
				));
		}
	}

	float pPosX = 87 + 955 * m_fCursor/100.f;
	if(m_light)
	m_light->setPositionX(pPosX);
	m_loadingbar->setPercent(m_fCursor);

	char str[10];
	memset(str,'0',sizeof(str));
	sprintf(str, "%d%%", (int)m_fCursor);
	m_lable->setText(str);
}

void LoadingUI::addLoadEndEvent(Ref* pListener, LoadEnd_Event loadEnd_event)
{
	_loadEndEventListener = pListener;
	_loadEndEventCallBack = loadEnd_event;
}

void LoadingUI::ClearLoadEndEvent()
{
	_loadEndEventListener = nullptr;
	_loadEndEventCallBack = nullptr;
}

void LoadingUI::LoadEndEvent()
{
	if (_loadEndEventListener&&_loadEndEventCallBack)
	{
		(_loadEndEventListener->*_loadEndEventCallBack)();
	}
	ClearLoadEndEvent();
}


void LoadingUI::Close()
{
	if ( m_pWidget )
	{
		m_pWidget->removeFromParent();
		m_pWidget = NULL;
	}
	m_fCursor = 0.0f;
	m_fPercent = 0.0f;

	gHero->ShowCopyEnterEffect();

	LoadEndEvent();

	removeFromParent();

	m_bActive = false;
}




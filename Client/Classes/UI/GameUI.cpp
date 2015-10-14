#include "GameUI.h"
#include "cocostudio/CCSGUIReader.h"
using namespace cocostudio;

GameUI::UI_JSON_MAPPING GameUI::s_ui_json_mapping;

void GameUI::registerUIjson(int idu,string json)
{
	UI_JSON_MAPPING::iterator itr = s_ui_json_mapping.find(idu);
	if ( itr == s_ui_json_mapping.end() )
	{
		s_ui_json_mapping[idu] = json;
	}
}

string GameUI::getUIjson(int idu)
{
	UI_JSON_MAPPING::iterator itr = s_ui_json_mapping.find(idu);
	if ( itr != s_ui_json_mapping.end() )
	{
		return itr->second;
	}

	return "";
}

void GameUI::CenterWidget(Widget* pWidget)
{
	Size vSize = gDirector->getVisibleSize();
	Size wSize = pWidget->getSize();
	float fScale = MIN(vSize.width / wSize.width, vSize.height / wSize.height);
	pWidget->setScale(fScale);

	Point pos((vSize.width - wSize.width * fScale) / 2, vSize.height - wSize.height * fScale);
	pos += gDirector->getVisibleOrigin();
	pWidget->setPosition(pos);
}

void GameUI::RightWidget(Widget* pWidget)
{
	Size vSize = gDirector->getVisibleSize();
	Size wSize = pWidget->getSize();
	float fScale = pWidget->getScale();

	Point pos((vSize.width - wSize.width * fScale),0);
	pos += gDirector->getVisibleOrigin();
	pWidget->setPosition(pos);
}

void GameUI::LeftWidget(Widget* pWidget)
{
	Size vSize = gDirector->getVisibleSize();
	Size wSize = pWidget->getSize();
	float fScale = MIN(vSize.width / wSize.width, vSize.height / wSize.height);
	pWidget->setScale(fScale);

	Point pos = gDirector->getVisibleOrigin();
	pWidget->setPosition(pos);
}

GameUI::GameUI(int idu,const std::string& strJsonFile) : m_IDU(idu),m_pWidget(NULL),m_nState(GUIS_NONE),m_pModel(NULL)
{
	registerUIjson(idu,strJsonFile);
}

GameUI::~GameUI()
{
	for (size_t i=0; i<m_effects.size(); ++i)
	{
		CC_SAFE_RELEASE(m_effects[i]);
	}
	m_effects.clear();
}

bool GameUI::init()
{
	string json = getUIjson(m_IDU);
	if ( !json.empty() )
	{
		m_pWidget = GUIReader::getInstance()->widgetFromJsonFile(json.c_str());
		if ( !m_pWidget )
		{
			return false;
		}
		addChild(m_pWidget);

		m_pModel = Layout::create();
		m_pModel->setSize(gDirector->getVisibleSize());
		m_pModel->_setLocalZOrder(-1);
		addChild(m_pModel);

		unDoModel();
	}

	if ( !onInit() )
	{
		return false;
	}

	Size vSize = gDirector->getVisibleSize();
	Size wSize = m_pWidget->getSize();
	float fScale = MIN(vSize.width / wSize.width, vSize.height / wSize.height);
	//m_pWidget->setScale(fScale);

	Size virSize = vSize / fScale;
	Point pos(virSize.width - wSize.width, virSize.height - wSize.height);
	pos += gDirector->getVisibleOrigin();
	//m_pWidget->setPosition(pos / 2);

	return true;
}

void GameUI::doModel()
{
	m_pModel->setTouchEnabled(true);
}

void GameUI::unDoModel()
{
	m_pModel->setTouchEnabled(false);
}

bool GameUI::isModal()
{
	return m_pModel->isTouchEnabled();
}

bool GameUI::onInit()
{
	return true;
}

void GameUI::update(float dt)
{
	for (EffectList::iterator itr = m_effects.begin(); itr!=m_effects.end(); )
	{
		Effect* pEffect = (*itr);
		if (!pEffect->getParent())
		{
			itr=m_effects.erase(itr);
			CC_SAFE_RELEASE(pEffect);
		}
		//else if(!pEffect->isLoop() && pEffect->isDone())
		//{
		//	itr=m_effects.erase(itr);
		//	pEffect->removeFromParentAndCleanup(true);
		//	CC_SAFE_RELEASE(pEffect);
		//}
		else
		{
			pEffect->update(dt);
			++itr;
		}
	}
}

#include "CopyMapUIContendFor.h"

CCopyMapContendFor::CCopyMapContendFor()
	:CCopyMapUI(IDU_CopyUIContendFor,JsonFile_CopyContendFor)
	,m_pPlayerScore(nullptr)
	,m_pMonsterScore(nullptr)
{
	for (int i=0; i<Max_ContendFor_Num; ++i)
	{
		m_pPlaceTitle[i] = nullptr;
		m_pPlaceStatus[i] = nullptr;
	}
}
CCopyMapContendFor::~CCopyMapContendFor()
{

}

bool CCopyMapContendFor::onInit()
{
	do 
	{
		m_pWaveIdx = (Text*)Helper::seekWidgetByName(m_pWidget,"WaveTitle");
		m_pPlayerScore = (Text*)Helper::seekWidgetByName(m_pWidget,"PlayerScore");
		m_pMonsterScore = (Text*)Helper::seekWidgetByName(m_pWidget,"MonsterScore");
		BREAK_IF(!(m_pPlayerScore&&m_pMonsterScore));		
		for (int i=0; i<Max_ContendFor_Num; ++i)
		{
			m_pPlaceTitle[i] = (Text*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("PlaceTitle_%d",i)->getCString());
			m_pPlaceStatus[i] = (Text*)Helper::seekWidgetByName(m_pWidget,CCString::createWithFormat("PlaceStatu_%d",i)->getCString());
			BREAK_IF(!(m_pPlaceTitle[i]&&m_pPlaceStatus[i]));	
			m_pPlaceTitle[i]->setEnabled(false);
			m_pPlaceStatus[i]->setEnabled(false);
		}
		m_pCountSecondsTitle = (Text*)Helper::seekWidgetByName(m_pWidget,"CountdownTitle");
		m_pCountSeconds = (Text*)Helper::seekWidgetByName(m_pWidget,"Countdown");
		BREAK_IF(!(m_pCountSeconds&&m_pCountSecondsTitle));
		m_pCountSecondsTitle->setText(STR_Copy_Title_CountFight);
		return true;
	} while (0);
	return false;
}

void CCopyMapContendFor::BeforeActive()
{
	m_pWaveIdx->setEnabled(false);
	m_pPlayerScore->setEnabled(false);
	m_pMonsterScore->setEnabled(false);
}

void CCopyMapContendFor::UpdateContendForInfo(pk::GS2C_ContentionInfo* value)
{
	m_pPlayerScore->setText(CCString::createWithFormat("%d",value->playerPoint)->getCString());
	m_pMonsterScore->setText(CCString::createWithFormat("%d",value->monsterPoint)->getCString());
	for (int i=0; i<Max_ContendFor_Num; ++i)
	{
		if (i<value->contentionPoints.size())
		{
			m_pPlaceTitle[i]->setEnabled(true);
			m_pPlaceStatus[i]->setEnabled(true);
			Process process(value->contentionPoints[i]);
			m_pPlaceTitle[i]->setColor(process.GetStatusColor());
			m_pPlaceStatus[i]->setColor(process.GetStatusColor());
			m_pPlaceTitle[i]->setText(CCString::createWithFormat("%c%s",'A'+i,STR_Copy_Title_ContendFor_Dot)->getCString());
			m_pPlaceStatus[i]->setText(process.GetStatusText());
			Text* pScore = (Text*)gMap->getChildByTag(value->contentionPoints[i].id);
			if (!pScore)
			{
				pScore = Text::create();
				pScore->setFontSize(32);
				gMap->getTerrain()->cell2World(process.x,process.y);
				pScore->setPosition(Point(process.x,process.y));
				pScore->setTag(process.id);
				gMap->addChild(pScore);
			} 
			pScore->setColor(process.GetValueColor());
			pScore->setText(CCString::createWithFormat("%d%%",process.processValue)->getCString());
		} 
		else
		{
			m_pPlaceTitle[i]->setEnabled(false);
			m_pPlaceStatus[i]->setEnabled(false);
		}
	}
}

void CCopyMapContendFor::OnActive()
{
	m_pWaveIdx->setEnabled(true);
	m_pPlayerScore->setEnabled(true);
	m_pMonsterScore->setEnabled(true);
}

void CCopyMapContendFor::SetWaveIdx(int nWaveIdx)
{
	m_nWaveIdx = nWaveIdx;
	if (m_pWaveIdx)
	{
		m_pWaveIdx->setText(CCString::createWithFormat("%s",STR_Copy_Title_ContendFor_Wave,nWaveIdx)->getCString());
	}
}
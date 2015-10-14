#include "CopyMapUIDef.h"
#include "GameScene/MessageCenter.h"

CCopyMapUIDef::CCopyMapUIDef()
	:CCopyMapUI(IDU_CopyUIDef,JsonFile_CopyDefUI)
{

}

CCopyMapUIDef::~CCopyMapUIDef()
{

}

bool CCopyMapUIDef::onInit()
{
	do 
	{
		m_pWaveIdx = (Text*)Helper::seekWidgetByName(m_pWidget,"WaveNum");
		m_pCountSeconds = (Text*)Helper::seekWidgetByName(m_pWidget,"Countdown");
		m_pCountSecondsTitle = (Text*)Helper::seekWidgetByName(m_pWidget,"CountdownTitle");
		BREAK_IF(!(m_pWaveIdx&&m_pCountSeconds&&m_pCountSecondsTitle));
		m_pCountSeconds->setEnabled(false);
		m_pCountSecondsTitle->setText(STR_Copy_Title_CountFight);
		return true;
	} while (0);
	return false;
}

void CCopyMapUIDef::updateMonsterWave(pk::GS2C_MonsterSpawnRemind* value)
{
	CCopyMapUI::updateMonsterWave(value);

	if(value->waveIndex>1)
	{
		gMessageCenter->SystemMessage(1002);
	}
}
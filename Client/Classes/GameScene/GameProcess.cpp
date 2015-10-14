#include "GameProcess.h"
#include "GameDataManager.h"
#include "GameExpression.h"
#include "GameUILayer.h"
#include "UI/DramaUi.h"
#include "Hero.h"
#include "BeginnerGuide.h"

GameProcess::GameProcess() : m_nStepID(0),m_pGameProcData(nullptr),m_nEventID(GameProcEvent_None)
{
	SetStepID(1);
}

GameProcess::~GameProcess()
{

}

bool GameProcess::Reload()
{
	if ( m_pGameProcData && m_pGameProcData->id == m_nStepID )
	{
		return true;
	}

	m_pGameProcData = GameProcData.get(m_nStepID);
	if ( !m_pGameProcData )
	{
		LOGE("game proc data[%d] not found.",m_nStepID);
		return false;
	}

	return true;
}

bool GameProcess::Execute(GameProcCfg* pData)
{
	if ( !pData )
	{
		return false;
	}

	vector<string> exp_list;
	StringUtil::StringSplit(pData->trigger_condition,";",exp_list);

	for ( size_t i = 0;i<exp_list.size();++i )
	{
		if ( !get_exp_value(exp_list[i]) )
		{
			return false;
		}
	}
	
	bool ret = false;

	switch (pData->func_type)
	{
	case GameProcFuncType_Succ: ret = true; break;
	case GameProcFuncType_Animation: ret = true; break;
	case GameProcFuncType_Drama:
		{
			vector<string> params;
			if ( 2 != StringUtil::StringSplit(pData->params,",",params) )
			{
				LOGE("GameProcess::Execute params[%s] error.",pData->params.c_str());
				break;
			}
			if( gGameUILayer->isActive(IDU_Drama) )
			{
				ret = true;
				break;
			}
			DramaUI* pDrama = (DramaUI*)gGameUILayer->open(IDU_Drama);
			if ( pDrama )
			{
				pDrama->showDramaByParam(atoi(params[0].c_str()),atoi(params[1].c_str()));

				ret = true;
			}
		}
		break;
	case GameProcFuncType_Guide: 
		{
			int guideid = atoi(pData->params.c_str());
			if ( guideid == 0 )
			{
				LOGE("GameProcess::Execute params[%s] guideid is 0.",pData->params.c_str());
			}
			gHero->GetGuidePtr()->OpenGuide(guideid);
			ret = true;
		}
		break;
	case GameProcFuncType_SystemMsg: 
		{

		}
		break;
	default:
		break;
	}

	if ( pData->type == GameProcType_Main )
	{
		if ( ret )
		{
			SetStepID(pData->succ > 0 ? pData->succ : m_nStepID + 1);
		}
		else
		{
			SetStepID(pData->fail > 0 ? pData->fail : m_nStepID);
		}
	}
	return true;
}

GameProcEvent GameProcess::GetEvent()
{
	GameProcEvent event = GameProcEvent_None;
	if ( !m_dequeEvents.empty() )
	{
		event = GameProcEvent(m_dequeEvents.front());
		m_dequeEvents.pop_front();
	}
	return event;
}

bool GameProcess::TranslateEvent(GameProcEvent event)
{
	class GameProcIterator : public ForeachIterator<GameProcCfg>
	{
	public:
		bool execute(GameProcCfg* item)
		{
			if ( item->type == GameProcType_Branch )
			{
				gGameProcess->Execute(item);
			}
			
			return true;
		}
	};

	GameProcIterator iter;
	GameProcData.foreach(iter);

	return true;
}

void GameProcess::Update(float dt)
{
	// 执行主线历程
	Execute(m_pGameProcData);

	// 处理事件，执行支线进程
	m_nEventID = GetEvent();
	while ( m_nEventID !=  GameProcEvent_None )
	{
		if( !TranslateEvent(m_nEventID) )
		{
			ClearEvent();
			break;
		}

		m_nEventID = GetEvent();
	}
}
#include "BeginnerGuide.h"
#include "GameDataManager.h"
#include "GameUILayer.h"
#include "Hero.h"
#include "TaskMgr.h"
#include "GameVariable.h"

BeginnerGuide::BeginnerGuide()
{

}

BeginnerGuide::~BeginnerGuide()
{
	Exit();
}

bool BeginnerGuide::IsGuideActive(int dataid)
{
	for ( size_t i = 0;i<m_listGuideUI.size();++i )
	{
		BeginnerGuideLayer* pLayer = m_listGuideUI[i];
		if ( pLayer && pLayer->getGuideData()->id == dataid )
		{
			return true;
		}
	}

	return false;
}

void BeginnerGuide::OpenGuide(int dataid)
{
	GuideCfg* pData = GuideData.get(dataid);
	if ( !pData )
	{
		LOGE("BeginnerGuide::open guide dataid[%d] not found.",dataid);
		return ;
	}

	OpenGuide(pData);
}

void BeginnerGuide::OpenGuide(GuideCfg* pData)
{
	if ( !pData )
	{
		return ;
	}

	// 不允许重复开启
	if ( IsGuideActive(pData->id) )
	{
		return ;
	}

	BeginnerGuideLayer* pLayer = nullptr;
	switch (pData->mode)
	{
	case GuideMode_Common: pLayer = BeginnerGuideCommon::create(pData); break;
	case GuideMode_Force: pLayer = BeginnerGuideForce::create(pData); break;
	case GuideMode_Move: pLayer = BeginnerGuideMove::create(pData); break;
	case GuideMode_Skill: pLayer = BeginnerGuideSkill::create(pData); break;
	default: break;
	}

	if ( pLayer )
	{
		// 是否需要关闭所有其他UI界面
		if ( pData->clearui )
		{
			gGameUILayer->closeOtherUIs();
		}

		gGameUILayer->addChild(pLayer,99999);
		pLayer->retain();
		m_listGuideUI.push_back(pLayer);
	}
}

void BeginnerGuide::CloseGuide(int dataid)
{
	for ( vector<BeginnerGuideLayer*>::iterator itr = m_listGuideUI.begin();itr != m_listGuideUI.end();++itr )
	{
		BeginnerGuideLayer* pLayer = *itr;
		if ( pLayer && pLayer->getGuideData()->id == dataid )
		{
			pLayer->onClose();
			pLayer->removeFromParent();
			pLayer->release();
			m_listGuideUI.erase(itr);
			return ;
		}
	}
}

void BeginnerGuide::CloseGuide()
{
	for ( vector<BeginnerGuideLayer*>::iterator itr = m_listGuideUI.begin();itr != m_listGuideUI.end();++itr )
	{
		BeginnerGuideLayer* pLayer = *itr;
		if ( pLayer )
		{
			pLayer->onClose();
			pLayer->removeFromParent();
			pLayer->release();
		}
	}

	m_listGuideUI.clear();
}

void BeginnerGuide::Initialize()
{
	
}

void BeginnerGuide::Exit()
{
	CloseGuide();
}

void BeginnerGuide::Update(float dt)
{
	for ( size_t i = 0;i<m_listGuideUI.size();++i )
	{
		BeginnerGuideLayer* pLayer = m_listGuideUI[i];
		if ( pLayer )
		{
			pLayer->update(dt);
		}
	}
}
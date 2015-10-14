#include "IndicatorLayer.h"
#include "RoleFighter.h"


CIndicatorLayer::CIndicatorLayer(RoleFighter* pRole) 
	:m_pRole(pRole)
{

}

CIndicatorLayer::~CIndicatorLayer()
{
	m_pRole = nullptr;
	m_pDynamicIndicators.clear();
	m_pStaticIndicators.clear();
}

CIndicatorLayer* CIndicatorLayer::createWithRole(RoleFighter* pRole)
{
	CIndicatorLayer* ret = new CIndicatorLayer(pRole);
	if ( ret && ret->Init() )
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_RELEASE(ret);

	return NULL;
}

bool CIndicatorLayer::Init()
{
	if ( !m_pRole )
	{
		return false;
	}
	return true;
}

void CIndicatorLayer::SetDynamicIndicators(pk::GS2C_GUIDE_LIST* value)
{
	size_t nDataSize = value->guides.size();
	size_t nUISize = m_pDynamicIndicators.size();
	size_t nMaxSize = nUISize>nDataSize?nUISize:nDataSize;


	for (size_t i=0; i<nMaxSize; ++i)
	{
		if (i<nUISize&&i>=nDataSize)
		{
			m_pDynamicIndicators[i].ui->removeFromParent();
		}
		else
		{
			int cx = value->guides[i].x;
			int cy = value->guides[i].y;
			gMap->getTerrain()->cell2World(cx,cy);
			Point targetPos(cx,cy);

			if(i>= nUISize)
			{
				Widget* pIndicator = gCtrlAllocator->LoadCtrl("Indicator");
				if(!pIndicator) return;
				addChild(pIndicator);

				m_pDynamicIndicators.push_back(Indicator(pIndicator,targetPos));
			}
			else
			{
				m_pDynamicIndicators[i].targetPos = targetPos;
			}
		}
	}
	m_pDynamicIndicators.resize(value->guides.size());
	UpdateDynamicIndicators();
}

void CIndicatorLayer::AddStaticIndicator(int cx, int cy, int offsetX, int offsetY)
{
	gMap->getTerrain()->cell2World(cx,cy);
	Point targetPos(cx,cy);
	Widget* pIndicator = gCtrlAllocator->LoadCtrl("Indicator");
	if(!pIndicator) return;
	addChild(pIndicator);
	m_pStaticIndicators.push_back(Indicator(pIndicator,targetPos,offsetX,offsetY));
	UpdateStaticIndicators();
}

void CIndicatorLayer::RemoveDynamicIndicators()
{
	for (size_t i=0; i<m_pDynamicIndicators.size(); ++i)
	{
		m_pDynamicIndicators[i].ui->removeFromParent();
	}
	m_pDynamicIndicators.clear();
}

void CIndicatorLayer::RemoveStaticIndicators()
{
	for (size_t i=0; i<m_pStaticIndicators.size(); ++i)
	{
		m_pStaticIndicators[i].ui->removeFromParent();
	}
	m_pStaticIndicators.clear();
}

void CIndicatorLayer::RemoveIndicators()
{
	RemoveDynamicIndicators();
	RemoveStaticIndicators();
}

void CIndicatorLayer::UpdateDynamicIndicators()
{
	for (size_t i=0; i<m_pDynamicIndicators.size(); ++i)
	{
		int cx = (int)m_pDynamicIndicators[i].targetPos.x;
		int cy = (int)m_pDynamicIndicators[i].targetPos.y;
		gMap->getTerrain()->world2Cell(cx,cy);
		Point PosTarget(cx,cy);
		Point PosHero(gHero->GetCellX(),gHero->GetCellY());
		if (PosTarget.getDistance(PosHero) <= 3)
		{
			m_pDynamicIndicators[i].ui->setVisible(false);
			continue;
		}
		else
		{
			m_pDynamicIndicators[i].ui->setVisible(true);
			float fRadian = (m_pDynamicIndicators[i].targetPos - m_pRole->getPosition()).getAngle();
			float fDegree = CC_RADIANS_TO_DEGREES(fRadian);
			m_pDynamicIndicators[i].ui->setRotation(-fDegree);
			m_pDynamicIndicators[i].ui->setPosition(Point(200*cos(fRadian),200*sin(fRadian)));	
		}
	}
}

void CIndicatorLayer::UpdateStaticIndicators()
{
	for (size_t i=0; i<m_pStaticIndicators.size(); ++i)
	{
		int cx = (int)m_pStaticIndicators[i].targetPos.x;
		int cy = (int)m_pStaticIndicators[i].targetPos.y;
		int offsetX = m_pStaticIndicators[i].offsetX;
		int offsetY = m_pStaticIndicators[i].offsetY;
		gMap->getTerrain()->world2Cell(cx,cy);
		Rect rect(cx,cy,offsetX,offsetY);
		if (rect.containsPoint(Point(gHero->GetCellX(),gHero->GetCellY())))
		{
			RemoveStaticIndicators();
			return;
		}

		float fRadian = (m_pStaticIndicators[i].targetPos - m_pRole->getPosition()).getAngle();
		float fDegree = CC_RADIANS_TO_DEGREES(fRadian);
		m_pStaticIndicators[i].ui->setRotation(-fDegree);
		m_pStaticIndicators[i].ui->setPosition(Point(200*cos(fRadian),200*sin(fRadian)));	
	}
}

void CIndicatorLayer::UpdateIndicators()
{
	setPosition(m_pRole->getPosition());
	UpdateDynamicIndicators();
	UpdateStaticIndicators();
}
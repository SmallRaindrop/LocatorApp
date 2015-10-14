#include "ItemGrid.h"

CItemGridArray::CItemGridArray():
	m_size(0),m_gridType(emGrids_None),m_operateEventSelector(NULL),m_operateEventListener(NULL),m_blimit(true)
{

}

CItemGridArray::CItemGridArray(int size):
	m_size(0),m_gridType(emGrids_None),m_operateEventSelector(NULL),m_operateEventListener(NULL)
{
	m_Grids.resize(size);
	for ( size_t i = 0;i<(size_t)size;++i )
	{
		m_Grids[i] = new CItemGrid;
	}
	m_size = size;
}

CItemGridArray::~CItemGridArray()
{
	clear();
}

void CItemGridArray::clear()
{
	for ( size_t i = 0;i<m_Grids.size();++i )
	{
		m_Grids[i]->ReleaseItem();
		CC_SAFE_DELETE(m_Grids[i]);
	}
	m_Grids.clear();
	m_size = 0;
}

void CItemGridArray::ClearData()
{
	for ( size_t i = 0;i<m_Grids.size();++i )
	{
		//m_Grids[i]->ReleaseItem();
		CC_SAFE_DELETE(m_Grids[i]);
	}
	m_Grids.clear();
	init(m_gridType, m_size);
	ActiveAllGrid();
}

void CItemGridArray::init(emGridsType type, int size)
{
	m_gridType = type;
	m_Grids.resize(size);
	for ( size_t i = 0;i<(size_t)size;++i )
	{
		m_Grids[i] = new CItemGrid;
	}
	m_size = size;
}

void CItemGridArray::init(emGridsType type, bool _limit /* = true */)
{
	m_gridType = type;
	m_size = 0;
	m_blimit = _limit;
}

void CItemGridArray::initGrids(vector<pk::BagItem>& itemVec,int activeCount)
{
	if(!m_blimit)
	{
		for ( size_t i = 0;i<(size_t)activeCount && i< itemVec.size();++i )
		{
			CItemGrid* pItemGrid = new CItemGrid;
			pItemGrid->SetActive(true);
			CItem* pItem = CItem::Create(&itemVec[i]);
			if(pItem)
			{
				pItemGrid->SetItem(pItem);
				m_Grids.push_back(pItemGrid);
				m_size++;
			}
			else
			{
				delete pItemGrid;
			}
		}
	}
	else
	{
		for ( size_t i = 0;i<(size_t)activeCount&&i<m_Grids.size();++i )
		{
			m_Grids[i]->SetActive(true);
			if (i<itemVec.size())
			{
				CItem* pItem = CItem::Create(&itemVec[i]);
				if (pItem)
				{
					m_Grids[itemVec[i].index]->SetItem(pItem);
				}
			}
		}
	}
}

CItemGrid* CItemGridArray::GetItemGrid(int pos)
{
	if( pos>=0 && pos<(int)m_Grids.size() )
	{
		return m_Grids[pos];
	}

	return NULL;
}

int CItemGridArray::ActiveOneLineItemGrids()
{
	int pos = GetFirstNeedActivePos();

	for (int i=pos; i<pos+4; i++)
	{
		CItemGrid* pGrid = GetItemGrid(i);
		if ( pGrid )
		{
			pGrid->SetActive(true);
		}		
	}
	return pos;
}

void CItemGridArray::ActiveAllGrid()
{
	for (int i=0; i<m_size; ++i)
	{
		m_Grids[i]->SetActive(true);
	}
}

CItem* CItemGridArray::GetItemByPos(int pos)
{
	CItemGrid* pGrid = GetItemGrid(pos);
	if ( pGrid )
	{
		return pGrid->GetItem();
	}

	return NULL;
}

CItem* CItemGridArray::GetItemByID(int64 itemID)
{
	for (int i=0; i<m_size; ++i)
	{
		CItem* pItem = m_Grids[i]->GetItem();
		if (pItem && (pItem->getId() == itemID))
		{
			return pItem;
		}
	}
	return NULL;
}

CItem* CItemGridArray::GetItemByDataID(int dataID)
{
	for (int i=0; i<m_size; ++i)
	{
		CItem* pItem = m_Grids[i]->GetItem();
		if (pItem && (pItem->getDataID() == dataID))
		{
			return pItem;
		}
	}
	return NULL;
}

int CItemGridArray::GetItemNum(int dataID)
{
	int itemSum = 0;
	for (int i=0; i<m_size; ++i)
	{
		CItem* pItem = m_Grids[i]->GetItem();
		if (pItem && (pItem->getDataID() == dataID))
		{
			itemSum += pItem->getCount();
		}
	}
	return itemSum;
}

void CItemGridArray::InsertItem(int pos,CItem* pItem)
{
	if(!m_blimit)
	{
		PushBackItem(pItem);
	}
	else
	{
		CItemGrid* pGrid = GetItemGrid(pos);
		if ( pGrid && pGrid->IsActive())
		{
			pGrid->SetItem(pItem);
			if (m_operateEventListener && m_operateEventSelector)
			{
				(m_operateEventListener->*m_operateEventSelector)(pos,Grid_Operate_Insert);
			}
		}
	}

}

void CItemGridArray::PushBackItem(CItem* pItem)
{
	CItemGrid* pItemGrid = new CItemGrid;
	pItemGrid->SetActive(true);
	pItemGrid->SetItem(pItem);
	m_Grids.push_back(pItemGrid);
	m_size++;
	if (m_operateEventListener && m_operateEventSelector)
	{
		(m_operateEventListener->*m_operateEventSelector)(m_size,Grid_Operate_Insert);
	}
}

void CItemGridArray::addItemToList(CItemGrid* itemgrid)
{
	if(itemgrid)
	m_Grids.push_back(itemgrid);
}

CItem* CItemGridArray::RemoveItem(int pos)
{
	CItemGrid* pGrid = GetItemGrid(pos);
	if ( pGrid )
	{
		CItem* pItem = pGrid->GetItem();
		pGrid->SetItem(NULL);
		if (m_operateEventListener && m_operateEventSelector)
		{
			(m_operateEventListener->*m_operateEventSelector)(pos,Grid_Operate_Remove);
		}
		return pItem;
	}
	return NULL;
}

void CItemGridArray::DeleteItem(int pos)
{
	if(!m_blimit)
	{
		int idx = 0;
		for (auto iter = m_Grids.begin(); iter!= m_Grids.end();iter++)
		{
			if(idx == pos)
			{
				if((*iter))
				(*iter)->ReleaseItem();
				m_Grids.erase(iter);
				m_size -= 1;
				break;
			}
		}
	}
	else
	{
		CItemGrid* pGrid = GetItemGrid(pos);
		if ( pGrid )
		{
			pGrid->ReleaseItem();
		}
	}

}

void CItemGridArray::DeleteAllItems()
{
	for ( size_t i = 0;i<m_Grids.size();++i )
	{
		CItemGrid* pGrid = m_Grids[i];
		if ( pGrid )
		{
			pGrid->ReleaseItem();
		}
	}
}

int	CItemGridArray::CountEmpty()
{
	int count = 0;
	for ( size_t i = 0;i<m_Grids.size();++i )
	{
		CItemGrid* pGrid = m_Grids[i];
		if ( pGrid && pGrid->IsEmpty() && pGrid->IsActive() )
		{
			++count;
		}
	}

	return count;
}

int	CItemGridArray::CountItem()
{
	int count = 0;
	for ( size_t i = 0;i<m_Grids.size();++i )
	{
		CItemGrid* pGrid = m_Grids[i];
		if ( pGrid && !pGrid->IsEmpty() )
		{
			++count;
		}
	}

	return count;
}

int	CItemGridArray::CountActive()
{
	int count = 0;
	for ( size_t i = 0;i<m_Grids.size();++i )
	{
		CItemGrid* pGrid = m_Grids[i];
		if ( pGrid && pGrid->IsActive() )
		{
			++count;
		}
	}

	return count;
}

int	CItemGridArray::CountNoBind()
{
	int count = 0;
	for ( size_t i = 0;i<m_Grids.size();++i )
	{
		CItem* pItem = m_Grids[i]->GetItem();
		if ( pItem && (!pItem->isBind()))
		{
			++count;
		}
	}

	return count;
}

int	CItemGridArray::CountNewAdd()
{
	int count = 0;
	for ( size_t i = 0;i<m_Grids.size();++i )
	{
		CItem* pItem = m_Grids[i]->GetItem();
		if ( pItem && pItem->IsNewAdd())
		{
			++count;
		}
	}

	return count;
}


bool CItemGridArray::IsFull()
{
	return CountEmpty() == 0;
}

int	CItemGridArray::GetFirstEmptyPos()
{
	for ( size_t i = 0;i<m_Grids.size();++i )
	{
		CItemGrid* pGrid = m_Grids[i];
		if ( pGrid && pGrid->IsEmpty() && pGrid->IsActive())
		{
			return i;
		}
	}

	return -1;
}

int CItemGridArray::GetFirstNeedActivePos()
{
	for ( size_t i = 0;i<m_Grids.size();++i )
	{
		CItemGrid* pGrid = m_Grids[i];
		if ( pGrid && !pGrid->IsActive())
		{
			return i;
		}
	}
	return -1;
}

void CItemGridArray::SwitchItem(int pos1,int pos2)
{
	CItemGrid* pGrid1 = GetItemGrid(pos1);
	CItemGrid* pGrid2 = GetItemGrid(pos2);
	SwitchItem(pGrid1,pGrid2);
}

void CItemGridArray::SwitchItem(CItemGrid* pGrid1,CItemGrid* pGrid2)
{
	if ( pGrid1 && pGrid2 )
	{
		CItem* pItem = pGrid1->GetItem();
		pGrid1->SetItem(pGrid2->GetItem());
		pGrid2->SetItem(pItem);
	}
}

void CItemGridArray::SetNewAdd(int pageIndex,int pageNum,bool bNewAdd)
{
	for (int i=pageIndex*pageNum; i<(pageIndex+1)*pageNum; ++i)
	{
		CItem* pItem = m_Grids[i]->GetItem();
		if ( pItem )
		{
			pItem->setNewAdd(bNewAdd);
		}
	}
}

void CItemGridArray::SetItemCdTime(int cdType, float cdTime)
{
	for ( size_t i = 0;i<m_Grids.size();++i )
	{
		CItem* pItem = m_Grids[i]->GetItem();
		if ( pItem )
		{
			pItem->SetCdTime(cdTime);
		}
	}
}

void CItemGridArray::updateItemCd(float dt)
{
	for ( size_t i = 0;i<m_Grids.size();++i )
	{
		CItemGrid* pGrid = m_Grids[i];
		if ( pGrid && pGrid->GetItem())
		{
			pGrid->GetItem()->updateCd(dt);
		}
	}
}
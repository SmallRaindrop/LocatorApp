#include "GridsManager.h"
#include "GameDataManager.h"

CGridsManager::CGridsManager()
{
	initialize();
}

CGridsManager::~CGridsManager()
{
	release();
}

void CGridsManager::update(float dt)
{
	pGridsData[emGrids_BagZaWu]->updateItemCd(dt);
}

bool CGridsManager::initialize()
{
	//data
	for (int i=0; i<emGrids_Count; ++i)
	{
		pGridsData[i] = new CItemGridArray;
	}

	pGridsData[emGrids_BagEquip]->init(emGrids_BagEquip,BAG_SIZE_EQUIP);
	pGridsData[emGrids_BagEquip]->ActiveAllGrid();
	pGridsData[emGrids_BagZaWu]->init(emGrids_BagZaWu,false);
	pGridsData[emGrids_BagZaWu]->ActiveAllGrid();
	pGridsData[emGrids_BagMaterial]->init(emGrids_BagMaterial,false);
	pGridsData[emGrids_BagMaterial]->ActiveAllGrid();
	pGridsData[emGrids_BagTuZi]->init(emGrids_BagTuZi, false);
	pGridsData[emGrids_BagTuZi]->ActiveAllGrid();
	pGridsData[emGrids_BagBook]->init(emGrids_BagBook, false);
	pGridsData[emGrids_BagBook]->ActiveAllGrid();

	pGridsData[emGrids_Role]->init(emGrids_Role,GRIDS_SIZE_ROLE);
	pGridsData[emGrids_Role]->ActiveAllGrid();

	pGridsData[emGrids_StrengthMaterial]->init(emGrids_StrengthMaterial,0);
	pGridsData[emGrids_TaskAward]->init(emGrids_TaskAward, GRIDS_SIZE_TASK);
	pGridsData[emGrids_TaskAward]->ActiveAllGrid();
	pGridsData[emGrids_CopyCheckout]->init(emGrids_CopyCheckout, false);
	//ui
	for (int i=0; i<emGrids_Count; ++i)
	{
		for (int j=0; j<MAX_PAGE_SIZE; ++j)
		{
			pGridsUI[i][j] = NULL;
		}
		pScrollUI[i] = nullptr;
	}
	return true;
}

void CGridsManager::release()
{
	for (int i=0; i<emGrids_Count; ++i)
	{
		CC_SAFE_DELETE(pGridsData[i]);
		pScrollUI[i] = nullptr;
		for (int j=0; j<MAX_PAGE_SIZE; ++j)
		{
			pGridsUI[i][j] = NULL;
		}
	}
}

//-------------------------------------------------仅用于data的接口-start-------------------------------------------------------//

CItem* CGridsManager::getGirdItem(emGridsType type,int pos)
{
	CItemGridArray* pData = getGridsData(type);

	if (pData)
	{
		return pData->GetItemByPos(pos);
	}
	else
	{
		return NULL;
	}
}

CItem*	CGridsManager::findItemInGrids(emGridsType type,int64 itemID)
{
	CItemGridArray* pData = getGridsData(type);
	if(!pData) return NULL;

	return pData->GetItemByID(itemID);
}

int	CGridsManager::getItemCountByDataID(emGridsType type,int dataID)
{
	CItemGridArray* pData = getGridsData(type);
	if(!pData) return 0;
	CItem* pItem = pData->GetItemByDataID(dataID);
	if(!pItem) return 0;

	return pItem->getCount();
}

CItem* CGridsManager::findItemByDataID(emGridsType type, int dataID)
{
	CItemGridArray* pData = getGridsData(type);
	if(!pData) return NULL;

	return pData->GetItemByDataID(dataID);
}

CItem* CGridsManager::findItemByDataID(int dataid)
{
	ItemCfg* itemdata = ItemData.get(dataid);
	if(itemdata)
	{
		return findItemByDataID((emGridsType)itemdata->type, dataid);
	}
	return nullptr;
}

int CGridsManager::countItems(emGridsType type)
{
	CItemGridArray* pData = getGridsData(type);
	return pData->CountItem();
}

int CGridsManager::countAtive(emGridsType type)
{
	CItemGridArray* pData = getGridsData(type);
	return pData->CountActive();
}

int CGridsManager::countEmpty(emGridsType type)
{
	CItemGridArray* pData = getGridsData(type);
	return pData->CountEmpty();
}

int CGridsManager::countNewAdd(emGridsType type)
{
	CItemGridArray* pData = getGridsData(type);
	return pData->CountNewAdd();
}

void CGridsManager::SetNewAdd(emGridsType type,int pageIndex,int pageNum,bool bNewAdd)
{
	CItemGridArray* pData = getGridsData(type);
	pData->SetNewAdd(pageIndex,pageNum,bNewAdd);
}

void CGridsManager::PushBackItem(emGridsType type,CItem* pItem)
{
	CItemGridArray* pData = getGridsData(type);
	if (pData)
	{
		pData->PushBackItem(pItem);
	}
}

int CGridsManager::GetFirstEmptyPos(emGridsType type)
{
	CItemGridArray* pData = getGridsData(type);
	if (pData)
	{
		return pData->GetFirstEmptyPos();
	}
	else
	{
		return -1;
	}
}

int	CGridsManager::getItemCntByDataID(emGridsType type, int dataID)
{
	CItemGridArray* pData = getGridsData(type);
	if(!pData) return 0;

	return pData->GetItemNum(dataID);
}

void CGridsManager::addOperateEvent(emGridsType type,Ref* pSender,Grid_OperateEvent event)
{
	CItemGridArray* pData = getGridsData(type);
	return pData->addOperateEvent(pSender,event);
}

void CGridsManager::clearData(emGridsType type)
{
	CItemGridArray* pData = getGridsData(type);
	if (pData)
	{
		return pData->clear();
	}
}

//-------------------------------------------------仅用于data的接口-end-------------------------------------------------------//

//-------------------------------------------------仅作用于ui的接口-start-------------------------------------------------------//

CGridArrayUI* CGridsManager::getGridsUI(emGridsType type, int pos)
{
	if (type >= emGrids_Count || !pGridsUI[type][0])
	{
		return NULL;
	}

	int page = pos/pGridsUI[type][0]->getCapacity();;
	if (page >= MAX_PAGE_SIZE)
	{
		return NULL;
	}
	else
	{
		return pGridsUI[type][page];
	}
}

void CGridsManager::attachUI(CGridArrayUI* pUI,emGridsType type,int index)
{
	if (type < emGrids_Count && index < MAX_PAGE_SIZE)
	{
		pGridsUI[type][index] = pUI;
	}
}

void CGridsManager::detachUI(emGridsType type)
{
	if (type < emGrids_Count)
	{
		for (int j=0; j<MAX_PAGE_SIZE; ++j)
		{
			pGridsUI[type][j] = NULL;
		}
	}
}

CGridIcon* CGridsManager::getIconByDataId(emGridsType type, int dataID)
{
	CItem* pItem = findItemByDataID(type,dataID);
	if (pItem)
	{
		return getIcon(type,pItem->getIndex());
	} 
	else
	{
		return NULL;
	}
}

CGridIcon* CGridsManager::getIconByItemId(emGridsType type, int64 itemID)
{
	CItem* pItem = findItemInGrids(type,itemID);
	if (pItem)
	{
		return getIcon(type,pItem->getIndex());
	} 
	else
	{
		return NULL;
	}
}

CGridIcon*	CGridsManager::getIcon(emGridsType type, int pos)
{
	CGridArrayUI* pUI = getGridsUI(type,pos);
	if (pUI)
	{
		return pUI->getIcon(pos);
	}
	return NULL;
}

Widget*	CGridsManager::getIconBk(emGridsType type, int pos)
{
	CGridArrayUI* pUI = getGridsUI(type,pos);
	if (pUI)
	{
		return pUI->GetIconBk(pos);
	}
	return NULL;
}

void CGridsManager::UpdateIconMask(emGridsType type)
{
	for (int i=0; i<MAX_PAGE_SIZE; i++)
	{
		CGridArrayUI* pUI = getGridsUIByIndex(type,i);
		if (pUI)
		{
			pUI->UpdateIconMask();
		}
	}
}

void CGridsManager::ShowMaskManual(emGridsType type,bool bShow,ItemCfg* pMaskItemCfg)
{
	for (int i=0; i<MAX_PAGE_SIZE; i++)
	{
		CGridArrayUI* pUI = getGridsUIByIndex(type,i);
		if(pUI)
		{
			pUI->ShowMaskManual(bShow,pMaskItemCfg);
		}
	}
}


void CGridsManager::insertItemAtGrids(emGridsType type,int pos,int index_from, int index_to)
{
	CItemGridArray* pData = getGridsData(type);
	if(!pData) return;
	for (int i= index_from,j=pos; i<index_to; ++i,++j)
	{
		CItem* pItem = pData->GetItemByPos(i);
		if (pItem)
		{
			CGridArrayUI* pUI = getGridsUI(type,j);
			if (pUI)
			{
				pUI->insertGridUI(j,pItem,type);
			}
		}
	}
}

void CGridsManager::removeAllGridsUIs(emGridsType type)
{
	for (int i=0; i<MAX_PAGE_SIZE; i++)
	{
		CGridArrayUI* pUI = getGridsUIByIndex(type,i);
		if(pUI)
		{
			pUI->removeAllGridUIs();
		}
	}
}

void CGridsManager::ShowCd(emGridsType type)
{
	for (int i=0; i<MAX_PAGE_SIZE; i++)
	{
		CGridArrayUI* pUI = getGridsUIByIndex(type,i);
		if(pUI)
		{
			pUI->ShowCd();
		}
	}
}

void CGridsManager::RemoveCd(emGridsType type)
{
	for (int i=0; i<MAX_PAGE_SIZE; i++)
	{
		CGridArrayUI* pUI = getGridsUIByIndex(type,i);
		if(pUI)
		{
			pUI->RemoveCd();
		}
	}
}

void CGridsManager::AddIconClickEvent(emGridsType type, Ref* pSender, IconClickEvent event)
{
	for (int i=0; i<MAX_PAGE_SIZE; i++)
	{
		CGridArrayUI* pUI = getGridsUIByIndex(type,i);
		if(pUI)
		{
			pUI->AddIconClickEvent(pSender,event);
		}
	}
}

void CGridsManager::clearUI()
{
	for (int i=0; i<emGrids_Count; ++i)
	{
		for (int j=0; j<MAX_PAGE_SIZE; ++j)
		{
			pGridsUI[i][j] = NULL;
		}
	}
}

//-------------------------------------------------仅作用于ui的接口-end-------------------------------------------------------//

//-------------------------------------------------作用于data和ui的接口-start-------------------------------------------------------//

void CGridsManager::ActiveOneLineGrids(emGridsType type)
{
	CItemGridArray* pData = getGridsData(type);
	if (pData)
	{
		int pos = pData->ActiveOneLineItemGrids();
		CGridArrayUI* pUI = getGridsUI(type,pos);
		if (pUI)
		{
			pUI->ActiveOneLineUI(pos);
		}
	}
}

void CGridsManager::resetGrids(emGridsType type,vector<pk::BagItem>& itemVec,int activeCount)
{
	removeAllGrids(type);
	CItemGridArray* pData = getGridsData(type);
	if(!pData) return;
	pData->initGrids(itemVec,activeCount);


	for (int i=0; i<MAX_PAGE_SIZE; i++)
	{
		CGridArrayUI* pUI = getGridsUIByIndex(type,i);
		if (pUI)
		{
			pUI->reset();
		}
		ScrollGrids_cl* pScroll = pScrollUI[i];
		if(pScroll)
			pScroll->reset();
	}
}

void CGridsManager::insertGrid(emGridsType type,int pos,CItem* pItem,bool bRealInsert)
{
	CItemGridArray* pData = getGridsData(type);
	pData->InsertItem(pos,pItem);
	if(bRealInsert)
	{
		pItem->setIndex(pos);
	}
	CGridArrayUI* pUI = getGridsUI(type,pos);
	if (pUI)
	{
		pUI->insertGridUI(pos,pItem,type);
	}
	ScrollGrids_cl* pSui = pScrollUI[type];
	if(pSui)
	{
		pSui->addItemByIndex(pos);
	}
	if(type == emGrids_BagEquip)
	{
		ScrollGrids_cl* pSuiR = pScrollUI[emGrids_BagEquipRole];
		if(pSuiR) pSuiR->addItemByIndex(pos);
	}
}

void CGridsManager::insertGrid(emGridsType type,int pos,int dataId,int num)
{
	ItemInfo info;
	info.count = num;
	info.dataId = dataId;
	CItem* pItem = CItem::Create(info);
	if ( !pItem )
	{
		return ;
	}

	CItemGridArray* pData = getGridsData(type);
	pData->InsertItem(pos,pItem);
	CGridArrayUI* pUI = getGridsUI(type,pos);
	if (pUI)
	{
		pUI->insertGridUI(pos,pItem,type);
	}
	ScrollGrids_cl* pSui = pScrollUI[type];
	if(pSui)
	{
		pSui->addItemByIndex(pos);
	}
	if(type == emGrids_BagEquip)
	{
		ScrollGrids_cl* pSuiR = pScrollUI[emGrids_BagEquipRole];
		if(pSuiR) pSuiR->addItemByIndex(pos);
	}
}

void CGridsManager::insertGrid(emGridsType type,int pos,int dataId,int num,bool binded)
{
	ItemInfo info;
	info.count = num;
	info.dataId = dataId;
	info.isBind = binded;
	CItem* pItem = CItem::Create(info);

	CItemGridArray* pData = getGridsData(type);
	pData->InsertItem(pos,pItem);
	CGridArrayUI* pUI = getGridsUI(type,pos);
	if (pUI)
	{
		pUI->insertGridUI(pos,pItem,type);
	}
	ScrollGrids_cl* pSui = pScrollUI[type];
	if(pSui)
	{
		pSui->addItemByIndex(pos);
	}
	if(type == emGrids_BagEquip)
	{
		ScrollGrids_cl* pSuiR = pScrollUI[emGrids_BagEquipRole];
		if(pSuiR) pSuiR->addItemByIndex(pos);
	}
}

void CGridsManager::PushBackItem(emGridsType type,CItem* pItem,int gridUIPos)
{
	CItemGridArray* pData = getGridsData(type);
	if(!pData)
	{
		pItem->release();
	}
	pData->PushBackItem(pItem);

	ScrollGrids_cl* pScroll = pScrollUI[type];
	if(pScroll)
	{
		pScroll->addItemByIndex(gridUIPos);
	}
	if(type == emGrids_BagEquip)
	{
		ScrollGrids_cl* pSuiR = pScrollUI[emGrids_BagEquipRole];
		if(pSuiR) pSuiR->addItemByIndex(gridUIPos);
	}

	CGridArrayUI* pUI = getGridsUI(type,gridUIPos);
	if (pUI)
	{
		pUI->insertGridUI(gridUIPos,pItem,type);
	}
	else
	{
		pItem->release();
	}
}

CItem* CGridsManager::removeGrid(emGridsType type,int pos)
{
	CItemGridArray* pData = getGridsData(type);
	if(!pData) return NULL;
	CItem* pItem = pData->RemoveItem(pos);
	if (pItem)
	{
		CGridArrayUI* pUI = getGridsUI(type,pos);
		if (pUI)
		{
			pUI->removeGridUI(pos);
		}
		ScrollGrids_cl* pScroll = pScrollUI[type];
		if(pScroll)
		{
			pScroll->removeItemByIndex(pos);
		}
		if(type == emGrids_BagEquip)
		{
			ScrollGrids_cl* pSuiR = pScrollUI[emGrids_BagEquipRole];
			if(pSuiR) pSuiR->removeItemByIndex(pos);
		}
	}
	return pItem;
}

void CGridsManager::move(emGridsType type_from, int pos_from, emGridsType type_to, int pos_to)
{
	CItem* pItem = removeGrid(type_from,pos_from);
	if ( pItem )
	{
		insertGrid(type_to,pos_to,pItem,true);
	}
}

void CGridsManager::deleteGrid(emGridsType type,int pos)
{
	CItemGridArray* pData = getGridsData(type);
	if(!pData) return;
	pData->DeleteItem(pos);

	CGridArrayUI* pUI = getGridsUI(type,pos);
	if (pUI)
	{
		pUI->removeGridUI(pos);
	}

	ScrollGrids_cl * psui = pScrollUI[type];
	if(psui)
		psui->removeItemByIndex(pos);
}

void CGridsManager::removeAllGrids(emGridsType type)
{
	CItemGridArray* pData = getGridsData(type);
	if(!pData) return;
	pData->DeleteAllItems();


	for (int i=0; i<MAX_PAGE_SIZE; i++)
	{
		CGridArrayUI* pUI = getGridsUIByIndex(type,i);
		if(pUI)
		{
			pUI->removeAllGridUIs();
		}
	}
}

void CGridsManager::deleteAllGrids(emGridsType type)
{
	CItemGridArray* pData = getGridsData(type);
	if(!pData) return;
	pData->clear();

	for (int i=0; i<MAX_PAGE_SIZE; i++)
	{
		CGridArrayUI* pUI = getGridsUIByIndex(type,i);
		if(pUI)
		{
			pUI->removeAllGridUIs();
		}
	}
}

void CGridsManager::newGridCnt(emGridsType type,int pos, int nNewCnt)
{
	CItemGridArray* pData = getGridsData(type);
	if(!pData) return;

	CItem* pItem = pData->GetItemByPos(pos);
	if(pItem)
	{
		pItem->setCount(nNewCnt);
		CGridArrayUI* pUI = getGridsUI(type,pos);
		if (pUI)
		{
			CGridIcon* pIcon = pUI->getIcon(pos);
			if (pIcon)
			{
				pIcon->ShowNum();
			}	
		}
	}
}

void CGridsManager::ShowCd(emGridsType type,int cdType,float cdTime)
{
	CItemGridArray* pData = getGridsData(type);
	if (pData)
	{
		pData->SetItemCdTime(cdType,cdTime);
	}
	for (int i=0; i<MAX_PAGE_SIZE; i++)
	{
		CGridArrayUI* pUI = getGridsUIByIndex(type,i);
		if(pUI)
		{
			pUI->ShowCd(cdType,cdTime);
		}
	}
}

//-------------------------------------------------作用于data和ui的接口-end-------------------------------------------------------//

void CGridsManager::createMailGrids(emGridsType mapType, emGridsType srcType)
{
	CItemGridArray* pGridsDes = getGridsData(mapType);
	CItemGridArray* pGridsSrc = getGridsData(srcType);
	if (!pGridsDes || !pGridsSrc)
	{
		return;
	}

	for (int i=0; i<pGridsSrc->getSize(); ++i)
	{
		/*过滤空格*/
		CItem* pItem = pGridsSrc->GetItemByPos(i);
		if (!pItem)
		{
			continue;
		}

		/*过滤绑定类型*/
		if (pItem->isBind())
		{
			continue;
		}
		else
		{
			pItem->retain();
			pGridsDes->PushBackItem(pItem);
		}
	}
}

void CGridsManager::createFurnaceGrids(emGridsType mapType, emGridsType srcType)
{
	CItemGridArray* pGridsDes = getGridsData(mapType);
	CItemGridArray* pGridsSrc = getGridsData(srcType);
	if (!pGridsDes || !pGridsSrc)
	{
		return;
	}

	for (int i=0; i<pGridsSrc->getSize(); ++i)
	{
		/*过滤空格*/
		CItem* pItem = pGridsSrc->GetItemByPos(i);
		if (!pItem)
		{
			continue;
		}
		/*过滤不能合成的装备*/
		EquipBaseCfg* pCfg = EquipBaseData.get(pItem->getDataID());
// 		if ( !pCfg || !pCfg->integrate )     临时注释
// 		{
// 			continue;
// 		}
		if ( !pCfg)
		{
			continue;
		}

		pItem->retain();
		pGridsDes->PushBackItem(pItem);
	}
}

void CGridsManager::createFurnaceStrenGrids()
{
	CItemGridArray* pGridsDes = getGridsData(emGrids_StrengthMaterial);
	CItemGridArray* pGridsSrc1 = getGridsData(emGrids_Role);
	CItemGridArray* pGridsSrc2 = getGridsData(emGrids_BagEquip);
	if (!pGridsDes || !pGridsSrc1 || !pGridsSrc2)
	{
		return;
	}

	for (int i=0; i<pGridsSrc1->getSize(); ++i)
	{
		/*过滤空格*/
		CItem* pItem = pGridsSrc1->GetItemByPos(i);
		if (!pItem)
		{
			continue;
		}
		pItem->retain();
		pGridsDes->PushBackItem(pItem);
	}

	for (int i=0; i<pGridsSrc2->getSize(); ++i)
	{
		/*过滤空格*/
		CItem* pItem = pGridsSrc2->GetItemByPos(i);
		if (!pItem)
		{
			continue;
		}
		pItem->retain();
		pGridsDes->PushBackItem(pItem);
	}
}

void CGridsManager::createNPCSellGrids()
{
	CItemGridArray* pGridsDes = NULL;
	//CItemGridArray* pGridsDes = getGridsData(emGrids_NPCSell);
	CItemGridArray* pGridsSrc1 = getGridsData(emGrids_BagEquip);
	CItemGridArray* pGridsSrc2 = getGridsData(emGrids_BagMaterial);
	CItemGridArray* pGridsSrc3 = getGridsData(emGrids_BagZaWu);
	if ( !pGridsDes || !pGridsSrc1 || !pGridsSrc2 || !pGridsSrc3 )
	{
		return;
	}

	for (int i=0; i<pGridsSrc1->getSize(); ++i)
	{
		/*过滤空格*/
		CItem* pItem = pGridsSrc1->GetItemByPos(i);
		if (!pItem || pItem->isBind() || pItem->getItemData()->pricesell == -1)
		{
			continue;
		}

		pItem->retain();
		pGridsDes->PushBackItem(pItem);
	}

	for (int i=0; i<pGridsSrc2->getSize(); ++i)
	{
		/*过滤空格*/
		CItem* pItem = pGridsSrc2->GetItemByPos(i);
		if (!pItem || pItem->isBind() || pItem->getItemData()->pricesell == -1)
		{
			continue;
		}

		pItem->retain();
		pGridsDes->PushBackItem(pItem);
	}

	for (int i=0; i<pGridsSrc3->getSize(); ++i)
	{
		/*过滤空格*/
		CItem* pItem = pGridsSrc3->GetItemByPos(i);
		if (!pItem || pItem->isBind() || pItem->getItemData()->pricesell == -1)
		{
			continue;
		}

		pItem->retain();
		pGridsDes->PushBackItem(pItem);
	}

}

void CGridsManager::addScrollUI( ScrollGrids_cl* scroll, emGridsType _type )
{
	pScrollUI[_type] = scroll;
}

void CGridsManager::removeItem( emGridsType _type, int index )
{
	if(pScrollUI[_type])
	{
		pScrollUI[_type]->removeItemByIndex(index);
	}
}

void CGridsManager::addItem( emGridsType _type, int index )
{
	if(pScrollUI[_type])
	{
		pScrollUI[_type]->addItemByIndex(index);
	}
}

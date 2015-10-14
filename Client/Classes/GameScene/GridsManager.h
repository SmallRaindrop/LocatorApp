#pragma once

#include "GameDef.h"
#include "Singleton.h"
#include "UI/CustomCtrl/GridArrayUI.h"
#include "UI/CustomCtrl/ScrollGrids.h"
/***************************************格子组管理器***************************************************/
class CGridsManager : public Singleton<CGridsManager>
{
public:
	CGridsManager();
	~CGridsManager();

	bool initialize();
	void release();

	void update(float dt);

	//仅用于data的接口
	CItemGridArray* getGridsData(emGridsType type) {if (type < emGrids_Count) return pGridsData[type]; return NULL;}

	CItem*			getGirdItem(emGridsType type,int pos);
	CItem*			findItemInGrids(emGridsType type, int64 itemID);
	CItem*			findItemByDataID(emGridsType type, int dataID);
	CItem*          findItemByDataID(int dataID);   //add Tangbo

	int				countItems(emGridsType type);
	int				countAtive(emGridsType type);
	int				countEmpty(emGridsType type);
	int				countNewAdd(emGridsType type);

	int				getItemCountByDataID(emGridsType type,int dataID);

	void			SetNewAdd(emGridsType type,int pageIndex,int pageNum,bool bNewAdd);

	void			PushBackItem(emGridsType type,CItem* pItem);

	int				GetFirstEmptyPos(emGridsType type);
	int				getItemCntByDataID(emGridsType type, int dataID);

	void			addOperateEvent(emGridsType type,Ref* pSender,Grid_OperateEvent event);

	void			clearData(emGridsType type);

	//仅作用于ui的接口
	CGridArrayUI*			getGridsUI(emGridsType type,int pos=0);
	inline CGridArrayUI*	getGridsUIByIndex(emGridsType type,int pageIndex) {return pGridsUI[type][pageIndex];}

	void			attachUI(CGridArrayUI* pUI,emGridsType type,int index = 0);
	void			detachUI(emGridsType type);

	CGridIcon*		getIconByDataId(emGridsType type, int dataID);
	CGridIcon*		getIconByItemId(emGridsType type, int64 itemID);
	CGridIcon*		getIcon(emGridsType type,int pos);
	Widget*			getIconBk(emGridsType type,int pos);

	//mask
	void			UpdateIconMask(emGridsType type);
	void			ShowMaskManual(emGridsType type,bool bShow,ItemCfg* pMaskItemCfg=NULL);

	//operate
	void			insertItemAtGrids(emGridsType type,int pos,int index_from, int index_to);
	void			removeAllGridsUIs(emGridsType type);

	//cd
	void			ShowCd(emGridsType type);
	void			RemoveCd(emGridsType type);

	void			AddIconClickEvent(emGridsType type, Ref* pSender, IconClickEvent event);

	//clear
	void			clearUI();

	//作用于data和ui的接口
	void			ActiveOneLineGrids(emGridsType type);

	void			resetGrids(emGridsType type,vector<pk::BagItem>& itemVec,int activeCount);

	void			insertGrid(emGridsType type,int pos,CItem* pItem,bool bRealInsert=false);
	void			insertGrid(emGridsType type,int pos,int dataId,int num);
	void			insertGrid(emGridsType type,int pos,int dataId,int num,bool binded);
	void			PushBackItem(emGridsType type,CItem* pItem,int gridUIPos);

	CItem*			removeGrid(emGridsType type,int pos);
	void			move(emGridsType type_from, int pos_from, emGridsType type_to, int pos_to);
	void			deleteGrid(emGridsType type,int pos);
	void			removeAllGrids(emGridsType type);
	void			deleteAllGrids(emGridsType type);

	void			newGridCnt(emGridsType type,int pos, int nNewCnt);

	void			ShowCd(emGridsType type,int cdType,float cdTime);


	//创建邮件映射背包
	void createMailGrids(emGridsType mapType, emGridsType srcType);
	/*创建熔炉映射合成背包*/
	void createFurnaceGrids(emGridsType mapType, emGridsType srcType);
	/*创建熔炉映射强化背包*/
	void createFurnaceStrenGrids();
	/*创建NPC Sell 背包*/
	void createNPCSellGrids();

	//加入滑动列表节点指针  add interface By Tangbo
	void addScrollUI(ScrollGrids_cl* scroll, emGridsType _type);
	//从滑动列表删除指定位置的子节点 add interface By Tangbo
	void removeItem(emGridsType _type, int index);
	//向滑动列表添加子节点到指定位置 add interface By Tangbo
	void addItem(emGridsType _type, int index);

private:
	CItemGridArray* pGridsData[emGrids_Count];
	CGridArrayUI*	pGridsUI[emGrids_Count][MAX_PAGE_SIZE];

	//保存滑动列表节点指针   add Tangbo
	ScrollGrids_cl* pScrollUI[emGrids_Count];                                                 
};

#define gGridsManager CGridsManager::Instance()

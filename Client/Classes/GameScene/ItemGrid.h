#ifndef __ItemGrid_h_
#define __ItemGrid_h_

#include "GameDef.h"
#include "Item.h"
#include "Singleton.h"
#include "UI/GameUIDef.h"

enum Grid_Operate
{
	Grid_Operate_Insert,
	Grid_Operate_Remove
};

typedef void (Ref::*Grid_OperateEvent)(int nIndex,Grid_Operate operate);
#define grideventselector(_SELECTOR) (Grid_OperateEvent)(&_SELECTOR)

/***************************************格子***************************************************/
class CItemGrid
{
public:
	CItemGrid() : m_pItem(nullptr),m_bActive(false){}
	~CItemGrid(){}

	inline CItem*	GetItem(){ return m_pItem; }
	inline void		SetItem(CItem* pItem){ m_pItem = pItem; }
	inline void		ReleaseItem(){ CC_SAFE_RELEASE_NULL(m_pItem); }
	inline void		SetActive(bool valid = false ){ m_bActive = valid; }
	inline bool		IsActive(){ return m_bActive; }
	inline bool		IsEmpty(){ return m_pItem == nullptr; }

private:
	CItem*	m_pItem;
	bool	m_bActive;	// 是否开启
};

typedef vector<CItemGrid*> ItemGridList;

/***************************************格子组***************************************************/
class CItemGridArray
{
public:
	CItemGridArray();
	CItemGridArray(int size);
	~CItemGridArray();
	
	void				init(emGridsType type,int size=0);
	void                init(emGridsType type, bool _limit = true);
	void				initGrids(vector<pk::BagItem>& itemVec,int activeCount);

	inline emGridsType	GetType() { return m_gridType; }
	inline void			SetType(emGridsType type) { m_gridType = type; }

	inline int			getSize(void) {return m_size;}

	inline const ItemGridList& getItemGridsList(){return m_Grids;}

	int					ActiveOneLineItemGrids();
	void				ActiveAllGrid();

	CItemGrid*			GetItemGrid(int pos);

	CItem*				GetItemByPos(int pos);
	CItem*				GetItemByID(int64 itemID);
	CItem*				GetItemByDataID(int dataID);

	virtual void		InsertItem(int pos,CItem* pItem);
	virtual void		PushBackItem(CItem* pItem);

	//此方法是在没有使用init方法下使用， 添加新的CItemGrid
	void                addItemToList(CItemGrid* itemgrid);

	virtual CItem*		RemoveItem(int pos);	//移动item
	void				DeleteItem(int pos);	//release item
	void				DeleteAllItems();

	int					GetFirstEmptyPos();
	int					GetFirstNeedActivePos();

	int					GetItemNum(int dataID);
	int					CountEmpty();
	int					CountItem();
	int					CountActive();
	int					CountNoBind();
	int					CountNewAdd();
	bool				IsFull();

	void				SetNewAdd(int pageIndex,int pageNum,bool bNewAdd);

	void				SetItemCdTime(int cdType, float cdTime);
	void				updateItemCd(float dt);

	void				SwitchItem(int pos1,int pos2);
	void				SwitchItem(CItemGrid* pGrid1,CItemGrid* pGrid2);

	inline void			addOperateEvent(Ref* pSender,Grid_OperateEvent event) {m_operateEventListener = pSender; m_operateEventSelector = event;}

	void				clear();

	//只用于清理容器的 不删除本身的item数据 即不释放内存
	inline void         clearItemGridList(){m_Grids.clear();}

	void                ClearData();        //add Tangbo
protected:
	bool                m_blimit;           //是否限制格子大小 默认是true限制
	emGridsType			m_gridType;
	ItemGridList		m_Grids;
	int					m_size;
    Ref*				m_operateEventListener;
	Grid_OperateEvent	m_operateEventSelector;
};

#endif //__ItemGrid_h_
#ifndef __Item_h_
#define __Item_h_

#include "Net/pk_item.h"
#include "GameDef.h"
#include "db.h"
#include "ItemType.h"
#include "UI/GameUIDef.h"

struct ItemInfo
{
	ItemInfo(){
		id = 0;
		index = 0;
		dataId = 0;
		count = 0;
		isBind = false;
		refineLevel = 0;
		enhanceLevel = 0;
		strengthenLevel = 0;
		cd=0;
		newAdd=false;
		dataEx = NULL;
		dataEx64 = 0;
		score = 0;
		tian_shu_exp = 0;
		tian_shu_use_index = 0;
		tian_shu_set_list.clear();
		soltStrengList.clear();
		tianShuList.clear();
		curInlay = false;
		otherInlay = false;
		gridUsed   = false;
		selectCount = 0;
	}

	//公共
	ObjectID	id;					//物品服务器id
	int			dataId;				//物品配置id
	int			index;				//物品在背包中的格子位置，从0开始 或者 装备栏中的部位 物品在装备栏有效
	int			count;				//叠加数量
	bool		isBind;				//是否绑定
	int8        refineLevel;	    //精炼等级    
	int8        enhanceLevel;       //进阶等级
	//装备
	int8        tian_shu_use_index; //当前使用的那一套镶嵌配置id 装备有效
	int16       tian_shu_exp;       //当前的进度值 天书有效
	int8        strengthenLevel;	//强化等级     天书有效
	vector<pk::EquipTianshu> tianShuList;	// 装备上面镶嵌的天书列表 装备有效
	vector<pk::TianshuSoltStreng> soltStrengList;	// 天书孔位强化信息 天书有效
	vector<pk::TianShuSet> tian_shu_set_list;    // 天书上面镶嵌的装备信息列表 天书有效

	//其他
	bool        curInlay;           //当前是否镶嵌               天书
	bool        otherInlay;         //其他地方镶嵌               天书
	bool        gridUsed;           //当前格子里面是否是用       天书
	int         selectCount;        //当前选择                   天书

	int32       score;              //品级
	int8        content_lv;         //容量等级

	float		cd;					//物品使用CD
	bool		newAdd;				//新增标识
	void*		dataEx;				//程序外部链接附加属性
	int64		dataEx64;		
};

class CItem : public Ref
{
public:
	CItem();
	CItem(ItemInfo& info);
	~CItem();

	static CItem* Create(ItemInfo& info);
	static CItem* Create(pk::BagItem* pBagItem);
	static CItem* Create(pk::EquipItem* pEquipItem);
	static CItem* Create(pk::GS2C_SignalItemInfo* pMailItem);

	bool InitWithItemInfo(ItemInfo& info);

	bool InitBagItem(pk::BagItem* pBagItem);

	bool InitEquipItem(pk::EquipItem* pEquipItem);

	inline ItemInfo& getItemInfo() { return m_Info; }

	//物品服务器id
	inline ObjectID	getId(){ return m_Info.id; }
	//物品位置
	inline void		setIndex(int nIndex) {m_Info.index=nIndex;}
	inline int		getIndex() { return m_Info.index; }
	//物品配置id
	inline int		getDataID(){ return m_Info.dataId; }

	inline ItemCfg*	getItemData(){ return m_pItemData; }
	inline EquipBaseCfg* getEquipBaseData(){ return m_pEquipData; }
	inline int		getArtID(){ return getItemData()->artid; }
	inline int		getType(){ return getItemData()->type; }
	inline int		getSubType(){ return getItemData()->subtype;}
	//所需等级  add Tangbo
	inline int      getUseLevel(){ return getItemData()->uselevel; }
	//所需职业  add Tangbo
	inline int		getUseCareer(){ return getItemData()->career; }
	//价额    add Tangbo
	inline int		getItemPrice(){ return getItemData()->pricesell; }
	//获取当前的装备等级评分 add Tangbo
	inline int      getScore(){return m_Info.score;}
	//获取当前经验值  add Tangbo
	inline int      getBookPercent(){return m_Info.tian_shu_exp;}

	//获取当前使用装备是否镶嵌 add Tangbo
	inline bool     getCurInlay(){return m_Info.curInlay;}
	inline void     setCurInlay(bool val){m_Info.curInlay = val;}

	//获取当前未使用装备是否镶嵌 add Tangbo
	inline bool     getOtherInlay(){return m_Info.otherInlay;}
	inline void     setOtherInlay(bool val){m_Info.otherInlay = val;}

	//当前格子里面是否是用       天书
	inline void     setGridUsed(bool val){m_Info.gridUsed = val;};
	
	//当前选择                   天书
	inline void     setSelectCount(int val){m_Info.selectCount = val;}

	//获取当前属性
	inline const ItemInfo& getCurItemInfo(){return m_Info;}   

	//刷新镶嵌状态
	void            refreshInlayStatus();

	//叠加数量
	inline void		setCount(int newCount){m_Info.count=newCount;}
	inline int		getCount(){ return m_Info.count;};
	//是否绑定
	inline bool		isBind() {return m_Info.isBind;}
	//精炼等级
	inline int		getRefinedLv(){return m_Info.refineLevel;}
	inline void		setRefinedLv(int nNewLv) { m_Info.refineLevel = nNewLv;}

	//进阶等级
	inline int		getEnhanceLv(){return m_Info.enhanceLevel;}
	inline void		setEnhanceLv(int nNewLv) { m_Info.enhanceLevel = nNewLv;}


	//cd
	inline void		SetCdTime(float cd) { m_Info.cd=cd; }
	inline float	GetCdTime() { return m_Info.cd; }
	inline float	GetCdTimeTotal(){ return getItemData()->cdtime; }
	inline bool		IsCding() {return m_Info.cd>0;};
	inline void		updateCd(float dt) { if(m_Info.cd>0) m_Info.cd-=dt;}
	//新增标识
	inline void		setNewAdd(bool bNewAdd) {m_Info.newAdd=bNewAdd;}
	inline bool		IsNewAdd() {return m_Info.newAdd;}
	//程序外部链接附加属性
	inline void		setDataEx(void* pData) { m_Info.dataEx=pData; }
	inline void*	getDataEx() { return m_Info.dataEx; }
	inline void		setDataEx64(int64 pData) { m_Info.dataEx64=pData; }
	inline int64	getDataEx64() { return m_Info.dataEx64; }

	
	EquipColumnType getEquipColumnType();

	inline bool		isEquip(){ return getType() == ItemType_Equip; }
	inline bool		isGodDevice(){ return getType() == ItemType_GodDevice; }
	inline bool		isSkyBook(){ return getType() == ItemType_SkyBook; }
	inline bool		isDrawingSheet(){ return getType() == ItemType_DrawingSheet; }
	inline bool		isMaterial(){ return getType() == ItemType_Material; }
	//是否可卖 add Tangbo
	inline bool		isDoSell(){ return getItemPrice() > -1; }

	vector<int>		m_skillId_vec;					// 武器对应技能ID vector
	vector<vector<int>>			m_all_attr_vec[6];  // 6阶不同的属性

protected:
	ItemInfo		m_Info;
	ItemCfg*		m_pItemData;
	EquipBaseCfg*	m_pEquipData;
};

#endif //__Item_h_
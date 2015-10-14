/***
 * 模块：PetDataManager
 * 作者：李阳
 * 时间：2015-09-28
 * 说明：宠物数据管理
 */

#ifndef __PetDataManager_h_
#define __PetDataManager_h_

#include "GameDef.h"
#include "db.h"
#include "Net/pk_item.h"

class PetData
{
public:
	PetData(int id,int dataId,int level,int exp,int strengLv,int isActive,
		pk::FightProperty prop,vector<pk::EquipTianshu> tianShuLis,int content_lv,vector<pk::TianshuSoltStreng> soltStrengList,int tian_shu_use_index);
	~PetData();

	/* Name		：GetPetBaseData
	 * Author	：Liyang
	 * Date		: 2015-09-28
	 * Desc		: 获取宠物配置数据
	 * Param	: none
	 * Return	: PetBaseCfg* 配置数据
	 */
	inline PetBaseCfg* GetPetBaseData(){ return m_pPetBaseData;}

	inline int GetPetID(){ return m_id; }
	inline int GetPetDataID(){ return m_dataId; }
	inline int GetPetLevel(){ return m_level; }
	inline int GetPetExp(){ return m_exp; }
	inline int GetPetStrengLv(){ return m_strengLv; }
	inline int GetPetActive(){ return m_isActive; }
	inline pk::FightProperty GetPetProperty(){return m_prop;}
	inline vector<pk::EquipTianshu> GetTianShuList(){return m_tianShuList;}
	inline int GetPetContentLv(){return m_content_lv;}
	inline vector<pk::TianshuSoltStreng> GetTianshuSoltStreng(){return m_soltStrengList;}
	inline int GetPetTianShuUseIndex(){return m_tian_shu_use_index;}

	inline void SetLevel(int level){m_level = level;}
	inline void SetExp(int exp){m_exp = exp;}
	inline void SetStrengLv(int strengLv){m_strengLv = strengLv;}
	inline void SetIsActive(int isActive){m_isActive = isActive;}
	inline void SetProp(pk::FightProperty prop){m_prop = prop;}
	inline void SetContentLv(int content_lv){m_content_lv = content_lv;}
	inline void SetTianShuUseIndex(int tian_shu_use_index){m_tian_shu_use_index = tian_shu_use_index;}

	/* Name		：Reload
	 * Author	：Liyang
	 * Date		: 2015-09-28
	 * Desc		: 重置宠物相关数据
	 * Param	: dataId
	 * Return	: void
	 */
	void Reload(int dataId);

public:
	int m_id;
	int m_dataId;
	int m_level;
	int m_exp;
	int m_strengLv;
	int m_isActive;									//1出战，0喂出战
	pk::FightProperty m_prop;
	vector<pk::EquipTianshu> m_tianShuList;			// 天书
	int m_content_lv;								// 容量等级
	vector<pk::TianshuSoltStreng> m_soltStrengList;	// 天书位置强化信息
	int m_tian_shu_use_index;						// 天书使用配置套

	PetBaseCfg* m_pPetBaseData;						// 宠物配置数据
};

typedef vector<PetData*> PetDataList;

class PetDataManager
{
public:
	PetDataManager();
	~PetDataManager();

	/* Name		：Insert
	 * Author	：Liyang
	 * Date		: 2015-09-28
	 * Desc		: 添加一个宠物
	 * Param	:
	 * Return	: PetData* 新加的宠物对象的指针
	 */
	PetData*	Insert(int id,int dataId,int level,int exp,int strengLv,int isActive,
		pk::FightProperty prop,vector<pk::EquipTianshu> tianShuLis,int content_lv,vector<pk::TianshuSoltStreng> soltStrengList,int tian_shu_use_index);

	/* Name		：Insert
	 * Author	：Liyang
	 * Date		: 2015-09-28
	 * Desc		: 添加一个宠物
	 * Param	: PetData* 宠物数据指针
	 * Return	: void
	 */
	void		Insert(PetData* pPetData);

	/* Name		：GetByID
	 * Author	：Liyang
	 * Date		: 2015-09-28
	 * Desc		: 获取一个宠物
	 * Param	: id 宠物ID
	 * Return	: PetData* 宠物数据指针
	 */
	PetData*	GetByID(int id);

	/* Name		：GetByDataID
	 * Author	：Liyang
	 * Date		: 2015-09-28
	 * Desc		: 获取一个宠物
	 * Param	: id 宠物配置ID
	 * Return	: PetData* 宠物数据指针
	 */
	PetData*	GetByDataID(int dataid);

	
	/* Name		：GetPetDataList
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 获取宠物数据列表
	 * Param	: none
	 * Return	: PetDataList 宠物数据列表
	 */
	inline PetDataList GetPetDataList(){return m_PetDatas;}

	/* Name		：Clear
	 * Author	：Liyang
	 * Date		: 2015-09-28
	 * Desc		: 清理宠物数据
	 * Param	: none
	 * Return	: void
	 */
	void		Clear();
private:
	PetDataList m_PetDatas;
};

#endif //__RoleBuff_h_
/***
 * 模块：GodDeviceManager
 * 作者：李阳
 * 时间：2015-09-01
 * 说明：神器的数据和管理
 */

#ifndef __GodDeviceManager_h_
#define __GodDeviceManager_h_

#include "GameDef.h"
#include "Net/pk_item.h"
#include "db.h"

enum GodDeviceType
{
	GodDeviceTypee_None,
};

class GodDevice
{
public:
	GodDevice(int godCfgID,int isDress,int refineLevel,int enhanceLevel,int equipId,vector<pk::EquipTianshu> tianShuList,int content_lv,vector<pk::TianshuSoltStreng> soltStrengList,int tian_shu_use_index);
	~GodDevice();
	static const int GOD_MAX_LEVEL = 5;
	static int getArtId(int dataid,int level);
	/* Name		：GetEquipBaseData
	 * Author	：Liyang
	 * Date		: 2015-09-10
	 * Desc		: 获取神器配置数据
	 * Param	: none
	 * Return	: EquipBaseCfg* 配置数据
	 */
	inline EquipBaseCfg* GetEquipBaseData(){ return m_pEquipData;}
	inline ItemCfg* GetItemData(){ return m_pItemData;}

	inline int GetGodIsDress(){ return m_isDress; }
	inline int GetGodRefineLevel(){ return m_refineLevel; }
	inline int GetGodEnhanceLevel(){ return m_enhanceLevel; }
	inline int GetGodEquipId(){ return m_equipId; }
	inline int GetGodDataId(){ return m_pEquipData->id; }
	inline int GetGodArtId(){ return getArtId(GetGodDataId(),GetGodEnhanceLevel()); }
	inline string GetGodDes(){ return m_pEquipData->descripe; }
	inline string GetGodName(){ return m_pEquipData->name; }
	inline vector<int> GetGodSkillIdVec(){ return m_skillId_vec; }

	void SetIsDress(int isDress);

	inline void SetRefineLevel(int refineLevel){m_refineLevel = refineLevel;}
	inline void SetEnhanceLevel(int enhanceLevel){m_enhanceLevel = enhanceLevel;}

	/* Name		：Reload
	 * Author	：Liyang
	 * Date		: 2015-09-01
	 * Desc		: 重置神器相关数据
	 * Param	: godid GodDevice ID
	 * Return	: void
	 */
	void Reload(int godid);

public:
	int m_isDress;						// 1:当前穿戴的神器,0则不是
	int m_refineLevel;					// 精炼等级
	int m_enhanceLevel;					// 进阶等级
	int m_equipId;						// 神器绑定的装备id
	vector<int>			m_skillId_vec;	// 神器对应技能ID vector

	vector<pk::EquipTianshu> m_tianShuList;			// 天书
	int8 m_content_lv;								// 容量等级
	vector<pk::TianshuSoltStreng> m_soltStrengList;	// 天书位置强化信息
	int8 m_tian_shu_use_index;						// 天书使用配置套

	vector<vector<int>>			m_all_attr_vec[6];  // 6阶不同的属性

	EquipBaseCfg*		m_pEquipData;		// 物品配置数据
	ItemCfg*			m_pItemData;		// 物品配置数据
};

typedef vector<GodDevice*> GodDeviceList;

class GodDeviceManager
{
public:
	GodDeviceManager();
	~GodDeviceManager();

	/* Name		：Insert
	 * Author	：Liyang
	 * Date		: 2015-09-01
	 * Desc		: 添加一个神器
	 * Param	: godCfgID 神器配置ID
	 * Return	: GodDevice* 新加的BUFF指针
	 */
	GodDevice*	Insert(int godCfgID,int isDress,int refineLevel,int enhanceLevel,int equipId,vector<pk::EquipTianshu> tianShuList,int content_lv,vector<pk::TianshuSoltStreng> soltStrengList,int tian_shu_use_index);

	/* Name		：Insert
	 * Author	：Liyang
	 * Date		: 2015-09-01
	 * Desc		: 添加一个神器
	 * Param	: GodDevice* 新加的神器指针
	 * Return	: void
	 */
	void		Insert(GodDevice* pGod);

	/* Name		：Get
	 * Author	：Liyang
	 * Date		: 2015-09-01
	 * Desc		: 获取一个神器
	 * Param	: godCfgID 神器配置ID
	 * Return	: GodDevice* 神器
	 */
	GodDevice*	Get(int godCfgID);

	/* Name		：GetIsDressGod
	 * Author	：Liyang
	 * Date		: 2015-09-01
	 * Desc		: 获取当前穿戴的神器的配置ID
	 * Param	: NONE
	 * Return	: 神器配置ID
	 */
	int	GetIsDressGod();

	/* Name		：GetIsDressGod
	 * Author	：Liyang
	 * Date		: 2015-09-08
	 * Desc		: 获取当前穿戴的神器
	 * Param	: NONE
	 * Return	: 当前穿戴的神器
	 */
	GodDevice*	GetIsDressGodPtr();

	/* Name		：GetIsDressGodIndex
	 * Author	：Liyang
	 * Date		: 2015-09-08
	 * Desc		: 获取当前穿戴的神器的index
	 * Param	: NONE
	 * Return	: 当前穿戴的神器的index
	 */
	int	GetIsDressGodIndex();

	/* Name		：Clear
	 * Author	：Liyang
	 * Date		: 2015-09-01
	 * Desc		: 清理神器数据
	 * Param	: none
	 * Return	: void
	 */
	void		Clear();

	/* Name		：Count
	 * Author	：Liyang
	 * Date		: 2015-09-01
	 * Desc		: 统计神器个数
	 * Param	: none
	 * Return	: int 神器个数
	 */
	inline int Count(){ return (int)m_GodDevices.size(); }

	/* Name		：GetBuffList
	 * Author	：Liyang
	 * Date		: 2015-08-21
	 * Desc		: 获取buff列表
	 * Param	: none
	 * Return	: RoleBuffList BUFF列表
	 */
	inline GodDeviceList GetDeviceList(){return m_GodDevices;}

private:
	GodDeviceList m_GodDevices;
};

#endif //__RoleBuff_h_
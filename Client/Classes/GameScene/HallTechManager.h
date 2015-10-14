/***
 * 模块：HallTechManager
 * 作者：李阳
 * 时间：2015-09-24
 * 说明：战舰数据管理
 */

#ifndef __HallTechManager_h_
#define __HallTechManager_h_

#include "GameDef.h"
#include "db.h"

class HallTech
{
public:
	HallTech(int id,int lv,double nextLvTime);
	~HallTech();

	void onTimer(float dt);

	/* Name		：GetHallTechData
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 获取战舰配置数据
	 * Param	: none
	 * Return	: HallTechCfg* 配置数据
	 */
	inline HallTechCfg* GetHallTechData(){ return m_pHallTechData;}

	inline double GetHallTechUpgradeTime(){ return m_nextLvTime; }
	inline int GetHallTechID(){ return m_id; }
	inline int GetHallLevel(){ return m_lv; }
	inline int GetHallMaxLevel(){ return m_pHallTechData->max_lv; }
	//inline string GetHallName(){ return m_pHallTechData->name; }
	inline int GetUpgradeItemID(){return m_pHallTechData->item;}
	
	/* Name		：GetHallDesByLevel
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 获取战舰描述
	 * Param	: none
	 * Return	: string 战舰描述
	 */
	string GetHallDes();

	/* Name		：GetUpgradeGoldByLevel
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 获取战舰功能升级所需的金币
	 * Param	: none
	 * Return	: int 金币数量
	 */
	int GetUpgradeGold();
	
	/* Name		：GetUpgradeItemCountByLevel
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 获取战舰功能升级所需材料数量
	 * Param	: 战舰功能的等级
	 * Return	: int 材料数量
	 */
	int GetUpgradeItemCountByLevel(int level);

	/* Name		：GetUpgradeNeedTimeByLevel
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 获取战舰功能升级所需的时间 毫秒
	 * Param	: 战舰功能的等级
	 * Return	: int 材料数量
	 */
	int GetUpgradeNeedTimeByLevel(int level);

	inline void SetLevel(int level){m_lv = level;}
	inline void SetNextLvTime(double nextTime){m_nextLvTime = nextTime;}

	/* Name		：Reload
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 重置战舰相关数据
	 * Param	: hallTechId
	 * Return	: void
	 */
	void Reload(int hallTechId);

public:
	int m_id;
	int m_lv;
	double m_nextLvTime;							// 升到下级的时间，0表示不是升级状态
	HallTechCfg*		m_pHallTechData;		// 战舰配置数据
};

typedef vector<HallTech*> HallTechList;

class HallTechManager
{
public:
	HallTechManager();
	~HallTechManager();

	/* Name		：Insert
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 添加一个战舰功能信息
	 * Param	: nextLvTime 升到下级的时间戳，0表示不是升级状态
	 * Return	: HallTech* 新加的战舰功能信息指针
	 */
	 HallTech*	Insert(int id,int lv,double nextLvTime);

	/* Name		：Insert
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 添加一个战舰功能信息
	 * Param	: HallTech* 新加的战舰功能信息指针
	 * Return	: void
	 */
	void		Insert(HallTech* pHallTech);

	/* Name		：Get
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 获取一个战舰功能信息
	 * Param	: id 战舰功能信息的ID
	 * Return	: HallTech* 战舰功能信息
	 */
	HallTech*	Get(int id);


	/* Name		：GetByCfgID
	 * Author	：Liyang
	 * Date		: 2015-10-08
	 * Desc		: 获取一个战舰功能信息
	 * Param	: cfgid 战舰功能信息的配置ID
	 * Return	: HallTech* 战舰功能信息
	 */
	HallTech*	GetByCfgID(int cfg_id);

	/* Name		：GetIsUpgrade
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 获取战舰功能是否是升级状态
	 * Param	: id 战舰功能信息ID
	 * Return	: bool 是否在升级状态
	 */
	bool	GetIsUpgrade(int id);

	/* Name		：GetUpgradeTime
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 获取战舰功能升级完成的时间
	 * Param	: id 战舰功能信息ID
	 * Return	: float 升级完成的时间
	 */
	float	GetUpgradeTime(int id);

	/* Name		：GetUpgradeTimePercent
	 * Author	：Liyang
	 * Date		: 2015-10-09
	 * Desc		: 获取战舰功能升级完成的时间百分比
	 * Param	: id 战舰功能信息ID
	 * Return	: float 升级完成的时间百分比
	 */
	float	GetUpgradeTimePercent(int id);

	/* Name		：GetLevelByID
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 获取战舰功能等级
	 * Param	: id 战舰功能信息ID
	 * Return	: int 战舰功能等级
	 */
	int	GetLevelByID(int id);

	/* Name		：GetLevelByCfgID
	 * Author	：Liyang
	 * Date		: 2015-10-08
	 * Desc		: 获取战舰功能等级
	 * Param	: cfg_id 战舰功能信息配置ID
	 * Return	: int 战舰功能等级
	 */
	int	GetLevelByCfgID(int cfg_id);

	/* Name		：GetHallTechList
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 获取战舰功能信息列表
	 * Param	: none
	 * Return	: HallTechList 战舰功能信息列表
	 */
	inline HallTechList GetHallTechList(){return m_HallTechs;}

	/* Name		：Clear
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 清理战舰功能数据
	 * Param	: none
	 * Return	: void
	 */
	void		Clear();

	void Update(float dt);
private:
	HallTechList m_HallTechs;
};

#endif //__RoleBuff_h_
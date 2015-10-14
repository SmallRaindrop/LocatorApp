#ifndef __Hero_h_
#define __Hero_h_

#include "Player.h"
#include "Singleton.h"
#include "Net/pk_role.h"
#include "Skill.h"
#include "Item.h"
#include "GridsManager.h"
#include "RoleBuff.h"
#include "MapItem.h"
#include "Net/pk_item.h"
#include "GodDeviceManager.h"
#include "HallTechManager.h"
#include "Net/pk_map.h"

typedef struct mySaleItem
{
	int32 price;
	int32 remainTime;
	int64 saleId;
	pk::GS2C_SignalItemInfo saleItem;
}MySaleItem;

typedef struct mySaleGold
{
	int32 price;
	int32 remainTime;
	int64 saleId;
	int32 goldType;
}MySaleGold;

class BeginnerGuide;
class CIndicatorLayer;

class CHero : public CPlayer,public Singleton<CHero>
{
public:
	static void	GetMoveCmd(int mapDataID,int cx,int cy,APath& path,pk::C2GS_PlayerMoveTo& cmd);
	static void	PathToPosInfo(int cx,int cy,APath& path,vector<pk::PosInfo>& posInfos);
	static void	PosInfoToPath(int cx,int cy,vector<pk::PosInfo>& posInfos,APath& path);

public:
	CHero();
	~CHero();

	bool initRole();
	void update(float dt);

	/* Name		：updateMove
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 移动处理
	 * Param	: none
	 * Return	: true 继续移动，false 移动结束
	 */
	bool updateMove(float dt);

	/* Name		：updateFlash
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 闪烁处理
	 * Param	: none
	 * Return	: true 继续闪烁，false 闪烁结束
	 */
	bool updateFlash(float dt);

	/* Name		：getModel
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取角色展示model对象指针
	 * Param	: none
	 * Return	: RoleModel* 角色对象指针
	 */
	inline RoleModel* getModel(){ return m_pRoleModel; }

protected:
	RoleModel*	m_pRoleModel;	// 角色展示Model

	// 角色属性
public:
	void SetProperty(RoleProperty idx,int val);
	void SetProperty(RoleProperty idx,__int64 val);
	void SetProperty(RoleProperty idx,const string& val);

	/* Name		：setProperty
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置角色基础属性
	 * Param	: value 服务器传过来的角色数据
	 * Return	: void
	 */
	void setProperty(pk::GS2C_PlayerProperty* value);

	/* Name		：setFightProperty
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置角色战斗属性
	 * Param	: value 服务器传过来的角色数据
	 * Return	: void
	 */
	void setFightProperty(pk::GS2C_PlayerFightProperty* value);

	/*角色单条属性变化*/
	void setSingleProperty(RoleProperty idx, __int64 value);

	inline __int64 GetExp(){ return GetPropertyInt64(RoleProperty_Exp); }
	inline __int64 GetMoneyBind(){ return GetPropertyInt64(RoleProperty_Coin_b); }
	inline __int64 GetMoney() { return GetPropertyInt64(RoleProperty_Coin_b); }
	inline int GetGold() { return GetPropertyInt(RoleProperty_Treasure_b); }
	inline string getHeadIcon(){ __String str; str.initWithFormat("%sCareer%d.png","assets/ui/icon/head/",GetCareer()); return str.getCString(); }

	/* Name		：SetLevel
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置角色等级
	 * Param	: val 等级
	 * Return	: void
	 */
	void SetLevel(int val);

	/*设置经验*/
	void SetExp(__int64 val,bool tips = true);

	/*设置金钱*/
	void SetMoney(__int64 val,bool tips = true);

	/*设置绑定金钱*/
	void SetMoneyBind(__int64 val,bool tips = true);

	/*设置元宝*/
	void SetGold(int val,bool tips = true);

	/*设置绑定元宝*/
	void SetGoldBind(int val,bool tips = true);

	/*设置当期血量*/
	void SetHP(__int64 val);

	/*设置最大血量*/
	void SetHPMax(__int64 val);

	/*设置当期法力*/
	void SetMP(int val);

	/*设置最大法力*/
	void SetMPMax(int val);

// 移动相关
public:
	/* Name		：setPosition
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置元素世界坐标系位置
	 * Param	: 世界坐标x,y
	 * Return	: void
	 */
	void setPosition(float x,float y);

	/* Name		：setPosition
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置元素世界坐标系位置
	 * Param	: 世界坐标Point& position
	 * Return	: void
	 */
	void setPosition(const Point &position);

	/* Name		：SetCell
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置地图元素的逻辑坐标位置
	 * Param	: 逻辑坐标cx,cy
	 * Return	: void
	 */
	void SetCell(int cx,int cy);

	/* Name		：MoveTo
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 移动到指定坐标，进入移动状态
	 * Param	: cx,cy 指定逻辑坐标
	 * Return	: void
	 */
	void MoveTo(int cx,int cy);

	/* Name		：MoveBy
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 在指定方向上移动，进入移动状态
	 * Param	: dir指定方向
	 * Return	: void
	 */
	void MoveBy(__Dir dir);

	/* Name		：NotifyServerStopMove
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 通知服务器停止移动
	 * Param	: none
	 * Return	: void
	 */
	void NotifyServerStopMove();

	/* Name		：processCommand
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 处理指令
	 * Param	: none
	 * Return	: void
	 */
	void processCommand(const RoleCommand& cmd);

	/* Name		：ChangeMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 切换地图
	 * Param	: mapID 地图ID，cx cy 地图逻辑坐标
	 * Return	: void
	 */
	void ChangeMap(ResID mapID,int cx,int cy);

	/* Name		：EnterMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 进入指定地图世界坐标
	 * Param	: pMap地图指针，pos地图中的世界坐标
	 * Return	: void
	 */
	void EnterMap(TileMap* pMap,int cx,int cy);

	/* Name		：LeaveMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 离开当前地图
	 * Param	: none
	 * Return	: void
	 */
	void LeaveMap();

	/* Name		：onEnterDoor
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 元素进入传送门回调函数
	 * Param	: pRegion进入的传送门指针
	 * Return	: void
	 */
	void onEnterDoor(CRegion* pRegion);

	/* Name		：IsTransfering
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 是否正在传送点传送
	 * Param	: none
	 * Return	: true 是，false 否
	 */
	inline bool IsTransfering()	{ return m_bTransDoorFlag;}

protected:
	bool	m_bTransDoorFlag;

public:

	/* Name		：searchItemByCell
	 * Author	：TangBo
	 * Date		: 2015-07-30
	 * Desc		: 搜素附近掉落装备
	 * Param	: cx,cy 地图的格子坐标
	 * Return	: true 有，false 否
	 */
	bool     searchItemByCell(int cx, int cy);

	/* Name		：searchItemByCell
	 * Author	：TangBo
	 * Date		: 2015-07-30
	 * Desc		: 搜素附近掉落装备
	 * Param	: cell 地图的格子坐标
	 * Return	: true 有，false 否
	 */
	bool     searchItemByCell(Point cell);

	bool TryPickupItem();
	bool IsRunningForPicking()	{return m_pPickupAction != NULL;}

	bool SelectTargetByPos(Point pos);
	void SelectTargetNearBy();
	void SelectTargetCancel();
	void SelectTarget(MapObject* pTarget);

	inline MapObject* GetSelectTarget(){ return m_pSelectTarget; }
protected:
	MapObject* m_pSelectTarget;
	CPickupItemAction *m_pPickupAction;

// 装备栏 换装
public:
	/* Name		：Equip
	 * Author	：YueLiangYou
	 * Date		: 2015-07-30
	 * Desc		: 请求穿上装备
	 * Param	: pos 背包索引
	 * Return	: void
	 */
	void	Equip(int pos);

	/* Name		：UnEquip
	 * Author	：YueLiangYou
	 * Date		: 2015-07-30
	 * Desc		: 请求卸下装备
	 * Param	: type 装备栏ID
	 * Return	: void
	 */
	void 	UnEquip(EquipColumnType type);

	void	OnEquiped(int pos,EquipColumnType type);
	void	OnUnEquiped(int pos,EquipColumnType type);
	void	RefreshEquip();

	/* Name		：UseItem
	 * Author	：YueLiangYou
	 * Date		: 2015-07-30
	 * Desc		: 请求使用物品
	 * Param	: pos 背包格子索引
	 * Return	: void
	 */
	void	UseItem(int pos);

	/* Name		：UseItem
	 * Author	：YueLiangYou
	 * Date		: 2015-07-30
	 * Desc		: 请求使用物品
	 * Param	: pos 背包格子索引
	 * Return	: pItem 物品指针
	 */
	void	UseItem(CItem* pItem);

protected:
	// 仓库数据
	//CItemGrid storage[];

	// 任务数据

//////////////////////////////////////////////////////////////////////////
// 技能数据
//////////////////////////////////////////////////////////////////////////
public:
	/* Name		：GetSkillManager
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取角色技能管理器
	 * Param	: none
	 * Return	: SkillManager&
	 */
	inline SkillManager& GetSkillManager(){ return m_SkillMgr; }

	/* Name		：GetSkill
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取角色技能
	 * Param	: skillid 技能ID
	 * Return	: Skill*
	 */
	inline CSkill* GetSkill(int skillid){ return GetSkillManager().Get(skillid); }
	inline CSkill* GetLastestSkill(){ return GetSkillManager().Last(); }
	inline CSkill* AddSkill(CSkill* pSkill){ return GetSkillManager().Insert(pSkill); }
	inline CSkill* AddSkill(int skillid){ return GetSkillManager().Insert(skillid); }

	inline void RemoveSkill(int skillid){ GetSkillManager().Remove(skillid); }
	inline void StartCd(int skillId) { return GetSkillManager().StartCd(skillId); }
	inline void UpdateSkillCd(float dt){ GetSkillManager().UpdateSkill(dt); }
	inline bool IsSkillStudyed(int skillid) { return GetSkillManager().IsStudyed(skillid);}

protected:
	SkillManager	m_SkillMgr;			// 技能管理器

	//////////////////////////////////////////////////////////////////////////
	// 战斗相关
	//////////////////////////////////////////////////////////////////////////
public:
	inline int	GetAttackID(){ return 1000+GetCareer()*100+1; }

	/* Name		：Evade
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 逃避躲闪
	 * Param	: cx,cy 逃避的目标位置
	 * Return	: void
	 */
	void Evade(int cx,int cy);

	/* Name		：Forward
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 冲锋
	 * Param	: cx,cy 冲锋的目标位置
	 * Return	: void
	 */
	void Forward(int cx,int cy);

	/* Name		：UseSkill
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 角色使用技能
	 * Param	: skillid 技能ID
	 * Return	: void
	 */
	void Attack(int skillid);

	/* Name		：UseSkill
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 角色使用技能
	 * Param	: pSkill 使用的技能对象，pTarget 目标对象
	 * Return	: void
	 */
	void UseSkill(SkillCfg* pSkill,RoleFighter* pTarget);

	/* Name		：UseSkill
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 角色使用技能
	 * Param	: pSkill 使用的技能对象，cx,cy 目标逻辑点
	 * Return	: void
	 */
	void UseSkill(SkillCfg* pSkill,int cx,int cy,int offsetX,int offsetY);

	/* Name		：PursueCheck
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 取消追捕
	 * Param	: none
	 * Return	: true 继续追捕 false 取消追捕
	 */
	bool PursueCheck();

	/* Name		：PursueOk
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 追捕到目标
	 * Param	: none
	 * Return	: true 追捕到目标，执行指令 false 继续追捕
	 */
	bool PursueOk();

	/* Name		：Dead
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 角色死亡处理
	 * Param	: pKiller 杀人犯
	 * Return	: void
	 */
	void Dead(RoleFighter* pKiller);

	/* Name		：DeadVirtual
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 角色濒死处理
	 * Param	: pKiller 杀人犯
	 * Return	: void
	 */
	void DeadVirtual(RoleFighter* pKiller);

	/* Name		：Relive
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 角色复活处理
	 * Param	: pFighter 复活者，自动复活为NULL
	 * Return	: void
	 */
	void Relive(RoleFighter* pFighter = nullptr);

	/* Name		：ShowDamageEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示伤害特效及音效
	 * Param	: pos 受伤位置，damage 伤害数值
	 * Return	: void
	 */
	void ShowDamageEffect(Point pos,int damage);

	/* Name		：ShowCritEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示暴击特效及音效
	 * Param	: pos 受伤位置，damage 伤害数值
	 * Return	: void
	 */
	void ShowCritEffect(Point pos,int damage);

	/* Name		：ShowMissEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示闪避特效及音效
	 * Param	: none
	 * Return	: void
	 */
	void ShowMissEffect();

	/* Name		：ShowRecoverHPByItem
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示吃血球效果
	 * Param	: none
	 * Return	: void
	 */
	void ShowRecoverHPByItem(int value);

	/* Name		：ShowRecoverMPByItem
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示吃法球效果
	 * Param	: none
	 * Return	: void
	 */
	void ShowRecoverMPByItem(int value);

	//////////////////////////////////////////////////////////////////////////
	// 战舰数据 
	//////////////////////////////////////////////////////////////////////////
public:
	/* Name		：GetGodDeviceManager
	 * Author	：Liyang
	 * Date		: 2015-09-24
	 * Desc		: 获取战舰数据管理器
	 * Param	: none
	 * Return	: HallTechManager&
	 */
	inline HallTechManager&	GetHallTechManager(){ return m_HallTechManager; }

protected:
	// 战舰数据管理器
	HallTechManager m_HallTechManager;
	
	//////////////////////////////////////////////////////////////////////////
	// ----战舰数据 end----
	//////////////////////////////////////////////////////////////////////////
public:
	/* Name		：GetGodDeviceManager
	 * Author	：Liyang
	 * Date		: 2015-09-01
	 * Desc		: 获取神器管理器
	 * Param	: none
	 * Return	: GodDeviceManager&
	 */
	inline GodDeviceManager&	GetGodDeviceManager(){ return m_GodDeviceMgr; }

	/* Name		：GetGodDevice
	 * Author	：Liyang
	 * Date		: 2015-09-01
	 * Desc		: 获取指定神器对象
	 * Param	: godCfgID
	 * Return	: GodDevice*
	 */
	inline GodDevice* GetGodDevice(int godCfgID){ return GetGodDeviceManager().Get(godCfgID); }

	/* Name		：GetGodDevice
	 * Author	：Liyang
	 * Date		: 2015-09-01
	 * Desc		: 通过下标获取指定神器对象
	 * Param	: index
	 * Return	: GodDevice*
	 */
	inline GodDevice* GetGodDeviceByIndex(int index){ return GetGodDeviceManager().GetDeviceList()[index]; }

	/* Name		：AddGodDevice
	 * Author	：Liyang
	 * Date		: 2015-09-01
	 * Desc		: 添加神器对象
	 * Param	: GodDevice* 神器对象
	 * Return	: void
	 */
	inline void	AddGodDevice(GodDevice* pGod){ GetGodDeviceManager().Insert(pGod); }

	/* Name		：AddGodDevice
	 * Author	：Liyang
	 * Date		: 2015-06-24
	 * Desc		: 添加指定BUFF对象
	 * Param	: buffid
	 * Return	: RoleBuff*
	 */
	inline GodDevice* AddGodDevice(int godCfgID,int isDress,int refineLevel,int enhanceLevel,int equipId,vector<pk::EquipTianshu> tianShuList,int content_lv,vector<pk::TianshuSoltStreng> soltStrengList,int tian_shu_use_index)
	{ return GetGodDeviceManager().Insert(godCfgID,isDress,refineLevel,enhanceLevel,equipId,tianShuList,content_lv,soltStrengList,tian_shu_use_index); }

	/* Name		：ClearGodDevice
	 * Author	：Liyang
	 * Date		: 2015-09-06
	 * Desc		: 清空神器列表
	 * Param	: none
	 * Return	: void
	 */
	inline void	ClearGodDevice(){ GetGodDeviceManager().Clear(); }

	//进入副本特效
	void		ShowCopyEnterEffect();
	//离开副本
	void		LeaveCopy();
	void		LeaveCopyWithEffect();
	inline void SetCanUseSkill(bool bCanUse) { m_bCanUseSkill = bCanUse; }
	inline bool CanUseSkill() { return m_bCanUseSkill; }
private:
	void		CopyEnterActionStart();
	void		CopyEnterActionProcess1();
	void		CopyEnterActionEnd();
	void		CopyLeaveActionStart();
	void		CopyLeaveActionProcess1();
	void		CopyLeaveActionEnd();
private:
	bool		m_bCanUseSkill;

protected:
	GodDeviceManager m_GodDeviceMgr;	// 神器数据管理器
	//////////////////////////////////////////////////////////////////////////
	// ----神器数据 end----
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// ----新手引导
	//////////////////////////////////////////////////////////////////////////
public:
	inline BeginnerGuide*	GetGuidePtr(){ return m_pGuide; }
	void					OnGuideStep(GuideCfg* pData);
	void					OnGuideInitialize();

protected:
	BeginnerGuide*			m_pGuide;

	/***************************方向指示******************************/
public:
	CIndicatorLayer*			GetIndicatorLayer() { return m_pIndicatorLayer; }
private:
	void						AddIndicatorLayer();
	CIndicatorLayer*			m_pIndicatorLayer;
};

#define gHero				CHero::Instance()
#define gMap				dynamic_cast<GameMap*>(gHero->GetMap())
#define GetMapRole(ID)		dynamic_cast<RoleFighter*>(gMap->getObjectManager()->getObject(ID))
#define GetMapPlayer(ID)	dynamic_cast<CPlayer*>(gMap->getObjectManager()->getObject(ID))
#define GetMapMonster(ID)	dynamic_cast<CMonster*>(gMap->getObjectManager()->getObject(ID))
#define GetMapItem(ID)	    dynamic_cast<CMapItem*>(gMap->getObjectManager()->getObject(ID))
#define GetMapObject(ID)	gMap->getObjectManager()->getObject(ID)
#define gIndicatorLayer		gHero->GetIndicatorLayer()

#endif //__Hero_h_
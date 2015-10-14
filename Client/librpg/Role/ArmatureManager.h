/***
 * 模块：动画管理器
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：管理所有动画创建及释放
 */

#pragma once

#include "GameDef.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"
#include "NotifyCenter.h"
#include "Singleton.h"


using namespace cocos2d;
using namespace cocostudio;

typedef map<string,Armature*> ArmatureMap;

class Role;
class Effect;

class ArmatureManager : public Ref,public Singleton<ArmatureManager>
{
public:
	ArmatureManager();
	~ArmatureManager();
	/* Name		：loadArmatureFileForEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 加载动画文件 ExportJson
	 * Param	: dataid 数据配置ID，pEffect加载对象
	 * Return	: void
	 */
	void loadArmatureFileForEffect(int dataid,Effect* pEffect);

	/* Name		：loadArmatureFileForRole
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 加载动画文件 ExportJson
	 * Param	: dataid 数据配置ID，pRole加载对象
	 * Return	: void
	 */
	void loadArmatureFileForRole(int dataid,Role* pRole);

	/* Name		：onArmatureComplete
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 加载动画文件完成回调 ExportJson
	 * Param	: percent 完成的进度，1.0f表示全部完成，否则未全部完成
	 * Return	: void
	 */
	void onArmatureComplete(float percent);

	/* Name		：getNotifyCenterRole
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取角色消息中心
	 * Param	: none
	 * Return	: NotifyCenter<Role>&
	 */
	inline NotifyCenter<Role>& getNotifyCenterRole(){ return m_ncRole; }

	/* Name		：getNotifyCenterEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取特效通知中心
	 * Param	: none
	 * Return	: NotifyCenter<Effect>&
	 */
	inline NotifyCenter<Effect>& getNotifyCenterEffect(){ return m_ncEffect; }

	/* Name		：getArmature
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 创建一个armature对象
	 * Param	: none
	 * Return	: Armature*
	 */
	Armature* getArmature(const string& name);

	Armature* cloneArmature(const Armature* armature);

	

protected:
	ArmatureMap m_mapArmatures;		// 动画表
	NotifyCenter<Role> m_ncRole;	// 角色通知中心
	NotifyCenter<Effect> m_ncEffect;// 特效通知中心
};

#define gArmatureManager ArmatureManager::Instance()
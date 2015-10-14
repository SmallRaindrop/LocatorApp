/***
 * 模块：RoleTile
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：角色头顶上的血条，名称的显示，角色称谓及成就特效
 */

#ifndef __RoleTile_h_
#define __RoleTile_h_

#include "GameDef.h"
#include "UI/GameUI.h"
#include "GameScene/TaskMgr.h"

#define CampColor_Monster	Color3B::WHITE
#define CampColor_Player	Color3B(0x12,0xea,0x2c)
#define CampColor_Red		Color3B::RED
#define CampColor_Blue		Color3B::BLUE

class RoleFighter;

class RoleTitle : public Layer
{
public:
	RoleTitle(RoleFighter* pRole);
	~RoleTitle();

	/* Name		：createWithRole
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 根据角色对象创建一个RoleTile
	 * Param	: pRole 角色对象
	 * Return	: RoleTitle* 
	 */
	static RoleTitle* createWithRole(RoleFighter* pRole);

	/* Name		：init
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 初始化一个RoleTile
	 * Param	: none
	 * Return	: bool true 成功，false 失败
	 */
	bool init();

	void updateRevivePanel();
	void clickReviveButton(Ref* pSender, TouchEventType type);

	void SetNameColor(Color3B clr);
	void SetTitleColor(Color3B clr);
	void SetGuildNameColor(Color3B clr);

	void SetNamePos(float x,float y);
	void SetTitlePos(float x,float y);
	void SetHPBarPos(float x,float y);

	/* Name		：SetRoleName
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置角色名称
	 * Param	: str 角色名称
	 * Return	: void
	 */
	void SetRoleName(const string& str);
	void UpdateRoleNameCampColor();

	/* Name		：SetHPBar
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置血量百分比
	 * Param	: none
	 * Return	: void
	 */
	void SetHPBar();

	/* Name		：SetHPPercent
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置血量百分比
	 * Param	: nPercent 血量百分比
	 * Return	: void
	 */
	void SetHPPercent(int nPercent);

	/* Name		：SetRoleTitle
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置角色称谓
	 * Param	: str 角色称谓
	 * Return	: void
	 */
	void SetRoleTitle(const string& str);

	/* Name		：SetNPCTaskState
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 改变任务状态 只有玩家才会用到
	 * Param	: state 任务状态
	 * Return	: void
	 */
	void SetNPCTaskState(NPCTaskState state);

	/* Name		：SetVip
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置VIP等级显示 只有玩家才会用到
	 * Param	: none
	 * Return	: void
	 */
	void SetVip(bool vip);

	/* Name		：SetTeamLeader
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置队长特效
	 * Param	: leader true 队长，false 不是队长
	 * Return	: void
	 */
	void SetTeamLeader(bool leader = true);

	
	/* Name		：GetRole
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取角色对象指针
	 * Param	: none
	 * Return	: RoleFighter* 角色对象指针
	 */
	void SetShowHPBar(bool bShow);

	/* Name		：GetRole
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取角色对象指针
	 * Param	: none
	 * Return	: RoleFighter* 角色对象指针
	 */

	//设置宝箱或者门的锁
	void SetLock();

	inline RoleFighter* GetRole(){ return m_pRole; }

	inline Text* GetName(){ return m_pName; }
	inline Text* GetTitle(){ return m_pTitle; }
	inline LoadingBar* GetHPBar(){ return m_pHPBar; }
	inline Text* GetGuildName(){ return m_pGuildName; }
	inline ImageView* GetTeamLeader(){ return m_pTeamLeader; }
	inline ImageView* GetVip(){ return m_pVip; }
	inline Widget*	GetLock() { return m_pLock; }

	void			updateTimer();								//  倒计时更新函数
	void			updateProgress();							//  进度条更新函数

	//开宝箱,开门
	void clickLock(Ref* pSender,TouchEventType type);

private:
	RoleFighter*	m_pRole;				// 角色对象指针
	Text*			m_pName;				// 角色名称，所有角色都有的，一开始就被创建
	LoadingBar*		m_pHPBar;				// 血条，所有角色都有的，一开始就被创建
	Text*			m_pTitle;				// 角色称谓，部分角色才有
	Text*			m_pGuildName;			// 公会名称，部分角色才有
	ImageView*		m_pTeamLeader;			// 组队队长特效，部分角色才有
	ImageView*		m_pVip;					// VIP称谓，部分角色才有
	ImageView*		m_pTaskFlag;			// 任务头顶上的特效，部分角色才有
	ImageView*		m_pAutoFight;			// 自动挂机头顶上的特效，部分角色才有
	ImageView*		m_pAutoMove;			// 自动寻路头顶上的特效，部分角色才有
	Widget*			m_revivePanel;			// 复活队友按钮面板
	ProgressTimer*	m_progressBar;			// 复活进度条
	ImageView*		m_reviveTip;			// 复活提示图片
	Text*			m_timer_text;			// 倒计时文本
	Button*			m_progress_btn;			
	int m_deadRestTime;			//	倒计时计数 单位：秒
	int	m_restPoint;			//	环形进度条剩余的点数 满值为10000

	Button*			m_pLock;					// 门或者宝箱类型的怪才有
};

#endif	// __RoleTile_h_
#ifndef __BEGINNER_GUIDE_UI_H__
#define __BEGINNER_GUIDE_UI_H__

#include "GameDef.h"
#include "UI/GameUI.h"
#include "db.h"

// 新手引导控件ID
enum GuideControlID
{
	GControlID_None,
	GControlID_TaskMain = 1,		// 主界面任务入口
	GControlID_TaskAccept = 2,		// 接受任务
	GControlID_TaskSubmit = 3,		// 提交任务
	GControlID_SkillIcon1 = 4,		// 技能按钮
	GControlID_SkillIcon2 = 5,
	GControlID_SkillIcon3 = 6,
	GControlID_SkillIcon4 = 7,
	GControlID_SkillIcon5 = 8,
	GControlID_SkillIcon6 = 9,
	GControlID_SkillIcon7 = 10,
	GControlID_Head = 11,			// 头像
	GControlID_MainRole = 12,		// 主界面角色功能按钮
	GControlID_MainBag = 13,		// 主界面背包
	GControlID_MainStrength = 14,	// 主界面强化功能按钮
	GControlID_MainPet = 15,		// 主界面宠物功能按钮
	GControlID_MainGuild = 16,		// 主界面公会功能按钮
	GControlID_MainFriend = 17,		// 主界面好友功能按钮
	GControlID_MainArchi = 18,		// 主界面成就功能按钮
	GControlID_MainSet = 19,		// 主界面设置功能按钮
	GControlID_NewItem = 20,		// 装备新物品
	GControlID_Tips = 21,			// 道具TIPs中的使用按钮
	GControlID_Strength = 22,		// 强化界面强化按钮
	GControlID_BagClose = 23,		// 关闭背包按钮
	GControlID_StrClose = 24,		// 关闭强化按钮
	GControlID_MainActivity = 25,	// 主界面活动中心按钮
	GControlID_Max,					// 最大值
};

struct GuideControlMapping
{
	GuideControlID	id;			// 控件ID
	emIDU			idu;		// UI界面ID
	int				type;		// 控件类型 0 普通控件，1 物品，2 装备
	string			name;		// 控件名称
};

class BeginnerGuideLayer : public Layer
{
public:
	BeginnerGuideLayer();
	virtual ~BeginnerGuideLayer();
	virtual bool initWithGuideData(GuideCfg* pData);

	/* Name		：getGuideControlRect
	 * Author	：Yueliangyou
	 * Date		: 2015-07-16
	 * Desc		: 获取控件区域
	 * Param	: controlid[in]控件ID，rect[out] 区域 
	 * Return	: true 成功;false 失败
	 */
	virtual bool getGuideControlRect(GuideControlID controlid,Rect& rect);

	/* Name		：getWidgetRect
	 * Author	：Yueliangyou
	 * Date		: 2015-07-16
	 * Desc		: 获取普通控件区域
	 * Param	: idu 已打开的界面，name[in] 控件名，rect[out] 区域 
	 * Return	: true 成功;false 失败
	 */
	virtual bool getWidgetRect(int idu,const string& name,Rect& rect);

	/* Name		：getItemRect
	 * Author	：Yueliangyou
	 * Date		: 2015-07-16
	 * Desc		: 获取物品控件区域
	 * Param	: dataid[in] 装备ID，rect[out] 区域 
	 * Return	: true 成功;false 失败
	 */
	virtual bool getItemRect(int dataid,Rect& rect);

	/* Name		：getEquipRect
	 * Author	：Yueliangyou
	 * Date		: 2015-07-16
	 * Desc		: 获取装备控件区域
	 * Param	: dataid[in] 装备ID，rect[out] 区域 
	 * Return	: true 成功;false 失败
	 */
	virtual bool getEquipRect(int dataid,Rect& rect);

	virtual void onComplete();
	virtual void onClose();

	inline GuideCfg*	getGuideData(){ return m_pGuideData; }
	inline float		getDelayTime(){ return m_fDelayTime; }
	inline void			setDelayTime(float dt){ m_fDelayTime = dt; }

protected:
	GuideCfg*	m_pGuideData;
	float		m_fDelayTime;
};

class BeginnerGuideCommon : public BeginnerGuideLayer
{
public:
	BeginnerGuideCommon();
	~BeginnerGuideCommon();
	static BeginnerGuideCommon* create(GuideCfg* pData);

	bool initWithGuideData(GuideCfg* pData);
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	//当新手引导退出的时候在onExit()中处理一些事情
	void onExit();

protected:
	ImageView* m_pImage;
};

class BeginnerGuideForce : public BeginnerGuideLayer
{
public:
	BeginnerGuideForce();
	~BeginnerGuideForce();
	static BeginnerGuideForce* create(GuideCfg* pData);

	bool initWithGuideData(GuideCfg* pData);
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void update(float delta);
	//当新手引导退出的时候在onExit()中处理一些事情
	void onExit();

protected:
	ClippingNode*	m_pClippingNode;
};

class BeginnerGuideMove : public BeginnerGuideLayer
{
public:
	BeginnerGuideMove();
	~BeginnerGuideMove();
	static BeginnerGuideMove* create(GuideCfg* pData);

	bool initWithGuideData(GuideCfg* pData);
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchMoved(Touch *pTouch, Event *pEvent);
	void onTouchEnded(Touch *touch, Event *unused_event); 
	void onTouchCancelled(Touch *touch, Event *unused_event);
	//当新手引导退出的时候在onExit()中处理一些事情
	void onExit();

protected:
	Point			m_OriginPoint;
	bool			m_bFlag;
};

class BeginnerGuideSkill : public BeginnerGuideLayer
{
public:
	BeginnerGuideSkill();
	~BeginnerGuideSkill();
	static BeginnerGuideSkill* create(GuideCfg* pData);

	bool initWithGuideData(GuideCfg* pData);
	bool onTouchBegan(Touch *pTouch, Event *pEvent);
	void onTouchMoved(Touch *pTouch, Event *pEvent);
	//当新手引导退出的时候在onExit()中处理一些事情
	void onExit();

	void onComplete();

protected:
	SkillCfg*		m_pSkillData;
	ImageView*		m_pSkillIcon;
};

#endif // __BEGINNER_GUIDE_UI_H__
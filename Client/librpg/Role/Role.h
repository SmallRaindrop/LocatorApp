/***
 * 作者：岳良友
 * 时间：2015-07-2
 * 说明：角色相关，角色外观的展示，角色移动，追踪等
 * 有自己行为，动作，甚至AI，Monster,Player,Hero,Npc,Pet都是一个角色
 */

#ifndef __Role_H_
#define __Role_H_

#include "GameDef.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"
#include "RoleData.h"
#include "RoleState.h"
#include "RoleEvent.h"
#include "NotifyCenter.h"
#include "MoveMonitor.h"
#include "Map/MapObject.h"
#include "RoleCommand.h"
#include "Effect.h"
#include "RoleEffect.h"

using namespace cocos2d;
using namespace cocostudio;

class Role : public MapObject,public StateMachine<Role>
{
public:
	static const int FACES = 5;

public:
	Role();
	virtual ~Role();

	CREATE_FUNC(Role);

	/* Name		：init
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 角色初始化
	 * Param	: none
	 * Return	: true 成功，false 失败
	 */
	virtual bool init(){ return true; }

	/* Name		：update
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 毎帧更新
	 * Param	: none
	 * Return	: void
	 */
	virtual void update(float dt);

	/* Name		：updateMove
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 移动处理
	 * Param	: none
	 * Return	: true 继续移动，false 移动结束
	 */
	virtual bool updateMove(float dt);

	/* Name		：updateFlash
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 闪烁处理
	 * Param	: none
	 * Return	: true 继续闪烁，false 闪烁结束
	 */
	virtual bool updateFlash(float dt);

	/* Name		：updateLightShadow
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 更新动态光影
	 * Param	: none
	 * Return	: dt 时间戳
	 */
	virtual void updateLightShadow(float dt);

	/* Name		：GhostShadowCallBack
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 残影回调处理
	 * Param	: pSprite 残影对象
	 * Return	: void
	 */
	virtual void GhostShadowCallBack(Sprite* pSprite);

	/* Name		：SetSkinEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置皮肤效果 
	 * Param	: type 效果类型
	 * Return	: void
	 */
	virtual void SetSkinEffect(int type);

public:
	/* Name		：EnterMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 进入指定地图世界坐标
	 * Param	: pMap地图指针，pos地图中的世界坐标
	 * Return	: void
	 */
	virtual void EnterMap(TileMap* pMap,const Point& pos);

	/* Name		：EnterMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 进入指定地图
	 * Param	: pMap地图指针，cx，cy地图中的逻辑坐标
	 * Return	: void
	 */
	virtual void EnterMap(TileMap* pMap,int cx,int cy);

	/* Name		：LeaveMap
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 离开当前地图
	 * Param	: none
	 * Return	: void
	 */
	virtual void LeaveMap();

	/* Name		：GetMoveMonitor
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取移动监控
	 * Param	: none
	 * Return	: 移动监控引用
	 */
	inline MoveMonitor& GetMoveMonitor(){ return m_MoveMonitor; }

	/* Name		：GetMovePath
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取当前移动路径
	 * Param	: none
	 * Return	: 移动路径
	 */
	inline APath& GetMovePath(){ return GetMoveMonitor().GetPath(); }

	/* Name		：MoveTo
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 移动到指定坐标，进入移动状态
	 * Param	: cx,cy 指定逻辑坐标
	 * Return	: void
	 */
	virtual void MoveTo(int cx,int cy);

	/* Name		：MoveBy
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 在指定方向上移动，进入移动状态
	 * Param	: dir指定方向
	 * Return	: void
	 */
	virtual void MoveBy(__Dir dir);

	/* Name		：MoveBy
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 按指定移动路径
	 * Param	: path路径 offset 时间偏移量
	 * Return	: void
	 */
	virtual void Move(APath& path,long offset=0);

	/* Name		：Stop
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 立即停止移动
	 * Param	: none
	 * Return	: void
	 */
	virtual void Stop();

	/* Name		：StopTo
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 到指定位置停止移动
	 * Param	: x,y指定位置
	 * Return	: void
	 */
	virtual void StopTo(int x,int y);

	/* Name		：IsMoving
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 是否处于移动状态
	 * Param	: none
	 * Return	: 移动状态返回true，其他false
	 */
	inline bool IsMoving(){ return GetCurrStateID() == RoleState_Move; }

	/* Name		：IsStandStill
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 是否处于待机状态
	 * Param	: none
	 * Return	: 待机状态返回true，其他false
	 */
	inline bool IsStandStill(){ return GetCurrStateID() == RoleState_Idle; }

	/* Name		：IsFlipped
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 是否经过翻转
	 * Param	: none
	 * Return	: true 已翻转，false 未翻转
	 */
	inline bool IsFlipped(){ return getArmor() ? getArmor()->getScaleX() == -1.0f : false; }

	inline Armature*	getArmor(){ return m_pArmor; }
	inline Armature*	getWeapon(){ return m_pWeapon; }
	inline Armature*	getWing(){ return m_pWing; }

	inline int			getDir(){ return m_nDir; }
	inline RoleAction	getActionName(){ return m_sActionName; }

	/* Name		：GetActionSpeed
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取动作播放速度
	 * Param	: none
	 * Return	: 播放速度
	 */
	inline int  GetActionSpeed(){ return m_nActionSpeed; }

	/* Name		：GetData
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取角色数据
	 * Param	: none
	 * Return	: RoleData*
	 */
	inline RoleData* GetData(){ return m_pData; }

	virtual void SetProperty(RoleProperty idx,int val){ GetData()->SetProperty(idx,val); }
	virtual void SetProperty(RoleProperty idx,__int64 val){ GetData()->SetProperty(idx,val); }
	virtual void SetProperty(RoleProperty idx,const string& val){ GetData()->SetProperty(idx,val); }

	/* Name		：GetPropertyInt
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取角色数据
	 * Param	: none
	 * Return	: int 值
	 */
	inline int GetPropertyInt(RoleProperty idx){ int val = 0;GetData()->GetProperty(idx,val); return val; }

	/* Name		：GetPropertyInt64
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取角色数据
	 * Param	: none
	 * Return	: __int64 值
	 */
	inline __int64 GetPropertyInt64(RoleProperty idx){ __int64 val = 0;GetData()->GetProperty(idx,val); return val; }

	/* Name		：GetPropertyStr
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取角色数据
	 * Param	: none
	 * Return	: string 值
	 */
	inline string GetPropertyStr(RoleProperty idx){ string val; GetData()->GetProperty(idx,val); return val; }

	/* Name		：GetRoleName
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取角色名称
	 * Param	: none
	 * Return	: 角色名称
	 */
	inline string& GetRoleName(){ return GetData()->GetName(); }

	/* Name		：HasStateFlag
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断角色是否拥有某个状态标志位
	 * Param	: val 状态值
	 * Return	: true 有，false 没有
	 */
	inline bool	HasStateFlag(int val){ return GetData()->HasStateFlag(RoleStatus(val)); }

	/* Name		：GetStateFlag
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取角色状态标志位
	 * Param	: none
	 * Return	: int 角色状态标志位
	 */
	inline int GetStateFlag(){ return GetData()->GetStateFlag(); }

	/* Name		：GetMoveSpeed
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取角色移动速度
	 * Param	: none
	 * Return	: int 角色移动速度
	 */
	inline int  GetMoveSpeed(){ return GetData()->GetSpeed(); }

	/* Name		：SetRoleName
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置角色名称
	 * Param	: val 名称
	 * Return	: void
	 */
	virtual void SetRoleName(const string& val){ GetData()->SetName(val); }

	/* Name		：SetStateFlag
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 设置角色状态标志位
	 * Param	: val 状态值
	 * Return	: void
	 */
	virtual void SetStateFlag(int val){ GetData()->SetStateFlag(RoleStatus(val)); }

	/* Name		：AddStateFlag
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 增加指定角色状态标志位
	 * Param	: val 状态值
	 * Return	: void
	 */
	virtual void AddStateFlag(int val){ GetData()->AddStateFlag(RoleStatus(val)); }

	/* Name		：ClrStateFlag
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 清除指定角色状态标志位
	 * Param	: val 状态值
	 * Return	: void
	 */
	virtual void ClrStateFlag(int val){ GetData()->ClrStateFlag(RoleStatus(val)); }

	/* Name		：SetMoveSpeed
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取角色移动速度
	 * Param	: int 角色移动速度
	 * Return	: void
	 */
	virtual void SetMoveSpeed(int speed){ GetData()->SetSpeed(speed); }

	/* Name		：SetActionSpeed
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 设置动作播放速度，播放时间
	 * Param	: speed 播放速度 单位ms
	 * Return	: void
	 */
	virtual void SetActionSpeed(int speed);

	/* Name		：changeDir
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 改变朝向
	 * Param	: dir 朝向
	 * Return	: void
	 */
	virtual void changeDir(__Dir dir);

	/* Name		：flip
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 设置翻转
	 * Param	: val true设置翻转，false不设置翻转
	 * Return	: void
	 */
	virtual void flip(bool val = true);

	/* Name		：playAction
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 播放指定动作
	 * Param	: action 动作ID，durationTo loop
	 * Return	: void
	 */
	virtual void playAction(RoleAction action,int duration = 0, int loop = -1);

	/* Name		：stopAction
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 停止当前播放的动作
	 * Param	: none
	 * Return	: void
	 */
	virtual void stopAction();

	/* Name		：refreshAction
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 更新动作
	 * Param	: go 是否保持当前帧
	 * Return	: void
	 */
	virtual void refreshAction(bool go = false);

	/* Name		：enableLightShadow
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 开启或者关闭动态光影
	 * Param	: flag = true 开启，= false 关闭
	 * Return	: void
	 */
	virtual void enableLightShadow(bool flag);

	/* Name		：enableGhostShadow
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 开启或者关闭残影效果
	 * Param	: flag = true 开启，= false 关闭
	 * Return	: void
	 */
	virtual void enableGhostShadow(bool flag);

	/* Name		：draw
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 画角色碰撞区域和占用格子
	 * Param	: none
	 * Return	: void
	 */
	virtual void draw(Renderer *renderer, const kmMat4& transform, bool transformUpdated);
	virtual void onDraw(Renderer *renderer, const kmMat4& transform, bool transformUpdated);

	/* Name		：drawCollisionRect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 画角色碰撞区域
	 * Param	: none
	 * Return	: void
	 */
	void drawCollisionRect(Renderer *renderer, const kmMat4& transform, bool transformUpdated);

	/* Name		：drawCollisionRect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 画角色占用格子
	 * Param	: none
	 * Return	: void
	 */
	void drawRoleCell(Renderer *renderer, const kmMat4& transform, bool transformUpdated);

	/* Name		：drawHungingPoints
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 画角色身上挂点
	 * Param	: none
	 * Return	: void
	 */
	void drawHungingPoints(Renderer *renderer, const kmMat4& transform, bool transformUpdated);

	// 换装
	virtual void equipWeapon(int dataid);
	virtual void equipArmor(int dataid);
	virtual void equipWing(int dataid);

	virtual void equipWeapon(const char* weapon);
	virtual void equipArmor(const char* armor);
	virtual void equipWing(const char* wing);

	virtual void unequipWeapon();
	virtual void unequipArmor();
	virtual void unequipWing();
	virtual void unequipAll();

	/* Name		：ShowEffectAsync
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通用展示角色特效及音效
	 * Param	: config特效标准配置
	 * Return	: void
	 */
	virtual void ShowEffectAsync(const string& config);

	/* Name		：ShowEffectAsync
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通用展示角色特效及音效
	 * Param	: effectid 特效文件ID，name 特效名称播放索引
	 * Return	: void
	 */
	virtual void ShowEffectAsync(int effectid,const string& name,int zorder = 0);

	/* Name		：ShowEffectAsync
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 在角色身上显示一个特效
	 * Param	: Effect* pEffect
	 * Return	: void
	 */
	virtual void ShowEffectAsync(RoleEffect* pEffect);

	/* Name		：ShowEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 在角色身上上显示一个特效
	 * Param	: config 配置数据 [id;name;hpoint;scale]
	 * Return	: void
	 */
	virtual void ShowEffect(const string& config);

	/* Name		：ShowEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 通用展示角色特效及音效
	 * Param	: effectid 特效文件ID，name 特效名称播放索引
	 * Return	: void
	 */
	virtual void ShowEffect(int effectid,const string& name,int hpt = 0,float scale = 1.0f,int zorder = 0);

	/* Name		：ShowEffect
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 在角色身上上显示一个特效
	 * Param	: Effect* pEffect
	 * Return	: void
	 */
	virtual void ShowEffect(Effect* pEffect);

	/* Name		：ShowEffectCallBack
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 展示角色特效通用回调
	 * Param	: none
	 * Return	: void
	 */
	virtual void ShowEffectCallBack(Layer* pLayer);

	/* Name		：PushShowEffectLayer
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 增加效果展示对象
	 * Param	: pLayer
	 * Return	: void
	 */
	virtual void PushShowEffectLayer(Layer* pLayer);

	/* Name		：ClearShowEffectLayer
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 清除角色身上的效果展示
	 * Param	: none
	 * Return	: void
	 */
	virtual void ClearShowEffectLayer(Layer* pLayer);

	/* Name		：ClearShowEffectLayer
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 清除角色身上的效果展示
	 * Param	: none
	 * Return	: void
	 */
	virtual void ClearShowEffectLayer();

	/* Name		：attach
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 附加特效
	 * Param	: config 配置数据
	 * Return	: void
	 */
	virtual void attach(const string& config);

	/* Name		：attach
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 附加特效
	 * Param	: dataid 特效配置ID，name 特效名称（播放动画）
	 * Return	: void
	 */
	virtual Effect* attach(int dataid,const string& name,int zorder = 0);

	/* Name		：attach
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 附加特效
	 * Param	: pEffect 特效对象指针
	 * Return	: void
	 */
	virtual void attach(Effect* pEffect);

	/* Name		：isAttached
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 是否附加特效
	 * Param	: dataid name 特效dataid和名称
	 * Return	: true 已附加，false 没有附加
	 */
	virtual bool isAttached(int dataid,const string& name);

	/* Name		：detach
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 去掉角色身上的某个特效
	 * Param	: dataid name 特效dataid和名称
	 * Return	: void
	 */
	virtual void detach(int dataid,const string& name);

	/* Name		：detach
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 去掉角色身上的某个特效
	 * Param	: pEffect 特效指针
	 * Return	: void
	 */
	virtual void detach(Effect* pEffect);

	/* Name		：detach
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 去掉角色身上的所有特效
	 * Param	: none
	 * Return	: void
	 */
	virtual void detach();

	/* Name		：onAnimationEvent
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 动作事件响应函数
	 * Param	: armature movementType movementID
	 * Return	: void
	 */
	virtual void onAnimationEvent(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);

	/* Name		：onFrameEvent
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 帧事件响应函数
	 * Param	: bone 骨骼，evt 事件自定义参数，
	 * Return	: void
	 */
	virtual void onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex);

	/* Name		：onNotifyCenter
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 收到通知中心传来消息
	 * Param	: msg 消息号
	 * Return	: void
	 */
	virtual void onNotifyCenter(int msg);

	/* Name		：processCommand
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 处理指令
	 * Param	: none
	 * Return	: void
	 */
	virtual void processCommand(const RoleCommand& cmd);

	/* Name		：pushCommand
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 新增指令
	 * Param	: cmd 指令数据
	 * Return	: void
	 */
	virtual void pushCommand(const RoleCommand& cmd);

	/* Name		：Pursue
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 追捕目标
	 * Param	: pTarget 追捕目标，distance 追击到与目标的距离，cmd 追捕到目标后执行指令
	 * Return	: void
	 */
	virtual void Pursue(__int64 targetid,int distance,const RoleCommand& cmd);

	/* Name		：PursueCancel
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 取消追捕
	 * Param	: none
	 * Return	: void
	 */
	virtual void PursueCancel();

	/* Name		：PursueCheck
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 取消追捕
	 * Param	: none
	 * Return	: true 继续追捕 false 取消追捕
	 */
	virtual bool PursueCheck();

	/* Name		：PursueOk
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 追捕到目标
	 * Param	: none
	 * Return	: true 追捕到目标，执行指令 false 继续追捕
	 */
	virtual bool PursueOk();

	/* Name		：PursueUpdate
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 追捕更新
	 * Param	: none
	 * Return	: void
	 */
	virtual void PursueUpdate();

	/* Name		：IsPursueing
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 是否正在追击
	 * Param	: none
	 * Return	: void
	 */
	inline bool IsPursueing(){ return m_nPursueTargetID != 0 ;}

	/* Name		：GetDistanceTo
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取自身与目标逻辑点的距离
	 * Param	: cx,cy 目标逻辑点
	 * Return	: int 距离
	 */
	inline int	GetDistanceTo(int cx,int cy){ return Distance(GetCellX(),GetCellY(),cx,cy); }

	/* Name		：GetDistanceTo
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 获取自身与目标的距离
	 * Param	: pTarget 目标对象
	 * Return	: int 距离
	 */
	inline int	GetDistanceTo(Role* pRole){ return pRole ? GetDistanceTo(pRole->GetCellX(),pRole->GetCellY()) : -1; }

protected:
	Armature* m_pArmor;			// 盔甲
	Armature* m_pWeapon;		// 武器
	Armature* m_pWing;			// 翅膀

	bool		m_bLightShadow;		// 动态光影开关
	int			m_nArmorShadowFrame;	// 盔甲的阴影帧
	int			m_nWeaponShadowFrame;	// 无期的阴影帧
	int			m_nWingShadowFrame;	// 翅膀的阴影帧
	Sprite*		m_pArmorShadow;		// 盔甲的阴影
	Sprite*		m_pWeaponShadow;	// 无期的阴影
	Sprite*		m_pWingShadow;		// 翅膀的阴影

	bool		m_bGhostShadow;// 残影效果开关
	Layer*		m_pGhostShadowLayer;// 残影层

	int			m_nArmorID;		// 盔甲DataID
	int			m_nWeaponID;	// 武器DataId
	int			m_nWingID;		// 翅膀DataId

	int			m_nActionSpeed;	// 动作播放速度
	RoleAction	m_sActionName;	// 动作ID
	int			m_nDurationTo;	//
	int			m_nLoop;		// 是否循环
	int			m_nDir;			// 当前朝向面向

	RoleData*	m_pData;		// 数据

	__int64			m_nPursueTargetID;		// 追击目标的ID，为什么要记录ID不记录指针，防止下线造成的野指针
	APoint			m_pursueTargetPos;		// 追击目标的位置
	int				m_nPursueDistance;		// 追击到与目标的距离
	RoleCommand		m_pursueCommand;		// 追击到目标后的指令

	MoveMonitor	m_MoveMonitor;	// 处理移动的监控

	deque<RoleCommand> m_dequeCommands;	// 指令列表

	EffectList		m_vEffects;				// 角色身上特效
	vector<Layer*>	m_vShowEffectLayers;	// 效果层

};

#endif //__Role_H_
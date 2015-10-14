#ifndef __BEGINNER_GUIDE_H__
#define __BEGINNER_GUIDE_H__

#include "GameDef.h"
#include "db.h"
#include "BeginnerGuideLayer.h"

// 新手引导模式
enum GuideMode
{
	GuideMode_Common,	// 普通模式引导
	GuideMode_Force,	// 强制模式引导
	GuideMode_Move,		// 移动引导
	GuideMode_Skill,	// 新技能学习引导
};

class BeginnerGuide
{
public:
	BeginnerGuide();
	~BeginnerGuide();

public:
	/* Name		：Update
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 更新引导层
	 * Param	: dt 时间戳
	 * Return	: void
	 */
	void Update(float dt);

	/* Name		：IsGuideActive
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 检查引导层是否开启
	 * Param	: dataid 配置数据项id
	 * Return	: true 开启，false 未开启
	 */
	bool IsGuideActive(int dataid);

	/* Name		：OpenGuide
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 开启引导层
	 * Param	: dataid 配置数据项ID
	 * Return	: void
	 */
	void OpenGuide(int dataid);

	/* Name		：OpenGuide
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 开启引导层
	 * Param	: pData 配置数据项
	 * Return	: void
	 */
	void OpenGuide(GuideCfg* pData);

	/* Name		：CloseGuide
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 关闭指定的引导层
	 * Param	: dataid 配置数据项id
	 * Return	: void
	 */
	void CloseGuide(int dataid);

	/* Name		：CloseGuide
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 关闭所有的引导层
	 * Param	: none
	 * Return	: void
	 */
	void CloseGuide();
	
	/* Name		：Initialize
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 初始化引导数据
	 * Param	: none
	 * Return	: void
	 */
	void Initialize();

	/* Name		：Exit
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 退出引导
	 * Param	: none
	 * Return	: void
	 */
	void Exit();

protected:
	vector<int>					m_listID;			// 完成过的所有引导ID记录
	vector<BeginnerGuideLayer*>	m_listGuideUI;		// 当前打开的所有引导UI界面
};

#endif
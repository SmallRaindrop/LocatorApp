
/***
 * 模块：GameHelper
 * 作者：岳良友
 * 时间：2015-7-7
 * 说明：游戏辅助相关功能
 */

#include "Singleton.h"
#include "UI/WaitMessageUI.h"

class GameHelper : public Singleton_Auto<GameHelper>
{
public:
	GameHelper();
	~GameHelper();

public:
	/* Name		：IsDoubleClicked
	 * Author	：YueLiangYou
	 * Date		: 2015-06-24
	 * Desc		: 判断是否为双击
	 * Param	: void
	 * Return	: bool 双击返回true，否则返回false
	 */
	bool IsDoubleClicked();

	/* Name		：setWaitMsgLayer
	 * Author	：TangBo
	 * Date		: 2015-07-16
	 * Desc		: 显示和关闭等待界面
	 * Param	: _show 
	 * Return	: 
	 */
	void SetWaitMsgLayer(bool _show);

};

#define gGameHelper GameHelper::Instance()
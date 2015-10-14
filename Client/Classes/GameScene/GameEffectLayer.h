/***
 * 模块：游戏特效层
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：技能特效，效果特效管理器，自动移除没用的特效
 */

#ifndef __GameEffectLayer_h_
#define __GameEffectLayer_h_

#include "GameDef.h"
#include "Effect.h"

class GameEffectLayer : public Layer , public Singleton<GameEffectLayer>
{
public:
	GameEffectLayer(){}
	~GameEffectLayer(){}

	void update(float dt){}

protected:
	EffectList m_Effects;
};

#define gEffectLayer GameEffectLayer::Instance()

#endif // __GameEffectLayer_h_
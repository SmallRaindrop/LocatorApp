#ifndef __ProgressBar_h_
#define __ProgressBar_h_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace std;
using namespace ui;

// 进度条
#define PRECENT_MAX    100.f

class ProgerssBar : public Node
{
public:
	ProgerssBar();
	~ProgerssBar();

	CREATE_FUNC(ProgerssBar);

	bool init();

	void setTexture(const string& background,const string& progress,const string& cursor = "");

	void update(float dt);

	// 设置进度条前进速度
	inline void SetMoveSpeed(float speed){ m_fSpeed = speed; }
	inline float SetMoveSpeed(){ return m_fSpeed; }

	// 设置游标
	inline void SetPercent(float percent){ m_fPercent = percent; }
	inline int GetPercent(){ return m_fPercent; }

	// 判读进度条是否完成
	inline bool IsComplete(){ return m_fCursor >= PRECENT_MAX; }

	// 设置大小
	inline const Size& GetSize(){ return m_Size; }
	void SetSize(Size size);

	// 设置文字显示
	void SetText(const string& str);

	void Reset();

protected:
	float	m_fSpeed;	// 进度走的速度
	float	m_fCursor;	// 进度条自身移动游标 游标位置不会超过当前进度
	float	m_fPercent;	// 当前进度

	Size	m_Size;		// 进度条的大小

	LayerColor* m_pLayerBackGround;	// 底
	LayerColor* m_pLayerProgress;	// 进度
	Node*		m_pLoadginBg;		// 进度条底图片
	LoadingBar* m_pLoadingBar;		// 进度条图片
	Sprite*		m_pImageCursor;		// 游标图片
	Label*		m_pText;			// 进度条文字
};

#endif
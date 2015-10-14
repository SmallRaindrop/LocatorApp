#pragma once
#include "UI/CocosUI.h"
#include "CCScheduler.h"

USING_NS_CC;

class TimerEx: public TimerTargetSelector
{
public:
	float GetElapsed()	{return _elapsed;}
};

class TimerProgressBar :public ui::LoadingBar
{
public:
	TimerProgressBar(void);
	virtual ~TimerProgressBar(void);
    static	TimerProgressBar* create();
	void	InitWithTarget(Node *pBase, Ref *pTarget, SEL_SCHEDULE pfnSelector, float fSeconds);
	void	update(float dt);
    void	SetBGImg(const char* texture);
	void	SetRunning(bool bRunning)	{m_bRunning = bRunning; setVisible(bRunning);}
private:
	TimerEx		m_timer;
	Node*		m_pBase;
	bool		m_bRunning;
	float		m_fHoldTime;
};


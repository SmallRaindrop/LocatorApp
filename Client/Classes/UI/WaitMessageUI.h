#pragma once

#include "cocos2d.h"

class  WaitMessageUI:public cocos2d::Layer
{
public:

	bool  init();

	void  onExit();

	void  onEnter();

	//重置超时响应时间
	inline void  reSetTimeout();


	static  WaitMessageUI * getInstance()
	{
		if(m_waitMsgPtr)
			m_waitMsgPtr = new WaitMessageUI();
		return m_waitMsgPtr;
	}

	/* 显示等待界面
	 * param: _isshow   
	 *      true:显示等待时间
	 *      false:关闭等待时间
	 * ret  :    */
	void   setShow(bool _isshow = true);

	//释放本身静态对象
	inline void   releaseFunc()
	{
		if(m_waitMsgPtr)
		{
			delete m_waitMsgPtr;
			m_waitMsgPtr = nullptr;
		}
	}

	//更新等待延迟
	void    update(float fd);

protected:
	WaitMessageUI();
	~WaitMessageUI();

private:

	static WaitMessageUI * m_waitMsgPtr;

	int                    m_timeout;                   //等待超时时间

	bool                   m_show;                      //当前是否显示
};
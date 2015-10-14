#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include "UI/CocosUI.h"
#include "Singleton.h"

class JoyStick : public Layout,public Singleton<JoyStick>
{
public:
	JoyStick();
	~JoyStick();

	bool	initialize();
	void	reset();

	void	TouchMoved(Point pos);
	bool	TouchBegan(Point pos);
	void	TouchEnded(Point pos);
	void	TouchCancelled(Point pos);

	//int					angleToDir(float angle);
	float				getAngle();
	int					getDir();
	float				getOffset();
	bool				isValidMove();


	void				update(float dt);

	inline void setValid(bool val){ m_bValid = val;}
	inline bool isValid(){ return m_bValid; }

private:
	ImageView*	m_pFrame;
	Button*		m_pBtn;
	bool		m_bValid;
	float		m_fCDTime;	// update更新时间
};

#define gJoyStick	JoyStick::Instance()

#endif
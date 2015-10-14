/****************************************************************************
 开锁UI
 彭龙华
 2015-09-16
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameUI.h"

class COpenLockKey;

class COpenLock : public GameUI
{
public:
	COpenLock();
	~COpenLock();

	virtual bool			onInit();
	virtual void			onOpen();
	virtual void			onClose();

	void					InitWithLockInfo(int nLockId);
	void					ResetLockInfo();
	void					setLockKeyRotate(COpenLockKey* pLockKey, const Point touchPoint);
	void					RotateEventPrizeKey();
	void					RotateEventLockKey();
	void					ScheduleLeftTime(float dt);

	inline int				GetLockId() { return m_nLockId; }
	inline void				SetLockId(int nId) { m_nLockId = nId; }
	inline int64			GetItemBoxId() { return m_nItemBoxId; }
	inline void				SetItemBoxId(int64 nId) { m_nItemBoxId = nId; }
	inline int				GetLeftTime() { return m_nLeftTime; }
	inline void				SetLeftTime(int nTime) { m_nLeftTime = nTime; }
	inline int				GetMaxTime() { return m_nMaxTime; }
	inline void				SetMaxTime(int nTime) { m_nMaxTime = nTime; }

	//点击关闭
	void clickCloseBtn(Ref* pSender,TouchEventType type);
	void clickLockKey(Ref* pSender,TouchEventType type);
	void clickResetBtn(Ref* pSender,TouchEventType type);
	void clickKeyBtn(Ref* pSender,TouchEventType type);
private:
	COpenLockKey*			m_prizeKey;			//开锁器
	COpenLockKey*			m_lockKey;			//开锁钥匙
	ImageView*				m_pLock;
	class Label*			m_pCountNum;						//倒计时数字
	Text*					m_pKeyNum;

	int						m_openDegreeMin;
	int						m_openDegreeMiddle;
	int						m_openDegreeMax;
	int64					m_nItemBoxId;
	int						m_nLockId;
	int						m_nLeftTime;
	int						m_nMaxTime;
};

typedef void (Ref::*RoateEvent_CallBack)();

class COpenLockKey : public Button
{
public:
	static COpenLockKey* create(const std::string& normalImage,
		const std::string& selectedImage = "",
		const std::string& disableImage = "",
		TextureResType texType = UI_TEX_TYPE_LOCAL);
public:
	COpenLockKey();
	~COpenLockKey();

	inline float			GetRotateRangeMin() { return m_fRotateRangeMin; }
	inline void				SetRotateRangeMin(float min) { m_fRotateRangeMin = min; }
	inline float			GetRotateRangeMax() { return m_fRotateRangeMax; }
	inline void				SetRotateRangeMax(float max) { m_fRotateRangeMax = max; }
	inline void				GetRotateRange(float& min, float& max) { min = m_fRotateRangeMin; max = m_fRotateRangeMax; }
	inline void				SetRotateRange(float min, float max) { m_fRotateRangeMin = min; m_fRotateRangeMax = max; }
	float					GetBoundaryRotation(float fRotation);
	inline bool				CanRotate() { return m_bRotateable; }
	inline void				SetRotateable(bool rotateable) { m_bRotateable = rotateable; }
	virtual void			setRotation(float rotation);
	void					AddRotateEvent(Ref* pListener, RoateEvent_CallBack callback);
	void					RotateEvent();
private:
	bool			m_bRotateable;
	float			m_fRotateRangeMin;
	float			m_fRotateRangeMax;
	Ref*			m_rotateEventListener;
	RoateEvent_CallBack	m_rotateEventCallBack;
};
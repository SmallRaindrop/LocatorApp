/****************************************************************************
 一笔画UI
 彭龙华
 2015-09-14
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameUI.h"
#include "GameScene/GameUILayer.h"

class CDot;
class CLine;
class CMagicLine;

class COneStroke : public GameUI
{
public:
	typedef enum _strokeZOrder
	{
		StrokeZOrder_Line,
		StrokeZOrder_MagicLine,
		StrokeZOrder_Dot,
	}StrokeZOrder;

public:
	COneStroke();
	~COneStroke();

	virtual bool			onInit();
	virtual void			onOpen();
	virtual void			onClose();
	void					InitStrokeInfo(int nStrokeId);
	void					ClearStrkeInfo();
	void					ResetStrkeInfo();
	void					FixMagicLine(const Point touchPosStart);
	void					CheckAndPaintedLine();
	void					ScheduleLeftTime(float dt);

	inline int				GetStrokeId() { return m_nStrokeId; }
	inline void				SetStrokeId(int nId) { m_nStrokeId = nId; }
	inline int				GetLeftTime() { return m_nLeftTime; }
	inline void				SetLeftTime(int nTime) { m_nLeftTime = nTime; }
	inline int				GetMaxTime() { return m_nMaxTime; }
	inline void				SetMaxTime(int nTime) { m_nMaxTime = nTime; }
	inline int64			GetItemBoxId() { return m_nItemBoxId; }
	inline void				SetItemBoxId(int64 nId) { m_nItemBoxId = nId; }

	//点击关闭
	void clickCloseBtn(Ref* pSender,TouchEventType type);
	void clickResetBtn(Ref* pSender,TouchEventType type);
	void clickKeyBtn(Ref* pSender,TouchEventType type);
	void touchEvent(Ref* pSender, TouchEventType type);

public:
	vector<CDot*>			m_dots;
	vector<CLine*>			m_lines;
	CMagicLine*				m_magicLine;
	class Label*			m_pCountNum;						//倒计时数字
	Text*					m_pKeyNum;

	int						m_nStrokeId;
	int						m_nLeftTime;
	int						m_nMaxTime;
	int64					m_nItemBoxId;
};

class CDot : public CheckBox
{
public:
	static CDot* create(const std::string& backGround,
		const std::string& backGroundSeleted,
		const std::string& cross,
		const std::string& backGroundDisabled,
		const std::string& frontCrossDisabled,
		TextureResType texType = UI_TEX_TYPE_LOCAL);

public:
	CDot() {}
	~CDot() {}

	inline float	GetRadius() { return m_fRadius; }
	inline void		SetRadius(float fRadius) { m_fRadius = fRadius; }
	bool			ContainPoint(const Point& pos);

private:
	float			m_fRadius;
};

class CLine : public ImageView
{
public:
	static CLine* create(	Point posStart,
							Point posEnd,
							const std::string& normalImg,
							const std::string& SelectedImg,
							TextureResType texType = UI_TEX_TYPE_LOCAL);
public:
	CLine();
	~CLine();

	bool			init(	Point posStart,
							Point posEnd,
							const std::string& normalImg,
							const std::string& SelectedImg,
							TextureResType texType = UI_TEX_TYPE_LOCAL);

	inline bool		IsPainted() { return m_bPainted; }
	inline void		SetPainted(bool bPainted) { m_bPainted = bPainted; OnPainted(); }
	void			OnPainted();

	inline Point	GetPosStart() { return m_posStart; }
	inline void		SetPosStart(const Point& pos) { m_posStart = pos; UpdateProperty(); if(IsPainted()){UpdatePropertySelected();} }
	inline Point	GetPosEnd() { return m_posEnd; }
	inline void		SetPosEnd(const Point& pos) { m_posEnd = pos; UpdateProperty(); if(IsPainted()){UpdatePropertySelected();} }
	bool			ContainPos(const Point pos1,const Point pos2);

private:
	void			UpdateProperty();
	void			UpdatePropertySelected();

private:
	ImageView*			m_pSelectedImage;
	bool				m_bPainted;
	Point				m_posStart;
	Point				m_posEnd;
};

class CMagicLine : public CLine
{
public:
	static CMagicLine* create(	Point posStart,
		Point posEnd,
		const std::string& normalImage,
		const std::string& selectedImage,
		TextureResType texType = UI_TEX_TYPE_LOCAL );
public:
	CMagicLine();
	~CMagicLine() {}

	inline bool			IsStartFixed() { return m_bStartFixed; }
	inline void			SetStartFixed(bool fixed) { m_bStartFixed = fixed; setEnabled(fixed); }

	void				RunBlinkAction();
private:
	bool			m_bStartFixed;
};
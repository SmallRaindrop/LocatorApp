#pragma once
#include "GameDef.h"
#include "UI/CocosUI.h"

class CScrollBar : public Widget
{
public:
	CScrollBar();
	~CScrollBar();

	static CScrollBar* create(ScrollView* listUI,std::string BottomID = "ScrollBarB",std::string TopID = "ScrollBarT");

	bool	init(ScrollView* listUI,std::string BottomID,std::string TopID);

	static CScrollBar* createWithFile(ScrollView* listUI,std::string BottomID,std::string TopID, TextureResType _type = UI_TEX_TYPE_LOCAL);

	bool	initWithFile(ScrollView* listUI,std::string BottomID,std::string TopID, TextureResType _type = UI_TEX_TYPE_LOCAL);

	void	setBarPosY(float pecent);
	void	setBarSize(float pecent);
	void	update(float delta);

private:
	ImageView*	m_pBarBottom;
	ImageView*	m_pBarTop;
	Layout*		m_ScrollContainer;
	float		m_fPosY;
	float		m_fTopHeight;
	float		m_fContainerHeight;
};
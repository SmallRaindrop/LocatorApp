#pragma once
#include "GameDef.h"
#include "UI/CocosUI.h"

class PageNum :public Widget
{
public:
	PageNum(void);
	~PageNum(void);

	static PageNum* create()
	{
		PageNum* rw = new PageNum();
		if(rw && rw->init())
		{
			rw->autorelease();
			return rw;
		}
		CC_SAFE_DELETE(rw);
		return NULL;
	}

	bool init();
	void setPageNum(int nPageNum);
	void turnToPage(int index);

private:
	class RadioButtonSet*	m_pPageSigns;
	Text*					m_pPageNum;
	int						m_nPageSum;
};


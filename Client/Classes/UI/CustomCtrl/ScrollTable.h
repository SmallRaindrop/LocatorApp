#pragma once
#include "UI/CocosUI.h"
#include "UI/ResMgr/CtrlAllocator.h"
#include "UI/CustomCtrl/ScrollList.h"

using std::vector;

//typedef void (CCObject::*SEL_SelectIndexEvent)(int, int64);

enum Table_Column_Type
{
	TCT_NONE = -99,
	TCT_STRING = 1,
	TCT_IMAGE,
	TCT_ANIMATION,
	TCT_BUTTON,
	TCT_CHECKBOX,
	TCT_NODE_PTR,
};

struct Format_Item
{
	Table_Column_Type	type;
	int					nOffsetX;
	Point				nAnchorPoint;
};

class CScrollTable :public CScrollList
{
public:
	CScrollTable(void);
	~CScrollTable(void);
    static CScrollTable* create(bool bItemSelectable, string strItemBGID)
	{
		CScrollTable* rw = new CScrollTable();
		if(rw && rw->init())
		{
			rw->m_bItemSelectable = bItemSelectable;
			rw->m_nItemBGID = strItemBGID;
			rw->setDirection(SCROLLVIEW_DIR_VERTICAL);
			rw->setBounceEnabled(true);
			rw->autorelease();
			return rw;
		}
		CC_SAFE_DELETE(rw);
		return NULL;
	}
	void			SetFormat(Table_Column_Type col1, int nOffsetX, double ptAnchorPointX, double ptAnchorPointY, ...);
	vector<Node*>	AddRow(long long nUserData = 0, ...);

private:
	vector<Format_Item>		m_vtrFormatItems;
};

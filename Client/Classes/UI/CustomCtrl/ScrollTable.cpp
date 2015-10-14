#include "ScrollTable.h"
#include "ui/UIText.h"
#include "ui/UIButton.h"


CScrollTable::CScrollTable(void)
{
}


CScrollTable::~CScrollTable(void)
{
}

// 类型，横向偏移，锚点； 类型，横向偏移，锚点...
void CScrollTable::SetFormat(Table_Column_Type col1, int nOffsetX, double ptAnchorPointX, double ptAnchorPointY, ...)
{
	va_list list;
	va_start(list, ptAnchorPointY);

	Format_Item item = {col1, nOffsetX, Point(ptAnchorPointX, ptAnchorPointY)};

	m_vtrFormatItems.clear();
	m_vtrFormatItems.push_back(item);

	while (true)
	{
		item.type = Table_Column_Type(va_arg(list, int));
		if (item.type == TCT_NONE)
			break;

		item.nOffsetX = va_arg(list, int);
		item.nAnchorPoint.x = va_arg(list, double);
		item.nAnchorPoint.y = va_arg(list, double);

		m_vtrFormatItems.push_back(item);
	}

}

vector<Node*> CScrollTable::AddRow(long long nUserData, ...)
{
	va_list list;
	va_start(list, nUserData);
	vector<Node*> vtrRowElem;

	Widget *pRow = AddItem("", nUserData);

	for (size_t i = 0; i < m_vtrFormatItems.size(); i++)
	{
		char *pRes = va_arg(list, char*);

		Node *pColItem = NULL;
		static Node *pLastColItem = NULL;
		switch (m_vtrFormatItems[i].type)
		{
		case TCT_STRING:
			pColItem = Text::create(pRes, "Helvetica", m_nFontSize);
			pColItem->setColor(getColor());
			if (!m_bTextShadow)((Label*)((Text*)pColItem)->getVirtualRenderer())->disableEffect();
			break;
		case TCT_IMAGE:
		case TCT_BUTTON:
		case TCT_CHECKBOX:
			pColItem = gCtrlAllocator->LoadCtrl(pRes);
			break;
		case TCT_NODE_PTR:
			pColItem = (Node*)pRes;
			break;
		case TCT_ANIMATION:
			{
				pColItem = Sprite::create();
			}
			break;
        default:
            break;
		}

		if (pColItem)
		{
			int nPosX = m_vtrFormatItems[i].nOffsetX;
			if (m_vtrFormatItems[i].nOffsetX == -1 && pLastColItem)
			{
				nPosX = pLastColItem->getPositionX() + pLastColItem->getContentSize().width * (1 - pLastColItem->getAnchorPoint().x);
			}
			pColItem->setPosition(nPosX, pRow->getSize().height / 2);
			pColItem->setAnchorPoint(m_vtrFormatItems[i].nAnchorPoint);
			pRow->addChild(pColItem);

		}
		vtrRowElem.push_back(pColItem);		// 空的指针也要加入，为了给外界固定索引
		pLastColItem = pColItem;
	}

	return vtrRowElem;
}



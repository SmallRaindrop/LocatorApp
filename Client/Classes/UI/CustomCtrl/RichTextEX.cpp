#include "RichTextEX.h"
#include "UnderLinedText.h"
#include "../../Common/CommonDef.h"


RichTextEx::RichTextEx(void) : m_bLinkTouchable(), m_fFontSize(40), m_clrLinkColor(Color3B::WHITE),
	m_pClickListenner(), m_pClickHandler(),m_nCurOptLink(0), m_bAppend()
{
}


RichTextEx::~RichTextEx(void)
{
}

void RichTextEx::SetContent(const char* strFormat, ...)
{
	if (!m_bAppend)
		removeAllElements();
	ParseFormat(strFormat);

	va_list l;
	va_start(l, strFormat);

	size_t i = 0;

	for (i = 0; i < m_vtrLinkTextSeg.size(); i++)
	{
		RichElement* pRM = NULL;
		pRM = RichElementText::create(i, _color, 255, m_vtrCommTextSeg[i].c_str(), Default_Font_File, m_fFontSize);
		pushBackElement(pRM);

		// 本类只能显示文字，不支持图片等
		Text *pLink = Text::create("", "Helvetica", m_fFontSize);	

		pLink->setFontSize(m_fFontSize);
		pLink->setColor(m_vtrLinkTextSeg[i].color);

		string strLink;
		switch (m_vtrLinkTextSeg[i].type)
		{
		case LT_INT:
			m_vtrLinkTextSeg[i].nData = va_arg(l, int);
			strLink = (CCString::createWithFormat("%d", (int)m_vtrLinkTextSeg[i].nData)->getCString());

			break;
		case LT_LINT:
			m_vtrLinkTextSeg[i].nData = va_arg(l, long);
			strLink = (CCString::createWithFormat("%ld", (long)m_vtrLinkTextSeg[i].nData)->getCString());
			break;
		case LT_LLINT:
			m_vtrLinkTextSeg[i].nData = va_arg(l, long long);
			strLink = (CCString::createWithFormat("%lld", (long long)m_vtrLinkTextSeg[i].nData)->getCString());
			break;
		case LT_STRING:
			m_vtrLinkTextSeg[i].nData = *(int*)va_arg(l, char*);
			strLink = ((const char*)(int)m_vtrLinkTextSeg[i].nData);
			break;
		case LT_FLOAT:
			m_vtrLinkTextSeg[i].nData = va_arg(l, float);
			strLink = (CCString::createWithFormat("%f", m_vtrLinkTextSeg[i].nData)->getCString());
			break;
		case LT_USERDEF:
			m_vtrLinkTextSeg[i].nData = *(int*)va_arg(l, void*);
			strLink = (((UserDef_Link*)(int)m_vtrLinkTextSeg[i].nData)->strText);
			break;
		}

		if (m_vtrLinkTextSeg[i].bUnderlined)
		{
			pLink = UnderlinedText::create(strLink.c_str());
		}
		else
		{
			pLink->setText(strLink.c_str());
		}

		pLink->setTag(i);
		pLink->setFontSize(m_fFontSize);
		pLink->setColor(m_vtrLinkTextSeg[i].color);
		pLink->addTouchEventListener(this, SEL_TouchEvent(&RichTextEx::ClickLink));
		pRM = RichElementCustomNode::create(i, m_vtrLinkTextSeg[i].color, 255, pLink);
		pushBackElement(pRM);
	}

	if (m_vtrCommTextSeg.size() > i)
	{
		pushBackElement(RichElementText::create(i, _color, 255, m_vtrCommTextSeg[i].c_str(),Default_Font_File, m_fFontSize));
	}
}

void RichTextEx::InsertArgument1ByOne(Link_Data* pFirst,bool bColorful)
{
	if ((int)m_vtrLinkTextSeg.size() <= m_nCurOptLink)
	{
		m_vtrLinkTextSeg.resize(m_nCurOptLink + 1);
	}
	m_vtrLinkTextSeg[m_nCurOptLink].type = pFirst->type;
	m_vtrLinkTextSeg[m_nCurOptLink].color = pFirst->color;
	m_vtrLinkTextSeg[m_nCurOptLink].bUnderlined = pFirst->bUnderlined;
	m_vtrLinkTextSeg[m_nCurOptLink].nData = pFirst->nData;
	m_vtrLinkTextSeg[m_nCurOptLink].strText = pFirst->strText;

	RichElement* pRM = NULL;
	if (!bColorful)
	{
		pRM = RichElementText::create(2 * m_nCurOptLink, _color, 255, m_vtrCommTextSeg[m_nCurOptLink].c_str(), Default_Font_File, m_fFontSize);
		pushBackElement(pRM);
	}

	const char* strLink = pFirst->strText.c_str();

	if (*strLink == 0)
	if (!bColorful)
	{
		switch (m_vtrLinkTextSeg[m_nCurOptLink].type)
		{
		case LT_INT:
			strLink = (CCString::createWithFormat("%f", m_vtrLinkTextSeg[m_nCurOptLink].nData)->getCString());
			break;
		case LT_LINT:
			strLink = (CCString::createWithFormat("%f", m_vtrLinkTextSeg[m_nCurOptLink].nData)->getCString());
			break;
		case LT_LLINT:
			strLink = (CCString::createWithFormat("%f", m_vtrLinkTextSeg[m_nCurOptLink].nData)->getCString());
			break;
		case LT_STRING:
			strLink = ((const char*)(int)m_vtrLinkTextSeg[m_nCurOptLink].nData);
			break;
		case LT_FLOAT:
			strLink = (CCString::createWithFormat("%f", m_vtrLinkTextSeg[m_nCurOptLink].nData)->getCString());
			break;
		case LT_USERDEF:
			strLink = (((UserDef_Link*)(int)m_vtrLinkTextSeg[m_nCurOptLink].nData)->strText);
			break;
		}
	}

	// 本类只能显示文字，不支持图片等
	if (m_vtrLinkTextSeg[m_nCurOptLink].bUnderlined)
	{
		Text *pLink = Text::create("", "Helvetica", m_fFontSize);
		pLink = UnderlinedText::create(strLink);
		((UnderlinedText*)pLink)->setFontSize(m_fFontSize);	// 非虚函数
		pLink->setTag(m_nCurOptLink);
		pLink->setColor(m_vtrLinkTextSeg[m_nCurOptLink].color);
		pLink->addTouchEventListener(this, SEL_TouchEvent(&RichTextEx::ClickLink));
		pRM = RichElementCustomNode::create(2 * (m_nCurOptLink + 1), m_vtrLinkTextSeg[m_nCurOptLink].color, 255, pLink);
		pushBackElement(pRM);
	}
	else
	{
		pushBackElement(RichElementText::create(2 * (m_nCurOptLink + 1), m_vtrLinkTextSeg[m_nCurOptLink].color, 255, strLink, Default_Font_File, m_fFontSize));
	}

	++m_nCurOptLink;
	if (m_vtrLinkTextSeg.size() == m_nCurOptLink && (int)m_vtrCommTextSeg.size() > m_nCurOptLink && !bColorful)
	{
		pushBackElement(RichElementText::create(2 * m_nCurOptLink, _color, 255, m_vtrCommTextSeg[m_nCurOptLink].c_str(), Default_Font_File, m_fFontSize));
	}
}

void RichTextEx::InsertArguments(Link_Data* pFirst, ...)
{
	va_list l;
	va_start(l, pFirst);

	for (size_t i = 0; i < m_vtrLinkTextSeg.size(); i++)
	{
		Link_Data* pData = (i == 0 ? pFirst : va_arg(l, Link_Data*));
		InsertArgument1ByOne(pData);
	}
}

void RichTextEx::ParseFormat(const char* strFormat)
{
	m_vtrCommTextSeg.clear();
	m_vtrLinkTextSeg.clear();

	const char* pCommTextStart = strFormat;
	const char* pCommTextEnd = strFormat;
	while (*strFormat)
	{
		if (*strFormat == '%')
		{
			LinkType type = LT_INT;
			pCommTextEnd = strFormat;
			switch (*(strFormat + 1))
			{
			case 'd':
				type = LT_INT;
				break;
			case 's':
				type = LT_STRING;
				break;
			case 'f':
				type = LT_FLOAT;
				break;
			case 'l':
                {
                    if (*(strFormat+2) == 'd') {
                        type = LT_LINT;
                    }
                    else if(*(strFormat+2) == 'l' && *(strFormat+3) == 'd')
                    {
                        type = LT_LLINT;
                    }
                }
				break;
			default:
				pCommTextEnd = pCommTextStart - 1;
                break;
			}
            
			if (pCommTextEnd >= pCommTextStart)
			{
				string strTmp(pCommTextStart, pCommTextEnd);
				Link_Data link = {type, m_clrLinkColor, false, 0};
				m_vtrCommTextSeg.push_back(strTmp);
				m_vtrLinkTextSeg.push_back(link);

				pCommTextStart = strFormat + 2;
				pCommTextEnd = pCommTextStart;

				strFormat++;
			}
		}

		strFormat++;
	}

	string strTmp(pCommTextStart, strFormat);
	m_vtrCommTextSeg.push_back(strTmp);
}

void RichTextEx::SetFormatString(const char* strFormat)
{
	removeAllElements();
	ParseFormat(strFormat);
	m_nCurOptLink = 0;

	// 如果没有连接文字，则后续也就不会插入链接，也就没有了普通文字的显示，这里加上
	if (m_vtrLinkTextSeg.size() == 0)
	{
		pushBackElement(RichElementText::create(0, _color, 255, strFormat, Default_Font_File, m_fFontSize));
	}
}

void RichTextEx::SetClickLinkEvent(Ref* pListenner, SEL_ClickLinkEvent pHandler)
{
	m_pClickListenner = pListenner;
	m_pClickHandler = pHandler;
}

void RichTextEx::ClickLink(Ref* pSender, TouchEventType)
{
	if (m_pClickListenner && m_pClickHandler)
	{
		int nIndex = ((Node*)pSender)->getTag();
		(m_pClickListenner->*m_pClickHandler)(nIndex, &m_vtrLinkTextSeg[nIndex]);
	}
}

void RichTextEx::ParseAndLayout(const string& str)
{
	if (!m_bAppend)
		removeAllElements();

	m_vtrCommTextSeg.clear();
	m_vtrLinkTextSeg.clear();

	m_nCurOptLink = 0;

	_makeLinkData(str);

	if (m_vtrLinkTextSeg.size() == 0)
	{
		SetContent(str.c_str());
	}
	else
	{
		for (size_t i=0; i<m_vtrLinkTextSeg.size(); ++i)
		{
			InsertArgument1ByOne(&m_vtrLinkTextSeg[i],true);
		}
	}

	formatText();
}

void RichTextEx::_makeLinkData(const string& str,size_t pos)
{
	if (pos > str.length()-1) {return;} 

	size_t posStart=pos,posEnd = pos;

	string text;
	string colorCfg;


	posStart = str.find("<C=",posStart);
	if (posStart == string::npos)
	{
		posStart=pos;
		posStart = str.find("<c=",posStart);
	}

	if (posStart == string::npos)
	{
		Link_Data link;
		link.type = LT_STRING;
		link.bUnderlined = false;
		link.color = getColor();
		link.strText = str.substr(pos,str.length()-pos);
		m_vtrLinkTextSeg.push_back(link);
	}
	else if (posStart!=pos && posStart!=string::npos)
	{
		Link_Data link;
		link.type = LT_STRING;
		link.bUnderlined = false;
		link.color = getColor();
		link.strText = str.substr(pos,posStart-pos);
		m_vtrLinkTextSeg.push_back(link);
		_makeLinkData(str,posStart);
	}
	else
	{
		Link_Data link;
		link.type = LT_STRING;
		link.bUnderlined = false;

		posEnd = str.find_first_of(">",posStart);
		if(posEnd == string::npos) return;
		colorCfg = str.substr(posStart+3,posEnd-posStart-3);
		vector<int> rgb;
		StringSplitToInt(colorCfg,",",rgb);
		link.color = Color3B(rgb[0],rgb[1],rgb[2]);
		posStart = posEnd+1;

		posEnd = str.find("</",posStart);
		if(posEnd == string::npos) return;
		link.strText = str.substr(posStart,posEnd-posStart);
		m_vtrLinkTextSeg.push_back(link);
		posStart = posEnd+1;

		posEnd = str.find_first_of(">",posStart);
		if(posEnd == string::npos) return;
		posStart = posEnd+1;

		_makeLinkData(str,posStart);
	}
}


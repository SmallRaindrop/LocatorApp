#pragma once
#include "GameDef.h"
#include "UI/CocosUI.h"

class RichTextEx : public RichText
{
public:
	enum LinkType
	{
		LT_INT,
		LT_LINT,
		LT_LLINT,
		LT_STRING,
		LT_FLOAT,
		LT_USERDEF
	};
	struct UserDef_Link
	{
		const char* strText;
		int64 nReserved;
	};

	struct Link_Data
	{
		LinkType	type;
		Color3B		color;
		bool		bUnderlined;
		double		nData;
		string		strText;	// 如果直接给文本，上面的nData就不读取了
	};

	typedef void (CCObject::*SEL_ClickLinkEvent)(int, struct RichTextEx::Link_Data*);

public:
	RichTextEx(void);
	~RichTextEx(void);
    static RichTextEx* create()
	{
		RichTextEx* rw = new RichTextEx();
		if(rw && rw->init())
		{
			rw->autorelease();
			return rw;
		}
		CC_SAFE_DELETE(rw);
		return NULL;
	}
	virtual void ClickLink(Ref*, TouchEventType);
	void		 SetClickLinkEvent(Ref*, SEL_ClickLinkEvent);
	void		 SetLinkTouchable(bool b)	{m_bLinkTouchable = b;}
	void		 SetLinkColor(Color3B color)	{m_clrLinkColor = color;}
	void		 SetFontSize(float nFontSize){m_fFontSize = nFontSize;}
	void		 SetContent(const char* strFormat, ...);
	void		 SetFormatString(const char* strFormat);
	void		 InsertArguments(Link_Data*, ...);
	void		 InsertArgument1ByOne(Link_Data*,bool bColorful=false);
	void		 ParseFormat(const char* strFormat);
	void		 ParseAndLayout(const string& str);
	void		 AppendMode(bool bAppend)	{m_bAppend = bAppend;}

private:
	void		 _makeLinkData(const string& str,size_t pos=0);
protected:
	Color3B				m_clrLinkColor;
	float				m_fFontSize;
	bool				m_bAppend;
	bool				m_bLinkTouchable;
	vector<string>		m_vtrCommTextSeg;
	vector<Link_Data>	m_vtrLinkTextSeg;
	int					m_nCurOptLink;

	Ref*				m_pClickListenner;
	SEL_ClickLinkEvent	m_pClickHandler;
};


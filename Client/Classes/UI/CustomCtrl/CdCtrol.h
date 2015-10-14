#pragma once
#include "GameDef.h"
#include "UI/CocosUI.h"
#include "CommonDef.h"

#define Child_Cd_Tag			(10)

class CdCtrol :public Widget
{
public:
	CdCtrol(const std::string& path);
	~CdCtrol(void);

	/* Name		：CdCtrol::create
	 * Author	：PengLongHua
	 * Date		: 2015-07-20
	 * Desc		: 创建CD控件
	 * Param	: none
	 * Return	: CdCtrol
	 */
    static CdCtrol* create(const std::string& path)
	{
		CdCtrol* rw = new CdCtrol(path);
		if(rw)
		{
			rw->autorelease();
			return rw;
		}
		CC_SAFE_DELETE(rw);
		return NULL;
	}

	/* Name		：CdCtrol::create
	 * Author	：PengLongHua
	 * Date		: 2015-07-20
	 * Desc		: 创建CD控件
	 * Param	: CdTime：cd剩余时间，CdTimeTotal：cd总时间,时间单位:毫秒
	 * Return	: CdCtrol
	 */
    static CdCtrol* create(int CdTime,int CdTimeTotal)
	{
		CdCtrol* rw = new CdCtrol(skill_cd_path);
		if(rw)
		{
			rw->autorelease();
			rw->SetCd(CdTime,CdTimeTotal);
			return rw;
		}
		CC_SAFE_DELETE(rw);
		return NULL;
	}
		
	void			SetCd(int CdTime,int CdTimeTotal);
	void			EndCd();
	virtual void	setSize(const Size &size);
	inline float	GetLeftTime() { return m_fCdTime*1000; }
	void			update(float dt);

private:
	ProgressTimer*		m_Timer;
	Text*				m_pCdTime;
	float				m_fCdTime;
	std::string			m_cdFilePath;
};


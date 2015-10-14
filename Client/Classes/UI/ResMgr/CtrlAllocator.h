#ifndef __CTRLALLOCATOR__
#define __CTRLALLOCATOR__

#include <vector>
#include <map>
#include <string>
#include "Singleton.h"
#include "ui/CocosUI.h"

USING_NS_CC;
using std::map;
using std::string;

/************************************************************************/
/* 通用资源加载类，把一些零散的碎图整合到一个UI界面里面方面获取
/************************************************************************/
class CCTrlAllocator : public Singleton<CCTrlAllocator>
{
public:
	CCTrlAllocator();
	~CCTrlAllocator();

	bool Initialize();
	void Release();

	Widget* LoadCtrl(const string &name);
private:
	map <string, Widget*>	m_mpTemplateCtrls;
	Widget*					m_pContainer;
};


#define gCtrlAllocator CCTrlAllocator::Instance()

#endif
#include "CtrlAllocator.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/UIImageView.h"
#include "GUI/CCControlExtension/CCScale9Sprite.h"
#include "cocostudio/CCActionManagerEx.h"
#include "cocostudio/WidgetReader/LayoutReader/LayoutReader.h"
#include "cocostudio/WidgetReader/ButtonReader/ButtonReader.h"
#include "cocostudio/WidgetReader/TextReader/TextReader.h"
#include "cocostudio/WidgetReader/ImageViewReader/ImageViewReader.h"
#include "cocostudio/WidgetReader/TextBMFontReader/TextBMFontReader.h"
#include "cocostudio/WidgetReader/TextFieldReader/TextFieldReader.h"

using namespace cocostudio;
using namespace extension;

CCTrlAllocator::CCTrlAllocator(): m_pContainer()
{
	Initialize();
}

CCTrlAllocator::~CCTrlAllocator()
{
	Release();
}

bool CCTrlAllocator::Initialize()
{
	m_pContainer = GUIReader::getInstance()->widgetFromJsonFile("assets/ui/CustomCtrls.json");
	CC_SAFE_RETAIN(m_pContainer);

	Vector<Node*> chl = m_pContainer->getChildren();
	for (int i = 0; i < chl.size(); i++)
	{
		Widget *pWidget = (Widget*)chl.at(i);
		m_mpTemplateCtrls.insert(std::make_pair(pWidget->getName(), pWidget));

		// 如果是图片，则有可能很大，游戏开始一次性全部加在会占用太大内存，这里将图片数据清除，只保留逻辑数据
		if (dynamic_cast<ImageView*> (pWidget))
		{
			ImageView* pImg = (ImageView*)pWidget;
			if (pImg->isScale9Enabled())
			{
				//((Scale9Sprite*)pImg->getVirtualRenderer())->initWithBatchNode(NULL, Rect::ZERO, Rect::ZERO);
			}
			else
			{
				((Sprite*)pImg->getVirtualRenderer())->setTexture(NULL);
			}
		}
	}

	return true;
}

void CCTrlAllocator::Release()
{
	if (m_pContainer)
	{
		m_pContainer->removeAllChildren();
		CC_SAFE_RELEASE(m_pContainer);
	}

	//delete LayoutReader::getInstance();
	//delete ButtonReader::getInstance();
	//delete TextReader::getInstance();
	//delete ImageViewReader::getInstance();
	//delete TextBMFontReader::getInstance();
	//delete TextFieldReader::getInstance();
	//
	
}

Widget* CCTrlAllocator::LoadCtrl(const string &name)
{
	map <string, Widget*>::iterator it = m_mpTemplateCtrls.find(name);
	if (it != m_mpTemplateCtrls.end())
	{
		Widget *pClone = it->second->clone();
		pClone->setPosition(Point::ZERO);
		//pClone->removeFromParent();
		return pClone;
	}

	return NULL;
}
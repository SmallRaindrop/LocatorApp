#ifndef __GameUILayer_h_
#define __GameUILayer_h_

#include "GameDef.h"
#include "Common/CommonDef.h"
#include "Singleton.h"
#include "UI/GameUI.h"

typedef map<int,GameUI*>	UITable;
typedef map<int,UICreator*> UICreators;
typedef map<int,int>		UITogetherTable;

class CGameUILayer : public Layer,public Singleton<CGameUILayer>
{
public:
	CGameUILayer();
	~CGameUILayer();

	virtual bool initialize();
	virtual void release();

	void update(float delta);

	void		registerUI(int idu,UICreator* pUICreator);
	UICreator*	getUICreator(int idu);

	GameUI*		createUI(int idu);
	GameUI*		getUI(int idu,bool bNew = true);

	GameUI*		getActiveUI(int idu);
	bool		isActive(int idu);
	bool		isActive(GameUI* pUI);

	void show(int idu);
	void show(GameUI* pUI);

	// 打开对话框
	GameUI* open(int idu);
	void open(GameUI* pUI);
	void openTogetherUI(int idu);

	// 关闭对话框
	void close(int idu);
	void close(GameUI* pUI);
	void closeTogetherUI(int idu);
	void closeOtherUIs();

	void destroyUI(int idu);
	void destroyUI(GameUI* pUI);
	void destroyUI();

private:
	UITable				m_UITable;
	UICreators			m_UICreators;
	UITogetherTable		m_UITogetherTable;
};

#define gGameUILayer CGameUILayer::Instance()

inline Point getPositionInUILayer(Widget *pW)
{
	return gGameUILayer->convertToNodeSpace(pW->getWorldPosition());
    //return convertToOneParentSpace(pW, gGameUILayer, Point(pW->getAnchorPoint().x * pW->getContentSize().width, pW->getAnchorPoint().y * pW->getContentSize().height));
}

inline Point getPositionInUILayer(Point worldPos)
{
	Point pos;
	pos.x = worldPos.x*GAME_UI_ORIG_SIZE.width/gDirector->getVisibleSize().width;
	pos.y = worldPos.y*GAME_UI_ORIG_SIZE.height/gDirector->getVisibleSize().height;
	return pos;
	//return convertToOneParentSpace(pW, gGameUILayer, Point(pW->getAnchorPoint().x * pW->getContentSize().width, pW->getAnchorPoint().y * pW->getContentSize().height));
}


#define Menu_Zorder		9999
#define Menu_Tag		1501
#define Menu4Player_Tag	1502
#define Menu4Achievement_Tag	1503
#define Menu4MatchMode_Tag	1504

#define gMenuInst ((CMenu*)gGameUILayer->getChildByTag(Menu_Tag))

#endif // __GameUILayer_h_
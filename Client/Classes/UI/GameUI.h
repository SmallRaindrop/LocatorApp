#ifndef __GameUI_h_
#define __GameUI_h_

#include "GameDef.h"
#include "ui/UIWidget.h"
#include "GameUIDef.h"
#include "ui/UIText.h"
#include "ui/UITextAtlas.h"
#include "ui/UIButton.h"
#include "ui/UILayout.h"
#include "ui/UIImageView.h"
#include "ui/UITextField.h"
#include "ui/UIPageView.h"
#include "ui/UIListView.h"
#include "ui/UIScrollView.h"
#include "ui/UICheckBox.h"
#include "UILoadingBar.h"
#include "CocosUI.h"
#include "CustomCtrl/CustomCtrl.h"
#include "effect.h"
#include "UIHelper.h"
#include "CommonDef.h"
#include "DataPool.h"
#include "CommonUI.h"

using namespace ui;

class GameUI;
class UICreator
{
public:
    UICreator(){}
    virtual ~UICreator(){}
	virtual GameUI*		createUI() = 0;
};

class GameUI : public Layer
{
public:
	static void CenterWidget(Widget* pWidget);
	static void RightWidget(Widget* pWidget);
	static void LeftWidget(Widget* pWidget);

public:
	GameUI(int idu,const std::string& strJsonFile);
	virtual ~GameUI();

	inline int			getIDU()	{ return m_IDU; }
	inline Widget*		getWidget()	{ return m_pWidget; }
	inline int			getState()	{ return m_nState; }
	inline void			setState(int state){ m_nState = state; }
	void				doModel();
	void				unDoModel();
	bool				isModal();

	virtual bool init();
	virtual void update(float dt);
	virtual bool onInit();
	virtual void onOpen() {};
	virtual void onShow() {};
	virtual void onClose(){};
	virtual void onDestroy(){};

public:
	static void		registerUIjson(int idu,string json);
	static string	getUIjson(int idu);

protected:
	int			m_IDU;
	Widget*		m_pWidget;
	int			m_nState;
	Layout*		m_pModel;

	EffectList	m_effects;

	typedef map<int,string> UI_JSON_MAPPING;

	static UI_JSON_MAPPING s_ui_json_mapping;
};

//
template <class T>
class UICreator_T : public UICreator
{
public:
	GameUI* createUI(){
		GameUI* pUI = new T;
		if ( pUI && pUI->init() )
		{
			return pUI;
		}

		CC_SAFE_DELETE(pUI);
		return NULL;
	}
};
#endif

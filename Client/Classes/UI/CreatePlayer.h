#pragma once
#include "GameDef.h"
#include "GameUI.h"
#include "CustomCtrl/RadioButtonSet.h"
#include "RoleModel.h"

RoleModel* createModelByPlayer(int career, int sex);

class CCreatePlayer : public GameUI
{
public:
	CCreatePlayer();
	~CCreatePlayer();

	bool			onInit();
	void			onOpen();

	void			SetRandomName();
	void			ShowCareerModel();

	void			update(float dt);

	void			clickCareerSel(int index);
	void			clickSexSel(int index);
	void			clickRandom(Ref* pSender, TouchEventType type);
	void			clickCreate(Ref* pSender, TouchEventType type);
	void			clickBack(Ref* pSender, TouchEventType type);
	void			clickMale(Ref* pSender, TouchEventType type);
	void			clickFemale(Ref* pSender, TouchEventType type);

	void            onEnter();

	void            onExit();

	/**
	 * Name : showFace
	 * Des  : 改变界面显示
	 */
	void           showFace();

	/**
	 * Name : setHeroImag
	 * Des  : 设置英雄显示图片
	 * Param: _career  职业
	 *        _sex     性别 1默认是男人
	 */
	void            setHeroImag(int _career, int _sex = 1);


	/**
	 * Name : clickCallBack
	 * Des  : 界面按钮回调函数
	 */
	void            clickCallBack(Ref* pSender, TouchEventType type);


	/**
	 * Name : clickListHero
	 * Des  : 点击list英雄回调函数
	 */
	void            clickListHero(Ref* pSender, TouchEventType type);

	CREATE_FUNC(CCreatePlayer);

private:
	int				m_career;
	int				m_sex;
	TextField*		m_pName;


	string			m_name;
	RadioButtonSet*	m_pCareerSel;
	RadioButtonSet*	m_pSexSel;
	CheckBox*		m_pMaleBtn;
	CheckBox*		m_pFemaleBtn;
	CheckBox*		m_pCareerZS;
	CheckBox*		m_pCareerFS;
	CheckBox*		m_pCareerGJ;
	ImageView*		m_pCareerTxt[3];
	ImageView*		m_pPower[3];
	Text*			m_pPowerTxt;

	Point			m_pZSPos;
	Point			m_pFSPos;
	Point			m_pGJPos;

	RoleModel*		m_pModel;
};
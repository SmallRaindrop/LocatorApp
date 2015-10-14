#pragma once
#include "GameUI.h"
#include "CustomCtrl/RichTextEX.h"
#include <functional>

typedef void (Ref::*YESORNO_EVENT)(bool bYesOrNO);
typedef void (*PURE_YESORNO_EVENT)(bool bYesOrNO);


class CMessageBoxUI : public GameUI
{
public:
	enum MsgBox_Mode
	{
		MBM_OK,
		MBM_YESNO
	};

	enum Scene_Type
	{
		Scene_Login = 0,
		Scene_Game
	};
public:
	CMessageBoxUI();
	~CMessageBoxUI();
	static void Show(MsgBox_Mode mode, const char* strMsg, const char* strButtonText1 = NULL, const char* strButtonText2 = NULL, 
					Ref *pListennerYes = NULL, YESORNO_EVENT pHandlerYes = NULL, Widget *pPlugin = NULL, Scene_Type sceneType = Scene_Game);

	//add Tangbo
	static void Show(MsgBox_Mode mode, const char* strMsg, const std::function<void(bool)>& pHandlerYes, const char* strButtonText1 = NULL, const char* strButtonText2 = NULL, 
		Ref *pListennerYes = NULL,  Widget *pPlugin = NULL, Scene_Type sceneType = Scene_Game);

	bool		onInit();
	void		onClose();

	void		clickBtnClose(Ref *pSender, TouchEventType type);
	void		clickBtnConfirm(Ref *pSender, TouchEventType type);
	void		clickBtn(Ref *pSender, TouchEventType type);
	void		SetInfo(MsgBox_Mode mode, const char* strMsg, Ref *pListenner, YESORNO_EVENT pHandler);
	void		SetInfo(MsgBox_Mode mode, const char* strMsg, Ref *pListenner,const std::function<void(bool)>& pHandler);   //add Tangbo
	void		AddPlugin(Widget *pPlugin);


private:
	RichTextEx*			m_pRichText;
	Text*				m_pMsgText;
	Button*				m_pBtnConfirm;	string m_strTextConfirm;
	Button*				m_pYes;			string m_strTextYes;
	Button*				m_pNo;			string m_strTextNo;
	Widget*				m_pPlugin;

	MsgBox_Mode			m_mode;

	Ref *				m_pListenner;
	YESORNO_EVENT		m_pHandler;
	PURE_YESORNO_EVENT	m_pPureHandler;	
	std::function<void(bool)> m_pFunction;
};
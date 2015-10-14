#include "MessageBoxUI.h"
#include "GameUIDef.h"
#include "GameScene/GameUILayer.h"
#include "UIHelper.h"
#include "GameScene/LoginScene.h"

CMessageBoxUI::CMessageBoxUI() 
	:GameUI(IDU_MESSAGEBOX,JSONFILE_MESSAGEBOXUI)
{
	m_pPlugin = NULL;
	m_pRichText = NULL;
	m_pHandler = NULL;
	m_pFunction = nullptr;
}

CMessageBoxUI::~CMessageBoxUI()
{
	//m_pFunction = nullptr;
}

void CMessageBoxUI::Show(MsgBox_Mode mode, const char* strMsg, const char* strButtonText1, const char* strButtonText2,
						 Ref *pListenner, YESORNO_EVENT pHandler, Widget *pPlugin,Scene_Type sceneType)
{
	CMessageBoxUI *pUI = (CMessageBoxUI*)gGameUILayer->getUI(IDU_MESSAGEBOX);
	pUI->SetInfo(mode, strMsg, pListenner, pHandler);

	if (mode == MBM_OK)
	{
		if (strButtonText1) pUI->m_pBtnConfirm->setTitleText(strButtonText1);
	}
	else
	{
		if (strButtonText1) pUI->m_pYes->setTitleText(strButtonText1);
		if (strButtonText2) pUI->m_pNo->setTitleText(strButtonText2);
	}

	if (pPlugin)
	{
		pUI->AddPlugin(pPlugin);
	}

	gGameUILayer->open(IDU_MESSAGEBOX);
}

 void CMessageBoxUI::Show(MsgBox_Mode mode, const char* strMsg, const std::function<void(bool)>& pHandler, const char* strButtonText1, const char* strButtonText2,
 						 Ref *pListenner, Widget *pPlugin,Scene_Type sceneType)
 {
 	CMessageBoxUI *pUI = (CMessageBoxUI*)gGameUILayer->getUI(IDU_MESSAGEBOX);
 	pUI->SetInfo(mode, strMsg, pListenner, pHandler);
 
 	if (mode == MBM_OK)
 	{
 		if (strButtonText1) pUI->m_pBtnConfirm->setTitleText(strButtonText1);
 	}
 	else
 	{
 		if (strButtonText1) pUI->m_pYes->setTitleText(strButtonText1);
 		if (strButtonText2) pUI->m_pNo->setTitleText(strButtonText2);
 	}
 
 	if (pPlugin)
 	{
 		pUI->AddPlugin(pPlugin);
 	}
 	gGameUILayer->open(IDU_MESSAGEBOX);
 }

bool CMessageBoxUI::onInit()
{
	if (!GameUI::onInit())
	{
		return false;
	}

	Button* pClose = (Button*)Helper::seekWidgetByName(m_pWidget, "Btn_close");
	if (pClose)
	{
		//pClose->addTouchEventListener(this,toucheventselector(CMessageBoxUI::clickBtnClose));
		//pClose->setButtonSpriteGray();
	}

	m_pYes = (Button*)Helper::seekWidgetByName(m_pWidget, "BoxBtn_Yes");
	if (m_pYes)
	{
		m_pYes->addTouchEventListener(this,toucheventselector(CMessageBoxUI::clickBtn));
		m_strTextYes = m_pYes->getTitleText();
		m_pYes->setButtonSpriteGray();
	}
	m_pNo = (Button*)Helper::seekWidgetByName(m_pWidget, "BoxBtn_No");
	if (m_pNo)
	{
		m_pNo->addTouchEventListener(this,toucheventselector(CMessageBoxUI::clickBtn));
		m_strTextNo = m_pNo->getTitleText();
		m_pNo->setButtonSpriteGray();
	}

	m_pBtnConfirm = (Button*)Helper::seekWidgetByName(m_pWidget, "BoxBtn_confirm");
	if (m_pBtnConfirm)
	{
		m_pBtnConfirm->addTouchEventListener(this,toucheventselector(CMessageBoxUI::clickBtnConfirm));
		m_strTextConfirm = m_pBtnConfirm->getTitleText();
		m_pBtnConfirm->setButtonSpriteGray();
	}

	m_pMsgText = (Text*)Helper::seekWidgetByName(m_pWidget, "BoxTxt_desc");
	m_pRichText = RichTextEx::create();
	m_pRichText->ignoreContentAdaptWithSize(false);
	m_pRichText->setSize(Size(m_pMsgText->getSize().width,0));
	m_pRichText->setPosition(Point(m_pMsgText->getSize().width/2,m_pMsgText->getSize().height/2));
	m_pRichText->SetFontSize(20);
	m_pMsgText->addChild(m_pRichText);

	return true;
}

void CMessageBoxUI::onClose()
{
	m_pBtnConfirm->setTitleText(m_strTextConfirm);
	m_pYes->setTitleText(m_strTextYes);
	m_pNo->setTitleText(m_strTextNo);
	if (m_pPlugin) m_pMsgText->setPosition(m_pPlugin->getPosition());	// »¹Ô­Î»ÖÃ
	removeChild(m_pPlugin);
}

void CMessageBoxUI::SetInfo(MsgBox_Mode mode, const char* strMsg, Ref *pListenner, YESORNO_EVENT pHandler)
{
	m_mode = mode;

	m_pBtnConfirm->setEnabled(false);
	m_pYes->setEnabled(false);
	m_pNo->setEnabled(false);

	if (mode == MBM_OK)
	{
		m_pBtnConfirm->setEnabled(true);
	}
	else if (mode == MBM_YESNO)
	{
		m_pYes->setEnabled(true);
		m_pNo->setEnabled(true);
	}

	m_pRichText->ParseAndLayout(strMsg);

	m_pListenner = pListenner;
	m_pHandler = pHandler;
}

void CMessageBoxUI::SetInfo(MsgBox_Mode mode, const char* strMsg, Ref *pListenner, const std::function<void(bool)>& pHandler)
{
	m_mode = mode;

	m_pBtnConfirm->setEnabled(false);
	m_pYes->setEnabled(false);
	m_pNo->setEnabled(false);

	if (mode == MBM_OK)
	{
		m_pBtnConfirm->setEnabled(true);
	}
	else if (mode == MBM_YESNO)
	{
		m_pYes->setEnabled(true);
		m_pNo->setEnabled(true);
	}

	m_pRichText->ParseAndLayout(strMsg);

	m_pListenner = pListenner;
	m_pFunction = pHandler;
}

void CMessageBoxUI::AddPlugin(Widget *pPlugin)
{
	m_pPlugin = pPlugin;
	m_pMsgText->getParent()->addChild(pPlugin);
	m_pPlugin->setPosition(m_pMsgText->getPosition());
	m_pPlugin->setAnchorPoint(Point(0.5f, 0.5f));
	m_pMsgText->setPositionY(m_pPlugin->getPositionY() + m_pPlugin->getSize().height / 2 + m_pMsgText->getSize().height / 2 + 10);
	((Widget*)m_pMsgText->getParent())->setSize(((Widget*)m_pMsgText->getParent())->getSize() + Size(0, m_pPlugin->getSize().height / 2 + 10));
}

void CMessageBoxUI::clickBtnClose(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		gGameUILayer->destroyUI(this);
	}
}

void CMessageBoxUI::clickBtnConfirm(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		gGameUILayer->destroyUI(this);
	}
}

void CMessageBoxUI::clickBtn(Ref *pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		if (m_pListenner&& m_pHandler)
		{
			(m_pListenner->*m_pHandler)(pSender == m_pYes);
			gGameUILayer->close(this);
		}
		else if(m_pFunction!= nullptr)
		{
			m_pFunction(pSender == m_pYes);
			gGameUILayer->close(this);
		}
	}
}
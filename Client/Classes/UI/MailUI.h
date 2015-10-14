/****************************************************************************
 邮件系统UI
 李阳
 2015-8-12
 ****************************************************************************/
#pragma once
#include "GameDef.h"
#include "GameUI.h"

class CMailUI : public GameUI
{
public:
	CMailUI();
	~CMailUI();

	bool			onInit();
	void			onOpen();

	CREATE_FUNC(CMailUI);
public:
	Widget*			createMailItem();						
	void			updateMailContent(int64 mail_id);			 // 更新右侧邮件显示区域内容
	void			updateMailList();						 // 更新左侧邮件列表

	void			clickCheckBoxMail(Ref*, TouchEventType); // 点击邮件，查看邮件

	void			clickCloseButton(Ref*, TouchEventType);
	void			clickGetAwardButton(Ref*, TouchEventType);
	void			clickGetAllButton(Ref*, TouchEventType);
	void			clickDeleteReadButton(Ref*, TouchEventType);
private:
	ListView*					m_mail_list;		// 邮件列表
	Button*						m_get_award_btn;	// 领取奖励按钮
	Slider*						mail_list_slider;

	Text*						m_mail_content_txt; // 邮件内容
	Text*						m_mail_title_txt;	// 邮件标题
	ScrollView*					m_mail_award_srcoll;	// 邮件附件列表

	CheckBox*					m_select_mail_item; // 选择的邮件

	vector<int64>				m_mail_id_vec;
public:
};


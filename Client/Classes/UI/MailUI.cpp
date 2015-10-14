#include "MailUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "GameScene/GameUILayer.h"
#include "Net/NetDispatcher.h"
#include "Net/pk_mail.h"
#include "Common/DataPool.h"

#define ROW_FONT_COUNTS 48.0 

CMailUI::CMailUI()
	:GameUI(IDU_MailUI,JsonFile_MailUI)
{
	m_select_mail_item = nullptr;
}

CMailUI::~CMailUI()
{

}

bool CMailUI::onInit()
{
	do 
	{
		BREAK_IF(!GameUI::onInit());

		Button *pCloseBtn = (Button*)Helper::seekWidgetByName(m_pWidget, "close_btn");
		BREAK_IF(pCloseBtn==NULL);
		pCloseBtn->setButtonSpriteGray();
		pCloseBtn->addTouchEventListener(this, SEL_TouchEvent(&CMailUI::clickCloseButton));

		Button *pDeleteReadBtn = (Button*)Helper::seekWidgetByName(m_pWidget, "del_btn");
		BREAK_IF(pDeleteReadBtn==NULL);
		pDeleteReadBtn->setButtonSpriteGray();
		pDeleteReadBtn->addTouchEventListener(this, SEL_TouchEvent(&CMailUI::clickDeleteReadButton));

		Button *pGetAllBtn = (Button*)Helper::seekWidgetByName(m_pWidget, "getAll_btn");
		BREAK_IF(pGetAllBtn==NULL);
		pGetAllBtn->setButtonSpriteGray();
		pGetAllBtn->addTouchEventListener(this, SEL_TouchEvent(&CMailUI::clickGetAllButton));

		m_get_award_btn = (Button*)Helper::seekWidgetByName(m_pWidget, "get_btn");
		BREAK_IF(m_get_award_btn==NULL);
		m_get_award_btn->setButtonSpriteGray();
		m_get_award_btn->addTouchEventListener(this, SEL_TouchEvent(&CMailUI::clickGetAwardButton));
		m_get_award_btn->setVisible(false);

		auto temp_mail_list_ = (ListView*)(Helper::seekWidgetByName(m_pWidget, "mail_list"));
	    mail_list_slider = dynamic_cast<Slider*>(Helper::seekWidgetByName(m_pWidget, "slider"));

		m_mail_content_txt = (Text*)(Helper::seekWidgetByName(m_pWidget, "content_text"));
		m_mail_title_txt = (Text*)(Helper::seekWidgetByName(m_pWidget, "title_text"));
		m_mail_title_txt->setColor(Color3B(222,209,164));
		m_mail_award_srcoll = (ScrollView*)(Helper::seekWidgetByName(m_pWidget, "award_scroll"));

		m_mail_content_txt->setText("");
		m_mail_title_txt->setText("");

		m_mail_list = temp_mail_list_;
		m_mail_list->setItemsMargin(5);

		return true;
	} while (0);

	return false;
}

void CMailUI::onOpen()
{
	updateMailList();
}

// 点击邮件，查看邮件
void CMailUI::clickCheckBoxMail(Ref* pSender, TouchEventType type) 
{
	string pathMailIcon[3] = {"assets/ui/mail/ico_youxiang1.png","assets/ui/mail/ico_youxiang2.png","assets/ui/mail/ico_youxiang3.png"};

	if(TOUCH_EVENT_ENDED == type)
	{
		int64 mail_id_ = m_mail_id_vec[((CheckBox*)pSender)->getTag()];	

		if (m_select_mail_item != nullptr) 
		{
			m_select_mail_item->setSelectedState(false); // 设置为不可点击的状态
		}

		if(m_select_mail_item == (CheckBox*)pSender) // 点击的邮件就是当前选择的邮件
		{
			CCLOG("not update\n");
		}else
		{
			m_select_mail_item =  ((CheckBox*)pSender);
			auto mail_item_temp_ = (Widget*)m_select_mail_item->getParent();
			auto head_img_ = (ImageView*)Helper::seekWidgetByName(mail_item_temp_, "head_img");	
			auto mail_title_label_ = (Text*)Helper::seekWidgetByName(mail_item_temp_, "title_label");
			auto mail_content_label_ = (Text*)Helper::seekWidgetByName(mail_item_temp_, "content_label");

			auto temp_mail_item_ = *(gDataPool->getMailByID(mail_id_));
			int isReaded = (temp_mail_item_.mailReadState == 0)? 1:	temp_mail_item_.mailReadState;	// 已读标记 0未读 1已读 2已领取
	
			auto isAwarded = temp_mail_item_.vec.size() == 0 ? 0:1;									// 是否有附件 0没有 1有
			if (temp_mail_item_.money>0)
			{
				isAwarded = 1;
			}

			mail_title_label_->setText(temp_mail_item_.mailSendName);
			mail_content_label_->setText(temp_mail_item_.mailTitle);

			if (isReaded == 0)
			{
				head_img_->loadTexture(pathMailIcon[0]);
			}else if(isReaded == 1 && isAwarded == 1)
			{
				head_img_->loadTexture(pathMailIcon[1]);
			}else
			{
				head_img_->loadTexture(pathMailIcon[2]);
			}

			if (isReaded == 0 || (isReaded == 1&&isAwarded == 1))
			{
				mail_title_label_->setColor(Color3B(56,241,13));
				mail_content_label_->setColor(Color3B(255,255,255));
			}else
			{
				mail_title_label_->setColor(Color3B(112,128,144));
				mail_content_label_->setColor(Color3B(112,128,144));
			}

			if(temp_mail_item_.mailReadState == 0)
			{
				pk::C2GS_Read_Mail cmd;
				cmd.mailId = mail_id_;
				cmd.Send(gNetSocket);
			}

			updateMailContent(mail_id_);
			CCLOG("update\n");
		}
	}
}

Widget*	CMailUI::createMailItem()
{
	auto node = GUIReader::getInstance()->widgetFromJsonFile("assets/ui/MailItem.json");
	return node;
}

void CMailUI::clickCloseButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(this);
	}
}

void CMailUI::clickGetAwardButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		// 点击了领取奖励按钮
		pk::C2GS_Get_Attach cmd;
		cmd.mailId = m_mail_id_vec[m_select_mail_item->getTag()];
		cmd.Send(gNetSocket);

		auto mail_item_temp_ = (Widget*)m_select_mail_item->getParent();
		auto head_img_ = (ImageView*)Helper::seekWidgetByName(mail_item_temp_, "head_img");	
		auto mail_title_label_ = (Text*)Helper::seekWidgetByName(mail_item_temp_, "title_label");
		auto mail_content_label_ = (Text*)Helper::seekWidgetByName(mail_item_temp_, "content_label");
		head_img_->loadTexture("assets/ui/mail/ico_youxiang3.png");
		mail_title_label_->setColor(Color3B(112,128,144));
		mail_content_label_->setColor(Color3B(112,128,144));
	}
}

void CMailUI::clickGetAllButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		// 点击了一键领取
		pk::C2GS_Get_Attach_List cmd;
		vector<int64> mailIdList_;
		mailIdList_.clear();
		auto mail_list_ = gDataPool->getMailList();
		for (size_t i = 0;i<mail_list_.size();i++)
		{
			if (mail_list_[i].mailReadState != 2 && (mail_list_[i].vec.size() != 0 || mail_list_[i].money>0) )
			{
				mailIdList_.push_back(mail_list_[i].mailId);
			}
		}

		cmd.mailIdList  = 	mailIdList_;
		cmd.Send(gNetSocket);
	}
}

void CMailUI::clickDeleteReadButton(Ref* pSender, TouchEventType type)
{
	if(TOUCH_EVENT_ENDED == type)
	{
		// 点击了删除已读
		pk::C2GS_Delete_Mail_List cmd;
		vector<int64> mailIdList_;
		mailIdList_.clear();
		auto mail_list_ = gDataPool->getMailList();
		for (size_t i = 0;i<mail_list_.size();i++)
		{
			if (mail_list_[i].mailReadState == 2)
			{
				mailIdList_.push_back(mail_list_[i].mailId);
			}

			if (mail_list_[i].mailReadState == 1 && (mail_list_[i].vec.size() == 0 && mail_list_[i].money<=0))
			{
				mailIdList_.push_back(mail_list_[i].mailId);
			}
		}
		if (mailIdList_.size()>0)
		{
			cmd.mailIdList  = 	mailIdList_;
			cmd.Send(gNetSocket);
		}
	}
}

void CMailUI::updateMailContent(int64 mail_id)
{
	auto mail_item_ = *(gDataPool->getMailByID(mail_id));
	m_mail_award_srcoll->removeAllChildren();

	auto isAwarded = mail_item_.vec.size() == 0 ? 0:1;								// 是否有附件 0没有 1有
	if (mail_item_.money>0)
	{
		isAwarded = 1;
	}

	int tempLength_ = getRealStringLength(mail_item_.mailContent);
	int row_number_=  ceil(tempLength_/ROW_FONT_COUNTS);
	int posY_ = m_mail_content_txt->getPosition().y;

	m_mail_content_txt->setText(mail_item_.mailContent);
	m_mail_title_txt->setText(mail_item_.mailSendName);

	

	int isReaded_ = mail_item_.mailReadState;

	if (isReaded_ != 2 && isAwarded == 1)
	{
		m_get_award_btn->setVisible(true);
	}else
	{
		m_get_award_btn->setVisible(false);
	}

	if (isAwarded == 1)
	{

		int award_number = 3;
		int award_row = ceil(award_number/3.0);
		// 往m_mail_award_list中添加物品
		Layer* award_layer_ = Layer::create();
		if (award_row == 1)
		{
			award_layer_->setContentSize(Size(320,150));
		}else
		{
			award_layer_->setContentSize(Size(320,75*award_row));
		}

		for (int i = 0;i<award_number;i++)
		{
			auto img_ = ImageView::create("assets/ui/MainUINormal/ico_jinbi.png");
			img_->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
			img_->setPosition(Point(30 + (i%3)*(67+30),award_layer_->getContentSize().height - i/3*(63+15)));

			auto name_ = Text::create();
			char name_str_[20];
			sprintf(name_str_,"X%d",1000);
			name_->setFontSize(18);
			name_->setText(name_str_);
			name_->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
			name_->setPosition(Point(img_->getContentSize().width/2,0));
			img_->addChild(name_);

			award_layer_->addChild(img_);
		}

		m_mail_award_srcoll->addChild(award_layer_);
		m_mail_award_srcoll->setInnerContainerSize(award_layer_->getContentSize());
		m_mail_award_srcoll->setPosition(Point(m_mail_content_txt->getPosition().x,posY_ - m_mail_award_srcoll->getContentSize().height - row_number_*30 - 10));
	}
}

void CMailUI::updateMailList()
{
	string pathMailIcon[3] = {"assets/ui/mail/ico_youxiang1.png","assets/ui/mail/ico_youxiang2.png","assets/ui/mail/ico_youxiang3.png"};
	CheckBox* default_select_mail_item_ = nullptr;
	m_select_mail_item = nullptr;
	m_mail_list->removeAllItems();
	m_mail_id_vec.clear();

	m_mail_award_srcoll->removeAllChildren();
	m_mail_content_txt->setText("");
	m_mail_title_txt->setText("");

	auto mail_list_ = gDataPool->getMailList();

	for (size_t i = 0;i<mail_list_.size();i++)
	{
		auto temp_mail_item_ = mail_list_[i];
		auto mail_item_temp_ = createMailItem();
		auto mail_checkbox_ = (CheckBox*)Helper::seekWidgetByName(mail_item_temp_, "checkbox");
		mail_checkbox_->setTag(i);
		m_mail_id_vec.push_back(temp_mail_item_.mailId);
		mail_checkbox_->addTouchEventListener(this, SEL_TouchEvent(&CMailUI::clickCheckBoxMail));
		if (i == 0)
		{
			default_select_mail_item_ = mail_checkbox_;
		}

		auto isReaded = temp_mail_item_.mailReadState;										// 已读标记 0未读 1已读 2已领取
		auto isAwarded = temp_mail_item_.vec.size() == 0 ? 0:1;								// 是否有附件 0没有 1有
		if (temp_mail_item_.money>0)
		{
			isAwarded = 1;
		}

		auto mail_title_label_ = (Text*)Helper::seekWidgetByName(mail_item_temp_, "title_label");
		mail_title_label_->setText(temp_mail_item_.mailSendName);

		auto mail_content_label_ = (Text*)Helper::seekWidgetByName(mail_item_temp_, "content_label");
		mail_content_label_->setText(temp_mail_item_.mailTitle);

		auto head_img_ = (ImageView*)Helper::seekWidgetByName(mail_item_temp_, "head_img");
		if (isReaded == 0)
		{
			head_img_->loadTexture(pathMailIcon[0]);
		}else if(isReaded == 1 && isAwarded == 1)
		{
			head_img_->loadTexture(pathMailIcon[1]);
		}else
		{
			head_img_->loadTexture(pathMailIcon[2]);
		}

		if (isReaded == 0 || (isReaded == 1&&isAwarded == 1))
		{
			mail_title_label_->setColor(Color3B(56,241,13));
			mail_content_label_->setColor(Color3B(255,255,255));
		}else
		{
			mail_title_label_->setColor(Color3B(112,128,144));
			mail_content_label_->setColor(Color3B(112,128,144));
		}

		m_mail_list->pushBackCustomItem(mail_item_temp_);
	}

	if (default_select_mail_item_ != nullptr)
	{
		default_select_mail_item_->setSelectedState(true);
		clickCheckBoxMail(default_select_mail_item_,TOUCH_EVENT_ENDED);
	}

	mail_list_slider->setList(m_mail_list, Slider::ListType::LISTVIEW_TYPE);


}

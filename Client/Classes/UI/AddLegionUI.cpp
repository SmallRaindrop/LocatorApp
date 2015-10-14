#include "AddLegionUI.h"
#include "../GameScene/GameUILayer.h"


enum Panel_Index
{
	Panel_Index_Mess,          //信息界面
	Panel_Index_Legion,        //军团信息界面
	Panel_Index_Create,        //创建军团界面
};

enum SignOption
{
	SignOption_Msg,            //信息标签
	SignOption_Legion,         //军团标签
	SignOption_Close,          //关闭标签
};

enum OptionBtn
{
	OptionBtn_Add,             //申请
	OptionBtn_create,          //创建
	OptionBtn_invitate,        //邀请
};


AddLegionUI_cl::AddLegionUI_cl():GameUI(IDU_AddLegionUI, JsonFile_AddLegionUI)
{
	m_pPanel[0] = nullptr;
	m_pPanel[1] = nullptr;
	m_pPanel[2] = nullptr;
	m_pSignBtn[0] = nullptr;
	m_pSignBtn[1] = nullptr;
	m_pSignBtn[2] = nullptr;
	m_nIndex = 0;
	m_pLegionList = nullptr;
	m_pLegionName = nullptr;
	m_pSearchName = nullptr;
}

AddLegionUI_cl::~AddLegionUI_cl()
{

}


bool AddLegionUI_cl::onInit()
{
	if(!GameUI::onInit()) return false;
	if(!m_pWidget) return false;
	m_pPanel[0] = Helper::seekWidgetByName(m_pWidget, "Panel_mess");
	m_pPanel[1] = Helper::seekWidgetByName(m_pWidget, "Panel_legion");
	m_pPanel[2] = Helper::seekWidgetByName(m_pWidget, "Panel_create");
	

	//信息界面 0加入军团 1创建军团 2军团邀请
	Button * btn[3];
	for (int i = 0; i < 3; i++)
	{
		btn[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanel[0], FORMAT_TO_STRING("Button_%d", i)));
		btn[i]->setTag(i);
		btn[i]->addTouchEventListener(this, toucheventselector(AddLegionUI_cl::callbackOption));

		m_pSignBtn[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, FORMAT_TO_STRING("Button_%d", i)));
		m_pSignBtn[i]->setTag(i);
		m_pSignBtn[i]->addTouchEventListener(this, toucheventselector(AddLegionUI_cl::callbackSign));
	}


	//搜索军团按钮
	Button*  searchBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pPanel[1], "Button_serach"));
	searchBtn->addTouchEventListener(this, toucheventselector(AddLegionUI_cl::callbackSearch));

	m_pLegionList = dynamic_cast<ListView*>(Helper::seekWidgetByName(m_pPanel[1],"ListView"));

	m_pLegionName = dynamic_cast<TextField*>(Helper::seekWidgetByName(m_pPanel[2],"TextField"));
	m_pLegionName->addEventListenerTextField(this, textfieldeventselector(AddLegionUI_cl::callbackCreateInput));

	m_pSearchName = dynamic_cast<TextField*>(Helper::seekWidgetByName(m_pPanel[1], "TextField_24"));
	m_pSearchName->addEventListenerTextField(this, textfieldeventselector(AddLegionUI_cl::callbackSearchInput));

	changeShow();

	return true;
}

void AddLegionUI_cl::changeShow()
{
	for (int i = 0; i < 3; i++)
	{
		m_pPanel[i]->setEnabled(false);
		if(i < 2) m_pSignBtn[i]->setButtonShowType(Normal_TYPE);
	}
	if(m_pPanel[m_nIndex])
	{
		m_pPanel[m_nIndex]->setEnabled(true);
	}
	if(m_nIndex == Panel_Index_Create)
	{
		m_pSignBtn[0]->setButtonShowType(Press_TYPE);
	}
	else
	{
		m_pSignBtn[m_nIndex]->setButtonShowType(Press_TYPE);
		if(Panel_Index_Legion == m_nIndex)
			updateLegionList();
	}
}


void AddLegionUI_cl::updateLegionList(Legion_V * vec /*= nullptr*/)
{
	if(vec == nullptr)
	{
		m_pLegionList->removeAllItems();
		Legion_cl* legion = gDataPool->getLegionData();
		Widget * child = Helper::seekWidgetByName(m_pWidget, "LegionChild");
		for (size_t i = 0; i < legion->getGuildList().size(); i++)
		{
			Widget* cloneChild = child->clone();
			m_pLegionList->pushBackCustomItem(cloneChild);
		}
	}
	else
	{
		m_pLegionList->removeAllItems();
		Widget * child = Helper::seekWidgetByName(m_pWidget, "LegionChild");
		Legion_V data = *vec;
		for (size_t i = 0; i < data.size(); i++)
		{
			Widget* cloneChild = child->clone();
			m_pLegionList->pushBackCustomItem(cloneChild);
		}
	}
}

Legion_V AddLegionUI_cl::searchMember()
{
	Legion_V ret;
	vector<string> strSub;
	string  str = m_pSearchName->getStringValue();
	if(m_pSearchName->getStringValue() != "")
	{
		int length = (int)str.length();
		const char* p_str = str.c_str();
		int i = 0;
		bool font = false; //上一个是否是英文
		while (i<length)
		{
			unsigned char c = p_str[i];
			if(c >127){                      //中文
				strSub.push_back(str.substr(i,3));
				i=i+3;
				font = false;
			}
			else{                                                //英文
				if(font)
				{
					strSub.at(strSub.size() - 1).append(str.substr(i,1));
				}
				else
				{
					strSub.push_back(str.substr(i,1));
				}
				
				i=i+1;
				font = true;
			}
		}
	}
	Legion_cl* legion = gDataPool->getLegionData();
	Legion_V data = legion->getGuildList();
	for (size_t i = 0; i < strSub.size(); i++)
	{
		for (size_t j = 2; j < strSub.size(); j++)
		{
			int cnt = (int)legion->getGuildList().size();
			for (auto iter = data.begin(); iter != data.end(); iter++)
			{
				if(iter->guildName.find(strSub[i].substr(i,j)) != string::npos)
				{
					ret.push_back(*iter);
					iter = data.erase(iter);
				}
				if(iter == data.end())
				{
					break;
				}
			}
		}
	}
	return ret;
}


void AddLegionUI_cl::callbackSign(Ref* pSender, TouchEventType event)
{
	if(event == TOUCH_EVENT_ENDED)
	{
		int signoption = dynamic_cast<Button*>(pSender)->getTag();
		switch (signoption)
		{
		case SignOption_Msg:
			m_nIndex = Panel_Index_Mess;
			break;
		case SignOption_Legion:
			m_nIndex = Panel_Index_Legion;
			break;
		case SignOption_Close:
			gGameUILayer->destroyUI(IDU_AddLegionUI);
			break;
		default:
			break;
		}
		if(signoption != SignOption_Close)
		{
			changeShow();
		}
	}
}

void AddLegionUI_cl::callbackOption(Ref* pSender, TouchEventType event)
{
	if(event == TOUCH_EVENT_ENDED)
	{
		int tag = dynamic_cast<Button*>(pSender)->getTag();
		switch (tag)
		{
		case OptionBtn_Add:
			m_nIndex = Panel_Index_Legion;
			break;
		case OptionBtn_create:
			m_nIndex = Panel_Index_Create;
			break;
		case OptionBtn_invitate:
			break;
		default:
			break;
		}
		if(tag != OptionBtn_invitate)
		{
			changeShow();
		}
	}
}

void AddLegionUI_cl::callbackSearch(Ref* pSender, TouchEventType event)
{
	if(event == TOUCH_EVENT_ENDED)
	{
		Legion_V data  = searchMember();
		updateLegionList(&data);
	}
}

void AddLegionUI_cl::callbackCreateInput(Ref* textfield, TextFiledEventType event)
{
	if(event == TEXTFIELD_EVENT_DELETE_BACKWARD)
	{
		
	}
}

void AddLegionUI_cl::callbackSearchInput(Ref* textfield, TextFiledEventType event)
{
	if(event == TEXTFIELD_EVENT_DELETE_BACKWARD)
	{
		if(m_pSearchName->getStringValue() == "")
		{
			updateLegionList();
		}
	}
}
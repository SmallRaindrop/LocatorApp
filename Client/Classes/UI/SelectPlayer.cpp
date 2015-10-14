#include "SelectPlayer.h"
#include "UIHelper.h"
#include "GameScene/LoginScene.h"
#include "GameScene/GameManager.h"
#include "GameScene/Hero.h"
#include "Net/NetDispatcher.h"
#include "CreatePlayer.h"
#include "GameScene/MessageCenter.h"
#include "MessageBoxUI.h"
#include "Net/pk_betweenClientLs.h"
#include "GameScene/GameUILayer.h"


enum  BTN_TAG
{
	One_Player = 0, 
	Two_Player,
	Three_Player,
	Delete_Player,
	Enter_Game,
	Back_TAG,  
};

enum Hero_Type
{
	ZhanShi_Type  = 1,
	FaShi_Type    = 2,
	GogJian_Type  = 3,
};

#define   ZHANSHI_BTN_IMAG          "assets/ui/createHero/img_touxiangzhanshi.png"
#define   FASHI_BTN_IMAG            "assets/ui/createHero/img_touxiangfashi.png"
#define   GONGJIAN_BTN_IMAG         "assets/ui/createHero/img_touxianggognshou.png"

#define   NONE_BTN_IMAG             "assets/ui/createHero/img_dianjichuangjian.png"

#define   ZHANSHI_SPR_IMAG          "assets/ui/createHero/img_zhanshijuese.png"
#define   FASHI_SPR_IMAG            "assets/ui/createHero/img_zhanshijuese.png"   //"assets/ui/createHero/img_fashi.png"
#define   GONGJIAN_SPR_IMAG         "assets/ui/createHero/img_zhanshijuese.png"   //"assets/ui/createHero/img_gongshou.png"

#define   ZHANSHI_SPR_IMAG1          "assets/ui/createHero/img_zhanshi.png"
#define   FASHI_SPR_IMAG1            "assets/ui/createHero/img_fashizi.png"
#define   GONGJIAN_SPR_IMAG1         "assets/ui/createHero/img_gongshouzi.png"

#define   MOVELEN        60



CSelectPlayer::CSelectPlayer() 
	:GameUI(IDU_SELECTPLAYER,JSONFILE_SELECTPLAYER)
	,m_curIndex(0)
	,m_pos(0.f)
{
	for (int i=0; i<Max_Player_Num; ++i)
	{
		m_playerContainer[i]=NULL;
		m_playerName[i]=NULL;
		m_roleModels[i]=NULL;
	}
	for (int i = 0; i < 5; i++)
	{
		m_pButton[i] = nullptr;
	}
}

CSelectPlayer::~CSelectPlayer()
{

}

bool CSelectPlayer::onInit()
{
	/**************************************
	 *  界面按钮  0 - 5   总共6个按钮    *
	 *  角色按钮  0 - 2                  *
	 *  删除按钮  3                      *
	 *  进入游戏  4                      *
	 *  返回登录  5                      *
	 **************************************/

	for(int i = 0; i < 6; i++)
	{
		m_pButton[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, FORMAT_TO_STRING("Button_%d", i)));
		if(m_pButton[i])
		{
			m_pButton[i]->setTag(i);
			m_pButton[i]->addTouchEventListener(this, toucheventselector(CSelectPlayer::clickCallBack));
			m_pButton[i]->setUserData((void*)0);
			m_pButton[i]->setTouchEnabled(true);
			m_pButton[i]->setPressedActionEnabled(true);
		}
	}
	m_pos = m_pButton[0]->getPositionX();
	return true;
}

void CSelectPlayer::onOpen()
{

}

void CSelectPlayer::onClose()
{
}

void CSelectPlayer::Show(vector<pk::UserPlayerData>& player_list)
{
	m_players.clear();
	m_players = player_list;
	m_curIndex = 0;
	auto heroSpr = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_hero"));
	heroSpr->setVisible(true);
	if(m_players.size()>0)
	{
		auto idx = 0;
		for (auto iter : m_players)
		{
            static int u_data = 1;
			m_pButton[idx]->setUserData((void*)&u_data);
			m_pButton[idx]->setPositionX(m_pos);
			setHeroImage(iter, m_pButton[idx]);
			idx += 1;
			if(idx >= 3)
			{
				break;
			}
		}
		for (int i = idx; i <= 2; i++)
		{
			pk::UserPlayerData temp;
			temp.career = -1;
            static int u_data = 0;
			m_pButton[i]->setUserData((void*)&u_data);
			m_pButton[i]->setPositionX(m_pos);
			setHeroImage(temp, m_pButton[i]);
		}
		m_pButton[0]->setPositionX(m_pButton[0]->getPositionX() - MOVELEN);
		auto pHeroSpr = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWidget,"Image_hero"));
		setHeroImage(m_players[0], pHeroSpr, 1);
	}
	else
	{
		for (int i = 0; i <= 2; i++)
		{
			pk::UserPlayerData temp;
			temp.career = -1;
            static int u_data = 0;
			m_pButton[i]->setUserData((void*)&u_data);
			m_pButton[i]->setPositionX(m_pos);
			setHeroImage(temp, m_pButton[i]);
		}
		if(heroSpr)
			heroSpr->setVisible(false);
	}
}

void CSelectPlayer::selectPlayer(int tag)
{
	if(isExitHero(tag))
	{
		showFace(tag);
	}else
	{
		if (m_players.size() >= Max_Player_Num)
		{
			gMessageCenter->SystemMessage(801);
		} 
		else
		{
			CLoginScene::gLoginLayer->OpenUI(login_ui_createplayer);
		}
	}
}


void CSelectPlayer::deletePlayer(bool bDel)
{
	if (bDel)
	{
		pk::C2GS_DeletePlayer cmd;
		cmd.playerID = m_players[m_curIndex].playerID;
		cmd.Send(gNetSocket);
	} 
}

template <typename T>
void CSelectPlayer::setHeroImage(pk::UserPlayerData _type, const T& pPtr, int ptrType /* = 0 */)
{
	auto IconImag = "";
	auto sprImag = "";
	auto careerImg = "";
	switch (_type.career)
	{
	case ZhanShi_Type:
		IconImag = ZHANSHI_BTN_IMAG;
		sprImag = ZHANSHI_SPR_IMAG;
		careerImg = ZHANSHI_SPR_IMAG1;
		break;
	case FaShi_Type:
		IconImag = FASHI_BTN_IMAG;
		sprImag = FASHI_SPR_IMAG;
		careerImg = FASHI_SPR_IMAG1;
		break;
	case GogJian_Type:
		IconImag = GONGJIAN_BTN_IMAG;
		sprImag = GONGJIAN_SPR_IMAG;
		careerImg = GONGJIAN_SPR_IMAG1;
		break;
	default:
		IconImag = NONE_BTN_IMAG;
		break;
	}
	if(ptrType)
	{
		((ImageView*)pPtr)->loadTexture(sprImag);
		return;
	}
	
	auto pBtn = dynamic_cast<Button*>(pPtr);
	/*pBtn->loadTextures(btnImag, btnImag);*/
	pBtn->setPressedActionEnabled(false);
	auto icon      = dynamic_cast<ImageView*>(pBtn->getChildByName("Image_heroIcon"));
	auto leveltext = dynamic_cast<Text * >(pBtn->getChildByName("Label_level"));
	auto nametext = dynamic_cast<Text * >(pBtn->getChildByName("Label_heroname"));
	auto career = dynamic_cast<ImageView * >(pBtn->getChildByName("Image_herotype"));
	auto zhezhao = dynamic_cast<ImageView*>(pBtn->getChildByName("Image_zhezhao"));
	auto lineSpr = dynamic_cast<ImageView*>(pBtn->getChildByName("Image_nameline"));
	if(*(int*)pBtn->getUserData() != 0)
	{
		icon->setVisible(true);
		leveltext->setVisible(true);
		nametext->setVisible(true);
		career->setVisible(true);
		zhezhao->setVisible(true);
		lineSpr->setVisible(true);
		icon->loadTexture(IconImag);
		leveltext->setText(INT_TO_STRING(_type.level));
		nametext->setText(_type.name.c_str());
		career->loadTexture(careerImg);
	}
	else
	{
		leveltext->setVisible(false);
		nametext->setVisible(false);
		career->setVisible(false);
		zhezhao->setVisible(false);
		lineSpr->setVisible(false);
		icon->setVisible(false);
	}
}

bool CSelectPlayer::isExitHero(int _idx)
{
	if(m_pButton[_idx])
	{
		auto userdata = *(int*)m_pButton[_idx]->getUserData();
		if(userdata != 0)
			return true;
	}
	return false;
}

void CSelectPlayer::showFace(int _idx)
{
	if(m_pButton[_idx])
	{
		m_pButton[m_curIndex]->runAction(MoveBy::create(0.2f, Point(MOVELEN, 0)));
		m_pButton[_idx]->runAction(MoveBy::create(0.2f, Point(-MOVELEN, 0)));
		auto heroSpr = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_hero"));
		if(heroSpr)
		setHeroImage(m_players[_idx], heroSpr, 1);
		m_curIndex = _idx;
	}
}

void CSelectPlayer::clickCallBack( Ref* pSender, TouchEventType type )
{
	if(type == TOUCH_EVENT_ENDED)
	{
		auto tag = ((Button*)pSender)->getTag();
		CCLOG("CSelectPlayer::clickCallBack tag = %d", tag);
		switch (tag)
		{
		case One_Player:
		case Two_Player:
		case Three_Player:
			selectPlayer(tag);
			break;
		case Delete_Player:
			if (m_players.empty())
			{
				gMessageCenter->SystemMessage(817);
			}
			else
			{
				CMessageBoxUI::Show(CMessageBoxUI::MBM_YESNO,STR_Player_Del.c_str(),[&](bool type){
					if(type)
					{
						pk::C2GS_DeletePlayer cmd;
						cmd.playerID = m_players[m_curIndex].playerID;
						cmd.Send(gNetSocket);
					}
				},STR_MESSAGEBOX_COMFIRM.c_str(),STR_MESSAGEBOX_CANCEL.c_str(),
					this,NULL,CMessageBoxUI::Scene_Login);	
			}
			break;
		case Enter_Game:
			if (m_players.empty())
			{
				gMessageCenter->SystemMessage(816);
			}
			else
			{
				gGameManager->SetPlayerID(m_players[m_curIndex].playerID);
				gHero->SetId(m_players[m_curIndex].playerID);
				gGameManager->EnterState(GS_Game);
			}
			break;
		case Back_TAG:
			{
				gNetDispatcher->DisConnect();
				CLoginScene::gLoginLayer->OpenUI(login_ui_login);
				break;
			}
		default:
			break;
		}

	}
}

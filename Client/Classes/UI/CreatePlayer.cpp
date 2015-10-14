#include "CreatePlayer.h"
#include "UIHelper.h"
#include "GameScene/LoginScene.h"
#include "Net/pk_nonInGame.h"
#include "Net/NetDispatcher.h"
#include "Common/NameManager.h"
#include "GameScene/MessageCenter.h"
#include "Common/StringDef.h"
#include "RoleModel.h"
#include "Net/pk_betweenClientLs.h"

#define Tag_Career_Model		(123)
#define   ZHANSHI_SPR_IMAG          "assets/ui/createHero/img_zhanshijuese.png"
#define   FASHI_SPR_IMAG            "assets/ui/createHero/img_zhanshijuese.png" //"assets/ui/createHero/img_fashi.png"
#define   GONGJIAN_SPR_IMAG         "assets/ui/createHero/img_zhanshijuese.png" //"assets/ui/createHero/img_gongshou.png"

#define   ZHANSHI_SPR_IMAG1          "assets/ui/createHero/img_zhanshi.png"
#define   FASHI_SPR_IMAG1            "assets/ui/createHero/img_fashizi.png"
#define   GONGJIAN_SPR_IMAG1         "assets/ui/createHero/img_gongshouzi.png"

enum Hero_Type
{
	ZhanShi_Type  = 1,
	FaShi_Type    = 2,
	GogJian_Type  = 3,
};

enum CREAT_BtnTAG
{
	Top_TAG,            //向上滑
	Down_TAG,           //向下滑
	Create_TAG,         //创建角色
	Rand_TAG,           //随机名字
	Back_TAG,           //返回登录
};

CCreatePlayer::CCreatePlayer() 
	:GameUI(IDU_CREATEPLAYER,JSONFILE_CREATEPLAYER)
	,m_career(1)
	,m_name("")
	,m_sex(1)
	,m_pName(NULL)
	,m_pCareerSel(NULL)
	,m_pMaleBtn(NULL)
	,m_pFemaleBtn(NULL)
	,m_pCareerZS(NULL)
	,m_pCareerFS(NULL)
	,m_pCareerGJ(NULL)
	,m_pPowerTxt(NULL)
	,m_pModel(NULL)
{

}

CCreatePlayer::~CCreatePlayer()
{

}

RoleModel* createModelByPlayer(int career, int sex)
{
	RoleModel* pModel = RoleModel::create();
	//pModel->setActionLoop(true);
	int type = career*10+sex;
	switch (type)
	{
	case 10:
		pModel->setAppearance(1000000,0,0);
		break;
	case 11:
		pModel->setAppearance(1000000,0,0);
		break;
	case 20:
		pModel->setAppearance(1000000,0,0);
		break;
	case 21:
		pModel->setAppearance(1000000,0,0);
		break;
	case 30:
		pModel->setAppearance(1000000,0,0);
		break;
	case 31:
		pModel->setAppearance(1000000,0,0);
		break;
	}
	return pModel;
}

bool CCreatePlayer::onInit()
{
	/*************************
	  界面按钮 0-4
	  0-1 上滑 下滑
	  2   创建
	  3   随机名字
	  4   返回登录
	************************/
	for (int i = 0; i < 5; i++)
	{
		auto btn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, FORMAT_TO_STRING("Button_%d", i)));
		if(btn)
		{
			btn->setTag(i);
			btn->addTouchEventListener(this, toucheventselector(CCreatePlayer::clickCallBack));
			btn->setPressedActionEnabled(true);
		}
	}

	m_pName = (TextField*)(Helper::seekWidgetByName(m_pWidget,"TextField"));
	m_pName->setMaxLengthEnabled(true);
	m_pName->setMaxLength(20);

	/********************
		职业选择
	*******************/
	auto pListView = dynamic_cast<ListView*>(Helper::seekWidgetByName(m_pWidget, "ListView_jueshe"));
	Vector<Widget*> heroImag = pListView->getItems();
	for (auto Iter: heroImag)
	{
		Iter->addTouchEventListener(this, toucheventselector(CCreatePlayer::clickListHero));
	}
	return true;
}


void CCreatePlayer::onEnter()
{
	GameUI::onEnter();
	m_career = 1;
	showFace();
}

void CCreatePlayer::onExit()
{
	GameUI::onExit();
}

void CCreatePlayer::onOpen()
{
// 	m_pCareerSel->ClickButton(0);
// 	m_pSexSel->ClickButton(0);
// 	SetRandomName();
}


void CCreatePlayer::SetRandomName()
{
	m_pName->setText(gStrManager->randomName(m_sex));
}

void CCreatePlayer::clickCareerSel(int index)
{
	m_career = index+1;

	//m_pCareerZS->setPosition(m_pZSPos);
	//m_pCareerFS->setPosition(m_pFSPos);
	//m_pCareerGJ->setPosition(m_pGJPos);
	for (int i=0; i<3; ++i)
	{
		m_pCareerTxt[i]->setVisible(false);
		m_pPower[i]->setVisible(false);
	}
	switch (index)
	{
	case 0:
		//m_pCareerZS->runAction(EaseElasticOut::create(MoveBy::create(0.3f,Point(70,0))));
		m_pCareerTxt[0]->setVisible(true);
		m_pPower[0]->setVisible(true);
		m_pPowerTxt->setText(STR_CareerDesc_ZS);
		break;
	case 1:
		//m_pCareerFS->runAction(EaseElasticOut::create(MoveBy::create(0.3f,Point(70,0))));
		m_pCareerTxt[1]->setVisible(true);
		m_pPower[1]->setVisible(true);
		m_pPowerTxt->setText(STR_CareerDesc_FS);
		break;
	case 2:
		//m_pCareerGJ->runAction(EaseElasticOut::create(MoveBy::create(0.3f,Point(70,0))));
		m_pCareerTxt[2]->setVisible(true);
		m_pPower[2]->setVisible(true);
		m_pPowerTxt->setText(STR_CareerDesc_GJ);
		break;
	}
	ShowCareerModel();
}

void CCreatePlayer::clickSexSel(int index)
{
	m_sex=rand()%2;
	SetRandomName();
	ShowCareerModel();
}

void CCreatePlayer::ShowCareerModel()
{
	m_pWidget->removeChildByTag(Tag_Career_Model,true);
	m_pModel = createModelByPlayer(m_career,m_sex);
	m_pModel->setPosition(Point(GAME_UI_ORIG_SIZE.width/2,GAME_UI_ORIG_SIZE.height/2-320));
	m_pModel->setTag(Tag_Career_Model);
	m_pWidget->addChild(m_pModel);
}

void CCreatePlayer::update(float dt)
{
// 	GameUI::update(dt);
// 	if (m_pModel)
// 	{
// 		m_pModel->update(dt);
// 	}
}

void CCreatePlayer::clickRandom(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		SetRandomName();
	}
}

void CCreatePlayer::clickCreate(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		m_name = m_pName->getStringValue();
		if (m_name.size()<2 || m_name.size()>7*3)
		{
			gMessageCenter->SystemMessage(802);
			return;
		}
		if (!m_name.empty())
		{
			pk::C2GS_CreatePlayer cmd;
			cmd.career = m_career;
			cmd.name = m_name;
			cmd.sex = 1;
			cmd.Send(gNetSocket);
		}
	}
}

void CCreatePlayer::clickBack(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		CLoginScene::gLoginLayer->OpenUI(login_ui_selectplayer);
	}
}

void CCreatePlayer::showFace()
{
	setHeroImag(m_career);
	m_pName->setText(gStrManager->randomName(m_sex));
}

void CCreatePlayer::setHeroImag( int _career, int _sex )
{
	auto  manstr = "";
	auto  womstr = "";
	auto  herotypestr = "";
	switch (_career)
	{
	case ZhanShi_Type:
		manstr = ZHANSHI_SPR_IMAG;
		womstr = ZHANSHI_SPR_IMAG;
		herotypestr = ZHANSHI_SPR_IMAG1;
		break;
	case FaShi_Type:
		manstr = FASHI_SPR_IMAG;
		womstr = FASHI_SPR_IMAG;
		herotypestr = FASHI_SPR_IMAG1;
		break;
	case GogJian_Type:
		manstr = GONGJIAN_SPR_IMAG;
		womstr = GONGJIAN_SPR_IMAG;
		herotypestr = GONGJIAN_SPR_IMAG1;
		break;
	default:
		break;
	}
	auto heroSpr = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWidget,"Image_hero"));
	auto careerType = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWidget,"Image_herotype"));
	if(heroSpr&&careerType)
	{
		if(_sex)
		{
			heroSpr->loadTexture(manstr);
		}
		heroSpr->loadTexture(womstr);
		careerType->loadTexture(herotypestr);
	}

}

void CCreatePlayer::clickCallBack( Ref* pSender, TouchEventType type )
{
	if(type == TOUCH_EVENT_ENDED)
	{
		auto tag = ((Button*)pSender)->getTag();
		CCLOG("CCreatePlayer::clickCallBack tag = %d", tag);
		switch (tag)
		{
		case Top_TAG:
			break;
		case Down_TAG:
			break;
		case Create_TAG:
			{
				auto pname = m_pName->getStringValue();
				if (pname.size()<2 || pname.size()>7*3)
				{
					gMessageCenter->SystemMessage(802);
					return;
				}
				if (!pname.empty())
				{
					pk::C2GS_CreatePlayer cmd;
					cmd.career = m_career;
					cmd.name = pname;
					cmd.sex = 1;
					cmd.Send(gNetSocket);
				}
			}
			break;
		case Rand_TAG:
			{
				m_pName->setText(gStrManager->randomName(m_sex));
				break;
			}
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

void CCreatePlayer::clickListHero( Ref* pSender, TouchEventType type )
{
	if(type == TOUCH_EVENT_ENDED)
	{
		auto tag = ((ImageView*)pSender)->getTag();
		CCLOG("CCreatePlayer::clickListHero tag = %d", tag);
		m_career = tag;
		showFace();
	}
	
}

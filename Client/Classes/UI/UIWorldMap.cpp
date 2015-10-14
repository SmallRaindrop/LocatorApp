#include "UIWorldMap.h"
#include "GameScene/GameUILayer.h"
#include "CustomCtrl/MenuForPlayer.h"
#include "MainUINormal.h"
#include "ChatMainUI.h"
#include "TeamUI.h"
#include "Net/NetDispatcher.h"
#include "DataPool.h"
#include "GameScene/MessageCenter.h"
#include "GameScene/TaskMgr.h"

/*************************获取类型描述 start ******************************/

string		GetTaskTypeDes(GameMapTaskType type)
{
	switch (type)
	{
	case GameMapTaskType_PT:
		return STR_Copy_Type_PT;
	case GameMapTaskType_XS:
		return STR_Copy_Type_XS;
	case GameMapTaskType_EM:
		return STR_Copy_Type_EM;
	case GameMapTaskType_CT:
		return STR_Copy_Type_CT;
	default:
		return "";
	}
}

string		GetMapEnemyDes(GameMapEnemyType type)
{
	switch (type)
	{
	case GameMapEnemyType_YG:
		return STR_Copy_Enemy_YG;
	case GameMapEnemyType_SZ:
		return STR_Copy_Enemy_SZ;
	case GameMapEnemyType_YG_SZ:
		return STR_Copy_Enemy_YG_SZ;
	default:
		return "";
	}
}

string		GetMapPlayDes(GameMapPlayType type)
{
	switch (type)
	{
	case GameMapPlayType_Def:
		return STR_Copy_Play_FS;
	case GameMapPlayType_Kill:
		return STR_Copy_Play_JM;
	case GameMapPlayType_Catch:
		return STR_Copy_Play_BH;
	default:
		return "";
	}
}

/*************************获取类型描述 end ******************************/

CUIWorldMap::CUIWorldMap(void)
:GameUI(IDU_WORLDMAPUI,JSONFILE_WORLDMAPUI)
,m_pPlaceList(NULL)
,m_pCopyList(NULL)
,m_pPrepare(NULL)
,m_pMatch(NULL)
,m_curMode(WorldMapMode_None)
,m_nCurLocaleId(0)
,m_curGameCopy(NULL)
,m_nMatchModeIdx(0)
,m_matchBtnStatus(MatchBtnStatus_None)
{

}


CUIWorldMap::~CUIWorldMap(void)
{
	m_pWorldPlaceLock.clear();
}

bool CUIWorldMap::onInit()
{
	do 
	{
		Widget* pTop = Helper::seekWidgetByName(m_pWidget,"Top");
		Widget* pLeftBottom = Helper::seekWidgetByName(m_pWidget,"LeftBottom");
		m_pPlaceList = Helper::seekWidgetByName(m_pWidget,"PlaceList");
		m_pCopyList = Helper::seekWidgetByName(m_pWidget,"CopyList");
		m_pPrepare = Helper::seekWidgetByName(m_pWidget,"Prepare");
		m_pMatch = Helper::seekWidgetByName(m_pWidget,"Match");
		BREAK_IF(!(pTop&&pLeftBottom&&m_pPlaceList&&m_pCopyList&&m_pPrepare&&m_pMatch));
		m_pPlaceList->setVisible(true);
		m_pCopyList->setVisible(true);
		m_pPrepare->setVisible(true);
		m_pMatch->setVisible(true);

		//Top
		Button* pCloseBtn = (Button*)Helper::seekWidgetByName(pTop, "Exit");
		Button* pChatBtn = (Button*)Helper::seekWidgetByName(pTop, "BtnChat");
		BREAK_IF(!(pCloseBtn&&pChatBtn));
		pCloseBtn->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickCloseBtn));
		pChatBtn->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickChatBtn));
		
		//Left Bottom
		for (int i=0; i<Team_Max_Num; ++i)
		{
			m_pTeamIcon[i] = (ImageView*)Helper::seekWidgetByName(pLeftBottom, CCString::createWithFormat("HeadIcon_%d",i)->getCString());
			BREAK_IF(!m_pTeamIcon[i]);
		}
		Button* pRandomBtn = (Button*)Helper::seekWidgetByName(pLeftBottom, "RandomMap");
		Button* pTeamBtn = (Button*)Helper::seekWidgetByName(pLeftBottom, "BtnTeam");
		BREAK_IF(!(pRandomBtn&&pTeamBtn));
		pRandomBtn->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickRandomBtn));
		pTeamBtn->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickTeamBtn));

		//Place List
		WorldPlaces& worldPlaces = gCopyDataMgr->GetWorldPlaces();
		int i = 0;
		while (true)
		{
			Button* pPlace = (Button*)Helper::seekWidgetByName(m_pPlaceList, CCString::createWithFormat("Place_%d",i)->getCString());
			if(!pPlace || i>=worldPlaces.size()) break;
			pPlace->setTag(i);
			pPlace->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickWorldPlace));
			Widget* pLock = pPlace->getChildByName("Lock");
			BREAK_IF(!pLock);
			pLock->setTag(i);
			m_pWorldPlaceLock.push_back(pLock);
			i++;
		}
		//Copy List
		m_pCopyListView = (ListView*)Helper::seekWidgetByName(m_pCopyList,"CopyListView");
		m_pParentCopyItem = Helper::seekWidgetByName(m_pWidget,"Template");
		m_pSlider = (Slider*)Helper::seekWidgetByName(m_pWidget,"Slider");
		BREAK_IF(!(m_pCopyListView&&m_pParentCopyItem&&m_pSlider));
		m_pParentCopyItem->setEnabled(false);
		//Prepare
		m_pChildCopyItem = Helper::seekWidgetByName(m_pPrepare,"TemplateCopy");
		m_pCopyMode = (Text*)Helper::seekWidgetByName(m_pPrepare,"TxtMode");
		m_pCamp = (Text*)Helper::seekWidgetByName(m_pPrepare,"TxtCamp");
		m_pMatchMode = (Text*)Helper::seekWidgetByName(m_pPrepare,"TxtMatchMode");
		m_pMenuMatchBg = (Widget*)Helper::seekWidgetByName(m_pPrepare,"MenuMatch");
		BREAK_IF(!(m_pChildCopyItem&&m_pCopyMode&&m_pCamp&&m_pMatchMode&&m_pMenuMatchBg));
		Button* pBtnMatch = (Button*)Helper::seekWidgetByName(m_pPrepare,"BtnMatch");
		Button* pBtnBack = (Button*)Helper::seekWidgetByName(m_pPrepare,"BtnBack");
		Button* pBtnStart = (Button*)Helper::seekWidgetByName(m_pPrepare,"BtnStart");
		BREAK_IF(!(pBtnMatch&&pBtnBack&&pBtnStart));
		pBtnMatch->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickMatch));
		pBtnBack->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickBackFromPrepare));
		pBtnStart->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickStartCopy));
		//任务奖励
		Widget *pBoxesPanel = Helper::seekWidgetByName(m_pPrepare, "GridsPanel");
		BREAK_IF(!pBoxesPanel);
		Node *pParent = pBoxesPanel->getParent();
		BREAK_IF(!pParent);
		CGridArrayUI *pPackUI = CGridArrayUI::create(emGrids_TaskAward,0,GRIDS_SIZE_TASK,pBoxesPanel,true);
		gGridsManager->attachUI(pPackUI, emGrids_TaskAward);
		pParent->addChild(pPackUI);

		//Match
		Widget* pMatchBg = Helper::seekWidgetByName(m_pMatch,"MatchBG");
		m_pBtnCountLeft = (Button*)Helper::seekWidgetByName(m_pMatch,"Btn_Left");
		m_pBtnCountRight = (Button*)Helper::seekWidgetByName(m_pMatch,"Btn_Right");
		m_pBtnCountCenter = (Button*)Helper::seekWidgetByName(m_pMatch,"Btn_Center");
		m_pMatchingSign = Helper::seekWidgetByName(m_pMatch,"MatchingSign");
		m_pMatchWaitTime = (Text*)Helper::seekWidgetByName(m_pMatch,"WaitTime");
		BREAK_IF(!(pMatchBg&&m_pBtnCountLeft&&m_pBtnCountRight&&m_pBtnCountCenter&&m_pMatchWaitTime));
		m_pCountTitle = RichTextEx::create();
		m_pCountTitle->SetFontSize(20.0f);
		m_pCountTitle->setPosition(Point(180,280));
		pMatchBg->addChild(m_pCountTitle);
		m_pCountNum = Label::createWithBMFont("assets/common/font/timer.fnt",CCString::createWithFormat("60")->getCString());
		m_pCountNum->setPosition(Point(180,230));
		pMatchBg->addChild(m_pCountNum);
		m_pMatchingSign->setVisible(false);

		SetMode(WorldMapMode_PlaceList);
		return true;
	} while (0);

	return false;
}

void CUIWorldMap::onOpen()
{
	gMacthMachine->UpdateMatchStatus();
	SetMode(WorldMapMode_PlaceList);
	if (gMacthMachine->IsMatchStarted())
	{
		ShowMatch();
	}
	ShowTeamIcon();
	UpdateBigPlaceLockUI();
}

void CUIWorldMap::update(float dt)
{
	if (gMacthMachine->IsMatchStarted())
	{
		m_pMatch->setEnabled(true);
		m_pCopyList->setVisible(true);
		m_pSlider->setEnabled(true);
		m_pPrepare->setEnabled(false);
		int nSeconds = (int)gMacthMachine->GetMatchCountSeconds();
		if(gMacthMachine->GetMatchCountSeconds()<0.0f)
		{
			m_pCountNum->setVisible(false);
			if( gMacthMachine->AmIInviter() )
			{
				SetMatchBtnStatus(gMacthMachine->GetMatchCopyMapIdToEnter()?MatchBtnStatus_CancelAndStart:MatchBtnStatus_Cancel);
			}
			else
			{
				SetMatchBtnStatus(MatchBtnStatus_PrepareOver);
			}
			if (gMacthMachine->GetMatchMode() == MatchMode_Match)
			{
				m_pMatchingSign->setVisible(true);
				m_pMatchWaitTime->setText(SecondsToTime((int)gMacthMachine->GetMatchWaitTime(),1));
			}
		}
		else
		{
			m_pMatchingSign->setVisible(false);
			m_pCountNum->setVisible(true);
			m_pCountNum->setString(CCString::createWithFormat("%d",nSeconds)->getCString());
			switch (gMacthMachine->GetMatchStatus())
			{
			case MatchStatus_NoTeam_Single:
			case MatchStatus_NoTeam_Invite:
				SetMatchBtnStatus(MatchBtnStatus_Cancel);
				break;
			case MatchStatus_NoTeam_Match:
				SetMatchBtnStatus((gMacthMachine->GetMatchMode() == MachMode_End)?MatchBtnStatus_Started:MatchBtnStatus_CancelAndStart);
				break;
			case MatchStatus_TeamNoFull_Invite:
			case MatchStatus_TeamNoFull_Match:
			case MatchStatus_TeamFull_Invite:
			case MatchStatus_TeamFull_Match:
				SetMatchBtnStatus(gMacthMachine->AmIInviter()?MatchBtnStatus_Cancel:(gMacthMachine->GetMatchPrepared()?MatchBtnStatus_PrepareOver:MatchBtnStatus_Prepare));
				break;
			default:
				break;
			}
		}
	} 
	else
	{
		m_pMatch->setEnabled(false);
	}
}

void CUIWorldMap::UpdateBigPlaceLockUI()
{
	WorldPlaces& worldPlaces = gCopyDataMgr->GetWorldPlaces();
	for (unsigned int i=0; i<m_pWorldPlaceLock.size(); ++i)
	{
		m_pWorldPlaceLock[i]->setVisible(!worldPlaces[i].unLock);
	}
}

void CUIWorldMap::UpdateSmallPlaceLockUI()
{
	if(GetMode() == WorldMapMode_CopyList)
	{
		WorldPlaces& worldPlaces = gCopyDataMgr->GetWorldPlaces();
		ShowLocaleList(worldPlaces[m_nBigPlaceIdx].worldMapId);
	}
}

void CUIWorldMap::ShowTeamIcon()
{
	m_pTeamIcon[0]->loadTexture(GetWorldMapCareerIcon(gHero->GetCareer()));

	for (int i=1; i<Team_Max_Num; ++i)
	{
		m_pTeamIcon[i]->setEnabled(false);
	}
	for (size_t i=1,j=0; i<Team_Max_Num&&j<CTeamUI::s_teamInfo.member_list.size(); ++i,++j)
	{
		//跳过自己
		if (CTeamUI::s_teamInfo.member_list[j].id == gHero->GetId())
		{
			j++;
			if(j>=CTeamUI::s_teamInfo.member_list.size()) return;
		}
		m_pTeamIcon[i]->setEnabled(true);
		m_pTeamIcon[i]->loadTexture(GetWorldMapCareerIcon(CTeamUI::s_teamInfo.member_list[j].career));
	}
}

void CUIWorldMap::SetMode(WorldMapMode mode)
{
	m_pPlaceList->setEnabled(false);
	m_pCopyList->setEnabled(false);
	m_pPrepare->setEnabled(false);
	m_pSlider->setEnabled(false);
	switch (mode)
	{
	case WorldMapMode_PlaceList:
		m_pPlaceList->setEnabled(true);
		break;
	case WorldMapMode_CopyList:
		m_pCopyList->setEnabled(true);
		m_pCopyList->setVisible(true);
		m_pSlider->setEnabled(true);
		break;
	case WorldMapMode_Prepare:
		m_pCopyList->setEnabled(true);
		m_pCopyList->setVisible(false);
		m_pPrepare->setEnabled(true);
		break;
    default:
        break;
	}
	m_curMode = mode;
}

void CUIWorldMap::SetMatchBtnStatus(MatchBtnStatus btnStatus)
{
	if(GetMatchBtnStatus() == btnStatus)
		return;

	m_matchBtnStatus = btnStatus;
	UpdateMatchBtn();
}

void CUIWorldMap::ShowLocaleList(int nWorldMapId)
{
	SetMode(WorldMapMode_CopyList);

	m_pCopyListView->removeAllItems();
	vector<GameCopy*> gameCopys = gCopyDataMgr->GetLocaleList(nWorldMapId);

	for (unsigned int i=0; i<gameCopys.size(); ++i)
	{
		Button* pParentCopyItem = (Button*)m_pParentCopyItem->clone();
		CC_SAFE_RETAIN(pParentCopyItem);
		pParentCopyItem->removeFromParent();
		pParentCopyItem->setEnabled(true);
		pParentCopyItem->setVisible(true);
		pParentCopyItem->setTag(gameCopys[i]->localeId);
		pParentCopyItem->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickLocale));
		m_pCopyListView->pushBackCustomItem(pParentCopyItem);
		CC_SAFE_RELEASE(pParentCopyItem);
		ShowGameCopyInfo(pParentCopyItem,gameCopys[i],false);
	}
	m_pSlider->setList(m_pCopyListView, Slider::ListType::LISTVIEW_TYPE);
}

void CUIWorldMap::ShrinkGameCopyList()
{
	if(m_nCurLocaleId == -1) return;
	vector<GameCopy*> gameCopys = gCopyDataMgr->GetMapList(m_nCurLocaleId);
	if (gameCopys.size()>1)
	{
		for (unsigned int i=0; i<gameCopys.size(); ++i)
		{
			m_pCopyListView->removeItem(m_nChildIdxInListView);
		}
	}
	m_nCurLocaleId = -1;
}

void CUIWorldMap::SpreadGameCopyList(unsigned int nIdx,vector<GameCopy*>& gameCopys)
{
	for (unsigned int i=0; i<gameCopys.size(); ++i)
	{
		Button* pChildCopyItem = (Button*)m_pChildCopyItem->clone();
		CC_SAFE_RETAIN(pChildCopyItem);
		pChildCopyItem->removeFromParent();
		pChildCopyItem->setEnabled(true);
		pChildCopyItem->setVisible(true);
		pChildCopyItem->setTouchEnabled(true);
		pChildCopyItem->setTag(gameCopys[i]->mapId);
		pChildCopyItem->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickChildCopyItem));
		m_nChildIdxInListView = nIdx+1;
		if(m_nChildIdxInListView>=m_pCopyListView->getItems().size())
		{
			m_pCopyListView->pushBackCustomItem(pChildCopyItem);
		}
		else
		{
			m_pCopyListView->insertCustomItem(pChildCopyItem,m_nChildIdxInListView);
		}
		CC_SAFE_RELEASE(pChildCopyItem);
		ShowGameCopyInfo(pChildCopyItem,gameCopys[i],true);
	}
}

void CUIWorldMap::ShowPrepare(GameCopy* gameCopy)
{
	MapCfg* pMagCfg = MapData.get(gameCopy->mapId);
	if(!pMagCfg) return;

	SetMode(WorldMapMode_Prepare);
	ShowGameCopyInfo(m_pChildCopyItem,gameCopy,true);
	SetMatchModeTxt();
	m_pCopyMode->setText(GetMapPlayDes(GameMapPlayType(pMagCfg->play_type)));
	m_pCamp->setText(GetMapEnemyDes(GameMapEnemyType(pMagCfg->enemy_faction)));

	//任务奖励
	TaskAward *pAward=gTaskManager->GetMapTaskAward(gameCopy->mapId);
	gGridsManager->removeAllGrids(emGrids_TaskAward);
	if (pAward)
	{
		size_t i = 0;
		for (; i < pAward->vtrItems.size(); i++)
		{
			gGridsManager->insertGrid(emGrids_TaskAward, i, pAward->vtrItems[i].pItem->id, pAward->vtrItems[i].nNum);
		}
	}

	m_curGameCopy = gameCopy;
}

void CUIWorldMap::ShowGameCopyInfo(Widget* pUI,GameCopy* gameCopy,bool bNeedCopyIcon)
{
	MapCfg* pMapCfg = MapData.get(gameCopy->mapId);
	LocaleCfg* pLocaleCfg = LocaleTableData.get(gameCopy->localeId);
	if((pMapCfg&&pLocaleCfg)==NULL) return;

	Button* pLocaleIcon = dynamic_cast<Button*>(pUI);
	Text* pLocaleName = (Text*)pUI->getChildByName("LocaleName");
	Text* pCopyName = (Text*)pUI->getChildByName("CopyName");
	Text* pCopyLv = (Text*)pUI->getChildByName("Lv");
	Widget* pLock = pUI->getChildByName("Lock");
	Widget* pTitleIconXS = pUI->getChildByName("CopyType_0");
	Widget* pTitleIconEM = pUI->getChildByName("CopyType_1");
	Widget* pTitleIconCT = pUI->getChildByName("CopyType_2");

	if(pLocaleIcon)
	{
		string pathIcon = CCString::createWithFormat("%s%s",ICON_PATH_LOCALE,pLocaleCfg->icon.c_str())->getCString();
		pLocaleIcon->loadTextures(pathIcon,pathIcon,pathIcon);
	}
	pLocaleName->setText(pLocaleCfg->name);
	pCopyName->setText(pMapCfg->name);
	pCopyLv->setText(CCString::createWithFormat("Lv.%d",pMapCfg->level_l)->getCString());
	if(pLock) pLock->setVisible(!gameCopy->unLock);
	if (pTitleIconXS&&pTitleIconEM&&pTitleIconCT)
	{
		vector<GameCopy*> gameCopys = gCopyDataMgr->GetMapList(gameCopy->localeId);
		pTitleIconXS->setVisible(gCopyDataMgr->IsSpecialTaskExist(gameCopys,GameMapTaskType_XS));
		pTitleIconEM->setVisible(gCopyDataMgr->IsSpecialTaskExist(gameCopys,GameMapTaskType_EM));
		pTitleIconCT->setVisible(gCopyDataMgr->IsSpecialTaskExist(gameCopys,GameMapTaskType_CT));
	}

	if(!bNeedCopyIcon) return;
	ImageView* pTypeImgBg = (ImageView*)gCtrlAllocator->LoadCtrl(CCString::createWithFormat("CopyTypeBG%d",pMapCfg->task_copy_type)->getCString());
	ImageView* pTypeImgTitle = (ImageView*)gCtrlAllocator->LoadCtrl(CCString::createWithFormat("CopyTypeTitle%d",pMapCfg->task_copy_type)->getCString());
	Size size = pUI->getContentSize();
	Point Pos(size.width,size.height);
	if(pTypeImgBg) { 
		pUI->removeChildByTag(11);
		pUI->addChild(pTypeImgBg);
		pTypeImgBg->setTag(11); 
		Size mySize = pTypeImgBg->getSize();
		pTypeImgBg->setPosition(Pos-Point(mySize.width/2,mySize.height/2));
	}
	if(pTypeImgTitle) {
		pUI->removeChildByTag(22); 
		pUI->addChild(pTypeImgTitle);
		pTypeImgTitle->setTag(22);
		Size mySize = pTypeImgTitle->getSize();
		pTypeImgTitle->setPosition(Pos-Point(mySize.width/2,mySize.height/2));
	}
}

void CUIWorldMap::ShowMatch()
{
	//随机副本
	if (gMacthMachine->GetMatchCopyMapIdToEnter() == 0)
	{
		m_pCountTitle->ParseAndLayout(STR_Match_randomCopy);
		return;
	}

	GameCopy* pGameCopy = gCopyDataMgr->GetGameCopy(gMacthMachine->GetMatchCopyMapIdToEnter());
	if(!pGameCopy) return;
	LocaleCfg* pLocaleCfg = LocaleTableData.get(pGameCopy->localeId);
	MapCfg* pMapCfg = MapData.get(pGameCopy->mapId);
	if(pLocaleCfg&&pMapCfg)
	{
		m_pCountTitle->ParseAndLayout(CCString::createWithFormat("%s-%s",pLocaleCfg->name.c_str(),pMapCfg->name.c_str())->getCString());
	}
}

void CUIWorldMap::UpdateMatchBtn()
{
	m_pBtnCountLeft->setVisible(false);
	m_pBtnCountRight->setVisible(false);
	m_pBtnCountCenter->setVisible(false);
	m_pBtnCountLeft->setTouchEnabled(false);
	m_pBtnCountRight->setTouchEnabled(false);
	m_pBtnCountCenter->setTouchEnabled(false);

	switch (GetMatchBtnStatus())
	{
	case MatchBtnStatus_Cancel:
		ShowBtnCancel();
		break;
	case MatchBtnStatus_CancelAndStart:
		ShowBtnCancelAndStart();
		break;
	case MatchBtnStatus_Started:
		ShowBtnStarted();
		break;
	case MatchBtnStatus_Prepare:
		ShowBtnPrepare();
		break;
	case MatchBtnStatus_PrepareOver:
		ShowBtnPrepareOver();
		break;
	default:
		break;
	}
}

void CUIWorldMap::ShowBtnCancel()
{
	m_pBtnCountCenter->setVisible(true);
	m_pBtnCountCenter->setTouchEnabled(true);
	m_pBtnCountCenter->setTitleText(STR_Match_Cancle1);
	m_pBtnCountCenter->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickCancelMatch));
}

void CUIWorldMap::ShowBtnCancelAndStart()
{
	//此处不能使用enable，会被父节点的m_pMatch->setEnable覆盖
	m_pBtnCountLeft->setVisible(true);
	m_pBtnCountRight->setVisible(true);
	m_pBtnCountLeft->setTouchEnabled(true);
	m_pBtnCountRight->setTouchEnabled(true);

	m_pBtnCountLeft->setTitleText(STR_Match_Cancle1);
	m_pBtnCountLeft->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickCancelMatch));
	m_pBtnCountRight->setTitleText(STR_Match_Start);
	m_pBtnCountRight->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickStartImmediately));
}

void CUIWorldMap::ShowBtnStarted()
{
	m_pBtnCountLeft->setVisible(true);
	m_pBtnCountRight->setVisible(true);
	m_pBtnCountLeft->setTouchEnabled(true);
	m_pBtnCountRight->setTouchEnabled(false);
}

void CUIWorldMap::ShowBtnPrepare()
{
	m_pBtnCountCenter->setVisible(true);
	m_pBtnCountCenter->setTouchEnabled(true);
	m_pBtnCountCenter->setTitleText(STR_Match_prepare);
	m_pBtnCountCenter->addTouchEventListener(this,toucheventselector(CUIWorldMap::clickPrepare));
}

void CUIWorldMap::ShowBtnPrepareOver()
{
	m_pBtnCountCenter->setVisible(true);
	m_pBtnCountCenter->setTitleText(STR_Match_prepare_over);
	m_pBtnCountCenter->addTouchEventListener(nullptr,nullptr);
}

void CUIWorldMap::SetInviterMatchData()
{
	switch (gMacthMachine->GetMatchStatus())
	{
	case MatchStatus_NoTeam_Single:
	case MatchStatus_NoTeam_Invite:
		gMacthMachine->SetMatchCountSeconds(5.0f);
		gMacthMachine->SetMatchCopyMapIdToEnter(m_curGameCopy->mapId);
		break;
	case MatchStatus_NoTeam_Match:
		gMacthMachine->SetMatchCountSeconds(-1.0f);
		gMacthMachine->SetMatchCopyMapIdToEnter(m_curGameCopy->mapId);
		break;
	default:
		break;
	}
}

void CUIWorldMap::SetInviterRandomMatchData()
{
	gMacthMachine->SetMatchMode(MatchMode_Match);
	gMacthMachine->UpdateMatchStatus();
	gMacthMachine->SetMatchCopyMapIdToEnter(0);

	switch (CTeamUI::GetTeamStatus())
	{
	case TeamStatus_NoTeam:
		gMacthMachine->SetMatchCountSeconds(-1.0f);
		break;
	case TeamStatus_TeamNoFull:
	case TeamStatus_TeamFull:
		gMacthMachine->SetMatchCountSeconds(60.0f);
		break;
	default:
		break;
	}
}

void CUIWorldMap::clickWorldPlace( Ref* pSender,TouchEventType type )
{
	if (TOUCH_EVENT_ENDED == type)
	{
		int nWorldPlaceIdx = ((Widget*)(pSender))->getTag();
		WorldPlaces& worldPlaces = gCopyDataMgr->GetWorldPlaces();
		if(nWorldPlaceIdx>=worldPlaces.size()) return;

		if (!worldPlaces[nWorldPlaceIdx].unLock)
		{
			gMessageCenter->SystemMessage(1214);
		}
		else
		{
			ShowLocaleList(worldPlaces[nWorldPlaceIdx].worldMapId);
			m_nBigPlaceIdx = nWorldPlaceIdx;
		}
	}
}

void CUIWorldMap::clickLocale(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		int nLocaleId = ((Widget*)pSender)->getTag();
		GameCopy* pGameBaseCopy = NULL;
		vector<GameCopy*> gameCopys = gCopyDataMgr->GetMapListAndBaseGameCopy(nLocaleId,pGameBaseCopy);
		if(!pGameBaseCopy) return;
		if (!pGameBaseCopy->unLock)
		{
			gMessageCenter->SystemMessage(1214);
			return;
		} 
		bool bHasTaskCopy = gameCopys.size()>1;
		if(nLocaleId == m_nCurLocaleId && bHasTaskCopy) return;
		ShrinkGameCopyList();
		if (bHasTaskCopy)
		{
			int nIdxInListView = m_pCopyListView->getIndex((Widget*)pSender);
			SpreadGameCopyList(nIdxInListView,gameCopys);
		}
		else
		{
			if(gMacthMachine->IsMatchStarted())
			{
				gMessageCenter->SystemMessage(1010);
			}
			else
			{
				ShowPrepare(gameCopys[0]);
			}
		}
		m_nCurLocaleId = nLocaleId;
	}
}

void CUIWorldMap::clickChildCopyItem(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		if(gMacthMachine->IsMatchStarted())
		{
			gMessageCenter->SystemMessage(1010);
			return;
		}
		int nMapId = ((Widget*)pSender)->getTag();
		GameCopy* pGameCopy = gCopyDataMgr->GetGameCopy(nMapId);
		if(pGameCopy) ShowPrepare(pGameCopy);
	}
}

void CUIWorldMap::clickCloseBtn(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		WorldMapMode mode = GetMode();
		switch (mode)
		{
		case WorldMapMode_PlaceList:
			gGameUILayer->close(this);
			break;
		case WorldMapMode_CopyList:
			SetMode(WorldMapMode_PlaceList);
			break;
		case WorldMapMode_Prepare:
			ShowLocaleList(m_curGameCopy->worldMapId);
			break;
		default:
			break;
		}
	}
}
void CUIWorldMap::clickChatBtn(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		gGameUILayer->close(IDU_CHATMAINUI);
		ChatMainUI* pChatUI = (ChatMainUI*)gGameUILayer->open(IDU_CHATMAINUI);
		if(pChatUI)
		{
			pChatUI->ShowFixedChannel(ChannelType_Team);
			pChatUI->setPosition(Point(63.0f,-34.0f));
		}
	}
}
void CUIWorldMap::clickRandomBtn(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		SetInviterRandomMatchData();
		pk::C2GS_ReqEnterCopyMap cmd;
		cmd.npcId = 0;
		cmd.npcDataID = 0; 
		cmd.enterMapDataId = 0; 
		cmd.enterType = gMacthMachine->GetMatchMode();
		cmd.Send(gNetSocket);
	}
}

void CUIWorldMap::clickTeamBtn(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		openTeamUI(UiOpenType_FromWorldMapUI);
	}
}

void CUIWorldMap::clickStartCopy(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		gMacthMachine->SetMatchMode(MatchMode(m_nMatchModeIdx?m_nMatchModeIdx:3));
		gMacthMachine->UpdateMatchStatus();

		if(gMacthMachine->IsMatchStarted())
		{
			gMessageCenter->SystemMessage(1010);
			return;
		}
		if (gMacthMachine->GetMatchStatus() == MatchStatus_TeamNoFull_Single || gMacthMachine->GetMatchStatus() == MatchStatus_TeamFull_Single)
		{
			gMessageCenter->SystemMessage(1014);
			return;
		}

		MapCfg* pMapCfg = MapData.get(m_curGameCopy->mapId);
		if(!pMapCfg) return;

		if (GameMapType(pMapCfg->type) == GameMapType_SiglePlayer)
		{
			if (CTeamUI::GetTeamStatus() != TeamStatus_NoTeam || gMacthMachine->GetMatchMode() != MatchMode_Single)
			{
				gMessageCenter->SystemMessage(1014);
				return;
			}
		}

		SetInviterMatchData();
		pk::C2GS_ReqEnterCopyMap cmd;
		cmd.npcId = 0;
		cmd.npcDataID = 0;
		cmd.enterMapDataId = m_curGameCopy->mapId;
		cmd.enterType = (int)gMacthMachine->GetMatchMode();
		cmd.Send(gNetSocket);
	}
}

void CUIWorldMap::clickBackFromPrepare(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		SetMode(WorldMapMode_CopyList);
	}
}

void CUIWorldMap::clickMatch(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		Point pos = getPositionInUILayer(m_pMenuMatchBg)-Point(0,32);
		CMenuForMatchMode::PopupMenu(pos,this,SEL_SelectIndexEvent(&CUIWorldMap::clickMatchItem),GameString.get(1503)->value.c_str(),GameString.get(1504)->value.c_str(),GameString.get(1505)->value.c_str(),0);
	}
}

void CUIWorldMap::clickMatchItem(int nIdx)
{
	switch (nIdx)
	{
	case 0:
		gMacthMachine->SetMatchMode(MatchMode_Match);
		break;
	case 1:
		gMacthMachine->SetMatchMode(MatchMode_Single);
		break;
	case 2:
		gMacthMachine->SetMatchMode(MatchMode_Invite);
		break;
	}
	gMacthMachine->UpdateMatchStatus();
	m_nMatchModeIdx = nIdx;
	SetMatchModeTxt();
}

void CUIWorldMap::SetMatchModeTxt()
{
	switch (gMacthMachine->GetMatchMode())
	{
	case MatchMode_Match:
		m_pMatchMode->setText(GameString.get(1503)->value.c_str());
		break;
	case MatchMode_Single:
		m_pMatchMode->setText(GameString.get(1504)->value.c_str());
		break;
	case MatchMode_Invite:
		m_pMatchMode->setText(GameString.get(1505)->value.c_str());
		break;
    default:
        break;
	}
}

void CUIWorldMap::clickCancelMatch(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		bool bNormalCancel = gMacthMachine->GetMatchMode() != MatchMode_Match;
		bNormalCancel |= ((gMacthMachine->GetMatchMode()==MatchMode_Match)&&gMacthMachine->GetMatchCountSeconds()>0.0f);
		if (bNormalCancel)
		{
			pk::C2GS_SponsorCancelEnterCopyMap cmd;
			cmd.curMapDataId = gMap->getMapDataID();
			cmd.Send(gNetSocket);
		} 
		else
		{
			pk::C2GS_SponsorCancelMatchEnter cmd;
			cmd.curMapDataId = gMap->getMapDataID();
			cmd.enterMapDataId = gMacthMachine->GetMatchCopyMapIdToEnter();
			cmd.Send(gNetSocket);
		}
	}
}
void CUIWorldMap::clickStartImmediately(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		pk::C2GS_SponsorExitMatchEnterCopyMapNow cmd;
		cmd.curMapDataId = gMap->getMapDataID();
		cmd.enterMapDataId = gMacthMachine->GetMatchCopyMapIdToEnter();
		cmd.Send(gNetSocket);
	}
}

void CUIWorldMap::clickPrepare(Ref* pSender,TouchEventType type)
{
	if (TOUCH_EVENT_ENDED == type)
	{
		gMacthMachine->SetMatchPrepared(true);
		pk::C2GS_PrepareCompleteEnterCopy cmd;
		cmd.sponsorId = gMacthMachine->GetMatchInvitedPlayerId();
		cmd.Send(gNetSocket);
	}
}
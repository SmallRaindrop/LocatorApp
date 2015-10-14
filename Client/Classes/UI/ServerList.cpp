#include "ServerList.h"
#include "UIHelper.h"
#include "GameScene/GameManager.h"
#include "Net/NetDispatcher.h"
#include "GameScene/LoginScene.h"

#define  LASTSERVER       "lastServer%d"
#define  MAX_LASTSERVER    8

#define  Recommend_Image  "assets/ui/login/img_tongchang.png"
#define  Hot_Image        "assets/ui/login/img_huobao.png"
#define  Full_Image       "assets/ui/login/img_yongji.png"
#define  Defend_Image     "assets/ui/login/img_weihu.png"



enum Btn_TAG
{
	CallBack_TAG,        //返回按钮TAG
	EnterGame_TAG,       //进入游戏按钮TAG
	SelectServer_TAG,    //选择服务器TAG
	ClosePanel_TAG,      //关闭服务器列表
};

enum ServerStatusString
{
	New_Str     = 915,  //新服
	Recom_Str   = 916,  //推荐
	Hot_Str     = 917,  //火爆
	Full_Str    = 918,  //爆满
	Def_Str     = 919,  //维护 
	Stop_Str    = 920,  //停服
	Test_Str    = 921,  //测试
};

CServerList::CServerList() 
	:GameUI(IDU_SERVERLIST,JSONFILE_SERVERLIST)
	,m_serverStatus(nullptr)
	,m_panelServer(nullptr)
	,m_curAreaIndex(0)
{
	m_lastServerList.clear();
	m_gameServers.clear();
	m_gameAreaServers.clear();
	m_curServerInfo.id = -1;
}

CServerList::~CServerList()
{
	m_lastServerList.clear();
	m_gameServers.clear();
	m_gameAreaServers.clear();
}

bool CServerList::onInit()
{
// 	m_pBigRegion[0] = (CheckBox*)(Helper::seekWidgetByName(m_pWidget,"Region0"));
// 	m_pBigRegion[1] = (CheckBox*)(Helper::seekWidgetByName(m_pWidget,"Region1"));
// 	m_pBigRegion[2] = (CheckBox*)(Helper::seekWidgetByName(m_pWidget,"Region2"));
// 	m_pBigRegion[3] = (CheckBox*)(Helper::seekWidgetByName(m_pWidget,"Region3"));
// 	m_pBigRegion[4] = (CheckBox*)(Helper::seekWidgetByName(m_pWidget,"Region4"));
// 	m_pBigRegion[5] = (CheckBox*)(Helper::seekWidgetByName(m_pWidget,"Region5"));
// 	Widget* pRegionPanel = Helper::seekWidgetByName(m_pWidget,"LabelPanel");
// 	Button* pBack = (Button*)(Helper::seekWidgetByName(m_pWidget,"Back"));
// 	m_pEnterServer = (Button*)(Helper::seekWidgetByName(m_pWidget,"Enter"));
// 	if ( !pBack || !m_pEnterServer || !pRegionPanel)
// 	{
// 		return false;
// 	}
// 	m_pEnterServer->addTouchEventListener(this,toucheventselector(CServerList::clickEnterServer));
// 	pBack->addTouchEventListener(this,toucheventselector(CServerList::clickBack));
// 
// 	m_pRadioRegion = RadioButtonSet::create();
// 	pRegionPanel->addChild(m_pRadioRegion);
// 	m_pRadioRegion->AddButton(m_pBigRegion[0]);
// 	m_pRadioRegion->AddButton(m_pBigRegion[1]);
// 	m_pRadioRegion->AddButton(m_pBigRegion[2]);
// 	m_pRadioRegion->AddButton(m_pBigRegion[3]);
// 	m_pRadioRegion->AddButton(m_pBigRegion[4]);
// 	m_pRadioRegion->AddButton(m_pBigRegion[5]);
// 	m_pRadioRegion->SetSelectEvent(this, SEL_SelectIndexEvent(&CServerList::clickRegionItem));
// 
// 	m_pRegionServerUI = Helper::seekWidgetByName(m_pWidget,"RegionServers");
// 	m_pRecommendServerUI = Helper::seekWidgetByName(m_pWidget,"Recommend");
// 
// 	for (int i=0; i<Region_Server_Size; ++i)
// 	{
// 		m_pServerBtns[i] = (Button*)(Helper::seekWidgetByName(m_pRegionServerUI,CCString::createWithFormat("%d",i)->getCString()));
// 		m_pServerBtns[i]->addTouchEventListener(this,toucheventselector(CServerList::clickServerItem));
// 	}
// 
// 	m_pSelected = Helper::seekWidgetByName(m_pWidget,"Selected");
// 	m_pSelected->setPosition(m_pServerBtns[0]->getPosition());
// 
// 	m_pServerLastLogin = (Button*)Helper::seekWidgetByName(m_pRecommendServerUI,"ServerLastLogin");
// 	m_pServerRecommend = (Button*)Helper::seekWidgetByName(m_pRecommendServerUI,"ServerRecommend");
// 	m_pServerLastLogin->addTouchEventListener(this,toucheventselector(CServerList::clickServerItem));
// 	m_pServerRecommend->addTouchEventListener(this,toucheventselector(CServerList::clickServerItem));

	m_panelServer = dynamic_cast<Layout*>(Helper::seekWidgetByName(m_pWidget,"Panel_list"));
	if(m_panelServer)
	{
		m_panelServer->setVisible(false);
		m_serverList = dynamic_cast<ListView*>(m_panelServer->getChildByName("ListView_server"));
		auto * areastr = String::createWithFormat("Button_Server%d", 0);
		for (int i = 0; i < AreaServer_Size; ++i)
		{
			areastr = String::createWithFormat("Button_Server%d", i);
			m_areaServerBtn[i] = dynamic_cast<Button*>(m_panelServer->getChildByName(areastr->getCString()));
			m_areaServerBtn[i]->setVisible(false);
			m_areaServerBtn[i]->setTag(i);
			m_areaServerBtn[i]->setPressedActionEnabled(true);
			m_areaServerBtn[i]->addTouchEventListener(this, toucheventselector(CServerList::serverCallBack));
		}
	}

	//返回按钮
	auto  pCallBack_btn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget,"Button_3")); 
	pCallBack_btn->setPressedActionEnabled(true);
	pCallBack_btn->setTag(CallBack_TAG);
	pCallBack_btn->addTouchEventListener(this, toucheventselector(CServerList::callBackFunc));

	//进入游戏按钮
	auto pEnterGame_btn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget,"Button_2"));
	pEnterGame_btn->setTag(EnterGame_TAG);
	pEnterGame_btn->addTouchEventListener(this, toucheventselector(CServerList::callBackFunc));

	//选择服务器按钮
	auto pSelectServer_Img = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget, "Label_btn"));
	pSelectServer_Img->setTag(SelectServer_TAG);
	pSelectServer_Img->setTouchScaleChangeEnabled(true);
	pSelectServer_Img->addTouchEventListener(this, toucheventselector(CServerList::callBackFunc));

	//关闭服务器列表容器按钮
	auto pClosedPanel_btn = dynamic_cast<Button*>(Helper::seekWidgetByName(m_pWidget, "Button_close"));
	pClosedPanel_btn->setPressedActionEnabled(true);
	pClosedPanel_btn->setTag(ClosePanel_TAG);
	pClosedPanel_btn->addTouchEventListener(this, toucheventselector(CServerList::callBackFunc));

	return true;
}

void CServerList::onEnter()
{
	GameUI::onEnter();
	setDefaultShow();
}

void CServerList::onExit()
{
	GameUI::onExit();
}

void CServerList::onOpen()
{
	
}

void CServerList::onClose()
{
	
}


void CServerList::setDefaultShow()
{
	m_panelServer->setVisible(false);
	if(m_gameAreaServers.size()> 0)
	{
		if(m_gameAreaServers[0].size()>0)
		{
			m_curServerInfo = m_gameAreaServers[0][0];
			setCurAreaSelectServ(Recommendation_Type, m_curServerInfo.id, m_curServerInfo.name.c_str());
		}
		else if(m_gameAreaServers.size()> 1 && m_gameAreaServers[1].size()>0)
		{
			m_curServerInfo = m_gameAreaServers[1][0];
			setCurAreaSelectServ(Recommendation_Type, m_curServerInfo.id, m_curServerInfo.name.c_str());
		}
	}
}

template <typename T>
void CServerList::setStatus(ServerAreaType _status, const T& pPtr,int _type /* = 0 */)
{
	auto imagStr = "";
	auto textStr = "";
	switch (_status)
	{
	case Recommendation_Type:
		imagStr = Recommend_Image;
		textStr = GameString.get(Recom_Str)->value.c_str();
		break;
	case Hot_Type:
		imagStr = Hot_Image;
		textStr = GameString.get(Hot_Str)->value.c_str();
		break;
	case Full_Type:
		imagStr = Full_Image;
		textStr = GameString.get(Full_Str)->value.c_str();
		break;
	case Defend_Type:
		imagStr = Defend_Image;
		textStr = GameString.get(Def_Str)->value.c_str();
		break;
	case Close_Type:
		imagStr = Defend_Image;
		textStr = GameString.get(Stop_Str)->value.c_str();
		break;
	case Test_Type:
		imagStr = Recommend_Image;
		textStr = GameString.get(Recom_Str)->value.c_str();
		break;
	case NewArea_Type:
		imagStr = Recommend_Image;
		textStr = GameString.get(Recom_Str)->value.c_str();
		break;
	default:
		break;
	}
	if(_type == 1)
	{
		dynamic_cast<Text*>(pPtr)->setText(textStr);
	}
	else
	{
		dynamic_cast<ImageView*>(pPtr)->loadTexture(imagStr);
	}
	
}

void CServerList::changAreaBtnStatusByIdx(int _idx)
{
	if(m_serverList)
	{
		auto listItem = m_serverList->getItems();
		for (auto iter : listItem)
		{
			dynamic_cast<Button*>(iter)->setButtonShowType(Normal_TYPE);
		}
		if(listItem.size() > _idx)
		{
			dynamic_cast<Button*>(listItem.at(_idx))->setButtonShowType(Press_TYPE);
		}
	}
}

void CServerList::setAreaListBtn(int _cnt)
{
	if(m_serverList)
	{
		auto idx = 0;
		auto listItem = m_serverList->getItems();
		for (int i = 1; i < listItem.size(); i++)
		{
			m_serverList->removeItem(1);
		}
		auto btn = dynamic_cast<Button*>(m_serverList->getItem(0));
		btn->addTouchEventListener(this, toucheventselector(CServerList::areaCallBack));
		if(m_lastServerList.size() == 0)   //没有最近登录的服务列表
		{
			idx = 1;
			btn->setTitleText(m_gameServers[0].regionName.c_str());
		}
		m_curAreaIndex = idx;
		btn->setButtonShowType(Press_TYPE);
		btn->setTag(idx);   //默认最近登录的区域 tag为0
		for (int i = 1; i <= _cnt - idx; i++)
		{
			auto otherbtn = dynamic_cast<Button*>(btn->clone());
			otherbtn->setTitleFontName(btn->getTitleFontName());
			otherbtn->setTitleFontSize(btn->getTitleFontSize());
			otherbtn->setTitleColor(btn->getTitleColor());
			otherbtn->setTitleText(m_gameServers[0].regionName.c_str());
			otherbtn->setTag(i+idx);
			otherbtn->addTouchEventListener(this, toucheventselector(CServerList::areaCallBack));
			m_serverList->pushBackCustomItem(otherbtn);
		}
	}
}

void CServerList::setServerShow(ServerAreaType _status, int _serverid, const char * _name, int _idx)
{
	if(m_areaServerBtn[_idx])
	{
		auto serid = dynamic_cast<Text*>(m_areaServerBtn[_idx]->getChildByName("Label_listid"));
		if(serid)
		serid->setText(INT_TO_STRING(_serverid));
		auto sername = dynamic_cast<Text*>(m_areaServerBtn[_idx]->getChildByName("Label_sn"));
		if (sername)
		sername->setText(_name);
		//TODO  还未定
		auto statusLabel = dynamic_cast<Text*>(m_areaServerBtn[_idx]->getChildByName("Label_st"));
		if(statusLabel)
			setStatus(_status, statusLabel, 1);
		m_areaServerBtn[_idx]->setVisible(true);
		if(_status == Defend_Type || _status == Close_Type)
		{
			m_areaServerBtn[_idx]->setTouchEnabled(false);
		}
		m_areaServerBtn[_idx]->setTouchEnabled(true);
	}
}

void CServerList::setCurAreaSelectServ(ServerAreaType _status, int _serverid, const char * _name)
{
	auto serverid = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget,"Label_areaid"));
	if(serverid)
	serverid->setText(INT_TO_STRING(_serverid));
	auto servername = dynamic_cast<Text*>(Helper::seekWidgetByName(m_pWidget,"Label_areaname"));
	if(servername)
		servername->setText(_name);
	auto statusImag = dynamic_cast<ImageView*>(Helper::seekWidgetByName(m_pWidget, "Image_statu"));
	if(statusImag)
	{
		//TODO: 暂定未定
		setStatus(_status, statusImag);
	}
}

void CServerList::setCurAreaShow(int _areaid)
{

}

void CServerList::showAreaServerList(int _id)
{
	//先隐藏所有服务器
	for (int i = 0; i < AreaServer_Size; i++)
	{
		m_areaServerBtn[i]->setVisible(false);
	}
	auto idx = 0;
	for (auto iter : m_gameAreaServers[_id])
	{
		setServerShow(Recommendation_Type, iter.id, iter.name.c_str(), idx);
		idx += 1;
	}

}


std::vector<int> CServerList::getLastServerList()
{
	m_lastServerList.clear();
	for(int i = 0 ; i < MAX_LASTSERVER; i++)
	{
		auto str = String::createWithFormat(LASTSERVER, i);
		auto lastServerId = cocos2d::UserDefault::getInstance()->getIntegerForKey(str->getCString(),-1);
		if(lastServerId != -1)
		m_lastServerList.push_back(lastServerId);
	}
	return m_lastServerList;
}

void CServerList::saveLastServerLsit()
{
	if(m_curServerInfo.id >0)
	{
		//检测是否存在
		auto isExit = false;
		for(auto iter = m_lastServerList.begin(); iter != m_lastServerList.end(); ++iter)
		{
			if(*iter == m_curServerInfo.id)
			{
				m_lastServerList.erase(iter);
				m_lastServerList.insert(m_lastServerList.begin(), m_curServerInfo.id);
				isExit = true;
				break;
			}
		}
		if(!isExit)
		{
			if(m_lastServerList.size() < MAX_LASTSERVER)
			{
				m_lastServerList.insert(m_lastServerList.begin(), m_curServerInfo.id);
			}
			else
			{
				m_lastServerList.pop_back();
				m_lastServerList.insert(m_lastServerList.begin(), m_curServerInfo.id);
			}
		}

		for(size_t i = 0 ; i < m_lastServerList.size(); i++)
		{
			auto str = String::createWithFormat(LASTSERVER, (int)i);
			cocos2d::UserDefault::getInstance()->setIntegerForKey(str->getCString(),m_lastServerList.at(i));
		}
	}

}

pk::GameServerInfo CServerList::findServerById(int _id)
{
	pk::GameServerInfo temp;
	temp.id = -1;
	for (auto iter: m_gameServers)
	{
		if(iter.id == _id)
			return iter;
	}
	return temp;
}

pk::GameServerInfo CServerList::findServerByName(const char* _name)
{
	pk::GameServerInfo temp;
	temp.id = -1;
	for (auto iter: m_gameServers)
	{
		if(iter.name == _name)
			return iter;
	}
	return temp;
}

ServerInfoList CServerList::findServerByAreaName(const char* _name)
{
	std::vector<pk::GameServerInfo> temp;
	temp.clear();
	for (auto iter : m_gameServers)
	{
		if(iter.regionName == _name)
			temp.push_back(iter);
	}
	return temp;
}

void CServerList::Show(int regionCnt,vector<pk::GameServerInfo>& gameServers)
{
	CCLOG("CServerList::Show");
	//int lastServerId = cocos2d::UserDefault::getInstance()->getIntegerForKey("lastServerId",-1);
	m_gameServers = gameServers;
	if(m_gameServers.size() > 0)
	{
		//最近登录的服务器列表
		getLastServerList();

		//区域按钮
		setAreaListBtn(regionCnt);

		//最近登录服务器
		auto lastidx = 0;
		ServerInfoList temp;
		for (auto iter = m_lastServerList.begin(); iter != m_lastServerList.end(); ++iter)
		{
			auto pSer = findServerById(*iter);
			if(pSer.id != -1)
			{
				setServerShow(Recommendation_Type, pSer.id, pSer.name.c_str(), lastidx);
				lastidx += 1;
				temp.push_back(pSer);
			}
			else
			{
				iter = m_lastServerList.erase(iter);
				if(iter == m_lastServerList.end())
					break;
			}
		}
		m_gameAreaServers[0] = temp;   //默认第一数据为最近登录数据

		//区域服务器
		auto pAreaName = "";
		temp.clear();
		lastidx = 1;
		auto listsize = m_gameServers.size();
		auto pIndex = 0;     //收到服务器列表的下标
		for (auto iter : m_gameServers)
		{
			//只有一个
			if(listsize == 1)
			{
				temp.push_back(iter);
				m_gameAreaServers.insert(make_pair(lastidx,temp));
				break;
			}
			pIndex += 1;

			if(strcmp(pAreaName,"") == 0)
			{
				pAreaName = iter.regionName.c_str();
				temp.push_back(iter);
			}
			else if(strcmp(pAreaName,iter.regionName.c_str()) != 0)
			{
				m_gameAreaServers.insert(make_pair(lastidx,temp));
				temp.clear();
				lastidx += 1;
				pAreaName = iter.regionName.c_str();
			}
			else
			{
				temp.push_back(iter);
				if(pIndex == listsize)
					m_gameAreaServers.insert(make_pair(lastidx,temp));
			}

		}

		if(m_gameAreaServers[0].size() > 0)
		{
			showAreaServerList(0);
		}
		else
		{
			showAreaServerList(1);
		}
		
	}
	
	setDefaultShow();

	
// 	m_ServersSet.clear();
// 	map<string, int> Name2Index;
// 	for (size_t i = 0; i < gameServers.size(); i++)
// 	{
// 		map<string, int>::iterator it = Name2Index.find(gameServers[i].regionName);
// 		if (it == Name2Index.end())
// 		{
// 			Name2Index.insert(make_pair(gameServers[i].regionName, (int)Name2Index.size()));
// 			it = Name2Index.find(gameServers[i].regionName);
// 		}
// 		if (it->second>=(int)m_ServersSet.size())
// 		{
// 			m_ServersSet.resize(it->second+1);
// 		}
// 		m_ServersSet[it->second].push_back(gameServers[i]);
// 
// 		//上次登录
// 		if (gameServers[i].id == lastServerId)
// 		{
// 			m_pLastLoginServer=gameServers[i];
// 			m_bHasLastLogin = true;
// 		}
// 	}
// 
// 	if(!Name2Index.empty())
// 	{
// 		//推荐取最后一个
// 		ServerInfoList servers = m_ServersSet[Name2Index.size()-1];
// 		m_pRecommondServer = servers[servers.size()-1];
// 		m_bHasRecommond = true;
// 
// 		m_pRadioRegion->ClickButton(0);
// 		for (size_t i=0; i<6; ++i)
// 		{
// 			m_pBigRegion[i]->setEnabled(i<=Name2Index.size());
// 		}
// 	}
}

void CServerList::ShowRecommond()
{
// 	m_pRegionServerUI->setEnabled(false);
// 	m_pRecommendServerUI->setEnabled(true);
// 	m_pServerRecommend->setEnabled(m_bHasRecommond);
// 	m_pServerLastLogin->setEnabled(m_bHasRecommond);
// 
// 	if (m_bHasRecommond)
// 	{
// 		m_pServerRecommend->setTitleText(CCString::createWithFormat("%s-%s",m_pRecommondServer.regionName.c_str(),m_pRecommondServer.name.c_str())->getCString());
// 		m_pServerRecommend->setTag(m_pRecommondServer.id);
// 	}
// 	if (m_bHasLastLogin)
// 	{
// 		m_pServerLastLogin->setTitleText(CCString::createWithFormat("%s-%s",m_pLastLoginServer.regionName.c_str(),m_pLastLoginServer.name.c_str())->getCString());
// 		m_pServerLastLogin->setTag(m_pLastLoginServer.id);
// 	}
// 	Widget* pServerItem = m_bHasLastLogin?m_pServerLastLogin:NULL;
// 	if (!pServerItem)
// 	{
// 		pServerItem = m_bHasRecommond?m_pServerRecommend:NULL;
// 	}
// 	if (pServerItem)
// 	{
// 		clickServerItem(pServerItem,TOUCH_EVENT_ENDED);
// 	}
}

void CServerList::clickRegionItem(int nIndex)
{
// 	if (nIndex == 0)
// 	{
// 		//推荐
// 		ShowRecommond();
// 		return;
// 	}
// 
// 	m_pRegionServerUI->setEnabled(true);
// 	m_pRecommendServerUI->setEnabled(false);
// 	int regionIndex = (int)nIndex-1;
// 	int serverNum = m_ServersSet[regionIndex].size();
// 	for (int i=0; i<Region_Server_Size; ++i)
// 	{
// 		if (i<serverNum)
// 		{
// 			m_pServerBtns[i]->setEnabled(true);
// 			m_pServerBtns[i]->setTitleText(CCString::createWithFormat("%s-%s",m_ServersSet[regionIndex][i].regionName.c_str(),m_ServersSet[regionIndex][i].name.c_str())->getCString());
// 			m_pServerBtns[i]->setTag(m_ServersSet[regionIndex][i].id);
// 		} 
// 		else
// 		{
// 			m_pServerBtns[i]->setEnabled(false);
// 		}
// 	}
// 	if (!m_ServersSet[regionIndex].empty())
// 	{
// 		clickServerItem(m_pServerBtns[0],TOUCH_EVENT_ENDED);
// 	}
}

void CServerList::clickServerItem(Ref* pSender, TouchEventType type)
{
// 	if (TOUCH_EVENT_ENDED != type) return;
// 
// 	m_serverId = ((Widget*)pSender)->getTag();
// 	m_pSelected->setPosition(((Widget*)pSender)->getPosition());
// 	int serversIndex = m_pRadioRegion->GetSelIndex();
// 
// 	pk::GameServerInfo curServer;
// 	if (serversIndex == 0)
// 	{
// 		curServer = (m_serverId == m_pRecommondServer.id?m_pRecommondServer:m_pLastLoginServer);
// 	}
// 	else
// 	{
// 		for (size_t i=0; i<m_ServersSet[serversIndex-1].size(); ++i)
// 		{
// 			if (m_serverId == m_ServersSet[serversIndex-1][i].id)
// 			{
// 				curServer = m_ServersSet[serversIndex-1][i];
// 				break;
// 			}
// 		}
// 	}
// 	if (curServer.status == 100 || curServer.status == 1000)
// 	{
// 		m_pEnterServer->setBright(false);
// 		m_pEnterServer->setTouchEnabled(false);
// 	}
// 	else
// 	{
// 		m_pEnterServer->setBright(true);
// 		m_pEnterServer->setTouchEnabled(true);
// 	}
}

void CServerList::clickEnterServer(Ref* pSender, TouchEventType type)
{
// 	if (type == TOUCH_EVENT_ENDED)
// 	{
// 		gGameManager->SetServerID(m_serverId);
// 		pk::C2LS_RequestSelGameServer cmd;
// 		cmd.serverID = m_serverId;
// 		cmd.Send(gNetSocket);
// 		cocos2d::UserDefault::getInstance()->setIntegerForKey("lastServerId",m_serverId);
// 	}
}

void CServerList::clickBack(Ref* pSender, TouchEventType type)
{
	if (type == TOUCH_EVENT_ENDED)
	{
		pk::C2LS_BackPreStatus cmd;
		cmd.Send(gNetSocket);
		CLoginScene::gLoginLayer->OpenUI(login_ui_login);
	}
}


void  CServerList::callBackFunc(Ref* pSender, TouchEventType type)
{
	if(type  == TOUCH_EVENT_ENDED)
	{
		auto tag = dynamic_cast<Widget*>(pSender)->getTag();
		CCLOG("CServerList::callBackFunc tag = %d", tag);
		switch (tag)
		{
		case CallBack_TAG:
			{
				pk::C2LS_BackPreStatus cmd;
				cmd.Send(gNetSocket);
				CLoginScene::gLoginLayer->OpenUI(login_ui_login);
				break;
			}
		case EnterGame_TAG:
			{
				gGameManager->SetServerID(m_curServerInfo.id);
				pk::C2LS_RequestSelGameServer cmd;
				cmd.serverID = m_curServerInfo.id;
				cmd.Send(gNetSocket);
				saveLastServerLsit();
				break;
			}
		case SelectServer_TAG:
			m_panelServer->setVisible(!m_panelServer->isVisible());
			break;
		case ClosePanel_TAG:
			m_panelServer->setVisible(false);
			break;
		default:
			break;
		}
	}
}

void  CServerList::areaCallBack(Ref* pSender, TouchEventType type)
{
	if(type == TOUCH_EVENT_ENDED)
	{
		auto tag = dynamic_cast<Button*>(pSender)->getTag();
		CCLOG("CServerList::areaCallBack tag = %d", tag);
		showAreaServerList(tag);
		m_curAreaIndex = tag;
		changAreaBtnStatusByIdx(tag);
	}
}

void CServerList::serverCallBack( Ref* pSender, TouchEventType type )
{
	if(type == TOUCH_EVENT_ENDED)
	{
		auto tag = dynamic_cast<Button*>(pSender)->getTag();
		CCLOG("CServerList::serverCallBack tag = %d", tag);
		if(m_gameAreaServers[m_curAreaIndex].size() >= tag)
		{
			m_curServerInfo = m_gameAreaServers[m_curAreaIndex][tag];
			setCurAreaSelectServ(Recommendation_Type, m_curServerInfo.id,m_curServerInfo.name.c_str());
		}
	}
}

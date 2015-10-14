#include "DataPool.h"
#include "CommonDef.h"
#include "GameScene/GameUILayer.h"
#include "GameScene/Hero.h"
#include "UI/TeamUI.h"
#include "UI/copyMapUI.h"
#include "UI/UIWorldMap.h"
#include "GameScene/GameManager.h"

#define  Relative_XMLDATANAME    "RelativeDate_"     //记录格式
#define  RECORDE_CNT              20                 //记录条数
#define  SINGBOOK_GRIDMAX         64

DataPool_cl::DataPool_cl()
{
	m_relativeDate.clear();
	m_blacklist.clear();
	m_friendlist.clear();
	m_relativelist.clear();
	m_pLegionData = nullptr;
	initData();
}

DataPool_cl::~DataPool_cl()
{
	destoryData();
}

void DataPool_cl::destoryData()
{
	saveRelativeDate();
	for (auto iter : m_relativeDate)
	{
		delete iter.second;
		iter.second = nullptr;
	}
	m_relativeDate.clear();
	m_blacklist.clear();
	m_friendlist.clear();
	m_relativelist.clear();
	for (int i = 0; i < SignBook_Max; i++)
	{
		m_pSignBook[i]->clear();
		CC_SAFE_DELETE(m_pSignBook[i]);
	}
	for (auto iter: m_vManuFactureList)
	{
		delete iter;
		iter = nullptr;
	}
	m_vManuFactureList.clear();
	if(m_pLegionData)
	{
		delete m_pLegionData;
		m_pLegionData = nullptr;
	}
}
void DataPool_cl::initData()
{
	initRelativeData();
	for (int i = 0; i < SignBook_Max; i++)
	{
		m_pSignBook[i] = new CItemGridArray();
		m_pSignBook[i]->init((emGridsType)i, SINGBOOK_GRIDMAX);
		m_pSignBook[i]->ActiveAllGrid();
	}
	m_pLegionData = new Legion_cl();
}

void DataPool_cl::Update(float dt)
{
	m_matchMachine.Update(dt);
}

bool DataPool_cl::isExistPlayer( FriendInfo_v &_Tlist, int64 _id )
{
	for (auto iter: _Tlist)
	{
		if(iter.playerId == _id)
			return true;
	}
	return false;
}

void DataPool_cl::deletePListDataByPtr( FriendInfo_v &_Tlist, pk::Friend_Info* _Ptr )
{
	for(auto iter = _Tlist.begin(); iter != _Tlist.end(); ++iter)
	{
		if((*iter).playerId == _Ptr->playerId)
		{
			_Tlist.erase(iter);
			break;
		}
	}
}

void DataPool_cl::setPListDataByPtr( FriendInfo_v &_Tlist, pk::Friend_Info* _Ptr )
{
	for (auto iter : _Tlist)
	{
		if(iter.playerId == _Ptr->playerId)
		{
			iter = *_Ptr;
			break;
		}
	}
}

pk::Friend_Info* DataPool_cl::getFriendPlayerInfo( int64 _id )
{
	pk::Friend_Info* ret = nullptr;
	for ( size_t i = 0; i<m_friendlist.size();++i )
	{
		ret = &m_friendlist[i];
		if ( ret->playerId == _id )
		{
			return ret;
		}
	}

	return ret;
}

pk::Friend_Info* DataPool_cl::getRelativePlayerInfo( int64 _id )
{
	pk::Friend_Info* ret = nullptr;
	for ( size_t i = 0; i<m_relativelist.size();++i )
	{
		ret = &m_relativelist[i];
		if ( ret->playerId == _id )
		{
			return ret;
		}
	}

	return ret;
}

void DataPool_cl::deletePListDataByID( FriendInfo_v &_Tlist, int64 _id )
{
	for(auto iter = _Tlist.begin(); iter != _Tlist.end(); ++iter)
	{
		if((*iter).playerId == _id)
		{
			_Tlist.erase(iter);
			break;
		}
	}
}

void DataPool_cl::addPlayerToRecentList(pk::Friend_Info* _ptr)
{
	if(_ptr)
	{
		for (auto iter = m_relativelist.begin(); iter != m_relativelist.end(); iter++)
		{
			if((*iter).playerId == _ptr->playerId)
			{
				m_relativelist.erase(iter);
				break;
			}
		}
		if(m_relativelist.size() > 0)
		m_relativelist.insert(m_relativelist.begin(), *_ptr);
		else
		{
			m_relativelist.push_back(*_ptr);
		}
	}
}

void DataPool_cl::sapratePDataList(FriendInfo_v& _list)
{
	m_friendlist.clear();
	m_blacklist.clear();
	for (auto iter : _list)
	{
		if(iter.type == 1) //好友
		{
			m_friendlist.push_back(iter);
		}
		else if(iter.type == 3) //黑名单
		{
			m_blacklist.push_back(iter);
		}
	}
	sortPlayerByOnline(m_friendlist);
	sortPlayerByOnline(m_blacklist);
}

void DataPool_cl::setRelativeList(FriendInfo_v& _Tlist)
{
	for (auto _tIter: _Tlist)
	{
		for(auto iter = m_relativelist.begin(); iter != m_relativelist.end(); iter++)
		{
			if(_tIter.playerId == (*iter).playerId)
			{
				iter = m_relativelist.erase(iter);
				if(iter == m_relativelist.end())
					break;
			}
		}
		m_relativelist.push_back(_tIter);
	}
	sortPlayerByOnline(m_relativelist);
// 	if(m_relativelist.size() < RECORDE_CNT)
// 	{
// 		getRelativeData();
// 		int relaCnt = m_relativeDate.size(); 
// 		int insertIdx = 0;
// 		if(relaCnt < RECORDE_CNT - m_relativelist.size())
// 			insertIdx = relaCnt;
// 		else
// 		{
// 			insertIdx = RECORDE_CNT - m_relativelist.size();
// 		}
// 		for (int i = 0; i < insertIdx; i++)
// 		{
// 			pk::Friend_Info temp;
// 			temp.playerId = m_relativeDate[i]->playerid;
// 			temp.name = m_relativeDate[i]->name;
// 			temp.level = m_relativeDate[i]->level;
// 			temp.online = 0;
// 			m_relativelist.push_back(temp);
// 		}
// 	}
}

void DataPool_cl::initRelativeData()
{
	/************************************
	*           数据记录方式            *
	*  KEY  "RelativeDate_%d"           *
	*  VAL  "id:name:level              *    
	************************************/
	m_relativeDate.clear();
	for (int i = 0; i < RECORDE_CNT; i++)
	{
		RecentlyPlayerData_st * pData = new RecentlyPlayerData_st();
		string  pXml = GetStringToXML(FORMAT_TO_STRING(Relative_XMLDATANAME, i));
		if(pXml != "")
		{
			string pStr[3];
			memset(pStr, 0, sizeof(pStr));
			bool isContinue = false;
			for (int i = 0; i < 3; i++)
			{
				size_t pidx = pXml.find(":");
				if(pidx == string::npos)
				{
					isContinue = true;
					break;
				}
				pStr[i] = pXml.substr(0, pidx);
				pXml = pXml.substr(pidx);
			}
			if(isContinue)
				continue;
			if(pStr[0]!= "") pData->playerid = atoll(pStr[0].c_str());
			if(pStr[1]!= "") pData->name = pStr[1].c_str();
			if(pStr[2]!= "") pData->level = atoi(pStr[2].c_str());
			m_relativeDate.insert(pair<int, RecentlyPlayerData_st*>(pData->playerid, pData));
		}
		else
		{
			delete pData;
			pData = nullptr;
			break;
		}
	}
}

void DataPool_cl::saveRelativeDate()
{
	int datesize = m_relativeDate.size()>RECORDE_CNT?RECORDE_CNT:m_relativeDate.size();
	for (int i = 0; i < datesize; i++)
	{
		auto pData = m_relativelist[i];
		string pStr = FORMAT_TO_STRING("%lld:%s:%d", pData.playerId, pData.name.c_str(), pData.level);
		SetStringToXML(FORMAT_TO_STRING(Relative_XMLDATANAME, i), pStr);
	}
}

void DataPool_cl::sortPlayerByOnline( FriendInfo_v &_Tlist )
{
	//时序是在传入列表中已经判断过了
	//分在线、不在线
	FriendInfo_v online;
	FriendInfo_v unline;
	for(auto iter: _Tlist)
	{
		if(iter.online == 1)
		{
			online.push_back(iter);
		}
		else
		{
			unline.push_back(iter);
		}
	}
	size_t idx = 0;
	for(auto iter: _Tlist)
	{
		if(idx < online.size())
		{
			iter = online.at(idx);
		}
		else if(idx - online.size() < unline.size())
		{
				iter = unline.at(idx - online.size());
		}
		idx += 1;
	}

	online.clear();
	unline.clear();
}

bool sortByID(const pk::Mail_Info& m1, const pk::Mail_Info& m2){

	return m1.mailId > m2.mailId;
}

bool sortByState(const pk::Mail_Info& m1, const pk::Mail_Info& m2){
	if (m1.mailReadState == m2.mailReadState)
	{
		return m1.mailId > m2.mailId;
	}else
	{
		return m1.mailReadState < m2.mailReadState;
	}
}

void DataPool_cl::setMailList(MailInfo_v& _list)
{
	m_maillist.clear();
	for (auto iter : _list)
	{
		m_maillist.push_back(iter);
	}

	std::sort(m_maillist.begin(), m_maillist.end(), sortByID); // 先使用ID排序
	std::sort(m_maillist.begin(), m_maillist.end(), sortByState); // 再使用状态排序
}

void DataPool_cl::deleteMailByID(int64 _id )
{
	for(auto iter = m_maillist.begin(); iter != m_maillist.end(); ++iter)
	{
		if((*iter).mailId == _id)
		{
			m_maillist.erase(iter);
			break;
		}
	}
}

pk::Mail_Info* DataPool_cl::getMailByID(int64 _id )
{
	pk::Mail_Info* ret = nullptr;
	for ( size_t i = 0; i<m_maillist.size();++i )
	{
		ret = &m_maillist[i];
		if ( ret->mailId == _id )
		{
			return ret;
		}
	}
	return ret;
}

void DataPool_cl::setMailStateByID(int64 _id,int _state)
{
	for(auto iter = m_maillist.begin(); iter != m_maillist.end(); ++iter)
	{
		if((*iter).mailId == _id)
		{
			(*iter).mailReadState = _state;
			break;
		}
	}
}

void DataPool_cl::addMailToList(pk::Mail_Info _mail)
{
	m_maillist.push_back(_mail);

	std::sort(m_maillist.begin(), m_maillist.end(), sortByID); // 先使用ID排序
	std::sort(m_maillist.begin(), m_maillist.end(), sortByState); // 再使用状态排序
}

bool DataPool_cl::judgeType(CItem* item, SignBook _type)
{
	if(!item) return false;
	switch (_type)
	{
	case DataPool_cl::SignBook_InlayedBook:
		break;
	case DataPool_cl::SignBook_RelicBook:
		if(item->getSubType() == SubType_TIANSHU_RELIC || item->getSubType() == SubType_TIANSHU_HALO)
			return true;
		break;
	case DataPool_cl::SignBook_WeaponBook:
		if(item->getSubType() == SubType_TIANSHU_WUJI || item->getSubType() == SubType_TIANSHU_WEAPON)
			return true;
		break;
	case DataPool_cl::SignBook_PetBook:
		if(item->getSubType() == SubType_TIANSHU_PET)
		return true;
		break;
	case DataPool_cl::SignBook_MaterialBook:
		if(item->getSubType() == SubType_TIANSHU_MATERIAL)
		return true;
		break;
	case DataPool_cl::SignBook_Max:
		break;
	default:
		break;
	}
	return false;
}

CItemGridArray* DataPool_cl::saparateDataFromBag(ShowConditions_st st)
{
	if(st._type == SignBook_Max) return nullptr;
	m_pSignBook[st._type]->ClearData();
	CItemGridArray* pGridsData = gGridsManager->getGridsData(emGrids_BagBook);
	int idx = 0;
	for (int i = 0; i < BAG_SIZE_TIANSHU; i++)
	{
		CItemGrid* pItemGrid = pGridsData->GetItemGrid(i);
		if(!pItemGrid || !pItemGrid->GetItem() ||
			pItemGrid->GetItem()->getType() != emGrids_BagBook ) continue;

		//是否判断子类型
		if(st.IsSubType && !judgeType(pItemGrid->GetItem(), st._type)) continue;

		//是否升级过
		if(st.IsShowUp && pItemGrid->GetItem()->getItemInfo().strengthenLevel > 0) continue;

		//当前孔位是否使用
		if(st.IsCurUse && pItemGrid->GetItem()->getItemInfo().gridUsed) continue;

		//当前是否镶嵌
		if(st.IsCurInlay && pItemGrid->GetItem()->getItemInfo().curInlay) continue;

		//其他是否镶嵌
		if(st.IsOtherInlay && pItemGrid->GetItem()->getItemInfo().otherInlay) continue;

		//是否exp是否大于0
		if(st.exp && pItemGrid->GetItem()->getItemInfo().tian_shu_exp > 0)continue;
		m_pSignBook[st._type]->InsertItem(idx, pItemGrid->GetItem());
		idx += 1;
	}
	return m_pSignBook[st._type];
}



CItem* DataPool_cl::getHeroWeapon()
{
	CItemGridArray* pGridsData = gGridsManager->getGridsData(emGrids_Role);
	if(!pGridsData) return nullptr;
	CItemGrid* ret = pGridsData->GetItemGrid(1);
	if(!ret) return nullptr;
	else
	{
		return ret->GetItem();
	}
}

const vector<pk::EquipTianshu>& DataPool_cl::getCurRelicConfig()
{
	GodDeviceManager& relic = gHero->GetGodDeviceManager();
	return relic.GetIsDressGodPtr()->m_tianShuList;
	static vector<pk::EquipTianshu> ret;
	return ret;
}

const vector<pk::EquipTianshu>& DataPool_cl::getCurWeaponConfig()
{
	CItem * pweapon = getHeroWeapon();
	if(pweapon)
	{
		return  pweapon->getCurItemInfo().tianShuList;
	}
	static vector<pk::EquipTianshu> ret;
	return ret;
}

const vector<pk::EquipTianshu>& DataPool_cl::getCurPetConfig()
{
	static vector<pk::EquipTianshu> ret;
	return ret;
}

void DataPool_cl::initManuFactureList( pk::GS2C_ManufactureList_Ret* value )
{
	for (auto iter:value->manufactureList)
	{
		ManufactureData_st * st = new ManufactureData_st();
		st->serverData = iter;
		BluePrintCfg* blueprint = BluePrintData.get(iter.itemDataId);
		if(blueprint)
		{
			if(iter.eliminateCdFlag == 0) //没有是用过加速
			{
				st->productTime = blueprint->time;
				int left = iter.remainSeconds;
				st->leftTime = left > 0? left:0;
				st->baseGold = blueprint->gold;
				st->minGold = MAX(blueprint->gold/blueprint->time * 3600,1);
				int gold = (blueprint->gold/blueprint->time * 3600)*(st->leftTime/3600);
				st->curGold = MAX(gold, st->minGold);
				st->percent = (float)(st->productTime-left)/st->productTime  *100;
			}
			else
			{
				st->productTime = fasttime;
				int left = iter.remainSeconds;
				st->leftTime = left > 0? left:0;
				st->percent = (float)(st->productTime-left)/st->productTime *100;
			}
			st->startTime = gGameManager->GetCurrTimeMS()/1000;

			ItemCfg* blueitem = ItemData.get(iter.itemDataId);
			if(blueitem)
			{
				st->icon = blueitem->icon;
				st->iconname = blueitem->name;
			}
			ItemCfg* targetitem = ItemData.get(blueprint->item_id);
			if(targetitem)
			{
				st->targetname = targetitem->name;
			}
			
		}
		m_vManuFactureList.push_back(st);
	}
}

void DataPool_cl::addManuFactureData( pk::GS2C_New_Manufacture_Element_Ret* value )
{
	if(value->errorCode == 0)
	{
		ManufactureData_st * st = new ManufactureData_st();
		st->serverData = value->manufactureElement;
		BluePrintCfg* blueprint = BluePrintData.get(st->serverData.itemDataId);
		if(blueprint)
		{
			st->productTime = blueprint->time;
			int left =  st->serverData.remainSeconds;
			st->leftTime = left > 0? left:0;
			st->startTime = gGameManager->GetCurrTimeMS()/1000;
			st->baseGold = blueprint->gold;
			st->minGold = MAX(blueprint->gold/blueprint->time * 3600,1);
			int gold = (blueprint->gold/blueprint->time * 3600)*(st->leftTime/3600);
			st->curGold = MAX(gold, st->minGold);
			st->percent = (float)(st->productTime-left)/st->productTime *100;
			ItemCfg* blueitem = ItemData.get(st->serverData.itemDataId);
			if(blueitem)
			{
				st->icon = blueitem->icon;
				st->iconname = blueitem->name;
			}
			ItemCfg* targetitem = ItemData.get(blueprint->item_id);
			if(targetitem)
			{
				st->targetname = targetitem->name;
			}
		}
		m_vManuFactureList.push_back(st);
	}
}

void DataPool_cl::cancelManuFactureCD( pk::GS2C_Eliminate_Cd_Ret* value )
{
	if(value->errorCode != 0) return;
	for (auto iter :m_vManuFactureList)
	{
		if(iter->serverData.itemDataId == value->manufactureElement.itemDataId)
		{
			iter->startTime = gGameManager->GetCurrTimeMS()/1000;
			iter->serverData.eliminateCdFlag = value->manufactureElement.eliminateCdFlag;
			iter->serverData.itemDataId = value->manufactureElement.itemDataId;
			iter->serverData.isDone = value->manufactureElement.isDone;
			iter->serverData.remainSeconds = value->manufactureElement.remainSeconds;
			iter->productTime = fasttime;
			int left =  iter->serverData.remainSeconds;
			iter->leftTime = left > 0? left:0;
			iter->percent = (float)(iter->productTime-left)/iter->productTime *100;
			break;
		}
	}
}

void DataPool_cl::removeManuFactureData(int dataid )
{
	for(auto iter = m_vManuFactureList.begin(); iter != m_vManuFactureList.end(); iter++)
	{
		if((*iter)->serverData.itemDataId == dataid)
		{
			delete (*iter);
			iter = m_vManuFactureList.erase(iter);
			break;
		}
	}
}

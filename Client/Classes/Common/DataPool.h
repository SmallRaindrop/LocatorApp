/*
 * 模块：管理界面静态数据
 * 作者：TangBo
 * 时间：2015/8/11
 */

#pragma once

#include <vector>
#include "../Net/pk_friend.h"
#include "../Net/pk_item.h"
#include "Singleton.h"
#include "GameScene/Hero.h"
#include "UIData/CMatchMachine.h"
#include "Net/pk_map.h"
#include "UIData/CCopyDataMgr.h"
#include "UIData/Legion.h"
#include "UIData/ChatData.h"

using namespace std;


struct RecentlyPlayerData_st
{
	RecentlyPlayerData_st()
	{
		playerid = 0;
		name = "";
		level = 0;
	}
	int64       playerid;      //玩家id
	string      name;          //玩家名字
	int         level;         //玩家等级
};

static  int  fasttime = 30;    //制造使用加速后最大时间

struct ManufactureData_st
{
	ManufactureData_st(){
		leftTime = 0;
		startTime = 0;
		productTime = 0;
		baseGold = 0;
		minGold = 0;
		curGold = 0;
		icon = "";
		iconname = "";
		targetname = "";
		percent = 0;
	}
	pk::Manufacture_Element   serverData;
	int   leftTime;           //剩下时间(秒)
	long  startTime;          //本地开始时间（秒）
	int   productTime;        //生产时间(秒)
	int   baseGold;           //基础加速砖石
	int   minGold;            //最小加速砖石
	int   curGold;            //当前加速砖石
	int   percent;            //进度条的值
	string  icon;             //图纸icon
	string  iconname;         //图纸名字
	string  targetname;       //目标名字
};


typedef  map<int64, RecentlyPlayerData_st*>  RecentPlayerData_m;
typedef  vector<pk::Friend_Info>     FriendInfo_v;
typedef  vector<pk::Mail_Info>		 MailInfo_v;
typedef  vector<ManufactureData_st*> ManufactureData_v;

class DataPool_cl : public Singleton_Auto<DataPool_cl>
{
public:
	DataPool_cl();
	~DataPool_cl();

	/*************************************************************************
					            公共接口
	*************************************************************************/
	/*
	 * Name  :destoryData
	 * Des   :清理数据
	 * Author:Tangbo
	 */
	void                     destoryData();

	//初始化数据
	void                     initData();

	//更新数据,每帧调用
	void					Update(float dt);


	/*************************************************************************
					            好友系统接口
	*************************************************************************/

	//在指定容器中是否存在此玩家 Tangbo
	bool                    isExistPlayer(FriendInfo_v &_Tlist, int64 _id);

	//根据ptr更改容器的数据
	void                    setPListDataByPtr(FriendInfo_v &_Tlist, pk::Friend_Info* _Ptr);


	//根据ptr删除容器的数据 Tangbo
	void                    deletePListDataByPtr(FriendInfo_v &_Tlist, pk::Friend_Info* _Ptr);

	//根据ID删除容器的数据  Tangbo
	void                    deletePListDataByID(FriendInfo_v& _Tlist, int64 _id);

	//向最近列表中添加玩家
	void                    addPlayerToRecentList(pk::Friend_Info* _ptr);

	//获取容器中指定玩家信息  Tangbo
	pk::Friend_Info*        getFriendPlayerInfo( int64 _id);

	//获取容器中指定玩家信息  Tangbo
	pk::Friend_Info*        getRelativePlayerInfo( int64 _id);

	//区分好友和黑名单数据  Tangbo
	void                    sapratePDataList(FriendInfo_v& _list);

	//得到好友列表  Tangbo
	FriendInfo_v &getFriendList() { return m_friendlist;}


	//得到黑名单列表 Tangbo
	FriendInfo_v &getBlackList() { return m_blacklist;}


	 //得到最近列表 Tangbo
	FriendInfo_v &getRelativeList() { return m_relativelist;}

	RecentPlayerData_m & getRelativeMapData(){return m_relativeDate;};


	 //设置最近列表数据      Tangbo
	void                     setRelativeList(FriendInfo_v& _Tlist);


	//获取本地最近列表数据   Tangbo
	void                     initRelativeData();

	//保存最近列表到本地数据 Tangbo
	void                     saveRelativeDate();

	//根据时序、在线排序  Tangbo
	void                     sortPlayerByOnline(FriendInfo_v &_Tlist);




	/*************************************************************************
					            邮件系统接口
	*************************************************************************/
	//从服务器获取邮件列表	 ashin
	void					 setMailList(MailInfo_v& _list);

	//得到邮件列表			 ashin
	MailInfo_v&				 getMailList() { return m_maillist;}
	
	//通过ID得到邮件		 ashin
	pk::Mail_Info*			 getMailByID(int64 _id);

	//通过ID删除邮件		 ashin
	void					 deleteMailByID(int64 _id);
	
	//通过ID更新邮件状态     ashin
	void					 setMailStateByID(int64 _id,int _state);

	//新增一封邮件
	void					 addMailToList(pk::Mail_Info _mail);

	/*************************************************************************
					            副本匹配
	*************************************************************************/

	//匹配是否启动---彭龙华
	CMatchMachine*			GetMatchMachine() { return &m_matchMachine; }

	/*************************************************************************
					            副本数据管理器
	*************************************************************************/
	CCopyDataMgr*			GetCopyDataMgr() { return &m_copyDataMgr; }
	
	/*************************************************************************
					            天书系统接口
	*************************************************************************/
	enum SignBook
	{
		SignBook_InlayedBook,
		SignBook_RelicBook,
		SignBook_WeaponBook,
		SignBook_PetBook,
		SignBook_MaterialBook,
		SingBook_All,
		SignBook_Max,
	};

	//天书弹出背包显示条件
	struct ShowConditions_st
	{
		ShowConditions_st(){
			_type  = SignBook_Max;
			IsSubType = false;
			IsShowUp = false;
			IsCurUse = false;
			IsCurInlay = false;
			IsOtherInlay = false;
			exp = false;
		}

		SignBook _type;        //当前要显示的类型
		// 以下false表示不判断要显示 默认都要显示  true不显示要判断 
		bool IsSubType;        //是否判断子类型
		bool IsShowUp;         //是否显示已升级的
		bool IsCurUse;         //当前孔位是否使用
		bool IsCurInlay;       //当前是否镶嵌
		bool IsOtherInlay;     //其他是否镶嵌
		bool exp;              //是否exp是否大于0
	};

	//判断当前天书是否当前类型
	bool judgeType(CItem* item, SignBook _type);
	
	//从天书背包分离出数据 
	CItemGridArray*          saparateDataFromBag(ShowConditions_st st);

	//获取角色当前装备的武器itemgrid指针
	CItem*                   getHeroWeapon();

	//获取当前装备神器的镶嵌天书列表
	const vector<pk::EquipTianshu>& getCurRelicConfig();

	//获取当前装备武器的镶嵌天书列表
	const vector<pk::EquipTianshu>& getCurWeaponConfig();

	//获取当前装备宠物的镶嵌天书列表
	const vector<pk::EquipTianshu>& getCurPetConfig();

	/*************************************************************************
					            制造系统数据
	*************************************************************************/

	//初始化制造系统数据
	void  initManuFactureList(pk::GS2C_ManufactureList_Ret* value);

	//增加一条制造数据
	void  addManuFactureData(pk::GS2C_New_Manufacture_Element_Ret* value);

	//消除cd时间制造数据
	void  cancelManuFactureCD(pk::GS2C_Eliminate_Cd_Ret* value);

	//删除一条制造数据
	void  removeManuFactureData(int dataid);

	//获取生产线数据列表
	inline ManufactureData_v& getManufactureData(){return m_vManuFactureList;}


	/*************************************************************************
					            军团系统数据
	*************************************************************************/

	Legion_cl* getLegionData(){return m_pLegionData;}

	/*************************************************************************
					            聊天数据管理器
	*************************************************************************/

	CChatDataMgr* GetChatDataMgr(){return &m_chatDataMgr;}  

private:

	FriendInfo_v            m_friendlist;                         //好友列表

	FriendInfo_v            m_blacklist;                          //黑名单列表

	FriendInfo_v            m_relativelist;                       //最近列表

	RecentPlayerData_m      m_relativeDate;                       //最近列表数据

	MailInfo_v              m_maillist;                           //邮件列表

	CMatchMachine			m_matchMachine;						  //匹配状态机

	CCopyDataMgr			m_copyDataMgr;						  //副本数据管理器

	CItemGridArray*         m_pSignBook[SignBook_Max];            //天书分页标签

	ManufactureData_v       m_vManuFactureList;                   //正在制造的数据

	Legion_cl*              m_pLegionData;                        //军团数据

	CChatDataMgr			m_chatDataMgr;						  //聊天数据管理器
};

#define  gDataPool          DataPool_cl::Instance()

#define  gMacthMachine		gDataPool->GetMatchMachine()			//匹配数据
#define  gCopyDataMgr		gDataPool->GetCopyDataMgr()				//副本数据	
#define  gChatDataMgr		gDataPool->GetChatDataMgr()				//聊天数据		
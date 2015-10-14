/***
 * 模块：服务器界面
 * 作者：sndy
 * 时间：2015-07-22
 * 说明：选择登录服务器
 */

#pragma once
#include "GameDef.h"
#include "GameUI.h"
#include "Net/pk_betweenClientLs.h"
#include "CustomCtrl/RadioButtonSet.h"

#define		Region_Server_Size		(12)
#define     AreaServer_Size          8

//服务器当前的状态类型
enum ServerAreaType
{
	Recommendation_Type = 0,         //推荐
	Hot_Type            = 1,         //火爆
	Full_Type           = 10,        //爆满
	Defend_Type         = 100,       //维护
	Close_Type          = 1000,      //关闭
	Test_Type           = 10000,     //测试
	NewArea_Type,                    //新服
};

typedef vector<pk::GameServerInfo> ServerInfoList;
typedef map<int, ServerInfoList>   ServerInfoMap;

class CServerList : public GameUI
{
public:


	CServerList();
	~CServerList();

	/******************************************************************/
	void			clickEnterServer(Ref* pSender, TouchEventType type);
	void			clickBack(Ref* pSender, TouchEventType type);
	void			clickRegionItem(int nIndex);
	void			ShowRecommond();
	void			clickServerItem(Ref*, TouchEventType);
	/******************************************************************/

	bool			onInit();
	void			onClose();
	void			onOpen();
	void			Show(int regionCnt,vector<pk::GameServerInfo>& gameServers);
	void            onEnter();
	void            onExit();



	/**
	 * Name : setCurAreaSelectServ
	 * Des  : 设置当前区域选择的服务器
	 * Param: _status    状态类型 
	 *        _serverid  服务器号
	 *        _name      服务器名
	 */
	void            setCurAreaSelectServ(ServerAreaType _status, int _serverid, const char * _name);

	/**
	 * Name : setStatus
	 * Des  : 设置服务器的状态图
	 * Param: _status    状态类型
	 *        _type      0 是图片 1是文本
	 *        pPtr       对象指针
	 */
	template  <typename T>
	void            setStatus(ServerAreaType _status, const T& pPtr,int _type = 0);

   /**
	 * Name : setCurAreaSelectServ
	 * Des  : 设置服务器的显示
	 * Param: _status    状态类型 
	 *        _serverid  服务器号
	 *        _name      服务器名
	 *        _idx       当前区域的序号
	 */
	void            setServerShow(ServerAreaType _status, int _serverid, const char * _name, int _idx);


	/**
	 * Name : changAreaBtnStatusByIdx
	 * Des  : 根据下标更改区域按钮的状态颜色
	 * Param: _idx 区域按钮id
	 */
	void            changAreaBtnStatusByIdx(int _idx);


	/**
	 * Name : setAreaListBtn
	 * Des  : 设置当前区域显示,并添加触摸事件
	 * Param: _cnt区域个数
	 */
	void            setAreaListBtn(int _cnt);

	/**
	 * Name : setCurAreaShow
	 * Des  : 设置当前选择的区的服务器列表
	 * Param: _areaid
	 */
	void           setCurAreaShow(int _areaid);


	/**
	 * Name : showAreaServerList
	 * Des  : 显示当前选择的区域服务器列表
	 * Param: _id 区域id  
	 */
	void      showAreaServerList(int _id);


	/**
	 * Name : setDefaultShow
	 * Des  : 设置默认显示
	 */
	void      setDefaultShow();

	/**
	 * Name : getLastServerList
	 * Des  : 获取最近登录服务器列表
	 */
	std::vector<int> getLastServerList();


	/**
	 * Name : saveLastServerList
	 * Des  : 保存最近登录的服务器
	 */
	void           saveLastServerLsit();

	/**
	 * Name : findServerById
	 * Des  : 按服务器的id查找服务器信息
	 * Param: _id  服务器id
	 * Ret  : pk::GameServerInfo 服务器信息
	 *        如果不存在id为-1
	 */
	pk::GameServerInfo findServerById(int _id);


	/**
	 * Name : findServerByName
	 * Des  : 按服务器的Name查找服务器信息
	 * Param: _name  服务器name
	 * Ret  : pk::GameServerInfo 服务器信息
	 *        如果不存在id为-1
	 */
	pk::GameServerInfo findServerByName(const char* _name);


	/**
	 * Name : findServerByAreaName
	 * Des  : 按区域的Name查找服务器信息
	 * Param: _name  区域name
	 * Ret  : 区域服务器列表信息
	 */
	ServerInfoList findServerByAreaName(const char* _name);

	/**
	 * Name : callBackFunc
	 * Des  : 界面的按钮回调
	 */
	void            callBackFunc(Ref* pSender, TouchEventType type);

	/**
	 * Name : areaCallBack
	 * Des  : 区域按钮回调
	 */
	void            areaCallBack(Ref* pSender, TouchEventType type);

	/**
	 * Name : areaCallBack
	 * Des  : 服务器按钮回调
	 */
	void            serverCallBack(Ref* pSender, TouchEventType type);

	CREATE_FUNC(CServerList);

private:
	//sndy param
	Widget*             m_panelServer;                             //服务器选择层容器
	Button*             m_areaServerBtn[AreaServer_Size];          //区域服务器选择按钮
	Text*               m_text[3];                                 //当前选择的区域服务器的文本
	ImageView*          m_serverStatus;                            //当前选择的区域服务器的状态标志指针
	ListView*           m_serverList;                              //开设的服务器容器指针
	std::vector<int>    m_lastServerList;                          //最近登录的服务器列表
	ServerInfoList      m_gameServers;                             //服务器列表
	ServerInfoMap       m_gameAreaServers;                         //区域服务器列表
	int                 m_curAreaIndex;                            //当前选择的区域id
	pk::GameServerInfo  m_curServerInfo;                           //当前选择的服务器
};
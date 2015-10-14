/***
 * 模块：加载界面
 * 作者：sndy
 * 时间：2015-07-21
 * 说明：加载和更新界面
 */
#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Singleton.h"


//加载界面的显示类型
enum LoadType
{
	UPDATE_TYPE,
	LOADRES_TYPE,

};

class LoadingUI : public cocos2d::Layer,public Singleton<LoadingUI>
{
public:
	typedef void (Ref::*LoadEnd_Event)();
public:
	LoadingUI();
	~LoadingUI();

	/**
	 * Name : initWidget
	 * Des  : 初始化界面对象指针
	 * Param:
	 */
	void initWidget();

	/**
	 * Name : setPercent
	 * Des  : 设置进度条到指定位置
	 * Param: _percent 当前进度的最大值
	 *        _fd      单帧步长
	 */
	inline void SetPercent(float _percent, float _fd = 4.f){ m_fPercent = _percent; m_fd = _fd; }

	/**
	 * Name : IsActive
	 * Des  : 加载界面是否在显示
	 * Param: none
	 * Ret  : 显示 true, 关闭 false
	 */
	inline bool IsActive(){ return m_bActive; }

	/**
	 * Name : Show
	 * Des  : 显示加载界面
	 * Parma: _type 当前要显示的加载界面类型
	 *        _idu  是要加载的界面IDU
	 */
	//void Show(LoadType _type, int _idu, ...);

		/**
	 * Name : Show
	 * Des  : 显示加载界面
	 * Parma: _type 当前要显示的加载界面类型
	 */
	void Show(LoadType _type);

	/**
	 * Name : update
	 * Des  : 更新加载进度
	 * Parma: fd 时间间隔
	 */
	void update(float dt);

	/**
	 * Name : Close
	 * Des  : 关闭加载界面
	 * Param:
	 */
	void Close();

	//设置加载后回调
	void	addLoadEndEvent(Ref* pListener, LoadEnd_Event loadEnd_event);
	void	ClearLoadEndEvent();
	void	LoadEndEvent();

private:
	bool						m_bActive;        //加载界面状态值,默认值是false, 显示状态是true
	cocos2d::ui::Widget*		m_pWidget;		  //界面指针
	float						m_fCursor;        //当前的进度值游标，游标会毎帧运行单帧步长
	float						m_fPercent;		  //当前的进度值，区间为0-100
	float						m_fd;             //运行单帧步长
	
	std::string					m_showtips;       //显现提示字符
	cocos2d::ui::Text*			m_lable;          //进度显示标签
	cocos2d::ui::Text*			m_tipslable;      //进度提示标签
	cocos2d::ui::LoadingBar*	m_loadingbar;     //进度条指针
	cocos2d::ui::ImageView*		m_light;          //进度高亮效果

	
	//std::vector<int>			m_iduV;           //需加载的界面IDU
	Ref*						_loadEndEventListener;
	LoadEnd_Event				_loadEndEventCallBack;
};


#define gLoadingUI LoadingUI::Instance()
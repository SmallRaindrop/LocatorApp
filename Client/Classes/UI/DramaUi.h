/* 剧情显示模块
   Data: 2015/7/20
   Author：Tangbo
*/

#pragma once
#include "cocos2d.h"
#include "GameUI.h"
#include "GameScene/GameUILayer.h"
#include "LoadingUI.h"

#define  UPDATETIME    0.1f
#define  DELAYTIME     5.f
#define  MAX_STRING		30
#define  MAX_WORDS_0	200
#define  MAX_WORDS_1	100

class DramaUI:public GameUI
{
public:

	static void		PlayDrama(int nDramaId)
	{
		if(!nDramaId) return;
		DramaUI* pDramaUI = (DramaUI*)gGameUILayer->getUI(IDU_Drama);
		if(!pDramaUI) return;
		pDramaUI->SetStartId(nDramaId);
		if (gLoadingUI->IsActive())
		{
			gLoadingUI->addLoadEndEvent(pDramaUI,LoadingUI::LoadEnd_Event(&DramaUI::showDrama));
		}
		else
		{
			pDramaUI->showDrama();
		}
	}

public:
	bool onInit();
	void onOpen();
	void onShow();
	void onClose();
	void onDestroy();

	//初始化不可穿透模式
	void  initModel();

	//初始化可穿透模式
	void  initUnmodel();

	inline int				GetStartId() { return m_dataID; }
	inline void				SetStartId(int startId) { m_dataID = startId; }

	/* Name  : showDramaByParam
	   Des   : 通过指定参数显示剧情对话
	   Parma : _startid 剧情数据起始id, _npcid 要对话的npcid
	   ret   : none
	*/
	void   showDramaByParam(int _startid, int _npcid);
	void   showDrama();

	/* Name  : touchevent
	   Des   : 设置当前层的触摸响应事件
	   Parma : 
	   ret   : 
	*/
	void    touchevent(Ref *pSender, TouchEventType _type);

	/* Name  : touchevent
	   Des   : 设置当前层的触摸响应事件
	   Parma : 
	   ret   : 
	*/
	void    passevent(Ref *pSender, TouchEventType _type);

	/* Name  : getCurShowContext()
	   Des   : 获取当前的显示内容,更替头像显示,文本显示
	   Param : none
	   ret   : 返回当前对话的内容
	*/
	string  getCurShowContext();

	/* Name  : getSubShowString()
	   Des   : 获取当前帧逐步显示的内容
	   Param : _index 当前逐步显示的位置
	   ret   : 返回逐显内容
	*/
	string  getSubShowString(int _index);

	/* Name  : showByInstant
	   Des   : 瞬间显示对话
	   Param : 
	   ret   :
	*/
	void    showByInstant();

	/* Name  : showByInterval
	   Des   : 逐步显示对话
	   Param : 
	   ret   :
	*/
	void    showByInterval();



	/* Name  : showCenterTips()
	   Des   : 显示中心提示字符
	   Param : 
	   ret   :
	*/
	void    showCenterTips();


	/* Name  : subDataByMainType
	 * Des   : 从Drama表数据中分离出,当前main的数据
	 * Param : main  
	 * ret   : 返回剧情对话内容
	 */
	vector<DramaCfg*> subDataByMainType(int main);

	/* Name  : subStringToVector(string _str)
	   Des   : 将要显示的字符按字截取到显示容器
	   Param : _str 当前对话要显示的字符
	   ret   :
	*/
	void    subStringToVector();

	/* Name  : nextTalk
	   Des   : 显示下一句
	   Parma : none
	   Ret   : none
	 */
	void    nextTalk(int _delay = DELAYTIME);


	/* Name  : update(float fd)
	   Des   : 更新逐步显示的字体
	   Param : fd 显示的间隔时间
	   ret   :
	*/
	void    updateShow(float fd);

	DramaUI();
	~DramaUI();

     //当前显示模式 false全屏显示(默认显示)  true 小屏显示可穿透
	CC_SYNTHESIZE_READONLY(bool, m_curShowMode, curShowMode);

private:
	struct TalkLine_st
	{
		TalkLine_st(){
			direct = 0;
			roleid = 0;
			person = 0;
			talkstr.clear();
		}

		int  direct;        //显示方向
		int  roleid;        //当句对话的角色id 0当前玩家(默认) 
		int  person;        //角色类型  0 npc 1玩家
		vector<std::string> talkstr;//当前说话的内容
	};
	typedef vector<TalkLine_st*>  VecStr;

	Text*                    m_pNpcName;          //npc名字

	Text*                    m_pHeroName;         //hero名字

	cocos2d::ui::Text      * m_pShowTextNpc;         //npc对话标签

	cocos2d::ui::Text      * m_pShowTextHero;         //hero对话标签

	cocos2d::ui::ImageView * m_npcIcon;           //npc图像

	cocos2d::ui::ImageView * m_heroIcon;          //英雄图像

	string                   m_showStr;           //说话内容


	int                      m_stcLen;            //话长度

	int                      m_dataID;            //显示数据id

	int                      m_touchCnt;          //触摸次数

	int                      m_curIndex;          //句显示下标

	int                      m_subIndex;          //逐显下标
	
	VecStr                   m_dump[MAX_STRING];          //最多30句

	bool                     m_isSkip;            //是否跳过
};




#pragma once
#include "GameDef.h"
#include "GameUI.h"
#include "Net/pk_nonInGame.h"
#include "CustomCtrl/ScrollTable.h"
#include "CustomCtrl/TuoYuanAction.h"
#include "RoleModel.h"
#include "CustomCtrl/RichTextEX.h"

#define Max_Player_Num			(3)

class CSelectPlayer : public GameUI
{
public:
	CSelectPlayer();
	~CSelectPlayer();

	bool			onInit();
	void			onClose();
	void			onOpen();
	void			Show(vector<pk::UserPlayerData>& player_list);

	void			deletePlayer(bool bDel);

	/**
	 * Name : selectPlayer
	 * Des  : 选择和创建英雄
	 * Param: tag 英雄按钮下标
	 */

	void			selectPlayer(int tag);

	/**
	 * Name : setHeroImage
	 * Des  : 设置角色按钮和角色的显示图片
	 * Param: _type 英雄数据
	 *        pPtr  对象指针
	 *        ptrType 0 为按钮 1为图片
	 */
	template <typename T>
	void            setHeroImage(pk::UserPlayerData _type, const T& pPtr, int ptrType = 0);


	/**
	 * Name ：isExitHero
	 * Des  : 检测是否有英雄
	 * Param: _idx 按钮的下标值
	 * Ret  : 有true 
	 */
	bool            isExitHero(int _idx);

	/**
	 * Name : showFace
	 * Des  : 选择按钮后,改变界面的显示
	 * Param: _idx 按钮的下标值
	 */
	void            showFace(int _idx);

	/**
	 * Name : clickCallBack
	 * Des  : 按钮时间回调
	 */
	void            clickCallBack(Ref* pSender, TouchEventType type);

	CREATE_FUNC(CSelectPlayer);

private:
	vector<pk::UserPlayerData>		m_players;
	lrTuoyuanConfig					m_tuoyuancfg;

	RoleModel*			m_roleModels[Max_Player_Num];
	Widget*				m_playerContainer[Max_Player_Num];
	RichTextEx*			m_playerName[Max_Player_Num];

	Button*             m_pButton[5];                         //界面按钮
	int                 m_curIndex;                           //当前选择的按钮下标
	float               m_pos;                                //英雄按钮默认位置
};
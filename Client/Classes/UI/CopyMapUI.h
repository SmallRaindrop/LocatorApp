/* 
	副本UI
	彭龙华
	2015-09-02
*/
#pragma once
#include "cocos2d.h"
#include "GameUI.h"
#include "Net/pk_map.h"

class CCopyMapUI:public GameUI
{
public:
	CCopyMapUI(int idu,const std::string& strJsonFile);
	~CCopyMapUI();

	virtual void			onClose();

	//副本初始化
	virtual void			UpdateCopyInitInfo(pk::GS2C_CopyInitInfo* value);
	//副本步骤进度
	virtual void			UpdateCopyProgress(pk::GS2C_UpdateCopyProgress* value);
	//副本小节，波数，轮数，是否激活
	virtual void			updateMonsterWave(pk::GS2C_MonsterSpawnRemind* value);
	//离开倒计时
	virtual void			UpdateCountTime(pk::GS2C_COPY_SUCC_TIME* value);

	//激活前回调
	virtual void			BeforeActive() {};
	//激活后回调
	virtual void			OnActive() {};

	//副本目标数
	virtual void			SetGoalNum(int nGoalNum);
	//当前目标数
	virtual void			SetCurNum(int nCurNum);
	//当前小节数
	virtual void			SetWaveIdx(int nWaveIdx);

	//启动倒计时
	virtual void			StartCountSeconds(int nSeconds);
	//结束倒计时
	virtual void			EndCountSeconds();
	//倒计时刷新
	virtual void			ScheduleCountSeconds(float dt);

	inline Copy_stepCfg*	GetStepDataCfg() { return m_pStepDataCfg; }
	inline MapCfg*			GetMapDataCfg() { return m_pMapDataCfg; }
public:
	static	void			OpenCopyMapUI();
	static	void			CloseCopyMapUI();

private:
	void					CheckIfShowIndicator();

protected:
	Copy_stepCfg*		m_pStepDataCfg;
	MapCfg*				m_pMapDataCfg;

	Text*				m_pGoalTitle;
	Text*				m_pCurTitle;
	Text*				m_pCountSecondsTitle;

	Text*				m_pWaveIdx;
	Text*				m_pGoalNum;
	Text*				m_pCurNum;
	Text*				m_pCountSeconds;

	int					m_nWaveIdx;
	int					m_nGoalNum;
	int					m_nCurNum;
	int					m_nCountSeconds;

	bool				m_bActive;
};
/***
 * 作者：岳良友
 * 时间：2015-07-2
 * 说明：游戏管理器，管理进入游戏初始化和退出游戏销毁。
 */

#ifndef __GameManager_h_
#define __GameManager_h_

#include "GameDef.h"
#include "Singleton.h"

enum GameState
{
	GS_None = 0,
	GS_Update,
	GS_Login,
	GS_Game,
};

struct MachineInfo
{
	MachineInfo(){
		_vendor = "Unknown";
		_num = "Unknown";
		_os = "Unknown";
		_cpu_vendor = "Unknown";
		_cpu_name = "Unknown";
		_cpu_abi = "Unknown";
	}
	MachineInfo(const MachineInfo& info){
		_vendor = info._vendor;
		_num = info._num;
		_os = info._os;
		_cpu_vendor = info._cpu_vendor;
		_cpu_name = info._cpu_name;
		_cpu_abi = info._cpu_abi;
	}
	MachineInfo(const string& vendor,const string& num,const string& os,const string& cpu_vendor,const string& cpu_name,const string& cpu_abi){
		_vendor = vendor;
		_num = num;
		_os = os;
		_cpu_vendor = cpu_vendor;
		_cpu_name = cpu_name;
		_cpu_abi = cpu_abi;
	}
	string _vendor;		// 手机厂商
	string _num;		// 手机型号
	string _os;			// 手机操作系统版本
	string _cpu_vendor;	// 手机CPU厂商
	string _cpu_name;	// 手机CPU商标
	string _cpu_abi;	// ABI
};

class GameManager : public Singleton_Auto<GameManager>
{
public:
	GameManager();
	~GameManager();

	/* Name		：Start
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 游戏启动设置
	 * Param	: none
	 * Return	: void
	 */
	void Start();

	/* Name		：Exit
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 游戏退出销毁
	 * Param	: none
	 * Return	: void
	 */
	void Exit();

	/* Name		：Preload
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 游戏预加载，打开游戏的初始化
	 * Param	: none
	 * Return	: true 成功，false 失败
	 */
	bool Preload();

	/* Name		：EnterGame
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 从登录界面到进入游戏界面的初始化
	 * Param	: none
	 * Return	: void
	 */
	void EnterGame();

	/* Name		：LeaveGame
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 退出游戏到登录界面调用该接口
	 * Param	: none
	 * Return	: void
	 */
	void LeaveGame();

	/* Name		：EnterLogin
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 进入登录界面调用接口
	 * Param	: none
	 * Return	: void
	 */
	void EnterLogin();

	/* Name		：EnterLogin
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 离开登录界面调用接口
	 * Param	: none
	 * Return	: void
	 */
	void LeaveLogin();

	/* Name		：EnterUpdate
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 进入更新界面调用接口
	 * Param	: none
	 * Return	: void
	 */
	void EnterUpdate();

	/* Name		：LeaveUpdate
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 离开更新界面调用接口
	 * Param	: none
	 * Return	: void
	 */
	void LeaveUpdate();

	void EnterState(GameState gs);
	void LeaveState();

	long GetCurrTimeMS();
	long long GetCurrTimeMicroS();

public:
	/* Name		：GetResourceRoot
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取资源根目录
	 * Param	: none
	 * Return	: string 资源目录
	 */
	inline string& GetResourceRoot(){ return m_sResourceRoot; }
	inline string GetRvdFile(){ return GetResourceRoot()+"data.rvd"; }
	inline string GetMpqFile(){ return GetResourceRoot()+"data.mpq"; }
	inline string GetMpqBakFile(){ return GetResourceRoot()+"data.bak"; }
	inline string GetLogPath(){ return GetResourceRoot()+"log"; }

	/* Name		：SetResourceRoot
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 设置资源根目录
	 * Param	: none
	 * Return	: string 资源目录
	 */
	inline void SetResourceRoot(const string& path){ m_sResourceRoot = path; }
	
	/* Name		：CreateDirectory
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 创建目录
	 * Param	: none
	 * Return	: string 目录路劲
	 */
	bool CreateDirectory(const string& path);

	/* Name		：RemoveDirectory
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 删除目录
	 * Param	: none
	 * Return	: string 目录路劲
	 */
	void RemoveDirectory(const string& path);

	/* Name		：LogMachineInfo
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 将机器信息写入日志
	 * Param	: none
	 * Return	: void
	 */
	void LogMachineInfo();

public:
	inline int		GetServerID(){ return m_ServerID; }
	inline __int64	GetServerTime(){ return m_ServerTime; }
	inline string	GetAccount(){ return m_Account; }
	inline AccountID GetAccountID(){ return m_AccountID; }
	inline PlayerID	GetPlayerID(){ return m_PlayerID; }

	inline void SetServerID(int id){ m_ServerID = id; }
	inline void SetServerTime(__int64 time){ m_ServerID = time; }
	inline void SetAccount(const string& acc){ m_Account = acc; }
	inline void SetAccountID(AccountID id){ m_AccountID = id; }
	inline void SetPlayerID(PlayerID id){ m_PlayerID = id; }
	inline void SetSign(string& sign){ m_sign = sign; }
	inline string GetSign(){ return m_sign; }

	inline int	GetStateFlag(){ return m_StateFlag; }
	inline void SetStateFlag(int state){ m_StateFlag = state; }

	inline bool IsGaming(){ return GS_Game == GetStateFlag(); }

	inline void SetMachineInfo(MachineInfo& info){ m_MachineInfo = info; }
	inline void SetMachineInfo(const string& vendor,const string& num,const string& os,const string& cpu_vendor,const string& cpu_name,const string& cpu_abi){ m_MachineInfo = MachineInfo(vendor,num,os,cpu_vendor,cpu_name,cpu_abi); }
	inline void SetMachineVendor(const string& val){ m_MachineInfo._vendor = val; }
	inline void SetMachineNum(const string& val){ m_MachineInfo._num = val; }
	inline void SetMachineOSVersion(const string& val){ m_MachineInfo._os = val; }

	inline MachineInfo& GetMachineInfo(){ return m_MachineInfo; }
	inline string& GetMachineVendor(){ return m_MachineInfo._vendor; }
	inline string& GetMachineNum(){ return m_MachineInfo._num; }
	inline string& GetMachineOSVersion(){ return m_MachineInfo._os; }

private:
	int			m_ServerID;			// 服务器ID
	__int64		m_ServerTime;		// 服务器时间
	string		m_Account;			// 登录账号
	AccountID	m_AccountID;		// 账号ID
	PlayerID	m_PlayerID;			// 角色ID
	int			m_StateFlag;		//
	string		m_sign;

	string		m_sResourceRoot;			// 资源目录

	MachineInfo m_MachineInfo;
};

#define gGameManager	GameManager::Instance()

#endif
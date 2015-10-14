#ifndef __GameUpdate_h_
#define __GameUpdate_h_

#include "ProgressData.h"
#include "ZipUncompressAsync.h"
#include "mpq/MPQPatcher.h"
#include "FileDownloadAsync.h"
#include "Version.h"
#include "GameUpdateManager.h"
#include "StateMachine.h"

enum UpdateStateType
{
	UpdateStateType_None,
	UpdateStateType_Start,
	UpdateStateType_List,
	UpdateStateType_Check,
	UpdateStateType_APK,
	UpdateStateType_Res_Diff,
	UpdateStateType_Res_Ext,
	UpdateStateType_Patch_Diff,
	UpdateStateType_Patch_Ext,
	UpdateStateType_Succ,
	UpdateStateType_Fail,
};

class IUpdateState : public IState<UpdateManager>
{
public:
	IUpdateState(int id = UpdateStateType_None) : IState(id){}
	virtual ~IUpdateState(){}

	void OnEvent(UpdateManager* pTarget,IStateEvent* event){}
};

// 更新开始
class CUpdateStart : public IUpdateState
{
public:
	CUpdateStart() : IUpdateState(UpdateStateType_Start){};
	~CUpdateStart(){};
public:
	void OnEnter(UpdateManager* pTarget);

	void OnLeave(UpdateManager* pTarget);

	void OnTimer(UpdateManager* pTarget,float dt);

protected:
	ZipUncompressAsync	m_zipUncompressor;
};

// 获取更新列表
class CUpdateList : public IUpdateState
{
public:
	CUpdateList() : IUpdateState(UpdateStateType_List){};
	~CUpdateList(){};
public:
	void OnEnter(UpdateManager* pTarget);

	void OnLeave(UpdateManager* pTarget);

	void OnTimer(UpdateManager* pTarget,float dt);

protected:
	string m_UpdateDescData;
};

// 运行环境检查，获取版本文件，版本检查
class CUpdateCheck : public IUpdateState
{
public:
	CUpdateCheck(){};
	~CUpdateCheck(){};
public:
	void OnEnter(UpdateManager* pTarget);

	void OnLeave(UpdateManager* pTarget);

	void OnTimer(UpdateManager* pTarget,float dt);

protected:
	string m_svdData;
	string m_svdURL;
};

// 更新APK
class CUpdateApk : public IUpdateState
{
public:
	CUpdateApk(){};
	~CUpdateApk(){};
public:
	void OnEnter(UpdateManager* pTarget);

	void OnLeave(UpdateManager* pTarget);

	void OnTimer(UpdateManager* pTarget,float dt);

protected:
	FileDownloader		m_fileDownloader;
	string				m_fileLocal;
	string				m_fileLocalTmp;
	string				m_fileURL;
};

// 更新差异包
class CUpdateResDif : public IUpdateState
{
public:
	CUpdateResDif(){};
	~CUpdateResDif(){};
public:
	void OnEnter(UpdateManager* pTarget);

	void OnLeave(UpdateManager* pTarget);

	void OnTimer(UpdateManager* pTarget,float dt);

protected:
	FileDownloader		m_fileDownloader;
	VersionDef			m_verTarget;
	string				m_fileLocal;
	string				m_fileLocalTmp;
	string				m_fileURL;
};


class CUpdatePatchDif : public IUpdateState
{
public:
	CUpdatePatchDif(){};
	~CUpdatePatchDif(){};
public:
	void OnEnter(UpdateManager* pTarget);

	void OnLeave(UpdateManager* pTarget);

	void OnTimer(UpdateManager* pTarget,float dt);

protected:
	MPQPatcher			m_mpqPatcher;
	VersionDef			m_verTarget;
	string				m_fileDat;
	string				m_fileDif;
	string				m_fileBak;
};

// 更新扩展包
class CUpdateResExt : public IUpdateState
{
public:
	CUpdateResExt(){};
	~CUpdateResExt(){};
public:
	void OnEnter(UpdateManager* pTarget);

	void OnLeave(UpdateManager* pTarget);

	void OnTimer(UpdateManager* pTarget,float dt);

	bool isValidExtValue(int n);

protected:
	FileDownloader		m_fileDownloader;
	string				m_fileLocal;
	string				m_fileLocalTmp;
	string				m_fileURL;
};

class CUpdatePatchExt : public IUpdateState
{
public:
	CUpdatePatchExt(){};
	~CUpdatePatchExt(){};
public:
	void OnEnter(UpdateManager* pTarget);

	void OnLeave(UpdateManager* pTarget);

	void OnTimer(UpdateManager* pTarget,float dt);

protected:
	MPQPatcher			m_mpqPatcher;
	string				m_fileDat;
	string				m_fileExt;
	string				m_fileBak;
};

class CUpdateSucc : public IUpdateState
{
public:
	CUpdateSucc() : IUpdateState(UpdateStateType_Succ){};
	~CUpdateSucc(){};
public:
	void OnEnter(UpdateManager* pTarget);

	void OnLeave(UpdateManager* pTarget);

	void OnTimer(UpdateManager* pTarget,float dt);
};

class CUpdateFail : public IUpdateState
{
public:
	CUpdateFail(string info = "") : IUpdateState(UpdateStateType_Fail),m_sInfo(info){}
	~CUpdateFail(){}
public:
	void OnEnter(UpdateManager* pTarget);

	void OnLeave(UpdateManager* pTarget);

	void OnTimer(UpdateManager* pTarget,float dt);

protected:
	string	m_sInfo;
};

#endif
#ifndef __VersionManager_h_
#define __VersionManager_h_

#include "GameDef.h"
#include "Version.h"
#include "Singleton.h"

// 本地APK包中版本文件描述
typedef struct _local_version_desc_ 
{
	int				pid;				// APK包代表的平台号标识
	int				pro;				// 网络协议号
	VersionDef		ver;				// 本地版本号
	int				ext;				// 扩展资源包标识
	string			url;				// 更新文件列表文件URL
	string			ip;					// 登录服务器IP
	unsigned short	port;				// 登录服务器端口号
}LVD;


enum
{
	ResExtPack1 = 0,
	ResExtPackN,
};

#define ResExtPack(N)	1<<(N)

// .rvd资源版本文件描述
typedef struct _resource_version_desc_
{
	_resource_version_desc_() : ext(0){}
	VersionDef	ver;			// 资源版本号
	int			ext;			// 扩展资源包标识,按位标识

	inline bool hasExtension(int idx){
		return (ext & idx) != 0;
	}

	inline void setExtension(int idx){
		ext |= idx;
	}

	inline void clrExtension(int idx){
		ext &= ~idx;
	}
}RVD;

// 更新服务器上版本文件描述
typedef struct _server_version_desc_
{
	VersionDef		ver;			// 最新版本号
	string			ip;				// 登录服务器IP
	unsigned short	port;			// 登录服务器端口号
}SVD;

class VersionManager : public Singleton_Auto<VersionManager>
{
public:
	VersionManager();
	~VersionManager();

	bool initialize();
	void release();

public:
	bool	readLVDFromFile(const string& xml);
	bool	readLVDFromBuffer(const char* pBuffer,size_t size);

	bool	readSVDFromFile(const string& xml);
	bool	readSVDFromBuffer(const char* pBuffer,size_t size);

	bool	readRVD(const string& rvd);
	bool	saveRVD(const string& rvd);

	bool	readUpdateDescFromFile(const string file);
	bool	readUpdateDescFromBuffer(const char* pBuffer,size_t size);

	bool	isResExpired();
	bool	isApkExpired();
	bool	isDebugMode();
	bool	isApkNeedUpdate();
	bool	isResNeedUpdate();

	VersionDef*		get_target_version();
	string			key_to_url(string key);

	inline string	key_to_apk(){ 
		string ret = "tz_v";
		ret += m_svd.ver.to_str();
		return ret;
	}
	inline string	key_to_res_dif(VersionDef& ver){
		string ret = "tz_dif_v";
		ret += ver.to_str();
		ret += "_v";
		ret += m_rvd.ver.to_str();
		return ret;
	}
	inline string	key_to_res_ext(int n){
		string ret = "tz_ext_v";
		ret += m_rvd.ver.to_str();
		ret += "_1";
		return ret;
	}

	inline LVD&	lvd(){ return m_lvd; }
	inline RVD&	rvd(){ return m_rvd; }
	inline SVD&	svd(){ return m_svd; }
	inline SVD&	svd_d(){ return m_svd_d; }
	
protected:
	LVD		m_lvd;		// APK包中版本文件描述
	RVD		m_rvd;		// 资源版本文件描述
	SVD		m_svd;		// 服务器版本文件正式版本描述
	SVD		m_svd_d;	// 服务器版本文件测试版本描述
	int		m_debug;	// 测试版本标志

	typedef map<string,VersionDef>	VersionMapping;
	VersionMapping	m_mapping;	// 版本映射表
	typedef map<string,string>		UpdateList;
	UpdateList		m_list;		// 更新文件列表
};

#define gGameVersion VersionManager::Instance()

#endif
#include "GameUpdate.h"

#include "../CCFileUtils.h"

#include "CCPlatformConfig.h"

#include "VersionManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "curl/include/win32/curl/curl.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "curl/include/ios/curl/curl.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include "curl/include/android/curl/curl.h"
#include "jni/JniHelper.h"
#endif

#include "mpq/MPQPackage.h"
#include "StringConverter.h"
#include "GameScene/GameManager.h"
#include "GameScene/GameDataManager.h"

#define UpdateError(CODE,...)	{ \
	pTarget->SetPromptString(CODE,##__VA_ARGS__);\
	pTarget->EnterState(UpdateStateType_Fail);\
	return; }

#define URLConnectionTimeOut	3000

static size_t onUrlVersionData(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	string *versionData = (string*)userdata;
	versionData->append((char*)ptr, size * nmemb);

	return (size * nmemb);
}

//
// =====----------------==========
//
void CUpdateStart::OnEnter(UpdateManager* pTarget)
{
	LOGI("=============update start===========");
	// 检查资源包
	pTarget->SetPromptString("check mpq");
	pTarget->GetUpdateUI()->GetProgressBar()->Reset();
	pTarget->GetUpdateUI()->GetProgressBar()->SetText("check 89%");

	string resPath = gGameManager->GetResourceRoot();
	string resFile = gGameManager->GetMpqFile();
	string resFileBak = gGameManager->GetMpqBakFile();
	string rvdFile = gGameManager->GetRvdFile();

	// 检查 rvd 是否存在?
	if ( !gGameVersion->readRVD(rvdFile) )
	{
		// 创建资源目录
		if ( !resPath.empty() )
		{
			gGameManager->CreateDirectory(resPath);
		}

		// 包含data.mpq
		if ( gFileUtils->isFileExist("data.mpq") )
		{
			pTarget->SetPromptString("split package");
			LOGI("split package.res path is:%s",resPath.c_str());
			LOGI("split package.res file is:%s",resFile.c_str());
			// update rvd
			gGameVersion->rvd().ver = gGameVersion->lvd().ver;
			gGameVersion->rvd().ext = gGameVersion->lvd().ext;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			// 解压
			m_zipUncompressor.uncompress(getApkPath(),"assets/data.mpq",resPath.c_str());
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			// 拷贝
			m_zipUncompressor.copy(gFileUtils->fullPathForFilename("data.mpq").c_str(),resFile.c_str());
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			//m_zipUncompressor.copy(gFileUtils->fullPathForFilename("data.mpq").c_str(),resFile.c_str());
			// WIN32平台无需分离资源包，直接获取更新列表
			pTarget->EnterState(UpdateStateType_List);
			return ;
#endif
		}
		else
		{
			// 通过URL 获取

			// install invalid apk.
			UpdateError(100);
		}
	}
	else
	{
		// rvd exist,data.mpq exist ?
		if( !gFileUtils->isFileExist(resFile) )
		{
			// data.mpq is deleted.maybe download from server.
			UpdateError(101);
		}
		// data.bak exist ? may be has error in last time?
		if( gFileUtils->isFileExist(resFileBak) )
		{
			LOGE("data.bak exist.game encountered a fatal error!!!");
			MPQPackage* pResPack = new MPQPackage;
			if ( pResPack && pResPack->revert(resFile.c_str(),resFileBak.c_str()) )
			{
				LOGE("game has reverted from a fatal error!!!");
				CC_SAFE_DELETE(pResPack);
				UpdateError(101);
			}
			CC_SAFE_DELETE(pResPack);
		}

		// 安装了高版本的游戏包，原有资源失效。
		if ( gGameVersion->isResExpired() )
		{
			pTarget->SetPromptString("split package");
			LOGI("split package.res path is:%s",resPath.c_str());
			LOGI("split package.res file is:%s",resFile.c_str());
			// update rvd
			gGameVersion->rvd().ver = gGameVersion->lvd().ver;
			gGameVersion->rvd().ext = gGameVersion->lvd().ext;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			m_zipUncompressor.uncompress(getApkPath(),"assets/data.mpq",resPath.c_str());
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			m_zipUncompressor.copy(gFileUtils->fullPathForFilename("data.mpq").c_str(),resFile.c_str());
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			//m_zipUncompressor.copy(gFileUtils->fullPathForFilename("data.mpq").c_str(),resFile.c_str());
			// WIN32平台无需分离资源包，直接获取更新列表
			pTarget->EnterState(UpdateStateType_List);
			return ;
#endif
		}
		else
		{
			// 无需分离资源包的情况，直接获取更新列表
			pTarget->EnterState(UpdateStateType_List);
			return ;
		}
	}
}

void CUpdateStart::OnTimer(UpdateManager* pTarget,float dt)
{
	if ( m_zipUncompressor.isBusy() )
	{
		// 更新进度条
		pTarget->GetUpdateUI()->GetProgressBar()->SetPercent(m_zipUncompressor.getProgress());
		pTarget->SetPromptString(102,m_zipUncompressor.getProgress());
	}
	else
	{
		if ( !m_zipUncompressor.getInfo().empty() )
		{
			UpdateError(103,m_zipUncompressor.getInfo().c_str());
		}

		// 更新进度条
		pTarget->GetUpdateUI()->GetProgressBar()->SetPercent(100);

		// 判断进度条是否完成
		if ( pTarget->GetUpdateUI()->GetProgressBar()->IsComplete() )
		{
			// 获取更新列表
			pTarget->EnterState(UpdateStateType_List);
		}		
	}
}

void CUpdateStart::OnLeave(UpdateManager* pTarget)
{
	// do nothing ,maybe to update fail state.
}

//
// =====----------------==========
//
//
// =====-------get update file and init update desc data in version manager---------==========
//
void CUpdateList::OnEnter(UpdateManager* pTarget)
{
	// 更新版本文件
	gGameVersion->saveRVD(gGameManager->GetRvdFile());
	pTarget->SetPromptString(201);
	pTarget->GetUpdateUI()->GetProgressBar()->Reset();
	pTarget->GetUpdateUI()->GetProgressBar()->SetText("check 89%");
	// 
	pTarget->GetUpdateUI()->GetProgressBar()->SetPercent(100);
	m_UpdateDescData.clear();
}

void CUpdateList::OnTimer(UpdateManager* pTarget,float dt)
{
	if ( pTarget->GetUpdateUI()->GetProgressBar()->IsComplete() )
	{
		pTarget->EnterState(UpdateStateType_Succ);
		return ;
	}
	else
	{
		return ;
	}
	// get version file from url
	CURL *_curl = curl_easy_init();
	if (! _curl)
	{
		UpdateError(202);
	}

	CURLcode res;
	curl_easy_setopt(_curl, CURLOPT_URL,gGameVersion->lvd().url.c_str());
	curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION,onUrlVersionData);
	curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &m_UpdateDescData);
	curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, true);
	curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, URLConnectionTimeOut);
	res = curl_easy_perform(_curl);

	if (res != 0)
	{
		curl_easy_cleanup(_curl);
		UpdateError(203);
	}

	long retcode = 0;
	res = curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE , &retcode); 
	if ( (res != CURLE_OK) || retcode != 200 )
	{
		curl_easy_cleanup(_curl);
		UpdateError(204);
	}

	curl_easy_cleanup(_curl);

	if( !gGameVersion->readUpdateDescFromBuffer(m_UpdateDescData.c_str(),m_UpdateDescData.length()) )
	{
		UpdateError(205);
	}

	pTarget->EnterState(UpdateStateType_Check);
}

void CUpdateList::OnLeave(UpdateManager* pTarget)
{
	m_UpdateDescData.clear();
}

//
// =====----------------==========
//
void CUpdateCheck::OnEnter(UpdateManager* pTarget)
{
	pTarget->SetPromptString(301);

	m_svdData.clear();

	string urlKey = "svd_"+StringConverter::toString(gGameVersion->lvd().pid);
	m_svdURL = gGameVersion->key_to_url(urlKey);
	if ( m_svdURL.empty() )
	{
		pTarget->EnterState(UpdateStateType_Succ);
	}
}

void CUpdateCheck::OnTimer(UpdateManager* pTarget,float dt)
{
	CURL *_curl = curl_easy_init();
	if (! _curl)
	{
		UpdateError(302);
	}

	CURLcode res;
	curl_easy_setopt(_curl, CURLOPT_URL,m_svdURL.c_str());
	curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION,onUrlVersionData);
	curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &m_svdData);
	curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, true);
	curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT, URLConnectionTimeOut);
	res = curl_easy_perform(_curl);

	if (res != 0)
	{
		curl_easy_cleanup(_curl);
		UpdateError(303);
	}

	long retcode = 0;
	res = curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE , &retcode); 
	if ( (res != CURLE_OK) || retcode != 200 )
	{
		curl_easy_cleanup(_curl);
		UpdateError(304);
	}

	curl_easy_cleanup(_curl);

	if( !gGameVersion->readSVDFromBuffer(m_svdData.c_str(),m_svdData.length()) )
	{
		UpdateError(305);
	}

	// debug mode?
	if ( gGameVersion->isDebugMode() )
	{
		gGameVersion->lvd().ip = gGameVersion->svd_d().ip;
		gGameVersion->lvd().port = gGameVersion->svd_d().port;
		pTarget->EnterState(UpdateStateType_Res_Ext);
	}
	else
	{
		gGameVersion->lvd().ip = gGameVersion->svd().ip;
		gGameVersion->lvd().port = gGameVersion->svd().port;

		if ( gGameVersion->isApkExpired() )
		{
			UpdateError(306);
		}
		// apk need update?
		if ( gGameVersion->isApkNeedUpdate() )
		{
			pTarget->EnterState(UpdateStateType_APK);
			return ;
		}
		// res need update?
		if ( gGameVersion->isResNeedUpdate() )
		{
			pTarget->EnterState(UpdateStateType_Res_Diff);
			return ;
		}

		pTarget->EnterState(UpdateStateType_Succ);
	}
}

void CUpdateCheck::OnLeave(UpdateManager* pTarget)
{
	m_svdData.clear();
	// remove update apk file
	string path = gGameManager->GetResourceRoot();
	string file = path + gGameVersion->key_to_apk() + ".apk";
	remove(file.c_str());
}

//
// =====----------------==========
//
void CUpdateApk::OnEnter(UpdateManager* pTarget)
{
	pTarget->SetPromptString(401);

	string path = gGameManager->GetResourceRoot();
	string key = gGameVersion->key_to_apk();
	m_fileLocal = path + key + ".apk";
	m_fileLocalTmp = m_fileLocal + ".tmp";
	m_fileURL = gGameVersion->key_to_url(key);
	if ( m_fileURL.empty() )
	{
		UpdateError(402);
	}

	if ( !m_fileDownloader.download(m_fileURL.c_str(),m_fileLocalTmp.c_str()) )
	{
		UpdateError(403);
	}
}

void CUpdateApk::OnTimer(UpdateManager* pTarget,float dt)
{
	if ( m_fileDownloader.isBusy() )
	{
		pTarget->SetPromptString(404);
	}
	else
	{
		if ( !m_fileDownloader.getInfo().empty() )
		{
			UpdateError(405);
		}
		else
		{
			if( 0 != rename(m_fileLocalTmp.c_str(),m_fileLocal.c_str()) )
			{
				UpdateError(406);
			}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			pTarget->SetPromptString("2B");
#endif
			// 重新安装APK
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			//installAPK(m_fileLocal.c_str());
#endif
		}
	}
}

void CUpdateApk::OnLeave(UpdateManager* pTarget)
{
	
}

//
// =====----------------==========
//
void CUpdateResDif::OnEnter(UpdateManager* pTarget)
{
	pTarget->SetPromptString(501);

	VersionDef* pVer = gGameVersion->get_target_version();
	if ( pVer )
	{
		m_verTarget = *pVer;
	}
	else
	{
		m_verTarget = gGameVersion->svd().ver;
	}

	string path = gGameManager->GetResourceRoot();
	string key = gGameVersion->key_to_res_dif(m_verTarget);
	m_fileLocal = path + key + ".mpq";
	m_fileLocalTmp = m_fileLocal + ".tmp";
	m_fileURL = gGameVersion->key_to_url(key);
	if ( m_fileURL.empty() )
	{
		// 未找到，直接更新完成
		pTarget->EnterState(UpdateStateType_Succ);
		return;
	}

	if ( !m_fileDownloader.download(m_fileURL.c_str(),m_fileLocalTmp.c_str()) )
	{
		UpdateError(502);
	}
}

void CUpdateResDif::OnTimer(UpdateManager* pTarget,float dt)
{
	if ( m_fileDownloader.isBusy() )
	{
		pTarget->SetPromptString(503);
	}
	else
	{
		if ( !m_fileDownloader.getInfo().empty() )
		{
			UpdateError(504);
		}
		else
		{
			if( 0 != rename(m_fileLocalTmp.c_str(),m_fileLocal.c_str()) )
			{
				UpdateError(505);
			}
			
			pTarget->EnterState(UpdateStateType_Patch_Diff);
		}
	}
}

void CUpdateResDif::OnLeave(UpdateManager* pTarget)
{

}
//
// -=-------
// 
void CUpdatePatchDif::OnEnter(UpdateManager* pTarget)
{
	string path = gGameManager->GetResourceRoot();
	m_fileDat = path + "data.mpq";
	m_fileBak = path + "data.bak";

	VersionDef* pVer = gGameVersion->get_target_version();
	if ( pVer )
	{
		m_verTarget = *pVer;
	}
	else
	{
		m_verTarget = gGameVersion->svd().ver;
	}
	string key = gGameVersion->key_to_res_dif(m_verTarget);
	m_fileDif = path + key + ".mpq";

	// dif exist ?
	if ( gFileUtils->isFileExist(m_fileDif) )
	{
		m_mpqPatcher.patch(m_fileDat.c_str(),m_fileDif.c_str(),m_fileBak.c_str());
	}
	else
	{
		UpdateError(601);
	}
}

void CUpdatePatchDif::OnTimer(UpdateManager* pTarget,float dt)
{
	if ( m_mpqPatcher.isBusy() )
	{
		pTarget->SetPromptString(602);
	}
	else
	{
		if ( !m_mpqPatcher.getInfo().empty() )
		{
			UpdateError(603);
		}
		else
		{
			// update rvd ver
			remove(m_fileBak.c_str());
			remove(m_fileDif.c_str());
			gGameVersion->rvd().ver = m_verTarget;
			gGameVersion->saveRVD(gGameManager->GetRvdFile());

			// compare is the latest version?
			if ( gGameVersion->isResNeedUpdate() )
			{
				pTarget->EnterState(UpdateStateType_Res_Diff);
			}
			else
			{
				pTarget->EnterState(UpdateStateType_Succ);
			}
		}
	}
}

void CUpdatePatchDif::OnLeave(UpdateManager* pTarget)
{
	
}
//
// =====----------------==========
//
bool CUpdateResExt::isValidExtValue(int n)
{
	return (n >= ResExtPack1 && n < ResExtPackN);
}

void CUpdateResExt::OnEnter(UpdateManager* pTarget)
{
	pTarget->SetPromptString(701);

	int nExt = pTarget->GetExtension();
	if ( !isValidExtValue(nExt) )
	{
		pTarget->EnterState(UpdateStateType_Succ);
		return ;
	}

	// already has ?
	if ( gGameVersion->rvd().hasExtension(ResExtPack(nExt)) )
	{
		pTarget->EnterState(UpdateStateType_Succ);
		return ;
	}

	string path = gGameManager->GetResourceRoot();
	string key = gGameVersion->key_to_res_ext(nExt);
	m_fileLocal = path + key + ".mpq";
	m_fileLocalTmp = m_fileLocal + ".tmp";
	
	// ext mpq file exist ?
	if ( gFileUtils->isFileExist(m_fileLocal) )
	{
		pTarget->EnterState(UpdateStateType_Patch_Ext);
		return ;
	}

	m_fileURL = gGameVersion->key_to_url(key);
	if ( m_fileURL.empty() )
	{
		UpdateError(702);
	}

	if ( !m_fileDownloader.download(m_fileURL.c_str(),m_fileLocalTmp.c_str()) )
	{
		UpdateError(703);
	}
}

void CUpdateResExt::OnTimer(UpdateManager* pTarget,float dt)
{
	if ( m_fileDownloader.isBusy() )
	{
		pTarget->SetPromptString(704);
	}
	else
	{
		if ( !m_fileDownloader.getInfo().empty() )
		{
			UpdateError(705);
		}
		else
		{
			if( 0 != rename(m_fileLocalTmp.c_str(),m_fileLocal.c_str()) )
			{
				UpdateError(706);
			}
			pTarget->EnterState(UpdateStateType_Patch_Ext);
		}
	}
}

void CUpdateResExt::OnLeave(UpdateManager* pTarget)
{

}

//
// -=-------
// 
void CUpdatePatchExt::OnEnter(UpdateManager* pTarget)
{
	string path = gGameManager->GetResourceRoot();
	m_fileDat = path + "data.mpq";
	m_fileBak = path + "data.bak";

	string key = gGameVersion->key_to_res_ext(pTarget->GetExtension());
	m_fileExt = path + key + ".mpq";
	
	// ext mpq file exist ?
	if ( gFileUtils->isFileExist(m_fileExt) )
	{
		m_mpqPatcher.patch(m_fileDat.c_str(),m_fileExt.c_str(),m_fileBak.c_str());
	}
	else
	{
		UpdateError(901);
	}
}

void CUpdatePatchExt::OnTimer(UpdateManager* pTarget,float dt)
{
	if ( m_mpqPatcher.isBusy() )
	{
		pTarget->SetPromptString(902);
	}
	else
	{
		if ( !m_mpqPatcher.getInfo().empty() )
		{
			UpdateError(903);
		}
		else
		{
			gGameVersion->rvd().setExtension(ResExtPack(pTarget->GetExtension()));
			pTarget->SetExtension(-1);
			gGameVersion->saveRVD(gGameManager->GetRvdFile());

			remove(m_fileBak.c_str());
			remove(m_fileExt.c_str());

			pTarget->EnterState(UpdateStateType_Succ);
		}
	}
}

void CUpdatePatchExt::OnLeave(UpdateManager* pTarget)
{

}

//
//
//
void CUpdateSucc::OnEnter(UpdateManager* pTarget)
{
	pTarget->SetPromptString(1000);
}

void CUpdateSucc::OnTimer(UpdateManager* pTarget,float dt)
{
	if ( pTarget->GetUpdateUI()->GetProgressBar()->IsComplete() )
	{
		pTarget->OnUpdateComplete();
		pTarget->LeaveState();
		return ;
	}

}

void CUpdateSucc::OnLeave(UpdateManager* pTarget)
{

}

void CUpdateFail::OnEnter(UpdateManager* pTarget)
{
	
}

void CUpdateFail::OnTimer(UpdateManager* pTarget,float dt)
{

}

void CUpdateFail::OnLeave(UpdateManager* pTarget)
{
	
}

#include "GameDef.h"
#include "FileDownloadAsync.h"
#include "RunnableAsync.h"

#include "base/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "curl/include/win32/curl/curl.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "curl/include/ios/curl/curl.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "curl/include/android/curl/curl.h"
#endif

static size_t onUrlDownloadData(void *ptr, size_t size, size_t nmemb, void *userdata)
{
	FILE *fp = (FILE*)userdata;
	size_t written = fwrite(ptr, size, nmemb, fp);
	return written;
}

static int onUrlDownloadProgress(void *ptr, double totalToDownload, double nowDownloaded, double totalToUpLoad, double nowUpLoaded)
{
	FileDownloader* pDownloader = (FileDownloader*)ptr;
	pDownloader->setRange((int)totalToDownload);
	pDownloader->setPos((int)nowDownloaded);
	return 0;
}

class FileDownloaderAsync : public IRunnable
{
public:
	FileDownloaderAsync(FileDownloader* pOwner,const char* url,const char* target) : m_pOwner(pOwner),m_sURL(url),m_sTarget(target){}
	~FileDownloaderAsync(){}

protected:
	unsigned long download(const char* url,const char* target)
	{
		FILE *fp = fopen(target, "wb+");
		if (! fp)
		{
			string msg = "open file ";
			msg += target;
			msg += " failed.";
			m_pOwner->setInfo(msg);
			return 0;
		}

		CURL *_curl = curl_easy_init();
		if (! _curl)
		{
			m_pOwner->setInfo("can not init curl while download.");
			return 0;
		}

		CURLcode res;
		curl_easy_setopt(_curl, CURLOPT_URL, url);
		curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, onUrlDownloadData);
		curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
		curl_easy_setopt(_curl, CURLOPT_NOPROGRESS, false);
		curl_easy_setopt(_curl, CURLOPT_PROGRESSFUNCTION, onUrlDownloadProgress);
		curl_easy_setopt(_curl, CURLOPT_PROGRESSDATA, m_pOwner);

		res = curl_easy_perform(_curl);
		if (res != 0)
		{
			fclose(fp);
			curl_easy_cleanup(_curl);
			m_pOwner->setInfo("download url file failed!");
			return 0;
		}

		// 检查文件是否存在
		int retcode = 0;
		res = curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE,&retcode); 
		if ( (res != CURLE_OK) || retcode != 200 )
		{
			char msg[256] = "";
			sprintf(msg,"get url file info failed! retcode:%d",retcode);
			m_pOwner->setInfo(msg);
			fclose(fp);
			curl_easy_cleanup(_curl);
			return 0;
		}
		//// 获取文件大小
		//double length = 0;
		//res = curl_easy_getinfo(_curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD , &length);
		//if ( res != CURLE_OK )
		//{
		//	fclose(fp);
		//	curl_easy_cleanup(_curl);
		//	m_pOwner->setInfo("get url file size failed!");
		//	return 0;
		//}

		fclose(fp);
		curl_easy_cleanup(_curl);
		return m_pOwner->getPos();
	}

	void execute(){
		download(m_sURL.c_str(),m_sTarget.c_str());
		m_pOwner->onComplete();
	}

	FileDownloader* m_pOwner;
	string			m_sURL;
	string			m_sTarget;
};


FileDownloader::FileDownloader() : m_bFree(true)
{

}

FileDownloader::~FileDownloader()
{

}

bool FileDownloader::download(const char* url,const char* target)
{
	if ( isBusy() )
	{
		return false;
	}
	reset();
	doAsync(new FileDownloaderAsync(this,url,target));
	m_bFree = false;

	return true;
}

void FileDownloader::onComplete()
{
	m_bFree = true;
}
#ifndef __FileDownloadAsync_h_
#define __FileDownloadAsync_h_


#include "ProgressData.h"

class FileDownloader : public CProgressData
{
public:
	FileDownloader();
	~FileDownloader();

public:
	bool download(const char* url,const char* target);

	void onComplete();
	bool isBusy(){ return !m_bFree; }
protected:
	bool	m_bFree;
};

#endif
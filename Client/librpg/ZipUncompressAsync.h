#ifndef __ZipUncompressAsync_h_
#define __ZipUncompressAsync_h_

#include <string>
#include "ProgressData.h"
using namespace std;

class ZipUncompressAsync : public CProgressData
{
public:
	ZipUncompressAsync();
	~ZipUncompressAsync();

public:
	bool uncompress(const char* pszApkFile,const char* pszFileName,const char* pszDesPath);
	bool uncompress(const char* pszApkFile,const char* pszDesPath);
	bool copy(const char* file_src,const char* file_des);

	void onComplete();
	bool isBusy(){ return !m_bFree; }
protected:
	bool	m_bFree;
};

#endif
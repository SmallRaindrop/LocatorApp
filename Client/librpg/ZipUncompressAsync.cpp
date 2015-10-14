#include "ZipUncompressAsync.h"
#include "cocos2d.h"
USING_NS_CC;
#include "unzip/unzip.h"
#include "RunnableAsync.h"

class UncompressZipTask : public IRunnable
{
public:
	UncompressZipTask(ZipUncompressAsync* pOwner,const char* zip,const char* path,const char* file=NULL) : m_pOwner(pOwner){
		m_sZip = zip?zip:"";
		m_sPath = path?path:"";
		m_sFile = file?file:"";
	}
	~UncompressZipTask(){}

protected:
	unsigned long uncompress(const char* pszApkFile,const char* pszFileName,const char* pszDesPath)
	{
		if ( !pszApkFile || !pszFileName || !pszDesPath )
		{
			m_pOwner->setInfo("invalid params!");
			return 0;
		}

		static const unsigned long Max_Copy_Size = 1024*8;
		unzFile pFile = NULL;
		unsigned char* pBuffer = NULL;
		unsigned long size = 0;

		do 
		{
			pFile = unzOpen(pszApkFile);
			if ( !pFile )
			{
				string msg = "open zip(";
				msg.append(pszApkFile);
				msg.append(") failed!");
				m_pOwner->setInfo(msg);
				break;
			}

			int nRet = unzLocateFile(pFile, pszFileName, 1);
			if(UNZ_OK != nRet)
			{
				string msg = "zip(";
				msg.append(pszApkFile);
				msg.append(") locate file(");
				msg.append(pszFileName);
				msg.append(") failed!");
				m_pOwner->setInfo(msg);
				break;
			}

			char szFilePathA[260];
			unz_file_info file_info;
			nRet = unzGetCurrentFileInfo(pFile, &file_info, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
			if(UNZ_OK != nRet)
			{
				string msg = "zip(";
				msg.append(pszApkFile);
				msg.append(") get file(");
				msg.append(pszFileName);
				msg.append(") info failed!");
				m_pOwner->setInfo(msg);
				break;
			}

			m_pOwner->setRange(file_info.uncompressed_size);

			nRet = unzOpenCurrentFile(pFile);
			if(UNZ_OK != nRet)
			{
				string msg = "zip(";
				msg.append(pszApkFile);
				msg.append(") open file(");
				msg.append(pszFileName);
				msg.append(") failed!");
				m_pOwner->setInfo(msg);
				break;
			}
			string targetFileName = pszFileName;
			size_t pos = targetFileName.find_last_of("/");
			if ( pos != string::npos )
			{
				targetFileName = targetFileName.substr(pos+1,targetFileName.length()-pos-1);
			}

			string targetFilePathKey = pszDesPath;
			targetFilePathKey.append(targetFileName);
			FILE* fp = fopen(targetFilePathKey.c_str(),"wb+");
			if ( !fp )
			{
				string msg = "zip(";
				msg.append(pszApkFile);
				msg.append(") open target file(");
				msg.append(targetFilePathKey);
				msg.append(") failed!");
				m_pOwner->setInfo(msg);
				break;
			}

			fseek(fp,SEEK_SET,0);

			while ( size < file_info.uncompressed_size )
			{
				unsigned long tmpSize = file_info.uncompressed_size-size>Max_Copy_Size?Max_Copy_Size:file_info.uncompressed_size-size;

				pBuffer = new unsigned char[tmpSize];
				CCAssert(pBuffer != NULL, "not enough memory");
				int nSize = unzReadCurrentFile(pFile, pBuffer,tmpSize);
				CCAssert(nSize != 0, "the file size is wrong");
				fwrite(pBuffer,tmpSize,1,fp);
				delete pBuffer;
				size += tmpSize;

				m_pOwner->setPos(size);
			}

			fclose(fp);
			unzCloseCurrentFile(pFile);

		} while (0);


		if (pFile)
		{
			unzClose(pFile);
		}



		return size;
	}

	unsigned long uncompress(const char* pszApkFile,const char* pszDesPath)
	{
		return 0;
	}

	void execute(){
		if ( m_sZip.empty() )
		{
			m_pOwner->onComplete();
			return;
		}

		if ( m_sFile.empty() )
		{
			uncompress(m_sZip.c_str(),m_sPath.c_str());
		}
		else
		{
			uncompress(m_sZip.c_str(),m_sFile.c_str(),m_sPath.c_str());
		}

		m_pOwner->onComplete();
	}

	ZipUncompressAsync* m_pOwner;
	string m_sZip;
	string m_sPath;
	string m_sFile;
};

class CopyFileTask : public IRunnable
{
public:
	CopyFileTask(ZipUncompressAsync* pOwner,const char* src,const char* des) : m_pOwner(pOwner){
		m_sSrc = src?src:"";
		m_sDes = des?des:"";
	}
	~CopyFileTask(){}

protected:
	unsigned long copy(const string& src,const string& des)
	{
		if ( src.empty() || des.empty() )
		{
			m_pOwner->setInfo("invalid params!");
			return 0;
		}

		static const unsigned long Max_Copy_Size = 1024*8;
		char buffer[Max_Copy_Size] = {0};
		int ret = 0;

		FILE* fp_r = fopen(src.c_str(),"rb");
		if ( !fp_r )
		{
			string info = "can't open file [";
			info += src;
			info += "].";
			m_pOwner->setInfo(info);
			return 0;
		}

		FILE* fp_w = fopen(des.c_str(),"wb+");
		if ( !fp_w )
		{
			string info = "can't open file [";
			info += des;
			info += "].";
			m_pOwner->setInfo(info);
			return 0;
		}
        
        fseek(fp_r, 0, SEEK_END);
        size_t total_size = ftell(fp_r);
        fseek(fp_r, 0, SEEK_SET);
        
        m_pOwner->setRange(total_size);
        
		while ( !feof(fp_r) )
		{
            //int read_size = total_size - ret > Max_Copy_Size ? Max_Copy_Size : total_size - ret;
			size_t read_size = fread(buffer,1,Max_Copy_Size,fp_r);
			size_t write_size = fwrite(buffer,1,read_size,fp_w);
			assert(read_size == write_size);
			ret += read_size;
            m_pOwner->setPos(ret);
		}

		fflush(fp_w);

		fclose(fp_r);
		fclose(fp_w);
		
		return ret;
	}

	void execute(){
		if ( m_sSrc.empty() )
		{
			m_pOwner->onComplete();
			return;
		}

		copy(m_sSrc.c_str(),m_sDes.c_str());

		m_pOwner->onComplete();
	}

	ZipUncompressAsync* m_pOwner;
	string m_sSrc;
	string m_sDes;
};

ZipUncompressAsync::ZipUncompressAsync() : m_bFree(true)
{

}

ZipUncompressAsync::~ZipUncompressAsync()
{

}

bool ZipUncompressAsync::uncompress(const char* pszApkFile,const char* pszFileName,const char* pszDesPath)
{
	if ( !m_bFree )
	{
		return false;
	}

	reset();
	doAsync(new UncompressZipTask(this,pszApkFile,pszDesPath,pszFileName));
	m_bFree = false;

	return true;
}

bool ZipUncompressAsync::uncompress(const char* pszApkFile,const char* pszDesPath)
{
	if ( !m_bFree )
	{
		return false;
	}

	reset();
	doAsync(new UncompressZipTask(this,pszApkFile,pszDesPath));
	m_bFree = false;

	return true;
}

bool ZipUncompressAsync::copy(const char* file_src,const char* file_des)
{
	if ( !m_bFree )
	{
		return false;
	}

	reset();
	doAsync(new CopyFileTask(this,file_src,file_des));
	m_bFree = false;

	return true;
}

void ZipUncompressAsync::onComplete()
{
	m_bFree = true;
}
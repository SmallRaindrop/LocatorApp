#include "VersionManager.h"
#include "cocos2d.h"
#include "../CCFileUtils.h"
#include "StringConverter.h"
#include "tinyxml2/tinyxml2.h"
#include "commonRef.h"
USING_NS_CC;

VersionManager::VersionManager()
{
	initialize();
}

VersionManager::~VersionManager()
{
	release();
}

bool VersionManager::initialize()
{
	if ( !readLVDFromFile("localVersion.xml"))
	{
		return false;
	}

	return true;
}

void VersionManager::release()
{

}

bool VersionManager::readLVDFromFile(const string& xml)
{
	readFromFile(xml.c_str());

	if(reader.isEof())
		return false;

	bool ret = readLVDFromBuffer((const char*)reader.bytes(),reader.length());

	return ret;
}

bool VersionManager::readLVDFromBuffer(const char* pBuffer,size_t size)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.Parse(pBuffer,size);
	if ( ret != tinyxml2::XML_SUCCESS )
	{
		return false;
	}

	tinyxml2::XMLElement* pRootElement = doc.RootElement();
	if ( pRootElement )
	{
		for ( tinyxml2::XMLElement* pNode=pRootElement->FirstChildElement();
			pNode;
			pNode=pNode->NextSiblingElement() )
		{
			string eleName = pNode->Name();
			if( eleName == "pid" )
			{
				m_lvd.pid = StringConverter::toInt(pNode->GetText());
			}
			else if( eleName == "pro" )
			{
				m_lvd.pro = StringConverter::toInt(pNode->GetText());
			}
			else if ( eleName == "ver" )
			{
				VersionDef ver(pNode->GetText());
				m_lvd.ver = ver;
			}
			else if( eleName == "ext" )
			{
				m_lvd.ext = StringConverter::toInt(pNode->GetText());
			}
			else if( eleName == "url" )
			{
				m_lvd.url = pNode->GetText();
			}
			else if( eleName == "ip" )
			{
				m_lvd.ip = pNode->GetText();
			}
			else if( eleName == "port" )
			{
				m_lvd.port = StringConverter::toInt(pNode->GetText());
			}
		}

		return true;
	}

	return false;
}

bool VersionManager::readSVDFromFile(const string& xml)
{
	readFromFile(xml.c_str());

	if(reader.isEof())
		return false;

	bool ret = readSVDFromBuffer((const char*)reader.bytes(),reader.length());

	return ret;
}

bool VersionManager::readSVDFromBuffer(const char* pBuffer,size_t size)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.Parse(pBuffer,size);
	if ( ret != tinyxml2::XML_SUCCESS )
	{
		return false;
	}

	tinyxml2::XMLElement* pRootElement = doc.RootElement();
	if ( pRootElement )
	{
		for ( tinyxml2::XMLElement* pNode=pRootElement->FirstChildElement();
			pNode;
			pNode=pNode->NextSiblingElement() )
		{
			string eleName = pNode->Name();
			if ( eleName == "ver" )
			{
				VersionDef ver(pNode->GetText());
				m_svd.ver = ver;
			}
			else if( eleName == "ip" )
			{
				m_svd.ip = pNode->GetText();
			}
			else if( eleName == "port" )
			{
				m_svd.port = StringConverter::toInt(pNode->GetText());
			}
			else if( eleName == "debug" )
			{
				m_debug = StringConverter::toInt(pNode->GetText());
			}
			if ( eleName == "ver_d" )
			{
				VersionDef ver(pNode->GetText());
				m_svd_d.ver = ver;
			}
			else if( eleName == "ip_d" )
			{
				m_svd_d.ip = pNode->GetText();
			}
			else if( eleName == "port_d" )
			{
				m_svd_d.port = StringConverter::toInt(pNode->GetText());
			}
		}

		return true;
	}

	return false;
}

bool VersionManager::readRVD(const string& rvd)
{
	FILE* fp = fopen(rvd.c_str(),"rb+");
	if ( fp )
	{
		int a,b,c,d,e;

		fread(&a,4,1,fp);
		fread(&b,4,1,fp);
		fread(&c,4,1,fp);
		fread(&d,4,1,fp);
		fread(&e,4,1,fp);

		fclose(fp);

		m_rvd.ver.v0 = a;
		m_rvd.ver.v1 = b;
		m_rvd.ver.v2 = c;
		m_rvd.ext = e;

		return true;
	}

	return false;
}

bool VersionManager::saveRVD(const string& rvd)
{
	FILE* fp = fopen(rvd.c_str(),"wb+");
	if ( fp )
	{
		fwrite(&m_rvd.ver.v0,4,1,fp);
		fwrite(&m_rvd.ver.v1,4,1,fp);
		fwrite(&m_rvd.ver.v2,4,1,fp);
		fwrite(&m_rvd.ext,4,1,fp);

		fclose(fp);

		return true;
	}

	return false;
}

bool VersionManager::readUpdateDescFromFile(const string file)
{
	readFromFile(file.c_str());

	if(reader.isEof())
		return false;

	bool ret = readUpdateDescFromBuffer((const char*)reader.bytes(),reader.length());

	return ret;
}

bool VersionManager::readUpdateDescFromBuffer(const char* pBuffer,size_t size)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError ret = doc.Parse(pBuffer,size);
	if ( ret != tinyxml2::XML_SUCCESS )
	{
		return false;
	}

	tinyxml2::XMLElement* pRootElement = doc.RootElement();
	if ( pRootElement )
	{
		for ( tinyxml2::XMLElement* pNode=pRootElement->FirstChildElement();
			pNode;
			pNode=pNode->NextSiblingElement() )
		{
			string eleName = pNode->Name();
			if ( eleName == "mapping" )
			{
				for ( tinyxml2::XMLElement* pSubNode=pNode->FirstChildElement();
					pSubNode;
					pSubNode=pSubNode->NextSiblingElement() )
				{
					const char* key = pSubNode->Attribute("key");
					const char* target = pSubNode->Attribute("target");
					if ( key && target )
					{
						VersionDef ver(target);
						m_mapping[key] = ver;
					}
				}
			}
			else if( eleName == "list")
			{
				for ( tinyxml2::XMLElement* pSubNode=pNode->FirstChildElement();
					pSubNode;
					pSubNode=pSubNode->NextSiblingElement() )
				{
					const char* key = pSubNode->Attribute("key");
					const char* url = pSubNode->Attribute("url");
					if ( key && url )
					{
						m_list[key] = url;
					}
				}
			}
		}
	}

	return true;
}

string VersionManager::key_to_url(string key)
{
	UpdateList::iterator itr = m_list.find(key);
	if ( itr != m_list.end() )
	{
		return itr->second.c_str();
	}

	return "";
}

VersionDef* VersionManager::get_target_version()
{
	string key = rvd().ver.to_str();
	VersionMapping::iterator itr = m_mapping.find(key);
	if ( itr != m_mapping.end() )
	{
		return &(itr->second);
	}

	return NULL;
}

bool VersionManager::isResExpired()
{
	// APK包中必须要有资源包
	if( gFileUtils->isFileExist("data.mpq") )
	{
		// APK包中的版本必须要高于资源版本
		if ( lvd().ver.is_high_to(rvd().ver) )
		{
			return true;
		}

		// 如果APK包中版本与资源版本相等，APK包中资源必须要大于扩展资源包。
		if( lvd().ver.is_equal_to(rvd().ver) && lvd().ext > rvd().ext )
		{
			return true;
		}
	}

	return false;
}

bool VersionManager::isApkExpired()
{
	return lvd().ver.is_invalid_to(svd().ver);
}

bool VersionManager::isDebugMode()
{
	return (m_debug>0 && lvd().ver.is_equal_to(svd_d().ver));
}

bool VersionManager::isApkNeedUpdate()
{
	return svd().ver.is_v2_high_to(lvd().ver);
}

bool VersionManager::isResNeedUpdate()
{
	return svd().ver.is_high_to(rvd().ver);
}
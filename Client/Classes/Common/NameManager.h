#ifndef __NAMEMANAGER_H_
#define __NAMEMANAGER_H_

#include "GameDef.h"
#include "Singleton.h"
#include <string>
#include <vector>
#include <set>
#include <map>

#define  gStrManager (NameManager::Instance())

typedef std::set<std::string> T_CharSet;

typedef std::map<unsigned char,T_CharSet> T_CharMap;

class NameManager : public Singleton_Auto<NameManager>
{

public:
	NameManager();
	~NameManager();

	bool init();

	void readNames();
	void readSensitiveStrings();

	std::string randomName(int sex);
	int getRandomPos(int size);
	 
	void addSensitiveString(const std::string& msg);
	bool replaceMsgByFilter(std::string* msg);    //将关键词转为*;
    bool replaceMsgByFilter( std::string& msg ,char* outBuff=NULL,int outLen=0); //替换敏感词,优化失败

	std::string getString(std::string key);  

	std::string getCareerById(int id);
    std::string getClientString(int key) const;
 

public:
	std::vector<std::string> _surNameMale;   //男姓；
	std::vector<std::string> _NameMale;       //男名1；
	std::vector<std::string> _surNameFamale;    //女姓；
	std::vector<std::string> _NameFamale;    //女名2；

	std::set<std::string> _filterNameString;    //敏感词的集合;
    T_CharMap _filterNameStringArr; // 不分字节数，最多6字节

	std::map< std::string , std::string > _stringsMap;
};
 



#endif
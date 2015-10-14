#include "NameManager.h"
#include "GameScene/GameDataManager.h"
#include "CommonDef.h"

using namespace std;
NameManager::NameManager()
{
	_surNameMale.clear();
	_NameMale.clear();
	_surNameFamale.clear();
	_NameFamale.clear();
	_filterNameString.clear();
	_stringsMap.clear();

	init();
}


bool NameManager::init()
{ 
	readNames();
	readSensitiveStrings(); 

	 return true;
}

NameManager::~NameManager()
{
	_surNameMale.clear();
	_NameMale.clear();
	_surNameFamale.clear();
	_NameFamale.clear();
	_filterNameString.clear();
	 _stringsMap.clear(); 
}


int NameManager::getRandomPos( int size )
{
	if (!size)
	{
		return 0;
	} 
	struct timeval tNow;
	gettimeofday(&tNow, NULL);
	srand( (tNow.tv_sec * 1000 + tNow.tv_usec / 1000));    //用当前系统时间(ms);
	 
	return (rand()%size);
}

std::string NameManager::randomName( int sex )
{
	std::string name = "";
	if (sex == 1)//男名；
	{ 
		name = _surNameMale[getRandomPos(_surNameMale.size())];
		name.append(_NameMale[getRandomPos(_NameMale.size())]);
	}
	else        //女名;
	{
		name = _surNameFamale[getRandomPos(_surNameFamale.size())];
		name.append(_NameFamale[getRandomPos(_NameFamale.size())]);
	}
	return name;
}

bool NameManager::replaceMsgByFilter( std::string*  msg )
{
	bool result=false;
	if(!msg)
		return false;
	std::string replaceStr = "*";
	int pos = 0;
	int srclen = 0;
	int dstlen = 0;
	std::set<std::string>::iterator iter = _filterNameString.begin();
	for(; iter != _filterNameString.end(); ++iter)
	{
		pos = 0;
		srclen = iter->size();
		dstlen = replaceStr.size();
		while((pos = msg->find((*iter).c_str(), pos)) != std::string::npos)
		{
			result=true;
			msg->replace(pos, srclen, replaceStr.c_str());
			pos += dstlen;
		}
	}

	return result;
}

bool NameManager::replaceMsgByFilter( std::string& msg ,char* outBuff,int outLen)
{
    unsigned char isFind;
    if(msg.size()==0)
        return false;
    char buf[1024]={0};
    char* buff=buf;
    int bufLen=0;

    const char* msgStr=msg.c_str();
    unsigned char value;
    int byte;
    
    std::set<std::string>::iterator iter;
    std::set<std::string>::iterator itend;

    T_CharMap::iterator it2;

    const char* temp;
    const char* temp2;
    int size;

    while((value=*msgStr)!='\0')  //不等于结束符
    {
        isFind&=0;
        it2=_filterNameStringArr.find(value);    
        if(it2!=_filterNameStringArr.end())
        {
            iter=it2->second.begin(); 
            itend=it2->second.end();
            while (iter!=itend)
            {
                temp=iter->c_str()+1;
                temp2=msgStr+1;
                size=iter->size();
                int i=1;
                while (i<size &&*temp++==*temp2++)
                {
                    i++;
                }
                if(i==size)
                {
                    isFind|=1;
                    break;
                }
                iter++;
            }
        }
       

        if(isFind&1)
        {
            *buff++='*';
            msgStr+=size;
        }
        else
        {
            byte=GetUtf8ByteNumByFirstWord(value);
            memcpy(buff,msgStr,byte);
            msgStr+=byte;
            buff+=byte;            
        }        
    }

    size=buff-buf;
    if(msg.size()!=size)
    {
        if(outBuff)
        {
            if(size<outLen)
            {
                memcpy(outBuff,buf,outLen);
                outBuff[buff-buf]='\0';
            }
        }
        else
        {
            msg=buf; //重新复制
        }
    }
    return true;
}

void NameManager::addSensitiveString(const std::string& msg )
{
	int size = msg.size();

	char* sentence;
	sentence = new char[size+1];
	strncpy(sentence, msg.c_str(), msg.size());
	sentence[msg.size()] = '\0';

	string value;
	char *tokenPtr=strtok(sentence, ",");


	while(tokenPtr != 0)
	{
		value = tokenPtr;
		_filterNameString.insert(value);

		tokenPtr=strtok(0, ",");
	}

	delete []sentence;
}

std::string NameManager::getString( std::string key )
{
	std::map< std::string , std::string >::iterator it = _stringsMap.find(key);
	if(it == _stringsMap.end())
	{
		return "";
	}
	else
	{
		return (*it).second;
	}
}

std::string NameManager::getCareerById( int id )
{
	std::string result="";
	switch (id)
	{
	case 1:
		{
			result=getString("zhanshi");
			break;
		}
	case 2:
		{
			result=getString("daoshi");
			break;
		}
	case 3:
		{
			result=getString("fashi");
			break;
		}
	default:
		break;
	}
	return result;
}

void NameManager::readNames()
{
	string name0=RandomNameData.get(1)->name;
	std::vector<string> namelist0; 
	StringSplit(name0,",", namelist0);    /** 分割字符串，str为源字符串，delimd为分隔符，des为输出的字符串容器 */
	_surNameMale = namelist0;

	string name1=RandomNameData.get(2)->name;
	std::vector<string> namelist1; 
	StringSplit(name1,",", namelist1);   
	_NameMale = namelist1;

	string name2=RandomNameData.get(3)->name;
	std::vector<string> namelist2; 
	StringSplit(name2,",", namelist2);   
	_surNameFamale = namelist2;

	string name3=RandomNameData.get(4)->name;
	std::vector<string> namelist3; 
	StringSplit(name3,",", namelist3);   
	_NameFamale = namelist3;
}

void NameManager::readSensitiveStrings()
{ 
	Data data = gFileUtils->getDataFromFile("assets/Data/sensitive_words_list.txt");
	if(!data.isNull()) return;
	std::string senStr;
	senStr.clear(); 
	for(ssize_t i = 0;i<data.getSize();++i )
	{
		senStr.push_back(data.getBytes()[i]);
	}
    //
	std::vector<string> senlist; 
	StringSplit(senStr,",", senlist);   
	std::vector<string>::iterator it=senlist.begin();
    unsigned char value;
	for(it;it!=senlist.end();it++)
	{
		_filterNameString.insert(*it);
        value=(unsigned char)((*it)[0]);

        T_CharMap::iterator it2=_filterNameStringArr.find(value);
        if(it2!=_filterNameStringArr.end())
        {
            it2->second.insert(*it);
        }
        else
        {
            T_CharSet set;
            set.insert(*it);
            _filterNameStringArr.insert(make_pair(value,set));
        }
	}
	senlist.clear();  
	 
}

std::string NameManager::getClientString( int key ) const
{
	//to do longhua

    //auto pCfg=dbManager::clientSystemStringTable.get(key);
    //if (pCfg)
    //{
    //    return pCfg->value;
    //}
    //static std::string strDef;
    //return strDef;
	return "";
}


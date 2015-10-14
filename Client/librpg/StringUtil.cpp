#include "StringUtil.h"
#include "StringConverter.h"
#include "cocos2d.h"
USING_NS_CC;


/** 把字符串转化为颜色 */
Color3B StringUtil::StringToColor( const string& str,const string& delimd )
{
    vector<string> v;
    v.clear();
    StringSplit(str,delimd,v);
    if (v.size()<3)
        return Color3B(255,255,255);
    int r = StringConverter::toInt(v[0]);
    int g = StringConverter::toInt(v[1]);
    int b = StringConverter::toInt(v[2]);
    return Color3B(r,g,b);
}

Rect StringUtil::StringToRect( const string& str,const string& delimd )
{
	vector<string> v;
	v.clear();
	StringSplit(str,delimd,v);
	if (v.size()<4)
        return Rect::ZERO;
	int x = StringConverter::toInt(v[0]);
	int y = StringConverter::toInt(v[1]);
	int w = StringConverter::toInt(v[2]);
	int h = StringConverter::toInt(v[3]);
	return Rect(x,y,w,h);
}

int StringUtil::StringSplit( const string& str,const string& delimd,vector<string>& des )
{
	size_t start = 0;
	size_t pos = 0;

    int delimdCount=0;
	for( unsigned int i = 0; ; i++ )
	{
		if( pos == str.npos )	break;

		pos = str.find_first_of(delimd,start);
		des.push_back(str.substr( start, pos - start ));
		delimdCount++;
		start = pos+delimd.size();
	}

    return delimdCount;
}

int StringUtil::StringSplit( const string& str,const string& delimd,list<string>& des )
{
    size_t start = 0;
    size_t pos = 0;

    int delimdCount=0;
    for( unsigned int i = 0; ; i++ )
    {
        if( pos == str.npos )	break;

        pos = str.find_first_of(delimd,start);
        if( pos != str.npos )
            delimdCount++;
        des.push_back(str.substr( start, pos - start ));
        start = pos+delimd.size();
    }

    return delimdCount;
}

/*字符串替换*/
void StringUtil::ReplaceStr(char* buf,std::string str,std::string pattern,std::string dstPattern,int count)
{
    std::string retStr="";
    string::size_type pos;

    int szStr=str.length();
    int szPattern=pattern.size();
    int i=0;
    int l_count=0;
    if(-1 == count) // replace all
        count = szStr;

    for(i=0; i<szStr; i++)
    {
        pos=str.find(pattern,i);

        if(std::string::npos == pos)
            break;
        if(pos < szStr)
        {
            std::string s=str.substr(i,pos-i);
            retStr += s;
            retStr += dstPattern;
            i=pos+pattern.length()-1;
            if(++l_count >= count)
            {
                i++;
                break;
            }
        }
    }
    retStr += str.substr(i);
    //	buf=retStr.c_str();
    strcpy(buf,retStr.c_str());
    //	return buf;
}

void StringUtil::ReplaceStr( std::string& str,std::string pattern,std::string dstPattern,int count/*=-1*/ )
{
    std::string buf;
    buf.resize(str.size()*4);
    ReplaceStr(&buf[0],str,pattern,dstPattern,count);
    str=buf.c_str();
}

void StringUtil::StringTrim( string& str,char ch/*=' '*/ )
{
	string::size_type pos = str.find_last_not_of(ch);
	if(pos != string::npos)
	{
		str.erase(pos + 1);
		pos = str.find_first_not_of(ch);
		if(pos != string::npos) str.erase(0, pos);
	}
	else
	{
		str.erase(str.begin(), str.end());
	}
	return;
}

void StringUtil::StringToLower( string& str )
{
    for (string::iterator iter=str.begin();iter!=str.end();iter++)
    {
        *iter=tolower(*iter);
    }
}

void StringUtil::StringToUper( string& str )
{
	for (string::iterator iter=str.begin();iter!=str.end();iter++)
    {
        *iter=toupper(*iter);
    }
}

string StringUtil::StringCut(const string& str,int max,const string& tail)
{
	string ret = "";
	int i = 0;
	while ( i<str.length() && i < max )
	{
		unsigned char c = str[i];
		if(c >127){			//中文
			ret += str.substr(i,3);
			i += 3;
		}
		else{              //英文
			ret += str.substr(i,1);
			i += 1;
		}
	}

	if ( str.length() > max )
	{
		return ret + tail;
	}

	return ret;
}

string StringUtil::StringCutFileName(const string& fileName)
{
	size_t pos1 = fileName.find_last_of("/\\");
	size_t pos2 = fileName.find_last_of(".");

	CCLOG("StringCutFileName pos1[%lu],pos2[%lu]",pos1,pos2);

	int len = 0;
	if ( pos1 == string::npos )
	{
		pos1 = 0;
	}
	if ( pos2 == string::npos )
	{
		len = fileName.length()-pos1-1;
	}
	else
	{
		len = pos2 - pos1 -1 > 0 ? pos2 - pos1 -1 : 0;
	}

	CCLOG("StringCutFileName pos1[%lu],len[%d]",pos1,len);

	string ret = fileName.substr(pos1+1,len);

	CCLOG("StringCutFileName ret[%s]",ret.c_str());

	return ret;
}
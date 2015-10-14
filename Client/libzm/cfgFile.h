/***
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：配置文件读写相关
 */

#ifndef __cfgFile_h_
#define __cfgFile_h_

#include <string>
#include <vector>
using namespace std;

#define	cfgFieldKey			1
#define cfgFieldNoClient	2
#define cfgFieldNoServer	4

#define cfgDataLength		1024*1024

enum cfgFieldType
{
	cfgFieldType_None = 0,
	cfgFieldType_Int,
	cfgFieldType_String,
	cfgFieldType_List,
};

struct cfgField{
	char	cLen;
	string	sName;
	short	nType;
	short	nProperty;

	cfgField(){
		cLen = 0;
		sName = "";
		nType = cfgFieldType_Int;
		nProperty = 0;
	}

	cfgField(const char* name,char len){
		cLen = len;
		sName = name;
		nType = cfgFieldType_Int;
		nProperty = 0;
	}

	void setType(short type){
		nType = type;
	}
	void setProperty(short p){
		nProperty = p;
	}
	void addProperty(short p){
		nProperty |= p;
	}
	void clrProperty(short p){
		nProperty &= (~p);
	}
	bool hasProperty(short p){
		return (nProperty & p) > 0;
	}
};

struct cfgData{
	string				module_name;
	int					field_count;
	int					record_count;
	vector<cfgField>	fields;
	int					size;
	int					ptr;
	char*				data;

	cfgData() : data(NULL){
		clear();
	}

	~cfgData(){
		if ( data )
		{
			delete[] data;
			data = NULL;
		}
	}

	void clear(){
		field_count = 0;
		record_count = 0;
		fields.clear();	
		size = 0;
		ptr = 0;
		if ( data )
		{
			delete data;
			data = NULL;
		}
	}

	void put(const void* p,int s){
		memcpy(data+size,p,s);
		size += s;
	}

	void put(int val){
		put(&val,sizeof(int));
	}

	void put(const char* str){
		int len = (int)strlen(str);
		put(&len,sizeof(int));
		put(str,len);
	}

	void bof(){
		ptr = 0;
	}

	void eof(){
		ptr = size;
	}

	int getInt(){
		int ret = *((int*)(data+ptr));
		ptr += sizeof(int);
		return ret;
	}

	string getString(){
		int len = *((int*)(data+ptr));
		ptr += sizeof(int);
		
		string ret = "";
		for ( int i=0;i<len;++i )
		{
			ret.push_back(*(data+ptr+i));
		}
		ptr += len;
		return ret;
	}

	void get(int& val){
		val = *((int*)(data+ptr));
		ptr += sizeof(int);
	}

	void get(string& str){

		str.clear();
		int len = *((int*)(data+ptr));
		ptr += sizeof(int);

		for(int i = 0;i<len;++i )
		{
			str.push_back(*(data+ptr+i));
		}

		ptr += len;
	}
};

class CCfgFile
{
public:
	CCfgFile();
	~CCfgFile();

public:
	cfgData*	load(const char* cfg_file);
	void		save(const char* cfg_file,cfgData* pData);

protected:
	// generate code for db.h
	string		convertToDbString(cfgData* pData);

public:
	static string	s_dbString;
};

#endif
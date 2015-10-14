#include "cfgFile.h"
#include <stdio.h>
#include <algorithm>

string CCfgFile::s_dbString = "#ifndef __db_h_\n#define __db_h_\n\n#include \"cfgFile.h\"\n\n";

CCfgFile::CCfgFile()
{

}

CCfgFile::~CCfgFile()
{

}

cfgData* CCfgFile::load(const char* cfg_file)
{
	if ( !cfg_file )
	{
		return NULL;
	}

	FILE* fp = fopen(cfg_file,"rb+");
	if ( !fp )
	{
		return NULL;
	}

	cfgData* pData = new cfgData;
	if ( !pData )
	{
		fclose(fp);
		return NULL;
	}

	unsigned char module_name_len = 0;
	fread(&module_name_len,1,1,fp);
	char* sModuleName = new char[module_name_len+1];
	memset(sModuleName,0,module_name_len+1);
	fread(sModuleName,module_name_len,1,fp);
	pData->module_name = sModuleName;
	delete[] sModuleName;

	// field count
	fread(&(pData->field_count),sizeof(int),1,fp);
	// record count
	fread(&(pData->record_count),sizeof(int),1,fp);

	// fields info
	for ( int j= 0;j<pData->field_count;++j )
	{
		cfgField field;
		
		fread(&field.cLen,1,1,fp);
		char nameLen = 0;
		fread(&nameLen,1,1,fp);

		char* sName = new char[nameLen+1];
		memset(sName,0,nameLen+1);
		fread(sName,nameLen,1,fp);
		field.sName = sName;
		delete[] sName;
		sName = NULL;

		fread(&field.nType,2,1,fp);
		fread(&field.nProperty,2,1,fp);

		pData->fields.push_back(field);
	}

	fread(&(pData->size),sizeof(int),1,fp);
	pData->data = new char[pData->size];
	if ( pData->data )
	{
		fread(pData->data,1,pData->size,fp);
	}

	fclose(fp);

	return pData;
}

string CCfgFile::convertToDbString(cfgData* pData)
{
	string dbString = "struct ";
	string structName = pData->module_name;
	transform(structName.begin(), structName.begin()+1, structName.begin(), (int(*)(int))toupper); 
	structName += "Cfg";
	dbString += structName;
	dbString += "{\n";

	string key = "id";
	string structList = "";
	string readList = "";
	string formatList = "";
	string formatArgs = "";
	// fields info
	for ( int j= 0;j<pData->field_count;++j )
	{
		cfgField field = pData->fields[j];

		if ( field.hasProperty(cfgFieldKey) )
		{
			key = field.sName;
		}

		if ( field.nType == cfgFieldType_Int )
		{
			structList += "	int		";
			formatList += "%d,";
			formatArgs += field.sName;
			formatArgs += ",";
		}
		else if ( field.nType == cfgFieldType_String )
		{
			structList += "	string	";
			formatList += "%s,";
			formatArgs += field.sName;
			formatArgs += ".c_str(),";
		}
		else if ( field.nType == cfgFieldType_List )
		{
			structList += "	string	";
			formatList += "%s,";
			formatArgs += field.sName;
			formatArgs += ".c_str(),";
		}

		structList += field.sName;
		structList += ";\n";
		readList += "		pData->get(";
		readList += field.sName;
		readList += ");\n";
	}

	formatList.erase(formatList.length()-1,1);
	formatArgs.erase(formatArgs.length()-1,1);

	dbString += structList;
	dbString += "\n	int key(){ return ";
	dbString += key;
	dbString += ";}\n\n	void read(cfgData* pData){\n";
	dbString += readList;
	dbString += "	}\n\n	void format(char* str){\n		sprintf(str,\"";
	dbString += formatList;
	dbString += "\",";
	dbString += formatArgs;
	dbString += ");\n	}\n};";

	return dbString;
}

void CCfgFile::save(const char* cfg_file,cfgData* pData)
{
	if ( !cfg_file || !pData )
	{
		return ;
	}

	s_dbString += convertToDbString(pData);
	s_dbString += "\n\n";
	
	FILE* fp = fopen(cfg_file,"wb+");
	if ( !fp )
	{
		return ;
	}

	// module name
	unsigned char module_name_len = pData->module_name.size();
	fwrite(&module_name_len,1,1,fp);
	fwrite(pData->module_name.c_str(),module_name_len,1,fp);

	// field count
	fwrite(&(pData->field_count),sizeof(int),1,fp);
	// record count
	fwrite(&(pData->record_count),sizeof(int),1,fp);

	// fields info
	for ( int j= 0;j<pData->field_count;++j )
	{
		cfgField field = pData->fields[j];

		fwrite(&field.cLen,1,1,fp);
		char nameLen = field.sName.length();
		fwrite(&nameLen,1,1,fp);
		fwrite(field.sName.c_str(),nameLen,1,fp);
		fwrite(&field.nType,2,1,fp);
		fwrite(&field.nProperty,2,1,fp);
	}

	fwrite(&(pData->size),sizeof(int),1,fp);
	fwrite(pData->data,pData->size,1,fp);

	fclose(fp);
}
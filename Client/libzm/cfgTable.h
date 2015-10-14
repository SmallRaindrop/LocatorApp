/***
 * 作者：岳良友
 * 时间：2015-06-19
 * 说明：配置文件读写相关
 */

#ifndef __cfgTable_h_
#define __cfgTable_h_

#include "cfgFile.h"

template <class T>
class ForeachIterator
{
public:
	virtual bool execute(T* item) = 0;
};

template <class T>
class CCfgTable
{
public:
	CCfgTable();
	virtual ~CCfgTable();

	typedef vector<T*>	ConfigTable;
protected:
	ConfigTable			m_Data;

	bool	load(cfgData* data);

public:
	T*		get(int key);
	inline const ConfigTable& getData(){return m_Data;}
	void	foreach(ForeachIterator<T>& itr);
	bool	load(const char* cfg_file);
	bool	load(const unsigned char* buffer,size_t size );
	bool	load(ByteArray& bytes);
	void	release();
	void	log(const char* log_file);
};

template <class T>
CCfgTable<T>::CCfgTable()
{

}

template <class T>
CCfgTable<T>::~CCfgTable()
{
	release();
}

template <class T>
void CCfgTable<T>::release()
{
	for ( size_t i=0;i<m_Data.size();++i )
	{
		T* pItem = m_Data[i];
		if ( pItem )
		{
			delete pItem;
		}
	}

	m_Data.clear();
}

template <class T>
bool CCfgTable<T>::load(cfgData* data)
{
	for ( int i=0;i<data->record_count;++i )
	{
		T* item = new T;
		if (item)
		{
			item->read(data);
			m_Data.push_back(item);
		}
	}

	return true;
}

template <class T>
bool CCfgTable<T>::load(const char* cfg_file)
{
	CCfgFile cfgFile;
	cfgData* pData = cfgFile.load(cfg_file);
	if ( pData )
	{
		load(pData);

		delete pData;
		pData = NULL;

		return true;
	}

	return false;
}

template <class T>
bool CCfgTable<T>::load(const unsigned char* buffer,size_t size )
{
	ByteArray bytes(buffer,size);
	return load(bytes);
}

template <class T>
bool CCfgTable<T>::load(ByteArray& bytes)
{
	if ( bytes.isNull() )
	{
		return false;
	}

	cfgData* pData = new cfgData;
	if ( !pData )
	{
		return false;
	}

	pData->module_name = bytes.read_string();
	pData->field_count = bytes.read_integer();
	pData->record_count = bytes.read_integer();

	// fields info
	for ( int j= 0;j<pData->field_count;++j )
	{
		cfgField field;
		field.cLen = bytes.read_byte();
		field.sName = bytes.read_string();
		field.nType = bytes.read_short();
		field.nProperty = bytes.read_short();

		pData->fields.push_back(field);
	}

	pData->size = bytes.read_integer();
	pData->data = new char[pData->size];
	if ( pData->data )
	{
		bytes.read(pData->data,pData->size);
	}

	load(pData);

	delete pData;
	pData = NULL;

	return true;
}

template <class T>
T* CCfgTable<T>::get(int id)
{
	for ( size_t i=0;i<m_Data.size();++i )
	{
		T* pItem = m_Data[i];
		if ( pItem && pItem->key() == id )
		{
			return pItem;
		}
	}

	return NULL;
}

template <class T>
void CCfgTable<T>::foreach(ForeachIterator<T>& itr)
{
	for ( size_t i=0;i<m_Data.size();++i )
	{
		T* pItem = m_Data[i];
		// 不判断pItem为空，让其暴露出来
		if ( !itr.execute(pItem) )
		{
			break;
		}
	}
}

template <class T>
void CCfgTable<T>::log(const char* log_file)
{
	FILE* fp = fopen(log_file,"wt+");
	if ( !fp )
	{
		return ;
	}

	for ( size_t i=0;i<m_Data.size();++i )
	{
		T* pItem = m_Data[i];
		if ( pItem )
		{
			char str[1024] = "";
			pItem->format(str);
			fprintf(fp,"%s\n",str);
		}
	}

	fclose(fp);
}

#endif

#include "MPQPackage.h"
#include "../hashCode.h"
#include <memory.h>
#include "zlib.h"

MPQPackage::MPQPackage() : m_fptr(NULL),m_IdentCode(0)
{
	clear_block_table();
}

MPQPackage::~MPQPackage()
{
	close(false);
}

void MPQPackage::clear_block_table()
{
	for ( size_t i=0;i<m_blockTable.size();++i )
	{
		delete m_blockTable[i];
	}

	m_blockTable.clear();
}

void MPQPackage::format_block_table(const char* log)
{
	FILE* fp = fopen(log,"w+");
	if ( !fp )
	{
		return ;
	}

	for ( int i=0;i<(int)m_blockTable.size();++i )
	{
		MPQBlock* pBlock = m_blockTable[i];
		if ( pBlock )
		{
			fprintf(fp,"idx:%04d,md5:%s,file: %s\n",i+1,MD5::binaryToHexString(pBlock->md5_code,MPQ_MD5_CODE_LEN).c_str(),pBlock->name.c_str());
		}
	}

	fclose(fp);
}

void MPQPackage::read_header(FILE* fptr)
{
	if ( !fptr )
	{
		return ;
	}

	fseek(fptr,0,SEEK_SET);
	unsigned char* pBuffer = new unsigned char[sizeof(MPQHeader)];
	fread(pBuffer,sizeof(MPQHeader),1,fptr);
	decrypt(pBuffer,(unsigned char*)&m_stHeader,sizeof(MPQHeader));
	delete[] pBuffer;
}

void MPQPackage::read_hash_table(FILE* fptr)
{
	if ( !fptr )
	{
		return ;
	}

	fseek(fptr,m_stHeader.hash_table_offset,SEEK_SET);
	unsigned char* pBuffer = new unsigned char[sizeof(MPQHashNode)*m_stHeader.hash_count];
	fread(pBuffer,sizeof(MPQHashNode),m_stHeader.hash_count,fptr);
	decrypt(pBuffer,(unsigned char*)&m_hashTable,sizeof(MPQHashNode)*m_stHeader.hash_count);
	delete[] pBuffer;
}

void MPQPackage::read_block_table(FILE* fptr)
{
	if ( !fptr )
	{
		return ;
	}

	clear_block_table();

	fseek(fptr,m_stHeader.block_table_offset,SEEK_SET);

	for ( unsigned int i = 0;i<m_stHeader.block_count; ++i )
	{
		MPQBlock* pBlock = new MPQBlock;
		unsigned char len = 0;
		fread(&len,1,1,fptr);

		unsigned char* pBuffer = new unsigned char[len];
		fread(pBuffer,1,len,fptr);

		unsigned char* name = new unsigned char[len+1];
		memset(name,0,len+1);
		decrypt(pBuffer,name,len);
		pBlock->name = (char*)name;
		delete[] pBuffer;
		delete[] name;

		fread(&(pBlock->offset),sizeof(unsigned int),1,fptr);
		fread(&(pBlock->size),sizeof(unsigned int),1,fptr);
		fread(&(pBlock->uncompress_size),sizeof(unsigned int),1,fptr);
		fread(&(pBlock->flag),sizeof(unsigned int),1,fptr);
		fread(&(pBlock->md5_code),1,MPQ_MD5_CODE_LEN,fptr);
		m_blockTable.push_back(pBlock);
	}
}

void MPQPackage::write_header(FILE* fptr)
{
	if ( !fptr )
	{
		return ;
	}

	fseek(fptr,0,SEEK_SET);
	unsigned char* pBuffer = new unsigned char[sizeof(MPQHeader)];
	encrypt((unsigned char*)&m_stHeader,pBuffer,sizeof(MPQHeader));
	fwrite(pBuffer,sizeof(MPQHeader),1,fptr);
	delete[] pBuffer;
}

void MPQPackage::write_hash_table(FILE* fptr)
{
	if ( !fptr )
	{
		return ;
	}

	fseek(fptr,m_stHeader.hash_table_offset,SEEK_SET);
	unsigned char* pBuffer = new unsigned char[sizeof(MPQHashNode)*m_stHeader.hash_count];
	encrypt((unsigned char*)&m_hashTable,pBuffer,sizeof(MPQHashNode)*m_stHeader.hash_count);
	fwrite(pBuffer,sizeof(MPQHashNode),m_stHeader.hash_count,fptr);
	delete[] pBuffer;
}

void MPQPackage::write_block_table(FILE* fptr)
{
	if ( !fptr )
	{
		return ;
	}

	fseek(fptr,m_stHeader.block_table_offset,SEEK_SET);

	for ( unsigned int i = 0;i<m_blockTable.size(); ++i )
	{
		MPQBlock* pBlock = m_blockTable[i];
		unsigned char len = (unsigned char)pBlock->name.length();
		fwrite(&len,1,1,fptr);
		unsigned char* pBuffer = new unsigned char[len];
		encrypt((unsigned char*)pBlock->name.c_str(),pBuffer,len);
		fwrite(pBuffer,len,1,fptr);
		delete[] pBuffer;
		fwrite(&(pBlock->offset),sizeof(unsigned int),1,fptr);
		fwrite(&(pBlock->size),sizeof(unsigned int),1,fptr);
		fwrite(&(pBlock->uncompress_size),sizeof(unsigned int),1,fptr);
		fwrite(&(pBlock->flag),sizeof(unsigned int),1,fptr);
		fwrite(&(pBlock->md5_code),MPQ_MD5_CODE_LEN,1,fptr);
	}
}

bool MPQPackage::create(const char* file_name)
{
	m_fptr = fopen(file_name,"wb+");
	if ( !m_fptr )
	{
		return false;
	}

	m_IdentCode = RSHash(file_name);
	m_stHeader.header_size = sizeof(MPQHeader);
	m_stHeader.hash_table_offset = m_stHeader.header_size+m_stHeader.data_size;
	m_stHeader.block_table_offset = m_stHeader.hash_table_offset+sizeof(m_hashTable);
	m_stHeader.format_version1 = 0;
	m_stHeader.format_version2 = 0;

	write_header(m_fptr);
	write_hash_table(m_fptr);
	write_block_table(m_fptr);

	pthread_mutex_init(&m_readMutex, NULL);

	return true;
}

bool MPQPackage::open(const char* file_name)
{
	m_fptr = fopen(file_name,"rb+");
	if ( !m_fptr )
	{
		return false;
	}
	m_IdentCode = RSHash(file_name);
	read_header(m_fptr);
	if( m_stHeader.sign[0] != MPQ_HEADER_SIGN0 || m_stHeader.sign[1] != MPQ_HEADER_SIGN1 || 
		m_stHeader.sign[2] != MPQ_HEADER_SIGN2 || m_stHeader.sign[3] != MPQ_HEADER_SIGN3 )
	{
		fclose(m_fptr);
		m_fptr = NULL;
		return false;
	}

	read_hash_table(m_fptr);
	read_block_table(m_fptr);

	pthread_mutex_init(&m_readMutex, NULL);

	return true;
}

bool MPQPackage::backup(const char* file_name)
{
	if ( !m_IdentCode )
	{
		return false;
	}

	FILE* fp = fopen(file_name,"wb+");
	if ( !fp )
	{
		return false;
	}

	// 文件标识
	fwrite(&m_IdentCode,sizeof(m_IdentCode),1,fp);
	// 文件头
	write_header(fp);
	// 文件hash表
	write_hash_table(fp);
	// 文件块表
	write_block_table(fp);

	fclose(fp);

	return true;
}

bool MPQPackage::revert(const char* file_name,const char* file_revert)
{
	m_fptr = fopen(file_name,"rb+");
	if ( !m_fptr )
	{
		return false;
	}
	m_IdentCode = RSHash(file_name);
	read_header(m_fptr);
	if( m_stHeader.sign[0] != MPQ_HEADER_SIGN0 || m_stHeader.sign[1] != MPQ_HEADER_SIGN1 || 
		m_stHeader.sign[2] != MPQ_HEADER_SIGN2 || m_stHeader.sign[3] != MPQ_HEADER_SIGN3 )
	{
		fclose(m_fptr);
		m_fptr = NULL;
		return false;
	}

	FILE* fp = fopen(file_revert,"rb+");
	if ( !fp )
	{
		return false;
	}

	unsigned long identCode = 0;
	fread(&identCode,sizeof(identCode),1,fp);
	if ( m_IdentCode != identCode )
	{
		fclose(fp);
		return false;
	}

	// 文件头
	read_header(fp);
	// 文件hash表
	read_hash_table(fp);
	// 文件块表
	read_block_table(fp);

	fclose(fp);

	close();

	return true;
}

void MPQPackage::close(bool bSave)
{
	if ( m_fptr )
	{
		if ( bSave )
		{
			write_header(m_fptr);
			write_hash_table(m_fptr);
			write_block_table(m_fptr);
			fflush(m_fptr);
		}

		clear_block_table();
		fclose(m_fptr);
		m_fptr = NULL;

		pthread_mutex_destroy(&m_readMutex);
	}
}

void MPQPackage::encrypt(const unsigned char* in, unsigned char* out, int size)
{
	for(int i = 0; i < size; i++)
	{
		out[i] = in[i]^MPQ_ENCRYPT_CODE1;
		out[i] = out[i]^MPQ_ENCRYPT_CODE3;
	}
}

void MPQPackage::decrypt(const unsigned char* in, unsigned char* out, int size)
{
	for(int i = 0; i < size; i++)
	{
		out[i] = in[i]^MPQ_ENCRYPT_CODE3;
		out[i] = out[i]^MPQ_ENCRYPT_CODE1;
	}
}

bool MPQPackage::is_block_valid(unsigned int idx)
{
	if ( (idx != MPQ_INVALID) && (idx < m_blockTable.size()) )
	{
		return !m_blockTable[idx]->is_mark(MPQ_BLOCK_DELETE);
	}

	return false;
}

bool MPQPackage::is_hash_node_hashed(unsigned int idx)
{
	if( m_hashTable[idx].verify_code_a == MPQ_INVALID || 
		m_hashTable[idx].verify_code_b == MPQ_INVALID ){
			return false;
	}
	return true;
}

bool MPQPackage::is_hash_node_valid(unsigned int idx)
{
	return is_hash_node_valid(&m_hashTable[idx]);
}

bool MPQPackage::is_hash_node_valid(MPQHashNode* pNode)
{
	if(!pNode ||
		pNode->verify_code_a == MPQ_INVALID || 
		pNode->verify_code_b == MPQ_INVALID ||
		pNode->block_index == MPQ_INVALID ){
			return false;
	}
	return true;
}

MPQHashNode* MPQPackage::get_hash_node(unsigned int idx)
{
	idx = idx % MPQ_HASH_TABLE_SIZE;
	return &m_hashTable[idx];
}

MPQHashNode* MPQPackage::find_hash_node(unsigned int hash_code,unsigned int verify_a,unsigned int verify_b)
{
	if ( MPQ_INVALID == hash_code || MPQ_INVALID == verify_a || MPQ_INVALID == verify_b )
	{
		return NULL;
	}

	unsigned int idx = hash_code % MPQ_HASH_TABLE_SIZE;
	unsigned int nHash0 = idx;
	while ( true )
	{
		if (m_hashTable[idx].verify_code_a == verify_a && 
			m_hashTable[idx].verify_code_b == verify_b )
		{
			return &m_hashTable[idx];
		}
		else
		{
			idx = (idx + 1) % MPQ_HASH_TABLE_SIZE;
		}

		if (idx == nHash0)
			break;
	}

	return NULL;
}

MPQHashNode* MPQPackage::find_hash_node(const char* file_name)
{   
	unsigned long nHash0 = BlizzardHash(file_name);
	unsigned long nHashA = BlizzardHashA(file_name);
	unsigned long nHashB = BlizzardHashB(file_name);

	return find_hash_node(nHash0,nHashA,nHashB);
}

MPQHashNode* MPQPackage::get_hash_node_new_for_diff(unsigned int hash_code,unsigned int verify_a,unsigned int verify_b)
{
	hash_code = hash_code % MPQ_HASH_TABLE_SIZE;
	unsigned long nIndex = hash_code;
	while ( is_hash_node_hashed(nIndex) )
	{
		nIndex = (nIndex + 1) % MPQ_HASH_TABLE_SIZE;
		if (nIndex == hash_code)
		{
			return NULL;
		}
	}

	m_hashTable[nIndex].verify_code_a = verify_a;
	m_hashTable[nIndex].verify_code_b = verify_b;
	return &m_hashTable[nIndex];
}

MPQHashNode* MPQPackage::get_hash_node_new(unsigned int hash_code,unsigned int verify_a,unsigned int verify_b)
{
	hash_code = hash_code % MPQ_HASH_TABLE_SIZE;
	unsigned long nIndex = hash_code;
	while ( is_hash_node_valid(nIndex) )
	{
		nIndex = (nIndex + 1) % MPQ_HASH_TABLE_SIZE;
		if (nIndex == hash_code)
		{
			return NULL;
		}
	}

	m_hashTable[nIndex].verify_code_a = verify_a;
	m_hashTable[nIndex].verify_code_b = verify_b;
	return &m_hashTable[nIndex];
}

MPQHashNode* MPQPackage::get_hash_node_new(const char* file_name)
{
	unsigned long nHash0 = BlizzardHash(file_name);
	unsigned long nHashA = BlizzardHashA(file_name);
	unsigned long nHashB = BlizzardHashB(file_name);

	return get_hash_node_new(nHash0,nHashA,nHashB);
}

void MPQPackage::reset_hash_node(MPQHashNode* pNode)
{
	pNode->verify_code_a = MPQ_INVALID;
	pNode->verify_code_b = MPQ_INVALID;
	pNode->block_index = MPQ_INVALID;
}

MPQBlock* MPQPackage::get_block(const char* file_name)
{
	MPQHashNode* pNode = find_hash_node(file_name);
	return get_block(pNode);
}

MPQBlock* MPQPackage::get_block(MPQHashNode* pNode)
{
	if ( pNode && is_block_valid(pNode->block_index) )
	{
		return m_blockTable[pNode->block_index];
	}

	return NULL;
}

unsigned char* MPQPackage::read_block(MPQBlock* pBlock,unsigned int& size_read,unsigned int offset /* = 0 */,unsigned int size /* = 0 */)
{
	if ( !pBlock )
	{
		size_read = 0;
		return NULL;
	}

	unsigned char* pRet = nullptr;
	// 被压缩的数据块不支持部分读取
	if ( pBlock->is_mark(MPQ_BLOCK_COMPRESS) )
	{
		unsigned char* pData = (unsigned char*) malloc(pBlock->size);
		if ( !pData )
		{
			size_read = 0;
			return NULL;
		}

		pthread_mutex_lock(&m_readMutex);
		fseek(m_fptr,pBlock->offset,SEEK_SET);
		fread(pData,1,pBlock->size,m_fptr);
		pthread_mutex_unlock(&m_readMutex);

		uLongf uncompress_size = (uLongf)pBlock->uncompress_size;
		pRet = (unsigned char*) malloc(uncompress_size);

		if ( Z_OK != uncompress(pRet,&uncompress_size,pData,pBlock->size) )
		{
			free(pData);
			free(pRet);
			size_read = 0;
			return NULL;
		}
		
		size_read = uncompress_size;
		free(pData);
	}
	else
	{
		size = (size > 0 && size <= pBlock->size ) ? size : pBlock->size;

		unsigned char* pData = (unsigned char*) malloc(size);
		if ( !pData )
		{
			size_read = 0;
			return NULL;
		}

		pthread_mutex_lock(&m_readMutex);
		fseek(m_fptr,pBlock->offset+offset,SEEK_SET);
		size_read = fread(pData,1,size,m_fptr);
		pthread_mutex_unlock(&m_readMutex);

		pRet = pData;
	}

	if ( pBlock->is_mark(MPQ_BLOCK_ENCRYPT) )
	{
		decrypt(pRet,pRet,size_read);
	}

	return pRet;
}

unsigned char* MPQPackage::read_hash_node(MPQHashNode* pNode,unsigned int& size_read,unsigned int offset /* = 0 */,unsigned int size /* = 0 */)
{
	if ( !pNode )
	{
		size = 0;
		return NULL;
	}

	return read_block(get_block(pNode),size);
}

unsigned char* MPQPackage::read_file(const char* file_name,unsigned int& size_read,unsigned int offset /* = 0 */,unsigned int size /* = 0 */)
{
	if ( !m_fptr )
	{
		size_read = 0;
		return NULL;
	}

	return read_block(get_block(file_name),size_read,offset,size);
}

unsigned int MPQPackage::append_data(const unsigned char* pData,unsigned int size,bool bCompress,bool bEncrypt)
{
	if ( !m_fptr || !pData || size == 0 )
	{
		return MPQ_INVALID;
	}

	MPQBlock* pBlock = new MPQBlock;
	pBlock->uncompress_size = size;
	pBlock->size = size;
	pBlock->offset = m_stHeader.header_size+m_stHeader.data_size;

	if ( bEncrypt )
	{
		//pBlock->mark(MPQ_BLOCK_ENCRYPT);
	}

	if ( bCompress && size > MPQ_COMPRESS_SIZE)
	{
		uLongf compress_size = size;
		unsigned char* pBuf = new unsigned char[size];
		if ( Z_OK != compress((Bytef*)pBuf,&compress_size,pData,size) )
		{
			delete pBuf;
			delete pBlock;
			return MPQ_INVALID;
		}
		pBlock->size = compress_size;
		pBlock->mark(MPQ_BLOCK_COMPRESS);

		fseek(m_fptr,pBlock->offset,SEEK_SET);
		fwrite(pBuf,pBlock->size,1,m_fptr);

		delete pBuf;
	}
	else
	{
		fseek(m_fptr,pBlock->offset,SEEK_SET);
		fwrite(pData,pBlock->size,1,m_fptr);
	}

	m_stHeader.data_size += pBlock->size;
	m_stHeader.hash_table_offset = m_stHeader.header_size+m_stHeader.data_size;
	m_stHeader.block_table_offset = m_stHeader.hash_table_offset+sizeof(m_hashTable);

	m_blockTable.push_back(pBlock);
	m_stHeader.block_count = m_blockTable.size();

	return m_stHeader.block_count-1;
}

void MPQPackage::remove_data(MPQHashNode* pNode)
{
	if ( pNode )
	{
		remove_data(get_block(pNode));
		reset_hash_node(pNode);
	}
}

void MPQPackage::remove_data(MPQBlock* pBlock)
{
	if ( pBlock && !pBlock->is_mark(MPQ_BLOCK_DELETE) )
	{
		pBlock->mark(MPQ_BLOCK_DELETE);
		m_stHeader.hole_size += pBlock->size;
	}
}

void MPQPackage::remove_data(unsigned int idx)
{
	if( !is_block_valid(idx) )
	{
		return ;
	}
	
	remove_data(m_blockTable[idx]);
}

bool MPQPackage::append_file(const char* file_name,bool bCompress,bool bEncrypt)
{
	if ( !file_name )
	{
		return false;
	}

	FILE* fp = fopen(file_name,"rb");
	if ( !fp )
	{
		return false;
	}

	// md5 check code
	MD5 m;
	m.update(fp);

	fseek(fp,0,SEEK_END);
	size_t file_size = ftell(fp);
	m.update(&file_size,sizeof(unsigned int));

	unsigned char* pData = new unsigned char[file_size];
	if ( !pData )
	{
		fclose(fp);
		return false;
	}

	fseek(fp,0,SEEK_SET);
	fread(pData,1,file_size,fp);
	fclose(fp);

	MPQHashNode* pNode = get_hash_node_new(file_name);
	if ( !pNode )
	{
		// no space
		delete pData;
		return false;
	}

	unsigned int blockIndex = append_data(pData,file_size,bCompress,bEncrypt);
	if ( blockIndex == MPQ_INVALID )
	{
		reset_hash_node(pNode);
		delete pData;
		return false;
	}

	pNode->block_index = blockIndex;
	MPQBlock* pBlock = get_block(pNode);
	memcpy(pBlock->md5_code,m.result(),MPQ_MD5_CODE_LEN);
	pBlock->name = file_name;
	
	delete pData;
	return true;
}

void MPQPackage::remove_file(const char* file_name)
{
	MPQHashNode* pNode = find_hash_node(file_name);
	if ( pNode )
	{
		remove_data(pNode);

		write_header(m_fptr);
		write_hash_table(m_fptr);
		write_block_table(m_fptr);
	}
}

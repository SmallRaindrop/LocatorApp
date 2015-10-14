#ifndef __MPQPackage_h_
#define __MPQPackage_h_

#include <stdio.h>
#include <vector>
#include <string>
#include <pthread.h>
#include "../MD5.h"

using namespace std;

// 非法值的定义
#define MPQ_INVALID				-1
// MD5码长度定义
#define MPQ_MD5_CODE_LEN		16
// hash表长度定义
#define MPQ_HASH_TABLE_SIZE		0x4FFF
//  压缩要求的最小长度
#define MPQ_COMPRESS_SIZE		0x40

// 签名定义
#define MPQ_HEADER_SIGN0		'M'		// 0位签名
#define MPQ_HEADER_SIGN1		'P'		// 1位签名
#define MPQ_HEADER_SIGN2		'Q'		// 2位签名
#define MPQ_HEADER_SIGN3		'.'		// 3位签名

// MPQ包加密码
#define MPQ_ENCRYPT_CODE1		0x9E
#define MPQ_ENCRYPT_CODE2		0x37
#define MPQ_ENCRYPT_CODE3		0x79
#define MPQ_ENCRYPT_CODE4		0xB9

// MPQ包头结构定义
typedef struct _mpq_header_
{
	unsigned char	sign[4];			// 4位签名
	unsigned int	header_size;		// 文件头长度
	unsigned int	data_size;			// 包数据长度
	unsigned int	hole_size;			// 包内空洞长度
	unsigned short	format_version1;	// 版本协议号
	unsigned short	format_version2;	// 版本协议号
	unsigned int	hash_table_offset;	// 哈希表偏移位置
	unsigned int	block_table_offset;	// 数据块表偏移位置
	unsigned int	hash_count;			// 哈希表实际长度
	unsigned int	block_count;		// 块实际个数

	_mpq_header_(){
		sign[0] = MPQ_HEADER_SIGN0;
		sign[1] = MPQ_HEADER_SIGN1;
		sign[2] = MPQ_HEADER_SIGN2;
		sign[3] = MPQ_HEADER_SIGN3;

		header_size = 0;
		data_size = 0;
		hole_size = 0;
		format_version1 = 0;
		format_version2 = 0;
		hash_table_offset = 0;
		block_table_offset = 0;
		hash_count = MPQ_HASH_TABLE_SIZE;
		block_count = 0;
	}
}MPQHeader;

// 块标志位定义 块被加密
#define MPQ_BLOCK_ENCRYPT		0x01
// 块标志位定义 块被压缩
#define MPQ_BLOCK_COMPRESS		0x02
// 块标志位定义 块被删除
#define MPQ_BLOCK_DELETE		0x04

// 块结构定义
typedef struct _mpq_block_
{
	string			name;					// 块名 （文件名）
	unsigned int	offset;					// 数据偏移位置
	unsigned int	size;					// 数据压缩后长度
	unsigned int	uncompress_size;		// 数据实际长度
	unsigned int	flag;					// 块标志位
	unsigned char	md5_code[MPQ_MD5_CODE_LEN];// 块数据MD5加密认证码

	_mpq_block_(){
		name = "";
		offset = 0;
		size = 0;
		uncompress_size = 0;
		flag = 0;
		memset(md5_code,0,MPQ_MD5_CODE_LEN);
	}

	void mark(unsigned int f)
	{
		flag |= f;
	}

	bool is_mark(unsigned int f){
		return (flag & f) != 0;
	}

	void cl_mark(unsigned int f)
	{
		flag &= ~f;
	}
}MPQBlock;

// 哈希表节点结构定义
typedef struct _mpq_hash_node_
{
	unsigned int verify_code_a;			// 节点认证码A
	unsigned int verify_code_b;			// 节点认证码B
	unsigned int block_index;			// 节点的块索引值

	_mpq_hash_node_(){
		verify_code_a = MPQ_INVALID;
		verify_code_b = MPQ_INVALID;
		block_index = MPQ_INVALID;
	}

}MPQHashNode;

// MPQ包定义
class MPQPackage
{
public:
	MPQPackage();
	~MPQPackage();

public:
	/* Name		：is_block_valid
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 检查数据块是否有效
	 * Param	: idx 下标索引
	 * Return	: 有效返回true 否则false
	 */
	bool is_block_valid(unsigned int idx);

	/* Name		：is_hash_node_valid
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 哈希节点是否有效
	 * Param	: pNode 节点指针
	 * Return	: 有效返回true 否则false
	 */
	bool is_hash_node_valid(MPQHashNode* pNode);

	/* Name		：is_hash_node_valid
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 哈希节点是否有效
	 * Param	: idx 下标索引
	 * Return	: 有效返回true 否则false
	 */
	bool is_hash_node_valid(unsigned int idx);

	bool is_hash_node_hashed(unsigned int idx);

	/* Name		：get_hash_node
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取哈希表节点
	 * Param	: idx 下标索引
	 * Return	: MPQHashNode* 哈希节点指针
	 */
	MPQHashNode* get_hash_node(unsigned int idx);

	/* Name		：get_hash_node_new
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取一个未使用的哈希表节点
	 * Param	: hash_code 文件哈希值，verify_a，verify_b 认证码 A 和 B
	 * Return	: MPQHashNode* 哈希节点指针
	 */
	MPQHashNode*	get_hash_node_new(unsigned int hash_code,unsigned int verify_a,unsigned int verify_b);
	MPQHashNode*	get_hash_node_new_for_diff(unsigned int hash_code,unsigned int verify_a,unsigned int verify_b);

	/* Name		：get_hash_node_new
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取一个未使用的哈希表节点
	 * Param	: file_name 文件名
	 * Return	: MPQHashNode* 哈希节点指针
	 */
	MPQHashNode* get_hash_node_new(const char* file_name);

	/* Name		：find_hash_node
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 查找哈希表节点
	 * Param	: file_name 文件名
	 * Return	: MPQHashNode* 哈希节点指针
	 */
	MPQHashNode* find_hash_node(const char* file_name);

	/* Name		：find_hash_node
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 查找哈希表节点
	 * Param	: hash_code 文件哈希值，verify_a，verify_b 认证码 A 和 B
	 * Return	: MPQHashNode* 哈希节点指针
	 */
	MPQHashNode* find_hash_node(unsigned int hash_code,unsigned int verify_a,unsigned int verify_b);

	/* Name		：get_block
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取数据块
	 * Param	: file_name 文件名
	 * Return	: MPQBlock* 数据块指针
	 */
	MPQBlock* get_block(const char* file_name);

	/* Name		：get_block
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 获取数据块
	 * Param	: pNode 哈希表节点
	 * Return	: MPQBlock* 数据块指针
	 */
	MPQBlock* get_block(MPQHashNode* pNode);

	/************************************************************************/
	/* 创建一个mpq文件
	/************************************************************************/
	bool create(const char* file_name);

	/************************************************************************/
	/* 打开一个mpq文件
	/************************************************************************/
	bool open(const char* file_name);

	/************************************************************************/
	/* 备份一个mpq文件信息,file_name:备份文件名
	/************************************************************************/
	bool backup(const char* file_name);
	bool revert(const char* file_name,const char* file_revert);

	/************************************************************************/
	/* 关闭mpq文件
	/************************************************************************/
	void close(bool bSave = true);
	
	/************************************************************************/
	/* 从包中读取文件信息
	/************************************************************************/
	/* Name		：read_file
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 读取文件内容
	 * Param	: file_name 文件名，size_read 读取的实际长度，offset 读取偏移，size 指定读取的长度
	 * Return	: 数据指针
	 */
	unsigned char* read_file(const char* file_name,unsigned int& size_read,unsigned int offset = 0,unsigned int size = 0);

	/* Name		：read_node
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 读取哈希节点内容
	 * Param	: pNode 哈希节点指针，size_read 读取的实际长度，offset 读取偏移，size 指定读取的长度
	 * Return	: 数据指针
	 */
	unsigned char* read_hash_node(MPQHashNode* pNode,unsigned int& size_read,unsigned int offset = 0,unsigned int size = 0);

	/* Name		：read_block
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 读取数据块内容
	 * Param	: pBlock 数据块指针，size_read 读取的实际长度，offset 读取偏移，size 指定读取的长度
	 * Return	: 数据指针
	 */
	unsigned char* read_block(MPQBlock* pBlock,unsigned int& size_read,unsigned int offset = 0,unsigned int size = 0);

	/************************************************************************/
	/* 从包中追加文件信息
	/************************************************************************/
	bool append_file(const char* file_name,bool bCompress = false,bool bEncrypt = false);

	/************************************************************************/
	/* 从包中删除文件信息
	/************************************************************************/
	void remove_file(const char* file_name);

	/************************************************************************/
	/* 向mpq中追加数据，返回块索引，失败返回 MPQ_INVALID           
	/************************************************************************/
	unsigned int append_data(const unsigned char* pData,unsigned int size,bool bCompress = false,bool bEncrypt = false);

	/************************************************************************/
	/* 从包中删除文件数据信息 不是真正删除数据 只是给相应的数据块删除标志位置1
	/************************************************************************/
	void	remove_data(MPQHashNode* pNode);
	void	remove_data(MPQBlock* pBlock);
	void	remove_data(unsigned int idx);

public:
	/* Name		：encrypt
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 内容加密
	 * Param	: in 内容输入，out 加密输出 size 内容长度输入
	 * Return	: void
	 */
	void encrypt(const unsigned char* in, unsigned char* out, int size);

	/* Name		：encrypt
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 内容解密
	 * Param	: in 内容输入，out 解密输出 size 内容长度输入
	 * Return	: void
	 */
	void decrypt(const unsigned char* in, unsigned char* out, int size);

	/* Name		：reset_hash_node
	 * Author	：YueLiangYou
	 * Date		: 2015-07-02
	 * Desc		: 重置哈希节点
	 * Param	: pNode 节点指针
	 * Return	: void
	 */
	void reset_hash_node(MPQHashNode* pNode);

	/************************************************************************/
	/* 读写包头，哈希表和数据块表
	/************************************************************************/
	void read_header(FILE* fptr);
	void read_hash_table(FILE* fptr);
	void read_block_table(FILE* fptr);
	void write_header(FILE* fptr);
	void write_hash_table(FILE* fptr);
	void write_block_table(FILE* fptr);

	/************************************************************************/
	/* 清理数据块表
	/************************************************************************/
	void clear_block_table();

	/************************************************************************/
	/* 数据块表写入指定日志文件
	/************************************************************************/
	void format_block_table(const char* log);

protected:
	pthread_mutex_t m_readMutex;						// 读取互斥对象
	FILE*			m_fptr;								// 文件指针
	MPQHeader		m_stHeader;							// 包头
	MPQHashNode		m_hashTable[MPQ_HASH_TABLE_SIZE];	// 哈希表
	typedef vector<MPQBlock*> MPQBlockTable;			// 数据块表
	MPQBlockTable	m_blockTable;						// 数据库表
	unsigned long	m_IdentCode;						// 认证码 用于认证包备份
};

#endif
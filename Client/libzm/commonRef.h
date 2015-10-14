#ifndef __common_h_
#define __common_h_

//C头文件
#include <stdio.h>
#include <string.h>
#include <errno.h>
//C++头文件
#include <cctype>
#include <cmath>
//STL头文件
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

#ifndef _MSC_VER
typedef long long			__int64;
#endif // !_MSC_VER

typedef unsigned char		uchar;
typedef unsigned char		uint8;
typedef unsigned short		ushort;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

typedef signed char			int8;
typedef signed short		int16;
typedef signed int			int32;
typedef signed long long	int64;

class ByteArray
{
public:
	ByteArray(const unsigned char* buf,unsigned long len) : _bytes(buf),_size(len),_offset(0){}
	~ByteArray(){ /*if(!isNull()) delete _bytes;*/ }

	inline bool isNull() const{ return _bytes == NULL; }
	inline bool isEof() const { return isNull() || _offset >= _size; }

	inline const unsigned char*	bytes() const { return _bytes; }
	inline unsigned long	length() const { return _size; }
	inline unsigned long	offset() const { return _offset; }
	inline unsigned long	left() const { return _size > _offset?_size-_offset:0; }

	inline void				set(unsigned long val){ _offset = val; }
	inline void				move(unsigned long val){ _offset += val; }

	inline unsigned char read_byte()
	{
		unsigned char val = 0;
		read(&val,1);
		return val;
	}

	inline short read_short()
	{
		short val = 0;
		read(&val,2);
		return val;
	}

	inline int read_integer()
	{
		int val = 0;
		read(&val,4);
		return val;
	}

	inline float read_float()
	{
		float val = 0.0f;
		read(&val,sizeof(float));
		return val;
	}

	inline std::string read_string()
	{
		int len = read_byte();
		char* buf = new char[len+1];
		memset(buf,0,len+1);
		read(buf,len);
		std::string ret = buf;
		delete[] buf;
		return ret;
	}

	inline unsigned long read(void* buf,unsigned long len)
	{
		if ( isNull() || left()<len )
		{
			return 0;
		}

		memcpy(buf,_bytes+_offset,len);
		move(len);
		return len;
	}

private:
	const unsigned char*	_bytes;
	unsigned long	_offset;
	unsigned long	_size;
};

#endif
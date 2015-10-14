#ifndef __Net_h_
#define __Net_h_

#include "zlib.h"
#include <memory.h>

#define NetPacketMaxSize		1024*8
#define NetPacketCompressSize	128
#define NetPacketHeadSize		2

struct NetPacket
{
	char buffer[NetPacketMaxSize];

	NetPacket(){
		header(2);
	}
	inline unsigned short header(){ return *((unsigned short*)buffer);}
	inline void header(unsigned short h){ memcpy(buffer,&h,sizeof(unsigned short)); }

	inline unsigned short length(){ unsigned short h = header(); return h & ~(1<<15); }
	inline void length(unsigned short len){ 
		unsigned short h = header();
		h &= (1<<15);
		h |= (len & ~(1<<15));
		header(h);
	}
	inline unsigned short length_no_head(){ return length()-NetPacketHeadSize; }

	inline bool compressed(){ unsigned short h = header(); return (h >> 15) == 1; }
	inline void compressed(bool compr){ 
		unsigned short h = header();
		if (compr)
		{
			h |= (1<<15);
		}
		else
		{
			h &= ~(1<<15);
		}
		header(h);
	}

	inline int	capacity(){ return NetPacketMaxSize-length(); }
	
	inline int	copy(const char* buf,int size){ 
		int len = capacity()>size?size:capacity(); 
		memcpy(ptr(),buf,len);
		length(len+length()); 
		return len;
	}

	inline void clear(){ header(2); }

	inline char* ptr(){ return buffer+length(); }
	inline char* ptr_no_head(){ return buffer+NetPacketHeadSize; }

	inline bool is_need_compress(){return length() >= NetPacketCompressSize;}

	bool combine()	// 封包
	{
		if ( is_need_compress() )
		{
			char	buf[NetPacketMaxSize];
			uLongf	len = NetPacketMaxSize;
			if ( Z_OK != compress((Bytef*)buf,&len,(Bytef*)ptr_no_head(),length_no_head()) ) // 包头不压缩
			{
				return false;
			}
			clear();
			copy(buf,len);
			compressed(true);
		}
		
		return true;
	}

	bool parse()	// 解包
	{
		if ( compressed() )
		{
			char	buf[NetPacketMaxSize];
			uLongf	len = NetPacketMaxSize;
			if ( Z_OK != uncompress((Bytef*)buf,&len,(Bytef*)ptr_no_head(),length_no_head()) )
			{
				return false;
			}
			clear();
			copy(buf,len);
		}

		return true;
	}
};

#endif
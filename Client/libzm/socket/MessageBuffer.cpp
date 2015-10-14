
#include "MessageBuffer.h"
#include "../commonRef.h"

MessageBuffer::MessageBuffer(int len) : m_nLen(len),m_rdPtr(0),m_wrPtr(0)
{
	m_pBuf = new char[len];
	//memset(m_pBuf,0,len);
}

MessageBuffer::~MessageBuffer()
{
	if (m_pBuf)
	{
		delete[] m_pBuf;
		m_pBuf = NULL;
	}
}

int MessageBuffer::put(const char* buf,int size)
{
	if ( space() < size || size == 0 )
	{
		return 0;
	}

	if( size < wr_ptr_tail()-wr_ptr() )
	{
		memcpy(wr_ptr(),buf,size);
		wr_ptr_inc(size);
	}
	else
	{
		int len0 = wr_ptr_tail()-wr_ptr();
		int len1 = size-len0;
		memcpy(wr_ptr(),buf,len0);
		wr_ptr_inc(len0);
		memcpy(wr_ptr(),buf+len0,len1);
		wr_ptr_inc(len1);
	}

	return size;
}

int MessageBuffer::pop(char* buf,int size)
{
	if ( this->size() < size || size == 0)
	{
		return 0;
	}

	if ( size < rd_ptr_tail()-rd_ptr() )
	{
		memcpy(buf,rd_ptr(),size);
		rd_ptr_inc(size);
	}
	else	// split two seg
	{
		int len0 = rd_ptr_tail()-rd_ptr();
		int len1 = size-len0;
		memcpy(buf,rd_ptr(),len0);
		rd_ptr_inc(len0);
		memcpy(buf+len0,rd_ptr(),len1);
		rd_ptr_inc(len1);
	}

	return size;
}

int MessageBuffer::get(char* buf,int size)
{
	if ( this->size() < size || size == 0)
	{
		return 0;
	}

	if ( size < rd_ptr_tail()-rd_ptr() )
	{
		memcpy(buf,rd_ptr(),size);
	}
	else	// split two seg
	{
		int len0 = rd_ptr_tail()-rd_ptr();
		int len1 = size-len0;
		memcpy(buf,rd_ptr(),len0);
		memcpy(buf+len0,rd_ptr(len0),len1);
	}

	return size;
}
#ifndef __MessageBuffer_h_
#define __MessageBuffer_h_

#define MIN_(a,b)	a>b?b:a
#define MAX_(A,B)	A>B?A:B

class MessageBuffer
{
public:
	MessageBuffer(int len);
	~MessageBuffer();

public:	
	int put(const char* buf,int size);
	int pop(char* buf,int size);
	int get(char* buf,int size);

	inline int capacity(){ return m_nLen; }
	inline int size(){ return m_wrPtr-m_rdPtr; }
	inline int space(){ return capacity()-size();}
	
	inline char* ptr_head(){ return m_pBuf; }
	inline char* ptr_tail(){ return m_pBuf + capacity(); }
	inline char* wr_ptr(){ return m_pBuf + m_wrPtr%m_nLen; }
	inline char* rd_ptr(){ return m_pBuf + m_rdPtr%m_nLen; }
	inline char* wr_ptr(int n){ return m_pBuf + (m_wrPtr+n)%m_nLen; }
	inline char* rd_ptr(int n){ return m_pBuf + (m_rdPtr+n)%m_nLen; }

	inline void clear(){ m_rdPtr = m_wrPtr = 0; }

	inline void wr_ptr_inc(int n){ m_wrPtr+=n;}
	inline void rd_ptr_inc(int n){ m_rdPtr+=n;}

	inline char* wr_ptr_tail(){
		if ( rd_ptr() <= wr_ptr() && space()>0 )
		{
			return ptr_tail();
		}
		else
		{
			return rd_ptr();
		}
	}
	inline char* rd_ptr_tail(){
		if ( wr_ptr() <= rd_ptr() && size()>0 )
		{
			return ptr_tail();
		}
		else
		{
			return wr_ptr();
		}
	}

protected:
	int		m_wrPtr;
	int		m_rdPtr;
	int		m_nLen;
	char*	m_pBuf;
};

#endif
#include <assert.h>
#include "IOSocket.h"
#include "Net.h"
#include "../Log.h"

IOSocket::IOSocket(SOCKET sock) : m_nErrorCode(0),m_sock(sock),m_rMessages(1024*8),m_sMessages(1024*8),m_rBuffer(1024*1),m_sBuffer(1024*1)
{

}

IOSocket::~IOSocket()
{
	closesocket(m_sock);
}

void IOSocket::error()
{
	int err_code = SocketLastError;
	switch( err_code )
	{
	//case IOSocketError_EAGAIN:
	case IOSocketError_EWOULDBLOCK:	// 接收缓冲区为0或者发送缓冲区满（对方未接收数据）
	case IOSocketError_EINTR:
		break;
	case IOSocketError_ECONNABORTED:
	case IOSocketError_ECONNRESET:
	case IOSocketError_ENOTCONN:
		{
			error(err_code);
		}
		break;
	default:
		{
			error(err_code);
		}
		break;
	}
}

void IOSocket::fetch()
{
	int len = m_rBuffer.space();
	if ( len == 0 )
	{
		return ;
	}

	if ( len <= m_rBuffer.wr_ptr_tail()-m_rBuffer.wr_ptr() )
	{
		int ret = ::recv(m_sock,m_rBuffer.wr_ptr(),len,0);
		if ( ret > 0)
		{
			m_rBuffer.wr_ptr_inc(ret);
		}
		else
		{
			error();
		}	
	}
	else	// split two seg
	{
		int len0 = m_rBuffer.wr_ptr_tail()-m_rBuffer.wr_ptr();
		int len1 = len-len0;
		int ret0 = ::recv(m_sock,m_rBuffer.wr_ptr(),len0,0);
		if ( ret0 > 0)
		{
			m_rBuffer.wr_ptr_inc(ret0);
			if ( ret0 == len0 )
			{
				int ret1 = ::recv(m_sock,m_rBuffer.wr_ptr(),len1,0);
				if ( ret1 > 0)
				{
					m_rBuffer.wr_ptr_inc(ret1);
				}
				else
				{
					error();
				}
			}
		}
		else
		{
			error();
		}
	}
}

void IOSocket::recv_n()
{
	fetch();
	if ( m_rBuffer.size() <= 0 )
	{
		return ;
	}

	// modified by wenziyong, temperary, not support compress, should improve performance
	int copyLen = MIN_(m_rMessages.space(), m_rBuffer.size());
	if(copyLen <= 0)
		return;

	// copy data from m_rBuffer to m_rMessages
	if ( copyLen <= m_rBuffer.rd_ptr_tail()-m_rBuffer.rd_ptr() )
	{
		int ret = m_rMessages.put(m_rBuffer.rd_ptr(),copyLen);
		assert(ret == copyLen);
		m_rBuffer.rd_ptr_inc(copyLen);
	}
	else	//two parts
	{
		int len1 = m_rBuffer.rd_ptr_tail()-m_rBuffer.rd_ptr();
		int len2 = copyLen-len1;

		int ret1 = m_rMessages.put(m_rBuffer.rd_ptr(),len1);
		assert(ret1 == len1);
		m_rBuffer.rd_ptr_inc(len1);

		int ret2 = m_rMessages.put(m_rBuffer.rd_ptr(),len2);
		assert(ret2 == len2);
		m_rBuffer.rd_ptr_inc(len2);
	}
	//移动m_rBuffer读指什的位置

	/*
	NetPacket packet;
	unsigned short h = *((unsigned short*)m_rBuffer.rd_ptr());
	packet.header(h);
	if ( packet.length() > NetPacketMaxSize || packet.length() <= 0 )
	{
		m_rBuffer.clear();	// 错误包，需要清理缓冲区
		return;
	}
	if ( packet.length() > m_rBuffer.size())
	{
		return; // 半包返回
	}

	int len = m_rBuffer.pop(packet.buffer,packet.length());
	if ( len < packet.length() || !packet.parse() )
	{
		return; // 这里如果还取到半包，直接丢弃。
	}
	m_rMessages.put(packet.ptr_no_head(),packet.length_no_head());
	*/
}

void IOSocket::flush()
{
	int len = m_sBuffer.size();
	if ( len == 0 )
	{
		return;
	}
	if ( len <= m_sBuffer.rd_ptr_tail()-m_sBuffer.rd_ptr() )
	{
		int ret = ::send(m_sock,m_sBuffer.rd_ptr(),len,0);
		if ( ret > 0)
		{
			m_sBuffer.rd_ptr_inc(ret);
		}
		else
		{
			error();
		}
	}
	else	// split two seg
	{
		int len0 = m_sBuffer.rd_ptr_tail()-m_sBuffer.rd_ptr();
		int len1 = len-len0;
		int ret0 = ::send(m_sock,m_sBuffer.rd_ptr(),len0,0);
		if ( ret0 > 0)
		{
			m_sBuffer.rd_ptr_inc(ret0);
			if ( ret0 == len0 )
			{
				int ret1 = ::send(m_sock,m_sBuffer.rd_ptr(),len1,0);
				if ( ret1 > 0)
				{
					m_sBuffer.rd_ptr_inc(ret1);
				}
				else
				{
					error();
				}
			}
		}
		else
		{
			error();
		}
	}
}

void IOSocket::send_n()
{
	// modified by wenziyong,对于客户端发送给服务器的包不进行压缩，直接把
	int needSendLen = m_sMessages.size();
	if(needSendLen > 0)
	{
		if ( m_sBuffer.space()<needSendLen)
		{
			flush();
		}

		// 计算能发多少数据
		int willSendLen = MIN_(m_sBuffer.space(), needSendLen);
		if(willSendLen > 0 )
		{
			// 把数据拷贝发送buff
			if ( willSendLen <= m_sMessages.rd_ptr_tail()-m_sMessages.rd_ptr() )
			{
				int ret = m_sBuffer.put(m_sMessages.rd_ptr(),willSendLen);
				assert(ret == willSendLen);
				m_sMessages.rd_ptr_inc(willSendLen);
			}
			else	//two parts
			{
				int len1 = m_sMessages.rd_ptr_tail()-m_sMessages.rd_ptr();
				int len2 = willSendLen-len1;

				int ret1 = m_sBuffer.put(m_sMessages.rd_ptr(),len1);
				assert(ret1 == len1);
				m_sMessages.rd_ptr_inc(len1);

				int ret2 = m_sBuffer.put(m_sMessages.ptr_head(),len2);
				assert(ret2 == len2);
				m_sMessages.rd_ptr_inc(len2);
			}
			flush();
		}

	}
	/*
	NetPacket packet;
	
	// 将消息队列的数据封包
	int len = MIN(packet.capacity(),m_sMessages.size());//maybe compress half msg
	if ( m_sMessages.rd_ptr()+len <= m_sMessages.ptr_tail() )
	{
		len = packet.copy(m_sMessages.rd_ptr(),len);
	}
	else	// split two seg
	{
		int len0 = m_sMessages.ptr_tail()-m_sMessages.rd_ptr();
		int len1 = len-len0;
		len = packet.copy(m_sMessages.rd_ptr(),len0);
		len +=packet.copy(m_sMessages.ptr_head(),len1);
	}
	if ( len > 0 && packet.combine() )
	{
		m_sMessages.rd_ptr(len);

		if ( m_sBuffer.space()<packet.length())
		{
			flush();
		}
		// 将封好的网络包放入发送缓冲区，如果发送缓冲区放不下，抛异常
		int ret = m_sBuffer.put(packet.buffer,packet.length());
		if ( ret < packet.length() )
		{
			//error(2);
			return ;
		}

		flush();
	}
	*/
}

int	IOSocket::recv(char* buf,int size)
{
	if ( m_rMessages.size() < size )
	{
		recv_n();
	}
	return m_rMessages.pop(buf,size);
}
int	IOSocket::send(const char* buf,int size)
{
	if ( m_sMessages.space() < size )
	{
		send_n();
	}

	return m_sMessages.put(buf,size);
}

int IOSocket::recv_pkt(stNetMsg& msg)
{
	if ( m_rMessages.size() < sizeof(stNetMsgHead) )
	{
		recv_n();
	}

	// 检查包头
	stNetMsgHead head;
	if ( 0 == m_rMessages.get((char*)&head,sizeof(stNetMsgHead)) )
	{
		return 0;
	}

	if ( head._size <= 0 || head._size > NetMsg_Max_Size )
	{
		LOGE("read invalid msg header{size=%u}",head._size);
		error(IOSocketError_PACKET);
		return 0;
	}

	if( 0 == recv(msg.ptr(),head._size) )
	{
		return 0;
	}

	return msg.size();
}

int	IOSocket::send_pkt(stNetMsg& msg)
{
	return send(msg.ptr(),msg.size());
}
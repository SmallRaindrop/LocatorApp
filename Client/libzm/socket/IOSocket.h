#ifndef __IOSocket_h_
#define __IOSocket_h_

#include "MessageBuffer.h"
#include "NetMsg.h"
#include "SocketDefine.h"

class IOSocket
{
public:
	IOSocket(SOCKET sock);
	~IOSocket();

	int		recv_pkt(stNetMsg& msg);
	int 	send_pkt(stNetMsg& msg);

	void	clear_recv(){ m_rMessages.clear(); }
	void	clear_send(){ m_sMessages.clear(); }

	int		recv(char* buf,int size);
	int		send(const char* buf,int size);

	// 将发送缓冲区数据发送到网络层
	void	send_n();
	// 从网络层接收数据到接收缓冲区
	void	recv_n();

	inline int	getErrorCode(){ return m_nErrorCode; }
	inline bool	hasErrorCode(){ return getErrorCode() != 0; }

protected:
	void	flush();
	void	fetch();
	int		get_addr(const char* host,int port,sockaddr_in* addr);
	void	error(int code){ m_nErrorCode = code; }
	void	error();

protected:
	SOCKET			m_sock;
	int				m_nErrorCode;

	MessageBuffer	m_rMessages;
	MessageBuffer	m_sMessages;

	MessageBuffer	m_rBuffer;
	MessageBuffer	m_sBuffer;
};

#endif
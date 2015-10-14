#ifndef __ClientSocket_h_
#define __ClientSocket_h_

#include "IOSocket.h"

class CClientSocket
{
public:
	CClientSocket();
	~CClientSocket();

public:
	IOSocket*	connect(const char* sIP,int port);
	int			get_addr(const char* host,int port,sockaddr_in* addr);
};

#endif
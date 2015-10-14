
#include "ClientSocket.h"
#include "../Log.h"

CClientSocket::CClientSocket()
{

}

CClientSocket::~CClientSocket()
{

}

int CClientSocket::get_addr(const char* host,int port,sockaddr_in* addr)
{
	addrinfo hints;
	addrinfo *aiList = NULL;
	char serviceName[64];
	int r = 0;
	//
	sprintf(serviceName,"%d",port);
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	r = getaddrinfo(host, serviceName, &hints, &aiList);
	if (r == 0) {
		memcpy(addr, aiList->ai_addr, sizeof(sockaddr_in));
		freeaddrinfo(aiList);
	}
	return r;
}

IOSocket* CClientSocket::connect(const char* sIP,int port)
{
	SOCKET sock_s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if ( sock_s == INVALID_SOCKET ){
		return NULL;
	}
	
	sockaddr_in addr;
	if( 0 != get_addr(sIP, port, &addr))
		return NULL;

	int ret = ::connect(sock_s, (sockaddr*)&addr, sizeof(sockaddr_in));
	if ( ret == SOCKET_ERROR ) {
		LOGE("connect to ip:%s port:%d error.\n", sIP, port );
		return NULL;
	}

	int iMode = 1; //0£º×èÈû
	ioctlsocket(sock_s,FIONBIO, (u_long *) &iMode);//·Ç×èÈûÉèÖÃ

	LOGI("connect to ip:%s port:%d succ.\n", sIP, port );

	return new IOSocket(sock_s);
}
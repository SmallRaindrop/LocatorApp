#ifndef __SocketDefine_h_
#define __SocketDefine_h_

#ifdef WIN32
#include <WS2tcpip.h>
#include <winsock2.h>
#define SocketLastError			WSAGetLastError()

#define IOSocketError_PACKET		55555
#define IOSocketError_EAGAIN		11
#define IOSocketError_EWOULDBLOCK	WSAEWOULDBLOCK
#define IOSocketError_EINTR			4
#define IOSocketError_ECONNABORTED	WSAECONNABORTED
#define IOSocketError_ECONNRESET	WSAECONNRESET
#define IOSocketError_ENOTCONN		WSAENOTCONN

#else

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <errno.h>

typedef int					SOCKET;
#define INVALID_SOCKET	(SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#define SocketLastError		errno
#define ioctlsocket			ioctl
#define closesocket			close

#define IOSocketError_PACKET		55555
#define IOSocketError_EAGAIN		11
#define IOSocketError_EWOULDBLOCK	EWOULDBLOCK
#define IOSocketError_EINTR			EINTR
#define IOSocketError_ECONNABORTED	ECONNABORTED
#define IOSocketError_ECONNRESET	ECONNRESET
#define IOSocketError_ENOTCONN		ENOTCONN

#endif

#endif // __SocketDefine_h_
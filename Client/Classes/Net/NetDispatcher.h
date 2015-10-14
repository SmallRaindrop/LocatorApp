#ifndef __NetDispatcher_h_
#define __NetDispatcher_h_

#include "GameDef.h"
#include "Singleton.h"
#include "socket/IOSocket.h"

enum NetLine{
	NetLine_None = 0,
	NetLine_Login,
	NetLine_Game,
};

// ÍøÂçÊÕ·¢Æ÷
//class NetDispatcher :public Ref, public CSingleton<NetDispatcher>
class NetDispatcher :public Singleton_Auto<NetDispatcher>
{
public:
	NetDispatcher();
	~NetDispatcher();

	bool NetStart();
	void NetEnd();

	void update(float dt);

	
	bool Connect(string ip,int port);
	void DisConnect();
	void Clear();

	inline bool			IsConnect(){ return m_pSocket? (m_pSocket->hasErrorCode() == false) : false; }
	inline int			GetLine(){ return m_nLine; }
	inline void			SetLine(int line){ m_nLine = line; }
	inline IOSocket*	GetIOSocket(){ return m_pSocket; }
	inline bool			IsLocked(){ return m_bLock; }
	inline void			Lock(){ m_bLock = true; }
	inline void			Unlock(){ m_bLock = false; }

	int		GetPacket();
	bool	ProcessMsg(stNetMsg& msg);
	void	HeartBeat();

private:
	int						m_nLine;
	IOSocket*				m_pSocket;

	std::deque<stNetMsg>	m_MsgQueue;
	bool					m_bLock;
};

#define gNetDispatcher	NetDispatcher::Instance()
#define gNetSocket		NetDispatcher::Instance()->GetIOSocket()

#endif
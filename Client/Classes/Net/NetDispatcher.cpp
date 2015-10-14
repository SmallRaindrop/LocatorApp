#include "NetDispatcher.h"
#include "socket/ClientSocket.h"
#include "pk_others.h"

NetDispatcher::NetDispatcher() : m_pSocket(NULL),m_bLock(false)
{
	NetStart();
}

NetDispatcher::~NetDispatcher()
{
	NetEnd();
}

bool NetDispatcher::NetStart()
{
#ifdef _WIN32
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	if ( WSAStartup(version, &wsaData) ) {	
		return false;
	}
#endif
	m_MsgQueue.clear();

	return true;
}

void NetDispatcher::NetEnd()
{
	DisConnect();
	m_MsgQueue.clear();
}

void NetDispatcher::update(float dt)
{
	static const int MAX_MSG_ONCE = 1;
	while ( IsConnect() )
	{
		stNetMsg msg;
		if ( m_pSocket->recv_pkt(msg) > 0 )
		{
			m_MsgQueue.push_back(msg);			
		}
		else
		{
			break;
		}
	}

	int i = 0;

	while( IsConnect() && m_MsgQueue.size()>0 && !IsLocked() )
	{
		stNetMsg& msg = m_MsgQueue.front();
		TIME_COST_BEGIN;
		if ( !ProcessMsg(msg) )
		{
			//CCLog("connect server failed! addr[%s],port[%d]",m_sAddr,m_nPort);
		}
		__String str;
		str.initWithFormat("msg:%d",msg.h._cmd);
		TIME_COST_LOG_IF(str.getCString(),2);
		if ( m_MsgQueue.size() > 0 )
		{
			m_MsgQueue.pop_front();
		}
		
		if (i++ >= MAX_MSG_ONCE)
		{
			break;
		}
	}

	// prosable closed.
	if ( IsConnect() )
	{
		// heart beat check
		if ( GetLine() == NetLine_Game )
		{
			static const int HEART_BEAT_TIMER = 10000;
			static float time_past = 0.0f;
			time_past += (dt*1000);
			if ( (int)time_past > HEART_BEAT_TIMER )
			{
				HeartBeat();
				time_past = 0.0f;
			}
		}
		// send data to net
		m_pSocket->send_n();
	}
	else
	{
        if (m_pSocket)
        {
            //CCLog("socket error code is %d",m_pSocket->getErrorCode());
        }
	}
}

bool NetDispatcher::Connect(string ip,int port)
{
	CCLOG("connect to ip:%s,port:%d.",ip.c_str(),port);
	CClientSocket client;
	m_pSocket = client.connect(ip.c_str(),port);
	if ( !m_pSocket )
	{
		LOGE("connect to ip:%s,port:%d.",ip.c_str(),port);
		return false;
	}
	LOGI("connect to ip:%s,port:%d ok.",ip.c_str(),port);
	return true;
}

void NetDispatcher::DisConnect()
{
	if(m_pSocket)
	{
		m_pSocket->send_n();
	}
	Clear();
	if ( m_pSocket )
	{
		delete m_pSocket;
		m_pSocket = NULL;
	}
}

bool NetDispatcher::ProcessMsg(stNetMsg& msg)
{
	extern bool DoMessage(stNetMsg& msg);
	return DoMessage(msg);
}

void NetDispatcher::Clear()
{
	if ( m_pSocket )
	{
		m_pSocket->clear_recv();
	}
	
	m_MsgQueue.clear();
}

void NetDispatcher::HeartBeat()
{
 	pk::C2GS_HeartBeat cmd;
 	cmd.Send(gNetSocket);
}

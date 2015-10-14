#ifndef __MessageCenter_h_
#define __MessageCenter_h_
/************************************************************************/
/* 消息中心   系统消息提示中心                                          */
/************************************************************************/

#include "GameDef.h"
#include "Singleton.h"

enum SystemMessageType
{
	SystemMessage_Msg,			// 系统消息 聊天框内显示的提示
	SystemMessage_Notice1,		// 公告 上方滚动的提示
	SystemMessage_Notice2,		// 公告 另外一种表现
	SystemMessage_Prompt,		// 系统提示，屏幕中间提示
	SystemMessage_Normal,		// 左下角提示，获得经验，获得金币，一会就消失
	SystemMessage_CompMN,		// 组合提示（SystemMessage_Msg + SystemMessage_Notice1）
	SystemMessage_CompMP,		// 组合提示（SystemMessage_Msg + SystemMessage_Prompt）
	SystemMessage_Alert,		// 弹出提示框提示
	SystemMessage_Mail,			// 邮件提示
	SystemMessage_Team,			// 组队提示
	SystemMessage_Trade,		// 交易提示
	SystemMessage_Chat,			// 好友聊天提示
	SystemMessage_Max,
};

#define Max_Message_Len		500

class SystemMessageCache
{
public:
	SystemMessageCache(int len = 100) : m_nLength(len) {}
	~SystemMessageCache(){}

	inline void push(const string& val){
		m_Msgs.push_back(val);
		while ( (int)m_Msgs.size() > m_nLength )
		{
			pop();
		}
	}

	inline string pop(){
		string ret = m_Msgs.front();
		m_Msgs.erase(m_Msgs.begin());
		return ret;
	}

	inline void clear(){
		m_Msgs.clear();
	}

	inline void remove(const string& str)
	{
		list<string>::iterator it = find(m_Msgs.begin(), m_Msgs.end(), str);
		if (it != m_Msgs.end())
		{
			m_Msgs.erase(it);
		}
	}

	inline bool has(const string& str){
		return (find(m_Msgs.begin(), m_Msgs.end(), str) != m_Msgs.end());
	}

	inline int length(){
		return (int)m_Msgs.size();
	}

	inline void length(int len){
		m_nLength = len;
	}

private:
	list<string>	m_Msgs;
	int				m_nLength;
};

class MessageCenter : public Singleton_Auto<MessageCenter>
{
public:
	MessageCenter();
	~MessageCenter();

	inline SystemMessageCache& GetMessageCache(SystemMessageType type){ return m_Cache[type]; }

public:
	void SystemMessage(SystemMessageType type,const char* format, ... );
	void SystemMessage(SystemMessageType type,const string& msg);
	void SystemMessage(int nCode, ...);
	void SystemMessage(int nCode, vector<string>& vtrArgs);

	bool HasMessage(SystemMessageType type, const string& msg);
	void RemoveMessage(SystemMessageType type, const string& msg);
protected:
	SystemMessageCache m_Cache[SystemMessage_Max];
};

SystemMessageType FormatMsgByArgFromVector(int nCode, vector<string>& vtrArgs, string &strMsg);

#define gMessageCenter				MessageCenter::Instance()
#define MessagePrompt(Msg, ...)		gMessageCenter->SystemMessage(SystemMessage_Prompt,Msg,##__VA_ARGS__)
#define MessageNormal(Msg, ...)		gMessageCenter->SystemMessage(SystemMessage_Normal,Msg,##__VA_ARGS__)
#define MessageSystem(Msg, ...)		gMessageCenter->SystemMessage(SystemMessage_Msg,Msg,##__VA_ARGS__)
#define MessageNotice1(Msg, ...)	gMessageCenter->SystemMessage(SystemMessage_Notice1,Msg,##__VA_ARGS__)
#define MessageNotice2(Msg, ...)	gMessageCenter->SystemMessage(SystemMessage_Notice2,Msg,##__VA_ARGS__)
#define MessageAlert(Msg, ...)		gMessageCenter->SystemMessage(SystemMessage_Alert,Msg,##__VA_ARGS__)
#define MessageMail(Msg, ...)		gMessageCenter->SystemMessage(SystemMessage_Mail,Msg,##__VA_ARGS__)
#define MessageTeam(Msg, ...)		gMessageCenter->SystemMessage(SystemMessage_Team,Msg,##__VA_ARGS__)
#define MessageChat(Msg, ...)		gMessageCenter->SystemMessage(SystemMessage_Chat,Msg,##__VA_ARGS__)
#define MessageTrade(Msg, ...)		gMessageCenter->SystemMessage(SystemMessage_Trade,Msg,##__VA_ARGS__)

#endif		// __MessageCenter_h_
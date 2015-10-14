#include "CommonDef.h"
#include "MessageCenter.h"
#include "GameDataManager.h"
#include "GameScene/BeginnerGuide.h"
#include "Hero.h"

MessageCenter::MessageCenter()
{
	GetMessageCache(SystemMessage_Trade).length(6);
}

MessageCenter::~MessageCenter()
{

}

void MessageCenter::RemoveMessage(SystemMessageType type, const string& msg)
{
	GetMessageCache(type).remove(msg);
}

bool MessageCenter::HasMessage(SystemMessageType type, const string& msg)
{
	return GetMessageCache(type).has(msg);
}

void MessageCenter::SystemMessage(SystemMessageType type,const string& msg)
{
	GetMessageCache(type).push(msg);
}

void MessageCenter::SystemMessage(SystemMessageType type,const char* format, ... )
{
	va_list l;
	char strOut[Max_Message_Len] = {0};
	va_start(l,format);

	vsnprintf(strOut, sizeof(strOut),format, l);

	string msg = strOut;
	SystemMessage(SystemMessageType(type),msg);
}

void MessageCenter::SystemMessage(int nCode, ...)
{
	ChatCfg *pData = ChatData.get(nCode);
	if (pData)
	{
		va_list l;
		va_start(l, nCode);

		char strOut[Max_Message_Len] = {};
		vsnprintf(strOut, sizeof(strOut), pData->content.c_str(), l);

		string msg = strOut;
		SystemMessage(SystemMessageType(pData->displaytype),msg);
	}
}

SystemMessageType FormatMsgByArgFromVector(int nCode, vector<string>& vtrArgs, string &strMsg)
{
	ChatCfg *pData = ChatData.get(nCode);
	char strOut[Max_Message_Len] = {};
	if (pData)
	{
		switch (vtrArgs.size())
		{
		case 0:
			sprintf(strOut, "%s",pData->content.c_str());
			break;
		case 1:
			sprintf(strOut, pData->content.c_str(), vtrArgs[0].c_str());
			break;
		case 2:
			sprintf(strOut, pData->content.c_str(), vtrArgs[0].c_str(), vtrArgs[1].c_str());
			break;
		case 3:
			sprintf(strOut, pData->content.c_str(), vtrArgs[0].c_str(), vtrArgs[1].c_str(), vtrArgs[2].c_str());
			break;
		}

		strMsg = strOut;
		return SystemMessageType(pData->displaytype);
	}

	return SystemMessage_Max;
}

void MessageCenter::SystemMessage(int nCode, vector<string>& vtrArgs)
{
	string strMsg;
	SystemMessageType type = FormatMsgByArgFromVector(nCode, vtrArgs, strMsg);

	if (type != SystemMessage_Max)
		SystemMessage(type, strMsg);
}

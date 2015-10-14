#include "Log.h"
#include <stdarg.h>
#include <time.h>

zmLog::zmLog() : m_fptr(NULL)
{

}

zmLog::~zmLog()
{
	Close();
}

const char* zmLog::GetTypeString(LogType type)
{
	static const char type_string[LogType_Max][16] = 
	{
		"info",
		"warning",
		"system",
		"error",
		"debug",
	};

	return type_string[type];
}

bool zmLog::Open(const char* file)
{
	if ( IsOpen() )
	{
		Close();
	}

	m_fptr = fopen(file,"wt+");

	if ( m_fptr )
	{
		Log(LogType_System,"==========Log System Started.==========");
		return true;
	}
	
	return false;
}

void zmLog::Close()
{
	if ( m_fptr )
	{
		Log(LogType_System,"==========Log System Closed.==========");

		fflush(m_fptr);
		fclose(m_fptr);
		m_fptr = NULL;
	}
}

void zmLog::Log(LogType type,const char* format, ... )
{
	
	if ( !IsOpen() )
	{
		Open("zmGame.log") ;
	}
	
	va_list l;
	va_start(l,format);
	char buf[2048] = {0};
	vsnprintf(buf,2048,format,l);
	va_end(l);

	time_t tnow = time(NULL);
	tm* tmtime = localtime(&tnow);
	char strtime[32] = "";
	strftime(strtime, sizeof(strtime), "%Y/%m/%d %H:%M:%S", tmtime);  

	m_mutext.lock();
	// 日志输出格式：[时间][Type] 日志内容
	fprintf(m_fptr,"[%s][%s] %s\r\n",strtime,GetTypeString(type),buf);
	fflush(m_fptr);
	m_mutext.unlock();
}
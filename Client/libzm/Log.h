#ifndef __zm_Log_h_
#define __zm_Log_h_

#include "Singleton.h"
#include <mutex>

enum LogType
{
	LogType_Info,		// 输出信息
	LogType_Warnning,	// 提醒
	LogType_System,		// 系统
	LogType_Error,		// 错误
	LogType_Debug,		// 调试
	LogType_Max,
};

// 日志输出格式：[时间][Type] 日志内容
// 例如：
//[2015/05/09 12:15:08][debug] 日志信息我i垃圾的房价
//[2015/05/09 12:15:08][warnning] ... 日志信息我i垃圾的房价 ...
//[2015/05/09 12:15:08][error] 日志信息我i垃圾的房价
//[2015/05/09 12:15:08][info] ... 日志信息我i垃圾的房价 ...
//[2015/05/09 12:15:08][info] 日志信息我i垃圾的房价
//[2015/05/09 12:15:08][warnning] ... 日志信息我i垃圾的房价 ...

class zmLog : public Singleton_Auto<zmLog>
{
public:
	zmLog();
	~zmLog();

	bool Open(const char* file);
	void Close();
	void Log(LogType type,const char* format, ... );
	const char* GetTypeString(LogType type);
	inline bool IsOpen(){ return m_fptr != NULL; }

protected:
	FILE* m_fptr;
	std::mutex m_mutext;
};

#define gLog zmLog::Instance()
#define LOGI(FMT, ...)	gLog->Log(LogType_Info,FMT,##__VA_ARGS__)
#define LOGW(FMT, ...)	gLog->Log(LogType_Warnning,FMT,##__VA_ARGS__)
#define LOGS(FMT, ...)	gLog->Log(LogType_System,FMT,##__VA_ARGS__)
#define LOGE(FMT, ...)	gLog->Log(LogType_Error,FMT,##__VA_ARGS__)
#define LOGD(FMT, ...)	gLog->Log(LogType_Debug,FMT,##__VA_ARGS__)

#endif
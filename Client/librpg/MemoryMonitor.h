#ifndef __MemoryMonitor_h_
#define __MemoryMonitor_h_

#include "base/CCPlatformConfig.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../libzm/Singleton.h"
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "../libzm/Singleton.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <pthread.h>
#endif

class MemoryMonitor : public Singleton_Auto<MemoryMonitor>
{
public:
	MemoryMonitor();
	~MemoryMonitor();

	bool isMemoryWarnning();
	bool isMemoryEmergence();

	double usedMemory();
	double freeMemory();
	double totlMemory();

	bool initialize();
	void releaseSgl();

	void clearMemory();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	volatile double m_usedMemory;
	volatile double m_freeMemory;
	volatile double m_totlMemory;

	volatile bool m_exit;
	pthread_t s_queryThread;

	void queryMemoryState();
	unsigned long queryMemorySelf();

	static void* threadProcedure(void* data);

	int killProcesses();
#endif
};

#define gMemoryMonitor MemoryMonitor::Instance()

#endif
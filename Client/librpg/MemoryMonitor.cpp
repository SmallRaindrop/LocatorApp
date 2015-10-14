#include "GameDef.h"
#include "MemoryMonitor.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include <mach/mach.h>
#include <sys/sysctl.h>
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <Windows.h>
#include <psapi.h>
#pragma comment(lib,"psapi.lib")
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/JniHelper.h"
#include <android/log.h>
#include <jni.h>
#include <unistd.h>
#endif
//
//#define P_G_SZ 20
//
//typedef struct proc_t {
//	// 1st 16 bytes
//	int
//		tid,		// (special)       task id, the POSIX thread ID (see also: tgid)
//		ppid;		// stat,status     pid of parent process
//	unsigned
//		pcpu;           // stat (special)  %CPU usage (is not filled in by readproc!!!)
//	char
//		state,		// stat,status     single-char code for process state (S=sleeping)
//		pad_1,		// n/a             padding
//		pad_2,		// n/a             padding
//		pad_3;		// n/a             padding
//	// 2nd 16 bytes
//	unsigned long long
//		utime,		// stat            user-mode CPU time accumulated by process
//		stime,		// stat            kernel-mode CPU time accumulated by process
//		// and so on...
//		cutime,		// stat            cumulative utime of process and reaped children
//		cstime,		// stat            cumulative stime of process and reaped children
//		start_time;	// stat            start time of process -- seconds since 1-1-70
//#ifdef SIGNAL_STRING
//	char
//		// Linux 2.1.7x and up have 64 signals. Allow 64, plus '\0' and padding.
//		signal[18],	// status          mask of pending signals, per-task for readtask() but per-proc for readproc()
//		blocked[18],	// status          mask of blocked signals
//		sigignore[18],	// status          mask of ignored signals
//		sigcatch[18],	// status          mask of caught  signals
//		_sigpnd[18];	// status          mask of PER TASK pending signals
//#else
//	long long
//		// Linux 2.1.7x and up have 64 signals.
//		signal,		// status          mask of pending signals, per-task for readtask() but per-proc for readproc()
//		blocked,	// status          mask of blocked signals
//		sigignore,	// status          mask of ignored signals
//		sigcatch,	// status          mask of caught  signals
//		_sigpnd;	// status          mask of PER TASK pending signals
//#endif
//	unsigned KLONG
//		start_code,	// stat            address of beginning of code segment
//		end_code,	// stat            address of end of code segment
//		start_stack,	// stat            address of the bottom of stack for the process
//		kstk_esp,	// stat            kernel stack pointer
//		kstk_eip,	// stat            kernel instruction pointer
//		wchan;		// stat (special)  address of kernel wait channel proc is sleeping in
//	long
//		priority,	// stat            kernel scheduling priority
//		nice,		// stat            standard unix nice level of process
//		rss,		// stat            resident set size from /proc/#/stat (pages)
//		alarm,		// stat            ?
//		// the next 7 members come from /proc/#/statm
//		size,		// statm           total # of pages of memory
//		resident,	// statm           number of resident set (non-swapped) pages (4k)
//		share,		// statm           number of pages of shared (mmap'd) memory
//		trs,		// statm           text resident set size
//		lrs,		// statm           shared-lib resident set size
//		drs,		// statm           data resident set size
//		dt;		// statm           dirty pages
//	unsigned long
//		vm_size,        // status          same as vsize in kb
//		vm_lock,        // status          locked pages in kb
//		vm_rss,         // status          same as rss in kb
//		vm_data,        // status          data size
//		vm_stack,       // status          stack size
//		vm_exe,         // status          executable size
//		vm_lib,         // status          library size (all pages, not just used ones)
//		rtprio,		// stat            real-time priority
//		sched,		// stat            scheduling class
//		vsize,		// stat            number of pages of virtual memory ...
//		rss_rlim,	// stat            resident set size limit?
//		flags,		// stat            kernel flags for the process
//		min_flt,	// stat            number of minor page faults since process start
//		maj_flt,	// stat            number of major page faults since process start
//		cmin_flt,	// stat            cumulative min_flt of process and child processes
//		cmaj_flt;	// stat            cumulative maj_flt of process and child processes
//	char
//		**environ,	// (special)       environment string vector (/proc/#/environ)
//		**cmdline;	// (special)       command line string vector (/proc/#/cmdline)
//	char
//		// Be compatible: Digital allows 16 and NT allows 14 ???
//		euser[P_G_SZ],	// stat(),status   effective user name
//		ruser[P_G_SZ],	// status          real user name
//		suser[P_G_SZ],	// status          saved user name
//		fuser[P_G_SZ],	// status          filesystem user name
//		rgroup[P_G_SZ],	// status          real group name
//		egroup[P_G_SZ],	// status          effective group name
//		sgroup[P_G_SZ],	// status          saved group name
//		fgroup[P_G_SZ],	// status          filesystem group name
//		cmd[16];	// stat,status     basename of executable file in call to exec(2)
//	struct proc_t
//		*ring,		// n/a             thread group ring
//		*next;		// n/a             various library uses
//	int
//		pgrp,		// stat            process group id
//		session,	// stat            session id
//		nlwp,		// stat,status     number of threads, or 0 if no clue
//		tgid,		// (special)       task group ID, the POSIX PID (see also: tid)
//		tty,		// stat            full device number of controlling terminal
//		euid, egid,     // stat(),status   effective
//		ruid, rgid,     // status          real
//		suid, sgid,     // status          saved
//		fuid, fgid,     // status          fs (used for file access only)
//		tpgid,		// stat            terminal process group id
//		exit_signal,	// stat            might not be SIGCHLD
//		processor;      // stat            current (or most recent?) CPU
//} proc_t;
//
//void stat2proc(const char* S, proc_t *restrict P) {
//	unsigned num;
//	char* tmp;
//
//	/* fill in default values for older kernels */
//	P->processor = 0;
//	P->rtprio = -1;
//	P->sched = -1;
//	P->nlwp = 0;
//
//	S = strchr(S, '(') + 1;
//	tmp = strrchr(S, ')');
//	num = tmp - S;
//	if(unlikely(num >= sizeof P->cmd)) num = sizeof P->cmd - 1;
//	memcpy(P->cmd, S, num);
//	P->cmd[num] = '\0';
//	S = tmp + 2;                 // skip ") "
//
//	num = sscanf(S,
//		"%c "
//		"%d %d %d %d %d "
//		"%lu %lu %lu %lu %lu "
//		"%Lu %Lu %Lu %Lu "  /* utime stime cutime cstime */
//		"%ld %ld "
//		"%d "
//		"%ld "
//		"%Lu "  /* start_time */
//		"%lu "
//		"%ld "
//		"%lu %"KLF"u %"KLF"u %"KLF"u %"KLF"u %"KLF"u "
//		"%*s %*s %*s %*s " /* discard, no RT signals & Linux 2.1 used hex */
//		"%"KLF"u %*lu %*lu "
//		"%d %d "
//		"%lu %lu",
//		&P->state,
//		&P->ppid, &P->pgrp, &P->session, &P->tty, &P->tpgid,
//		&P->flags, &P->min_flt, &P->cmin_flt, &P->maj_flt, &P->cmaj_flt,
//		&P->utime, &P->stime, &P->cutime, &P->cstime,
//		&P->priority, &P->nice,
//		&P->nlwp,
//		&P->alarm,
//		&P->start_time,
//		&P->vsize,
//		&P->rss,
//		&P->rss_rlim, &P->start_code, &P->end_code, &P->start_stack, &P->kstk_esp, &P->kstk_eip,
//		/*     P->signal, P->blocked, P->sigignore, P->sigcatch,   */ /* can't use */
//		&P->wchan, /* &P->nswap, &P->cnswap, */  /* nswap and cnswap dead for 2.4.xx and up */
//		/* -- Linux 2.0.35 ends here -- */
//		&P->exit_signal, &P->processor,  /* 2.2.1 ends with "exit_signal" */
//		/* -- Linux 2.2.8 to 2.5.17 end here -- */
//		&P->rtprio, &P->sched  /* both added to 2.5.18 */
//		);
//
//	if(!P->nlwp){
//		P->nlwp = 1;
//	}
//}

MemoryMonitor::MemoryMonitor()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	m_exit = false;
	m_usedMemory = 0.0;
	m_freeMemory = 1024.0;
	m_totlMemory = 1024.0;
#endif

	initialize();
}

MemoryMonitor::~MemoryMonitor()
{
	releaseSgl();
}

bool MemoryMonitor::isMemoryWarnning()
{
	double freeMem = freeMemory();
	double usedMem = usedMemory();

	if (freeMem < 50.0f || usedMem > 200.0f)
		return true;

	return false;
}

bool MemoryMonitor::isMemoryEmergence()
{
 	return (freeMemory() < 25.0);
}

double MemoryMonitor::usedMemory()
{
	double result = 0.0;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	task_basic_info_data_t taskInfo;
	mach_msg_type_number_t infoCount = TASK_BASIC_INFO_COUNT;
	kern_return_t kernReturn = task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&taskInfo, &infoCount);
	if(kernReturn != KERN_SUCCESS) {
		return result;
	}	
	result = (taskInfo.resident_size / 1024.0) / 1024.0;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(handle,&pmc,sizeof(pmc));
	result = (pmc.WorkingSetSize / 1024.0) / 1024.0; 
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	result = m_usedMemory;
#endif

	return result;
}

double MemoryMonitor::freeMemory()
{
	double result = 1000.0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	vm_statistics_data_t vmStats;
	mach_msg_type_number_t infoCount = HOST_VM_INFO_COUNT;
	kern_return_t kernReturn = host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmStats, &infoCount);
	if(kernReturn != KERN_SUCCESS)
	{
		return result;
	}
	result = ((vm_page_size * vmStats.free_count) / 1024.0) / 1024.0;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	MEMORYSTATUS memstatus;
	memset(&memstatus,0,sizeof(MEMORYSTATUS));
	memstatus.dwLength =sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&memstatus);
	result = (memstatus.dwAvailPhys / 1024.0) /1024.0; 
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	result = m_freeMemory;
#endif

	return result;
}


double MemoryMonitor::totlMemory()
{
	double result = 1000.0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	vm_statistics_data_t vmStats;
	mach_msg_type_number_t infoCount = HOST_VM_INFO_COUNT;
	kern_return_t kernReturn = host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmStats, &infoCount);
	if(kernReturn != KERN_SUCCESS)
	{
		return result;
	}
	result = ((vm_page_size * vmStats.free_count) / 1024.0) / 1024.0;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	MEMORYSTATUS memstatus;
	memset(&memstatus,0,sizeof(MEMORYSTATUS));
	memstatus.dwLength =sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&memstatus);
	result = (memstatus.dwTotalPhys / 1024.0) /1024.0;
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	result = m_totlMemory;
#endif

	return result;
}

bool MemoryMonitor::initialize()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	pthread_create(&s_queryThread, NULL, &MemoryMonitor::threadProcedure, this);
#endif
	return true;
}

void MemoryMonitor::releaseSgl()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	m_exit = true;
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void* MemoryMonitor::threadProcedure(void* data)
{
	MemoryMonitor* mm = (MemoryMonitor*)(data);

	while (!mm->m_exit)
	{
		mm->queryMemoryState();
		sleep(1);
	}
}

unsigned long MemoryMonitor::queryMemorySelf()
{
	char buf[256] = {0};
	unsigned long rssValue = 0;

	FILE* fp = fopen("/proc/self/status","r");
	if ( !fp )
	{
		return 0;
	}

	while ( !feof(fp) )
	{
		fgets(buf,sizeof(buf),fp);
		if ( strstr(buf,"VmRSS:") )
		{
			sscanf(buf,"VmRSS:\t%8lu kB\n",&rssValue);
			break;
		}
	}     

	fclose(fp);

	return rssValue;
}

void MemoryMonitor::queryMemoryState()
{	
	char buf[256] = {0};
	unsigned long usedValue = 1024*1024;
	unsigned long freeValue = 1024*1024;

	FILE* fp = fopen("/proc/meminfo","r");
	if ( !fp )
	{
		m_totlMemory = 1024;
		m_freeMemory = 1024;
	}

	while ( !feof(fp) )
	{
		fgets(buf,sizeof(buf),fp);
		if ( strstr(buf,"MemTotal:") )
		{
			sscanf(buf,"MemTotal:\t%8lu kB\n",&usedValue);
		}
		if ( strstr(buf,"MemFree:") )
		{
			sscanf(buf,"MemFree:\t%8lu kB\n",&freeValue);
			break;
		}
	}

	m_totlMemory = usedValue/1024.0;
	m_freeMemory = freeValue/1024.0;
	m_usedMemory = (double)queryMemorySelf()/1024.0;
}

int MemoryMonitor::killProcesses()
{
	//pid_t pid = 0;
	//FILE* fp = NULL;
	//struct dirent *next = NULL;
	//char path[256] = {0};

	//DIR* dir = opendir("/proc");
	//if ( !dir )
	//{
	//	return -EIO;
	//}

	//while (( next = readdir(dir) ) != NULL)
	//{
	//	/* skip non-number */
	//	if (!isdigit(*next->d_name))
	//		continue;

	//	pid = strtol(next->d_name, NULL, 0);
	//	sprintf(path, "/proc/%u/stat", pid);
	//	fp = fopen(path, "r");
	//	if(fp == NULL)
	//		continue;

	//	fclose(fp);
	//}

	//closedir(dir) ;

	return 0;
}

#endif

void MemoryMonitor::clearMemory()
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
	killProcesses();
#endif
}
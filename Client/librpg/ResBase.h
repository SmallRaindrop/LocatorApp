#ifndef __ResBase_h_
#define __ResBase_h_

#include "GameDef.h"
#include "Singleton.h"
#include <pthread.h>
#include "semaphore.h"

typedef unsigned long ResID;

enum ResType
{
	ResType_None,
	ResType_Pvr,
	ResType_Img,
	ResType_File,
};

enum ResStatus
{
	ResStatus_None,
	ResStatus_Loading,
	ResStatus_Ok,
	ResStatus_Fail,
};

enum ResResult
{
	ResResult_None,
	ResResult_Waiting,
	ResResult_Ok,
	ResResult_Fail,
};

struct ResData
{
	ResData() : id(0),type(ResType_None),status(ResStatus_None),pathKey(""){}
	ResData(ResID resid,ResType t,ResStatus s,string path) : id(resid),type(t),status(s),pathKey(path){}
	~ResData(){}

	ResID		id;		// 资源ID
	ResType		type;	// 资源类型 pvr,img,file
	ResStatus	status;	// 资源状态 null,loading...,ok,fail
	string		pathKey;// 资源路劲
};

class ResBase;
class ResTask : public Ref
{
public:
	ResTask() : type(ResType_None),pathKey(""),result(ResResult_None),pBase(NULL){}
	~ResTask(){}
	ResType		type;		// 资源类型 pvr,img,file
	string		pathKey;	// 资源路劲
	ResResult	result;		// 任务结果
	ResBase*	pBase;
};

class ResBase : public Ref
{
public:
	ResBase(ResID id,ResType type,string pathKey) : m_Data(id,type,ResStatus_None,pathKey){}
	~ResBase(){}

	inline ResID		getID(){ return m_Data.id; }
	inline ResType		getType(){ return m_Data.type;}
	inline ResStatus	getStatus(){ return m_Data.status; }
	inline string		getPathKey(){ return m_Data.pathKey; }

	inline bool			isLoading(){ return getStatus() == ResStatus_Loading; }
	inline bool			isOk(){ return getStatus() == ResStatus_Ok; }
	inline bool			isUsing(){ return isOk(); }
	inline bool			isFree(){ return isOk(); }

	ResTask*			getTask();

	virtual bool		loadAsync();
	virtual bool		load() = 0;
	virtual void		onLoadComplete(ResTask* pTask);

protected:
	ResData	m_Data;
};

class ResThread : public Ref,public Singleton<ResThread>
{
public:
	ResThread();
	~ResThread();

	bool initialize();
	void releaseSgl();

	bool addTask(ResTask* pTask);
	void clear();
	void update(float dt);
	void quit();
	void quitOk();

	inline bool isActive(){ return !m_bQuit; }

private:
	static void* threadProc(void* param);

private:
	queue<ResTask*> m_taskQueue;
	queue<ResTask*> m_taskQueueCompleted;

	pthread_mutex_t m_taskQueueMutex;
	pthread_mutex_t m_taskQueueCompletedMutex;
	pthread_t		m_hThread;
	sem_t*			m_signal; 
	volatile bool	m_bQuit;
};

#define gResThread ResThread::Instance()

#endif
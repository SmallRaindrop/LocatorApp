#include "ResBase.h"
#include "commonRef.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define CC_ASYNC_USE_NAMED_SEMAPHORE 1
#define CC_ASYNC_SEMAPHORE  "jymf"
#endif

ResTask* ResBase::getTask()
{
	ResTask* pTask = new ResTask;
	if ( pTask )
	{
		pTask->type = getType();
		pTask->pathKey = getPathKey();
		pTask->pBase = this;
		return pTask;
	}

	return NULL;
}

bool ResBase::loadAsync()
{
	ResTask* pTask = getTask();
	if ( pTask )
	{
		m_Data.status = ResStatus_Loading;
		gResThread->addTask(pTask);
		return true;
	}
	
	return false;
}

void ResBase::onLoadComplete(ResTask* pTask)
{
	if( pTask->result == ResResult_Ok )
	{
		m_Data.status = ResStatus_Ok;
	}
	else
	{
		m_Data.status = ResStatus_Fail;
	}
	CC_SAFE_RELEASE(pTask);
	
}

ResThread::ResThread() : m_signal(NULL),m_bQuit(false)
{
	initialize();
}

ResThread::~ResThread()
{
	releaseSgl();
}

bool ResThread::initialize()
{
#if CC_ASYNC_USE_NAMED_SEMAPHORE
	m_signal = sem_open(CC_ASYNC_SEMAPHORE, O_CREAT, 0644, 0);
	if(m_signal == SEM_FAILED)
	{
		m_signal = NULL;
		return false;
	}
#else
	static sem_t sem;
	int result = sem_init(&sem, 0, 0);
	if (result < 0)
	{
		return false;
	}
	m_signal = &sem;
#endif

	pthread_mutex_init(&m_taskQueueMutex, NULL);
	pthread_mutex_init(&m_taskQueueCompletedMutex, NULL);

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	struct sched_param stShedParam;
	pthread_attr_getschedparam(&attr, &stShedParam);

	stShedParam.sched_priority = sched_get_priority_min(SCHED_OTHER);
	pthread_attr_setschedparam(&attr, &stShedParam);

	pthread_create(&m_hThread, &attr, &ResThread::threadProc, this);	

	gDirector->getScheduler()->schedule(schedule_selector(ResThread::update), this, 0, false);

	return true;
}

void ResThread::releaseSgl()
{
	// 通知退出
	if ( isActive() )
	{
		quit();
	}

	// 释放未完成的任务
	clear();

	gDirector->getScheduler()->unschedule(schedule_selector(ResThread::update), this);

	// 销毁信号和互斥对象
	if (m_signal)
	{
#if CC_ASYNC_USE_NAMED_SEMAPHORE
		sem_unlink(CC_ASYNC_SEMAPHORE);
		sem_close(m_signal);
#else
		sem_destroy(m_signal);
#endif
		m_signal = NULL;
	}

	pthread_mutex_destroy(&m_taskQueueMutex);
	pthread_mutex_destroy(&m_taskQueueCompletedMutex);
}

bool ResThread::addTask(ResTask* pTask)
{
	if ( pTask )
	{
		pthread_mutex_lock(&m_taskQueueMutex);
		m_taskQueue.push(pTask);
		pthread_mutex_unlock(&m_taskQueueMutex);
		sem_post(m_signal);
		pTask->result = ResResult_Waiting;
		return true;
	}

	return false;
}

void ResThread::update(float dt)
{
	ResTask *pTask = NULL;
	if (m_taskQueueCompleted.empty())
	{

	}
	else
	{
		pthread_mutex_lock(&m_taskQueueCompletedMutex);
		pTask = m_taskQueueCompleted.front();
		m_taskQueueCompleted.pop();
		pthread_mutex_unlock(&m_taskQueueCompletedMutex);

		pTask->pBase->onLoadComplete(pTask);
	}
}

void ResThread::clear()
{
	ResTask* pTask = NULL;
	pthread_mutex_lock(&m_taskQueueMutex);
	pthread_mutex_lock(&m_taskQueueCompletedMutex);
	while (m_taskQueue.size())
	{
		pTask = m_taskQueue.front();
		pTask->result = ResResult_Fail;
		pTask->pBase->onLoadComplete(pTask);
		m_taskQueue.pop();
	}
	while (m_taskQueueCompleted.size())
	{
		pTask = m_taskQueueCompleted.front();
		pTask->pBase->onLoadComplete(pTask);
		m_taskQueueCompleted.pop();
	}
	pthread_mutex_unlock(&m_taskQueueMutex);
	pthread_mutex_unlock(&m_taskQueueCompletedMutex);
}

void ResThread::quit()
{
	m_bQuit = true;
	sem_post(m_signal);
}

void ResThread::quitOk()
{
	LOGI("=========ResThread::quitOk=============");
}

void* ResThread::threadProc(void* param)
{
	ResThread* object = (ResThread*)(param);

	ResTask* pTask = NULL;

	while (true)
	{
		if ( !object->m_signal || sem_wait(object->m_signal) < 0 )
		{
			break;
		}
		
		if ( object->m_taskQueue.empty() )
		{
			if ( object->m_bQuit )
			{
				break;
			}

			continue;
		}
		pthread_mutex_lock(&object->m_taskQueueMutex);
		pTask = object->m_taskQueue.front();
		object->m_taskQueue.pop();
		pthread_mutex_unlock(&object->m_taskQueueMutex);

		if ( pTask->pBase->load() )
		{
			pTask->result = ResResult_Ok;
			pthread_mutex_lock(&object->m_taskQueueCompletedMutex);
			object->m_taskQueueCompleted.push(pTask);
			pthread_mutex_unlock(&object->m_taskQueueCompletedMutex);
		}
		else
		{
			pTask->result = ResResult_Fail;
			pthread_mutex_lock(&object->m_taskQueueCompletedMutex);
			object->m_taskQueueCompleted.push(pTask);
			pthread_mutex_unlock(&object->m_taskQueueCompletedMutex);
		}
	}

	LOGI("=========ResThread::quitOk=============");

	return 0;
}
#ifndef _Thread_H
#define _Thread_H
#include <pthread.h>
#include "Uncopiable.h"
#include <atomic>

class CThread : Uncopiable
{
	enum ThreadStatus
	{
		THREAD_STATUS_READY = 1,	// 当前线程处于准备状态
		THREAD_STATUS_RUNNING,	// 处于运行状态
		THREAD_STATUS_SUSPEND,	// 线程挂起暂停
		THREAD_STATUS_EXITING,	// 线程正在退出
		THREAD_STATUS_EXIT		// 已经退出 
	};

public:
	pthread_t GetThreadID() const;
	unsigned char GetStatus();
	bool IsRun();
	bool IsClose();

	virtual ~CThread();
	virtual bool Start();
	virtual bool Run();
	virtual bool Exit();
	virtual void Join();

private:
	static void *ThreadFunction(void *pParm);
	void SetStatus(unsigned char btStatus);

private:
	pthread_t m_tID = 0;
	unsigned char m_btStatus = THREAD_STATUS_READY;
	unsigned int m_uSleepMill = 5;
	std::atomic_uchar m_threadStatus;
};

#endif // _Thread_H


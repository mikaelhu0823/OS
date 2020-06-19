#include "stdafx.h"
#include "Thread.h"
#include <assert.h>


Thread::Thread():
	m_ThreadName(""),
	m_bRun(false),
	m_pLock(NULL)
{
	m_pLock = new Mutex();
	assert(m_pLock);
}

Thread::Thread(const char* ThreadName):
	m_ThreadName(ThreadName),
	m_bRun(false),
	m_pLock(NULL)
{
	m_pLock = new Mutex();
	assert(m_pLock);
}

Thread::Thread(const std::string& ThreadName):
	m_ThreadName(ThreadName),
	m_bRun(false),
	m_pLock(NULL)
{
	m_pLock = new Mutex();
	assert(m_pLock);
}

Thread::~Thread(void)
{
	if (m_pLock)
	{
		delete m_pLock;
		m_pLock = NULL;
	}
}

bool Thread::Start(bool bSuspend)
{
	if (m_bRun)
	{
		return true;
	}
	if (bSuspend)
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, this, CREATE_SUSPENDED, &m_ThreadID);
	}
	else
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, this, 0, &m_ThreadID);
	}
	m_bRun = (NULL != m_handle);
	return m_bRun;
}

void Thread::Exit()
{
	//Lock lock(*m_pLock);  //hnc??? need lock???
	m_bRun = false;
}

void Thread::run()
{
	while(m_bRun)
	{
		Run();
	}
}

void Thread::Join(int timeout)
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	if (timeout <= 0)
	{
		timeout = INFINITE;
	}
	::WaitForSingleObject(m_handle, timeout);
}

void Thread::Resume()
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	::ResumeThread(m_handle);
}

void Thread::Suspend()
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	::SuspendThread(m_handle);
}

bool Thread::Terminate(unsigned long ExitCode)
{
	if (NULL == m_handle || !m_bRun)
	{
		return true;
	}
	if (::TerminateThread(m_handle, ExitCode))
	{
		::CloseHandle(m_handle);
		return true;
	}
	return false;
}

unsigned int Thread::GetThreadID()
{
	return m_ThreadID;
}

std::string Thread::GetThreadName()
{
	return m_ThreadName;
}

void Thread::SetThreadName(std::string ThreadName)
{
	m_ThreadName = ThreadName;
}

void Thread::SetThreadName(const char* ThreadName)
{
	if (NULL == ThreadName)
	{
		m_ThreadName = "";
	}
	else
	{
		m_ThreadName = ThreadName;
	}
}

unsigned int Thread::ThreadFunc(void* arg)
{
	Thread* pThread = (Thread*)arg;
	pThread->run();
	return 0;
}

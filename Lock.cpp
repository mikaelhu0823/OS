#include "stdafx.h"
#include "Lock.h"  

Mutex::Mutex()
{
	m_mutex = ::CreateMutex(NULL, FALSE, NULL);
}

Mutex::~Mutex()
{
	::CloseHandle(m_mutex);
}

void Mutex::Lock() const
{
	DWORD d = WaitForSingleObject(m_mutex, INFINITE);
}
  
void Mutex::Unlock() const
{
	::ReleaseMutex(m_mutex);
}

Lock::Lock(const IMyLock& m): m_lock(m)
{
	m_lock.Lock();
}

Lock::~Lock()
{
	m_lock.Unlock();
}


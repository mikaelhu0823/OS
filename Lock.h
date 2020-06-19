#pragma once

#include <windows.h>  

//锁接口类  
class IMyLock
{
public:
	virtual ~IMyLock() {}

	virtual void Lock() const = 0;
	virtual void Unlock() const = 0;
};

//互斥对象锁类  
class Mutex : public IMyLock
{
public:
	Mutex();
	virtual ~Mutex();

	virtual void Lock() const;
	virtual void Unlock() const;

private:
	HANDLE m_mutex;
};

//锁  
class Lock
{
public:
	Lock(const IMyLock&);
	virtual ~Lock();

private:
	const IMyLock& m_lock;
};


#pragma once

#include <windows.h>  

//���ӿ���  
class IMyLock
{
public:
	virtual ~IMyLock() {}

	virtual void Lock() const = 0;
	virtual void Unlock() const = 0;
};

//�����������  
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

//��  
class Lock
{
public:
	Lock(const IMyLock&);
	virtual ~Lock();

private:
	const IMyLock& m_lock;
};


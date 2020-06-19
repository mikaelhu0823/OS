#include "stdafx.h"
#include "CLock.h"


CCritSection::CCritSection()
{
	InitializeCriticalSection(&_critSect);
}
CCritSection::~CCritSection()
{
	DeleteCriticalSection(&_critSect);
}

void CCritSection::Acquire()
{
	EnterCriticalSection(&_critSect);
}

void CCritSection::Release()
{
	LeaveCriticalSection(&_critSect);
}


CLock::CLock(CCritSection _critSection) :m_critSection(_critSection)
{
	m_critSection.Acquire();
}

CLock::~CLock()
{
	m_critSection.Release();
}
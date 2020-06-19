#pragma once

#include<windows.h>  


class CCritSection
{
	friend class CLock;
public:
	CCritSection();
	virtual ~CCritSection();

	void Acquire();
	void Release();
private:
	CRITICAL_SECTION _critSect;
};


class CLock {
public:
	CLock(CCritSection _critSection);
	virtual ~CLock();

private:
	CCritSection m_critSection;
};
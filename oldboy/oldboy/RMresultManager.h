#pragma once
#include "RMmacro.h"
class CRMresultManager
{
	SINGLETON(CRMresultManager);

public:
	CRMresultManager(void);
	~CRMresultManager(void);

	// selectManager�� �׷��� �׳� ����?

	void			ShowResult();

private:
	std::wstring	string2wstring(const std::string& str) const;

};


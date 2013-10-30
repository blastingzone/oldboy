#pragma once
#include "RMenumSet.h"

class CRMplayer
{
public:
	CRMplayer(void);
	~CRMplayer(void);

	void		SetCount(CountType countType, UINT score = 1); // ����Ʈ ���� 1
	UINT		GetCount(CountType countType);

private:
	UINT		m_PerfectCount;
	UINT		m_GoodCount;
	UINT		m_MissCount;
	UINT		m_ComboCount;
	UINT		m_ScoreCount;
};


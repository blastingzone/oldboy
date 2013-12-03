#pragma once

//sm9: �� ������ ���� �̷��� �����ͼ� �������? ���� �̷� ������ �׳� �ý��� rand() �ᵵ ��
//�� ��Ȯ�� ������ ���� ������ http://en.wikipedia.org/wiki/Mersenne_twister 

class CRMwellRandom
{
	SINGLETON(CRMwellRandom);
private:
	CRMwellRandom(void);
	~CRMwellRandom(void);

public:
	unsigned long WELLRNG512(void);
	unsigned long WellRand(int r);
	unsigned long WellRandom(int nMin, int nMax);

private:
	unsigned long m_WellState[16];
	unsigned long m_WellIndex;
};

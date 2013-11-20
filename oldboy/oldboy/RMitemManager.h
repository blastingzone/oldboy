#pragma once
#include "RMenumSet.h"

class CRMitem;

class CRMitemManager
{
	SINGLETON(CRMitemManager);

private:
	CRMitemManager(void);
	~CRMitemManager(void);

public:
	void		RotateItem();
	// ���� �ð����� �� Ƽ���� �����۵��� �������� ȸ���ϸ鼭 ��ü ��
	//   <-- [3Ƽ��] -->
	//   <-- [2Ƽ��] -->
	//   <-- [1Ƽ��] -->

	// �������� ���� �۵��� �� ������ ��ü���� Ȯ�� �� ����

private:
	// ���� �ߵ� ���� �������� �� �迭
	CRMitem*	m_NowItem[PLAYER_MAX];

	// ������ �信 ���ʴ�� Ƽ��� Ÿ���� �����ֱ� ���� �迭
	ItemT1Type	m_Player1T1item;
	ItemT2Type	m_Player1T2item;
	ItemT3Type	m_Player1T3item;
	ItemT1Type	m_Player2T1item;
	ItemT2Type	m_Player2T2item;
	ItemT3Type	m_Player2T3item;

	// �� Ƽ� ��ǥ��(y��)�� ����
	float		m_Player1ItemPosition[TIER_MAX];
	float		m_Player2ItemPosition[TIER_MAX];
};


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
	ItemTearType	m_NowItem[PLAYER_MAX];

	// ������ �信 ���ʴ�� Ƽ��� Ÿ���� �����ֱ� ���� �迭
	ItemTearType	m_TearItem[PLAYER_MAX][TIER_MAX];
	
	// �� Ƽ� ��ǥ��(y��)�� ����
	float		m_Player1ItemPosition[TIER_MAX];
	float		m_Player2ItemPosition[TIER_MAX];
};


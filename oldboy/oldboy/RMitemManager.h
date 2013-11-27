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
	ItemType	m_NowItem[PLAYER_MAX];

	// ������ �信 ���ʴ�� Ƽ��� Ÿ���� �����ֱ� ���� �迭
	ItemType	m_TearItem[TIER_MAX];
	
	// �� Ƽ� ��ǥ��(y��)�� ����
	float		m_ItemPosition[TIER_MAX];
};


#pragma once
#include "RMenumSet.h"

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
	// 1P�� ������ 1~3Ƽ����� �ĺ��� ���� enum�� �� �迭
	ItemType	m_Player1Item[3];
	ItemType	m_Player2Item[3];
};


#pragma once
#include "rmobject.h"

class CRMitem :
	public CRMobject
{
public:
	CRMitem(void);
	~CRMitem(void);

private:
	ItemType	m_ThisType;
};

// �θ� Ŭ����
// �� Ƽ���� ���� �����۵��� �� Ŭ������ ��� �޾Ƽ� ���� �ϸ� ��
#pragma once
#include "rmobject.h"

class CRMchildEffectImage:
		public CRMobject
{
public:
	CRMchildEffectImage(void);
	~CRMchildEffectImage(void);

	virtual void	Update();
	void HitEffectFlag(); //��Ʈ�� ������� �ƴ��� Ȯ���� �־��ִ� �޼ҵ�

private:
	char m_pBitFlag;
};


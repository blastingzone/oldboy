#pragma once
#include "rmobject.h"

class CRMchildEffectImage:
		public CRMobject
{
	SINGLETON(CRMchildEffectImage);

public:
	CRMchildEffectImage(void);
	~CRMchildEffectImage(void);

	virtual void	Update();
	void HitEffectFlag(); //��Ʈ�� ������� �ƴ��� Ȯ���� �־��ִ� �޼ҵ�

private:
	unsigned char m_pBitFlag;
};


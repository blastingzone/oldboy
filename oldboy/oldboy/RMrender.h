#pragma once
#include "oldboy.h"

class CRMrender
{
private:
	CRMrender(void);
	~CRMrender(void);

public:
	// �̱��� ���� �޼ҵ�
	static CRMrender*	GetInstance();
	static void			ReleaseInstance();

	// ���丮 & ���� Ÿ�� ���� �� ��ȯ
	HRESULT	CreateFactory();
	HRESULT	CreateRenderTarget();
	ID2D1Factory*			GetRenderFactory() { return m_pDisplayFactory; }
	ID2D1HwndRenderTarget*	GetRenderTarget() { return m_pDisplayRenderTarget; }

	// ������ ���۰� ����
	void	RenderInit();
	HRESULT	RenderEnd();

private:
	ID2D1Factory*			m_pDisplayFactory;
	ID2D1HwndRenderTarget*	m_pDisplayRenderTarget;

	// �̱��� ��� ����
	static CRMrender* m_pInstance;
};


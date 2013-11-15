#include "stdafx.h"
#include "RMmacro.h"
#include "RMrender.h"
#include "RMmainLoop.h"

CRMrender::CRMrender(void):
	m_pDisplayFactory(nullptr),
	m_pDisplayRenderTarget(nullptr)
{
}


CRMrender::~CRMrender(void)
{
	SafeRelease(m_pDisplayFactory);
	SafeRelease(m_pDisplayRenderTarget);
}

HRESULT CRMrender::CreateFactory()
{
	HRESULT hr = S_FALSE;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDisplayFactory);

	return hr;
}

HRESULT CRMrender::CreateRenderTarget()
{
	HRESULT hr = S_FALSE;

	RECT rc;
	GetClientRect(CRMmainLoop::GetInstance()->GetHwnd(), &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	hr = m_pDisplayFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(CRMmainLoop::GetInstance()->GetHwnd(), size),
		&m_pDisplayRenderTarget
		);
	// D2D1_PRESENT_OPTIONS_IMMEDIATELY - FPS ���� ����(���������� ��ٸ��� ����)

	return hr;
}


///////////////////////////////////////////////////////////////////////////////
//RenderInit()�� RenderEnd()�� �׻� ���� �ٳ�� ��
//
//Begin �� End ���̿� �� Object�� ������ ������ �߰��� �� �ֵ��� ��
///////////////////////////////////////////////////////////////////////////////

void CRMrender::RenderInit()
{
	HRESULT hr = S_FALSE;

	m_pDisplayRenderTarget->BeginDraw();
	m_pDisplayRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
}

HRESULT CRMrender::RenderEnd()
{
	HRESULT hr = S_FALSE;

	hr =m_pDisplayRenderTarget->EndDraw();

	if ( hr == D2DERR_RECREATE_TARGET )
	{
		hr = S_OK;
		SafeRelease(m_pDisplayRenderTarget);
		SafeRelease(m_pDisplayFactory);
	}

	return hr;
}
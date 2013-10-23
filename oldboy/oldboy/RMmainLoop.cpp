#include "stdafx.h"
#include "RMmainLoop.h"

CRMmainLoop* CRMmainLoop::m_pInstance = nullptr;

CRMmainLoop::CRMmainLoop(void):
	m_NowTime(0),
	m_PrevTime(0),
	m_ElapsedTime(0),
	m_Fps(0)
{
	//1000ms�� 60���� ���� 60Fps�� ������ �� �ֵ��� ��
	m_Fps = 1000/60;
}


CRMmainLoop::~CRMmainLoop(void)
{
}


void CRMmainLoop::RunMessageLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); //msg �ʱ�ȭ �Լ�

	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // PeekMessage�� ��� ���� ���� ���� ���·� ����(non blocked function)
		{
			if ( msg.message == WM_QUIT )
			{
				return;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg); //Wndproc�� ����Ǿ� ����
		}
		else
		{
			// ó�� �ؾ� �� ���� �������� ó����(objectManager -> update)
			// CRMRender::GetInstance()->MovePosition();
			// �ӽ÷� �߰���

			m_NowTime = timeGetTime();

			if ( m_PrevTime == 0 )
			{
				m_PrevTime = m_NowTime;
			}

			m_ElapsedTime = m_NowTime - m_PrevTime;

			if(m_ElapsedTime % m_Fps == 0)
			{
				//ȭ�鿡 ���� ó���� ����(objectManager -> render)
// 				CRMRender::GetInstance()->Render();
// 				ValidateRect(m_HWnd, NULL);

				m_PrevTime = m_NowTime;
			}

			if(m_ElapsedTime > m_Fps)
			{
				m_PrevTime = m_NowTime;
			}
		}
	}
}


HRESULT CRMmainLoop::Init()
{
	//HRESULT hr = S_FALSE;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= HINST_THISCOMPONENT;
	wcex.hIcon			= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_OLDBOY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_OLDBOY);
	wcex.lpszClassName	= L"RhythmMatch";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);


	m_Hwnd = CreateWindow(wcex.lpszClassName, 
						L"Rhythm Match v0.125", 
						WS_OVERLAPPEDWINDOW,
						50,  //�ϱ� 4���� ȭ�� ���� ��ǥ �ǹ� 
						50, //
						1024, //
						668, //
						NULL, 
						NULL, 
						wcex.hInstance, 
						NULL);

	if (!m_Hwnd)
	{
		return S_FALSE;
	}

	ShowWindow(m_Hwnd, SW_SHOWNORMAL);
	UpdateWindow(m_Hwnd);

	return S_OK;
}





//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK CRMmainLoop::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	
	case WM_CREATE:
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

CRMmainLoop* CRMmainLoop::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new CRMmainLoop();
	}
	return m_pInstance;
}

void CRMmainLoop::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

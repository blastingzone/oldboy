#include "stdafx.h"
#include "RMmainLoop.h"
#include "RMObjectManager.h"
#include "RMresourceManager.h"
#include "RMrender.h"

#include "RMchildNote.h"
#include "RMchildBGImage.h"

CRMmainLoop* CRMmainLoop::m_pInstance = nullptr;

CRMmainLoop::CRMmainLoop(void):
	m_NowTime(0),
	m_PrevTime(0),
	m_ElapsedTime(0),
	m_Fps(0)
{
	// 1000ms�� 60���� ���� 60Fps�� ������ �� �ֵ��� ��
	m_Fps = 1000/60;

	// fmod ����ϱ� fmodex.dll������ �ʿ��ϴ�.
	CRMsound::GetInstance()->InitSound();
	CRMsound::GetInstance()->LoadSound();
}


CRMmainLoop::~CRMmainLoop(void)
{
	CRMsound::ReleaseInstance();
	CRMobjectManager::ReleaseInstance();
	CRMresourceManager::ReleaseInstance();
	CRMrender::ReleaseInstance();
}


void CRMmainLoop::RunMessageLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); //msg �ʱ�ȭ �Լ�

	CreateObject();
	// ������Ʈ ���� �κ��� �����丵
	
	CRMsound::GetInstance()->PLAYsound();

	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // PeekMessage�� ��� ���� ���� ���� ���·� ����(non blocked function)
		{
			if ( msg.message == WM_QUIT )
			{
				return;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);	// Wndproc�� ����Ǿ� ����
		}
		else
		{
			m_NowTime = timeGetTime();

			if ( m_PrevTime == 0 )
			{
				m_PrevTime = m_NowTime;
			}

			m_ElapsedTime = m_NowTime - m_PrevTime;

			if(m_ElapsedTime % m_Fps == 0)
			{
				// ó�� �ؾ� �� ���� �������� ó����
				// Update
				CRMobjectManager::GetInstance()->Update();
				// ������Ʈ �ֱ⸦ ȭ�� �ѷ��ִ� �ֱ�� ����ȭ ��Ű�� ���ؼ� �������� �̵���Ŵ
				// �׷��� ���� ��� ������Ʈ�� ���ο��� ������ �ð� ����� üũ�ؼ�
				// �ڽ��� update �Ǿ�� �� Ÿ�̹��� ����ϰų� �ؾ� ��

				CRMrender::GetInstance()->RenderInit();

				// ȭ�鿡 ���� ó���� ����
				// Render
				CRMobjectManager::GetInstance()->Render();

				CRMrender::GetInstance()->RenderEnd();
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
	// HRESULT hr = S_FALSE;

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= CRMmainLoop::WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= HINST_THISCOMPONENT;
	wcex.hIcon			= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_OLDBOY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL; // ��� ���� �κ� NULL�� ����
	wcex.lpszMenuName	= NULL;	// �޴� ���� �κ� NULL�� ����
	wcex.lpszClassName	= L"RhythmMatch";
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);


	m_Hwnd = CreateWindow(wcex.lpszClassName, 
						L"Rhythm Match v0.125", 
						WS_OVERLAPPEDWINDOW,
						50,		// �ϱ� 4���� ȭ�� ���� ��ǥ �ǹ� 
						50,		//
						1024,	//
						668,	//
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

void CRMmainLoop::CreateObject()
{
	// �̹��� ���ҽ��� �ҷ������� ������ �ʿ���
	CRMrender::GetInstance()->CreateFactory();
	CRMrender::GetInstance()->CreateRenderTarget();
	// 	// ������ ���η����� �����ڿ� �� �ִ� ������?
	// ���� �ʿ��� ���η��� �̱����� ȣ���ϹǷ� �޸� ���� ���� �߻�!

	// �̹��� ���ҽ� ���� �ҷ�����
	CRMresourceManager::GetInstance()->InitTexture();

	/**********************************************************************************/
	// ȭ�� ����� ���� �ϱ� ���� �ӽ÷� �߰� �� ��
	/**********************************************************************************/
	CRMobject*	testObject = new CRMchildBGImage();
	testObject->SetKey(BG_IMAGE);
	testObject->SetPosition(0, 0);
	CRMobjectManager::GetInstance()->AddObject(testObject);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(400, 0);
	CRMobjectManager::GetInstance()->AddObject(testObject);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(800, 0);
	CRMobjectManager::GetInstance()->AddObject(testObject);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(400, -150);
	CRMobjectManager::GetInstance()->AddObject(testObject);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(800, -150);
	CRMobjectManager::GetInstance()->AddObject(testObject);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(400, -300);
	CRMobjectManager::GetInstance()->AddObject(testObject);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(800, -300);
	CRMobjectManager::GetInstance()->AddObject(testObject);

}

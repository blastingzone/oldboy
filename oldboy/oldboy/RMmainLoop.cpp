#include "stdafx.h"
#include "RMmainLoop.h"
#include "RMObjectManager.h"
#include "RMresourceManager.h"
#include "RMrender.h"

#include "RMchildNote.h"
#include "RMchildBGImage.h"
#include "RMchildShutter.h"

CRMmainLoop* CRMmainLoop::m_pInstance = nullptr;

CRMmainLoop::CRMmainLoop(void):
	m_NowTime(0),
	m_PrevTime(0),
	m_ElapsedTime(0),
	m_Fps(0),
	m_SceneType(TITLE)
{
	// 1000ms�� 60���� ���� 60Fps�� ������ �� �ֵ��� ��
	m_Fps = 1000/60;

	// fmod ����ϱ� fmodex.dll������ �ʿ��ϴ�.
	CRMsound::GetInstance()->InitSound();
	CRMsound::GetInstance()->LoadSound("test.mp3");
	CRMsound::GetInstance()->LoadSound("Dengue_Fever-Integration.mp3");
	CRMsound::GetInstance()->LoadSound("se1.wav");
	CRMsound::GetInstance()->LoadSound("se2.wav");
	CRMsound::GetInstance()->LoadSound("se3.wav");
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
	
	CRMsound::GetInstance()->PLAYsound("test.mp3");

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

			if(m_ElapsedTime % m_Fps == 0) //SM9: �̰� 0���� �� �ȶ������� ��ҷ���??
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

				// test sound
				testSound();

				// test Key
				testKey();

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
						1040,	// 1024 + 16
						700,	// 668 + 32
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
	testObject->SetKey(BG_IMAGE_TITLE);
	testObject->SetPosition(0, 0);
	testObject->SetScene(TITLE);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_1);

	testObject = new CRMchildBGImage();
	testObject->SetKey(BG_IMAGE_PLAY);
	testObject->SetPosition(0, 0);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_1);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(395, 0);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_2);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(910, 0);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_2);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(395, -150);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_2);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(910, -150);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_2);

	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(395, -300);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_2);
	
	testObject = new CRMchildNote();
	testObject->SetKey(NOTE_NORMAL_1);
	testObject->SetPosition(910, -300);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_2);

	testObject = new CRMchildShutter();
	testObject->SetKey(SHUTTER_IMAGE);
	testObject->SetPosition(0, -660);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_3);

	testObject = new CRMchildShutter();
	testObject->SetKey(SHUTTER_IMAGE);
	testObject->SetPosition(515, -880);
	testObject->SetScene(PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, Layer_3);
}

// ================================================================

int testSoundCount = 0;
void CRMmainLoop::testSound()
{
	
	if(m_SceneType == PLAY)
	{
		++testSoundCount;
	}

	if(testSoundCount==300)
	{
		CRMsound::GetInstance()->PLAYSEsound("se1.wav");
	}
	if(testSoundCount==450)
	{
		CRMsound::GetInstance()->PLAYSEsound("se2.wav");
	}
	if(testSoundCount==540)
	{
		CRMsound::GetInstance()->PLAYSEsound("se3.wav");
	}
	if(testSoundCount==663)
	{
		CRMsound::GetInstance()->PLAYSEsound("se3.wav");
		testSoundCount = 200;
	}

	
}

void CRMmainLoop::testKey()
{

	if(CRMinput::GetInstance()->InputKeyboard() == P1TARGET1)
	{
		// 'A'Ű �Է��� ���� �� ���� �Ѿ�� ���� ����� ������ �־��� ���� 
		// RMinput.cpp Ȯ�� �� ���� ���� Key Status�� �ʱ�ȭ ���� �ʾ���

		// �� ��� Ű�� �� �� ���� ���¸� ��� ���� �ִ� ��� �ν��� �Ǿ
		// �� if ������ ����� ������ �ν� �Ǿ� ��� ���η� ����
		
		// �׷��� �ϴ��� GoNextScene() �޼ҵ带 ��� �ݺ� ȣ��(1/60�ʿ� 1ȸ�� ��ģ����...)
		// �� ��� ������ 1/60�ʿ� �� ���� ��� �ݺ� ���� �Ǵ��� ���� ��ó�� ������ ���̰�

		// ���콺�� �巡�� �� ������ ���η��� ������ ���� ������
		// (�츮 ���ӿ����� WM_MOVE�� ��Ÿ �޽��� ó���� �� �ϹǷ� �̵�ó���� �帧 ������ �� ��)
		// �ϴ��� GoNextScene() �޼ҵ� ȣ���� ���߰� �Ǿ
		// ��ġ ���콺�� �巡�� �� ������ ���������� �뷡�� ������ ��ó�� ������ ����
		
		GoNextScene();
	}
}

void CRMmainLoop::GoNextScene()
{
	if(m_SceneType == TITLE)
	{
		m_SceneType = PLAY;

		CRMsound::GetInstance()->PLAYsound("Dengue_Fever-Integration.mp3");
		// ���� �ǹ̻� ��� ���� ����� ���� �����ϴ� ���� �̰��� ��ġ �Ǵ� ���� ����
	}
}

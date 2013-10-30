#include "stdafx.h"
#include "oldboy.h"

#include "RMmainLoop.h"
#include "RMObjectManager.h"
#include "RMresourceManager.h"
#include "RMrender.h"

#include "RMchildNote.h"
#include "RMchildBGImage.h"
#include "RMchildShutter.h"
#include "RMsound.h"
#include "RMJudgeManager.h"
#include "RMchildEffectImage.h"

CRMmainLoop::CRMmainLoop(void):
	m_NowTime(0),
	m_PrevTime(0),
	m_ElapsedTime(0),
	m_Fps(0),
	m_FpsCheckTime(0),
	m_SceneType(SCENE_TITLE)
{
	// 1000ms�� 60���� ���� 60Fps�� ������ �� �ֵ��� ��
	m_Fps = 1000 / 60;
}

CRMmainLoop::~CRMmainLoop(void)
{
}

void CRMmainLoop::RunMessageLoop()
{
	MSG msg;
	UINT fps = 0;

	ZeroMemory(&msg, sizeof(msg)); //msg �ʱ�ȭ �Լ�

	// fmod ����ϱ� fmodex.dll������ �ʿ��ϴ�.
	CRMsound::GetInstance()->CreateSound();
	CRMsound::GetInstance()->LoadSound("test.mp3");
	CRMsound::GetInstance()->LoadSound("Dengue_Fever-Integration.mp3");
	CRMsound::GetInstance()->LoadSound("se1.wav");
	CRMsound::GetInstance()->LoadSound("se2.wav");
	CRMsound::GetInstance()->LoadSound("se3.wav");

	CreateObject();
	// ������Ʈ ���� �κ��� �����丵
	
	CRMsound::GetInstance()->PlaySound("test.mp3");

	while ( true )
	{
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) // PeekMessage�� ��� ���� ���� ���� ���·� ����(non blocked function)
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

			if( m_NowTime - m_FpsCheckTime > 1000 )
			{
				printf_s("FPS : %d \n", fps);

				m_FpsCheckTime = m_NowTime;
				fps = 0;
			}

			m_ElapsedTime = m_NowTime - m_PrevTime;

			if( m_ElapsedTime == m_Fps )
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
				++fps;

				CRMrender::GetInstance()->RenderEnd();
				m_PrevTime = m_NowTime;

				// test sound
				TestSound();

				// test Key
				TestKeyboard();
				CRMjudgeManager::GetInstance()->JudgeNote();
			}

			if ( m_ElapsedTime > m_Fps )
			{
				m_PrevTime = m_NowTime;
			}
		}
	}
}

HRESULT CRMmainLoop::CreateMainLoopWindow()
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
						SCREEN_SIZE_X,	// 1024 + 16
						SCREEN_SIZE_Y,	// 668 + 32
						NULL, 
						NULL, 
						wcex.hInstance, 
						NULL);

	if ( !m_Hwnd )
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
	switch ( message )
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

void CRMmainLoop::CreateObject()
{
	// �̹��� ���ҽ��� �ҷ������� ������ �ʿ���
	CRMrender::GetInstance()->CreateFactory();
	CRMrender::GetInstance()->CreateRenderTarget();
	// ������ ���η����� �����ڿ� �� �ִ� ������?
	// ���� �ʿ��� ���η��� �̱����� ȣ���ϹǷ� �޸� ���� ���� �߻�!

	// �̹��� ���ҽ� ���� �ҷ�����
	CRMresourceManager::GetInstance()->CreateFactory();
	CRMresourceManager::GetInstance()->CreateTexture();

	/**********************************************************************************/
	// ȭ�� ����� ���� �ϱ� ���� �ӽ÷� �߰� �� ��
	/**********************************************************************************/
	CRMobject*	testObject = new CRMchildBGImage();
	testObject->SetObjectType(OBJECT_BG_IMAGE_TITLE);
	testObject->SetPosition(0, 0);
	testObject->SetSceneType(SCENE_TITLE);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_BACKGROUND);

	testObject = new CRMchildBGImage();
	testObject->SetObjectType(OBJECT_BG_IMAGE_PLAY);
	testObject->SetPosition(0, 0);
	testObject->SetSceneType(SCENE_PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_BACKGROUND);
	
	for ( int i = 0; i < 100; ++i )
	{
		testObject = new CRMchildNote();
		testObject->SetObjectType(OBJECT_NOTE_NORMAL_1);
		testObject->SetPosition(0, 0);
		testObject->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_MEMORY_POOL);
	}

	testObject = new CRMchildShutter();
	testObject->SetObjectType(OBJECT_SHUTTER);
	testObject->SetPosition(0, -670);
	testObject->SetSceneType(SCENE_PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_SHUTTER);

	testObject = new CRMchildShutter();
	testObject->SetObjectType(OBJECT_SHUTTER);
	testObject->SetPosition(515, -890);
	testObject->SetSceneType(SCENE_PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_SHUTTER);

	testObject = new CRMchildEffectImage();
	testObject->SetObjectType(OBJECT_NOTE_HIT);
	testObject->SetPosition(DEFAULT_POSITION_X, DEFAULT_POSITION_Y);
	testObject->SetSceneType(SCENE_PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_NOTE_HIT);
	
	testObject = new CRMchildEffectImage();
	testObject->SetObjectType(OBJECT_NOTE_HIT);
	testObject->SetPosition(DEFAULT_POSITION_X, DEFAULT_POSITION_Y);
	testObject->SetSceneType(SCENE_PLAY);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_NOTE_HIT);
}

// ================================================================

void CRMmainLoop::TestSound()
{
	
	if ( m_SceneType != SCENE_PLAY )
	{
		return;
	}

	if ( CRMinput::GetInstance()->GetKeyboardInput()[P1_ATTACK] == true )
	{
		CRMjudgeManager::GetInstance()->StartNote(PLAYER_ONE , OBJECT_NOTE_NORMAL_1 );
	}

	if ( CRMinput::GetInstance()->GetKeyboardInput()[P1_TARGET1] == true )
	{
		CRMsound::GetInstance()->PlayEffect( "se3.wav" );
	}
	if ( CRMinput::GetInstance()->GetKeyboardInput()[P1_TARGET2] == true )
	{
		CRMsound::GetInstance()->PlayEffect("se3.wav");
	}
}

void CRMmainLoop::TestKeyboard()
{

	if ( CRMinput::GetInstance()->GetKeyboardInput()[P1_TARGET1] == true && m_SceneType == SCENE_TITLE )
	{
		GoNextScene();
	}
}

void CRMmainLoop::GoNextScene()
{
	if ( m_SceneType == SCENE_TITLE )
	{
		m_SceneType = SCENE_PLAY;

		CRMsound::GetInstance()->PlaySound("Dengue_Fever-Integration.mp3");
	}
}

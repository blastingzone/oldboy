#include "stdafx.h"
#include "resource.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMmainLoop.h"
#include "RMObjectManager.h"
#include "RMresourceManager.h"
#include "RMrender.h"
#include "RMinput.h"
#include "RMchildNote.h"
#include "RMchildBGImage.h"
#include "RMchildShutter.h"
#include "RMsound.h"
#include "RMJudgeManager.h"
#include "RMchildEffectImage.h"
#include "RMlabel.h"
#include "RMvideoPlayer.h"
#include "RMxmlLoader.h"
#include "RMnoteManager.h"
#include "RMmusicSelectManager.h"

CRMmainLoop::CRMmainLoop(void):
	m_NowTime(0),
	m_PrevTime(0),
	m_ElapsedTime(0),
	m_Fps(0),
	m_FpsCheckTime(0),
	m_SceneType(SCENE_OPENING),
	m_Hwnd(NULL),
	m_MusicSelectIndex(0)
{
	// 1000ms�� 60���� ���� 60Fps�� ������ �� �ֵ��� ��
	m_Fps = ( 1000 / 60 ) + 1;
}

CRMmainLoop::~CRMmainLoop(void)
{
}

void CRMmainLoop::RunMessageLoop()
{
	MSG msg;
	UINT fps = 0;
	HRESULT hr = S_FALSE;

	ZeroMemory( &msg, sizeof(msg) ); //msg �ʱ�ȭ �Լ�
	//===================================================================
	// ���� �����͸� �ҷ��´�.
	FindMusicData();

	//===================================================================
	// fmod ����ϱ� fmodex.dll������ �ʿ��ϴ�.
	hr = CRMsound::GetInstance()->CreateSound();
	if ( hr != S_OK )
	{
		MessageBox( NULL, ERROR_SOUND_INIT, ERROR_TITLE, MB_OK | MB_ICONSTOP );
		return;
	}
	hr = CRMsound::GetInstance()->LoadSound(BGM_TITLE, SOUND_BG_TITLE );
	if ( hr != S_OK )
	{
		MessageBox( NULL, ERROR_SOUND_LOADING, ERROR_TITLE, MB_OK | MB_ICONSTOP );
		return;
	}

	//===================================================================
	// ������ ��� �κ�
	hr = CRMvideoPlayer::GetInstance()->CreateFactory();
	
	if ( hr == S_OK )
	{
		CRMvideoPlayer::GetInstance()->StartVideo();
	}
	else
	{
		hr = GoNextScene();
		// ������ ����� ���� �ʱ�ȭ�� ���� ���� ��� ������ ��� �н�
		if ( hr != S_OK )
		{
			MessageBox( NULL, ERROR_CHANGE_SCENE, ERROR_TITLE, MB_OK | MB_ICONSTOP );
			return;
		}
	}

	hr = CreateObject();
	if ( hr != S_OK )
	{
		MessageBox( NULL, ERROR_CREATE_RESOURCE, ERROR_TITLE, MB_OK | MB_ICONSTOP );
		return;
	}

	// ������Ʈ ���� �κ��� �����丵
	
	while ( true )
	{
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) // PeekMessage�� ��� ���� ���� ���� ���·� ����(non blocked function)
		{
			if ( msg.message == WM_QUIT )
			{
				CRMvideoPlayer::GetInstance()->DestoryFactory();
				return;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);	// Wndproc�� ����Ǿ� ����
		}
		else
		{
			if ( m_SceneType == SCENE_OPENING )
			{
				CRMvideoPlayer::GetInstance()->RenderVideo();

				CRMinput::GetInstance()->UpdateKeyState();
				if ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P1_TARGET1 ) == KEY_STATUS_UP )
				{
					CRMvideoPlayer::GetInstance()->DestoryFactory();
					hr = GoNextScene();

					if ( hr != S_OK )
					{
						MessageBox( NULL, ERROR_CHANGE_SCENE, ERROR_TITLE, MB_OK | MB_ICONSTOP );
						return;
					}
				}
				continue;
			}

			m_NowTime = timeGetTime();

			if ( m_PrevTime == 0 )
			{
				m_PrevTime = m_NowTime;
			}

			
#ifdef _DEBUG
			// FPS ��¿� ���
			if( ( m_NowTime - m_FpsCheckTime ) > 1000 )
			{
			//	printConsole("FPS : %d \n", fps);

				CRMlabel*	testLabel = new CRMlabel();
				wchar_t		testChar[255] = {0, };
				swprintf_s(testChar, L"FPS : %d ", fps);

				testLabel->CreateLabel(LABEL_FPS, testChar, LABEL_FONT_NORMAL, 15.0F );
				testLabel->SetRGBA( 1.0f, 1.0f, 1.0f, 1.f );
				testLabel->SetSceneType( SCENE_PLAY );
				testLabel->SetPosition( 20, 20 );

				m_FpsCheckTime = m_NowTime;
				fps = 0;
			}
#endif

			m_ElapsedTime = m_NowTime - m_PrevTime;

			if( m_ElapsedTime == m_Fps )
			{
				// �׽�Ʈ 
				
				// ó�� �ؾ� �� ���� �������� ó����
				// Update
				CRMobjectManager::GetInstance()->Update();

				CRMrender::GetInstance()->RenderInit();

				// ȭ�鿡 ���� ó���� ����
				// Render
				CRMobjectManager::GetInstance()->Render();
				++fps;

				CRMrender::GetInstance()->RenderEnd();
				m_PrevTime = m_NowTime;
			}

			//////////////////////////////////////////////////////////////////////////
			// �Ҹ� �и� ������ ���� FPS = 60�� ���ߴ� �κп��� ����
			//////////////////////////////////////////////////////////////////////////
			CRMinput::GetInstance()->UpdateKeyState();

			// test sound
			TestSound();
			
			// test Key
			hr = TestKeyboard();
			if ( hr != S_OK )
			{
				MessageBox( NULL, ERROR_CHANGE_SCENE, ERROR_TITLE, MB_OK | MB_ICONSTOP );
				return;
			}


			//////////////////////////////////////////////////////////////////////////
			// �� ���� �κ� 
			//////////////////////////////////////////////////////////////////////////
			
			if ( m_SceneType == SCENE_SELECT_MUSIC )
			{
				CRMmusicSelectManager::GetInstance()->ShowMusicList( m_MusicVector, m_MusicSelectIndex );
			}
			else if ( m_SceneType == SCENE_PLAY )
			{
				CRMnoteManager::GetInstance()->StartNote();
				CRMjudgeManager::GetInstance()->JudgeNote();

				// �̷��� ���� ���� �ʿ�� ���µ�...
				if ( !CRMsound::GetInstance()->GetIsPlaying() )
				{
					m_SceneType = SCENE_RESULT;
				}
			}
			

			

			//////////////////////////////////////////////////////////////////////////
			// �������
			//////////////////////////////////////////////////////////////////////////

			if ( m_ElapsedTime > m_Fps )
			{
				m_PrevTime = m_NowTime;
			}
		}
	}
}



void CRMmainLoop::FindMusicData()
{
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA( MUSIC_FOLDER_SEARCH, &findFileData );

	if ( hFind == INVALID_HANDLE_VALUE )
	{
		CloseHandle(hFind);
		return;
	}

	do 
	{
		if ( (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
		{
			std::string folderName = findFileData.cFileName;
			if ( folderName.compare(".") != 0 && folderName.compare("..") != 0 )
			{
				HRESULT hr = S_FALSE;
				hr = CRMxmlLoader::GetInstance()->LoadMusicData( folderName );
				if ( hr != S_OK )
				{
					MessageBox( NULL, ERROR_LOAD_MUSIC_XML, ERROR_TITLE, MB_OK | MB_ICONSTOP );
					return;
				}
				m_MusicVector.push_back( folderName );
			}
		}
	} while ( FindNextFileA(hFind, &findFileData) != 0);
	FindClose(hFind);

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
	wcex.lpszClassName	= CLASS_NAME;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);

	int START_POSITION_X = 0;
	int START_POSITION_Y = 0;

	START_POSITION_X = GetSystemMetrics(SM_CXSCREEN);
	START_POSITION_Y = GetSystemMetrics(SM_CYSCREEN);

	START_POSITION_X = (START_POSITION_X - SCREEN_SIZE_X)/2;
	START_POSITION_Y = (START_POSITION_Y - SCREEN_SIZE_Y)/2;

	m_Hwnd = CreateWindow(wcex.lpszClassName, 
		GAME_NAME, 
		WS_POPUPWINDOW,
		START_POSITION_X,		// �ϱ� 4���� ȭ�� ���� ��ǥ �ǹ� 
		START_POSITION_Y,		//
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

HRESULT CRMmainLoop::CreateObject()
{
	HRESULT hr = S_FALSE;

	// �̹��� ���ҽ��� �ҷ������� ������ �ʿ���
	hr = CRMrender::GetInstance()->CreateFactory();
	if ( hr != S_OK )
	{
		MessageBox( NULL, ERROR_CREATE_RENDER, ERROR_TITLE, MB_OK | MB_ICONSTOP );
		return hr;
	}
	hr = CRMrender::GetInstance()->CreateRenderTarget();
	if ( hr != S_OK )
	{
		MessageBox( NULL, ERROR_CREATE_RENDER_TARGET, ERROR_TITLE, MB_OK | MB_ICONSTOP );
		return hr;
	}
	// ������ ���η����� �����ڿ� �� �ִ� ������?
	// ���� �ʿ��� ���η��� �̱����� ȣ���ϹǷ� �޸� ���� ���� �߻�!

	// �̹��� ���ҽ� ���� �ҷ�����
	hr = CRMresourceManager::GetInstance()->CreateFactory();
	if ( hr != S_OK )
	{
		MessageBox( NULL, ERROR_CREATE_WIC_FACTORY, ERROR_TITLE, MB_OK | MB_ICONSTOP );
		return hr;
	}
	hr = CRMresourceManager::GetInstance()->CreateTexture();
	if ( hr != S_OK )
	{
		MessageBox( NULL, ERROR_CREATE_BG_IMAGE, ERROR_TITLE, MB_OK | MB_ICONSTOP );
		return hr;
	}

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
	
	testObject = new CRMchildBGImage();
	testObject->SetObjectType(OBJECT_BG_IMAGE_SELECT);
	testObject->SetPosition(0, 0);
	testObject->SetSceneType(SCENE_SELECT_MUSIC);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_BACKGROUND);
	
	testObject = new CRMchildBGImage();
	testObject->SetObjectType(OBJECT_BG_IMAGE_RESULT);
	testObject->SetPosition(0, 0);
	testObject->SetSceneType(SCENE_RESULT);
	CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_BACKGROUND);




	for ( int i = 0 ; i < 100 ; ++i )
	{
		testObject = new CRMchildNote();
		testObject->SetObjectType(OBJECT_NOTE_NORMAL_1);
		testObject->SetPosition( DEFAULT_POSITION_X, DEFAULT_POSITION_Y );
		testObject->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_MEMORY_POOL);
	}

	CRMchildShutter* shutterObject = new CRMchildShutter();
	shutterObject->SetObjectType(OBJECT_SHUTTER);
	shutterObject->SetPosition(0, -670);
	shutterObject->SetSceneType(SCENE_PLAY);
	shutterObject->SetPlayer(PLAYER_ONE);
	CRMobjectManager::GetInstance()->AddObject(shutterObject, LAYER_SHUTTER);

	shutterObject = new CRMchildShutter();
	shutterObject->SetObjectType(OBJECT_SHUTTER);
	shutterObject->SetPosition(515, -890);
	shutterObject->SetSceneType(SCENE_PLAY);
	shutterObject->SetPlayer(PLAYER_TWO);
	CRMobjectManager::GetInstance()->AddObject(shutterObject, LAYER_SHUTTER);

	for ( int i = 0 ; i < 20 ; ++ i )
	{
		testObject = new CRMchildEffectImage();
		testObject->SetObjectType(OBJECT_NOTE_HIT);
		testObject->SetPosition(DEFAULT_POSITION_X, DEFAULT_POSITION_Y);
		testObject->SetSceneType(SCENE_PLAY);
		CRMobjectManager::GetInstance()->AddObject(testObject, LAYER_NOTE_HIT);
	}

	return hr;
}

// ================================================================

void CRMmainLoop::TestSound()
{
	
	if ( m_SceneType != SCENE_PLAY )
	{
		return;
	}

	if ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P1_TARGET1 ) == KEY_STATUS_DOWN )
	{
		CRMsound::GetInstance()->PlayEffect( SOUND_NOTE_1 );
		return;
	}
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P1_TARGET2 ) == KEY_STATUS_DOWN )
	{
		CRMsound::GetInstance()->PlayEffect( SOUND_NOTE_2 );
		return;
	}
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P2_TARGET1 ) == KEY_STATUS_DOWN )
	{
		CRMsound::GetInstance()->PlayEffect( SOUND_NOTE_1 );
		return;
	}
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P2_TARGET2 ) == KEY_STATUS_DOWN )
	{
		CRMsound::GetInstance()->PlayEffect( SOUND_NOTE_2 );
		return;
	}

	if ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P1_ATTACK ) == KEY_STATUS_DOWN )
	{
		int testRand1 = rand();
		if( testRand1%2 == 0 )
		{
			CRMjudgeManager::GetInstance()->StartNote( PLAYER_ONE , OBJECT_NOTE_NORMAL_1 );
		}
		else
		{
			CRMjudgeManager::GetInstance()->StartNote( PLAYER_ONE , OBJECT_NOTE_NORMAL_2 );
		}
		return;
	}
	if ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P2_ATTACK ) == KEY_STATUS_DOWN )
	{
		int testRand2 = rand();
		if( testRand2%2 == 0 )
		{
			CRMjudgeManager::GetInstance()->StartNote( PLAYER_TWO , OBJECT_NOTE_NORMAL_1 );
		}
		else
		{
			CRMjudgeManager::GetInstance()->StartNote( PLAYER_TWO , OBJECT_NOTE_NORMAL_2 );
		}
		return;
	}
}

HRESULT CRMmainLoop::TestKeyboard()
{
	HRESULT hr = S_OK;

	if ( ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P1_TARGET1 ) == KEY_STATUS_UP ) && m_SceneType == SCENE_TITLE )
	{
		hr = GoNextScene();
	}

	if ( ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P1_TARGET1 ) == KEY_STATUS_DOWN ) && m_SceneType == SCENE_SELECT_MUSIC )
	{
		m_PlayMusicName = m_MusicVector.at( m_MusicSelectIndex % m_MusicVector.size() );

		hr = GoNextScene();
	}

	if ( ( CRMinput::GetInstance()->GetKeyStatusByKey( KEY_TABLE_P2_ATTACK ) == KEY_STATUS_DOWN ) && m_SceneType == SCENE_SELECT_MUSIC )
	{
		++m_MusicSelectIndex;
	}


	return hr;
}

HRESULT CRMmainLoop::GoNextScene()
{
	HRESULT hr = S_FALSE;

	if ( m_SceneType == SCENE_OPENING )
	{
		m_SceneType = SCENE_TITLE;
		CRMsound::GetInstance()->PlaySound( SOUND_BG_TITLE );
		return S_OK;
	}

	if ( m_SceneType == SCENE_TITLE )
	{
		m_SceneType = SCENE_SELECT_MUSIC;
		CRMsound::GetInstance()->PlaySound( SOUND_BG_TITLE );
		return S_OK;
	}

	if ( m_SceneType == SCENE_SELECT_MUSIC )
	{
		hr = CRMresourceManager::GetInstance()->CreateTexture( m_PlayMusicName );
		if ( hr != S_OK )
		{
			MessageBox( NULL, ERROR_LOAD_IMAGE, ERROR_TITLE, MB_OK | MB_ICONSTOP );
			return hr;
		}

		hr = CRMsound::GetInstance()->LoadPlaySound( m_PlayMusicName );

		if ( hr != S_OK )
		{
			MessageBox( NULL, ERROR_LOAD_SOUND, ERROR_TITLE, MB_OK | MB_ICONSTOP );
			return hr;
		}

		hr = CRMxmlLoader::GetInstance()->LoadNoteData( m_PlayMusicName );

		if ( hr != S_OK )
		{
			MessageBox( NULL, ERROR_LOAD_MUSIC_XML, ERROR_TITLE, MB_OK | MB_ICONSTOP );
			return hr;
		}

		m_SceneType = SCENE_PLAY;
		CRMsound::GetInstance()->PlaySound( SOUND_BG_PLAY, false );

		CRMnoteManager::GetInstance()->Initialize();

		return S_OK;
	}

	return S_FALSE;
}

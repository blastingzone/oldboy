
// oldboy.cpp : �����Լ��� ���� �Ǿ� �ִ� ����.

#include "stdafx.h"
#include "RMmacro.h"
#include "RMmainLoop.h"

//////////////////////////////////////////////////////////////////////////
// ������ �ܼ� ����

#ifdef _DEBUG
#include "RMprintConsole.h"
#endif // _DEBUG

// �ܼ��� ���ַ��� ���� ����� �ּ�ó��
//////////////////////////////////////////////////////////////////////////

// D2D & WIC
#pragma comment(lib, "d2d1")
#pragma comment(lib, "winmm")
#pragma comment(lib, "dwrite")
#pragma comment(lib, "WindowsCodecs")

// fmod
#pragma comment( lib, "LibraryFmod/fmodex_vc.lib" )

// bandi
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")


//�����Լ� ����
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


#ifdef _PRINT_CONSOLE


	// �޸� ����� �ɼ� �κ�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ������ �ܼ� ����� ���� �Ǿ� ���� ������ �̱������� �ܼ��� ������
	CRMprintConsole::GetInstance();
#endif // _PRINT_CONSOLE

	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if ( SUCCEEDED( CoInitialize( NULL ) ) )
	{
		if ( SUCCEEDED( CRMmainLoop::GetInstance()->CreateMainLoopWindow() ) )
		{
			CRMmainLoop::GetInstance()->RunMessageLoop();
		}

		CoUninitialize();
	}

	return 0;
}



// oldboy.cpp : �����Լ��� ���� �Ǿ� �ִ� ����.


#include "stdafx.h"
#include "oldboy.h"
#include "RMmainLoop.h"


//�����Լ� ����
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// �޸� ����� �ɼ� �κ�
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	AllocConsole();
	FILE* pFile; 
	freopen_s(&pFile, "CONOUT$", "wb", stdout);

	//HACCEL hAccelTable;
	//hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OLDBOY));

	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if(SUCCEEDED(CoInitialize(NULL)))
	{
		if(SUCCEEDED(CRMmainLoop::GetInstance()->CreateMainLoopWindow()))
		{
			CRMmainLoop::GetInstance()->RunMessageLoop();
			CRMmainLoop::ReleaseInstance();

		}

	

		CoUninitialize();
	}

	FreeConsole();

	return 0;
}


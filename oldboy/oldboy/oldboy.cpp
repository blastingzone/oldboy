// oldboy.cpp : �����Լ��� ���� �Ǿ� �ִ� ����.
//
/*
	copyright wow
*/

#include "stdafx.h"
#include <crtdbg.h>

#ifdef _DEBUG
#define	new new(_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	getchar();

	return 0;
}


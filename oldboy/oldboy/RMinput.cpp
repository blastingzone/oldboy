#include "stdafx.h"
#include "oldboy.h"
#include "RMinput.h"

CRMinput* CRMinput::m_pInstance = nullptr;

CRMinput::CRMinput(void):
	m_InputKey(NO_INPUT)
{
}


CRMinput::~CRMinput(void)
{
}

KeyTable CRMinput::GetKeyboardInput()
{
	m_InputKey = NO_INPUT;
	// ���� �ʱ�ȭ �κ��� ������ �߰���

	if ( GetAsyncKeyState(VK_A) & 0x8000 )
	{
		m_InputKey = P1TARGET1;
	}

	////////////////////////////////////
	//�ϴ� �׽�Ʈ�� �빮�� AŰ�� ��
	//Ű ������ ���� �����ϵ��� ��

	return m_InputKey;
}

CRMinput* CRMinput::GetInstance()
{
	if ( m_pInstance == nullptr )
	{
		m_pInstance = new CRMinput();
	}

	return m_pInstance;
}

void CRMinput::ReleaseInstance()
{
	if ( m_pInstance != nullptr )
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
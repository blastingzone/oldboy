#include "stdafx.h"
#include "RMinput.h"

CRMinput* CRMinput::m_pInstance = nullptr;

CRMinput::CRMinput(void):
	m_inputKey(NO_INPUT)
{
}


CRMinput::~CRMinput(void)
{
}

KeyTable CRMinput::InputKeyboard()
{
	m_inputKey = NO_INPUT;
	// ���� �ʱ�ȭ �κ��� ������ �߰���

	if(GetAsyncKeyState(VK_A) & 0x8000)
	{
		m_inputKey = P1TARGET1;
	}

	////////////////////////////////////
	//�ϴ� �׽�Ʈ�� �빮�� AŰ�� ��
	//Ű ������ ���� �����ϵ��� ��

	return m_inputKey;
}

CRMinput* CRMinput::GetInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new CRMinput();
	}

	return m_pInstance;
}

void CRMinput::ReleaseInstance()
{
	if(m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}
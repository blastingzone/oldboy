#pragma once
#include "oldboy.h"

class CRMsound
{
public:
	CRMsound(void);
	~CRMsound(void);

	// fmod�� �Լ�
	void InitSound();
	void LoadSound();
	void PLAYsound();
	void DeleteSound();

	// �̱��� ���� method
	static CRMsound*	GetInstance();
	static void			ReleaseInstance();

private:
	void ErrorCheck();
	
private:
	FMOD::System*	m_SystemS;
	FMOD::Sound*	m_Sound;
	FMOD::Channel*	m_Channel;

	FMOD_RESULT		m_Result;

	//�̱��� ���� member ����
	static CRMsound*	m_pInstance;
};


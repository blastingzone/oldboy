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
	void ERRCHECK(FMOD_RESULT result);
	
private:
	FMOD::System*	m_SystemS;
	FMOD::Sound*	m_Sound;
	FMOD::Channel*	m_Channel;

	//�̱��� ���� member ����
	static CRMsound*	m_pInstance;
};


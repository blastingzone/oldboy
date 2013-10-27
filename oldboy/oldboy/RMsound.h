#pragma once
#include "oldboy.h"

class CRMsound
{
public:
	CRMsound(void);
	~CRMsound(void);

	// fmod�� �Լ�
	void InitSound();
	void LoadSound(std::string fileName);
	void PLAYsound(std::string fileName);
	void DeleteSound();

	// �̱��� ���� method
	static CRMsound*	GetInstance();
	static void			ReleaseInstance();

	void PLAYSEsound(std::string fileName);
private:
	void ErrorCheck();
	
private:
	FMOD::System*	m_SystemS;
	//FMOD::Sound*	m_Sound;
	FMOD::Channel*	m_Channel;

	FMOD_RESULT		m_Result;

	std::map<std::string, FMOD::Sound*>	m_SoundMap;

	//�̱��� ���� member ����
	static CRMsound*	m_pInstance;
};


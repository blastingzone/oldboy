#pragma once

#include "RMinclude.h"

class CRMsound
{
public:
	CRMsound(void);
	~CRMsound(void);

	// fmod�� �Լ�
	void				CreateSound();
	
	void				LoadSound( const std::string& fileName );
	void				PlaySound( const std::string& fileName );
	void				PlayEffect( const std::string& fileName );

	// �̱��� ���� method
	static CRMsound*	GetInstance();
	static void			ReleaseInstance();
	
private:
	void				DeleteSound();
	void				CheckError();
	

	FMOD::System*		m_SystemS;
	FMOD::Channel*		m_Channel;
	FMOD_RESULT			m_Result;

	//FMOD::Sound*	m_Sound;
	std::map<std::string, FMOD::Sound*>	m_SoundMap;

	//�̱��� ���� member ����
	static CRMsound*	m_pInstance;
};


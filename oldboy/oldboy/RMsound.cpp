#include "stdafx.h"
#include "oldboy.h"
#include "RMsound.h"

CRMsound::CRMsound(void):
	m_SystemS(nullptr),
	m_Channel(nullptr),
	m_Result(FMOD_ERR_UNINITIALIZED)
{
}


CRMsound::~CRMsound(void)
{
	// �Ҹ��ڿ��� �Ҵ��� �ڿ��� �ݳ��ϵ��� ��
	DeleteSound();
}


// ���� üũ
void CRMsound::CheckError()
{
	if ( m_Result != FMOD_OK )
	{
#ifdef DEBUG
		printf_s("FMOD error! (%d) %s\n", m_Result, FMOD_ErrorString(m_Result));
#endif // DEBUG
	}
}

// ���丮 ����
void CRMsound::CreateSound()
{
	m_Result = FMOD::System_Create(&m_SystemS);  // Create the main system object.
	CheckError();

	if ( m_Result == FMOD_OK )
	{
		m_Result = m_SystemS->init(2, FMOD_INIT_NORMAL, 0); // Initialize FMOD.
		CheckError();
	}
}


// ���ҽ� ���� - ����ϰ��� �ϴ� ���� �ε�
void CRMsound::LoadSound( const std::string& fileName )
{
	// ����ε�
	if ( m_Result == FMOD_OK )
	{
		FMOD::Sound* m_Sound;
		std::string filePath = "./Resource/"+fileName;
		m_Result = m_SystemS->createSound(filePath.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &m_Sound);
		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
		
		CheckError();
		m_SoundMap[fileName] = m_Sound;
	}
}

// ���
void CRMsound::PlaySound( const std::string& fileName )
{
	if ( m_Result == FMOD_OK )
	{
		m_Channel->stop();
		m_Result = m_SystemS->playSound(FMOD_CHANNEL_FREE, m_SoundMap[fileName], false, &m_Channel);
		m_Channel->setVolume(0.5);
		m_Channel->setMode(FMOD_LOOP_NORMAL);
		CheckError();
	}
}

// ȿ���� ���
void CRMsound::PlayEffect( const std::string& fileName )
{
	if ( m_Result == FMOD_OK )
	{
		
		m_Result = m_SystemS->playSound(FMOD_CHANNEL_FREE, m_SoundMap[fileName], false, &m_Channel);
		m_Channel->setVolume(0.5);
		CheckError();
	}
}


// ���� ó��
void CRMsound::DeleteSound()
{

	for ( auto& iter : m_SoundMap )
	{
		auto toBeRelease = iter.second;
		toBeRelease->release(); // m_Sound
	}
	m_SoundMap.clear();

	if ( m_SystemS )
	{
		m_SystemS->release();
		m_SystemS->close();
		m_SystemS = NULL;
	}
}

#include "stdafx.h"
#include "oldboy.h"
#include "RMsound.h"
#include "RMxmlLoader.h"
#include "RMmusicData.h"

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


	if ( m_SystemS )
	{
		m_SystemS->release();
		m_SystemS->close();
		m_SystemS = NULL;
	}

}


// ���� üũ
void CRMsound::CheckError()
{
	if ( m_Result != FMOD_OK )
	{
		printConsole("FMOD error! (%d) %s\n", m_Result, FMOD_ErrorString(m_Result));
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
void CRMsound::LoadSound( const std::string& filePath, SoundType soundType )
{
	// ����ε�
	if ( m_Result == FMOD_OK )
	{
		FMOD::Sound* m_Sound;
		m_Result = m_SystemS->createSound(filePath.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &m_Sound);
		// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
		
		CheckError();
		m_SoundMap[soundType] = m_Sound;
	}
}

void CRMsound::LoadPlaySound( const std::string& musicFolderName )
{
	DeleteSound();
	std::string filePath;
	LoadSound("./Resource/bgm_title_00_01.mp3", SOUND_BG_TITLE );

	filePath = "./Music/";
	filePath.append(musicFolderName);
	filePath.append("/");
	filePath.append( *(CRMxmlLoader::GetInstance()->GetMusicData( musicFolderName )->GetSoundBackground() ) );
	LoadSound( filePath, SOUND_BG_PLAY );

	filePath = "./Music/";
	filePath.append(musicFolderName);
	filePath.append("/");
	filePath.append( *(CRMxmlLoader::GetInstance()->GetMusicData( musicFolderName )->GetSoundNoteEffect1() ) );
	LoadSound( filePath, SOUND_NOTE_1 );

	filePath = "./Music/";
	filePath.append(musicFolderName);
	filePath.append("/");
	filePath.append( *(CRMxmlLoader::GetInstance()->GetMusicData( musicFolderName )->GetSoundNoteEffect2() ) );

	LoadSound( filePath, SOUND_NOTE_2 );

}

// ���
void CRMsound::PlaySound( SoundType soundType )
{
	if ( m_Result == FMOD_OK )
	{
		m_Channel->stop();
		m_Result = m_SystemS->playSound(FMOD_CHANNEL_FREE, m_SoundMap[soundType], false, &m_Channel);
		m_Channel->setVolume(0.8f);
		m_Channel->setMode(FMOD_LOOP_NORMAL);

		CheckError();
	}
}

// ȿ���� ���
void CRMsound::PlayEffect( SoundType soundType )
{
	if ( m_Result == FMOD_OK )
	{
		
		m_Result = m_SystemS->playSound(FMOD_CHANNEL_FREE, m_SoundMap[soundType], false, &m_Channel);
		m_Channel->setVolume(0.7f);
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

}

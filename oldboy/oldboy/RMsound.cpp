#include "stdafx.h"
#include "oldboy.h"
#include "RMsound.h"
#include "RMxmlLoader.h"
#include "RMmusicData.h"

CRMsound::CRMsound(void):
	m_SystemS(nullptr),
	m_ChannelBG(nullptr),
	m_ChannelSE(nullptr),
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
HRESULT CRMsound::CheckError()
{
	if ( m_Result != FMOD_OK )
	{
		printConsole( ERROR_FMOD_CONSOLE, m_Result, FMOD_ErrorString( m_Result ) );

		return S_FALSE;
	}

	return S_OK;
}

// ���丮 ����
HRESULT CRMsound::CreateSound()
{
	m_Result = FMOD::System_Create(&m_SystemS);  // Create the main system object.
	
	if ( CheckError() != S_OK )
	{
		return S_FALSE;
	}
	
	m_Result = m_SystemS->init(2, FMOD_INIT_NORMAL, 0); // Initialize FMOD.
		
	if ( CheckError() != S_OK )
	{
		return S_FALSE;
	}
	
	return S_OK;
}


// ���� ���ҽ� ����
HRESULT CRMsound::LoadSound( const std::string& filePath, SoundType soundType )
{
	if ( CheckError() != S_OK )
	{
		return S_FALSE;
	}
	
	FMOD::Sound* m_Sound;

	m_Result = m_SystemS->createSound(filePath.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &m_Sound);
	// FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
	
	if ( CheckError() != S_OK )
	{
		return S_FALSE;
	}

	m_SoundMap[soundType] = m_Sound;
	
	return S_OK;
}

// � ���� ������ ������ �ε�
HRESULT CRMsound::LoadPlaySound( const std::string& musicFolderName )
{
	HRESULT hr = S_FALSE;

	DeleteSound();

	std::string filePath;
	hr = LoadSound( BGM_TITLE, SOUND_BG_TITLE );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	filePath = MUSIC_FOLDER;
	filePath.append( musicFolderName );
	filePath.append( FOLDER_SLASH );
	filePath.append( *(CRMxmlLoader::GetInstance()->GetMusicData( musicFolderName )->GetSoundBackground() ) );
	hr = LoadSound( filePath, SOUND_BG_PLAY );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	filePath = MUSIC_FOLDER;
	filePath.append(musicFolderName);
	filePath.append(FOLDER_SLASH);
	filePath.append( *(CRMxmlLoader::GetInstance()->GetMusicData( musicFolderName )->GetSoundNoteEffect1() ) );
	hr = LoadSound( filePath, SOUND_NOTE_1 );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	filePath = MUSIC_FOLDER;
	filePath.append( musicFolderName );
	filePath.append( FOLDER_SLASH );
	filePath.append( *(CRMxmlLoader::GetInstance()->GetMusicData( musicFolderName )->GetSoundNoteEffect2() ) );
	hr = LoadSound( filePath, SOUND_NOTE_2 );
	if ( CheckError() != S_OK )
	{
		DeleteSound();
		return hr;
	}

	return hr;
}

// ���
void CRMsound::PlaySound( SoundType soundType, bool isLoop )
{
	if ( m_Result == FMOD_OK )
	{

		if ( m_ChannelBG != nullptr )
		{
			m_ChannelBG->stop();
		}
		
		m_Result = m_SystemS->playSound( FMOD_CHANNEL_FREE, m_SoundMap[soundType], false, &m_ChannelBG );
		m_ChannelBG->setVolume(0.8f);
		if (isLoop)
		{
			m_ChannelBG->setMode( FMOD_LOOP_OFF );
		}
		else
		{
			m_ChannelBG->setMode( FMOD_LOOP_NORMAL );
		}
		

		CheckError();
	}
}

// ȿ���� ���
void CRMsound::PlayEffect( SoundType soundType )
{
	if ( m_Result == FMOD_OK )
	{
		m_Result = m_SystemS->playSound( FMOD_CHANNEL_FREE, m_SoundMap[soundType], false, &m_ChannelSE );
		m_ChannelSE->setVolume( 0.7f );
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

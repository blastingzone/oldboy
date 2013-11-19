﻿#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMresourceManager.h"
#include "RMimage.h"
#include "RMxmlLoader.h"
#include "RMmusicData.h"

CRMresourceManager::CRMresourceManager(void):
	m_pWICFactory(nullptr)
{
}


CRMresourceManager::~CRMresourceManager(void)
{
	SafeRelease(m_pWICFactory);

	InitializeMap();
}


void CRMresourceManager::InitializeMap()
{
	for ( auto& iter : m_TextureMap )
	{
		auto toBeDelete = iter.second;
		SafeDelete( toBeDelete );
	}
	m_TextureMap.clear();
}

void CRMresourceManager::InitializeAlbum()
{
	if ( m_TextureMap[OBJECT_ALBUM_IMAGE] != nullptr )
	{
		SafeDelete( m_TextureMap[OBJECT_ALBUM_IMAGE] );
	}
}

//////////////////////////////////////////////////////////////////////////
//CLSID_WICImagingFactory는 1, 2가 나뉘어져 있음
//각 PC에 따라서 구동되는 것이 다르기 때문에 해당 내용에 대해서 확인하는 방어 코드 작성
//////////////////////////////////////////////////////////////////////////

HRESULT CRMresourceManager::CreateFactory()
{
	HRESULT hr = S_FALSE;

	if ( m_pWICFactory == nullptr )
	{
		hr = CoCreateInstance( CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory) );

		if ( hr == REGDB_E_CLASSNOTREG )
		{
			hr = CoCreateInstance( CLSID_WICImagingFactory1, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory) );

			if ( hr == REGDB_E_CLASSNOTREG )
			{
				hr = CoCreateInstance( CLSID_WICImagingFactory2, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pWICFactory) );
			}
		}

	}

	return hr;
}


HRESULT CRMresourceManager::CreateTexture()
{
	InitializeMap();

	HRESULT hr = S_FALSE;
	CRMimage* texture = new CRMimage(); //SM9: 이렇게 선언과 동시에 초기화/할당 하는 것을 습관들이도록.

	hr = texture->CreateImage( BG_IMAGE_TITLE );
	
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_BG_IMAGE_TITLE] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureMap[OBJECT_BG_IMAGE_TITLE] = nullptr;
		SafeDelete(texture);
	}


	texture = new CRMimage();
	hr = texture->CreateImage( BG_IMAGE_SELECT );
	
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_BG_IMAGE_SELECT] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureMap[OBJECT_BG_IMAGE_SELECT] = nullptr;
		SafeDelete(texture);
	}

	texture = new CRMimage();
	hr = texture->CreateImage( BG_IMAGE_RESULT );
	
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_BG_IMAGE_RESULT] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureMap[OBJECT_BG_IMAGE_RESULT] = nullptr;
		SafeDelete(texture);
	}

	return hr;
}

HRESULT CRMresourceManager::CreateTexture( const std::string& folderName )
{
	InitializeMap();

	HRESULT hr = S_FALSE;
	CRMimage* texture;

	texture = new CRMimage();
	hr = texture->CreateImage( BG_IMAGE_TITLE );
	
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_BG_IMAGE_TITLE] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureMap[OBJECT_BG_IMAGE_TITLE] = nullptr;
		InitializeMap();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( BG_IMAGE_SELECT );
	
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_BG_IMAGE_SELECT] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureMap[OBJECT_BG_IMAGE_SELECT] = nullptr;
		InitializeMap();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( BG_IMAGE_RESULT );
	
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_BG_IMAGE_RESULT] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureMap[OBJECT_BG_IMAGE_RESULT] = nullptr;
		InitializeMap();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageBackground() ) );
	
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_BG_IMAGE_PLAY] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureMap[OBJECT_BG_IMAGE_PLAY] = nullptr;
		InitializeMap();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageShutter() ) );
	
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_SHUTTER] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureMap[OBJECT_SHUTTER] = nullptr;
		InitializeMap();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNote1() ) );
	
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_NOTE_NORMAL_1] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureMap[OBJECT_NOTE_NORMAL_1] = nullptr;
		InitializeMap();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNote2() ) );
	
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_NOTE_NORMAL_2] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureMap[OBJECT_NOTE_NORMAL_2] = nullptr;
		InitializeMap();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNoteEffect() ) );
	
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_NOTE_HIT] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureMap[OBJECT_NOTE_HIT] = nullptr;
		InitializeMap();

		return hr;
	}

	return hr;
}


HRESULT CRMresourceManager::CreateTextureAlbum( const std::string& folderName )
{
	InitializeAlbum();

	HRESULT hr = S_FALSE;
	CRMimage* texture;

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageAlbum() ) );
	
	if ( hr == S_OK )
	{
		m_TextureMap[OBJECT_ALBUM_IMAGE] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		InitializeAlbum();
		return hr;
	}

	return hr;
}

std::wstring CRMresourceManager::GetFilePath( const std::string& folderName, const std::string& resourceName ) const
{
	std::string str = MUSIC_FOLDER;
	str.append( folderName );
	str.append( FOLDER_SLASH );
	str.append( resourceName );

	std::wstring wstr(str.length(),L' ');
	copy(str.begin(),str.end(),wstr.begin());

	return wstr;
}


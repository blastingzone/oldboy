﻿#include "stdafx.h"
#include "RMdefine.h"
#include "RMconst.h"
#include "RMmacro.h"
#include "RMresourceManager.h"
#include "RMimage.h"
#include "RMxmlLoader.h"
#include "RMmusicData.h"

CRMresourceManager::CRMresourceManager(void):
	m_pWICFactory(nullptr)
{
	ZeroMemory(&m_TextureArray, sizeof(m_TextureArray));
}


CRMresourceManager::~CRMresourceManager(void)
{
	SafeRelease(m_pWICFactory);

	InitializeArray();
}


void CRMresourceManager::InitializeArray()
{
	for ( auto& toBeDelete : m_TextureArray )
	{
		SafeDelete( toBeDelete );
	}
}

void CRMresourceManager::InitializeAlbum( AlbumImageType imageType )
{
	if ( imageType == ALBUM_IMAGE_STATIC )
	{
		SafeDelete( m_TextureArray[WIDGET_ALBUM_IMAGE] );
	}
	else if ( imageType == ALBUM_IMAGE_DYNAMIC )
	{
		SafeDelete( m_TextureArray[WIDGET_MOVING_ALBUM_IMAGE] );
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


// 기본 Resource폴더의 텍스쳐 로드
HRESULT CRMresourceManager::CreateTexture()
{
	InitializeArray();
	
	HRESULT hr = S_FALSE;
	CRMimage* texture = new CRMimage();

	hr = TextureMaker( BG_IMAGE_TITLE, WIDGET_BG_IMAGE_TITLE );
	hr = TextureMaker( BG_IMAGE_SELECT, WIDGET_BG_IMAGE_SELECT );
	hr = TextureMaker( BG_IMAGE_RESULT, WIDGET_BG_IMAGE_RESULT );

	//////////////////////////////////////////////////////////////////////////
	//tooltips
	//////////////////////////////////////////////////////////////////////////
	hr = TextureMaker( BG_TOOLTIP_1, WIDGET_TOOLTIP_1 );
	hr = TextureMaker( BG_TOOLTIP_2, WIDGET_TOOLTIP_2 );
	hr = TextureMaker( BG_TOOLTIP_3, WIDGET_TOOLTIP_3 );

	//////////////////////////////////////////////////////////////////////////
	//pause
	//////////////////////////////////////////////////////////////////////////
	hr = TextureMaker( PAUSE_IMAGE_PLAY_CANCEL, WIDGET_PAUSE_IMAGE_PLAY_CANCEL );
	hr = TextureMaker( PAUSE_IMAGE_PLAY_OK, WIDGET_PAUSE_IMAGE_PLAY_OK );
	hr = TextureMaker( PAUSE_IMAGE_TITLE_CANCEL, WIDGET_PAUSE_IMAGE_TITLE_CANCEL );
	hr = TextureMaker( PAUSE_IMAGE_TITLE_OK, WIDGET_PAUSE_IMAGE_TITLE_OK );

	//////////////////////////////////////////////////////////////////////////
	// 플레이 화면
	//////////////////////////////////////////////////////////////////////////
	hr = TextureMaker( PLAY_IMAGE_JUDGE_RING, WIDGET_JUDGE_RING );
	hr = TextureMaker( PLAY_IMAGE_BLUE_GAUGE, WIDGET_GAUGE_2P );
	hr = TextureMaker( PLAY_IMAGE_RED_GAUGE, WIDGET_GAUGE_1P );
	hr = TextureMaker( PLAY_IMAGE_JUDGE_PERFECT, WIDGET_PLAY_JUDGE_PERFECT );
	hr = TextureMaker( PLAY_IMAGE_JUDGE_GOOD, WIDGET_PLAY_JUDGE_GOOD );
	hr = TextureMaker( PLAY_IMAGE_JUDGE_MISS, WIDGET_PLAY_JUDGE_MISS );
	hr = TextureMaker( PLAY_IMAGE_JUDGE_NONE, WIDGET_PLAY_JUDGE_NONE );

	hr = TextureMaker( PLAY_IMAGE_ALERT_GROW_BLUE, WIDGET_PLAY_ALERT_GROW_BLUE );
	hr = TextureMaker( PLAY_IMAGE_ALERT_GROW_RED, WIDGET_PLAY_ALERT_GROW_RED );

	//////////////////////////////////////////////////////////////////////////
	// SLECT BAR
	//////////////////////////////////////////////////////////////////////////
	hr = TextureMaker( UI_IMAGE_SELECT_BAR_0, WIDGET_UI_IMAGE_SELECT_BAR_0 );
	hr = TextureMaker( UI_IMAGE_SELECT_BAR_1, WIDGET_UI_IMAGE_SELECT_BAR_1 );
	hr = TextureMaker( UI_IMAGE_SELECT_BAR_2, WIDGET_UI_IMAGE_SELECT_BAR_2 );
	hr = TextureMaker( UI_IMAGE_SELECT_BAR_3, WIDGET_UI_IMAGE_SELECT_BAR_3 );
	hr = TextureMaker( UI_IMAGE_SELECT_BAR_4, WIDGET_UI_IMAGE_SELECT_BAR_4 );
	hr = TextureMaker( UI_IMAGE_SELECT_BAR_5, WIDGET_UI_IMAGE_SELECT_BAR_5 );

	//////////////////////////////////////////////////////////////////////////
	// UI
	//////////////////////////////////////////////////////////////////////////
	hr = TextureMaker( UI_IMAGE_RESULT_WIN_CLEAR, WIDGET_UI_IMAGE_RESULT_WIN_CLEAR );
	hr = TextureMaker( UI_IMAGE_RESULT_WIN_FAIL, WIDGET_UI_IMAGE_RESULT_WIN_FAIL );
	hr = TextureMaker( UI_IMAGE_RESULT_LOSE_CLEAR, WIDGET_UI_IMAGE_RESULT_LOSE_CLEAR );
	hr = TextureMaker( UI_IMAGE_RESULT_LOSE_FAIL, WIDGET_UI_IMAGE_RESULT_LOSE_FAIL );

	hr = TextureMaker( UI_IMAGE_PLAY_CPU_MODE, WIDGET_UI_IMAGE_PLAY_CPU_MODE );

	//////////////////////////////////////////////////////////////////////////
	// TITLE MODE
	//////////////////////////////////////////////////////////////////////////
	hr = TextureMaker( TITLE_MODE_SINGLE, WIDGET_TITLE_MODE_SINGLE );
	hr = TextureMaker( TITLE_MODE_DUAL, WIDGET_TITLE_MODE_DUAL );
	hr = TextureMaker( TITLE_MODE_TUTORIAL, WIDGET_TITLE_MODE_TUTORIAL );
	hr = TextureMaker( TITLE_MODE_EXIT, WIDGET_TITLE_MODE_EXIT );

	//////////////////////////////////////////////////////////////////////////
	// 아이템 이미지 리소스 추가
	//////////////////////////////////////////////////////////////////////////
	
	// Item_T1_Duplicate
	hr = TextureMaker( L"./Resource/itemSet/Item_T1_Duplicate_Color.png", WIDGET_ITEM_T1_DUPLICATE_COLOR );
	hr = TextureMaker( L"./Resource/itemSet/Item_T1_Duplicate_Gray.png", WIDGET_ITEM_T1_DUPLICATE_GRAY );
	hr = TextureMaker( L"./Resource/cardSet/t1_duplicate.png", WIDGET_ITEM_T1_DUPLICATE_CARD );

	// Item_T1_Mist
	hr = TextureMaker( L"./Resource/itemSet/Item_T1_Cloud_Color.png", WIDGET_ITEM_T1_MIST_COLOR );
	hr = TextureMaker( L"./Resource/itemSet/Item_T1_Cloud_Gray.png", WIDGET_ITEM_T1_MIST_GRAY );
	hr = TextureMaker( L"./Resource/cardSet/t1_mist.png", WIDGET_ITEM_T1_MIST_CARD );

	// Item_T1_ScoreUp
	hr = TextureMaker( L"./Resource/itemSet/Item_T1_ScoreUp_Color.png", WIDGET_ITEM_T1_SCORE_UP_COLOR );
	hr = TextureMaker( L"./Resource/itemSet/Item_T1_ScoreUp_Gray.png", WIDGET_ITEM_T1_SCORE_UP_GRAY );
	hr = TextureMaker( L"./Resource/cardSet/t1_scoreup.png", WIDGET_ITEM_T1_SCORE_UP_CARD );

	// Item_T2_Barrier
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_Barrier_Color.png", WIDGET_ITEM_T2_BARRIER_COLOR );
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_Barrier_Gray.png", WIDGET_ITEM_T2_BARRIER_GRAY );
	hr = TextureMaker( L"./Resource/cardSet/t2_barrier.png", WIDGET_ITEM_T2_BARRIER_CARD );

	// Item_T2_Delay
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_Delay_Color.png", WIDGET_ITEM_T2_DELAY_COLOR );
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_Delay_Gray.png", WIDGET_ITEM_T2_DELAY_GRAY );
	hr = TextureMaker( L"./Resource/cardSet/t2_delay.png", WIDGET_ITEM_T2_DELAY_CARD );

	// Item_T2_GaugeClear
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_GaugeClear_Color.png", WIDGET_ITEM_T2_GAUGE_CLEAR_COLOR );
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_GaugeClear_Gray.png", WIDGET_ITEM_T2_GAUGE_CLEAR_GRAY );
	hr = TextureMaker( L"./Resource/cardSet/t2_gaugeclear.png", WIDGET_ITEM_T2_GAUGE_CLEAR_CARD );

	// Item_T2_Rotate
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_Rotate_Color.png", WIDGET_ITEM_T2_ROTATE_COLOR );
	hr = TextureMaker( L"./Resource/itemSet/Item_T2_Rotate_Gray.png", WIDGET_ITEM_T2_ROTATE_GRAY );
	hr = TextureMaker( L"./Resource/cardSet/t2_rotate.png", WIDGET_ITEM_T2_ROTATE_CARD );

	// Item_T3_Recovery
	hr = TextureMaker( L"./Resource/itemSet/Item_T3_Recovery_Color.png", WIDGET_ITEM_T3_RECOVERY_COLOR );
	hr = TextureMaker( L"./Resource/itemSet/Item_T3_Recovery_Gray.png", WIDGET_ITEM_T3_RECOVERY_GRAY );
	hr = TextureMaker( L"./Resource/cardSet/t3_recovery.png", WIDGET_ITEM_T3_RECOVERY_CARD );

	// Item_T3_Reverse
	hr = TextureMaker( L"./Resource/itemSet/Item_T3_Reverse_Color.png", WIDGET_ITEM_T3_REVERSE_COLOR );
	hr = TextureMaker( L"./Resource/itemSet/Item_T3_Reverse_Gray.png", WIDGET_ITEM_T3_REVERSE_GRAY );
	hr = TextureMaker( L"./Resource/cardSet/t3_reverse.png", WIDGET_ITEM_T3_REVERSE_CARD );

	return hr;
}

HRESULT CRMresourceManager::TextureMaker( const std::wstring& path, WidgetType type )
{
	HRESULT hr = S_FALSE;
	CRMimage* texture = new CRMimage();
	hr = texture->CreateImage( path );

	if ( hr == S_OK )
	{
		m_TextureArray[type] = texture;
		return hr;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureArray[type] = nullptr;
		SafeDelete(texture);

		return hr;
	}
}

HRESULT CRMresourceManager::CreateTexture( const std::string& folderName )
{
	
	HRESULT hr = S_FALSE;
	CRMimage* texture;

	// 기본 자원 로드
	hr = CreateTexture();
	if ( hr == S_FALSE )
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		InitializeArray();
		return hr;
	}
	

	// 곡마다 바뀌는 정보 로드

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageBackground() ) );
	
	if ( hr == S_OK )
	{
		m_TextureArray[WIDGET_BG_IMAGE_PLAY] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureArray[WIDGET_BG_IMAGE_PLAY] = nullptr;
		InitializeArray();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageShutter() ) );
	
	if ( hr == S_OK )
	{
		m_TextureArray[WIDGET_SHUTTER] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureArray[WIDGET_SHUTTER] = nullptr;
		InitializeArray();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNote1() ) );
	
	if ( hr == S_OK )
	{
		m_TextureArray[WIDGET_NOTE_NORMAL_1] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureArray[WIDGET_NOTE_NORMAL_1] = nullptr;
		InitializeArray();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNote2() ) );
	
	if ( hr == S_OK )
	{
		m_TextureArray[WIDGET_NOTE_NORMAL_2] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureArray[WIDGET_NOTE_NORMAL_2] = nullptr;
		InitializeArray();

		return hr;
	}

	texture = new CRMimage();
	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageNoteEffect() ) );
	
	if ( hr == S_OK )
	{
		m_TextureArray[WIDGET_NOTE_HIT] = texture;
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		m_TextureArray[WIDGET_NOTE_HIT] = nullptr;
		InitializeArray();

		return hr;
	}

	return hr;
}


HRESULT CRMresourceManager::CreateTextureAlbum( const std::string& folderName,  AlbumImageType imageType )
{
	HRESULT hr = S_FALSE;
	CRMimage* texture = new CRMimage();

	hr = texture->CreateImage( GetFilePath( folderName, CRMxmlLoader::GetInstance()->GetMusicData( folderName )->GetImageAlbum() ) );

	if ( hr == S_OK )
	{
		InitializeAlbum( imageType );

		if ( imageType == ALBUM_IMAGE_STATIC )
		{
			m_TextureArray[WIDGET_ALBUM_IMAGE] = texture;
		}
		else if ( imageType == ALBUM_IMAGE_DYNAMIC )
		{
			m_TextureArray[WIDGET_MOVING_ALBUM_IMAGE] = texture;
		}
	}
	else
	{
		printConsole( ERROR_LOAD_IMAGE_CONSOLE, hr);
		SafeDelete( texture );
		InitializeAlbum( imageType );
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


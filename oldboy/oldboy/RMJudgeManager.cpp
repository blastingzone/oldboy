#include "stdafx.h"
#include "oldboy.h"
#include "RMjudgeManager.h"
#include "RMobjectManager.h"
#include "RMobject.h"
#include "RMsound.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"
#include "RMchildEffectImage.h"
#include "RMlabel.h"
#include "RMchildEffectManager.h"

CRMjudgeManager::CRMjudgeManager(void) :
	m_Player1Judge(NO_JUDGE), m_Player2Judge(NO_JUDGE)
{
}


CRMjudgeManager::~CRMjudgeManager(void)
{
}

void CRMjudgeManager::StartNote( PlayerNumber player , ObjectType objectType )
{
	std::list<CRMobject*>* notePoolList = CRMobjectManager::GetInstance()->GetObjectList( LAYER_MEMORY_POOL );

	if ( notePoolList->size() == 0 )
	{
		return; 
	}
		

	auto& iter = notePoolList->begin();
	auto thisNote = iter;
	switch ( player )
	{
	case PLAYER_ONE:
		(*thisNote)->SetObjectType( objectType );
		(*thisNote)->SetPosition( 395, -100 );
		(*thisNote)->SetVisible(true);
		(*thisNote)->SetSceneType( SCENE_PLAY );
		CRMobjectManager::GetInstance()->AddObject( *thisNote , LAYER_NOTE1 );
		notePoolList->pop_front();
		break;
	case PLAYER_TWO:
		(*thisNote)->SetObjectType( objectType );
		(*thisNote)->SetPosition( 910, -100 );
		(*thisNote)->SetVisible(true);
		(*thisNote)->SetSceneType( SCENE_PLAY );
		CRMobjectManager::GetInstance()->AddObject( *thisNote , LAYER_NOTE2 );
		notePoolList->pop_front();
		break;
	case NO_PLAYER:
	default:
		break;
	}
}

void CRMjudgeManager::JudgeNote()
{
		/*
			1. ��Ʈ���� �� ��ġ ����?

			2. ��ġ�� �Ǻ� ���� ���̸� 
			Ű���� �Ŵ������� ���� => ���ȳ�?  -> �����ؾ� �� �� - ��ǲ�Ŵ����� Ű ��ư Ǫ��

			3. ��������?
			
			3-1 �ϴ��� ����� �ڵ�ó�� ���������� �޸�Ǯ�� �־���

			3-2 �Ǻ� => ��Ʈ�� ������ �� 

			3-3 ����Ʈ �ߵ�! (by �ŵ��� - "char�� ��Ʈ�������� �ϰڽ��ϴ�.")

			//545 ����
			//+- 10   535 ���ѽ���, 555���峡
			//+- 30   515 �� ����, 575�� �� 
		*/

	std::list<CRMobject*>* note1List = CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE1 );
	std::list<CRMobject*>* note2List = CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE2 );
	
	if( note1List->size() > 0 )
	{
		auto& iterP1 = note1List->begin();
		auto thisNoteP1 = iterP1;

		// Player1 Miss 575
		/*if ( (*thisNoteP1)->GetPositionY() > SCREEN_SIZE_Y - 125 + NOTE_SIZE )*/
		if ( (*thisNoteP1)->GetPositionY() > 555 )
		{

			printf_s( "1P NoteOut Miss \n" );
			
			//score up
			CRMplayer1P::GetInstance()->AddEvent( JUDGE_MISS );
			m_Player1Judge = JUDGE_MISS;
			PrintScore( PLAYER_ONE );

			DeleteNote( note1List );
		}
		// Player1 Perfect 
		else if ( (*thisNoteP1)->GetPositionY() > 534 && (*thisNoteP1)->GetPositionY() < 556 )
		{
			if ( IsKeyInputRight( *thisNoteP1 , PLAYER_ONE ) )
			{

				//effect �÷��� ����
				//�÷��׸� �����ϸ� ����Ʈ ������ �˾Ƽ� �ǰԲ� ����
				//�÷��� �����ϴ� ���� effect manager(�̱���)�� ���� �ΰ� �����սô�
				/*
						1. judge���� effect Manager flag����
						2. childeffectimage���� flag Ȯ��
						3. childeffectimage���� flag Ȯ�� �� �ٽ� flag �ʱ�ȭ
				*/
				float hitPositionX = (*thisNoteP1)->GetPositionX();
				float hitPositionY = (*thisNoteP1)->GetPositionY();
				CRMchildEffectManager::GetInstance()->SetFlag( PLAYER_ONE , hitPositionX , hitPositionY );

				printf_s( "1P Perfect \n" );

				//score up
				CRMplayer1P::GetInstance()->AddEvent( JUDGE_PERFECT );
				m_Player1Judge = JUDGE_PERFECT;
				PrintScore( PLAYER_ONE );

				//Ű �����鼭 �ٷ� ����� �÷��� ������ �ȵ�
				//Ű�� ������ ������ ������ �Ǹ� miss ó�� �Ұ�
				//deleteNote �̵�
				DeleteNote( note1List );
			}
		}
		// Player1 Good
		else if ( ( (*thisNoteP1)->GetPositionY() > 514 && (*thisNoteP1)->GetPositionY() < 576 ) )
		{
			if ( IsKeyInputRight( *thisNoteP1 , PLAYER_ONE ) )
			{
				float hitPositionX = (*thisNoteP1)->GetPositionX();
				float hitPositionY = (*thisNoteP1)->GetPositionY();
				CRMchildEffectManager::GetInstance()->SetFlag( PLAYER_ONE , hitPositionX , hitPositionY );

				printf_s( "1P Good \n" );

				//score up
				CRMplayer1P::GetInstance()->AddEvent( JUDGE_GOOD );
				m_Player1Judge = JUDGE_GOOD;
				PrintScore( PLAYER_ONE );

				DeleteNote( note1List );
			}
		}
		// Player1 �ʹ� ���� ���� MISS (aŰ�� ������ ������ good������ ���� ȸ��)
		else if ( (*thisNoteP1)->GetPositionY() > 504 )
		{
			if ( IsKeyInputRight( *thisNoteP1 , PLAYER_ONE ) )
			{
				printf_s( "1P Time Miss \n" );

				//score up;
				CRMplayer1P::GetInstance()->AddEvent( JUDGE_MISS );
				m_Player1Judge = JUDGE_MISS;
				PrintScore( PLAYER_ONE );

				DeleteNote( note1List );
			}
		}

	}

	//2p�� Ű ����Ʈ �߰� �� ��
	
	// Player2============================================================

	if( note2List->size() > 0 )
	{
		auto& iterP2 = note2List->begin();
		auto thisNoteP2 = iterP2;

		// Player2 Miss 575
		if ( (*thisNoteP2)->GetPositionY() > 555 )
		{

			printf_s( "2P NoteOut miss \n" );

			//score up
			CRMplayer2P::GetInstance()->AddEvent( JUDGE_MISS );
			m_Player2Judge = JUDGE_MISS;
			PrintScore( PLAYER_TWO );

			DeleteNote( note2List );
		}
		// Player2 Perfect 
		else if ( (*thisNoteP2)->GetPositionY() > 534 && (*thisNoteP2)->GetPositionY() < 556 )
		{
			if ( IsKeyInputRight( *thisNoteP2 , PLAYER_TWO ) )
			{
				printf_s( "2P Perfect \n" );

				//score up
				CRMplayer2P::GetInstance()->AddEvent( JUDGE_PERFECT );
				m_Player2Judge = JUDGE_PERFECT;
				PrintScore( PLAYER_TWO );

				// effect ����
				// CRMchildEffectImage::GetInstance()->HitEffectFlag();

				DeleteNote( note2List );
			}
		}
		// Player2 Good
		else if ( ( (*thisNoteP2)->GetPositionY() > 514 && (*thisNoteP2)->GetPositionY() < 576 ) )
		{
			if ( IsKeyInputRight( *thisNoteP2 , PLAYER_TWO ) )
			{
				printf_s( "2P Good \n" );

				//score up
				CRMplayer2P::GetInstance()->AddEvent( JUDGE_GOOD );
				m_Player2Judge = JUDGE_GOOD;
				PrintScore( PLAYER_TWO );

				DeleteNote( note2List );
			}
		}
		// Player2 �ʹ� ���� ���� MISS (aŰ�� ������ ������ good������ ���� ȸ��)
		else if ( (*thisNoteP2)->GetPositionY() > 504 )
		{
			if ( IsKeyInputRight( *thisNoteP2 , PLAYER_TWO ) )
			{
				printf_s( "2P Time Miss \n" );

				//score up
				CRMplayer2P::GetInstance()->AddEvent( JUDGE_MISS );
				m_Player2Judge = JUDGE_MISS;
				PrintScore( PLAYER_TWO );

				DeleteNote( note2List );
			}
		}
	}
}


bool CRMjudgeManager::IsKeyInputRight( CRMobject* note , PlayerNumber player )
{
	KeyTable target1;
	KeyTable target2;
	switch ( player )
	{
	case PLAYER_ONE:
		target1 = P1_TARGET1;
		target2 = P1_TARGET2;
		break;
	case PLAYER_TWO:
		target1 = P2_TARGET1;
		target2 = P2_TARGET2;
		break;
	case NO_PLAYER:
	default:
		break;
	}

	if ( note->GetObjectType() == OBJECT_NOTE_NORMAL_1 )
	{
		if ( CRMinput::GetInstance()->GetKeyStatusByKey( target1 ) == KEY_DOWN )
		{
			note->SetVisible( false );
			//DeleteNote( objectList );
			return true;
		}
	}
	else if ( note->GetObjectType() == OBJECT_NOTE_NORMAL_2 )
	{
		if ( CRMinput::GetInstance()->GetKeyStatusByKey( target2 ) == KEY_DOWN )
		{
			note->SetVisible( false );
			//DeleteNote( objectList );
			return true;
		}
	}

	return false;
}


void CRMjudgeManager::DeleteNote( std::list<CRMobject*>* objectList )
{
	CRMobjectManager::GetInstance()->AddObject( *objectList->begin() , LAYER_MEMORY_POOL );
	objectList->pop_front();
}

void CRMjudgeManager::PrintScore( PlayerNumber player )
{
	printf_s("����ǥ - 1P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d]  2P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d] \n", 
			CRMplayer1P::GetInstance()->GetCount( PERFECT_COUNT ), CRMplayer1P::GetInstance()->GetCount( GOOD_COUNT ), 
			CRMplayer1P::GetInstance()->GetCount( MISS_COUNT ), CRMplayer1P::GetInstance()->GetCount( COMBO_COUNT ), CRMplayer1P::GetInstance()->GetCount( SCORE_COUNT ),
			CRMplayer2P::GetInstance()->GetCount( PERFECT_COUNT ), CRMplayer2P::GetInstance()->GetCount( GOOD_COUNT ), 
			CRMplayer2P::GetInstance()->GetCount( MISS_COUNT ), CRMplayer2P::GetInstance()->GetCount( COMBO_COUNT ), CRMplayer2P::GetInstance()->GetCount( SCORE_COUNT )
			);

	CRMplayer*	thisPlayer = nullptr;
	wchar_t		*playerScoreLabelName;
	wchar_t		*playerComboLabelName;
	float		positionX = 0;
	float		positionY = 100;
	JudgeType	thisPlayerJudge = NO_JUDGE;

	switch ( player )
	{
	case PLAYER_ONE:
		thisPlayer = CRMplayer1P::GetInstance();
		playerScoreLabelName = L"�÷��̾�1����";
		playerComboLabelName = L"�÷��̾�1�޺�";
		positionX = 100;
		thisPlayerJudge = m_Player1Judge;

		break;
	case PLAYER_TWO:
		thisPlayer = CRMplayer2P::GetInstance();
		playerScoreLabelName = L"�÷��̾�2����";
		playerComboLabelName = L"�÷��̾�2�޺�";
		positionX = 600;
		thisPlayerJudge = m_Player2Judge;

		break;
	default:
		return;
	}

	wchar_t		score[255] = { 0, };
	wchar_t		judge[255] = { 0, };
	
	switch ( thisPlayerJudge )
	{
	case JUDGE_PERFECT:
		swprintf_s( judge, L"PERFECT!!" );
		break;
	case JUDGE_GOOD:
		swprintf_s( judge, L"  GOOD!  " );
		break;
	case JUDGE_MISS:
		swprintf_s( judge, L"  MISS..." );
		break;
	default:
		break;
	}

	swprintf_s( score, L"%10s \n %10d \n  %8s", L"SCORE", thisPlayer->GetCount( SCORE_COUNT ), judge );

	CRMlabel* playerScoreLabel = new CRMlabel();
	playerScoreLabel->CreateLabel( playerScoreLabelName , score, L"���� ���", 35.0F );
	playerScoreLabel->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	playerScoreLabel->SetSceneType( SCENE_PLAY );
	playerScoreLabel->SetPosition( positionX , positionY );

	if ( thisPlayer->GetCount( COMBO_COUNT ) > 0 )
	{
		swprintf_s( score, L"%8s \n  %10d", L"COMBO", thisPlayer->GetCount( COMBO_COUNT ) );

		CRMlabel* playerComboLabel = new CRMlabel();
		playerComboLabel->CreateLabel( playerComboLabelName , score, L"���� ���", 35.0F );
		playerComboLabel->SetRGBA( 0.8f, 0.5f, 0.2f, 1.f );
		playerComboLabel->SetSceneType( SCENE_PLAY );
		playerComboLabel->SetPosition( positionX, positionY + 250 );
	}
	else
	{
		CRMlabel* playerComboLabel = new CRMlabel();
		playerComboLabel->CreateLabel( playerComboLabelName , L"", L"���� ���", 35.0F );
		playerComboLabel->SetRGBA( 0.f, 0.f, 0.f, 1.f );
		playerComboLabel->SetSceneType( SCENE_PLAY );
		playerComboLabel->SetPosition( positionX, positionY + 250 );
	}

}



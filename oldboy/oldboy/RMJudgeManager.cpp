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
		
	CRMobject* thisNote = CRMobjectManager::GetInstance()->GetObjectFront( LAYER_MEMORY_POOL );
	if ( thisNote == nullptr )
	{
		return; 
	}

	switch ( player )
	{
	case PLAYER_ONE:
		thisNote->SetObjectType( objectType );
		thisNote->SetPosition( 395, -100 );
		thisNote->SetVisible(true);
		thisNote->SetSceneType( SCENE_PLAY );
		CRMobjectManager::GetInstance()->AddObject( thisNote , LAYER_NOTE1 );
		CRMobjectManager::GetInstance()->DeleteNoteListFront( LAYER_MEMORY_POOL );
		break;
	case PLAYER_TWO:
		thisNote->SetObjectType( objectType );
		thisNote->SetPosition( 910, -100 );
		thisNote->SetVisible(true);
		thisNote->SetSceneType( SCENE_PLAY );
		CRMobjectManager::GetInstance()->AddObject( thisNote , LAYER_NOTE2 );
		CRMobjectManager::GetInstance()->DeleteNoteListFront( LAYER_MEMORY_POOL );
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



	//2p�� Ű ����Ʈ �߰� �� ��
	
	// Player2============================================================

	JudgeNoteByPlayer( PLAYER_ONE );
	JudgeNoteByPlayer( PLAYER_TWO );
}


void CRMjudgeManager::JudgeNoteByPlayer( PlayerNumber playerNumber )
{

	LayerType playerLayer;
	CRMplayer* playerClass = nullptr;
	switch ( playerNumber )
	{
	case PLAYER_ONE:
		playerLayer = LAYER_NOTE1;
		playerClass = CRMplayer1P::GetInstance();
		break;
	case PLAYER_TWO:
		playerLayer = LAYER_NOTE2;
		playerClass = CRMplayer2P::GetInstance();
		break;
	case NO_PLAYER:
	default:
		break;
	}

	CRMobject* thisNote = CRMobjectManager::GetInstance()->GetObjectFront( playerLayer );
	if ( thisNote != nullptr )
	{
		if ( thisNote->GetPositionY() > 555 )
		{
#ifdef _DEBUG
			printf_s( "%dP NoteOut Miss \n",playerLayer );
#endif // _DEBUG

			//score up
			playerClass->AddEvent( JUDGE_MISS );
			PrintScore( playerNumber, JUDGE_MISS );

			CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
		}
		// Player1 Perfect 
		else if ( thisNote->GetPositionY() > 534 && thisNote->GetPositionY() < 556 )
		{
			if ( IsKeyInputRight( thisNote , playerNumber ) )
			{

				//effect �÷��� ����
				//�÷��׸� �����ϸ� ����Ʈ ������ �˾Ƽ� �ǰԲ� ����
				//�÷��� �����ϴ� ���� effect manager(�̱���)�� ���� �ΰ� �����սô�
				/*
						1. judge���� effect Manager flag����
						2. childeffectimage���� flag Ȯ��
						3. childeffectimage���� flag Ȯ�� �� �ٽ� flag �ʱ�ȭ
				*/
				float hitPositionX = thisNote->GetPositionX();
				float hitPositionY = thisNote->GetPositionY();
				CRMchildEffectManager::GetInstance()->SetFlag( playerNumber , hitPositionX , hitPositionY );

#ifdef _DEBUG
				printf_s( "%dP Perfect \n", playerLayer );
#endif // _DEBUG

				//score up
				playerClass->AddEvent( JUDGE_PERFECT );
				PrintScore( playerNumber, JUDGE_PERFECT );

				//Ű �����鼭 �ٷ� ����� �÷��� ������ �ȵ�
				//Ű�� ������ ������ ������ �Ǹ� miss ó�� �Ұ�
				//deleteNote �̵�
				CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
			}
		}
		// Player1 Good
		else if ( ( thisNote->GetPositionY() > 514 && thisNote->GetPositionY() < 576 ) )
		{
			if ( IsKeyInputRight( thisNote , playerNumber ) )
			{
				float hitPositionX = thisNote->GetPositionX();
				float hitPositionY = thisNote->GetPositionY();
				CRMchildEffectManager::GetInstance()->SetFlag( playerNumber , hitPositionX , hitPositionY );
#ifdef _DEBUG
				printf_s( "%dP Good \n", playerLayer );
#endif // _DEBUG

				
				//score up
				playerClass->AddEvent( JUDGE_GOOD );
				PrintScore( playerNumber, JUDGE_GOOD );

				CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
			}
		}
		// Player1 �ʹ� ���� ���� MISS (aŰ�� ������ ������ good������ ���� ȸ��)
		else if ( thisNote->GetPositionY() > 504 )
		{
			if ( IsKeyInputRight( thisNote , playerNumber ) )
			{

#ifdef _DEBUG
				printf_s( "%dP Time Miss \n", playerLayer );
#endif // _DEBUG

				//score up;
				playerClass->AddEvent( JUDGE_MISS );
				PrintScore( playerNumber, JUDGE_MISS );

				CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
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


void CRMjudgeManager::PrintScore( PlayerNumber player, JudgeType judgeType )
{
#ifdef _DEBUG
	printf_s("����ǥ - 1P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d]  2P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d] \n", 
			CRMplayer1P::GetInstance()->GetCount( PERFECT_COUNT ), CRMplayer1P::GetInstance()->GetCount( GOOD_COUNT ), 
			CRMplayer1P::GetInstance()->GetCount( MISS_COUNT ), CRMplayer1P::GetInstance()->GetCount( COMBO_COUNT ), CRMplayer1P::GetInstance()->GetCount( SCORE_COUNT ),
			CRMplayer2P::GetInstance()->GetCount( PERFECT_COUNT ), CRMplayer2P::GetInstance()->GetCount( GOOD_COUNT ), 
			CRMplayer2P::GetInstance()->GetCount( MISS_COUNT ), CRMplayer2P::GetInstance()->GetCount( COMBO_COUNT ), CRMplayer2P::GetInstance()->GetCount( SCORE_COUNT )
			);
#endif // _DEBUG

	CRMplayer*	thisPlayer = nullptr;
	wchar_t		*playerScoreLabelName;
	wchar_t		*playerComboLabelName;
	float		positionX = 0;
	float		positionY = 100;

	switch ( player )
	{
	case PLAYER_ONE:
		thisPlayer = CRMplayer1P::GetInstance();
		playerScoreLabelName = L"�÷��̾�1����";
		playerComboLabelName = L"�÷��̾�1�޺�";
		positionX = 100;

		break;
	case PLAYER_TWO:
		thisPlayer = CRMplayer2P::GetInstance();
		playerScoreLabelName = L"�÷��̾�2����";
		playerComboLabelName = L"�÷��̾�2�޺�";
		positionX = 600;

		break;
	default:
		return;
	}

	wchar_t		score[255] = { 0, };
	wchar_t		judge[255] = { 0, };
	
	switch ( judgeType )
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



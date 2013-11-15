#include "stdafx.h"
#include "RMmacro.h"
#include "RMdefine.h"
#include "RMkeyMapping.h"
#include "RMjudgeManager.h"
#include "RMobjectManager.h"
#include "RMobject.h"
#include "RMsound.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"
#include "RMchildEffectImage.h"
#include "RMlabel.h"
#include "RMchildEffectManager.h"
#include "RMinput.h"

CRMjudgeManager::CRMjudgeManager(void)
{
}


CRMjudgeManager::~CRMjudgeManager(void)
{
}

void CRMjudgeManager::StartNote( PlayerNumber player , ObjectType objectType ) const
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
		thisNote->SetPosition( NOTE_ONE_START_POSITION_X, NOTE_START_POSITION_Y );
		thisNote->SetVisible(true);
		thisNote->SetSceneType( SCENE_PLAY );
		CRMobjectManager::GetInstance()->AddObject( thisNote , LAYER_NOTE1 );
		CRMobjectManager::GetInstance()->DeleteNoteListFront( LAYER_MEMORY_POOL );
		break;
	case PLAYER_TWO:
		thisNote->SetObjectType( objectType );
		thisNote->SetPosition( NOTE_TWO_START_POSITION_X, NOTE_START_POSITION_Y );
		thisNote->SetVisible(true);
		thisNote->SetSceneType( SCENE_PLAY );
		CRMobjectManager::GetInstance()->AddObject( thisNote , LAYER_NOTE2 );
		CRMobjectManager::GetInstance()->DeleteNoteListFront( LAYER_MEMORY_POOL );
		break;
	case PLAYER_NONE:
	default:
		break;
	}
}

void CRMjudgeManager::JudgeNote() const
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
	
	// Player2============================================================

	JudgeNoteByPlayer( PLAYER_ONE );
	JudgeNoteByPlayer( PLAYER_TWO );
}


void CRMjudgeManager::JudgeNoteByPlayer( PlayerNumber playerNumber ) const
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
	case PLAYER_NONE:
	default:
		return;
	}

	CRMobject* thisNote = CRMobjectManager::GetInstance()->GetObjectFront( playerLayer );
	if ( thisNote != nullptr )
	{
		//note bottom miss
		if ( thisNote->GetPositionY() > NOTE_JUDGE_LATE_MISS_LINE )
		{
			printConsole( "%dP NoteOut Miss HP:%d \n", playerLayer, playerClass->GetHP() );

			//score up
			playerClass->AddEvent( JUDGE_MISS );
			playerClass->SubHP();
			PrintScore( playerNumber, JUDGE_MISS );

			CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
		}
		// Perfect 
		else if ( thisNote->GetPositionY() > NOTE_JUDGE_PERFECT_START_LINE && thisNote->GetPositionY() < NOTE_JUDGE_PERFECT_END_LINE )
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

				printConsole( "%dP Perfect \n", playerLayer );

				//score up
				playerClass->AddEvent( JUDGE_PERFECT );
				PrintScore( playerNumber, JUDGE_PERFECT );

				//Ű �����鼭 �ٷ� ����� �÷��� ������ �ȵ�
				//Ű�� ������ ������ ������ �Ǹ� miss ó�� �Ұ�
				//deleteNote �̵�
				CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
			}
		}
		// Good
		else if ( ( thisNote->GetPositionY() > NOTE_JUDGE_GOOD_START_LINE && thisNote->GetPositionY() < NOTE_JUDGE_GOOD_END_LINE ) )
		{
			if ( IsKeyInputRight( thisNote , playerNumber ) )
			{
				//effect �÷��� ����
				float hitPositionX = thisNote->GetPositionX();
				float hitPositionY = thisNote->GetPositionY();
				CRMchildEffectManager::GetInstance()->SetFlag( playerNumber , hitPositionX , hitPositionY );

				printConsole( "%dP Good \n", playerLayer );
	
				//score up
				playerClass->AddEvent( JUDGE_GOOD );
				PrintScore( playerNumber, JUDGE_GOOD );

				CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
			}
		}
		// �ʹ� ���� ���� MISS (aŰ�� ������ ������ good������ ���� ȸ��)

		else if ( thisNote->GetPositionY() > NOTE_JUDGE_FAST_MISS_LINE )
		{
			if ( IsKeyInputRight( thisNote , playerNumber ) )
			{

				printConsole( "%dP Time Miss HP:%d \n", playerLayer, playerClass->GetHP() );

				//score up;
				playerClass->AddEvent( JUDGE_MISS );
				playerClass->SubHP();
				PrintScore( playerNumber, JUDGE_MISS );

				CRMobjectManager::GetInstance()->DeleteNoteListFront( playerLayer );
			}
		}
	}
}


bool CRMjudgeManager::IsKeyInputRight( CRMobject* note , PlayerNumber player ) const
{
	KeyTable target1;
	KeyTable target2;
	switch ( player )
	{
	case PLAYER_ONE:
		target1 = KEY_TABLE_P1_TARGET1;
		target2 = KEY_TABLE_P1_TARGET2;
		break;
	case PLAYER_TWO:
		target1 = KEY_TABLE_P2_TARGET1;
		target2 = KEY_TABLE_P2_TARGET2;
		break;
	case PLAYER_NONE:
	default:
		break;
	}

	if ( note->GetObjectType() == OBJECT_NOTE_NORMAL_1 )
	{
		if ( CRMinput::GetInstance()->GetKeyStatusByKey( target1 ) == KEY_STATUS_DOWN )
		{
			note->SetVisible( false );
			//DeleteNote( objectList );
			return true;
		}
	}
	else if ( note->GetObjectType() == OBJECT_NOTE_NORMAL_2 )
	{
		if ( CRMinput::GetInstance()->GetKeyStatusByKey( target2 ) == KEY_STATUS_DOWN )
		{
			note->SetVisible( false );
			//DeleteNote( objectList );
			return true;
		}
	}

	return false;
}


void CRMjudgeManager::PrintScore( PlayerNumber player, JudgeType judgeType ) const
{
	printConsole("����ǥ - 1P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d]  2P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d] \n", 
			CRMplayer1P::GetInstance()->GetCount( COUNT_PERFECT ), CRMplayer1P::GetInstance()->GetCount( COUNT_GOOD ), 
			CRMplayer1P::GetInstance()->GetCount( COUNT_MISS ), CRMplayer1P::GetInstance()->GetCount( COUNT_COMBO ), CRMplayer1P::GetInstance()->GetCount( COUNT_SCORE ),
			CRMplayer2P::GetInstance()->GetCount( COUNT_PERFECT ), CRMplayer2P::GetInstance()->GetCount( COUNT_GOOD ), 
			CRMplayer2P::GetInstance()->GetCount( COUNT_MISS ), CRMplayer2P::GetInstance()->GetCount( COUNT_COMBO ), CRMplayer2P::GetInstance()->GetCount( COUNT_SCORE )
			);

	CRMplayer*	thisPlayer = nullptr;
	wchar_t		*playerScoreLabelName;
	wchar_t		*playerComboLabelName;
	float		positionX = 0;
	float		positionY = 100;

	switch ( player )
	{
	case PLAYER_ONE:
		thisPlayer = CRMplayer1P::GetInstance();
		playerScoreLabelName = LABEL_NAME_P1_SCORE;
		playerComboLabelName = LABEL_NAME_P1_COMBO;
		positionX = 100;

		break;
	case PLAYER_TWO:
		thisPlayer = CRMplayer2P::GetInstance();
		playerScoreLabelName = LABEL_NAME_P2_SCORE;
		playerComboLabelName = LABEL_NAME_P2_COMBO;
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
		swprintf_s( judge, LABEL_JUDGE_PERFECT );
		break;
	case JUDGE_GOOD:
		swprintf_s( judge, LABEL_JUDGE_GOOD );
		break;
	case JUDGE_MISS:
		swprintf_s( judge,LABEL_JUDGE_MISS );
		break;
	default:
		break;
	}

	swprintf_s( score, L"%10s \n %10d \n  %8s", LABEL_PLAY_SCORE, thisPlayer->GetCount( COUNT_SCORE ), judge );

	CRMlabel* playerScoreLabel = new CRMlabel();
	playerScoreLabel->CreateLabel( playerScoreLabelName , score, LABEL_FONT_NORMAL, 35.0F );
	playerScoreLabel->SetRGBA( 0.0f, 0.3f, 0.7f, 1.f );
	playerScoreLabel->SetSceneType( SCENE_PLAY );
	playerScoreLabel->SetPosition( positionX , positionY );

	if ( thisPlayer->GetCount( COUNT_COMBO ) > 1 )
	{
		swprintf_s( score, L"%8s \n  %10d", LABEL_PLAY_COMBO, thisPlayer->GetCount( COUNT_COMBO ) );

		CRMlabel* playerComboLabel = new CRMlabel();
		playerComboLabel->CreateLabel( playerComboLabelName , score, LABEL_FONT_NORMAL, 35.0F );
		playerComboLabel->SetRGBA( 0.8f, 0.5f, 0.2f, 1.f );
		playerComboLabel->SetSceneType( SCENE_PLAY );
		playerComboLabel->SetPosition( positionX, positionY + 250 );
	}
	else
	{
		CRMlabel* playerComboLabel = new CRMlabel();
		playerComboLabel->CreateLabel( playerComboLabelName , L"", LABEL_FONT_NORMAL, 35.0F );
		playerComboLabel->SetRGBA( 0.f, 0.f, 0.f, 1.f );
		playerComboLabel->SetSceneType( SCENE_PLAY );
		playerComboLabel->SetPosition( positionX, positionY + 250 );
	}

}



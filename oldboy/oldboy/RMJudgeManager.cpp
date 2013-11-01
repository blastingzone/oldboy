#include "stdafx.h"
#include "oldboy.h"
#include "RMjudgeManager.h"
#include "RMobjectManager.h"
#include "RMobject.h"
#include "RMsound.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"

CRMjudgeManager::CRMjudgeManager(void)
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
		(*thisNote)->SetSceneType( SCENE_PLAY );
		CRMobjectManager::GetInstance()->AddObject( *thisNote , LAYER_NOTE1 );
		notePoolList->erase(notePoolList->begin());
		break;
	case PLAYER_TWO:
		(*thisNote)->SetObjectType( objectType );
		(*thisNote)->SetPosition( 910, -100 );
		(*thisNote)->SetSceneType( SCENE_PLAY );
		CRMobjectManager::GetInstance()->AddObject( *thisNote , LAYER_NOTE2 );
		notePoolList->erase(notePoolList->begin());
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
	
	////////////////////////
	//���� �ذ� �ʿ� : ��ġ�� ��Ʈ�� ������ ���� ��� ù ��° ��Ʈ ������ �ι�° ��Ʈ�� �������� ����
	////////////////////////

	if( note1List->size() > 0 )
	{
		auto& iterP1 = note1List->begin();
		auto thisNoteP1 = iterP1;

		// Player1 Miss 575
		if ( (*thisNoteP1)->GetPositionY() > SCREEN_SIZE_Y - 125 + NOTE_SIZE )
		{
			printf_s( "1P NoteOut Miss \n" );
			
			//score up
			CRMplayer1P::GetInstance()->AddEvent( JUDGE_MISS );

			DeleteNote( note1List );
		}
		// Player1 Perfect 
		else if ( (*thisNoteP1)->GetPositionY() > 534 && (*thisNoteP1)->GetPositionY() < 556 )
		{
			if ( IsKeyInputRight( *thisNoteP1 , note1List , PLAYER_ONE ) )
			{
				printf_s( "1P Perfect \n" );

				//score up
				CRMplayer1P::GetInstance()->AddEvent( JUDGE_PERFECT );
			}
		}
		// Player1 Good
		else if ( ( (*thisNoteP1)->GetPositionY() > 514 && (*thisNoteP1)->GetPositionY() < 576 ) )
		{
			if ( IsKeyInputRight( *thisNoteP1 , note1List , PLAYER_ONE ) )
			{
				printf_s( "1P Good \n" );

				//score up
				CRMplayer1P::GetInstance()->AddEvent( JUDGE_GOOD );
			}
		}
		// Player1 �ʹ� ���� ���� MISS (aŰ�� ������ ������ good������ ���� ȸ��)
		else if ( (*thisNoteP1)->GetPositionY() > 504 )
		{
			if ( IsKeyInputRight( *thisNoteP1 , note1List , PLAYER_ONE ) )
			{
				printf_s( "1P Time Miss \n" );

				//score up;
				CRMplayer1P::GetInstance()->AddEvent( JUDGE_MISS );
			}
		}

	}
	
	// Player2============================================================

	if( note2List->size() > 0 )
	{
		auto& iterP2 = note2List->begin();
		auto thisNoteP2 = iterP2;

		// Player2 Miss 575
		if ( (*thisNoteP2)->GetPositionY() > SCREEN_SIZE_Y - 125 + NOTE_SIZE )
		{
			printf_s( "2P NoteOut miss \n" );

			//score up
			CRMplayer2P::GetInstance()->AddEvent( JUDGE_MISS );

			DeleteNote( note2List );
		}
		// Player2 Perfect 
		else if ( (*thisNoteP2)->GetPositionY() > 534 && (*thisNoteP2)->GetPositionY() < 556 )
		{
			if ( IsKeyInputRight( *thisNoteP2 , note2List , PLAYER_TWO ) )
			{
				printf_s( "2P Perfect \n" );

				//score up
				CRMplayer2P::GetInstance()->AddEvent( JUDGE_PERFECT );
			}
		}
		// Player2 Good
		else if ( ( (*thisNoteP2)->GetPositionY() > 514 && (*thisNoteP2)->GetPositionY() < 576 ) )
		{
			if ( IsKeyInputRight( *thisNoteP2 , note2List , PLAYER_TWO ) )
			{
				printf_s( "2P Good \n" );

				//score up
				CRMplayer2P::GetInstance()->AddEvent( JUDGE_GOOD );
			}
		}
		// Player2 �ʹ� ���� ���� MISS (aŰ�� ������ ������ good������ ���� ȸ��)
		else if ( (*thisNoteP2)->GetPositionY() > 504 )
		{
			if ( IsKeyInputRight( *thisNoteP2 , note2List , PLAYER_TWO ) )
			{
				printf_s( "2P Time Miss \n" );

				//score up
				CRMplayer2P::GetInstance()->AddEvent( JUDGE_MISS );
			}
		}
	}

	printf_s("����ǥ - 1P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d]  2P [P:%d] [G:%d] [M:%d] [C:%d] [S:%d] \n", 
				CRMplayer1P::GetInstance()->GetCount( PERFECT_COUNT ), CRMplayer1P::GetInstance()->GetCount( GOOD_COUNT ), 
				CRMplayer1P::GetInstance()->GetCount( MISS_COUNT ), CRMplayer1P::GetInstance()->GetCount( COMBO_COUNT ), CRMplayer1P::GetInstance()->GetCount( SCORE_COUNT ),
				CRMplayer2P::GetInstance()->GetCount( PERFECT_COUNT ), CRMplayer2P::GetInstance()->GetCount( GOOD_COUNT ), 
				CRMplayer2P::GetInstance()->GetCount( MISS_COUNT ), CRMplayer2P::GetInstance()->GetCount( COMBO_COUNT ), CRMplayer2P::GetInstance()->GetCount( SCORE_COUNT )
				);
}


bool CRMjudgeManager::IsKeyInputRight( CRMobject* note , std::list<CRMobject*>* objectList , PlayerNumber player )
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
			DeleteNote( objectList );
			return true;
		}
	}
	else if ( note->GetObjectType() == OBJECT_NOTE_NORMAL_2 )
	{
		if ( CRMinput::GetInstance()->GetKeyStatusByKey( target2 ) == KEY_DOWN )
		{
			DeleteNote( objectList );
			return true;
		}
	}

	return false;
}


void CRMjudgeManager::DeleteNote( std::list<CRMobject*>* objectList )
{
	CRMobjectManager::GetInstance()->AddObject( *objectList->begin() , LAYER_MEMORY_POOL );
	objectList->erase(objectList->begin());
}


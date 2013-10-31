#include "stdafx.h"
#include "oldboy.h"
#include "RMjudgeManager.h"
#include "RMobjectManager.h"
#include "RMobject.h"
#include "RMsound.h"

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
	std::list<CRMobject*>* note1List = CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE1 );
	std::list<CRMobject*>* note2List = CRMobjectManager::GetInstance()->GetObjectList( LAYER_NOTE2 );

	if( note1List->size() > 0 )
	{
		auto& iterP1 = note1List->begin();
		auto thisNoteP1 = iterP1;
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


		// Player1 Miss 575
		if ( (*thisNoteP1)->GetPositionY() > SCREEN_SIZE_Y - 125 + NOTE_SIZE )
		{
			printf_s( "1.miss \n" );
			//score up
			DeleteNote( note1List );
		}
		// Player1 Perfect 
		else if ( (*thisNoteP1)->GetPositionY() > 534 && (*thisNoteP1)->GetPositionY() < 556 )
		{
			if ( IsKeyInputRight( *thisNoteP1 , note1List ) )
			{
				printf_s( "1.Perfect \n" );
				//score up
			}
		}
		// Player1 Good
		else if ( ( (*thisNoteP1)->GetPositionY() > 514 && (*thisNoteP1)->GetPositionY() < 576 ) )
		{
			if ( IsKeyInputRight( *thisNoteP1 , note1List ) )
			{
				printf_s( "1.Good \n" );
				//score up
			}
		}
		// Player1 �ʹ� ���� ���� MISS (aŰ�� ������ ������ good������ ���� ȸ��)
		else if ( (*thisNoteP1)->GetPositionY() > 504 )
		{
			if ( IsKeyInputRight( *thisNoteP1 , note1List ) )
			{
				printf_s( "1.EarlyLate Miss \n" );
				//score up
			}
		}else{
			if ( CRMinput::GetInstance()->GetKeyStatusByKey( P1_TARGET1 ) == KEY_DOWN )
			{
				CRMsound::GetInstance()->PlayEffect( "se2.wav" );
			}
			if ( CRMinput::GetInstance()->GetKeyStatusByKey( P1_TARGET2 ) == KEY_DOWN )
			{
				CRMsound::GetInstance()->PlayEffect( "se3.wav" );
			}
		}
		

	}
	
	if( note2List->size() > 0 )
	{
		auto& iterP2 = note2List->begin();
		auto thisNoteP2 = iterP2;


		if ( (*thisNoteP2)->GetPositionY() > SCREEN_SIZE_Y - 1 )
		{
			DeleteNote( note2List );
		}
	}



	

}


bool CRMjudgeManager::IsKeyInputRight( CRMobject* note , std::list<CRMobject*>* objectList )
{
	if ( note->GetObjectType() == OBJECT_NOTE_NORMAL_1 )
	{
		if ( CRMinput::GetInstance()->GetKeyStatusByKey( P1_TARGET1 ) == KEY_DOWN )
		{
			CRMsound::GetInstance()->PlayEffect( "se2.wav" );
			DeleteNote( objectList );
			return true;
		}
	}
	else if ( note->GetObjectType() == OBJECT_NOTE_NORMAL_2 )
	{
		if ( CRMinput::GetInstance()->GetKeyStatusByKey( P1_TARGET2 ) == KEY_DOWN )
		{
			CRMsound::GetInstance()->PlayEffect( "se3.wav" );
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


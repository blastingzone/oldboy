#include "stdafx.h"
#include "oldboy.h"
#include "RMchildEffectManager.h"

CRMchildEffectManager::CRMchildEffectManager(void):
	m_BitFlag(0x00),
	m_Effect1PStartPositionX(0.f),
	m_Effect1PStartPositionY(0.f),
	m_FlagSetter1P(0),
	m_FlagSetter2P(0)
{
}

CRMchildEffectManager::~CRMchildEffectManager(void)
{
}


//////////////////////////////////////////////////////////////////////////////
//BitFlag ����															//
//�� ��Ʈ�� � ����Ʈ�� play ȭ�鿡 ����������� ���ƾ� ���� ����Ī		//
//�� ȭ�鿡 �ִ� 8������ ���� ����											//
//////////////////////////////////////////////////////////////////////////////

void CRMchildEffectManager::SetFlag( PlayerNumber targetPlayer , float positionX, float positionY )
{
	// ��Ʈ�� �ѷ��� ������ ����
	// judgeManager���� ��ġ���� �����ָ� ���� �ߴٰ�
	// ����Ʈ �������Ͱ� �������� �޾� �� �� �ֵ��� ��
	
	// printConsole( "1P flag : %d , 2P flag: %d \n", m_FlagSetter1P, m_FlagSetter2P );

	switch ( targetPlayer )
	{
	case PLAYER_ONE:
		m_FlagSetter1P = ++m_FlagSetter1P % 4;

		m_Effect1PStartPositionX = positionX;
		m_Effect1PStartPositionY = positionY;

		m_BitFlag |= ( 0x0010 << (3 - m_FlagSetter1P) );

		// printConsole("1P BitFlag �ߵ�! %x \n", m_BitFlag);

		break;		
	case PLAYER_TWO:
		m_FlagSetter2P = ++m_FlagSetter2P % 4;

		m_Effect2PStartPositionX = positionX;
		m_Effect2PStartPositionY = positionY;

		m_BitFlag |= ( 0x0001 << (3 - m_FlagSetter2P) );

		// printConsole("2P BitFlag �ߵ�! %x \n", m_BitFlag);

		break;

	case PLAYER_NONE:
	default:
		break;
	}
}

void CRMchildEffectManager::ResetFlag( int highMask )
{
	if ( highMask == 1 )
	{
		m_BitFlag &= 0x000F;
	}
	else
	{
		m_BitFlag &= 0x00F0;
	}
}

Position CRMchildEffectManager::GetStartPosition( PlayerNumber targetPlayer ) const
{
	Position pos = { 0, };

	switch ( targetPlayer )
	{
	case PLAYER_ONE:
		pos.x = m_Effect1PStartPositionX;
		pos.y = m_Effect1PStartPositionY;
		break;
	case PLAYER_TWO:
		pos.x = m_Effect2PStartPositionX;
		pos.y = m_Effect2PStartPositionY;
		break;
	case PLAYER_NONE:
	default:
		pos.x = ERROR_POSITION;
		pos.y = ERROR_POSITION;
		break;
	}

	return pos;
}




#include "stdafx.h"
#include "oldboy.h"
#include "RMchildEffectManager.h"

CRMchildEffectManager::CRMchildEffectManager(void):
	m_BitFlag(0x00),
	m_EffectStartPositionX(0.f),
	m_EffectStartPositionY(0.f),
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
	//��Ʈ�� �ѷ��� ������ ����
	//judgeManager���� ��ġ���� �����ָ� ���� �ߴٰ�
	//����Ʈ �������Ͱ� �������� �޾� �� �� �ֵ��� ��
	m_EffectStartPositionX = positionX;
	m_EffectStartPositionY = positionY;
	
	//�׿��ο� BitFlag ����
	//��ⷯ ������ ���ؼ� �� ��Ʈ�� �÷��׸� ���� �� �ֵ��� ��
	int flagPosition1 = 0;
	int flagPosition2 = 0;

#ifdef _DEBUG
	printf_s( "1P flag : %d , 2P flag: %d \n", m_FlagSetter1P, m_FlagSetter2P );
#endif // _DEBUG

	switch ( targetPlayer )
	{
	case PLAYER_ONE:
		m_FlagSetter1P = m_FlagSetter1P % 4;
		switch ( m_FlagSetter1P )
		{
		case 0:
			m_BitFlag = ( m_BitFlag | 0x80 );
			++m_FlagSetter1P;
			break;
		case 1:
			m_BitFlag = ( m_BitFlag | 0x40 );
			++m_FlagSetter1P;
			break;
		case 2:
			m_BitFlag = ( m_BitFlag | 0x20 );
			++m_FlagSetter1P;
			break;
		case 3:
			m_BitFlag = ( m_BitFlag | 0x10 );
			++m_FlagSetter1P;
			break;
		default:
#ifdef _DEBUG
			printf_s( "Flag Setting Error\n" );
#endif // _DEBUG

			break;
		}
		break;
	case PLAYER_TWO:
		m_FlagSetter2P = m_FlagSetter2P % 4;
		switch ( m_FlagSetter2P )
		{
		case 0:
			m_BitFlag = ( m_BitFlag | 0x08 );
			++m_FlagSetter2P;
			break;
		case 1:
			m_BitFlag = ( m_BitFlag | 0x04 );
			++m_FlagSetter2P;
			break;
		case 2:
			m_BitFlag = ( m_BitFlag | 0x02 );
			++m_FlagSetter2P;
			break;
		case 3:
			m_BitFlag = ( m_BitFlag | 0x01 );
			++m_FlagSetter2P;
			break;
		default:
#ifdef _DEBUG
			printf_s( "Flag Setting Error\n" );
#endif // _DEBUG
			break;
		}
		break;
	case NO_PLAYER:
		break;
	default:
		break;
	}
}

void CRMchildEffectManager::ResetFlag()
{
	m_BitFlag = 0x00;
}



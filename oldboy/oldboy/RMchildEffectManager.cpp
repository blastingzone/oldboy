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
	
#ifdef _DEBUG
	printf_s( "1P flag : %d , 2P flag: %d \n", m_FlagSetter1P, m_FlagSetter2P );
#endif // _DEBUG

	switch ( targetPlayer )
	{
	case PLAYER_ONE:
		m_FlagSetter1P = ++m_FlagSetter1P % 4;

		m_BitFlag |= ( 0x0010 << (3 - m_FlagSetter1P) );
#ifdef _DEBUG
		printf_s("1P BitFlag �ߵ�! %x \n", m_BitFlag);
#endif
		break;		
	case PLAYER_TWO:
		m_FlagSetter2P = ++m_FlagSetter2P % 4;

		m_BitFlag |= ( 0x0001 << (3 - m_FlagSetter2P) );
#ifdef _DEBUG
		printf_s("2P BitFlag �ߵ�! %x \n", m_BitFlag);
#endif
		break;

	case NO_PLAYER:
	default:
		break;
	}
}

void CRMchildEffectManager::ResetFlag()
{
	m_BitFlag = 0x00;
}



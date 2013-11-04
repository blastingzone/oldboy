#include "stdafx.h"
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


//////////////////////////////////////////////////////////////////
//BitFlag ����													//
//�� ��Ʈ�� � ����Ʈ�� play ȭ�鿡 ����������� ���ƾ� ���� ����Ī		//
//�� ȭ�鿡 �ִ� 8������ ���� ����								    //
//////////////////////////////////////////////////////////////////

void CRMchildEffectManager::SetFlag( PlayerNumber targetPlayer , float m_PositionX, float m_PositionY )
{
	//��Ʈ�� �ѷ��� ������ ����
	//judgeManager���� ��ġ���� �����ָ� ���� �ߴٰ�
	//����Ʈ �������Ͱ� �������� �޾� �� �� �ֵ��� ��
	m_EffectStartPositionX = m_PositionX;
	m_EffectStartPositionY = m_PositionY;
	
	//�׿��ο� BitFlag ����
	//��ⷯ ������ ���ؼ� �� ��Ʈ�� �÷��׸� ���� �� �ֵ��� ��
	int flagPosition1 = 0;
	int flagPosition2 = 0;
	switch (targetPlayer)
	{
	case PLAYER_ONE:
		flagPosition1 = m_FlagSetter1P % 4;
		switch (flagPosition1)
		{
		case 0:
			m_BitFlag = ( m_BitFlag | 0x80);
			++m_FlagSetter1P;
			break;
		case 1:
			m_BitFlag = ( m_BitFlag | 0x40);
			++m_FlagSetter1P;
			break;
		case 2:
			m_BitFlag = ( m_BitFlag | 0x20);
			++m_FlagSetter1P;
			break;
		case 3:
			m_BitFlag = ( m_BitFlag | 0x10);
			++m_FlagSetter1P;
			break;
		default:
			printf_s("Flag Setting Error\n");
			break;
		}
		break;
	case PLAYER_TWO:
		flagPosition2 = m_FlagSetter2P % 4;
		switch (flagPosition2)
		{
		case 0:
			m_BitFlag = ( m_BitFlag | 0x08);
			++m_FlagSetter2P;
			break;
		case 1:
			m_BitFlag = ( m_BitFlag | 0x04);
			++m_FlagSetter2P;
			break;
		case 2:
			m_BitFlag = ( m_BitFlag | 0x02);
			++m_FlagSetter2P;
			break;
		case 3:
			m_BitFlag = ( m_BitFlag | 0x01);
			++m_FlagSetter2P;
			break;
		default:
			printf_s("Flag Setting Error\n");
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
	if(!m_BitFlag)
	{
		return;
	}
	else
	{
		m_BitFlag = 0x00;
	}
}



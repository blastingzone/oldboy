#include "stdafx.h"
#include "oldboy.h"
#include "RMchildEffectImage.h"
#include "RMchildEffectManager.h"
#include "RMmainLoop.h"

CRMchildEffectImage::CRMchildEffectImage(void):
	m_EffectTime(0),
	m_EffectType(0)
{
}


CRMchildEffectImage::~CRMchildEffectImage(void)
{
}

void CRMchildEffectImage::Update()
{
	if ( m_Visible == false && CRMchildEffectManager::GetInstance()->GetFlag() )
	{
		m_EffectTime = 0;

		m_PositionX = CRMchildEffectManager::GetInstance()->GetStartPositionX() - 22;
		m_PositionY = CRMchildEffectManager::GetInstance()->GetStartPositionY() - 22;

		m_Visible = true;
		
		for ( int i = 0 ; i < 8 ; ++i )
		{
			if ( CRMchildEffectManager::GetInstance()->GetFlag() & ( 0x01 << i ) )
			{
				m_EffectType = i % 4;
			}
		}
#ifdef _DEBUG
		printf_s( "�׽�Ʈ ��� �÷��� [ %x ] ��ǥ [ %f , %f ] Ÿ�� [ %d ] \n", 
			CRMchildEffectManager::GetInstance()->GetFlag(), 
			m_PositionX, m_PositionY, m_EffectType );
#endif
		CRMchildEffectManager::GetInstance()->ResetFlag();
	}

	if ( m_Visible == false )
	{
		return;
	}

	//2p �߰� �ʿ� ����

	m_PositionX -= 10 * m_EffectTime;;
	m_PositionY -= ( 7 - ( m_EffectType * 2) ) * m_EffectTime;

	// 8���� Ŀ���� 2P�� ����Ʈ ȿ�� �̹����� 1P ������ ħ����
	if ( ++m_EffectTime > 8 )
	{
		CRMobject::m_Visible = false;
	}

	return;
}
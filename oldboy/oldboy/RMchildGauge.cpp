#include "stdafx.h"
#include "RMmacro.h"
#include "RMchildGauge.h"
#include "RMmainLoop.h"
#include "RMchildShutter.h"
#include "RMobjectManager.h"
#include "RMdefine.h"
#include "RMplayer1P.h"
#include "RMplayer2P.h"

CRMchildGauge::CRMchildGauge(void)
{
}


CRMchildGauge::~CRMchildGauge(void)
{
}

void CRMchildGauge::Update()
{
	SetVisibleByScene();

	//////////////////////////////////////////////////////////////////////////
	//�� �÷��̾ ������ ��� ���
	//1. ������ ���̸� ���� �� ���� ������ ����
	//2. �������� ���̸� ������ ���� Ȯ��(���� �ϴ� �� ����)
	//3. ���� ���� �� ������ ���� �� �� �������� ���� ��� ������ ��� ����
	//4. �������� ���̰� ���� ���� ���� ��ų� ���� ��� -> ������ �����
	//4-1. ���Ϳ��� �Ű� �Ⱦ��� �� ��
	//////////////////////////////////////////////////////////////////////////

	float nowShutterPosition = 0.0f;
	int hp = CRMplayer1P::GetInstance()->GetHP();

	nowShutterPosition = SHUTTER_START_POSITION_Y + (PLAYER_HP_MAX - (float) hp ) * -((float) SHUTTER_START_POSITION_Y / 10) + 668;
	
	if ( m_playerNumber == PLAYER_TWO )
	{
		hp = CRMplayer2P::GetInstance()->GetHP();
		nowShutterPosition = SHUTTER_START_POSITION_Y + (PLAYER_HP_MAX - (float) hp ) * -((float) SHUTTER_START_POSITION_Y / 10) + 668;
	}


	if ( m_PositionY - 12 >= nowShutterPosition)
	{
		int mp = CRMplayer1P::GetInstance()->GetMP();
		
		if( m_playerNumber == PLAYER_TWO )
		{
			mp = CRMplayer2P::GetInstance()->GetMP();
		}

		if( mp < hp * 65 ) //mp �� hp ����
		{
			m_PositionY = (float)( SCREEN_SIZE_Y - 12 - mp );

// ���� ���� Ŀ���� �������� ��ġ ���� ����Ǿ�� �ұ�?
// ���� �ڵ���!
// 			float resultPosition = (float)( SCREEN_SIZE_Y - 12 - mp );
// 			if ( (int)m_PositionY != (int)resultPosition )
// 			{
// 				m_PositionY += (resultPosition - m_PositionY) / 20;
// 			}
// 			m_PositionY = (float)( SCREEN_SIZE_Y - 12 - mp );
		}
	}
	else
	{
		//���� �������� �ִϸ��̼ǰ� ��ũ ����
		float resultPosion = nowShutterPosition;
		if ( (int)m_PositionY != (int)resultPosion )
		{
			m_PositionY += (resultPosion - m_PositionY) /20;
		}
	}

}
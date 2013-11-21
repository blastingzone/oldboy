#include "stdafx.h"
#include "RMmacro.h"
#include "RMchildGauge.h"
#include "RMmainLoop.h"
#include "RMchildShutter.h"
#include "RMobjectManager.h"
#include "RMdefine.h"
#include "RMplayer1P.h"

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

	switch (m_playerNumber)
	{
	case PLAYER_NONE:
		break;
	case PLAYER_ONE:
		nowShutterPosition = SHUTTER_START_POSITION_Y + (PLAYER_HP_MAX - (float) CRMplayer1P::GetInstance()->GetHP() ) * -((float) SHUTTER_START_POSITION_Y / 10) + 668;
		break;
	case PLAYER_TWO:
		nowShutterPosition = SHUTTER_START_POSITION_Y + (PLAYER_HP_MAX - (float) CRMplayer1P::GetInstance()->GetHP() ) * -((float) SHUTTER_START_POSITION_Y / 10) + 668;
		break;
	case PLAYER_MAX:
		break;
	default:
		break;
	}


	if ( m_PositionY <= nowShutterPosition)
	{
		switch (m_playerNumber)
		{
		case PLAYER_ONE:
			
			break;
		case PLAYER_TWO:
			
			break;
		default:
			break;
		}
	}
}
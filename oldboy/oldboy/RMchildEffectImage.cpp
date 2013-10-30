#include "stdafx.h"
#include "oldboy.h"
#include "RMchildEffectImage.h"
#include "RMmainLoop.h"

//////////////////////////////////////////////////////////////////
//BitFlag ����													//
//�� ��Ʈ�� � ����Ʈ�� play ȭ�鿡 ����������� ���ƾ� ���� ����Ī		//
//�� ȭ�鿡 �ִ� 8������ ���� ����								    //
//////////////////////////////////////////////////////////////////


CRMchildEffectImage::CRMchildEffectImage(void):
	m_pBitFlag(0)
{
}


CRMchildEffectImage::~CRMchildEffectImage(void)
{
}

void CRMchildEffectImage::Update()
{
	if( m_pBitFlag & 0x80 || m_pBitFlag & 0x08) //1p || 2p ù ��° Ÿ��
	{
		CRMobject::SetVisibleByScene();
		
		if ( CRMmainLoop::GetInstance()->GetNowScene() == m_Scene)
		{
			return;
		}
		
		//������ ��ǥ ������ �����̶� �����Ӻ��� �ٲ���
		for( int deltaTime = 0 ; deltaTime < 4 ; ++ deltaTime)
		{
			m_PositionY -= 3;
			m_PositionX -= 3;
		}

		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;
	}

	//2,3,4 �׸� �߰��� ��
}

void CRMchildEffectImage::HitEffectFlag()
{
	m_pBitFlag = (char) 0x80;
	//�׽�Ʈ�� ��Ʈ Ȯ�� �� �Է� �߰�
}


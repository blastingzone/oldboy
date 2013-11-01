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
	m_pBitFlag((char)0x00)
{
}


CRMchildEffectImage::~CRMchildEffectImage(void)
{
}

void CRMchildEffectImage::Update()
{
	if( m_pBitFlag & 0x80) //1p ù ��° Ÿ��
	{
		CRMobject::SetVisibleByScene();
		
		if ( CRMmainLoop::GetInstance()->GetNowScene() == m_Scene)
		{
			return;
		}
		
		//������ ��ǥ ������ �����̶� �����Ӻ��� �ٲ���
		m_PositionY -= 3;
		m_PositionX -= 3;

		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;

		m_pBitFlag = m_pBitFlag & 0x7f;
	}

	else if( m_pBitFlag & 0x40)
	{
		CRMobject::SetVisibleByScene();

		if ( CRMmainLoop::GetInstance()->GetNowScene() == m_Scene)
		{
			return;
		}

		//������ ��ǥ ������ �����̶� �����Ӻ��� �ٲ���
		m_PositionY -= 3;
		m_PositionX += 3;

		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;

		m_pBitFlag = m_pBitFlag & 0xbf;
	}

	else if( m_pBitFlag & 0x20)
	{
		CRMobject::SetVisibleByScene();

		if ( CRMmainLoop::GetInstance()->GetNowScene() == m_Scene)
		{
			return;
		}

		//������ ��ǥ ������ �����̶� �����Ӻ��� �ٲ���
		m_PositionY -= 3;
		m_PositionX -= 3;

		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;

		m_pBitFlag = m_pBitFlag & 0xdf;
	}

	else if( m_pBitFlag & 0x10)
	{
		CRMobject::SetVisibleByScene();

		if ( CRMmainLoop::GetInstance()->GetNowScene() == m_Scene)
		{
			return;
		}

		//������ ��ǥ ������ �����̶� �����Ӻ��� �ٲ���
		m_PositionY -= 3;
		m_PositionX += 3;

		m_PositionX = DEFAULT_POSITION_X;
		m_PositionY = DEFAULT_POSITION_Y;

		m_pBitFlag = m_pBitFlag & 0xef;
	}

	

	//2p ������ ���·� ��Ʈ ������ �����ؼ� �߰� �� ��(����)
	//1p �׽�Ʈ �� ����
}

void CRMchildEffectImage::HitEffectFlag()
{



	m_pBitFlag = (char) 0x80;
	//�׽�Ʈ�� ��Ʈ Ȯ�� �� �Է� �߰�


}


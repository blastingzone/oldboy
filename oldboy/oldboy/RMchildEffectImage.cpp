#include "stdafx.h"
#include "oldboy.h"
#include "RMchildEffectImage.h"
#include "RMmainLoop.h"
#include "RMchildEffectManager.h"

CRMchildEffectImage::CRMchildEffectImage(void):
	m_EffectTime(0)
{
}


CRMchildEffectImage::~CRMchildEffectImage(void)
{
}

void CRMchildEffectImage::Update()
{
	++m_EffectTime;
	
	if( (CRMchildEffectManager::GetInstance()->GetFlag() & 0x80) || (CRMchildEffectManager::GetInstance()->GetFlag() & 0x20))
	{

		m_EffectTime = 0;
		
		m_PositionX = CRMchildEffectManager::GetInstance()->GetStartPositionX();
		m_PositionY = CRMchildEffectManager::GetInstance()->GetStartPositionY();

		CRMobject::SetVisibleByScene();

		CRMchildEffectManager::GetInstance()->ResetFlag();
	}
	
	if( (CRMchildEffectManager::GetInstance()->GetFlag() & 0x40) || (CRMchildEffectManager::GetInstance()->GetFlag() & 0x01))
	{

		m_EffectTime = 0;

		m_PositionX = CRMchildEffectManager::GetInstance()->GetStartPositionX();
		m_PositionY = CRMchildEffectManager::GetInstance()->GetStartPositionY();

		CRMobject::SetVisibleByScene();

		CRMchildEffectManager::GetInstance()->ResetFlag();
	}

	//2p �߰� �ʿ�
	//�ϴ� 1p���� X ��ǥ Ʋ������ �ذ��ؾ� ��

	m_PositionX -= 10;
	m_PositionY -= 10;

	if(m_EffectTime>10)
	{
		CRMobject::m_Visible = false;
	}

	return;
}
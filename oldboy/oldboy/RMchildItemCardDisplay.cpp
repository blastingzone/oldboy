#include "stdafx.h"
#include "RMchildItemCardDisplay.h"
#include "RMmacro.h"
#include "RMitemManager.h"


CRMchildItemCardDisplay::CRMchildItemCardDisplay(void)
{
}


CRMchildItemCardDisplay::~CRMchildItemCardDisplay(void)
{
}

void CRMchildItemCardDisplay::Update()
{
	//아이템이 발동되면 해당 카드가 떠 있도록 함
	if ( CRMitemManager::GetInstance()->GetActivatedItem(m_playerNumber) )
	{
		SetVisibleByScene();
	}

	//아이템 파티클 시스템

}

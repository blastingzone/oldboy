﻿#include "stdafx.h"
#include "RMchildItemCardDisplay.h"
#include "RMmacro.h"
#include "RMitemManager.h"


CRMchildItemCardDisplay::CRMchildItemCardDisplay(void):
	m_cardTimeToLive(0)
{
}


CRMchildItemCardDisplay::~CRMchildItemCardDisplay(void)
{
}

void CRMchildItemCardDisplay::Update()
{
	m_cardTimeToLive++;

	SetVisibleByScene();



	//아이템이 발동되면 해당 카드가 떠 있도록 함
	if ( (CRMitemManager::GetInstance()->GetActivatedItem(m_playerNumber) == ITEM_TYPE_NONE) || m_cardTimeToLive>1000 )
	{
		m_Visible = false;
	}

}

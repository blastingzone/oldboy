#pragma once
#include "RMenumSet.h"

class CRMchildEffectManager
{
	SINGLETON(CRMchildEffectManager);

private:
	CRMchildEffectManager(void);
	~CRMchildEffectManager(void);

public:
	void	SetFlag( PlayerNumber targetPlayer , float m_PositionX, float m_PositionY );
	void	ResetFlag( int highMask );

	void	GetStartPosition( PlayerNumber targetPlayer, float* x, float* y );
	char	GetFlag() { return m_BitFlag; }

private:
	int		m_FlagSetter1P; //� ��Ʈ �����ǿ� ������ ��ⷯ �������� Ȯ��
	int		m_FlagSetter2P; //� ��Ʈ �����ǿ� ������ ��ⷯ �������� Ȯ��
	char	m_BitFlag;
	float	m_Effect1PStartPositionX;
	float	m_Effect1PStartPositionY;
	float	m_Effect2PStartPositionX;
	float	m_Effect2PStartPositionY;
};


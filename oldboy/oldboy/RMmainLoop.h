#pragma once
#include "oldboy.h"

class CRMmainLoop
{
private:
	CRMmainLoop(void);
	~CRMmainLoop(void);


public:
	// �̱��� ���� method
	static CRMmainLoop*	GetInstance();
	static void			ReleaseInstance();

	// �ʱ�ȭ �� ���ѷ���
	HRESULT					Init();
	void					RunMessageLoop();
	
	HWND					GetHwnd(){ return m_Hwnd; }				// ������ �ڵ� ��ȯ
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	// ��ü ���̵� ��� �����ϵ��� static���� ��


private:
	HWND	m_Hwnd;
	
	UINT	m_NowTime;
	UINT	m_PrevTime;
	UINT	m_ElapsedTime;
	UINT	m_Fps;

	//�̱��� ���� member ����
	static CRMmainLoop* m_pInstance;
};


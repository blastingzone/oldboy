#pragma once
#include "oldboy.h"

class CRMmainLoop
{
private:
	CRMmainLoop(void);
	~CRMmainLoop(void);

//�̱��� ���� method
public:
	static CRMmainLoop*	GetInstance();
	static void			ReleaseInstance();


public:
	void					RunMessageLoop();
	HRESULT					Init();
	
	HWND					GetHwnd(){return m_Hwnd;}
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM); //��ü ���̵� ��� �����ϵ��� static���� ��


private:
	HWND m_Hwnd;
	
	UINT m_NowTime;
	UINT m_PrevTime;
	UINT m_ElapsedTime;
	UINT m_Fps;

//�̱��� ���� member ����
private:
	static CRMmainLoop* m_pInstance;
};


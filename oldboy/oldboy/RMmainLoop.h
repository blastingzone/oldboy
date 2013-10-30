#pragma once
#include "RMenumSet.h"

class CRMmainLoop
{
	SINGLETON(CRMmainLoop);
private:
	CRMmainLoop(void);
	~CRMmainLoop(void);

public:
	// �ʱ�ȭ �� ���ѷ���
	HRESULT					CreateMainLoopWindow();
	void					RunMessageLoop();

	// �� ����
	SceneType				GetNowScene() { return m_SceneType; }
	void					GoNextScene();
	
	HWND					GetHwnd() { return m_Hwnd; }				// ������ �ڵ� ��ȯ
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	// ��ü ���̵� ��� �����ϵ��� static���� ��

private:

	// �ӽ� �׽�Ʈ �Լ�
	void	TestSound();
	void	TestKeyboard();

	void	CreateObject();

	HWND	m_Hwnd;
	
	UINT	m_NowTime;
	UINT	m_PrevTime;
	UINT	m_ElapsedTime;
	UINT	m_Fps;

	UINT	m_FpsCheckTime;

	SceneType		m_SceneType;
};


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
	HRESULT					GoNextScene();
	HRESULT					GoPrevScene();

	HWND					GetHwnd() { return m_Hwnd; }				// ������ �ڵ� ��ȯ
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	// ��ü ���̵� ��� �����ϵ��� static���� ��

private:

	void	FindMusicData();

	// �ӽ� �׽�Ʈ �Լ�
	void	TestSound();
	HRESULT	TestKeyboard();

	HRESULT	CreateObject();


private:

	HWND							m_Hwnd;
	
	UINT							m_NowTime;
	UINT							m_PrevTime;
	UINT							m_ElapsedTime;
	UINT							m_Fps;

	UINT							m_FpsCheckTime;

	SceneType						m_SceneType;

	std::vector<std::string>		m_MusicVector;

	std::string						m_PlayMusicName;
};


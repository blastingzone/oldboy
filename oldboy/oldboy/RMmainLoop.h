#pragma once
#include "oldboy.h"
#include "RMsound.h"
#include "RMEnumSceneType.h"

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

	// �� ����
	SCENE_TYPE				GetNowScene() { return m_SceneType; }
	void					GoNextScene();
	
	HWND					GetHwnd(){ return m_Hwnd; }				// ������ �ڵ� ��ȯ
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);	// ��ü ���̵� ��� �����ϵ��� static���� ��

private:
	void	CreateObject();

	HWND	m_Hwnd;
	
	UINT	m_NowTime;
	UINT	m_PrevTime;
	UINT	m_ElapsedTime;
	UINT	m_Fps;

	SCENE_TYPE		m_SceneType;

	//�̱��� ���� member ����
	static CRMmainLoop* m_pInstance;


	void testSound();
};


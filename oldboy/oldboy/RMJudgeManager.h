#pragma once
class CRMjudgeManager
{
	SINGLETON(CRMjudgeManager);

public:
	CRMjudgeManager(void);
	~CRMjudgeManager(void);



	// �̱���
	// static CRMjudgeManager*		GetInstance();
	// static void					ReleaseInstance();

	//��Ʈ ����
	void						StartNote( PlayerNumber player );
	
	//��Ʈ ����
	void						JudgeNote();

private:
	//static CRMjudgeManager*		m_pInstance;
};


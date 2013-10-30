#pragma once
class CRMJudgeManager
{
public:
	CRMJudgeManager(void);
	~CRMJudgeManager(void);

	// �̱���
	static CRMJudgeManager*		GetInstance();
	static void					ReleaseInstance();

	//��Ʈ ����
	void						StartNote(PLAYER_NUMBER player);
	
	//��Ʈ ����
	void						JudgeNote();

private:
	static CRMJudgeManager*		m_pInstance;

};


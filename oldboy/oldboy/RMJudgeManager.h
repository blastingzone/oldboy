#pragma once
#include "RMobject.h"
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
	void						StartNote( PlayerNumber player , ObjectType objectType );
	
	//��Ʈ ����
	void						JudgeNote();

private:
	void						DeleteNote( std::list<CRMobject*>* objectList );
};


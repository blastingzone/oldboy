#pragma once

class CRMobject;

class CRMjudgeManager
{
	SINGLETON(CRMjudgeManager);

public:
	CRMjudgeManager(void);
	~CRMjudgeManager(void);

	//��Ʈ ����
	void						StartNote( PlayerNumber player , ObjectType objectType );
	
	//��Ʈ ����
	void						JudgeNote();

private:
	void						DeleteNote( std::list<CRMobject*>* objectList );

};


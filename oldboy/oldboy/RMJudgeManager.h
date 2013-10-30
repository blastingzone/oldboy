#pragma once

class CRMobject;

class CRMjudgeManager
{
	SINGLETON(CRMjudgeManager);

private:
	CRMjudgeManager(void);
	~CRMjudgeManager(void);

public:
	//��Ʈ ����
	void						StartNote( PlayerNumber player , ObjectType objectType );
	
	//��Ʈ ����
	void						JudgeNote();
	bool						IsKeyInputRight( CRMobject* note , std::list<CRMobject*>* objectList );

private:
	void						DeleteNote( std::list<CRMobject*>* objectList );

};


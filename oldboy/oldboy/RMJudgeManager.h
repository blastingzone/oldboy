#pragma once

#include "RMenumSet.h"

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
	bool						IsKeyInputRight( CRMobject* note , PlayerNumber player );

private:
	void						DeleteNote( std::list<CRMobject*>* objectList );
	void						PrintScore( PlayerNumber player );

	JudgeType					m_Player1Judge;
	JudgeType					m_Player2Judge;
};


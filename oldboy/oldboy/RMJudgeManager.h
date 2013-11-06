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
	void						JudgeNoteByPlayer( PlayerNumber playerNumber );
	void						PrintScore( PlayerNumber player, JudgeType judgeType );

	JudgeType					m_Player1Judge;
	JudgeType					m_Player2Judge;
};


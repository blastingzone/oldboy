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
	void						StartNote( PlayerNumber player , ObjectType objectType ) const;
	
	//��Ʈ ����
	void						JudgeNote() const;
	

private:
	void						JudgeNoteByPlayer( PlayerNumber playerNumber ) const;
	void						PrintScore( PlayerNumber player, JudgeType judgeType ) const;
	bool						IsKeyInputRight( CRMobject* note , PlayerNumber player ) const;
};


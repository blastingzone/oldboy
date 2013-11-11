#pragma once

class CRMlabel;

class CRMlabelManager
{
	SINGLETON(CRMlabelManager);

private:
	CRMlabelManager(void);
	~CRMlabelManager(void);

public:
	// ���丮 �ʱ�ȭ
 	HRESULT						CreateFactory();
	IDWriteFactory*				GetTextFactory() { return m_DWriteFactory; }

	void						AddLabel( std::wstring key , CRMlabel* label );

	// CRMobjectManager���� friend class�� �� �ʿ� ����
	std::map<std::wstring, CRMlabel*>	m_LabelMap;

private:
	void								CheckError(HRESULT);

	IDWriteFactory*						m_DWriteFactory;
};


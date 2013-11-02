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

	std::map<std::wstring, CRMlabel*>*	GetLabelMap() { return &m_LabelMap; }

private:
	void								CheckError(HRESULT);

	IDWriteFactory*						m_DWriteFactory;
	std::map<std::wstring, CRMlabel*>	m_LabelMap;
};


#pragma once

class CRMlabel;

class CRMlabelManager
{
	SINGLETON(CRMlabelManager);
	friend class CRMobjectManager;

private:
	CRMlabelManager(void);
	~CRMlabelManager(void);

public:
	// ���丮 �ʱ�ȭ
 	HRESULT						CreateFactory();
	IDWriteFactory*				GetTextFactory() const { return m_DWriteFactory; } //SM9: const �ٿ�����..

	void						AddLabel(const std::wstring& key , CRMlabel* label ); //SM9: ���⵵ const


	
	//std::map<std::wstring, CRMlabel*>	m_LabelMap;

private:
	void								CheckError(HRESULT);

	IDWriteFactory*						m_DWriteFactory;

	// CRMobjectManager���� friend class�� �� �ʿ� ����
	// �׸��� CRMobjectManager���� �̰��� �����ϱ� ������ private�ȿ� friend class CRMobjectManager; ��� ����� �Ǵ°�...

	std::map<std::wstring, CRMlabel*>	m_LabelMap;
};


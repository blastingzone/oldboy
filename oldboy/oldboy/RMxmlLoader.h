#pragma once

class CRMmusicData;

class CRMxmlLoader
{
	SINGLETON(CRMxmlLoader);

public:
	CRMxmlLoader(void);
	~CRMxmlLoader(void);

	void		TestXML();
private:
	//           �����̸�  ���ǰ�ü
	std::map<std::string, CRMmusicData*>	m_MusicDataMap;
};


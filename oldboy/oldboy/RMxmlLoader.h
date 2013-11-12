#pragma once

class CRMmusicData;

class CRMxmlLoader
{
	SINGLETON(CRMxmlLoader);

public:
	CRMxmlLoader(void);
	~CRMxmlLoader(void);
	
	void				LoadMusicData(const std::string& folderName );
	CRMmusicData*		GetMusicData(const std::string& folderName ) { return m_MusicDataMap[folderName]; } //SM9: �̷��� const ��߰���?
private:
	//           �����̸�  ���ǰ�ü
	std::map<std::string, CRMmusicData*>	m_MusicDataMap;
};


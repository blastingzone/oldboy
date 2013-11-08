#pragma once

class CRMmusicData;

class CRMxmlLoader
{
	SINGLETON(CRMxmlLoader);

public:
	CRMxmlLoader(void);
	~CRMxmlLoader(void);
	
	void				LoadMusicData( std::string folderName );
	CRMmusicData*		GetMusicData( std::string folderName ) { return m_MusicDataMap[folderName]; }
private:
	//           �����̸�  ���ǰ�ü
	std::map<std::string, CRMmusicData*>	m_MusicDataMap;
};


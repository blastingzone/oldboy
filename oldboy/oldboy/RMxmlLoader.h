#pragma once



class CRMmusicData;
class CRMnoteData;

class CRMxmlLoader
{
	SINGLETON(CRMxmlLoader);


public:
	CRMxmlLoader(void);
	~CRMxmlLoader(void);
	
	HRESULT				LoadMusicData( const std::string& folderName );
	HRESULT				LoadNoteData( const std::string& folderName );
	CRMnoteData*		GetNoteFirst();
	HRESULT				DeleteNoteFirst();

	CRMmusicData*		GetMusicData( const std::string& folderName ) { return m_MusicDataMap[folderName]; }
private:
	//           �����̸�  ���ǰ�ü
	std::map<std::string, CRMmusicData*>	m_MusicDataMap;
	std::list<CRMnoteData*>					m_NoteList;
};

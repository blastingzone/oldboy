#pragma once
#include "RMenumSet.h"

class CRMimage;

class CRMresourceManager
{
	SINGLETON(CRMresourceManager);

private:
	CRMresourceManager(void);
	~CRMresourceManager(void);
	
public:
	// ���丮 �ʱ�ȭ
	HRESULT						CreateFactory();
	IWICImagingFactory*			GetImageFactory() const { return m_pWICFactory; } //SM9: �̰͵�  const ���̴°� ������?

	HRESULT						CreateTexture();
	HRESULT						CreateTexture( const std::string& folderName );

	CRMimage*					GetTexture( ObjectType key ) { return m_TextureMap[key]; } 
	
private:
	void								LogError(HRESULT);
	void								InitializeMap();
	std::wstring						GetFilePath( const std::string& folderName, const std::string& resourceName );

	IWICImagingFactory*					m_pWICFactory;
	std::map<ObjectType, CRMimage*>		m_TextureMap;
};


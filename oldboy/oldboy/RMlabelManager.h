#pragma once

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
// 
// 	HRESULT						CreateTexture();
// 	CRMimage*					GetTexture( ObjectType key ) { return m_TextureMap[key]; }

private:
	void						CheckError(HRESULT);

	IDWriteFactory*				m_DWriteFactory;

	// 	IDWriteTextFormat*		m_TextFormat;
	// 	ID2D1SolidColorBrush*	m_Brush;
	// �� �ΰ��� �� �󺧷�.
};


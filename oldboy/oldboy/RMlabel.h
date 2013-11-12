#pragma once
#include "RMobject.h"

class CRMlabel :
	public CRMobject
{
public:
	CRMlabel(void);
	~CRMlabel(void);

	void		CreateLabel( std::wstring key, std::wstring string, wchar_t* fontFace, float fontSize );

	virtual void	Update();
	virtual void	Render();

	wchar_t*	GetString() { return m_String; }
	wchar_t*	GetFontFace() { return m_FontFace; }
	float		GetFontSize() { return m_FontSize; }
	float		GetRed() { return m_ColorR; }
	float		GetGreen() { return m_ColorG; }
	float		GetBlue() { return m_ColorB; }
	float		GetOpacity() { return m_Opacity; }
	bool		IsItalic() { return m_Italic; }
	bool		IsBold() { return m_Bold; }

	// void		SetString( wchar_t* string ) { m_String = string; }
	void		SetFontSize( float fontsize ) { m_FontSize = fontsize; }
	void		SetFontFace( wchar_t* fontface ) { m_FontFace = fontface; }
	void		SetBold( bool bold ) { m_Bold = bold; }
	void		SetItalic( bool italic ) { m_Italic = italic; }
	void		SetRed( float r ) { m_ColorR = r; }
	void		SetGreen( float g ) { m_ColorG = g; }
	void		SetBlue( float b ) { m_ColorB = b; }
	void		SetColor( float r, float g, float b ) { m_ColorR = r; m_ColorG = g; m_ColorB = b; }
	void		SetOpacity( float opacity ) { m_Opacity = opacity; }
	void		SetRGBA( float r, float g, float b, float a ) { m_ColorR = r; m_ColorG = g; m_ColorB = b; m_Opacity = a; }

private:
	void		SetTextFormat();

	IDWriteTextFormat*		m_TextFormat;
	ID2D1SolidColorBrush*	m_Brush;

	wchar_t*	m_FontFace;
	// wchar_t*	m_String;
	wchar_t		m_String[255]; //SM9: 255 이런거 define으로 빼던가 (나중에 버퍼 오버플로의 주범이 될 수있는 코드) 그냥 string 쓰던가..

	float		m_FontSize;
	float		m_ColorR, m_ColorG, m_ColorB;
	float		m_Opacity;
	bool		m_Bold;
	bool		m_Italic;
};


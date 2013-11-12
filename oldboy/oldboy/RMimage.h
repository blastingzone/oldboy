#pragma once

class CRMimage
{
public:
	CRMimage(void);
	~CRMimage(void);

public:
	HRESULT			CreateImage( const std::wstring& path );

	float			GetWidth() const { return m_Width; } //SM9: �̷��� ��� ������ ���¸� �ٲ��� �ʴ� �Լ��� ��� �ִ��� const�� �ٿ���
	float			GetHeight() const { return m_Height; }

	ID2D1Bitmap*	Get2DImg() const { return m_D2DImg; }

private:
	ID2D1Bitmap*	m_D2DImg;

private:
	float			m_Width;
	float			m_Height;

};


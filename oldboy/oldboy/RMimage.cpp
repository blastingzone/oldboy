#include "stdafx.h"
#include "RMimage.h"
#include "RMresourceManager.h"
#include "RMrender.h"


CRMimage::CRMimage(void) :
	m_width(0.0),
	m_height(0.0),
	m_2DImg(nullptr)
{
}

CRMimage::~CRMimage(void)
{
	SafeRelease(m_2DImg);
	// �ش� �κ� �������� ���ؼ� �޸� ������ �߻��Ͽ���
}

HRESULT CRMimage::Init( std::wstring path )
{
	IWICImagingFactory*	imageFactory = CRMresourceManager::GetInstance()->GetImageFactory();
	IWICBitmapDecoder* bitmapDecoder = nullptr;
	HRESULT hr = S_FALSE;

	// ���ڴ� ����
	hr = imageFactory->CreateDecoderFromFilename( path.c_str(), nullptr, GENERIC_READ, 
		WICDecodeMetadataCacheOnDemand, &bitmapDecoder );

	if(FAILED(hr))
		return hr;

	// ���ڴ����� ������ ����
	IWICBitmapFrameDecode* bitmapFrameDecode = nullptr;
	hr = bitmapDecoder->GetFrame( 0, &bitmapFrameDecode );

	if(FAILED(hr))
	{
		SafeRelease(bitmapDecoder);
		return hr;
	}

	IWICFormatConverter*	formatConverter = nullptr;

	// �������� ������� ������ ����
	hr = imageFactory->CreateFormatConverter( &formatConverter );

	if(FAILED(hr))
	{
		SafeRelease(bitmapFrameDecode);
		SafeRelease(bitmapDecoder);
		return hr;
	}

	hr = formatConverter->Initialize( bitmapFrameDecode, 
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, nullptr, 0.0f,
		WICBitmapPaletteTypeCustom );

	if(FAILED(hr))
	{
		SafeRelease(bitmapFrameDecode);
		SafeRelease(bitmapDecoder);
	}

	hr = CRMrender::GetInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap(formatConverter, nullptr, &m_2DImg);

	if(FAILED(hr))
	{
		SafeRelease(bitmapFrameDecode);
		SafeRelease(bitmapDecoder);
	}

	m_width = m_2DImg->GetSize().width;
	m_height = m_2DImg->GetSize().height;

	SafeRelease( bitmapFrameDecode );
	SafeRelease( bitmapDecoder );

	return hr;
}

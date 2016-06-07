#include "Common.h"
#include "ThumbnailProvider.h"
#include "gdiplus.h"

using namespace Gdiplus;
CThumbnailProvider::CThumbnailProvider()
{
    DllAddRef();
    m_cRef = 1;
    m_pSite = NULL;
}


CThumbnailProvider::~CThumbnailProvider()
{
    if (m_pSite)
    {
        m_pSite->Release();
        m_pSite = NULL;
    }
    DllRelease();
}


STDMETHODIMP CThumbnailProvider::QueryInterface(REFIID riid,
                                                void** ppvObject)
{
    static const QITAB qit[] = 
    {
        QITABENT(CThumbnailProvider, IInitializeWithStream),
        QITABENT(CThumbnailProvider, IThumbnailProvider),
        QITABENT(CThumbnailProvider, IObjectWithSite),
        {0},
    };
    return QISearch(this, qit, riid, ppvObject);
}


STDMETHODIMP_(ULONG) CThumbnailProvider::AddRef()
{
    LONG cRef = InterlockedIncrement(&m_cRef);
    return (ULONG)cRef;
}


STDMETHODIMP_(ULONG) CThumbnailProvider::Release()
{
    LONG cRef = InterlockedDecrement(&m_cRef);
    if (0 == cRef)
        delete this;
    return (ULONG)cRef;
}


STDMETHODIMP CThumbnailProvider::Initialize(IStream *pstm, 
                                            DWORD grfMode)
{
    return S_OK;
}


STDMETHODIMP CThumbnailProvider::GetThumbnail(UINT cx, 
                                              HBITMAP *phbmp, 
                                              WTS_ALPHATYPE *pdwAlpha)
{
	*phbmp = NULL; 
	*pdwAlpha = WTSAT_UNKNOWN;
	ULONG_PTR token;
	GdiplusStartupInput input;
	if (Ok == GdiplusStartup(&token, &input, NULL))
	{
		//gcImage.LogBuffer();
		Bitmap * pBitmap = new Bitmap(188, 141);
		if( pBitmap )
		{
			Graphics xGraphics( pBitmap );
			Font xFont( L"Arial", 12, FontStyleRegular, UnitPoint );
			SolidBrush xBrush( Color( 0, 0, 0) );
			xGraphics.DrawString(L"Hello!", 6, &xFont, PointF(0.0f,0.0f), &xBrush );
			Color color(255, 0, 0);
			pBitmap->GetHBITMAP(color, phbmp);
		}
	}
	GdiplusShutdown(token);
	if( *phbmp != NULL )
		return NOERROR;
	return E_NOTIMPL;

}


STDMETHODIMP CThumbnailProvider::GetSite(REFIID riid, 
                                         void** ppvSite)
{
    if (m_pSite)
    {
        return m_pSite->QueryInterface(riid, ppvSite);
    }
    return E_NOINTERFACE;
}


STDMETHODIMP CThumbnailProvider::SetSite(IUnknown* pUnkSite)
{
    if (m_pSite)
    {
        m_pSite->Release();
        m_pSite = NULL;
    }

    m_pSite = pUnkSite;
    if (m_pSite)
    {
        m_pSite->AddRef();
    }
    return S_OK;
}


STDAPI CThumbnailProvider_CreateInstance(REFIID riid, void** ppvObject)
{
    *ppvObject = NULL;

    CThumbnailProvider* ptp = new CThumbnailProvider();
    if (!ptp)
    {
        return E_OUTOFMEMORY;
    }

    HRESULT hr = ptp->QueryInterface(riid, ppvObject);
    ptp->Release();
    return hr;
}
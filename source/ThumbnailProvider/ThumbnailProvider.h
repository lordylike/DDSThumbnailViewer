#pragma once

class CThumbnailProvider : public IThumbnailProvider, IObjectWithSite, IInitializeWithStream
{
private:
    LONG m_cRef;
    IUnknown* m_pSite;

    ~CThumbnailProvider();

public:
    CThumbnailProvider();

    //  IUnknown methods
    STDMETHOD(QueryInterface)(REFIID, void**);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    //  IInitializeWithSteam methods
    STDMETHOD(Initialize)(IStream*, DWORD);

    //  IThumbnailProvider methods
    STDMETHOD(GetThumbnail)(UINT, HBITMAP*, WTS_ALPHATYPE*);

    //  IObjectWithSite methods
    STDMETHOD(GetSite)(REFIID, void**);
    STDMETHOD(SetSite)(IUnknown*);
};
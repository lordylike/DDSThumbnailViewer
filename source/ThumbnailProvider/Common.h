#pragma once

#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <thumbcache.h>
#include <strsafe.h>

STDAPI_(ULONG) DllAddRef();
STDAPI_(ULONG) DllRelease();
STDAPI_(HINSTANCE) DllInstance();

// {68BF0019-79AB-4e7f-9500-AA3B5227DFE6}
//#define szCLSID_SampleThumbnailProvider L"{68BF0019-79AB-4e7f-9500-AA3B5227DFE6}"
//DEFINE_GUID(CLSID_SampleThumbnailProvider, 0x68bf0019, 0x79ab, 0x4e7f, 0x95, 0x0, 0xaa, 0x3b, 0x52, 0x27, 0xdf, 0xe6);

// {C950B823-FB52-434E-9377-E833C9806E6E}
DEFINE_GUID(CLSID_SampleThumbnailProvider,
	0xc950b823, 0xfb52, 0x434e, 0x93, 0x77, 0xe8, 0x33, 0xc9, 0x80, 0x6e, 0x6e);
#define szCLSID_SampleThumbnailProvider L"{C950B823-FB52-434E-9377-E833C9806E6E}"
#pragma once

#include "pch.h"
#include <Windows.h>


inline void ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		throw Platform::Exception::CreateException(hr);
	}
}

template<class T> inline void SafeRelease(T **ppT) {
	if(*ppT) {
		(*ppT)->Release();
		*ppT = NULL;
	}
}

#if _DEBUG
inline void dbgf(const wchar_t* format, ...) {
	va_list list;
	va_start(list, format);

	UINT32 len = _vscwprintf(format, list); // add space for "\r\n\0"
	wchar_t* buf = new wchar_t[len];
	vswprintf(buf, len, format, list);

	OutputDebugStringW(buf);
	delete [] buf;
	OutputDebugStringW(L"\r\n");
}
#else
inline void dbgf(...) {
}
#endif
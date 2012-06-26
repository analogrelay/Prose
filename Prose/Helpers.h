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
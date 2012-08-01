#pragma once

#include "pch.h"
#include <Windows.h>

#if _DEBUG
inline void dbgf(const wchar_t* format, ...) {
	va_list list;

	va_start(list, format);
	UINT32 len = _vscwprintf(format, list) + 1; // add space for "\r\n\0"
	va_end(list);
	
	va_start(list, format);
	wchar_t* buf = new wchar_t[len];
	vswprintf_s(buf, len, format, list);
	va_end(list);

	OutputDebugStringW(buf);
	delete [] buf;
	OutputDebugStringW(L"\r\n");
}
#else
inline void dbgf(...) {
}
#endif

// Helpful equality comparers
bool operator==(Windows::UI::Text::FontWeight left, Windows::UI::Text::FontWeight right);
bool operator!=(Windows::UI::Text::FontWeight left, Windows::UI::Text::FontWeight right);

namespace Prose {
	Windows::UI::Xaml::DependencyProperty^ RegisterDP(
		Platform::String^ name,
		Platform::Type^ type,
		Platform::Type^ owner);
	Windows::UI::Xaml::DependencyProperty^ RegisterDP(
		Platform::String^ name,
		Platform::Type^ type,
		Platform::Type^ owner,
		Platform::Object^ defaultValue);
	Windows::UI::Xaml::DependencyProperty^ RegisterDP(
		Platform::String^ name,
		Platform::Type^ type,
		Platform::Type^ owner,
		Windows::UI::Xaml::PropertyChangedCallback^ changedCallback);
	Windows::UI::Xaml::DependencyProperty^ RegisterDP(
		Platform::String^ name,
		Platform::Type^ type,
		Platform::Type^ owner,
		Platform::Object^ defaultValue,
		Windows::UI::Xaml::PropertyChangedCallback^ changedCallback);

	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw Platform::Exception::CreateException(hr);
		}
	}
}
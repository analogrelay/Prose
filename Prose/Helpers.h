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
	generic<typename T>
	public interface class INullable {
		property bool HasValue { bool get(); }
		property T Value { T get(); }
	};

	template<typename T>
	private ref class Nullable sealed :
		public INullable<T>
	{
	public:
		virtual property bool HasValue { bool get() { return _hasValue; } }
		virtual property T Value { 
			T get() { 
				if(!_hasValue) {
					throw ref new Platform::NullReferenceException();
				}
				return _value; 
			} 
		}

		Nullable(void) : _hasValue(false) { };
		Nullable(T value) : _hasValue(true), _value(value) { };

	private:
		bool _hasValue;
		T _value;
	};
}
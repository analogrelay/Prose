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

#define _CORE_DEPENDENCY_PROPERTY(Name) private: \
	static Windows::UI::Xaml::DependencyProperty^ _ ## Name ## Property; \
public: \
	static property Windows::UI::Xaml::DependencyProperty^ Name ## Property { Windows::UI::Xaml::DependencyProperty^ get() { return _ ## Name ## Property; } }


#define DEPENDENCY_PROPERTY(Name, Type) _CORE_DEPENDENCY_PROPERTY(Name) \
	property Type^ Name { \
		Type^ get() { return (Type^)GetValue(Name ## Property); } \
		void set(Type^ value) { SetValue(Name ## Property, value); } \
	}

#define DEPENDENCY_PROPERTY_VAL(Name, Type) _CORE_DEPENDENCY_PROPERTY(Name) \
	property Type Name { \
		Type get() { return (Type)GetValue(Name ## Property); } \
		void set(Type value) { SetValue(Name ## Property, value); } \
	}

#define IMPLEMENT_DP(Owner, Name, Type) Windows::UI::Xaml::DependencyProperty^ Owner::_ ## Name ## Property = Windows::UI::Xaml::DependencyProperty::Register( \
	"Name", Type::typeid, Owner::typeid, ref new Windows::UI::Xaml::PropertyMetadata(nullptr))

#define NOTIFY_PROPERTY(Type, Name) private: \
	Type _ ## Name; \
public: \
	property Type Name { \
		Type get() { return _ ## Name; }; \
		void set(Type value) { \
			if(_ ## Name != value) { \
				_ ## Name = value; \
				OnPropertyChanged(L"Name"); \
			} \
		} \
	}
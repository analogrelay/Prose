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

#define _BACKING_FIELD(Type, Name) Type _ ## Name;
#define _NULLITY_FIELD_NAME(Name) _Is ## Name ## Set
#define _NULLITY_FIELD(Type, Name) bool _NULLITY_FIELD_NAME(Name);
#define _NULLITY_PROPERTY(Type, Name) property bool Is ## Name ## Set { bool get() { return _NULLITY_FIELD_NAME(Name); } };
#define _GETTER(Type, Name) Type get() { return _ ## Name; };
#define _SETTER(Type, Name) void set(Type value) { _ ## Name = value; };
#define _NOTIFY_PROPERTY_SETTER_BODY(Name) if(_ ## Name != value) { \
	_ ## Name = value; \
	OnPropertyChanged(L"Name"); \
}

#define PROPERTY(Type, Name) private: \
	_BACKING_FIELD(Type, Name) \
public: \
	property Type Name { \
		_GETTER(Type, Name) \
		_SETTER(Type, Name) \
	}

#define NOTIFY_PROPERTY(Type, Name) private: \
	_BACKING_FIELD(Type, Name) \
public: \
	property Type Name { \
		_GETTER(Type, Name) \
		void set(Type value) { \
			_NOTIFY_PROPERTY_SETTER_BODY(Name) \
		} \
	}

#define NOTIFY_NULLABLE_PROPERTY(Type, Name) private: \
	_BACKING_FIELD(Type, Name) \
	_NULLITY_FIELD(Type, Name) \
public: \
	property Type Name { \
		_GETTER(Type, Name) \
		void set(Type value) { \
			_NULLITY_FIELD_NAME(Name) = true; \
			_NOTIFY_PROPERTY_SETTER_BODY(Name) \
		} \
	} \
internal: \
	_NULLITY_PROPERTY(Type, Name)

#define NULLABLE_PROPERTY(Type, Name) private: \
	_BACKING_FIELD(Type, Name) \
	_NULLITY_FIELD(Type, Name) \
public: \
	property Type Name { \
		_GETTER(Type, Name) \
		void set(Type value) { \
			_NULLITY_FIELD_NAME(Name) = true; \
			_ ## Name = value; \
		} \
	} \
internal: \
	_NULLITY_PROPERTY(Type, Name)
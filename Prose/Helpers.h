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

	template<typename T>
	private class Nullable sealed {
	public:
		bool HasValue() const { return _hasValue; }
		T const& GetValue() const {
			if(!_hasValue) {
				throw ref new Platform::NullReferenceException();
			}
			return _value;
		}

		Nullable(void) : _hasValue(false) { }
		Nullable(const T& value) : _hasValue(true), _value(value) { }
		Nullable(nullptr_t value) : _hasValue(false) { }

		operator T const&(void) const {
			if(!_hasValue) {
				throw ref new Platform::NullReferenceException();
			}
			return _value;
		}
	private:
		bool _hasValue;
		T _value;
	};

	template<typename T>
	bool operator==(Nullable<T> const& left, Nullable<T> const& right) {
		return (!left.HasValue() && !right.HasValue()) ||
			(left.GetValue() == right.GetValue());
	}

	template<typename T>
	bool operator==(nullptr_t const& left, Nullable<T> const& right) {
		return !right.HasValue();
	}

	template<typename T>
	bool operator==(Nullable<T> const& left, nullptr_t const& right) {
		return !left.HasValue();
	}

	template<typename T>
	bool operator!=(Nullable<T> const& left, Nullable<T> const& right) {
		return !(left == right);
	}

	template<typename T>
	bool operator!=(nullptr_t const& left, Nullable<T> const& right) {
		return !(left == right);
	}

	template<typename T>
	bool operator!=(Nullable<T> const& left, nullptr_t const& right) {
		return !(left == right);
	}

	template<typename T>
	bool isnull(T const& item) {
		return item == nullptr;
	}

	template<>
	bool isnull<Windows::UI::Text::FontStretch>(Windows::UI::Text::FontStretch const& item);
}
#pragma once

#include <limits>

namespace Prose {
	public ref class TextFormat sealed :
		Windows::UI::Xaml::DependencyObject
	{
	public:
		DEPENDENCY_PROPERTY(Windows::UI::Xaml::Media::FontFamily^, FontFamily);
		DEPENDENCY_PROPERTY(double, FontSize);
		DEPENDENCY_PROPERTY(Windows::UI::Xaml::Media::Brush^, Foreground);
		DEPENDENCY_PROPERTY(Windows::UI::Text::FontStretch, FontStretch);
		DEPENDENCY_PROPERTY(Windows::UI::Text::FontStyle, FontStyle);
		DEPENDENCY_PROPERTY(Windows::UI::Text::FontWeight, FontWeight);
		DEPENDENCY_PROPERTY(bool, Strikethrough);
		DEPENDENCY_PROPERTY(bool, Underline);

		TextFormat(void) { }

	internal:
		void ApplyDeviceIndependent(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 start, UINT32 length);
		void ApplyDeviceDependent(Microsoft::WRL::ComPtr<ID2D1RenderTarget> target, Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 offset, UINT32 length);

	private:
		Microsoft::WRL::ComPtr<ID2D1Brush> ConvertBrush(Microsoft::WRL::ComPtr<ID2D1RenderTarget> target, Windows::UI::Xaml::Media::Brush^ xamlBrush);
	};
}
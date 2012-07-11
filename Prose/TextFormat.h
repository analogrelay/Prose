#pragma once

#include <limits>
#include <list>

namespace Prose {
	public ref class TextFormat sealed :
		public Windows::UI::Xaml::DependencyObject
	{
	public:
		DEPENDENCY_PROPERTY(Windows::UI::Xaml::Media::FontFamily^, FontFamily);
		DEPENDENCY_PROPERTY(double, FontSize);
		DEPENDENCY_PROPERTY(Windows::UI::Xaml::Media::Brush^, Foreground);
		DEPENDENCY_PROPERTY(Windows::UI::Text::FontStretch, FontStretch);
		DEPENDENCY_PROPERTY(Windows::UI::Text::FontStyle, FontStyle);
		DEPENDENCY_PROPERTY(Windows::UI::Text::FontWeight, FontWeight);
		DEPENDENCY_PROPERTY(bool, HasStrikethrough);
		DEPENDENCY_PROPERTY(bool, HasUnderline);

		TextFormat(void) { }

		TextFormat^ MergeWith(TextFormat^ overridingCopy);
	internal:
		void ApplyDeviceIndependent(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 start, UINT32 length);
		void ApplyDeviceDependent(Microsoft::WRL::ComPtr<ID2D1RenderTarget> target, Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 offset, UINT32 length);

		static TextFormat^ MergeSequence(std::list<TextFormat^>& list);
	private:
		Microsoft::WRL::ComPtr<ID2D1Brush> ConvertBrush(Microsoft::WRL::ComPtr<ID2D1RenderTarget> target, Windows::UI::Xaml::Media::Brush^ xamlBrush);
	};
}
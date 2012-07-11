#pragma once

#include <limits>

namespace Prose {
	public ref class TextFormat sealed
	{
	public:
		PROPERTY(Windows::UI::Xaml::Media::FontFamily^, FontFamily)
		PROPERTY(double, FontSize)
		PROPERTY(Windows::UI::Xaml::Media::Brush^, Foreground)
		PROPERTY(Windows::UI::Text::FontStretch, FontStretch)
		NULLABLE_PROPERTY(Windows::UI::Text::FontStyle, FontStyle)
		NULLABLE_PROPERTY(Windows::UI::Text::FontWeight, FontWeight)

		TextFormat(void) :
			_FontFamily(nullptr),
			_FontSize(std::numeric_limits<double>::quiet_NaN()),
			_Foreground(nullptr),
			_FontStretch(Windows::UI::Text::FontStretch::Undefined),
			_FontStyle(Windows::UI::Text::FontStyle::Normal),
			_IsFontStyleSet(false),
			_FontWeight(Windows::UI::Text::FontWeights::Normal),
			_IsFontWeightSet(false) { }

	internal:
		void ApplyDeviceIndependent(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 start, UINT32 length);
		void ApplyDeviceDependent(Microsoft::WRL::ComPtr<ID2D1RenderTarget> target, Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 offset, UINT32 length);

	private:
		Microsoft::WRL::ComPtr<ID2D1Brush> ConvertBrush(Microsoft::WRL::ComPtr<ID2D1RenderTarget> target, Windows::UI::Xaml::Media::Brush^ xamlBrush);
	};
}
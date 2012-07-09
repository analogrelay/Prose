#pragma once

#include <limits>

namespace Prose {
	public ref class TextFormat sealed
	{
	public:
		property Windows::UI::Xaml::Media::FontFamily^ FontFamily;
		property double FontSize;
		property Windows::UI::Xaml::Media::Brush^ Foreground;

		TextFormat(void) {
			FontFamily = nullptr;
			FontSize = std::numeric_limits<double>::quiet_NaN();
			Foreground = nullptr;
		}

	internal:
		void ApplyDeviceIndependent(Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 start, UINT32 length);
		void ApplyDeviceDependent(Microsoft::WRL::ComPtr<ID2D1RenderTarget> target, Microsoft::WRL::ComPtr<IDWriteTextLayout> layout, UINT32 offset, UINT32 length);

	private:
		Microsoft::WRL::ComPtr<ID2D1Brush> ConvertBrush(Microsoft::WRL::ComPtr<ID2D1RenderTarget> target, Windows::UI::Xaml::Media::Brush^ xamlBrush);
	};
}
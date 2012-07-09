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
	};
}
#pragma once

#include "TextFormat.h"

namespace Prose {
	namespace Controls {
		namespace WFM = Windows::Foundation::Metadata;
		namespace WUX = Windows::UI::Xaml;
		namespace WUT = Windows::UI::Text;

		[WFM::WebHostHidden]
		public ref class DocumentNode :
			public WUX::DependencyObject {
		public:
			DEPENDENCY_PROPERTY(WUX::Media::FontFamily^, FontFamily);
			DEPENDENCY_PROPERTY(WUX::Media::Brush^, Foreground);
			DEPENDENCY_PROPERTY(WUT::FontStretch, FontStretch);
			DEPENDENCY_PROPERTY(double, FontSize);
			DEPENDENCY_PROPERTY(WUT::FontStyle, FontStyle);
			DEPENDENCY_PROPERTY(WUT::FontWeight, FontWeight);
			DEPENDENCY_PROPERTY(bool, HasStrikethrough);
			DEPENDENCY_PROPERTY(bool, HasUnderline);

		internal:
			TextFormat^ CreateFormat();
		};
	}
}
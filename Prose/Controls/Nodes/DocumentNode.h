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
			property WUX::Media::FontFamily^ FontFamily {
				WUX::Media::FontFamily^ get();
				void set(WUX::Media::FontFamily^ value);
			}

			property WUX::Media::Brush^ Foreground {
				WUX::Media::Brush^ get();
				void set(WUX::Media::Brush^ value);
			}

			property WUT::FontStretch FontStretch {
				WUT::FontStretch get();
				void set(WUT::FontStretch value);
			}
			
			property double FontSize {
				double get();
				void set(double value);
			}

			property WUT::FontStyle FontStyle {
				WUT::FontStyle get();
				void set(WUT::FontStyle value);
			}

			property WUT::FontWeight FontWeight {
				WUT::FontWeight get();
				void set(WUT::FontWeight value);
			}

			property bool HasStrikethrough {
				bool get();
				void set(bool value);
			}

			property bool HasUnderline {
				bool get();
				void set(bool value);
			}

		internal:
			TextFormat^ CreateFormat();

		private:
			WUX::Media::FontFamily^ _fontFamily;
			WUX::Media::Brush^ _foreground;
			WUT::FontStretch _fontStretch;

			Nullable<double> _fontSize;
			Nullable<WUT::FontStyle> _fontStyle;
			Nullable<WUT::FontWeight> _fontWeight;
			Nullable<bool> _hasStrikethrough;
			Nullable<bool> _hasUnderline;
		};
	}
}
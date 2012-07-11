#pragma once

#include "DocumentNode.h"
#include "InlinePair.h"
#include "..\TextFormat.h"

#include <limits>

namespace Prose {
	namespace Structure {
		public ref class Inline :
			public DocumentNode
		{
			DEPENDENCY_PROPERTY(Windows::UI::Xaml::Media::FontFamily^, FontFamily);
			DEPENDENCY_PROPERTY(double, FontSize);
			DEPENDENCY_PROPERTY(Windows::UI::Xaml::Media::Brush^, Foreground);
			DEPENDENCY_PROPERTY(Windows::UI::Text::FontStretch, FontStretch);
			DEPENDENCY_PROPERTY(Windows::UI::Text::FontStyle, FontStyle);
			DEPENDENCY_PROPERTY(Windows::UI::Text::FontWeight, FontWeight);
			DEPENDENCY_PROPERTY(bool, Strikethrough);
			DEPENDENCY_PROPERTY(bool, Underline);
			
		public:
			virtual property UINT32 Length { UINT32 get() { throw ref new Platform::NotImplementedException(); } }
			virtual InlinePair^ Split(UINT32 localOffset) { throw ref new Platform::NotImplementedException(); };

			/// <summary>Creates a TextFormat representing this node</summary>
			TextFormat^ CreateFormat(void);

		public protected:
			void CopyStyleTo(Inline^ other);
		};
	}
}
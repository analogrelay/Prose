#pragma once

#include "DocumentNode.h"
#include "InlinePair.h"
#include <limits>

namespace Prose {
	namespace Structure {
		public ref class Inline abstract:
			public DocumentNode
		{
			NOTIFY_PROPERTY(Windows::UI::Xaml::Media::FontFamily^, FontFamily);
			NOTIFY_PROPERTY(double, FontSize);
			NOTIFY_PROPERTY(Windows::UI::Xaml::Media::Brush^, Foreground);

		public:
			virtual property UINT32 Length { UINT32 get() { throw ref new Platform::NotImplementedException(); } }
			virtual InlinePair^ Split(UINT32 localOffset) { throw ref new Platform::NotImplementedException(); };

		public protected:
			void CopyStyleTo(Inline^ other);

		private protected:
			Inline(void) : _FontSize(std::numeric_limits<double>::quiet_NaN()), _FontFamily(nullptr), _Foreground(nullptr) {}
		};
	}
}
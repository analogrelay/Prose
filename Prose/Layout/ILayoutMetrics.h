#pragma once

#include "..\FormattedRange.h"

namespace Prose {
	namespace Layout {
		private interface class ILayoutMetrics {
			virtual property UINT32 LineCount {
				UINT32 get();
			}

			virtual property Windows::Foundation::Rect RenderArea {
				Windows::Foundation::Rect get();
			}

			virtual property Windows::Foundation::Rect LayoutBounds {
				Windows::Foundation::Rect get();
			}

			virtual property Windows::Foundation::Collections::IVector<FormattedRange^>^ FormattedRanges {
				Windows::Foundation::Collections::IVector<FormattedRange^>^ get() = 0;
			}

			virtual property UINT32 TextLength {
				UINT32 get() = 0;
			}

			virtual INT32 HitTest(Windows::Foundation::Point point);
		};
	}
}

#pragma once

namespace Prose {
	namespace Layout {
		public interface class ILayoutMetrics {
			virtual property UINT32 LineCount {
				UINT32 get() = 0;
			}

			virtual property Windows::Foundation::Rect RenderArea {
				Windows::Foundation::Rect get() = 0;
			}

			virtual property Windows::Foundation::Rect LayoutBounds {
				Windows::Foundation::Rect get() = 0;
			}
		};
	}
}
#pragma once

namespace Prose {
	namespace Layout {
		public interface class ILayoutMetrics {
			virtual property UINT32 LineCount {
				UINT32 get() = 0;
			}

			virtual property Windows::Foundation::Point Origin {
				Windows::Foundation::Point get() = 0;
			}

			virtual property Windows::Foundation::Size Size {
				Windows::Foundation::Size get() = 0;
			}
		};
	}
}
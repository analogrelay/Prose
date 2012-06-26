#pragma once

namespace Prose {
	namespace Layout {
		public interface class ILayoutMetrics {
			virtual property Windows::Foundation::Size Size {
				Windows::Foundation::Size get() = 0;
			}
		};
	}
}
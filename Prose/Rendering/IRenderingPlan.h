#pragma once

namespace Prose {
	namespace Rendering {
		public interface class IRenderingPlan
		{
		public:
			virtual property Windows::Foundation::Size RenderSize {
				Windows::Foundation::Size get() = 0;
			}
		};
	}
}
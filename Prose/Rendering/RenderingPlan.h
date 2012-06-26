#pragma once
#include "RenderSurface.h"

namespace Prose {
	namespace Rendering {
		public ref class RenderingPlan sealed
		{
		public:
			property Windows::Foundation::Collections::IVector<RenderSurface^>^ Surfaces {
				Windows::Foundation::Collections::IVector<RenderSurface^>^ get() { return _surfaces; }
			}

			RenderingPlan(void);
		private:
			Windows::Foundation::Collections::IVector<RenderSurface^>^ _surfaces;
		};
	}
}
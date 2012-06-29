#pragma once
#include <windows.ui.xaml.media.dxinterop.h>

#include "DirectWriteSurface.h"

namespace Prose {
	namespace Rendering {
		private ref class DirectWriteRenderingPlan sealed :
			public RenderingPlan
		{
		public:
			property Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ Surfaces {
				Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ get() { return _surfaces; }
			};

			DirectWriteRenderingPlan(void) : _surfaces(ref new Platform::Collections::Vector<DirectWriteSurface^>()) { }
		private:

			Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ _surfaces;
		};
	}
}
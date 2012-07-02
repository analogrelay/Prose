#pragma once
#include <windows.ui.xaml.media.dxinterop.h>

#include "DirectWriteSurface.h"

namespace Prose {
	namespace Rendering {
		private ref class DirectWriteRenderingPlan sealed :
			public IRenderingPlan
		{
		public:
			property Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ Surfaces {
				Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ get() { return _surfaces; }
			};

			virtual property Windows::Foundation::Size RenderSize {
				Windows::Foundation::Size get();
			}

			DirectWriteRenderingPlan(void) : _surfaces(ref new Platform::Collections::Vector<DirectWriteSurface^>()), _renderSizeCalculated(false), _renderSize() { }
		private:
			bool _renderSizeCalculated;
			Windows::Foundation::Size _renderSize;
			Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ _surfaces;
		};
	}
}
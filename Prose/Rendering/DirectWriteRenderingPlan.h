#pragma once
#include "DirectWriteSurface.h"

namespace Prose {
	namespace Rendering {
		public ref class DirectWriteRenderingPlan sealed :
			public RenderingPlan
		{
		public:
			DirectWriteRenderingPlan(void) : _surfaces(ref new Platform::Collections::Vector<DirectWriteSurface^>()) { }

			virtual void RenderTo(Windows::UI::Xaml::Controls::Image^ image) override;

		private:
			Windows::Foundation::Collections::IVector<DirectWriteSurface^>^ _surfaces;
		};
	}
}
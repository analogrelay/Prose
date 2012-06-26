#pragma once
#include "RenderSurface.h"
#include "DWRenderRange.h"

namespace Prose {
	namespace Rendering {
		private ref class DWRenderSurface sealed : public RenderSurface
		{
		public:
			DWRenderSurface(void);

			property Windows::Foundation::Collections::IVector<DWRenderRange^>^ Ranges {
				Windows::Foundation::Collections::IVector<DWRenderRange^>^ get() { return _ranges; }
			};

			virtual Windows::UI::Xaml::UIElement^ RenderToUIElement(void) override;
		private:
			Windows::Foundation::Collections::IVector<DWRenderRange^>^ _ranges;
		};
	}
}
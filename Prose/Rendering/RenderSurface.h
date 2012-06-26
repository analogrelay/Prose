#pragma once

namespace Prose {
	namespace Rendering {
		public ref class RenderSurface abstract
		{
		public:
			virtual Windows::UI::Xaml::UIElement^ RenderToUIElement(void) = 0;
		};
	}
}
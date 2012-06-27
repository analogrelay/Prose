#pragma once

namespace Prose {
	namespace Rendering {
		public ref class RenderingPlan abstract
		{
		public:
			virtual void RenderTo(Windows::UI::Xaml::Controls::Image^ image) = 0;
		};
	}
}
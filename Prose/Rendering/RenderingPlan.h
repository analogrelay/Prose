#pragma once

namespace Prose {
	namespace Rendering {
		public ref class RenderingPlan abstract
		{
		public:
			virtual void RenderTo(Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ targetSurface, Windows::Foundation::Rect targetRect) = 0;
		};
	}
}
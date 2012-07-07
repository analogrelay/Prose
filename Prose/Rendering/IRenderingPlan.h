#pragma once

namespace Prose {
	namespace Rendering {
		public interface class IRenderingPlan
		{
		public:
			void Attach(Windows::UI::Xaml::Media::Imaging::VirtualSurfaceImageSource^ targetSurface, Windows::Foundation::Rect region);

			virtual property Windows::Foundation::Size RenderSize {
				Windows::Foundation::Size get() = 0;
			}
		};
	}
}
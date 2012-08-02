#pragma once

namespace Prose {
	namespace Rendering {
		namespace WUX = Windows::UI::Xaml;
		namespace WF = Windows::Foundation;

		private interface class IRenderingPlan
		{
		public:
			void Attach(WUX::Media::Imaging::VirtualSurfaceImageSource^ targetSurface, WF::Rect region);

			virtual property WF::Size RenderSize {
				WF::Size get() = 0;
			}
		};
	}
}
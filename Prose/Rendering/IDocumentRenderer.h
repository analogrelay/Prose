#pragma once
#include "IRenderingPlan.h"
#include "..\Layout\LayoutTree.h"

namespace Prose {
	namespace Rendering {
		public interface class IDocumentRenderer {
			IRenderingPlan^ PlanRendering(Prose::Layout::LayoutTree^ layout);
			void Render(IRenderingPlan^ plan, Windows::UI::Xaml::Media::Imaging::VirtualSurfaceImageSource^ targetSurface, Windows::Foundation::Rect region);
		};
	}
}
#pragma once
#include "RenderingPlan.h"
#include "..\Layout\LayoutTree.h"

namespace Prose {
	namespace Rendering {
		public interface class IDocumentRenderer {
			RenderingPlan^ PlanRendering(Prose::Layout::LayoutTree^ layout);
			void Render(RenderingPlan^ plan, Windows::UI::Xaml::Media::Imaging::SurfaceImageSource^ targetSurface, Windows::Foundation::Rect region);
		};
	}
}
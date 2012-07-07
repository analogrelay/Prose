#pragma once
#include "IRenderingPlan.h"
#include "..\Layout\LayoutTree.h"

namespace Prose {
	namespace Rendering {
		public interface class IDocumentRenderer {
			IRenderingPlan^ PlanRendering(Prose::Layout::LayoutTree^ layout);
		};
	}
}
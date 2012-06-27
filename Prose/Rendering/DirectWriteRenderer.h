#pragma once

#include "RenderingPlan.h"
#include "IDocumentRenderer.h"
#include "..\Layout\LayoutTree.h"
#include "..\Layout\LayoutVisitor.h"

namespace Prose {
	namespace Rendering {
		public ref class DirectWriteRenderer sealed :
			public IDocumentRenderer
		{
		public:
			DirectWriteRenderer(void);

			virtual RenderingPlan^ PlanRendering(Prose::Layout::LayoutTree^ layout);
		};
	}
}
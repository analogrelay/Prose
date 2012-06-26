#pragma once

#include "..\Layout\LayoutVisitor.h"
#include "DWRenderSurface.h"

namespace Prose {
	namespace Rendering {
		private ref class RenderingLayoutVisitor sealed :
			public Layout::LayoutVisitor
		{
		public:
			RenderingLayoutVisitor(void);

			virtual void Visit(Layout::Box^ box) override;
			virtual void Visit(Layout::Span^ span) override;

		private:
			DWRenderSurface^ _currentSurface;
			RenderingPlan^ _plan;
		};
	}
}
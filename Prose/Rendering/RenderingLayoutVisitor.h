#pragma once
#include "..\Layout\LayoutVisitor.h"
#include "DirectWriteRenderingPlan.h"

namespace Prose {
	namespace Rendering {
		private ref class RenderingLayoutVisitor sealed :
			public Layout::LayoutVisitor
		{
		public:
			RenderingLayoutVisitor(DirectWriteRenderer^ renderer);

			property DirectWriteRenderingPlan^ RenderingPlan {
				DirectWriteRenderingPlan^ get() { return _plan; }
			}

			virtual void Visit(Layout::LayoutBox^ box) override;
		private:
			DirectWriteRenderingPlan^ _plan;
		};
	}
}
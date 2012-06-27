#pragma once
#include "..\Layout\LayoutVisitor.h"
#include "DirectWriteRenderingPlan.h"

namespace Prose {
	namespace Rendering {
		private ref class RenderingLayoutVisitor sealed :
			public Layout::LayoutVisitor
		{
		public:
			RenderingLayoutVisitor(void);

			property DirectWriteRenderingPlan^ RenderingPlan {
				DirectWriteRenderingPlan^ get() { return _plan; }
			}

			virtual void Visit(Layout::Box^ box) override;
			virtual void Visit(Layout::Span^ span) override;
		private:
			DirectWriteRenderingPlan^ _plan;
		};
	}
}
#pragma once
#include "LayoutNode.h"
#include "ILayoutMetrics.h"

namespace Prose {
	namespace Layout {
		public ref class LayoutBox sealed :
			public LayoutNode
		{
		public:
			LayoutBox(void);

			property Windows::UI::Xaml::Thickness Margin;
			
			property ILayoutMetrics^ Metrics {
				ILayoutMetrics^ get() { return _metrics; }
				void set(ILayoutMetrics^ value) { _metrics = value; }
			};

			virtual void Accept(LayoutVisitor^ visitor) override;
		private:
			ILayoutMetrics^ _metrics;
		};
	}
}
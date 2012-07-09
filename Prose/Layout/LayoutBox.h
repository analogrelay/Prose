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
			LayoutBox(Windows::UI::Xaml::Thickness margin);

			property Windows::UI::Xaml::Thickness Margin {
				Windows::UI::Xaml::Thickness get() { return _margin; }
			}
			
			property ILayoutMetrics^ Metrics {
				ILayoutMetrics^ get() { return _metrics; }
				void set(ILayoutMetrics^ value) { _metrics = value; }
			};

			virtual void Accept(LayoutVisitor^ visitor) override;
		private:
			Windows::UI::Xaml::Thickness _margin;
			ILayoutMetrics^ _metrics;
		};
	}
}
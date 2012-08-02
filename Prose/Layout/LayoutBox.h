#pragma once
#include "LayoutNode.h"
#include "ILayoutMetrics.h"

namespace Prose {
	namespace Structure {
		ref class TextPointer;
		ref class StructureNode;
	}
	namespace Layout {
		namespace WUX = Windows::UI::Xaml;
		namespace WFC = Windows::Foundation::Collections;
		namespace PS = Prose::Structure;

		ref class LayoutPointer;
		ref class LayoutVisitor;
		ref class LayoutInline;

		private ref class LayoutBox :
			public LayoutNode
		{
		public:
			property WUX::Thickness Margin {
				WUX::Thickness get() { return _margin; }
			}
			
			property ILayoutMetrics^ Metrics {
				ILayoutMetrics^ get() { return _metrics; }
				void set(ILayoutMetrics^ value) { _metrics = value; }
			};

			property WFC::IVector<LayoutInline^>^ Inlines {
				WFC::IVector<LayoutInline^>^ get() { return _inlines; }
			}

			virtual void Accept(LayoutVisitor^ visitor) override;
			
			LayoutPointer^ HitTest(Windows::Foundation::Point point);

		internal:
			LayoutBox(PS::StructureNode^ node);
			LayoutBox(PS::StructureNode^ node, WUX::Thickness margin);

		public protected:
			virtual property PS::StructureNode^ StructureNode {
				virtual PS::StructureNode^ get() override;
			}

		private:
			WUX::Thickness _margin;
			PS::StructureNode^ _node;
			ILayoutMetrics^ _metrics;
			WFC::IVector<LayoutInline^>^ _inlines;
		};
	}
}

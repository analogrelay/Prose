#pragma once
#include "LayoutNode.h"
#include "ILayoutMetrics.h"

namespace Prose {
	namespace Structure {
		ref class TextPointer;
		ref class DocumentNode;
	}
	namespace Layout {
		namespace WUX = Windows::UI::Xaml;
		namespace WFC = Windows::Foundation::Collections;
		namespace PS = Prose::Structure;

		ref class LayoutPointer;
		
		interface class ILayoutVisitor;
		interface class ILayoutInline;

		public interface class ILayoutBox :
			public ILayoutNode {

			property WUX::Thickness Margin {
				WUX::Thickness get();
			}

			property ILayoutMetrics^ Metrics {
				ILayoutMetrics^ get();
			}

			property WFC::IVector<ILayoutInline^>^ Inlines {
				WFC::IVector<ILayoutInline^>^ get();
			}

			PS::TextPointer^ LayoutToText(LayoutPointer^ ptr);
		};

		private ref class LayoutBox :
			public LayoutNode,
			public ILayoutBox
		{
		public:
			property WUX::Thickness Margin {
				WUX::Thickness get() { return _margin; }
			}
			
			property ILayoutMetrics^ Metrics {
				ILayoutMetrics^ get() { return _metrics; }
				void set(ILayoutMetrics^ value) { _metrics = value; }
			};

			property WFC::IVector<ILayoutInline^>^ Inlines {
				WFC::IVector<ILayoutInline^>^ get() { return _inlines; }
			}

			virtual void Accept(ILayoutVisitor^ visitor) override;
			virtual PS::TextPointer^ LayoutToText(LayoutPointer^ ptr);

			LayoutPointer^ HitTest(Windows::Foundation::Point point);

		internal:
			LayoutBox(PS::DocumentNode^ node);
			LayoutBox(PS::DocumentNode^ node, WUX::Thickness margin);

		public protected:
			virtual property PS::IDocumentNode^ StructureNode {
				virtual PS::IDocumentNode^ get() override;
			}

		private:
			WUX::Thickness _margin;
			PS::DocumentNode^ _node;
			ILayoutMetrics^ _metrics;
			WFC::IVector<ILayoutInline^>^ _inlines;
		};
	}
}

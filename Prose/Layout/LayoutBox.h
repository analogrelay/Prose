#pragma once
#include "LayoutNode.h"
#include "ILayoutMetrics.h"

namespace Prose {
	namespace Structure {
		ref class TextPointer;
		ref class DocumentNode;
	}
	namespace Layout {
		ref class LayoutPointer;
		ref class LayoutVisitor;
		ref class LayoutInline;

		public ref class LayoutBox sealed :
			public LayoutNode
		{
		public:
			LayoutBox(Prose::Structure::DocumentNode^ node);
			LayoutBox(Prose::Structure::DocumentNode^ node, Windows::UI::Xaml::Thickness margin);
			
			property Windows::UI::Xaml::Thickness Margin {
				Windows::UI::Xaml::Thickness get() { return _margin; }
			}
			
			property ILayoutMetrics^ Metrics {
				ILayoutMetrics^ get() { return _metrics; }
				void set(ILayoutMetrics^ value) { _metrics = value; }
			};

			property Windows::Foundation::Collections::IVector<LayoutInline^>^ Inlines {
				Windows::Foundation::Collections::IVector<LayoutInline^>^ get() { return _inlines; }
			}

			virtual void Accept(LayoutVisitor^ visitor) override;
			virtual Prose::Structure::TextPointer^ LayoutToText(LayoutPointer^ ptr);

			LayoutPointer^ HitTest(Windows::Foundation::Point point);

		public protected:
			virtual property Prose::Structure::DocumentNode^ StructureNode {
				virtual Prose::Structure::DocumentNode^ get() override;
			}

		private:
			Windows::UI::Xaml::Thickness _margin;
			Prose::Structure::DocumentNode^ _node;
			ILayoutMetrics^ _metrics;
			Windows::Foundation::Collections::IVector<LayoutInline^>^ _inlines;
		};
	}
}

#pragma once
#include "..\Structure\DocumentNode.h"
#include "LayoutNode.h"

namespace Prose {
	namespace Layout {
		namespace PS = Prose::Structure;


		public interface class ILayoutInline :
			public ILayoutNode {

			property Platform::String^ Text {
				Platform::String^ get();
			}
		};

		private ref class LayoutInline :
			public LayoutNode,
			public ILayoutInline
		{
		public:
			property Platform::String^ Text {
				Platform::String^ get() { return _text; }
			}
			
			virtual void Accept(ILayoutVisitor^ visitor) override;

		internal:
			LayoutInline(PS::IDocumentNode^ node, Platform::String^ text);

		public protected:
			virtual property PS::IDocumentNode^ StructureNode {
				virtual PS::IDocumentNode^ get() override;
			}

		private:
			PS::IDocumentNode^ _node;
			Platform::String^ _text;
		};
	}
}
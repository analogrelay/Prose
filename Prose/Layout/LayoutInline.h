#pragma once
#include "..\Structure\StructureNode.h"
#include "LayoutNode.h"

namespace Prose {
	namespace Layout {
		namespace PS = Prose::Structure;

		private ref class LayoutInline :
			public LayoutNode
		{
		public:
			property Platform::String^ Text {
				Platform::String^ get() { return _text; }
			}
			
			virtual void Accept(LayoutVisitor^ visitor) override;

		internal:
			LayoutInline(PS::StructureNode^ node, Platform::String^ text);

		public protected:
			virtual property PS::StructureNode^ StructureNode {
				virtual PS::StructureNode^ get() override;
			}

		private:
			PS::StructureNode^ _node;
			Platform::String^ _text;
		};
	}
}
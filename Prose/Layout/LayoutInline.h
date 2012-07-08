#pragma once
#include "..\Structure\DocumentNode.h"
#include "LayoutNode.h"

namespace Prose {
	namespace Layout {
		public ref class LayoutInline sealed :
			public LayoutNode
		{
		public:
			LayoutInline(Prose::Structure::DocumentNode^ node, Platform::String^ text);

			property Platform::String^ Text {
				Platform::String^ get() { return _text; }
			}
			
			virtual void Accept(LayoutVisitor^ visitor) override;

		public protected:
			virtual property Prose::Structure::DocumentNode^ StructureNode {
				virtual Prose::Structure::DocumentNode^ get() override;
			}

		private:
			Prose::Structure::DocumentNode^ _node;
			Platform::String^ _text;
		};
	}
}
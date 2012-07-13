#pragma once
#include "..\Structure\DocumentNode.h"
#include "..\Events\PointerEvents.h"

namespace Prose {
	namespace Layout {
		ref class LayoutVisitor;

		public ref class LayoutNode abstract
		{
		public:
			virtual event Prose::Events::PointerLayoutEventHandler^ PointerEntered;
			virtual void FirePointerEntered(Prose::Events::PointerLayoutEventArgs^ args);

			virtual void Accept(LayoutVisitor^ visitor) = 0;
		
		public protected:
			virtual property Prose::Structure::DocumentNode^ StructureNode {
				virtual Prose::Structure::DocumentNode^ get() { throw ref new Platform::NotImplementedException(); };
			}
		};
	}
}
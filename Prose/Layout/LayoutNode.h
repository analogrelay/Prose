#pragma once
#include "Structure\StructureNode.h"
#include "Events\PointerLayoutEvent.h"

namespace Prose {
	namespace Layout {
		namespace PE = Prose::Events;
		namespace PS = Prose::Structure;

		ref class LayoutVisitor;

		private ref class LayoutNode abstract
		{
		public:
			virtual void Accept(LayoutVisitor^ visitor) abstract;

		public protected:
			virtual property PS::StructureNode^ StructureNode {
				virtual PS::StructureNode^ get() { return _structureNode; };
			}

		private protected:
			LayoutNode(PS::StructureNode^ structureNode);

		private:
			PS::StructureNode^ _structureNode;
			PE::IRoutedEventManager^ _eventManager;
		};
	}
}
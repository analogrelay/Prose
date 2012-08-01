#pragma once
#include "..\Structure\DocumentNode.h"
#include "..\Events\PointerLayoutEvent.h"

namespace Prose {
	namespace Layout {
		namespace PE = Prose::Events;
		namespace PS = Prose::Structure;

		interface class ILayoutVisitor;

		public interface class ILayoutNode :
			public PE::IRoutedEventSource {
			event PE::PointerLayoutEventHandler^ PointerEntered;
			event PE::PointerLayoutEventHandler^ PointerExited;
			event PE::PointerLayoutEventHandler^ PointerMoved;
			event PE::PointerLayoutEventHandler^ Invalidated;

			property ILayoutNode^ Parent { ILayoutNode^ get(); }

			void FirePointerEntered(PE::IPointerLayoutEventArgs^ args);
			void FirePointerExited(PE::IPointerLayoutEventArgs^ args);
			void FirePointerMoved(PE::IPointerLayoutEventArgs^ args);

			void Accept(ILayoutVisitor^ visitor);
		};

		private ref class LayoutNode abstract :
			public PE::IRoutedEventSource
		{
			DEFINE_ROUTED_EVENT(
				PE::PointerLayoutEventHandler, 
				PE::IPointerLayoutEventArgs^,
				PointerEntered);
			DEFINE_ROUTED_EVENT(
				PE::PointerLayoutEventHandler, 
				PE::IPointerLayoutEventArgs^,
				PointerExited);
			DEFINE_ROUTED_EVENT(
				PE::PointerLayoutEventHandler, 
				PE::IPointerLayoutEventArgs^,
				PointerMoved);
			DEFINE_ROUTED_EVENT(
				PE::CustomRoutedEventHandler,
				PE::ICustomRoutedEventArgs^,
				Invalidated);

		public:
			virtual void FirePointerEntered(PE::IPointerLayoutEventArgs^ args);
			virtual void FirePointerExited(PE::IPointerLayoutEventArgs^ args);
			virtual void FirePointerMoved(PE::IPointerLayoutEventArgs^ args);

			virtual void Accept(ILayoutVisitor^ visitor) abstract;
		
			virtual property ILayoutNode^ Parent { ILayoutNode^ get() { return _parent; } }
			virtual PE::IRoutedEventManager^ GetRoutedEventManager() { return _eventManager; }
			virtual PE::IRoutedEventSource^ GetEventRoutingParent(void) { return Parent; }

		public protected:
			virtual property PS::IDocumentNode^ StructureNode {
				virtual PS::IDocumentNode^ get() { return _structureNode; };
			}

		private protected:
			LayoutNode(PS::IDocumentNode^ structureNode);

		internal:
			void DetachParent(void) { _parent = nullptr; }
			void AttachParent(ILayoutNode^ parent) { _parent = parent; }

		private:
			ILayoutNode^ _parent;
			PS::IDocumentNode^ _structureNode;
			PE::IRoutedEventManager^ _eventManager;
		};
	}
}
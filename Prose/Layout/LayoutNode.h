#pragma once
#include "..\Structure\DocumentNode.h"
#include "..\Events\PointerEvents.h"

namespace Prose {
	namespace Layout {
		ref class LayoutVisitor;

		public ref class LayoutNode abstract :
			public Prose::Events::IRoutedEventSource
		{
			DEFINE_ROUTED_EVENT(
				Prose::Events::PointerLayoutEventHandler, 
				Prose::Events::PointerLayoutEventArgs^,
				PointerEntered);
			DEFINE_ROUTED_EVENT(
				Prose::Events::PointerLayoutEventHandler, 
				Prose::Events::PointerLayoutEventArgs^,
				PointerExited);
			DEFINE_ROUTED_EVENT(
				Prose::Events::PointerLayoutEventHandler, 
				Prose::Events::PointerLayoutEventArgs^,
				PointerMoved);
			DEFINE_ROUTED_EVENT(
				Prose::Events::CustomRoutedEventHandler,
				Prose::Events::CustomRoutedEventArgs^,
				Invalidated);


		public:
			virtual void FirePointerEntered(Prose::Events::PointerLayoutEventArgs^ args);
			virtual void FirePointerExited(Prose::Events::PointerLayoutEventArgs^ args);
			virtual void FirePointerMoved(Prose::Events::PointerLayoutEventArgs^ args);

			virtual void Accept(LayoutVisitor^ visitor) = 0;
		
			virtual property LayoutNode^ Parent { LayoutNode^ get() { return _parent; } }
			virtual Prose::Events::IRoutedEventManager^ GetRoutedEventManager() { return _eventManager; }
			virtual Prose::Events::IRoutedEventSource^ GetEventRoutingParent(void) { return Parent; }

		public protected:
			virtual property Prose::Structure::DocumentNode^ StructureNode {
				virtual Prose::Structure::DocumentNode^ get() { return _structureNode; };
			}

		private protected:
			LayoutNode(Prose::Structure::DocumentNode^ structureNode);

		internal:
			void DetachParent(void) { _parent = nullptr; }
			void AttachParent(LayoutNode^ parent) { _parent = parent; }

		private:
			LayoutNode^ _parent;
			Prose::Structure::DocumentNode^ _structureNode;
			Prose::Events::IRoutedEventManager^ _eventManager;
		};
	}
}
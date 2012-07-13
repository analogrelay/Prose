#pragma once
#include "..\Structure\DocumentNode.h"
#include "..\Events\PointerEvents.h"

namespace Prose {
	namespace Layout {
		ref class LayoutVisitor;

		public ref class LayoutNode :
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

		public:
			virtual void FirePointerEntered(Prose::Events::PointerLayoutEventArgs^ args);
			virtual void FirePointerExited(Prose::Events::PointerLayoutEventArgs^ args);
			virtual void FirePointerMoved(Prose::Events::PointerLayoutEventArgs^ args);

			virtual void Accept(LayoutVisitor^ visitor) { dbgf(L"Accept was called but is not implemented for this sub-class"); };
		
			virtual property LayoutNode^ Parent { LayoutNode^ get() { return _parent; } }
			virtual Prose::Events::IRoutedEventManager^ GetRoutedEventManager() { return _eventManager; }
			virtual Prose::Events::IRoutedEventSource^ GetEventRoutingParent(void) { return Parent; }

		public protected:
			virtual property Prose::Structure::DocumentNode^ StructureNode {
				virtual Prose::Structure::DocumentNode^ get() { throw ref new Platform::NotImplementedException(); };
			}

		private protected:
			LayoutNode(void);

		internal:
			void DetachParent(void) { _parent = nullptr; }
			void AttachParent(LayoutNode^ parent) { _parent = parent; }

		private:
			LayoutNode^ _parent;
			Prose::Events::IRoutedEventManager^ _eventManager;
		};
	}
}
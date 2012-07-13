#pragma once

#include "..\Events\PointerEvents.h"
#include "..\Events\IRoutedEventSource.h"
#include "..\Events\RoutedEvent.h"

namespace Prose {
	namespace Structure {
		ref class DocumentVisitor;

		public ref class DocumentNode : 
			public Windows::UI::Xaml::DependencyObject,
			public Prose::Events::IRoutedEventSource
		{
			DEFINE_ROUTED_EVENT(
				Prose::Events::PointerTextEventHandler, 
				Prose::Events::PointerTextEventArgs^,
				PointerEntered);
			DEFINE_ROUTED_EVENT(
				Prose::Events::PointerTextEventHandler, 
				Prose::Events::PointerTextEventArgs^,
				PointerExited);
			DEFINE_ROUTED_EVENT(
				Prose::Events::PointerTextEventHandler, 
				Prose::Events::PointerTextEventArgs^,
				PointerMoved);

			virtual void Accept(DocumentVisitor^ visitor) { dbgf(L"Accept was called but is not implemented for this sub-class"); };

			/// <summary>Not intended to be called by user-code</summary>
			virtual void FirePointerEntered(Prose::Events::PointerTextEventArgs^ args);
			virtual void FirePointerExited(Prose::Events::PointerTextEventArgs^ args);
			virtual void FirePointerMoved(Prose::Events::PointerTextEventArgs^ args);
			
			virtual Prose::Events::IRoutedEventManager^ GetRoutedEventManager() { return _eventManager; }
			virtual Prose::Events::IRoutedEventSource^ GetEventRoutingParent(void) { return Parent; }

			virtual property DocumentNode^ Parent { DocumentNode^ get() { return _parent; } }

		internal:
			void DetachParent(void) { _parent = nullptr; }
			void AttachParent(DocumentNode^ parent) { _parent = parent; }

		private protected:
			DocumentNode(void);

		private:
			DocumentNode^ _parent;
			Prose::Events::IRoutedEventManager^ _eventManager;
		};
	}
}

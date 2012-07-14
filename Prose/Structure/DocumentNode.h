#pragma once

#include "..\Events\PointerEvents.h"
#include "..\Events\IRoutedEventSource.h"
#include "..\Events\RoutedEvent.h"
#include "..\Events\CustomRoutedEvent.h"

namespace Prose {
	namespace Structure {
		interface class IDocumentVisitor;

		public interface class IDocumentNode {
			event Prose::Events::PointerTextEventHandler^ PointerEntered;
			event Prose::Events::PointerTextEventHandler^ PointerExited;
			event Prose::Events::PointerTextEventHandler^ PointerMoved;

			property IDocumentNode^ Parent { IDocumentNode^ get(); }
			
			void Accept(IDocumentVisitor^ visitor);
			void DetachParent();
			void AttachParent(IDocumentNode^ parent);
		};

		public ref class DocumentNode : 
			public Windows::UI::Xaml::DependencyObject,
			public Prose::Events::IRoutedEventSource,
			public IDocumentNode
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
			DEFINE_ROUTED_EVENT(
				Prose::Events::CustomRoutedEventHandler,
				Prose::Events::CustomRoutedEventArgs^,
				Invalidated);

		public:
			virtual property IDocumentNode^ Parent { IDocumentNode^ get() { return _parent; } }
			
			virtual void Accept(IDocumentVisitor^ visitor) { dbgf(L"Accept called but subclass '%s' does not implement it", GetType()->FullName); }
			
			virtual Prose::Events::IRoutedEventManager^ GetRoutedEventManager() { return _eventManager; }
			virtual Prose::Events::IRoutedEventSource^ GetEventRoutingParent(void) { return dynamic_cast<Prose::Events::IRoutedEventSource^>(Parent); }

			virtual void FirePointerEntered(Prose::Events::PointerTextEventArgs^ args);
			virtual void FirePointerExited(Prose::Events::PointerTextEventArgs^ args);
			virtual void FirePointerMoved(Prose::Events::PointerTextEventArgs^ args);
			
			virtual void DetachParent(void) { _parent = nullptr; }
			virtual void AttachParent(IDocumentNode^ parent) { _parent = parent; }

		private protected:
			DocumentNode(void);

		private:
			IDocumentNode^ _parent;
			Prose::Events::IRoutedEventManager^ _eventManager;
		};
	}
}

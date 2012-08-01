#pragma once

#include "..\Events\PointerTextEvent.h"
#include "..\Events\IRoutedEventSource.h"
#include "..\Events\RoutedEvent.h"
#include "..\Events\CustomRoutedEvent.h"

namespace Prose {
	namespace Structure {
		namespace PE = Prose::Events;
		namespace WUX = Windows::UI::Xaml;

		interface class IDocumentVisitor;

		public interface class IDocumentNode {
			event PE::PointerTextEventHandler^ PointerEntered;
			event PE::PointerTextEventHandler^ PointerExited;
			event PE::PointerTextEventHandler^ PointerMoved;

			property IDocumentNode^ Parent { IDocumentNode^ get(); }
			
			void Accept(IDocumentVisitor^ visitor);
			void DetachParent();
			void AttachParent(IDocumentNode^ parent);
		};

		private ref class DocumentNode abstract : 
			public WUX::DependencyObject,
			public PE::IRoutedEventSource,
			public IDocumentNode
		{
			DEFINE_ROUTED_EVENT(
				PE::PointerTextEventHandler, 
				PE::IPointerTextEventArgs^,
				PointerEntered);
			DEFINE_ROUTED_EVENT(
				PE::PointerTextEventHandler, 
				PE::IPointerTextEventArgs^,
				PointerExited);
			DEFINE_ROUTED_EVENT(
				PE::PointerTextEventHandler, 
				PE::IPointerTextEventArgs^,
				PointerMoved);
			DEFINE_ROUTED_EVENT(
				PE::CustomRoutedEventHandler,
				PE::ICustomRoutedEventArgs^,
				Invalidated);

		public:
			virtual property IDocumentNode^ Parent { IDocumentNode^ get() { return _parent; } }
			
			virtual void Accept(IDocumentVisitor^ visitor) { dbgf(L"Accept called but subclass '%s' does not implement it", GetType()->FullName); }
			
			virtual PE::IRoutedEventManager^ GetRoutedEventManager() { return _eventManager; }
			virtual PE::IRoutedEventSource^ GetEventRoutingParent(void) { return dynamic_cast<PE::IRoutedEventSource^>(Parent); }

			virtual void FirePointerEntered(PE::PointerTextEventArgs^ args);
			virtual void FirePointerExited(PE::PointerTextEventArgs^ args);
			virtual void FirePointerMoved(PE::PointerTextEventArgs^ args);
			
			virtual void DetachParent(void) { _parent = nullptr; }
			virtual void AttachParent(IDocumentNode^ parent) { _parent = parent; }

		private protected:
			DocumentNode(void);

		private:
			IDocumentNode^ _parent;
			PE::IRoutedEventManager^ _eventManager;
		};
	}
}

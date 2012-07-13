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
		public:
			static property Prose::Events::RoutedEvent^ PointerEnteredEvent { Prose::Events::RoutedEvent^ get() { return _PointerEnteredEvent; } }

			virtual event Prose::Events::PointerTextEventHandler^ PointerEntered {
				Windows::Foundation::EventRegistrationToken add(Prose::Events::PointerTextEventHandler^ handler);
				void remove(Windows::Foundation::EventRegistrationToken token);
				void raise(Platform::Object^ sender, Prose::Events::PointerTextEventArgs^ args);
			};

			virtual void Accept(DocumentVisitor^ visitor) { dbgf(L"Accept was called but is not implemented for this sub-class"); };

			/// <summary>Not intended to be called by user-code</summary>
			virtual void FirePointerEntered(Prose::Events::PointerTextEventArgs^ args);
			
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

			static Prose::Events::RoutedEvent^ _PointerEnteredEvent;
		};
	}
}

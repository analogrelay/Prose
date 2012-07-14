#pragma once

#include "CustomRoutedEvent.h"

namespace Prose {
	namespace Events {
		ref class RoutedEvent;
		ref class RoutedEventHandlerInfo;

		public interface class IRoutedEventManager {
			Windows::Foundation::Collections::IIterable<RoutedEventHandlerInfo^>^ GetHandlersForRoutedEvent(
				RoutedEvent^ routedEvent);

			Windows::Foundation::EventRegistrationToken AddHandlerForRoutedEvent(
				RoutedEvent^ routedEvent, 
				Windows::Foundation::TypedEventHandler<Platform::Object^, ICustomRoutedEventArgs^>^ handler, 
				bool invokeForHandledEvents);

			void RemoveHandlerForRoutedEvent(
				RoutedEvent^ routedEvent, 
				Windows::Foundation::EventRegistrationToken token);
		};

		public interface class IRoutedEventSource
		{
			IRoutedEventManager^ GetRoutedEventManager();
			IRoutedEventSource^ GetEventRoutingParent(void);
		};
	}
}
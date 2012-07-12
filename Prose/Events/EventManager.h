#pragma once
#include "IRoutedEventSource.h"

#include <map>
#include <vector>
#include <mutex>

namespace Prose {
	namespace Events {
		ref class RoutedEvent;
		interface class ICustomRoutedEventArgs;
		
		public enum class RoutingStrategy {
			Tunnel,
			Bubble,
			Direct
		};

		public ref class EventManager sealed
		{
		public:
			static RoutedEvent^ RegisterRoutedEvent(
				Platform::String^ name,
				RoutingStrategy routingStrategy,
				Platform::Type^ handlerType,
				Platform::Type^ ownerType);

			static void RaiseRoutedEvent(
				RoutedEvent^ routedEvent,
				IRoutedEventSource^ source,
				ICustomRoutedEventArgs^ args);

			static Windows::Foundation::EventRegistrationToken AddHandler(
				RoutedEvent^ routedEvent,
				IRoutedEventSource^ source,	
				CustomRoutedEventHandler^ handler);

			static Windows::Foundation::EventRegistrationToken AddHandler(
				RoutedEvent^ routedEvent,
				IRoutedEventSource^ source,	
				CustomRoutedEventHandler^ handler,
				bool invokeForHandledEvents);

			static void RemoveHandler(
				RoutedEvent^ routedEvent,
				IRoutedEventSource^ source,
				Windows::Foundation::EventRegistrationToken token);

		internal:
			static UINT64 GetNextEventId();
		private:
			EventManager(void) {};

			static volatile UINT64 _nextId;
		};
	}
}
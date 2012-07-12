#pragma once

#include "IRoutedEventSource.h"
#include "RoutedEvent.h"

namespace Prose {
	namespace Events {
		private ref class RoutedEventManager sealed :
			public IRoutedEventManager
		{
		public:
			RoutedEventManager(void);

			virtual Windows::Foundation::Collections::IIterable<RoutedEventHandlerInfo^>^ GetHandlersForRoutedEvent(RoutedEvent^ routedEvent);
			virtual Windows::Foundation::EventRegistrationToken AddHandlerForRoutedEvent(RoutedEvent^ routedEvent, CustomRoutedEventHandler^ handler, bool invokeForHandledEvents);
			virtual void RemoveHandlerForRoutedEvent(RoutedEvent^ routedEvent, Windows::Foundation::EventRegistrationToken token);

		private:
			class RoutedEventHandlerList {
			public:
				RoutedEventHandlerList(void);

				Windows::Foundation::Collections::IIterable<RoutedEventHandlerInfo^>^ GetHandlers();
				Windows::Foundation::EventRegistrationToken AddHandler(CustomRoutedEventHandler^ handler, bool invokeForHandledEvents);
				void RemoveHandler(Windows::Foundation::EventRegistrationToken token);
			private:
				UINT64 _nextId;
				Platform::Collections::Vector<RoutedEventHandlerInfo^>^ _handlers;
			};

			std::shared_ptr<RoutedEventHandlerList> GetOrCreateHandlerList(RoutedEvent^ routedEvent);
			std::map<RoutedEvent^, std::shared_ptr<RoutedEventHandlerList>> _handlerLists;
		};
	}
}
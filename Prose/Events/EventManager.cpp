#include "pch.h"
#include "EventManager.h"
#include "RoutedEvent.h"
#include "RoutedEventHandlerInfo.h"


using namespace Prose::Events;

using namespace Windows::Foundation;

using namespace Platform;

volatile UINT64 EventManager::_nextId = 0;

namespace std {
	template<>
	struct less<Platform::Type^> {
		bool operator()(Platform::Type^ left, Platform::Type^ right) const {
			return left->FullName < right->FullName;
		}
	};
}

void RaiseDirectEvent(
	RoutedEvent^ routedEvent,
	IRoutedEventSource^ source,
	ICustomRoutedEventArgs^ args) {
	
	// Get the handlers
	auto handlers = source->GetRoutedEventManager()->GetHandlersForRoutedEvent(routedEvent);

	// Invoke them!
	for each(auto handler in handlers) {
		handler->InvokeHandler(source, args);
	}
}

void RaiseBubbledEvent(
	RoutedEvent^ routedEvent,
	IRoutedEventSource^ source,
	ICustomRoutedEventArgs^ args) {

	// Raise the event on this object and it's parents until we're done
	IRoutedEventSource^ current = source;
	while(current) {
		RaiseDirectEvent(routedEvent, current, args);
		current = current->GetEventRoutingParent();
	}
}

void RaiseTunnelledEvent(
	RoutedEvent^ routedEvent,
	IRoutedEventSource^ source,
	ICustomRoutedEventArgs^ args) {

	// Get to the root of the hierarchy, collecting targets along the way
	std::vector<IRoutedEventSource^> targets;
	IRoutedEventSource^ current = source;
	while(current) {
		targets.push_back(current);
		current = current->GetEventRoutingParent();
	}

	// Work backwards through the vector, raising events
	for(auto it = targets.end(); it >= targets.begin(); it--) {
		RaiseDirectEvent(routedEvent, *it, args);
	}
}

RoutedEvent^ EventManager::RegisterRoutedEvent(
	Platform::String^ name,
	RoutingStrategy routingStrategy,
	Platform::Type^ handlerType,
	Platform::Type^ ownerType) {

	return ref new RoutedEvent(name, routingStrategy, handlerType, ownerType);
}

void EventManager::RaiseRoutedEvent(
	RoutedEvent^ routedEvent,
	IRoutedEventSource^ source,
	ICustomRoutedEventArgs^ args) {

	// Determine the routing strategy
	switch (routedEvent->RoutingStrategy)
	{
	case RoutingStrategy::Direct:
		// Just raise it on this object
		RaiseDirectEvent(routedEvent, source, args);
		break;
	case RoutingStrategy::Bubble:
		RaiseBubbledEvent(routedEvent, source, args);
		break;
	case RoutingStrategy::Tunnel:
		RaiseTunnelledEvent(routedEvent, source, args);
		break;
	}
}

Windows::Foundation::EventRegistrationToken EventManager::AddHandler(
	RoutedEvent^ routedEvent,
	IRoutedEventSource^ source,
	TypedEventHandler<Platform::Object^, ICustomRoutedEventArgs^>^ handler) {
	return AddHandler(routedEvent, source, handler, false);
}
	
Windows::Foundation::EventRegistrationToken EventManager::AddHandler(
	RoutedEvent^ routedEvent,
	IRoutedEventSource^ source,
	TypedEventHandler<Platform::Object^, ICustomRoutedEventArgs^>^ handler,
	bool invokeForHandledEvents) {
	
	return source->GetRoutedEventManager()->AddHandlerForRoutedEvent(routedEvent, handler, invokeForHandledEvents);
}

void EventManager::RemoveHandler(
	RoutedEvent^ routedEvent,
	IRoutedEventSource^ source,
	Windows::Foundation::EventRegistrationToken token) {
	source->GetRoutedEventManager()->RemoveHandlerForRoutedEvent(routedEvent, token);
}

UINT64 EventManager::GetNextEventId() {
	UINT64 id = InterlockedIncrement(&_nextId);
	
	// 'id' is the incremented id, so we know that (id - 1) is assigned to this event
	return id - 1;
}
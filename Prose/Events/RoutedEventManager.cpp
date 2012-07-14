#include "pch.h"
#include "RoutedEventManager.h"
#include "RoutedEventHandlerInfo.h"

using namespace Prose::Events;

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

using namespace Platform::Collections;

RoutedEventManager::RoutedEventManager(void)
{
}

IIterable<RoutedEventHandlerInfo^>^ RoutedEventManager::GetHandlersForRoutedEvent(RoutedEvent^ routedEvent) {
	return GetOrCreateHandlerList(routedEvent)->GetHandlers();
}

Windows::Foundation::EventRegistrationToken RoutedEventManager::AddHandlerForRoutedEvent(RoutedEvent^ routedEvent, TypedEventHandler<Platform::Object^, ICustomRoutedEventArgs^>^ handler, bool invokeForHandledEvents) {
	return GetOrCreateHandlerList(routedEvent)->AddHandler(handler, invokeForHandledEvents);
}

void RoutedEventManager::RemoveHandlerForRoutedEvent(RoutedEvent^ routedEvent, Windows::Foundation::EventRegistrationToken token) {
	GetOrCreateHandlerList(routedEvent)->RemoveHandler(token);
}

auto RoutedEventManager::GetOrCreateHandlerList(RoutedEvent^ routedEvent) -> std::shared_ptr<RoutedEventHandlerList> {
	std::shared_ptr<RoutedEventHandlerList> handlerList = nullptr;
	if(!_handlerLists.count(routedEvent)) {
		handlerList = std::make_shared<RoutedEventHandlerList>();
		_handlerLists.insert(std::pair<RoutedEvent^, std::shared_ptr<RoutedEventHandlerList>>(routedEvent, handlerList));
	} else {
		handlerList = _handlerLists.at(routedEvent);
	}
	return handlerList;
}


RoutedEventManager::RoutedEventHandlerList::RoutedEventHandlerList(void) : _nextId(0), _handlers(ref new Vector<RoutedEventHandlerInfo^>()) { }

IIterable<RoutedEventHandlerInfo^>^ RoutedEventManager::RoutedEventHandlerList::GetHandlers() {
	return _handlers;
}

Windows::Foundation::EventRegistrationToken RoutedEventManager::RoutedEventHandlerList::AddHandler(TypedEventHandler<Platform::Object^, ICustomRoutedEventArgs^>^ handler, bool invokeForHandledEvents) {
	// Create a Handler Info structure
	auto info = ref new RoutedEventHandlerInfo(handler, invokeForHandledEvents, _nextId++);

	// Create a registration token
	Windows::Foundation::EventRegistrationToken tok;
	tok.Value = info->Id;

	// Add the handler
	_handlers->Append(info);

	// Return the token
	return tok;
}

void RoutedEventManager::RoutedEventHandlerList::RemoveHandler(Windows::Foundation::EventRegistrationToken token) {
	// Search for the handler with this ID
	for(UINT32 i = 0; i < _handlers->Size; i++) {
		if(_handlers->GetAt(i)->Id == token.Value) {
			_handlers->RemoveAt(i);
			return;
		}
	}
}

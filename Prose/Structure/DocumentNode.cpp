#include "pch.h"
#include "DocumentNode.h"
#include "..\Events\RoutedEventManager.h"

using namespace Prose::Structure;
using namespace Prose::Events;

using namespace Windows::UI::Xaml::Input;

RoutedEvent^ DocumentNode::_PointerEnteredEvent = EventManager::RegisterRoutedEvent(
	L"PointerEntered", RoutingStrategy::Bubble, PointerTextEventHandler::typeid, DocumentNode::typeid);

DocumentNode::DocumentNode(void) : _eventManager(ref new RoutedEventManager()) {
}

Windows::Foundation::EventRegistrationToken DocumentNode::PointerEntered::add(PointerTextEventHandler^ handler) {
	return EventManager::AddHandler(
		_PointerEnteredEvent, 
		this, 
		reinterpret_cast<CustomRoutedEventHandler^>(handler), 
		false);
}

void DocumentNode::PointerEntered::remove(Windows::Foundation::EventRegistrationToken token) {
	EventManager::RemoveHandler(_PointerEnteredEvent, this, token);
}

void DocumentNode::PointerEntered::raise(Platform::Object^ sender, Prose::Events::PointerTextEventArgs^ args) {
	EventManager::RaiseRoutedEvent(_PointerEnteredEvent, this, args);
}

void DocumentNode::FirePointerEntered(PointerTextEventArgs^ args) {
	PointerEntered(this, args);
}
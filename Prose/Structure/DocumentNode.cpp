#include "pch.h"
#include "DocumentNode.h"
#include "..\Events\RoutedEventManager.h"

using namespace Prose::Structure;
using namespace Prose::Events;

using namespace Windows::UI::Xaml::Input;

IMPLEMENT_ROUTED_EVENT(DocumentNode, Bubble, PointerTextEventHandler, PointerTextEventArgs^, PointerEntered);
IMPLEMENT_ROUTED_EVENT(DocumentNode, Bubble, PointerTextEventHandler, PointerTextEventArgs^, PointerExited);
IMPLEMENT_ROUTED_EVENT(DocumentNode, Bubble, PointerTextEventHandler, PointerTextEventArgs^, PointerMoved);
IMPLEMENT_ROUTED_EVENT(DocumentNode, Bubble, CustomRoutedEventHandler, CustomRoutedEventArgs^, Invalidated);

DocumentNode::DocumentNode(void) : _eventManager(ref new RoutedEventManager()) {
}

void DocumentNode::FirePointerEntered(PointerTextEventArgs^ args) {
	PointerEntered(this, args);
}

void DocumentNode::FirePointerExited(PointerTextEventArgs^ args) {
	PointerExited(this, args);
}

void DocumentNode::FirePointerMoved(PointerTextEventArgs^ args) {
	PointerMoved(this, args);
}
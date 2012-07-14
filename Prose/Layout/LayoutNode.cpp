#include "pch.h"
#include "LayoutNode.h"
#include "LayoutPointer.h"
#include "..\Events\RoutedEventManager.h"

using namespace Prose::Structure;
using namespace Prose::Layout;
using namespace Prose::Events;

IMPLEMENT_ROUTED_EVENT(LayoutNode, Bubble, PointerLayoutEventHandler, PointerLayoutEventArgs^, PointerEntered);
IMPLEMENT_ROUTED_EVENT(LayoutNode, Bubble, PointerLayoutEventHandler, PointerLayoutEventArgs^, PointerExited);
IMPLEMENT_ROUTED_EVENT(LayoutNode, Bubble, PointerLayoutEventHandler, PointerLayoutEventArgs^, PointerMoved);
IMPLEMENT_ROUTED_EVENT(LayoutNode, Bubble, CustomRoutedEventHandler, CustomRoutedEventArgs^, Invalidated);

LayoutNode::LayoutNode(Prose::Structure::DocumentNode^ structureNode) : _eventManager(ref new RoutedEventManager()), _structureNode(structureNode) {
}

void LayoutNode::FirePointerEntered(PointerLayoutEventArgs^ args) {
	// Fire my event
	PointerEntered(this, args);

	// TODO: Bubble?

	// Fire structure node event
	TextPointer^ ptr = args->LayoutPointer->GetTextPointer();
	PointerTextEventArgs^ textargs = ref new PointerTextEventArgs(
		StructureNode, ptr, args->PointerInfo);
	StructureNode->FirePointerEntered(textargs);
}

void LayoutNode::FirePointerExited(PointerLayoutEventArgs^ args) {
	// Fire my event
	PointerExited(this, args);

	// TODO: Bubble?

	// Fire structure node event
	TextPointer^ ptr = args->LayoutPointer->GetTextPointer();
	PointerTextEventArgs^ textargs = ref new PointerTextEventArgs(
		StructureNode, ptr, args->PointerInfo);
	StructureNode->FirePointerExited(textargs);
}

void LayoutNode::FirePointerMoved(PointerLayoutEventArgs^ args) {
	// Fire my event
	PointerMoved(this, args);

	// TODO: Bubble?

	// Fire structure node event
	TextPointer^ ptr = args->LayoutPointer->GetTextPointer();
	PointerTextEventArgs^ textargs = ref new PointerTextEventArgs(
		StructureNode, ptr, args->PointerInfo);
	StructureNode->FirePointerMoved(textargs);
}
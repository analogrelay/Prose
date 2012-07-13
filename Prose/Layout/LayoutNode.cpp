#include "pch.h"
#include "LayoutNode.h"
#include "LayoutPointer.h"

using namespace Prose::Structure;
using namespace Prose::Layout;
using namespace Prose::Events;

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
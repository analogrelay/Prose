#include "pch.h"
#include "LayoutInline.h"
#include "LayoutVisitor.h"

using namespace Prose;
using namespace Prose::Layout;
using namespace Prose::Structure;

LayoutInline::LayoutInline(Prose::Structure::StructureNode^ node, Platform::String^ text) : LayoutNode(node), _text(text) { }

void LayoutInline::Accept(LayoutVisitor^ visitor) { visitor->Visit(this); }

StructureNode^ LayoutInline::StructureNode::get() {
	return _node;
}
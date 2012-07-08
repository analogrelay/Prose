#include "pch.h"
#include "LayoutInline.h"
#include "LayoutVisitor.h"

using namespace Prose;
using namespace Prose::Layout;
using namespace Prose::Structure;

LayoutInline::LayoutInline(Prose::Structure::DocumentNode^ node, Platform::String^ text) : _node(node), _text(text) { }

void LayoutInline::Accept(LayoutVisitor^ visitor) { visitor->Visit(this); }

DocumentNode^ LayoutInline::StructureNode::get() {
	return _node;
}
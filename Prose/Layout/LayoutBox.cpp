#include "pch.h"
#include "LayoutBox.h"
#include "LayoutVisitor.h"
#include "LayoutInline.h"
#include "ChildNodeCollection.h"

#include <assert.h>

using namespace Prose;
using namespace Prose::Layout;
using namespace Prose::Structure;
using namespace Platform::Collections;
using namespace Windows::Foundation;

LayoutBox::LayoutBox(Prose::Structure::StructureNode^ node) : LayoutNode(node), _inlines(ref new Vector<LayoutInline^>()), _metrics(nullptr), _margin(0) { }
LayoutBox::LayoutBox(Prose::Structure::StructureNode^ node, Windows::UI::Xaml::Thickness margin) : LayoutNode(node), _inlines(ref new Vector<LayoutInline^>()), _metrics(nullptr), _margin(margin) { }

void LayoutBox::Accept(LayoutVisitor^ visitor) { visitor->Visit(this); }

StructureNode^ LayoutBox::StructureNode::get() {
	return _node;
}

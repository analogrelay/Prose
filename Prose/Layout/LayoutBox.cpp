#include "pch.h"
#include "LayoutBox.h"
#include "LayoutVisitor.h"
#include "LayoutInline.h"

#include <assert.h>

using namespace Prose;
using namespace Prose::Layout;
using namespace Prose::Structure;
using namespace Platform::Collections;
using namespace Windows::Foundation;

LayoutBox::LayoutBox(Prose::Structure::DocumentNode^ node) : _node(node), _inlines(ref new Vector<LayoutInline^>()), _metrics(nullptr), _margin(0) { }
LayoutBox::LayoutBox(Prose::Structure::DocumentNode^ node, Windows::UI::Xaml::Thickness margin) : _node(node), _inlines(ref new Vector<LayoutInline^>()), _metrics(nullptr), _margin(margin) { }

void LayoutBox::Accept(LayoutVisitor^ visitor) { visitor->Visit(this); }

LayoutPointer^ LayoutBox::HitTest(Point point) {
	// Run the hit test against the metrics
	INullable<UINT32>^ offset = Metrics->HitTest(point);
	
	if(!offset->HasValue) {
		return nullptr; // No match
	}
	UINT32 offsetVal = offset->Value;

	// Find the span
	UINT32 counter = 0;
	for(UINT32 i = 0; i < Inlines->Size; i++) {
		auto span = Inlines->GetAt(i);
		if(offsetVal >= counter && offsetVal < (counter + span->Text->Length())) {
			return ref new LayoutPointer(this, span, i, offsetVal - counter, offsetVal);
		}
		counter += span->Text->Length();
	}

	// No match?
	assert(false);
	return nullptr;
}

TextPointer^ LayoutBox::LayoutToText(LayoutPointer^ ptr) {
	if(ptr->Owner != this) {
		throw ref new Platform::InvalidArgumentException("Provided LayoutPointer must be owned by this Layout Node");
	}
	return ref new TextPointer(
		(reinterpret_cast<Paragraph^>(StructureNode)),
		(reinterpret_cast<Inline^>(ptr->Node->StructureNode)),
		ptr->NodeIndex,
		ptr->LocalOffset,
		ptr->GlobalOffset);
}

DocumentNode^ LayoutBox::StructureNode::get() {
	return _node;
}
